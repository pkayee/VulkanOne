#include <iostream>
import application;
#include <exception>

int main() {
    app::MainApplication app{};
    try {
        app.init();
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
}