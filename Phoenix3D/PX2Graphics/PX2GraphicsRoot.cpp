// PX2GraphicsRoot.cpp

#include "PX2GraphicsRoot.hpp"
#include "PX2Environment.hpp"
#include "PX2StringHelp.hpp"
#include "PX2FString.hpp"
#include "PX2Renderer.hpp"
#include "PX2StdVC4Material.hpp"
#include "PX2VertexColor4Material.hpp"
#include "PX2LightAmbientConstant.hpp"
#include "PX2LightDiffuseConstant.hpp"
#include "PX2LightSpecularConstant.hpp"
#include "PX2LightAttenuationConstant.hpp"
#include "PX2LightModelDVectorConstant.hpp"
#include "PX2LightWorldDVectorConstant.hpp"
#include "PX2LightTexMaterial.hpp"
#include "PX2LightTex2Material.hpp"
#include "PX2SkinMaterial.hpp"
#include "PX2StdMaterial.hpp"
#include "PX2MaterialManager.hpp"
#include "PX2TriMesh.hpp"
#include "PX2VertexFormat.hpp"
#include "PX2StandardMesh.hpp"
#include "PX2Time.hpp"
using namespace PX2;

const std::string GraphicsRoot::sEmptyResPath = "EmptyResPath";
const std::string GraphicsRoot::sTerResPath = "TerResPath";
std::string GraphicsRoot::PX2Path;
//----------------------------------------------------------------------------
GraphicsRoot::GraphicsRoot ()
{
	mIsInEditor = false;
	mFogParam = Float4(0.0f, 120.0f, 0.0f, 0.0f);
	mFogColor = Float4::RED;
	mFogColorDist = Float4::BLUE;

	MaterialManager *mi = new0 MaterialManager();
	PX2_UNUSED(mi);
}
//----------------------------------------------------------------------------
GraphicsRoot::~GraphicsRoot ()
{
	MaterialManager *mi = MaterialManager::GetSingletonPtr();
	if (mi)
	{
		mi->Terminate();

		delete0(mi);
		MaterialManager::Set(0);
	}
}
//----------------------------------------------------------------------------
bool GraphicsRoot::Initlize ()
{
	// 你需要创建PX2_PATH环境变量，应用程序依赖于此查找各种资源文件。
	PX2Path = Environment::GetVariable("PX2_PATH");
	//if (PX2Path == "")
	//{
	//	assertion(false, "Please set the PX2_PATH environment variable.\n");
	//	FILE* ofile = fopen("ApplicationError.txt", "w");
	//	fprintf(ofile, "Please set the PX2_PATH environment variable.\n");
	//	fclose(ofile);
	//	//return false;
	//}
	//PX2Path += "/";

	InitTerm::ExecuteInitializers();

	std::string directory;

	// 应用程序当前目录
	Environment::InsertDirectory("/");

	// Camera
#if defined (PX2_USE_DX9)
	// DirectX使用深度在区间[0,1]内的矩阵。
	Camera::SetDefaultDepthType(Camera::PM_DEPTH_ZERO_TO_ONE);
#endif

#if defined(PX2_USE_OPENGL) || defined(PX2_USE_OPENGLES2)
	// OpenGL使用深度在区间[-1,1]内的矩阵。
	Camera::SetDefaultDepthType(Camera::PM_DEPTH_MINUS_ONE_TO_ONE);
#endif

	PX2_MATERIALMAN.Initlize();

	// create help meshs
	VertexFormat *vf = GetVertexFormat(GraphicsRoot::VFT_PC);
	StandardMesh stdMesh(vf);

	mTriMeshXY = stdMesh.Rectangle(4, 4, 20000.0f, 20000.0f);
	mTriMeshXY->UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);
	mTriMeshXY->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	mTriMeshXY->GetMaterialInstance()->GetMaterial()->GetWireProperty(0, 0)->Enabled = true;
	mTriMeshXY->Update(GetTimeInSeconds(), false);

	mTriMeshXZ = stdMesh.Rectangle(4, 4, 20000.0f, 20000.0f);
	mTriMeshXZ->WorldTransform.SetRotate(Matrix3f().MakeEulerXYZ(Mathf::HALF_PI,
		0.0f, 0.0f));
	mTriMeshXZ->UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);
	mTriMeshXZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	mTriMeshXZ->Update(GetTimeInSeconds(), false);

	mTriMeshYZ = stdMesh.Rectangle(4, 4, 20000.0f, 20000.0f);
	mTriMeshYZ->WorldTransform.SetRotate(Matrix3f().MakeEulerXYZ(0.0f,
		Mathf::HALF_PI, 0.0f));
	mTriMeshYZ->UpdateModelSpace(Renderable::GU_MODEL_BOUND_ONLY);
	mTriMeshYZ->SetMaterialInstance(VertexColor4Material::CreateUniqueInstance());
	mTriMeshYZ->Update(GetTimeInSeconds(), false);

	return true;
}
//-----------------------------------------------------------------------------
bool GraphicsRoot::Terminate ()
{
	mTriMeshXY = 0;
	mTriMeshXZ = 0;
	mTriMeshYZ = 0;

	PX2_MATERIALMAN.Terminate();

	mRenderSteps.clear();
	mCamera = 0;
	mAllLights.clear();
	mCreatedVFs.clear();

	Environment::RemoveAllDirectories();

	InitTerm::ExecuteTerminators();

	return true;
}
//----------------------------------------------------------------------------
void GraphicsRoot::SetRenderViewPort (Renderer *renderer, bool adjustCamera,
	const Sizef *projSize, const Rectf *sceneViewPort)
{
	if (mRect.IsEmpty()) return;

	Camera *camera = renderer->GetCamera();

	if (projSize && sceneViewPort && !sceneViewPort->IsEmpty())
	{
		float widthScale = mRect.Width()/projSize->Width;
		float heightScale = mRect.Height()/projSize->Height;

		float newX = mRect.Left + sceneViewPort->Left*widthScale;
		float newY = mRect.Bottom + sceneViewPort->Bottom*heightScale;
		float newWidth = sceneViewPort->Width()*widthScale;
		float newHeight = sceneViewPort->Height()*heightScale;
		renderer->SetViewport(Rectf(newX, newY, newWidth, newHeight));
	}
	else
	{
		renderer->SetViewport(mRect);
	}

	if (adjustCamera && camera->IsPerspective())
	{
		float upFovDegrees = 0.0f;
		float aspectRatio = 0.0f;
		float dMin = 0.0f;
		float dMax = 0.0f;
		camera->GetFrustum(upFovDegrees, aspectRatio, dMin, dMax);
		camera->SetFrustum(upFovDegrees, 
			(float)mRect.Width()/(float)mRect.Height(), dMin, dMax);
	}
}
//----------------------------------------------------------------------------
void GraphicsRoot::AddLight (Light *light)
{
	bool bIn = false;
	for (int i=0; i<(int)mAllLights.size(); i++)
	{
		if (light == mAllLights[i])
			bIn = true;
	}

	if (!bIn)
	{
		mAllLights.push_back(light);
	}
}
//----------------------------------------------------------------------------
void GraphicsRoot::RemoveLight (Light *light)
{
	std::vector<Pointer0<Light> >::iterator it = mAllLights.begin();
	for (; it!=mAllLights.end(); it++)
	{
		if (*it == light)
		{
			mAllLights.erase(it);
			return;
		}
	}
}
//----------------------------------------------------------------------------
void GraphicsRoot::ClearAllLights ()
{
	mAllLights.clear();
}
//----------------------------------------------------------------------------
int GraphicsRoot::GetNumLights ()
{
	return (int)mAllLights.size();
}
//----------------------------------------------------------------------------
Light *GraphicsRoot::GetLight (int index)
{
	int numLights = (int)mAllLights.size();
	if (index>=0 && index<numLights)
	{
		return mAllLights[index];
	}

	return 0;
}
//----------------------------------------------------------------------------
void GraphicsRoot::ComputeEnvironment (VisibleSet &vs)
{
	for (int i=0; i<vs.GetNumVisible(); i++)
	{
		PX2::Renderable *renderable = vs.GetVisible(i);
		PX2::APoint renPos = renderable->WorldTransform.GetTranslate();
		renderable->ClearLights();

		for (int j=0; j<GraphicsRoot::GetSingleton().GetNumLights(); j++)
		{
			PX2::Light *light = GraphicsRoot::GetSingleton().GetLight(j);
			PX2::APoint lightPos = light->Position;

			if (light->GetType() == Light::LT_DIRECTIONAL ||
				light->GetType() == Light::LT_AMBIENT)
			{
				renderable->AddLight(light);
			}
			else if (light->GetType() == Light::LT_POINT)
			{
				Vector3f diff = renPos - lightPos;
				float len = diff.Length();
				if (len <= 8)
					renderable->AddLight(light);
			}
		}
	}

	for (int i=0; i<vs.GetNumVisible(); i++)
	{
		PX2::Renderable *renderable = vs.GetVisible(i);

		PX2::Light *lightDir = 0;
		for (int j=0; j<renderable->GetNumLights(); j++)
		{
			PX2::Light *light = renderable->GetLight(j);
			if (light->GetType() == Light::LT_DIRECTIONAL)
			{
				lightDir = light;
				break;
			}
		}

		PX2::MaterialInstance *inst = renderable->GetMaterialInstance();
		if (!inst)
			continue;

		PX2::Material *mtl = inst->GetMaterial();

		PX2::StdMaterial *stdMtl = DynamicCast<StdMaterial>(mtl);
		PX2::StdVC4Material *stdVC4Mtl = DynamicCast<StdVC4Material>(mtl);
		PX2::LightTexMaterial *lightTexMtl = DynamicCast<LightTexMaterial>(mtl);
		PX2::LightTex2Material *lightTex2Mtl = DynamicCast<LightTex2Material>(mtl);
		PX2::SkinMaterial *skinMtl = DynamicCast<SkinMaterial>(mtl);

		LightModelDVectorConstant *modelDVectorConstant = 0;
		LightWorldDVectorConstant *lightWorldDVectorConstant = 0;
		LightAmbientConstant *ambConstant = 0;
		LightDiffuseConstant *difConstant = 0;
		LightSpecularConstant *specConstant = 0;

		if ((lightTexMtl||lightTex2Mtl) && lightDir)
		{
			lightWorldDVectorConstant = DynamicCast<LightWorldDVectorConstant>(inst->GetVertexConstant(0, "LightWorldDirection"));
			specConstant = DynamicCast<LightSpecularConstant>(inst->GetVertexConstant(0, "LightSpecular"));

			if (lightWorldDVectorConstant)
				lightWorldDVectorConstant->SetLight(lightDir);

			if (specConstant)
				specConstant->SetLight(lightDir);
		}
		else if ((stdMtl||stdVC4Mtl) && lightDir)
		{
			lightWorldDVectorConstant = DynamicCast<LightWorldDVectorConstant>(inst->GetVertexConstant(0, "LightWorldDirection"));

			if (lightWorldDVectorConstant)
				lightWorldDVectorConstant->SetLight(lightDir);

			ambConstant = DynamicCast<LightAmbientConstant>(inst->GetVertexConstant(0, "gLightAmbient"));
			difConstant = DynamicCast<LightDiffuseConstant>(inst->GetVertexConstant(0, "gLightDiffuse"));
			specConstant = DynamicCast<LightSpecularConstant>(inst->GetVertexConstant(0, "gLightSpecular"));

			if (modelDVectorConstant)
				modelDVectorConstant->SetLight(lightDir);

			if (ambConstant)
				ambConstant->SetLight(lightDir);

			if (difConstant)
				difConstant->SetLight(lightDir);

			if (specConstant)
				specConstant->SetLight(lightDir);
		}
		else if (skinMtl && lightDir)
		{
			lightWorldDVectorConstant = DynamicCast<LightWorldDVectorConstant>(inst->GetVertexConstant(0, "LightWorldDirection"));

			if (lightWorldDVectorConstant)
				lightWorldDVectorConstant->SetLight(lightDir);

			ambConstant = DynamicCast<LightAmbientConstant>(inst->GetVertexConstant(0, "gLightAmbient"));
			difConstant = DynamicCast<LightDiffuseConstant>(inst->GetVertexConstant(0, "gLightDiffuse"));
			specConstant = DynamicCast<LightSpecularConstant>(inst->GetVertexConstant(0, "gLightSpecular"));

			if (modelDVectorConstant)
				modelDVectorConstant->SetLight(lightDir);

			if (ambConstant)
				ambConstant->SetLight(lightDir);

			if (difConstant)
				difConstant->SetLight(lightDir);

			if (specConstant)
				specConstant->SetLight(lightDir);
		}
	}
}
//----------------------------------------------------------------------------
bool GraphicsRoot::AddRenderStep(RenderStep *step)
{
	if (IsHasRenderStep(step))
		return false;

	mRenderSteps.push_back(step);

	return true;
}
//----------------------------------------------------------------------------
bool GraphicsRoot::IsHasRenderStep(RenderStep *step) const
{
	for (int i = 0; i < (int)mRenderSteps.size(); i++)
	{
		if (step == mRenderSteps[i])
		{
			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
bool GraphicsRoot::RemoveRenderStep(RenderStep *step)
{
	std::vector<RenderStepPtr>::iterator it = mRenderSteps.begin();
	for (; it != mRenderSteps.end(); it++)
	{
		if (*it == step)
		{
			mRenderSteps.erase(it);

			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------
void GraphicsRoot::ComputeVisibleSet()
{
	for (int i = 0; i < (int)mRenderSteps.size(); i++)
	{
		mRenderSteps[i]->ComputeVisibleSet();
	}
}
//----------------------------------------------------------------------------
void GraphicsRoot::Draw()
{
	for (int i = 0; i < (int)mRenderSteps.size(); i++)
	{
		mRenderSteps[i]->Draw();
	}
}
//----------------------------------------------------------------------------
VertexFormat *GraphicsRoot::GetVertexFormat(VertexFormatType type)
{
	std::map<VertexFormatType, VertexFormatPtr >::iterator it =
		mCreatedVFs.find(type);

	if (it != mCreatedVFs.end())
	{
		return it->second;
	}
	else
	{
		VertexFormat *vf = 0;
		if (VFT_PT1 == type)
		{
			vf = VertexFormat::Create(2,
				VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
				VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0);
		}
		else if (VFT_PT2 == type)
		{
			vf = VertexFormat::Create(3,
				VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
				VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 0,
				VertexFormat::AU_TEXCOORD, VertexFormat::AT_FLOAT2, 1);
		}
		else if (VFT_PC == type)
		{
			vf = VertexFormat::Create(2,
				VertexFormat::AU_POSITION, VertexFormat::AT_FLOAT3, 0,
				VertexFormat::AU_COLOR, VertexFormat::AT_FLOAT4, 0);
		}

		mCreatedVFs[type] = vf;

		return vf;
	}

	return 0;
}
//----------------------------------------------------------------------------
ObjectLoadFun GraphicsRoot::msUserLoadFun = 0;
//----------------------------------------------------------------------------
void GraphicsRoot::SetUserLoadFun(ObjectLoadFun userLoadFun)
{
	msUserLoadFun = userLoadFun;
}
//----------------------------------------------------------------------------