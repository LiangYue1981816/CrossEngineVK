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

	class CROSS_EXPORT CGLES3CommandBufferManager
	{
		friend class CGLES3Device;
		friend class CGLES3CommandBuffer;


	protected:
		CGLES3CommandBufferManager(CGLES3Device *pDevice);
		virtual ~CGLES3CommandBufferManager(void);


	protected:
		int Create(void);
		void Destroy(void);

	protected:
		CGfxCommandBufferPtr AllocCommandBuffer(void);
		void FreeCommandBuffer(CGLES3CommandBuffer *pCommandBuffer);


	protected:
		pthread_mutex_t m_mutex;
		eastl::map<CGLES3CommandBuffer*, CGLES3CommandBuffer*> m_pCommandBuffers;

	protected:
		CGLES3Device *m_pDevice;
	};

}
