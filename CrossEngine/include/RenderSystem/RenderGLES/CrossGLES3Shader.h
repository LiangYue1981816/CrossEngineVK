/****************************************************************************
Copyright (c) 2017 LiangYue.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sub license, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#pragma once
#include "CrossEngine.h"


namespace CrossEngine {

	class CROSS_EXPORT CGLES3Shader : public CGfxShader
	{
		friend class CGLES3ShaderManager;


	protected:
		CGLES3Shader(CGLES3Device *pDevice, CGfxResourceManager *pResourceManager);
		virtual ~CGLES3Shader(void);


	public:
		CGLES3Device* GetDevice(void) const;
		HANDLE GetHandle(void) const;
		const spirv_cross::Compiler* GetShaderCompiler(void) const;

	public:
		BOOL Create(const char *szSource, size_t length, VkShaderStageFlagBits flags);
		BOOL Create(const uint32_t *words, size_t numWords, VkShaderStageFlagBits flags);
		void Destroy(void);
		void DumpLog(void) const;


	protected:
		GLuint m_program;
		spirv_cross::Compiler *m_pShaderCompiler;

	protected:
		CGLES3Device *m_pDevice;
	};

}
