// PX2ShaderParameters.hpp

#ifndef PX2SHADERPARAMETERS_HPP
#define PX2SHADERPARAMETERS_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Shader.hpp"
#include "PX2ShaderFloat.hpp"
#include "PX2Texture.hpp"

namespace PX2
{

	/// 着色器参数类
	/**
	* 一个材质，为每个渲染pass维护一个“着色器参数”，一个“着色器参数”内保存
	* 着色器所有所需的“着色器常量”。
	*/
	class ShaderParameters : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(ShaderParameters);

	public:
		ShaderParameters (Shader* shader);
		virtual ~ShaderParameters ();

		// 成员访问
		inline int GetNumConstants () const;
		inline int GetNumTextures () const;
		inline ShaderFloatPtr* GetConstants () const;
		inline TexturePtr* GetTextures () const;

		// 这些函数设置constants/textures。如果函数成功，函数返回在常量数组中的
		// 索引。
		int SetConstant (const std::string& name, ShaderFloat* sfloat);
		int SetTexture (const std::string& name, Texture* texture);

		// 通过上面函数返回的索引，直接设置着色器常量
		void SetConstant (int handle, ShaderFloat* sfloat);
		void SetTexture (int handle, Texture* texture);

		// 成员访问
		ShaderFloat* GetConstant (const std::string& name) const;
		Texture* GetTexture (const std::string& name) const;

		// handle由上面的Set*函数返回获得
		ShaderFloat* GetConstant (int handle) const;
		Texture* GetTexture (int handle) const;

		// 在绘制的时候更新常量
		void UpdateConstants (const Renderable* renderable, const Camera* camera);

	protected:
		ShaderPtr mShader;
		int mNumConstants;
		ShaderFloatPtr* mConstants;
		int mNumTextures;
		TexturePtr* mTextures;
		std::vector<std::string> mTextureResPath;
	};

	PX2_REGISTER_STREAM(ShaderParameters);
	typedef Pointer0<ShaderParameters> ShaderParametersPtr;
#include "PX2ShaderParameters.inl"

}

#endif
