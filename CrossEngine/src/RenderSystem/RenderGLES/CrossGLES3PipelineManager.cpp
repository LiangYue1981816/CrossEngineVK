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

	CGLES3PipelineManager::CGLES3PipelineManager(CGLES3Device *pDevice)
		: m_pDevice(pDevice)
	{

	}

	CGLES3PipelineManager::~CGLES3PipelineManager(void)
	{

	}

	CGfxPipelineComputePtr CGLES3PipelineManager::AllocPipelineCompute(void)
	{
		CGLES3PipelineCompute *pPipelineCompute = SAFE_NEW CGLES3PipelineCompute(m_pDevice, this);
		{
			mutex_autolock mutex(&m_mutex);
			m_pResources[pPipelineCompute] = pPipelineCompute;
		}
		return CGfxPipelineComputePtr(pPipelineCompute);
	}

	CGfxPipelineGraphicsPtr CGLES3PipelineManager::AllocPipelineGraphics(uint32_t numAttachments)
	{
		CGLES3PipelineGraphics *pPipelineGraphics = SAFE_NEW CGLES3PipelineGraphics(m_pDevice, this, numAttachments);
		{
			mutex_autolock mutex(&m_mutex);
			m_pResources[pPipelineGraphics] = pPipelineGraphics;
		}
		return CGfxPipelineGraphicsPtr(pPipelineGraphics);
	}

}
