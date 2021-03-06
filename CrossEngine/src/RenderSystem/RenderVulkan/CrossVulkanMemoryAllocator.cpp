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

	#define NODE_INDEX(size) (((size) / m_alignment) - 1)

	CVulkanMemoryAllocator::CVulkanMemoryAllocator(CVulkanDevice *pDevice, uint32_t memoryTypeIndex, VkDeviceSize memorySize, VkDeviceSize memoryAlignment)
		: m_pDevice(pDevice)
		, m_vkMemory(VK_NULL_HANDLE)

		, m_size(memorySize)
		, m_full(memorySize)
		, m_type(memoryTypeIndex)
		, m_alignment(memoryAlignment)

		, m_root{ NULL }
		, m_nodes(NULL)
		, m_pListHead(NULL)

		, pNext(NULL)
		, pPrev(NULL)
	{
		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.pNext = NULL;
		allocInfo.allocationSize = m_full;
		allocInfo.memoryTypeIndex = m_type;
		vkAllocateMemory(m_pDevice->GetDevice(), &allocInfo, ((CVulkanInstance *)m_pDevice->GetInstance())->GetAllocator()->GetAllocationCallbacks(), &m_vkMemory);

		m_nodes = SAFE_NEW mem_node[m_full / m_alignment];
		m_pListHead = SAFE_NEW CVulkanMemory(this, m_pDevice, m_vkMemory, m_pDevice->GetPhysicalDeviceMemoryProperties().memoryTypes[m_type].propertyFlags, m_full, 0, m_alignment);

		InitNodes(m_full / m_alignment);
		InsertMemory(m_pListHead);
	}

	CVulkanMemoryAllocator::~CVulkanMemoryAllocator(void)
	{
		ASSERT(m_size == m_full);
		ASSERT(m_pListHead->pNext == NULL);
		ASSERT(m_pListHead->pPrev == NULL);
		ASSERT(m_pListHead->m_size == m_full);

		SAFE_DELETE(m_pListHead);
		SAFE_DELETE_ARRAY(m_nodes);

		vkFreeMemory(m_pDevice->GetDevice(), m_vkMemory, ((CVulkanInstance *)m_pDevice->GetInstance())->GetAllocator()->GetAllocationCallbacks());
	}

	CVulkanMemory* CVulkanMemoryAllocator::AllocMemory(VkDeviceSize size)
	{
		//  Device Memory
		//
		//             Memory Handle 
		//             |                Size                 |
		//  --------------------------------------------------------------
		// |           |       |              |              |            |
		// |    ...    |       | RequestSize  |    Memory    |     ...    |
		// |___________|_______|______________|______________|____________|
		//             |       |              |              |
		//             Offset  |              |              Next Memory Handle
		//             |       AlignOffset    |
		//             |   Align RequestSize  |
		//                                    New Memory Handle

		size = ALIGN_BYTE(size, m_alignment);

		if (m_size >= size) {
			if (CVulkanMemory *pMemory = SearchMemory(size)) {
				RemoveMemory(pMemory);

				if (pMemory->m_size >= size + m_alignment) {
					CVulkanMemory *pMemoryNext = SAFE_NEW CVulkanMemory(this, m_pDevice, m_vkMemory, m_pDevice->GetPhysicalDeviceMemoryProperties().memoryTypes[m_type].propertyFlags, pMemory->m_size - size, pMemory->m_offset + size, m_alignment);
					{
						pMemoryNext->pNext = pMemory->pNext;
						pMemoryNext->pPrev = pMemory;
						pMemory->pNext = pMemoryNext;

						if (pMemoryNext->pNext) {
							pMemoryNext->pNext->pPrev = pMemoryNext;
						}

						InsertMemory(pMemoryNext);
					}

					pMemory->m_size = size;
				}

				pMemory->bInUse = TRUE;
				m_size -= pMemory->m_size;

				return pMemory;
			}
		}

		return NULL;
	}

	void CVulkanMemoryAllocator::FreeMemory(CVulkanMemory *pMemory)
	{
		pMemory->bInUse = FALSE;
		m_size += pMemory->m_size;

		if (pMemory->pNext && pMemory->pNext->bInUse == FALSE) {
			RemoveMemory(pMemory->pNext);
			pMemory = MergeMemory(pMemory, pMemory->pNext);
		}

		if (pMemory->pPrev && pMemory->pPrev->bInUse == FALSE) {
			RemoveMemory(pMemory->pPrev);
			pMemory = MergeMemory(pMemory->pPrev, pMemory);
		}

		InsertMemory(pMemory);
	}

	void CVulkanMemoryAllocator::InitNodes(uint32_t numNodes)
	{
		m_root = RB_ROOT;

		for (uint32_t indexNode = 0; indexNode < numNodes; indexNode++) {
			m_nodes[indexNode].size = (indexNode + 1) * m_alignment;
			m_nodes[indexNode].pFreeListHead = NULL;
		}
	}

	void CVulkanMemoryAllocator::InsertMemory(CVulkanMemory *pMemory)
	{
		ASSERT(pMemory->bInUse == FALSE);
		mem_node *pMemoryNode = &m_nodes[NODE_INDEX(pMemory->m_size)];
		rb_node **node = &m_root.rb_node;
		rb_node *parent = NULL;

		while (*node) {
			mem_node *pMemoryNodeCur = container_of(*node, mem_node, node);

			parent = *node;

			if (pMemoryNode->size > pMemoryNodeCur->size) {
				node = &(*node)->rb_right;
				continue;
			}

			if (pMemoryNode->size < pMemoryNodeCur->size) {
				node = &(*node)->rb_left;
				continue;
			}

			ASSERT(pMemoryNode == pMemoryNodeCur);

			pMemory->pFreePrev = NULL;
			pMemory->pFreeNext = pMemoryNode->pFreeListHead;
			pMemoryNode->pFreeListHead->pFreePrev = pMemory;
			pMemoryNode->pFreeListHead = pMemory;

			return;
		}

		pMemory->pFreeNext = NULL;
		pMemory->pFreePrev = NULL;
		pMemoryNode->pFreeListHead = pMemory;

		rb_init_node(&pMemoryNode->node);
		rb_link_node(&pMemoryNode->node, parent, node);
		rb_insert_color(&pMemoryNode->node, &m_root);
	}

	void CVulkanMemoryAllocator::RemoveMemory(CVulkanMemory *pMemory)
	{
		ASSERT(pMemory->bInUse == FALSE);
		mem_node *pMemoryNode = &m_nodes[NODE_INDEX(pMemory->m_size)];

		if (pMemory->pFreeNext) {
			pMemory->pFreeNext->pFreePrev = pMemory->pFreePrev;
		}

		if (pMemory->pFreePrev) {
			pMemory->pFreePrev->pFreeNext = pMemory->pFreeNext;
		}

		if (pMemoryNode->pFreeListHead == pMemory) {
			pMemoryNode->pFreeListHead = pMemory->pFreeNext;
		}

		if (pMemoryNode->pFreeListHead == NULL) {
			rb_erase(&pMemoryNode->node, &m_root);
		}
	}

	CVulkanMemory* CVulkanMemoryAllocator::MergeMemory(CVulkanMemory *pMemory, CVulkanMemory *pMemoryNext)
	{
		ASSERT(pMemory->m_offset + pMemory->m_size == pMemoryNext->m_offset);

		pMemory->m_size = pMemory->m_size + pMemoryNext->m_size;
		pMemory->pNext = pMemoryNext->pNext;

		if (pMemoryNext->pNext) {
			pMemoryNext->pNext->pPrev = pMemory;
		}

		SAFE_DELETE(pMemoryNext);

		return pMemory;
	}

	CVulkanMemory* CVulkanMemoryAllocator::SearchMemory(VkDeviceSize size) const
	{
		mem_node *pMemoryNode = NULL;
		rb_node *node = m_root.rb_node;

		while (node) {
			mem_node *pMemoryNodeCur = container_of(node, mem_node, node);

			if (size > pMemoryNodeCur->size) {
				node = node->rb_right;
				continue;
			}

			pMemoryNode = pMemoryNodeCur;

			if (size < pMemoryNodeCur->size) {
				node = node->rb_left;
				continue;
			}

			ASSERT(pMemoryNode->pFreeListHead);
			ASSERT(pMemoryNode->pFreeListHead->bInUse == FALSE);
			ASSERT(pMemoryNode->pFreeListHead->m_size / m_alignment * m_alignment >= size);

			break;
		}

		return pMemoryNode ? pMemoryNode->pFreeListHead : NULL;
	}

	BOOL CVulkanMemoryAllocator::IsEmpty(void) const
	{
		return m_size == m_full ? TRUE : FALSE;
	}

	uint32_t CVulkanMemoryAllocator::GetMemoryAlignment(void) const
	{
		return m_alignment;
	}

	uint32_t CVulkanMemoryAllocator::GetMemoryTypeIndex(void) const
	{
		return m_type;
	}

	VkMemoryPropertyFlags CVulkanMemoryAllocator::GetMemoryPropertyFlags(void) const
	{
		return m_pDevice->GetPhysicalDeviceMemoryProperties().memoryTypes[m_type].propertyFlags;
	}

	VkDeviceSize CVulkanMemoryAllocator::GetFullSize(void) const
	{
		return m_full;
	}

	VkDeviceSize CVulkanMemoryAllocator::GetAllocatedSize(void) const
	{
		return m_size;
	}

	void CVulkanMemoryAllocator::DumpLog(void) const
	{
		LOGI("\t\t\tAllocator: host = %s coherent = %s cached = %s size = %d full = %d\n", 
			GetMemoryPropertyFlags() & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT ? "true" : "false",
			GetMemoryPropertyFlags() & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT ? "true" : "false",
			GetMemoryPropertyFlags() & VK_MEMORY_PROPERTY_HOST_CACHED_BIT ? "true" : "false",
			GetAllocatedSize(), 
			GetFullSize());
	}

}
