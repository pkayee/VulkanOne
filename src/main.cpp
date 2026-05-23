#include <iostream>
#include <vk_one/app/application.h>
#include <exception>
#include <vk_one/engine/utils.hpp>

int main() {
    vk_one::Application app{};
    try {
        app.init();
        app.run();
    } catch (const std::exception &e) {
        vk_one::Log::warn(e.what());
    }
}