/*
* Phoenix 3D 游戏引擎 Version 2.0
*
* Copyright (C) 2009-2011 http://www.Phoenix3d.org/
*
* 文件名称	：	PX2PixelShader.hpp
*
* 版本		:	1.0 (2011/02/01)
*
* 作者		：	more
*
*/

#ifndef PX2PIXELSHADER_HPP
#define PX2PIXELSHADER_HPP

#include "PX2GraphicsPre.hpp"
#include "PX2Shader.hpp"

namespace PX2
{

	/// 像素着色器类
	class PixelShader : public Shader
	{
		PX2_DECLARE_RTTI;
		PX2_DECLARE_NAMES;
		PX2_DECLARE_PROPERTY;
		PX2_DECLARE_STREAM(PixelShader);

	public:
		PixelShader (const std::string& programName, int numInputs,
			int numOutputs, int numConstants, int numSamplers, bool profileOwner);

		virtual ~PixelShader ();

		// 像素着色器版本信息
		enum Profile
		{
			PP_NONE,
			PP_PS_1_1,
			PP_PS_2_0,
			PP_PS_3_0,
			PP_ARBFP1,
			PP_OPENGLES2
		};

		static void SetProfile (Profile profile);
		static Profile GetProfile ();

	protected:
		static Profile msProfile;
	};

	PX2_REGISTER_STREAM(PixelShader);
	typedef Pointer0<PixelShader> PixelShaderPtr;

}

#endif
