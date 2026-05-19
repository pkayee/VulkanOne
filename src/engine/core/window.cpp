#include <stdexcept>
#include <iostream>

#include <vk_one/engine/renderer/instance.hpp>
#include <vk_one/engine/core/window.h>
#include <vk_one/engine/config.h>


namespace vk_one {
    Window::Window(int width, int height, bool resizable, const std::string &name)
    : m_width(width), m_height(height), m_resizable(resizable), m_name(name) {
    #ifdef DEBUG
        Log::print("[===LOADING WINDOW===]");

        Log::print(std::format(
            "Loaded window: '{}' Size: {}x{}",
            m_name, m_width, m_height),
        Log::Color::BLUE);
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
        glfwWindowHint(GLFW_RESIZABLE, m_resizable);

        this->m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), nullptr, nullptr);

        if (!this->m_window) { throw std::runtime_error("failed to create window"); }
    }
}
