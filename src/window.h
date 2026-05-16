#pragma once

#include <string>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>



namespace app {

    class Window {
    public:
        Window(int w, int h, std::string name);
        ~Window();

        Window(const Window &) = delete;
        Window operator&(const Window &) = delete;

        bool windowShouldClose() { return glfwWindowShouldClose(window); };
    private:
        void initWindow();

        const int32_t WIDTH;
        const int32_t HEIGHT;

        std::string windowName;
        GLFWwindow* window;
    };
}