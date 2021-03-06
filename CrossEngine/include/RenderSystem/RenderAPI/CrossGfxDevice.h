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

	#define VERTEX_BUFFER_BINDING 0
	#define INSTANCE_BUFFER_BINDING 1

	typedef enum AttributeFlagBits {
		VERTEX_ATTRIBUTE_POSITION = 0x00000001,
		VERTEX_ATTRIBUTE_NORMAL = 0x00000002,
		VERTEX_ATTRIBUTE_BINORMAL = 0x00000004,
		VERTEX_ATTRIBUTE_COLOR = 0x00000008,
		VERTEX_ATTRIBUTE_TEXCOORD0 = 0x00000010,
		VERTEX_ATTRIBUTE_TEXCOORD1 = 0x00000020,
		VERTEX_ATTRIBUTE_INDICES = 0x00000040,
		VERTEX_ATTRIBUTE_WEIGHTS = 0x00000080,

		VERTEX_ATTRIBUTE_MASK = 
		VERTEX_ATTRIBUTE_POSITION | 
		VERTEX_ATTRIBUTE_NORMAL | 
		VERTEX_ATTRIBUTE_BINORMAL | 
		VERTEX_ATTRIBUTE_COLOR | 
		VERTEX_ATTRIBUTE_TEXCOORD0 |
		VERTEX_ATTRIBUTE_TEXCOORD1 |
		VERTEX_ATTRIBUTE_INDICES |
		VERTEX_ATTRIBUTE_WEIGHTS,

		INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL0 = 0x00000100,
		INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL1 = 0x00000200,
		INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL2 = 0x00000400,
		INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL3 = 0x00000800,

		INSTANCE_ATTRIBUTE_TRANSFORM = 
		INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL0 |
		INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL1 |
		INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL2 |
		INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL3,

		INSTANCE_ATTRIBUTE_MASK = 
		INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL0 |
		INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL1 |
		INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL2 |
		INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL3,

		ATTRIBUTE_FLAG_COUNT = 12
	} AttributeFlagBits;


	class CROSS_EXPORT CGfxDevice
	{
	protected:
		CGfxDevice(void)
		{

		}
		virtual ~CGfxDevice(void)
		{

		}


	public:
		uint32_t GetStride(uint32_t format) const;
		uint32_t GetAttributeFlag(const char *szName) const;
		uint32_t GetAttributeSize(uint32_t attribute) const;
		uint32_t GetAttributeOffset(uint32_t format, uint32_t attribute) const;
		uint32_t GetAttributeComponents(uint32_t attribute) const;
		uint32_t GetAttributeLocation(uint32_t attribute) const;
		VkFormat GetAttributeFormat(uint32_t attribute) const;

	public:
		virtual CGfxInstance* GetInstance(void) const = 0;
		virtual CGfxQueue* GetComputeQueue(void) const = 0;
		virtual CGfxQueue* GetGraphicsQueue(void) const = 0;
		virtual CGfxQueue* GetTransferQueue(void) const = 0;

	public:
		virtual void ResetCommandBufferPool(uint32_t pool) = 0;
		virtual void AllocCommandBufferPool(uint32_t pool) = 0;
		virtual CGfxCommandBufferPtr AllocCommandBuffer(uint32_t pool, VkCommandBufferLevel level) = 0;

		virtual void ResetDescriptorSetPool(uint32_t pool) = 0;
		virtual void AllocDescriptorSetPool(uint32_t pool) = 0;
		virtual CGfxDescriptorSetPtr AllocDescriptorSet(uint32_t pool, const CGfxDescriptorSetLayoutPtr &ptrDescriptorSetLayout) = 0;
		virtual CGfxDescriptorSetPtr AllocDescriptorSet(uint32_t pool, uint32_t set, const CGfxPipelineComputePtr &ptrPipelineCompute) = 0;
		virtual CGfxDescriptorSetPtr AllocDescriptorSet(uint32_t pool, uint32_t set, const CGfxPipelineGraphicsPtr &ptrPipelineGraphics) = 0;
		virtual CGfxDescriptorSetLayoutPtr AllocDescriptorSetLayout(uint32_t set) = 0;

		virtual CGfxIndexBufferPtr NewIndexBuffer(void) = 0;
		virtual CGfxVertexBufferPtr NewVertexBuffer(void) = 0;
		virtual CGfxUniformBufferPtr NewUniformBuffer(void) = 0;
		virtual CGfxTexturePtr NewTexture(void) = 0;
		virtual CGfxRenderTexturePtr NewRenderTexture(void) = 0;
		virtual CGfxShaderPtr NewShader(void) = 0;
		virtual CGfxMaterialPtr NewMaterial(void) = 0;
		virtual CGfxPipelineComputePtr NewPipelineCompute(void) = 0;
		virtual CGfxPipelineGraphicsPtr NewPipelineGraphics(uint32_t numAttachments) = 0;
		virtual CGfxRenderPassPtr NewRenderPass(uint32_t numAttachments, uint32_t numSubpasses) = 0;
		virtual CGfxFrameBufferPtr NewFrameBuffer(uint32_t numAttachments) = 0;

	public:
		virtual void SetShaderCachePath(const char *szPath) = 0;
		virtual void AddShaderIncludePath(const char *szPath) = 0;
		virtual void AddShaderMacroDefinition(const char *szName) = 0;
		virtual void AddShaderMacroDefinition(const char *szName, const char *szValue) = 0;
		virtual BOOL PrecompileShader(const char *szSource, size_t length, VkShaderStageFlagBits flags, eastl::vector<uint32_t> &words) = 0;

	public:
		virtual int WaitIdle(void) const = 0;

	public:
		virtual void DumpLog(void) const = 0;
	};

}
