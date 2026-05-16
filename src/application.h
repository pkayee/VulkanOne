#pragma once

#include "window.h"
#include <memory>



namespace app {
    class MainApplication {
    public:
        std::string jsonFilePath = "src/configs.json";
        void init();
        void run();


    private:
        std::unique_ptr<Window> mainWindow;
    };

}
