module;

#include <string>
#include <GLFW/glfw3.h>
#include <stdexcept>

module window;


namespace app {
    Window::Window(int w, int h, std::string name) : WIDTH{w}, HEIGHT{h}, windowName{name} {
        initWindow();
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::initWindow() {
        if (!glfwInit()) { throw std::runtime_error("glfw could not be initialized"); }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        this->window = glfwCreateWindow(WIDTH, HEIGHT, windowName.c_str(), nullptr, nullptr);

        if (!this->window) { throw std::runtime_error("failed to create window"); }
    }
}
