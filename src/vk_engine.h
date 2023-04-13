﻿// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vk_types.h>
#include <vector>

class VulkanEngine {
public:

	bool _isInitialized{ false };
	int _frameNumber{ 0 };

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
};