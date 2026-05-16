#pragma once

#include "engine/window.h"
#include "engine/config.h"
#include <memory>



namespace app {
    class MainApplication {
    public:
        std::string jsonFilePath = "src/engine/configs.json";
        void init();
        void run();


    private:
        std::unique_ptr<Window> mainWindow;
        WindowConfig windowConfig;
    };

}
