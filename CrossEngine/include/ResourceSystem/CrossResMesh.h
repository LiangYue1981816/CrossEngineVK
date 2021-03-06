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

	class CROSS_EXPORT CResMesh : public CResource
	{
		friend class CResMeshManager;


	protected:
		CResMesh(CResourceManager *pResourceManager);
		virtual ~CResMesh(void);


	public:
		uint32_t GetFormat(void) const;
		uint32_t GetIndexCount(void) const;
		uint32_t GetVertexCount(void) const;
		const glm::aabb& GetAABB(void) const;

		const CGfxIndexBufferPtr& GetIndexBuffer(void) const;
		const CGfxVertexBufferPtr& GetVertexBuffer(void) const;

	public:
		virtual RESOURCE_TYPE GetType(void) const;
		virtual BOOL IsValid(void) const;

	protected:
		virtual BOOL InternalLoad(BOOL bSyncPostLoad);
		virtual BOOL InternalPostLoad(void);
		virtual void InternalLoadFail(void);
		virtual void InternalLoadSuccess(void);

	protected:
		BOOL LoadMesh(CStream *pStream);
		BOOL LoadHeader(CStream *pStream);
		BOOL LoadFormat(CStream *pStream);
		BOOL LoadBounds(CStream *pStream);
		BOOL LoadIndexBuffer(CStream *pStream);
		BOOL LoadVertexBuffer(CStream *pStream);


	protected:
		void *m_pIndexBuffer;
		uint32_t m_indexBufferSize;
		uint32_t m_indexBufferOffset;

		void *m_pVertexBuffer;
		uint32_t m_vertexBufferSize;
		uint32_t m_vertexBufferOffset;

	protected:
		uint32_t m_format;
		glm::aabb m_aabb;

	protected:
		CGfxIndexBufferPtr m_ptrIndexBuffer;
		CGfxVertexBufferPtr m_ptrVertexBuffer;
	};

}
