// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vk_types.h>
#include <vector>
#include <functional>
#include <deque>

#include <vk_mesh.h>
#include <glm/glm.hpp>

struct MeshPushConstants {
	glm::vec4 data;
	glm::mat4 render_matrix;
};
class PipelineBuilder {
public:

	std::vector<VkPipelineShaderStageCreateInfo> _shaderStages;
	VkPipelineVertexInputStateCreateInfo _vertexInputInfo;
	VkPipelineInputAssemblyStateCreateInfo _inputAssembly;
	VkViewport _viewport;
	VkRect2D _scissor;
	VkPipelineRasterizationStateCreateInfo _rasterizer;
	VkPipelineColorBlendAttachmentState _colorBlendAttachment;
	VkPipelineMultisampleStateCreateInfo _multisampling;
	VkPipelineLayout _pipelineLayout;

	VkPipeline build_pipeline(VkDevice device, VkRenderPass pass);
	VkPipelineDepthStencilStateCreateInfo _depthStencil;
};

struct DeletionQueue
{
	std::deque<std::function<void()>> deletors;

	void push_function(std::function<void()>&& function) {
		deletors.push_back(function);
	}

	void flush() {
		// reverse iterate the deletion queue to execute all the functions
		for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
			(*it)(); //call the function
		}

		deletors.clear();
	}
};

class VulkanEngine {
public:

	bool _isInitialized{ false };
	int _frameNumber{ 0 };
	int _selectedShader{ 0 };// 0 red; 1 colorful

	VkExtent2D _windowExtent{ 1700 , 900 };

	VkInstance _instance;//Vulkan library handle
	VkDebugUtilsMessengerEXT _debug_messenger;//Vulkan debug output handle
	VkPhysicalDevice _chosenGPU;//GPU chosen as the default device
	VkDevice _device; //Vulkan device for commands
	VkSurfaceKHR _surface; //Vulkan window surface

	VkSwapchainKHR _swapchain; // from other articles
	VkFormat _swapchainImageFormat;// image format expected by the windowing system
	std::vector<VkImage> _swapchainImages;//array of images from the swapchain
	std::vector<VkImageView> _swapchainImageViews;//array of image-views from the swapchain

	VkQueue _graphicsQueue;//queue we will submit to
	uint32_t _graphicsQueueFamily;// family of that queue
	VkCommandPool _commandPool;//the command pool for out commands
	VkCommandBuffer _mainCommandBuffer;//the buffer we will record into

	VkRenderPass _renderPass;
	std::vector<VkFramebuffer> _framebuffers;

	VkSemaphore _presentSemaphore, _renderSemaphore;
	VkFence _renderFence;

	VkPipelineLayout _trianglePipelineLayout;
	VkPipeline _trianglePipeline;
	VkPipeline _redTrianglePipeline;

	DeletionQueue _mainDeletionQueue;

	VmaAllocator _allocator; //vma lib allocator

	VkPipeline _meshPipeline;
	Mesh _triangleMesh;

	VkPipelineLayout _meshPipelineLayout;

	Mesh _monkeyMesh;

	VkImageView _depthImageView;
	AllocatedImage _depthImage;

	//the format for the depth image
	VkFormat _depthFormat;

	struct SDL_Window* _window{ nullptr };

	//initializes everything in the engine
	void init();

	//shuts down the engine
	void cleanup();

	//draw loop
	void draw();

	//run main loop
	void run();


private:
	void init_vulkan();
	void init_swapchain();
	void init_commands();

	void init_default_renderpass();
	void init_framebuffers();
	void init_sync_structures();
	void init_pipelines();

	void load_meshes();

	void upload_mesh(Mesh& mesh);

	//loads a shader module from a spir-v file. Returns false if it errors
	bool load_shader_module(const char* filePath, VkShaderModule* outShaderModule);
};



