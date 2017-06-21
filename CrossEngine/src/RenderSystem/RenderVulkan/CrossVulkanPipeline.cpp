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

	CVulkanDescriptorSetLayout::CVulkanDescriptorSetLayout(CVulkanDevice *pDevice, uint32_t set)
		: m_pDevice(pDevice)

		, m_set(set)
		, m_vkDescriptorSetLayout(VK_NULL_HANDLE)
		, m_numTypesUsedCount{ 0 }
	{

	}

	CVulkanDescriptorSetLayout::~CVulkanDescriptorSetLayout(void)
	{

	}

	BOOL CVulkanDescriptorSetLayout::Create(void)
	{
		try {
			std::vector<VkDescriptorSetLayoutBinding> bindings;
			CALL_BOOL_FUNCTION_THROW(CreateBindings(bindings));

			VkDescriptorSetLayoutCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			createInfo.pNext = NULL;
			createInfo.flags = 0;
			createInfo.bindingCount = bindings.size();
			createInfo.pBindings = bindings.data();
			CALL_VK_FUNCTION_THROW(vkCreateDescriptorSetLayout(m_pDevice->GetDevice(), &createInfo, m_pDevice->GetVulkan()->GetAllocator()->GetAllocationCallbacks(), &m_vkDescriptorSetLayout));

			return TRUE;
		}
		catch (VkResult err) {
			CVulkanInstance::SetLastError(err);
			Destroy();

			return FALSE;
		}
	}

	BOOL CVulkanDescriptorSetLayout::CreateBindings(std::vector<VkDescriptorSetLayoutBinding> &bindings)
	{
		bindings.clear();

		for (const auto &itBinding : m_bindings) {
			bindings.push_back(itBinding.second);
		}

		return TRUE;
	}

	void CVulkanDescriptorSetLayout::Destroy(void)
	{
		if (m_vkDescriptorSetLayout) {
			vkDestroyDescriptorSetLayout(m_pDevice->GetDevice(), m_vkDescriptorSetLayout, m_pDevice->GetVulkan()->GetAllocator()->GetAllocationCallbacks());
		}

		m_bindings.clear();
		m_vkDescriptorSetLayout = VK_NULL_HANDLE;
	}

	BOOL CVulkanDescriptorSetLayout::SetBinding(uint32_t binding, VkDescriptorType type, VkShaderStageFlags flags)
	{
		m_numTypesUsedCount[type]++;

		m_bindings[binding].binding = binding;
		m_bindings[binding].descriptorType = type;
		m_bindings[binding].descriptorCount = 1;
		m_bindings[binding].stageFlags = flags;
		m_bindings[binding].pImmutableSamplers = NULL;

		return TRUE;
	}

	VkDescriptorSetLayout CVulkanDescriptorSetLayout::GetLayout(void) const
	{
		return m_vkDescriptorSetLayout;
	}

	uint32_t CVulkanDescriptorSetLayout::GetSet(void) const
	{
		return m_set;
	}

	const uint32_t* CVulkanDescriptorSetLayout::GetTypesUsedCount(void) const
	{
		return m_numTypesUsedCount;
	}


	CVulkanPipeline::CVulkanPipeline(CVulkanDevice *pDevice)
		: m_pDevice(pDevice)

		, m_vkPipeline(VK_NULL_HANDLE)
		, m_vkPipelineLayout(VK_NULL_HANDLE)
	{
		m_shaderStages[VK_SHADER_STAGE_VERTEX_BIT] = {};
		m_shaderStages[VK_SHADER_STAGE_VERTEX_BIT].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		m_shaderStages[VK_SHADER_STAGE_VERTEX_BIT].pNext = NULL;
		m_shaderStages[VK_SHADER_STAGE_VERTEX_BIT].flags = 0;
		m_shaderStages[VK_SHADER_STAGE_VERTEX_BIT].stage = VK_SHADER_STAGE_VERTEX_BIT;

		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT] = {};
		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT].pNext = NULL;
		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT].flags = 0;
		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT].stage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;

		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT] = {};
		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT].pNext = NULL;
		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT].flags = 0;
		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT].stage = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;

		m_shaderStages[VK_SHADER_STAGE_GEOMETRY_BIT] = {};
		m_shaderStages[VK_SHADER_STAGE_GEOMETRY_BIT].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		m_shaderStages[VK_SHADER_STAGE_GEOMETRY_BIT].pNext = NULL;
		m_shaderStages[VK_SHADER_STAGE_GEOMETRY_BIT].flags = 0;
		m_shaderStages[VK_SHADER_STAGE_GEOMETRY_BIT].stage = VK_SHADER_STAGE_GEOMETRY_BIT;

		m_shaderStages[VK_SHADER_STAGE_FRAGMENT_BIT] = {};
		m_shaderStages[VK_SHADER_STAGE_FRAGMENT_BIT].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		m_shaderStages[VK_SHADER_STAGE_FRAGMENT_BIT].pNext = NULL;
		m_shaderStages[VK_SHADER_STAGE_FRAGMENT_BIT].flags = 0;
		m_shaderStages[VK_SHADER_STAGE_FRAGMENT_BIT].stage = VK_SHADER_STAGE_FRAGMENT_BIT;

		m_shaderStages[VK_SHADER_STAGE_COMPUTE_BIT] = {};
		m_shaderStages[VK_SHADER_STAGE_COMPUTE_BIT].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		m_shaderStages[VK_SHADER_STAGE_COMPUTE_BIT].pNext = NULL;
		m_shaderStages[VK_SHADER_STAGE_COMPUTE_BIT].flags = 0;
		m_shaderStages[VK_SHADER_STAGE_COMPUTE_BIT].stage = VK_SHADER_STAGE_COMPUTE_BIT;
	}

	CVulkanPipeline::~CVulkanPipeline(void)
	{

	}

	BOOL CVulkanPipeline::CreateDescriptorSetLayouts(std::vector<VkDescriptorSetLayout> &layouts)
	{
		layouts.clear();

		for (const auto &itShader : m_ptrShaders) {
			const CGfxShaderPtr &ptrShader = itShader.second;
			const spirv::module_type &module = ((CVulkanShader *)((CGfxShader *)ptrShader))->GetMoudleType();

			for (const auto &variable : module.variables) {
				if (variable.second.storage_class != SpvStorageClassUniform &&
					variable.second.storage_class != SpvStorageClassUniformConstant) {
					continue;
				}

				uint32_t set = variable.second.descriptor_set;
				uint32_t binding = variable.second.binding;
				VkShaderStageFlags shaderStageFlags = itShader.first;

				if (m_pDescriptorSetLayouts[set] == NULL) {
					m_pDescriptorSetLayouts[set] = SAFE_NEW CVulkanDescriptorSetLayout(m_pDevice, set);
				}

				if (variable.second.storage_class == SpvStorageClassUniform) {
					m_pDescriptorSetLayouts[set]->SetBinding(binding, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, shaderStageFlags);
				}

				if (variable.second.storage_class == SpvStorageClassUniformConstant) {
					m_pDescriptorSetLayouts[set]->SetBinding(binding, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, shaderStageFlags);
				}
			}
		}

		for (const auto &itDescriptorSetLayout : m_pDescriptorSetLayouts) {
			if (CVulkanDescriptorSetLayout* pDescriptorSetLayout = itDescriptorSetLayout.second) {
				pDescriptorSetLayout->Create();
				layouts.push_back(pDescriptorSetLayout->GetLayout());
			}
		}

		return TRUE;
	}

	BOOL CVulkanPipeline::CreateShaderStages(std::vector<VkPipelineShaderStageCreateInfo> &shaderStages)
	{
		shaderStages.clear();

		for (const auto &itShaderStage : m_shaderStages) {
			if (itShaderStage.second.module) {
				shaderStages.push_back(itShaderStage.second);
			}
		}

		return TRUE;
	}

	void CVulkanPipeline::DestroyDescriptorSetLayouts(void)
	{
		for (const auto &itDescriptorSetLayout : m_pDescriptorSetLayouts) {
			if (CVulkanDescriptorSetLayout* pDescriptorSetLayout = itDescriptorSetLayout.second) {
				pDescriptorSetLayout->Destroy();
				SAFE_DELETE(pDescriptorSetLayout);
			}
		}

		m_pDescriptorSetLayouts.clear();
	}

	void CVulkanPipeline::DestroyShaderStages(void)
	{
		m_shaderStages[VK_SHADER_STAGE_VERTEX_BIT].module = VK_NULL_HANDLE;
		m_shaderStages[VK_SHADER_STAGE_VERTEX_BIT].pName = NULL;

		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT].module = VK_NULL_HANDLE;
		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT].pName = NULL;

		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT].module = VK_NULL_HANDLE;
		m_shaderStages[VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT].pName = NULL;

		m_shaderStages[VK_SHADER_STAGE_GEOMETRY_BIT].module = VK_NULL_HANDLE;
		m_shaderStages[VK_SHADER_STAGE_GEOMETRY_BIT].pName = NULL;

		m_shaderStages[VK_SHADER_STAGE_FRAGMENT_BIT].module = VK_NULL_HANDLE;
		m_shaderStages[VK_SHADER_STAGE_FRAGMENT_BIT].pName = NULL;

		m_shaderStages[VK_SHADER_STAGE_COMPUTE_BIT].module = VK_NULL_HANDLE;
		m_shaderStages[VK_SHADER_STAGE_COMPUTE_BIT].pName = NULL;

		for (auto &itShader : m_ptrShaders) {
			CGfxShaderPtr &ptrShader = itShader.second;
			ptrShader.Release();
		}

		m_ptrShaders.clear();
	}

	VkPipelineLayout CVulkanPipeline::GetPipelineLayout(void) const
	{
		return m_vkPipelineLayout;
	}

	const CVulkanDescriptorSetLayout* CVulkanPipeline::GetDescriptorSetLayout(uint32_t set) const
	{
		const auto &itDescriptorSetLayout = m_pDescriptorSetLayouts.find(set);
		return itDescriptorSetLayout != m_pDescriptorSetLayouts.end() ? itDescriptorSetLayout->second : NULL;
	}

}