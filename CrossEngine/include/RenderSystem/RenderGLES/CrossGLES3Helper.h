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

	class CROSS_EXPORT CGLES3Helper
	{
	public:
		static const char* glEnumToString(GLenum param);

		static GLboolean glIsFormatDepthOnly(GLenum format);
		static GLboolean glIsFormatStencilOnly(GLenum format);
		static GLboolean glIsFormatDepthStencil(GLenum format);

		static GLenum glTranslateFormat(VkFormat format, GLenum &internalFormat, GLenum &externalFormat, GLenum &type);
		static GLenum glTranslateMagFilter(VkFilter magFilter);
		static GLenum glTranslateMinFilter(VkFilter minFilter, VkSamplerMipmapMode mipmapMode);
		static GLenum glTranslateAddressMode(VkSamplerAddressMode addressMode);
		static GLenum glTranslateStencilOp(VkStencilOp op);
		static GLenum glTranslateCompareOp(VkCompareOp op);
		static GLenum glTranslateBlendOp(VkBlendOp op);
		static GLenum glTranslateBlendFactor(VkBlendFactor factor);
		static GLenum glTranslateCullMode(VkCullModeFlags cullMode);
		static GLenum glTranslateFrontFace(VkFrontFace frontFace);
		static GLenum glTranslateStencilFace(VkStencilFaceFlags stencilFace);
		static GLenum glTranslatePrimitiveTopology(VkPrimitiveTopology topology);
		static GLenum glTranslateIndexType(VkIndexType type);

		static GLsizei glGetIndexTypeSize(VkIndexType type);
	};

}
