#include <iostream>
#include <vk_one/app/application.h>
#include <exception>

int main() {
    vk_one::Application app{};
    try {
        app.init();
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
}