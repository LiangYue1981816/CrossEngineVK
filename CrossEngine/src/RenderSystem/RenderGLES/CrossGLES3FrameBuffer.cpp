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

#include "_CrossEngine.h"


namespace CrossEngine {

	CGLES3FrameBuffer::CGLES3FrameBuffer(CGLES3Device *pDevice, CGfxResourceManager *pResourceManager, uint32_t numAttachments)
		: CGfxFrameBuffer(pResourceManager)
		, m_pDevice(pDevice)
		, m_framebuffer(0)
		, m_framebufferMSAA(0)

		, m_width(0)
		, m_height(0)
	{
		m_attachments.resize(numAttachments);
	}

	CGLES3FrameBuffer::~CGLES3FrameBuffer(void)
	{

	}

	CGLES3Device* CGLES3FrameBuffer::GetDevice(void) const
	{
		return m_pDevice;
	}

	HANDLE CGLES3FrameBuffer::GetHandle(void) const
	{
		return (HANDLE)m_framebuffer;
	}

	HANDLE CGLES3FrameBuffer::GetHandleMSAA(void) const
	{
		return (HANDLE)m_framebufferMSAA;
	}

	BOOL CGLES3FrameBuffer::Create(HANDLE hRenderPass)
	{
		if (CompatibilityCheck((const CGLES3RenderPass *)hRenderPass) == FALSE) {
			return FALSE;
		}

		glGenFramebuffers(1, &m_framebuffer);
		glGenFramebuffers(1, &m_framebufferMSAA);

		return TRUE;
	}

	BOOL CGLES3FrameBuffer::CompatibilityCheck(const CGLES3RenderPass *pRenderPass) const
	{
		if (m_attachments.size() != pRenderPass->GetAttachmentCount()) {
			return FALSE;
		}

		for (uint32_t indexAttachment = 0; indexAttachment < pRenderPass->GetAttachmentCount(); indexAttachment++) {
			const VkAttachmentDescription *pAttachmentDescription = pRenderPass->GetAttachmentDescription(indexAttachment);

			GLenum type;
			GLenum internalFormat;
			GLenum externalFormat;
			CGLES3Helper::glTranslateFormat(pAttachmentDescription->format, internalFormat, externalFormat, type);

			if (m_attachments[indexAttachment].format != externalFormat) {
				return FALSE;
			}
		}

		return TRUE;
	}

	void CGLES3FrameBuffer::Destroy(void)
	{
		if (m_framebuffer) {
			glDeleteFramebuffers(1, &m_framebuffer);
		}

		if (m_framebufferMSAA) {
			glDeleteFramebuffers(1, &m_framebufferMSAA);
		}

		m_framebuffer = 0;
		m_framebufferMSAA = 0;

		m_width = 0;
		m_height = 0;
	}

	BOOL CGLES3FrameBuffer::SetAttachment(uint32_t indexAttachment, GLenum target, GLenum format, uint32_t width, uint32_t height, HANDLE hImageView)
	{
		if (indexAttachment >= m_attachments.size()) {
			return FALSE;
		}

		if (m_width == 0) m_width = width;
		if (m_height == 0) m_height = height;
		if (m_width != width || m_height != height) return FALSE;

		m_attachments[indexAttachment].target = target;
		m_attachments[indexAttachment].format = format;
		m_attachments[indexAttachment].texture = (GLuint)hImageView;

		return TRUE;
	}

	BOOL CGLES3FrameBuffer::SetPresentAttachment(uint32_t indexAttachment, VkFormat format, uint32_t width, uint32_t height, HANDLE hImageView)
	{
		GLenum type;
		GLenum internalFormat;
		GLenum externalFormat;
		CGLES3Helper::glTranslateFormat(format, internalFormat, externalFormat, type);
		
		if (SetAttachment(indexAttachment, GL_TEXTURE_2D, externalFormat, width, height, hImageView)) {
			m_attachments[indexAttachment].ptrRenderTexture.Release();
			return TRUE;
		}

		return FALSE;
	}

	BOOL CGLES3FrameBuffer::SetColorAttachment(uint32_t indexAttachment, const CGfxRenderTexturePtr &ptrRenderTexture)
	{
		if (SetAttachment(indexAttachment, ((CGLES3RenderTexture *)((CGfxRenderTexture *)ptrRenderTexture))->GetTarget(), ((CGLES3RenderTexture *)((CGfxRenderTexture *)ptrRenderTexture))->GetFormat(), ptrRenderTexture->GetWidth(), ptrRenderTexture->GetHeight(), ptrRenderTexture->GetHandle())) {
			m_attachments[indexAttachment].ptrRenderTexture = ptrRenderTexture;
			return TRUE;
		}

		return FALSE;
	}

	BOOL CGLES3FrameBuffer::SetDepthStencilAttachment(uint32_t indexAttachment, const CGfxRenderTexturePtr &ptrRenderTexture)
	{
		if (SetAttachment(indexAttachment, ((CGLES3RenderTexture *)((CGfxRenderTexture *)ptrRenderTexture))->GetTarget(), ((CGLES3RenderTexture *)((CGfxRenderTexture *)ptrRenderTexture))->GetFormat(), ptrRenderTexture->GetWidth(), ptrRenderTexture->GetHeight(), ptrRenderTexture->GetHandle())) {
			m_attachments[indexAttachment].ptrRenderTexture = ptrRenderTexture;
			return TRUE;
		}

		return FALSE;
	}

	uint32_t CGLES3FrameBuffer::GetWidth(void) const
	{
		return m_width;
	}

	uint32_t CGLES3FrameBuffer::GetHeight(void) const
	{
		return m_height;
	}

	GLuint CGLES3FrameBuffer::GetRenderTexture(uint32_t indexAttachment) const
	{
		return indexAttachment < m_attachments.size() ? m_attachments[indexAttachment].texture : 0;
	}

	GLenum CGLES3FrameBuffer::GetRenderTextureTarget(uint32_t indexAttachment) const
	{
		return indexAttachment < m_attachments.size() ? m_attachments[indexAttachment].target : GL_INVALID_ENUM;
	}

	GLenum CGLES3FrameBuffer::GetRenderTextureFormat(uint32_t indexAttachment) const
	{
		return indexAttachment < m_attachments.size() ? m_attachments[indexAttachment].format : GL_INVALID_ENUM;
	}

	void CGLES3FrameBuffer::DumpLog(void) const
	{
		if (m_framebuffer) {
			LOGI("\t\tFrameBuffer 0x%x (MSAA 0x%x): width = %d height = %d\n", m_framebuffer, m_framebufferMSAA, m_width, m_height);
			for (uint32_t indexAttachment = 0; indexAttachment < m_attachments.size(); indexAttachment++) {
				LOGI("\t\t\tAttachment %d: texture = 0x%x format = %s\n", indexAttachment, m_attachments[indexAttachment].texture, CGLES3Helper::glEnumToString(m_attachments[indexAttachment].format));
			}
		}
	}

}
