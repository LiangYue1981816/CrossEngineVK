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

	class CROSS_EXPORT CGLES3CommandBindDescriptorSetGraphics : public CGfxCommandBase
	{
		friend class CGLES3CommandBuffer;


	protected:
		CGLES3CommandBindDescriptorSetGraphics(const CGfxDescriptorSetPtr &ptrDescriptorSet, const CGfxPipelineGraphicsPtr &ptrPipelineGraphics)
		{
			m_ptrDescriptorSet = ptrDescriptorSet;
			m_ptrPipelineGraphics = ptrPipelineGraphics;
		}


	protected:
		virtual void Execute(void) const
		{
			if (m_ptrDescriptorSet.IsNull() || m_ptrDescriptorSet->GetHandle() == NULL) {
				return;
			}

			if (m_ptrPipelineGraphics.IsNull() || m_ptrPipelineGraphics->GetHandle() == NULL) {
				return;
			}

			const CGLES3DescriptorSet *pDescriptorSet = (CGLES3DescriptorSet *)((CGfxDescriptorSet *)m_ptrDescriptorSet);
			const CGLES3PipelineGraphics *pPipelineGraphics = (CGLES3PipelineGraphics *)((CGfxPipelineGraphics *)m_ptrPipelineGraphics);

			GLuint indexTexUnit = 0;
			Bind(pPipelineGraphics->GetShader(VK_SHADER_STAGE_VERTEX_BIT), pDescriptorSet, indexTexUnit);
			Bind(pPipelineGraphics->GetShader(VK_SHADER_STAGE_FRAGMENT_BIT), pDescriptorSet, indexTexUnit);
		}

		void Bind(const CGfxShaderPtr &ptrShader, const CGLES3DescriptorSet *pDescriptorSet, GLuint &indexTexUnit) const
		{
			if (ptrShader.IsNull() || ptrShader->GetHandle() == NULL) {
				return;
			}

			BindUniformBlocks((GLuint)ptrShader->GetHandle(), pDescriptorSet);
			BindSampledImages((GLuint)ptrShader->GetHandle(), pDescriptorSet, indexTexUnit);
			BindInputAttachments((GLuint)ptrShader->GetHandle(), pDescriptorSet, indexTexUnit);
		}

		void BindUniformBlocks(GLuint program, const CGLES3DescriptorSet *pDescriptorSet) const
		{
			CGLES3DescriptorSetLayout *pDescriptorSetLayout = pDescriptorSet->GetDescriptorSetLayout();
			const std::map<uint32_t, uint32_t> &uniformBlockBindings = pDescriptorSetLayout->GetUniformBlockBindings(program);

			for (const auto &itBinding : uniformBlockBindings) {
				GLuint binding = itBinding.first;
				GLuint location = itBinding.second;

				const CGfxUniformBufferPtr &ptrUniformBuffer = pDescriptorSet->GetUniformBuffer(binding);
				if (ptrUniformBuffer.IsNull() || ptrUniformBuffer->GetHandle() == NULL) continue;

				const uint32_t offset = pDescriptorSet->GetUniformBufferOffset(binding);
				const VkDescriptorBufferInfo &bufferInfo = ptrUniformBuffer->GetDescriptorBufferInfo(pDescriptorSetLayout->GetSet(), binding);
				glBindBufferRange(GL_UNIFORM_BUFFER, binding, (GLuint)ptrUniformBuffer->GetHandle(), bufferInfo.offset + offset, bufferInfo.range);
				glUniformBlockBinding(program, location, binding);
			}
		}

		void BindSampledImages(GLuint program, const CGLES3DescriptorSet *pDescriptorSet, GLuint &indexTexUnit) const
		{
			CGLES3DescriptorSetLayout *pDescriptorSetLayout = pDescriptorSet->GetDescriptorSetLayout();
			const std::map<uint32_t, uint32_t> &sampledImageBindings = pDescriptorSet->GetDescriptorSetLayout()->GetSampledImageBindings(program);

			for (const auto &itBinding : sampledImageBindings) {
				GLuint binding = itBinding.first;
				GLuint location = itBinding.second;

				const CGfxTexturePtr &ptrTexture = pDescriptorSet->GetTexture(binding);
				if (ptrTexture.IsNull() || ptrTexture->GetHandle() == NULL) continue;

				const CGLES3Texture *pTexture = (CGLES3Texture *)((CGfxTexture *)ptrTexture);
				glActiveTexture(GL_TEXTURE0 + indexTexUnit);
				glBindSampler(indexTexUnit, pTexture->GetSampler());
				glBindTexture(pTexture->GetTarget(), (GLuint)pTexture->GetHandle());
				glProgramUniform1i(program, location, indexTexUnit);

				indexTexUnit++;
			}
		}

		void BindInputAttachments(GLuint program, const CGLES3DescriptorSet *pDescriptorSet, GLuint &indexTexUnit) const
		{
			CGLES3DescriptorSetLayout *pDescriptorSetLayout = pDescriptorSet->GetDescriptorSetLayout();
			const std::map<uint32_t, uint32_t> &inputAttachmentBindings = pDescriptorSet->GetDescriptorSetLayout()->GetInputAttachmentBindings(program);

			for (const auto &itBinding : inputAttachmentBindings) {
				GLuint binding = itBinding.first;
				GLuint location = itBinding.second;

				const CGfxRenderTexturePtr &ptrRenderTexture = pDescriptorSet->GetRenderTexture(binding);
				if (ptrRenderTexture.IsNull() || ptrRenderTexture->GetHandle() == NULL) continue;

				const CGLES3RenderTexture *pRenderTexture = (CGLES3RenderTexture *)((CGfxRenderTexture *)ptrRenderTexture);
				glActiveTexture(GL_TEXTURE0 + indexTexUnit);
				glBindSampler(indexTexUnit, pRenderTexture->GetSampler());
				glBindTexture(pRenderTexture->GetTarget(), (GLuint)pRenderTexture->GetHandle());
				glProgramUniform1i(program, location, indexTexUnit);

				indexTexUnit++;
			}
		}

	protected:
		CGfxDescriptorSetPtr m_ptrDescriptorSet;
		CGfxPipelineGraphicsPtr m_ptrPipelineGraphics;
	};

}