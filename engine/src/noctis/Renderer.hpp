#pragma once

#include "noctis.hpp"
#include <array>
#include <glm/glm.hpp>
#include <optional>
#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Noctis
{
    struct Vertex
    {
        glm::vec3 pos{};
        glm::vec3 color{};
        glm::vec2 texCoord{};

        static VkVertexInputBindingDescription getBindingDescription()
        {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
        {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

            return attributeDescriptions;
        }

        bool operator==(const Vertex &other) const
        {
            return pos == other.pos && color == other.color && texCoord == other.texCoord;
        }
    };

    struct QueueFamilyIndices
    {
        std::optional<u32> graphicsFamily;
        std::optional<u32> presentFamily;

        bool isComplete() const { return graphicsFamily.has_value() && presentFamily.has_value(); }
    };

    struct SwapchainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct UniformBufferObject
    {
        alignas(16) glm::mat4 model;
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
    };

    class Renderer
    {
      private:
        VkInstance mInstance;
        VkPhysicalDevice mPhysicalDevice;
        VkDevice mDevice;
        VkDebugUtilsMessengerEXT mDebugMessenger;
        VkSurfaceKHR mSurface;
        VkQueue mPresentQueue;
        VkQueue mGraphicsQueue;
        VkSwapchainKHR mSwapchain;
        std::vector<VkImage> mSwapchainImages;
        VkFormat mSwapchainImageFormat;
        VkExtent2D mSwapchainExtent;
        std::vector<VkImageView> mSwapchainImageViews;
        VkRenderPass mRenderPass;
        VkDescriptorSetLayout mDescriptorSetLayout;
        VkPipelineLayout mPipelineLayout;
        VkPipeline mGraphicsPipeline;
        std::vector<VkFramebuffer> mSwapchainFramebuffers;
        VkCommandPool mCommandPool;
        std::vector<VkCommandBuffer> mCommandBuffers;
        std::vector<VkSemaphore> mImageAvailableSemaphores;
        std::vector<VkSemaphore> mRenderFinishedSemaphores;
        std::vector<VkFence> mInFlightFences;
        u32 mCurrentFrame = 0;
        VkBuffer mVertexBuffer;
        VkDeviceMemory mVertexBufferMemory;
        VkBuffer mIndexBuffer;
        VkDeviceMemory mIndexBufferMemory;
        std::vector<VkBuffer> mUniformBuffers;
        std::vector<VkDeviceMemory> mUniformBuffersMemory;
        std::vector<void *> mUniformBuffersMapped;
        VkDescriptorPool mDescriptorPool;
        std::vector<VkDescriptorSet> mDescriptorSets;
        VkImage mTextureImage;
        VkImageView mTextureImageView;
        VkDeviceMemory mTextureImageMemory;
        VkSampler mTextureSampler;
        VkImage mDepthImage;
        VkDeviceMemory mDepthImageMemory;
        VkImageView mDepthImageView;

        void createViewportImage();
        void createViewportImageViews();

#ifdef NDEBUG
        const bool enableValidationLayers = false;
#else
        const bool enableValidationLayers = true;
#endif

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                            VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                            void *pUserData);

        SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice device);

        const std::vector<const char *> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        };

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        const std::vector<const char *> validationLayers = {
            "VK_LAYER_KHRONOS_validation",
        };

        void createInstance();

        void setupDebugMessenger();

        void pickPhysicalDevice();

        void createLogicalDevice();

        void createSwapchain();

        void createImageViews();

        void createRenderPass();

        void createDescriptorSetLayout();

        void createGraphicsPipeline();

        void createFramebuffers();

        void createCommandPool();

        void createDepthResources();

        void createTextureImage();

        void createTextureImageView();

        void createTextureSampler();

        void createVertexBuffer();

        void createIndexBuffer();

        void createUniformBuffers();

        void createDescriptorPool();

        void createDescriptorSets();

        void createCommandBuffers();

        void createSyncObjects();

        void initImgui();

        VkShaderModule createShaderModule(const std::vector<char> &code) const;

        void createBuffer(VkDeviceSize size,
                          VkBufferUsageFlags usage,
                          VkMemoryPropertyFlags properties,
                          VkBuffer &buffer,
                          VkDeviceMemory &bufferMemory);

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

        VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates,
                                     VkImageTiling tiling,
                                     VkFormatFeatureFlags features);

        VkFormat findDepthFormat();

        bool hasStencilComponent(VkFormat format);

        void updateUniformBuffer(u32 currentImage);

        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        bool isDeviceSuitable(VkPhysicalDevice device);

        void recordCommandBuffer(VkCommandBuffer commandBuffer, u32 imageIndex);

        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

        void cleanupSwapchain();

        void recreateSwapchain();

        VkResult createDebugUtilsMessengerEXT(VkInstance instance,
                                              const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                              const VkAllocationCallbacks *pAllocator,
                                              VkDebugUtilsMessengerEXT *pDebugMessenger);

        void destroyDebugUtilsMessengerExt(VkInstance instance,
                                           VkDebugUtilsMessengerEXT debugMessenger,
                                           const VkAllocationCallbacks *pAllocator);

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

        bool checkValidationLayerSupport();

        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        void createImage(u32 width,
                         u32 height,
                         VkFormat format,
                         VkImageTiling tiling,
                         VkImageUsageFlags usage,
                         VkMemoryPropertyFlags properties,
                         VkImage &image,
                         VkDeviceMemory &imageMemory);

        VkCommandBuffer beginSingleTimeCommands();

        void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR capabilities);

        std::vector<const char *> getRequiredExtensions();

      public:
        Renderer(const char *windowTitle, i32 width, i32 height);
        ~Renderer();
        bool pollForEvent();
        void drawFrame();
        GLFWwindow *window;
        void loadModel();
    };

} // namespace Noctis
