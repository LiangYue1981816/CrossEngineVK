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

	static const uint32_t VERTEX_ATTRIBUTE_FLAG_POSITION    = 0x00000001;
	static const uint32_t VERTEX_ATTRIBUTE_FLAG_NORMAL      = 0x00000002;
	static const uint32_t VERTEX_ATTRIBUTE_FLAG_BINORMAL    = 0x00000004;
	static const uint32_t VERTEX_ATTRIBUTE_FLAG_COLOR       = 0x00000008;
	static const uint32_t VERTEX_ATTRIBUTE_FLAG_SKIN_INDEX  = 0x00000010;
	static const uint32_t VERTEX_ATTRIBUTE_FLAG_SKIN_WEIGHT = 0x00000020;
	static const uint32_t VERTEX_ATTRIBUTE_FLAG_TEXCOORD0   = 0x00000040;
	static const uint32_t VERTEX_ATTRIBUTE_FLAG_TEXCOORD1   = 0x00000080;
	static const uint32_t VERTEX_ATTRIBUTE_FLAG_TEXCOORD2   = 0x00000100;
	static const uint32_t VERTEX_ATTRIBUTE_FLAG_TEXCOORD3   = 0x00000200;
	static const uint32_t VERTEX_ATTRIBUTE_FLAG_TEXCOORD4   = 0x00000400;
	static const uint32_t VERTEX_ATTRIBUTE_FLAG_TEXCOORD5   = 0x00000800;
	static const uint32_t VERTEX_ATTRIBUTE_FLAG_TEXCOORD6   = 0x00001000;
	static const uint32_t VERTEX_ATTRIBUTE_FLAG_TEXCOORD7   = 0x00002000;

	typedef enum VertexAttribute {
		VERTEX_ATTRIBUTE_POSITION = 0,
		VERTEX_ATTRIBUTE_NORMAL,
		VERTEX_ATTRIBUTE_BINORMAL,
		VERTEX_ATTRIBUTE_COLOR,
		VERTEX_ATTRIBUTE_SKIN_INDEX,
		VERTEX_ATTRIBUTE_SKIN_WEIGHT,
		VERTEX_ATTRIBUTE_TEXCOORD0,
		VERTEX_ATTRIBUTE_TEXCOORD1,
		VERTEX_ATTRIBUTE_TEXCOORD2,
		VERTEX_ATTRIBUTE_TEXCOORD3,
		VERTEX_ATTRIBUTE_TEXCOORD4,
		VERTEX_ATTRIBUTE_TEXCOORD5,
		VERTEX_ATTRIBUTE_TEXCOORD6,
		VERTEX_ATTRIBUTE_TEXCOORD7,
		VERTEX_ATTRIBUTE_COUNT
	} VertexAttribute;


	typedef enum CommandBufferLevel {
		COMMAND_BUFFER_LEVEL_PRIMARY = 0,
		COMMAND_BUFFER_LEVEL_SECONDARY = 1,
	} CommandBufferLevel;

	typedef enum TextureFormat {

	} TextureFormat;

	typedef enum TextureFilter {
		TEXTURE_FILTER_NEAREST = 0,
		TEXTURE_FILTER_LINEAR = 1,
	} TextureFilter;

	typedef enum SamplerMipmapMode {
		SAMPLER_MIPMAP_MODE_NEAREST = 0,
		SAMPLER_MIPMAP_MODE_LINEAR = 1,
	} SamplerMipmapMode;

	typedef enum SamplerAddressMode {
		SAMPLER_ADDRESS_MODE_REPEAT = 0,
		SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT = 1,
		SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE = 2,
		SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER = 3,
		SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE = 4,
	} SamplerAddressMode;

	typedef enum PrimitiveTopology {
		PRIMITIVE_TOPOLOGY_POINT_LIST = 0,
		PRIMITIVE_TOPOLOGY_LINE_LIST = 1,
		PRIMITIVE_TOPOLOGY_LINE_STRIP = 2,
		PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 3,
		PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = 4,
		PRIMITIVE_TOPOLOGY_TRIANGLE_FAN = 5,
		PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY = 6,
		PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY = 7,
		PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY = 8,
		PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY = 9,
		PRIMITIVE_TOPOLOGY_PATCH_LIST = 10,
	} PrimitiveTopology;

	typedef enum PolygonMode {
		POLYGON_MODE_FILL = 0,
		POLYGON_MODE_LINE = 1,
		POLYGON_MODE_POINT = 2,
	} PolygonMode;

	typedef enum FrontFace {
		FRONT_FACE_COUNTER_CLOCKWISE = 0,
		FRONT_FACE_CLOCKWISE = 1,
	} FrontFace;

	typedef enum LogicOp {
		LOGIC_OP_CLEAR = 0,
		LOGIC_OP_AND = 1,
		LOGIC_OP_AND_REVERSE = 2,
		LOGIC_OP_COPY = 3,
		LOGIC_OP_AND_INVERTED = 4,
		LOGIC_OP_NO_OP = 5,
		LOGIC_OP_XOR = 6,
		LOGIC_OP_OR = 7,
		LOGIC_OP_NOR = 8,
		LOGIC_OP_EQUIVALENT = 9,
		LOGIC_OP_INVERT = 10,
		LOGIC_OP_OR_REVERSE = 11,
		LOGIC_OP_COPY_INVERTED = 12,
		LOGIC_OP_OR_INVERTED = 13,
		LOGIC_OP_NAND = 14,
		LOGIC_OP_SET = 15,
	} LogicOp;

	typedef enum CompareOp {
		COMPARE_OP_NEVER = 0,
		COMPARE_OP_LESS = 1,
		COMPARE_OP_EQUAL = 2,
		COMPARE_OP_LESS_OR_EQUAL = 3,
		COMPARE_OP_GREATER = 4,
		COMPARE_OP_NOT_EQUAL = 5,
		COMPARE_OP_GREATER_OR_EQUAL = 6,
		COMPARE_OP_ALWAYS = 7,
	} CompareOp;

	typedef enum StencilOp {
		STENCIL_OP_KEEP = 0,
		STENCIL_OP_ZERO = 1,
		STENCIL_OP_REPLACE = 2,
		STENCIL_OP_INCREMENT_AND_CLAMP = 3,
		STENCIL_OP_DECREMENT_AND_CLAMP = 4,
		STENCIL_OP_INVERT = 5,
		STENCIL_OP_INCREMENT_AND_WRAP = 6,
		STENCIL_OP_DECREMENT_AND_WRAP = 7,
	} StencilOp;

	typedef enum BlendFactor {
		BLEND_FACTOR_ZERO = 0,
		BLEND_FACTOR_ONE = 1,
		BLEND_FACTOR_SRC_COLOR = 2,
		BLEND_FACTOR_ONE_MINUS_SRC_COLOR = 3,
		BLEND_FACTOR_DST_COLOR = 4,
		BLEND_FACTOR_ONE_MINUS_DST_COLOR = 5,
		BLEND_FACTOR_SRC_ALPHA = 6,
		BLEND_FACTOR_ONE_MINUS_SRC_ALPHA = 7,
		BLEND_FACTOR_DST_ALPHA = 8,
		BLEND_FACTOR_ONE_MINUS_DST_ALPHA = 9,
		BLEND_FACTOR_CONSTANT_COLOR = 10,
		BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR = 11,
		BLEND_FACTOR_CONSTANT_ALPHA = 12,
		BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA = 13,
		BLEND_FACTOR_SRC_ALPHA_SATURATE = 14,
		BLEND_FACTOR_SRC1_COLOR = 15,
		BLEND_FACTOR_ONE_MINUS_SRC1_COLOR = 16,
		BLEND_FACTOR_SRC1_ALPHA = 17,
		BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA = 18,
	} BlendFactor;

	typedef enum BlendOp {
		BLEND_OP_ADD = 0,
		BLEND_OP_SUBTRACT = 1,
		BLEND_OP_REVERSE_SUBTRACT = 2,
		BLEND_OP_MIN = 3,
		BLEND_OP_MAX = 4,
	} BlendOp;

	typedef enum IndexType {
		INDEX_TYPE_UINT16 = 0,
		INDEX_TYPE_UINT32 = 1,
	} IndexType;

	typedef enum ShaderStageFlagBits {
		SHADER_STAGE_VERTEX_BIT = 0x00000001,
		SHADER_STAGE_TESSELLATION_CONTROL_BIT = 0x00000002,
		SHADER_STAGE_TESSELLATION_EVALUATION_BIT = 0x00000004,
		SHADER_STAGE_GEOMETRY_BIT = 0x00000008,
		SHADER_STAGE_FRAGMENT_BIT = 0x00000010,
		SHADER_STAGE_COMPUTE_BIT = 0x00000020,
		SHADER_STAGE_ALL_GRAPHICS = 0x0000001F,
	} ShaderStageFlagBits;

	typedef enum SampleCountFlagBits {
		SAMPLE_COUNT_1_BIT = 0x00000001,
		SAMPLE_COUNT_2_BIT = 0x00000002,
		SAMPLE_COUNT_4_BIT = 0x00000004,
		SAMPLE_COUNT_8_BIT = 0x00000008,
		SAMPLE_COUNT_16_BIT = 0x00000010,
		SAMPLE_COUNT_32_BIT = 0x00000020,
		SAMPLE_COUNT_64_BIT = 0x00000040,
	} SampleCountFlagBits;

	typedef enum CullModeFlagBits {
		CULL_MODE_NONE = 0,
		CULL_MODE_FRONT_BIT = 0x00000001,
		CULL_MODE_BACK_BIT = 0x00000002,
		CULL_MODE_FRONT_AND_BACK = 0x00000003,
	} CullModeFlagBits;
	typedef uint32_t CullModeFlags;

	typedef enum ColorComponentFlagBits {
		COLOR_COMPONENT_R_BIT = 0x00000001,
		COLOR_COMPONENT_G_BIT = 0x00000002,
		COLOR_COMPONENT_B_BIT = 0x00000004,
		COLOR_COMPONENT_A_BIT = 0x00000008,
	} ColorComponentFlagBits;
	typedef uint32_t ColorComponentFlags;

	typedef enum StencilFaceFlagBits {
		STENCIL_FACE_FRONT_BIT = 0x00000001,
		STENCIL_FACE_BACK_BIT = 0x00000002,
		STENCIL_FRONT_AND_BACK = 0x00000003,
	} StencilFaceFlagBits;
	typedef uint32_t StencilFaceFlags;

	typedef struct StencilOpState {
		StencilOp failOp;
		StencilOp passOp;
		StencilOp depthFailOp;
		CompareOp compareOp;
		uint32_t compareMask;
		uint32_t writeMask;
		uint32_t reference;
	} StencilOpState;


	class CROSS_EXPORT CGfxInstance;
	class CROSS_EXPORT CGfxQueue;
	class CROSS_EXPORT CGfxDevice;
	class CROSS_EXPORT CGfxSwapchain;

	template<class T>
	class CROSS_EXPORT CGfxResourcePtr;
	class CROSS_EXPORT CGfxResource;
	class CROSS_EXPORT CGfxResourceManager;

	class CROSS_EXPORT CGfxIndexBuffer;
	class CROSS_EXPORT CGfxVertexBuffer;
	class CROSS_EXPORT CGfxUniformBuffer;
	class CROSS_EXPORT CGfxTexture;
	class CROSS_EXPORT CGfxRenderTexture;
	class CROSS_EXPORT CGfxShader;
	class CROSS_EXPORT CGfxPipelineCompute;
	class CROSS_EXPORT CGfxPipelineGraphics;
	class CROSS_EXPORT CGfxFrameBuffer;
	class CROSS_EXPORT CGfxDescriptorSet;
	class CROSS_EXPORT CGfxCommandBuffer;

	typedef CGfxResourcePtr<CGfxIndexBuffer> CGfxIndexBufferPtr;
	typedef CGfxResourcePtr<CGfxVertexBuffer> CGfxVertexBufferPtr;
	typedef CGfxResourcePtr<CGfxUniformBuffer> CGfxUniformBufferPtr;
	typedef CGfxResourcePtr<CGfxTexture> CGfxTexturePtr;
	typedef CGfxResourcePtr<CGfxRenderTexture> CGfxRenderTexturePtr;
	typedef CGfxResourcePtr<CGfxShader> CGfxShaderPtr;
	typedef CGfxResourcePtr<CGfxPipelineCompute> CGfxPipelineComputePtr;
	typedef CGfxResourcePtr<CGfxPipelineGraphics> CGfxPipelineGraphicsPtr;
	typedef CGfxResourcePtr<CGfxFrameBuffer> CGfxFrameBufferPtr;
	typedef CSharedPtr<CGfxDescriptorSet> CGfxDescriptorSetPtr;
	typedef CSharedPtr<CGfxCommandBuffer> CGfxCommandBufferPtr;

}
