#include <stdexcept>
#include <iostream>

#include <vk_one/engine/renderer/instance.hpp>
#include <vk_one/engine/core/window.h>
#include <vk_one/engine/config.h>


namespace vk_one {
    Window::Window(const WindowConfig* config) : m_windowConfig(config){
        #ifdef DEBUG
            std::cerr << "\033[33m"
            << "Loaded window:'" << m_windowConfig->name << "'"
            << " Size:" << m_windowConfig->width << "x" << m_windowConfig->height
            << "\033[0m" << "\n";
        #endif
        initWindow();
    }

    Window::~Window() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Window::initWindow() {
        if (!glfwInit()) { throw std::runtime_error("glfw could not be initialized"); }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, m_windowConfig->resizable);

        this->m_window = glfwCreateWindow(m_windowConfig->width, m_windowConfig->height, m_windowConfig->name.c_str(), nullptr, nullptr);

        if (!this->m_window) { throw std::runtime_error("failed to create window"); }
    }
}
