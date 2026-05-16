#pragma once

#include <string>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>



namespace app {
    struct WindowConfig;
    class Window {
    public:
        Window(const WindowConfig* config);
        ~Window();

        Window(const Window &) = delete;
        Window operator&(const Window &) = delete;

        bool windowShouldClose() { return glfwWindowShouldClose(window); };
    private:
        const WindowConfig* windowConfig;
        void initWindow();

        GLFWwindow* window;
    };
}