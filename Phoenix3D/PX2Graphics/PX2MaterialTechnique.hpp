/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2MaterialTechnique.hpp
*
* 版本		:	1.0 (2011/02/01)
*
* 作者		：	more
*
*/

#ifndef PX2MATERIALTECHNIQUE_HPP
#define PX2MATERIALTECHNIQUE_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2MaterialPass.hpp"

namespace PX2
{

	class MaterialTechnique : public Object
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(MaterialTechnique);

	public:
		MaterialTechnique ();
		virtual ~MaterialTechnique ();

		void SetTag(const std::string &tag);
		const std::string &GetTag() const;

		// 插入一个新的pass到pass队列末尾。
		void InsertPass (MaterialPass* pass);
		void PopLastPass ();

		// 成员访问
		inline int GetNumPasses () const;
		MaterialPass* GetPass (int passIndex) const;

		// 访问每个pass的元素
		VertexShader* GetVertexShader (int passIndex) const;
		PixelShader* GetPixelShader (int passIndex) const;
		AlphaProperty* GetAlphaProperty (int passIndex) const;
		CullProperty* GetCullProperty (int passIndex) const;
		DepthProperty* GetDepthProperty (int passIndex) const;
		OffsetProperty* GetOffsetProperty (int passIndex) const;
		StencilProperty* GetStencilProperty (int passIndex) const;
		WireProperty* GetWireProperty (int passIndex) const;

	protected:
		std::string mTag;
		std::vector<MaterialPassPtr> mPasses;
	};

	PX2_REGISTER_STREAM(MaterialTechnique);
	typedef Pointer0<MaterialTechnique> MaterialTechniquePtr;
#include "PX2MaterialTechnique.inl"

}

#endif
