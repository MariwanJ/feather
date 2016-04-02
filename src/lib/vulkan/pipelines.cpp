/***********************************************************************
 *
 * Filename: pipelines.cpp
 *
 * Description: holds all the pools for shaders.
 *
 * Copyright (C) 2016 Richard Layman, rlayman2000@yahoo.com 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

#include "pipelines.hpp"
//#include "mesh.hpp"
//#include "pointlight.hpp"

#include "swapchain.hpp"

using namespace feather::vulkan;

Pipeline::Pipeline(
        std::string shadeVertShader,
        std::string shadeFragShader,
        std::string wireVertShader,
        std::string wireFragShader,
        std::string wireGeomShader,
        std::string pointVertShader,
        std::string pointFragShader,
        std::string pointGeomShader
        ) : 
    m_shadeVertShader(shadeVertShader),
    m_shadeFragShader(shadeFragShader),
    m_wireVertShader(wireVertShader),
    m_wireFragShader(wireFragShader),
    m_wireGeomShader(wireGeomShader),
    m_pointVertShader(pointVertShader),
    m_pointFragShader(pointFragShader),
    m_pointGeomShader(pointGeomShader)
{

}

Pipeline::~Pipeline()
{

}

void Pipeline::cleanup(VkDevice device)
{
    vkDestroyPipeline(device, m_shade, nullptr);
    vkDestroyPipeline(device, m_wire, nullptr);
    vkDestroyPipeline(device, m_point, nullptr);
}

void Pipeline::prepare(VkDevice device, VkPipelineCache cache, VkPipelineLayout layout, VkRenderPass renderPass, VkPipelineVertexInputStateCreateInfo* vi)
{
    // Create our rendering pipeline used in this example
    // Vulkan uses the concept of rendering pipelines to encapsulate
    // fixed states
    // This replaces OpenGL's huge (and cumbersome) state machine
    // A pipeline is then stored and hashed on the GPU making
    // pipeline changes much faster than having to set dozens of 
    // states
    // In a real world application you'd have dozens of pipelines
    // for every shader set used in a scene
    // Note that there are a few states that are not stored with
    // the pipeline. These are called dynamic states and the 
    // pipeline only stores that they are used with this pipeline,
    // but not their states



    // Solid Shading Pipeline
    VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};

    pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    // The layout used for this pipeline
    pipelineCreateInfo.layout = layout;
    // Renderpass this pipeline is attached to
    pipelineCreateInfo.renderPass = renderPass;

    // Edge Shading Pipeline
    VkGraphicsPipelineCreateInfo pipelineEdgeCreateInfo = {};

    pipelineEdgeCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    // The layout used for this pipeline
    pipelineEdgeCreateInfo.layout = layout;
    // Renderpass this pipeline is attached to
    pipelineEdgeCreateInfo.renderPass = renderPass;

    VkResult err;

    // Vertex input state for solid shading 
    // Describes the topoloy used with this pipeline
    VkPipelineInputAssemblyStateCreateInfo inputSolidAssemblyState = {};
    inputSolidAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    // This pipeline renders vertex data as triangle lists
    inputSolidAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    // Vertex input state for edge shading 
    // Describes the topoloy used with this pipeline
    VkPipelineInputAssemblyStateCreateInfo inputEdgeAssemblyState = {};
    inputEdgeAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    // This pipeline renders vertex data as line lists
    inputEdgeAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;


    // Rasterization state
    VkPipelineRasterizationStateCreateInfo rasterizationState = {};
    rasterizationState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    // Solid polygon mode
    rasterizationState.polygonMode = VK_POLYGON_MODE_FILL;
    // No culling
    rasterizationState.cullMode = VK_CULL_MODE_NONE;
    rasterizationState.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizationState.depthClampEnable = VK_FALSE;
    rasterizationState.rasterizerDiscardEnable = VK_FALSE;
    rasterizationState.depthBiasEnable = VK_FALSE;
    rasterizationState.lineWidth = 4.0; // this does not work yet, have to enable wide lines?

    // Color blend state
    // Describes blend modes and color masks
    VkPipelineColorBlendStateCreateInfo colorBlendState = {};
    colorBlendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    // One blend attachment state
    // Blending is not used in this example
    VkPipelineColorBlendAttachmentState blendAttachmentState[1] = {};
    blendAttachmentState[0].colorWriteMask = 0xf;
    blendAttachmentState[0].blendEnable = VK_FALSE;
    colorBlendState.attachmentCount = 1;
    colorBlendState.pAttachments = blendAttachmentState;

    // Viewport state
    VkPipelineViewportStateCreateInfo viewportState = {};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    // One viewport
    viewportState.viewportCount = 1;
    // One scissor rectangle
    viewportState.scissorCount = 1;

    // Enable dynamic states
    // Describes the dynamic states to be used with this pipeline
    // Dynamic states can be set even after the pipeline has been created
    // So there is no need to create new pipelines just for changing
    // a viewport's dimensions or a scissor box
    VkPipelineDynamicStateCreateInfo dynamicState = {};
    // The dynamic state properties themselves are stored in the command buffer
    std::vector<VkDynamicState> dynamicStateEnables;
    dynamicStateEnables.push_back(VK_DYNAMIC_STATE_VIEWPORT);
    dynamicStateEnables.push_back(VK_DYNAMIC_STATE_SCISSOR);
    dynamicStateEnables.push_back(VK_DYNAMIC_STATE_LINE_WIDTH);
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.pDynamicStates = dynamicStateEnables.data();
    dynamicState.dynamicStateCount = dynamicStateEnables.size();

    // Depth and stencil state
    // Describes depth and stenctil test and compare ops
    VkPipelineDepthStencilStateCreateInfo depthStencilState = {};
    // Basic depth compare setup with depth writes and depth test enabled
    // No stencil used 
    depthStencilState.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencilState.depthTestEnable = VK_TRUE;
    depthStencilState.depthWriteEnable = VK_TRUE;
    depthStencilState.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    depthStencilState.depthBoundsTestEnable = VK_FALSE;
    depthStencilState.back.failOp = VK_STENCIL_OP_KEEP;
    depthStencilState.back.passOp = VK_STENCIL_OP_KEEP;
    depthStencilState.back.compareOp = VK_COMPARE_OP_ALWAYS;
    depthStencilState.stencilTestEnable = VK_FALSE;
    depthStencilState.front = depthStencilState.back;

    // Multi sampling state
    VkPipelineMultisampleStateCreateInfo multisampleState = {};
    multisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleState.pSampleMask = NULL;
    // No multi sampling used in this example
    //multisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampleState.rasterizationSamples = VK_SAMPLE_COUNT_4_BIT;


    // Load shaders

    VkPipelineShaderStageCreateInfo shaderStages[3] = { {},{} };

    // Wireframe shader
    shaderStages[0] = loadShader(device, m_wireVertShader.c_str(), VK_SHADER_STAGE_VERTEX_BIT);
    shaderStages[1] = loadShader(device, m_wireFragShader.c_str(), VK_SHADER_STAGE_FRAGMENT_BIT);
    shaderStages[2] = loadShader(device, m_wireGeomShader.c_str(), VK_SHADER_STAGE_GEOMETRY_BIT);

    // Assign states to solid shading
    // Three shader stages
    pipelineEdgeCreateInfo.stageCount = 3;
    // Assign pipeline state create information
    pipelineEdgeCreateInfo.pVertexInputState = vi;
    pipelineEdgeCreateInfo.pInputAssemblyState = &inputEdgeAssemblyState;
    pipelineEdgeCreateInfo.pRasterizationState = &rasterizationState;
    pipelineEdgeCreateInfo.pColorBlendState = &colorBlendState;
    pipelineEdgeCreateInfo.pMultisampleState = &multisampleState;
    pipelineEdgeCreateInfo.pViewportState = &viewportState;
    pipelineEdgeCreateInfo.pDepthStencilState = &depthStencilState;
    pipelineEdgeCreateInfo.pStages = shaderStages;
    pipelineEdgeCreateInfo.renderPass = renderPass;
    pipelineEdgeCreateInfo.pDynamicState = &dynamicState;

    // wireframe rendering pipeline 
    //err = vkCreateGraphicsPipelines(device, cache, 1, &pipelineEdgeCreateInfo, nullptr, &m_meshPipelines.wire);
    //assert(!err);
    // wireframe rendering pipeline 
    err = vkCreateGraphicsPipelines(device, cache, 1, &pipelineEdgeCreateInfo, nullptr, &m_wire);
    assert(!err);


    // Point shader
    shaderStages[0] = loadShader(device, m_pointVertShader.c_str(), VK_SHADER_STAGE_VERTEX_BIT);
    shaderStages[1] = loadShader(device, m_pointFragShader.c_str(), VK_SHADER_STAGE_FRAGMENT_BIT);
    shaderStages[2] = loadShader(device, m_pointGeomShader.c_str(), VK_SHADER_STAGE_GEOMETRY_BIT);

    // Point rendering pipeline 
    err = vkCreateGraphicsPipelines(device, cache, 1, &pipelineEdgeCreateInfo, nullptr, &m_point);
    assert(!err);

    // Base solid shader
    shaderStages[0] = loadShader(device, m_shadeVertShader.c_str(), VK_SHADER_STAGE_VERTEX_BIT);
    shaderStages[1] = loadShader(device, m_shadeFragShader.c_str(), VK_SHADER_STAGE_FRAGMENT_BIT);

    // Assign states to solid shading
    // Three shader stages
    pipelineCreateInfo.stageCount = 2;
    // Assign pipeline state create information
    pipelineCreateInfo.pVertexInputState = vi;
    pipelineCreateInfo.pInputAssemblyState = &inputSolidAssemblyState;
    pipelineCreateInfo.pRasterizationState = &rasterizationState;
    pipelineCreateInfo.pColorBlendState = &colorBlendState;
    pipelineCreateInfo.pMultisampleState = &multisampleState;
    pipelineCreateInfo.pViewportState = &viewportState;
    pipelineCreateInfo.pDepthStencilState = &depthStencilState;
    pipelineCreateInfo.pStages = shaderStages;
    pipelineCreateInfo.renderPass = renderPass;
    pipelineCreateInfo.pDynamicState = &dynamicState;


    // solid rendering pipeline 
    err = vkCreateGraphicsPipelines(device, cache, 1, &pipelineCreateInfo, nullptr, &m_shade);
    assert(!err);
}

VkPipelineShaderStageCreateInfo Pipeline::loadShader(VkDevice device, const char * fileName, VkShaderStageFlagBits stage)
{
    VkPipelineShaderStageCreateInfo shaderStage = {};
    shaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStage.stage = stage;
    shaderStage.module = feather::vulkan::tools::loadShader(fileName, device, stage);
    shaderStage.pName = "main"; // todo : make param
    assert(shaderStage.module != NULL);
    m_shaderModules.push_back(shaderStage.module);
    return shaderStage;
}


// PIPELINES


Pipelines::Pipelines()
{

}

Pipelines::~Pipelines()
{
}

void Pipelines::cleanup(VkDevice device)
{
    // Clean up used Vulkan resources 
    // Note : Inherited destructor cleans up resources stored in base class
    /*
    vkDestroyPipeline(device, m_meshPipelines.solid, nullptr);
    vkDestroyPipeline(device, m_meshPipelines.wire, nullptr);
    vkDestroyPipeline(device, m_meshPipelines.point, nullptr);

    vkDestroyPipeline(device, m_lightPipelines.solid, nullptr);
    vkDestroyPipeline(device, m_lightPipelines.wire, nullptr);
    vkDestroyPipeline(device, m_lightPipelines.point, nullptr);
    */
    m_meshPipeline.cleanup(device);
    m_lightPipeline.cleanup(device);
    vkDestroyPipelineLayout(device, m_pipelineLayout, nullptr);
}

