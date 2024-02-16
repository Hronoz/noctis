#include "Renderer.hpp"

#include "render/vulkan/VulkanBackend.hpp"

template <class T>
Renderer<T>::Renderer()
{
    T("Test");
}

template <class T>
Renderer<T>::~Renderer()
= default;

template <class T>
bool Renderer<T>::drawFrame(RenderPacket packet)
{
    return true;
}

template class Renderer<VulkanBackend>;