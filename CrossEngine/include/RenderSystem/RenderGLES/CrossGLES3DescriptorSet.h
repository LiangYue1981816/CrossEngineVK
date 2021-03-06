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

	class CROSS_EXPORT CGLES3DescriptorSet : public CGfxDescriptorSet
	{
		friend class CGLES3DescriptorSetManager;


	protected:
		CGLES3DescriptorSet(CGLES3Device *pDevice, CGLES3DescriptorSetManager *pDescriptorSetManager, const CGfxDescriptorSetLayoutPtr &ptrDescriptorSetLayout);
		virtual ~CGLES3DescriptorSet(void);


	protected:
		void Release(void);

	public:
		CGLES3Device* GetDevice(void) const;
		HANDLE GetHandle(void) const;
		const CGfxDescriptorSetLayoutPtr& GetDescriptorSetLayoutPtr(void) const;

	public:
		void SetTexture(uint32_t binding, const CGfxTexturePtr &ptrTexture);
		void SetRenderTexture(uint32_t binding, const CGfxRenderTexturePtr &ptrRenderTexture);
		void SetUniformBuffer(uint32_t binding, const CGfxUniformBufferPtr &ptrUniformBuffer);
		void UpdateDescriptorSets(void);

	public:
		void SetUniformBufferData(uint32_t binding, size_t offset, size_t size, const void *pBuffer);

	public:
		const CGfxTexturePtr& GetTexture(uint32_t binding) const;
		const CGfxRenderTexturePtr& GetRenderTexture(uint32_t binding) const;
		const CGfxUniformBufferPtr& GetUniformBuffer(uint32_t binding) const;
		const CGfxDescriptorSetLayoutPtr& GetDescriptorSetLayout(void) const;


	protected:
		CGfxDescriptorSetLayoutPtr m_ptrDescriptorSetLayout;

	protected:
		eastl::map<uint32_t, CGfxTexturePtr> m_ptrTextures;
		eastl::map<uint32_t, CGfxRenderTexturePtr> m_ptrRenderTextures;
		eastl::map<uint32_t, CGfxUniformBufferPtr> m_ptrUniformBuffers;
		eastl::map<uint32_t, uint32_t> m_uniformBufferOffsets;

	protected:
		CGLES3DescriptorSetManager *m_pDescriptorSetManager;

	protected:
		CGLES3Device *m_pDevice;
	};

}