void Pipelines::bind(VkDevice device, VkCommandBuffer buffer, Node* node, VkDeviceSize offsets[1])
{
    switch(node->type())
    {
        case Node::Null:
            bindMesh(device, buffer, node, offsets);
            break;
        case Node::Camera:
            bindMesh(device, buffer, node, offsets);
            break;
        case Node::Light:
            bindLight(device, buffer, node, offsets);
            break;
        case Node::Mesh:
            bindMesh(device, buffer, node, offsets);
            break;
        default:
            bindMesh(device, buffer, node, offsets);
    }
}

void Pipelines::prepare(VkDevice device, VkRenderPass renderPass, VkPipelineVertexInputStateCreateInfo* vi)
{
    m_meshPipeline.prepare(
            device,
            m_pipelineCache,
            m_pipelineLayout,
            renderPass,
            vi);

    m_lightPipeline.prepare(
            device,
            m_pipelineCache,
            m_pipelineLayout,
            renderPass,
            vi);
}
 
void Pipelines::bindMesh(VkDevice device, VkCommandBuffer buffer, Node* node, VkDeviceSize offsets[1])
{
    vkCmdBindVertexBuffers(buffer, VERTEX_BUFFER_BIND_ID, 1, &static_cast<Mesh*>(node)->buffer()->vertices.buf, offsets);

    // Bind triangle indices
    vkCmdBindIndexBuffer(buffer, static_cast<Mesh*>(node)->buffer()->indices.buf, 0, VK_INDEX_TYPE_UINT32);

    // Solid Shading
    // Bind the rendering pipeline (including the shaders)
    vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_meshPipeline.shade());

    // Draw indexed triangle
    vkCmdDrawIndexed(buffer, static_cast<Mesh*>(node)->buffer()->indexCount, 1, 0, 0, 1);
    // change over to edge index

    // Bind indices
    vkCmdBindIndexBuffer(buffer, static_cast<Mesh*>(node)->buffer()->edges.buf, 0, VK_INDEX_TYPE_UINT32);

    // EDGES

    // set line width
    vkCmdSetLineWidth(buffer, 2.0);

    // Shading
    vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_meshPipeline.wire());

    // Draw indexed 
    vkCmdDrawIndexed(buffer, static_cast<Mesh*>(node)->buffer()->edgeCount, 1, 0, 0, 1);

    // POINTS

    // Shading 
    vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_meshPipeline.point());

    // Draw indexed 
    vkCmdDrawIndexed(buffer, static_cast<Mesh*>(node)->buffer()->edgeCount, 1, 0, 0, 1);
}

