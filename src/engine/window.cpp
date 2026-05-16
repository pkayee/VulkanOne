
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

#include "window.h"
#include "config.h"


namespace app {
    Window::Window(const WindowConfig* config) : windowConfig(config){
        if (windowConfig) {
            std::cout << "Loaded name: '" << windowConfig->name << "'" << std::endl;
        }
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
