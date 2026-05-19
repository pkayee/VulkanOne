#pragma once

#include <string>

#include <GLFW/glfw3.h>



namespace vk_one {
    struct WindowConfig;
    class Window {
    public:
        Window(const WindowConfig* config);
        ~Window();

        Window(const Window &) = delete;
        Window operator&(const Window &) = delete;

        bool windowShouldClose() { return glfwWindowShouldClose(m_window); }
        GLFWwindow* handle() { return m_window; }

    private:
        const WindowConfig* m_windowConfig;
        void initWindow();

        GLFWwindow* m_window;
    };
}