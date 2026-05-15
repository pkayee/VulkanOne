module;

#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

export module config;


export namespace app {
    struct WindowConfig {
        static inline const std::string structName = "WindowConfig";

        int width;
        int height;
        std::string name;

        friend void from_json(const nlohmann::json j, WindowConfig& c) {
            j.at("width").get_to(c.width);
            j.at("height").get_to(c.height);
            j.at("name").get_to(c.name);
        }
    };

    class ConfigManager {
    public:
        WindowConfig parseJson(std::string filePath) {
            std::ifstream file(filePath);

            if (!file.is_open()) { throw std::runtime_error("could not open json"); }

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