void Pipelines::bindLight(VkDevice device, VkCommandBuffer buffer, Node* node, VkDeviceSize offsets[1])
{
    vkCmdBindVertexBuffers(buffer, VERTEX_BUFFER_BIND_ID, 1, &static_cast<PointLight*>(node)->buffer()->vertices.buf, offsets);

    // Uncomment this to shade the light mesh
    /*
    // Bind triangle indices
    vkCmdBindIndexBuffer(buffer, static_cast<PointLight*>(node)->buffer()->indices.buf, 0, VK_INDEX_TYPE_UINT32);

    // Solid Shading
    // Bind the rendering pipeline (including the shaders)
    vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_lightPipeline.shade());

    // Draw indexed triangle
    vkCmdDrawIndexed(buffer, static_cast<PointLight*>(node)->buffer()->indexCount, 1, 0, 0, 1);
    // change over to edge index

    // Bind indices
    vkCmdBindIndexBuffer(buffer, static_cast<PointLight*>(node)->buffer()->edges.buf, 0, VK_INDEX_TYPE_UINT32);
    */

    // EDGES

    // set line width
    vkCmdSetLineWidth(buffer, 2.0);

    // Shading
    vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_lightPipeline.wire());

    // Draw indexed 
    vkCmdDrawIndexed(buffer, static_cast<PointLight*>(node)->buffer()->edgeCount, 1, 0, 0, 1);

}

void Pipelines::createCache(VkDevice device)
{
    VkPipelineCacheCreateInfo pipelineCacheCreateInfo = {};
    pipelineCacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    VkResult err = vkCreatePipelineCache(device, &pipelineCacheCreateInfo, nullptr, &m_pipelineCache);
    assert(!err);
}

void Pipelines::createLayout(VkDevice device, VkPipelineLayoutCreateInfo info)
{
    VkResult err;
    err = vkCreatePipelineLayout(device, &info, nullptr, &m_pipelineLayout);
    assert(!err);
}


