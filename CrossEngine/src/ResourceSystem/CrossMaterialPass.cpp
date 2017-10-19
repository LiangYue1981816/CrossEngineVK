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

	CMaterialPass::CMaterialPass(void)
	{

	}

	CMaterialPass::~CMaterialPass(void)
	{

	}

	const CGfxPipelineGraphicsPtr& CMaterialPass::GetGfxPipeline(void) const
	{
		return m_ptrPipeline->GetGfxPipeline();
	}

	const CGfxDescriptorSetPtr& CMaterialPass::GetDescriptorSet(void) const
	{
		return m_ptrDescriptorSet;
	}

	BOOL CMaterialPass::Load(TiXmlNode *pPassNode, BOOL bSync)
	{
		if (LoadPipeline(pPassNode, bSync) == FALSE) return FALSE;
		if (LoadTextures(pPassNode, bSync) == FALSE) return FALSE;
		if (LoadUniforms(pPassNode, bSync) == FALSE) return FALSE;

		return TRUE;
	}

	BOOL CMaterialPass::PostLoad(void)
	{
		return TRUE;
	}

	BOOL CMaterialPass::LoadPipeline(TiXmlNode *pPassNode, BOOL bSync)
	{
		if (TiXmlNode *pPipelineNode = pPassNode->FirstChild("Pipeline")) {
			const char *szName = pPipelineNode->ToElement()->AttributeString("name");

			DWORD dwName = HashValue(szName);
			m_ptrPipeline = GraphicsManager()->LoadResource(dwName, bSync);
		}

		return TRUE;
	}

	BOOL CMaterialPass::LoadTextures(TiXmlNode *pPassNode, BOOL bSync)
	{
		if (TiXmlNode *pTextureNode = pPassNode->FirstChild("Texture2D")) {
			do {
				const char *szName = pTextureNode->ToElement()->AttributeString("name");
				const char *szTexture = pTextureNode->ToElement()->AttributeString("texture");

				DWORD dwName = HashValue(szName);
				m_textures[dwName] = TextureManager()->LoadResource(dwName, bSync);
			} while (pTextureNode = pTextureNode->IterateChildren("Texture2D", pTextureNode));
		}

		if (TiXmlNode *pTextureNode = pPassNode->FirstChild("TextureCube")) {
			do {
				const char *szName = pTextureNode->ToElement()->AttributeString("name");
				const char *szTexture = pTextureNode->ToElement()->AttributeString("texture");

				DWORD dwName = HashValue(szName);
				m_textures[dwName] = TextureManager()->LoadResource(dwName, bSync);
			} while (pTextureNode = pTextureNode->IterateChildren("TextureCube", pTextureNode));
		}

		return TRUE;
	}

	BOOL CMaterialPass::LoadUniforms(TiXmlNode *pPassNode, BOOL bSync)
	{
		if (TiXmlNode *pFloatNode = pPassNode->FirstChild("Float")) {
			do {
				const char *szName = pFloatNode->ToElement()->AttributeString("name");
				const char *szValue = pFloatNode->ToElement()->AttributeString("value");

				float value;
				scanf(szValue, "%f", &value);

				DWORD dwName = HashValue(szName);
				m_uniformFloats[dwName] = GfxDevice()->NewUniformBuffer();
				m_uniformFloats[dwName]->Create(sizeof(value), &value, TRUE);
			} while (pFloatNode = pFloatNode->IterateChildren("Float", pFloatNode));
		}

		if (TiXmlNode *pVectorNode = pPassNode->FirstChild("Vector")) {
			do {
				const char *szName = pVectorNode->ToElement()->AttributeString("name");
				const char *szValue = pVectorNode->ToElement()->AttributeString("value");

				glm::vec4 value;
				scanf(szValue, "%f %f %f %f", &value.x, &value.y, &value.z, &value.w);

				DWORD dwName = HashValue(szName);
				m_uniformFloats[dwName] = GfxDevice()->NewUniformBuffer();
				m_uniformFloats[dwName]->Create(sizeof(value), &value, TRUE);
			} while (pVectorNode = pVectorNode->IterateChildren("Vector", pVectorNode));
		}

		return TRUE;
	}

}
