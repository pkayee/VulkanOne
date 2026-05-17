
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

#include <vk_one/engine/core/window.h>
#include <vk_one/engine/config.h>


namespace vk_one {
    Window::Window(const WindowConfig* config) : windowConfig(config){
        #ifdef DEBUG
            std::cout << "Loaded window:'" << windowConfig->name << "'"
            << " Size:" << windowConfig->width << "x" << windowConfig->height;
        #endif
        initWindow();
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::initWindow() {
        if (!glfwInit()) { throw std::runtime_error("glfw could not be initialized"); }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, windowConfig->resizable);

        this->window = glfwCreateWindow(windowConfig->width, windowConfig->height, windowConfig->name.c_str(), nullptr, nullptr);

        if (!this->window) { throw std::runtime_error("failed to create window"); }
    }
}
