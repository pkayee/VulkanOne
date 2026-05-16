#pragma once


#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

namespace app {
    struct WindowConfig {
        static inline const std::string structName = "WindowConfig";

        int width;
        int height;
        bool resizable;
        std::string name;

        friend void from_json(const nlohmann::json& j, WindowConfig& c) {
            j.at("width").get_to(c.width);
            j.at("height").get_to(c.height);
            j.at("resizable").get_to(c.resizable);
            j.at("name").get_to(c.name);
        }
    };

    class ConfigManager {
    public:
        WindowConfig parseJson(std::string filePath) {
            std::ifstream file(filePath);

            if (!file.is_open()) { throw std::runtime_error("Could not open json! Check if Working dir is correct!"); }

            nlohmann::json data = nlohmann::json::parse(file);
            WindowConfig windowConfig;

            loadConfig(data, windowConfig);
            return windowConfig;
        }

    private:
        template<typename T>
        void loadConfig(const nlohmann::json& data, T& configStruct ) {
            auto const& section = data.at(T::structName);
            configStruct = section.template get<T>();
        }
    };
}