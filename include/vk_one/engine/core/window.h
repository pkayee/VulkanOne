#pragma once

#include <string>

#include <GLFW/glfw3.h>

#include <vk_one/engine/config.h>

namespace vk_one {
    class Window {
    public:
        Window(int width, int height, bool resizable, const std::string& name);
        ~Window();

        Window(const Window &) = delete;
        Window& operator=(const Window &) = delete;

        bool windowShouldClose() { return glfwWindowShouldClose(m_window); }
        GLFWwindow* handle() { return m_window; }
    private:
        void initWindow();

        int32_t m_width;
        int32_t m_height;
        bool m_resizable;

        std::string m_name;

        GLFWwindow* m_window;
    };
}