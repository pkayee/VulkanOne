#pragma once

#include <vk_one/engine/utils.hpp>
#include <nlohmann/json.hpp>

namespace vk_one {

    class ConfigManager {
    public:
        using ConfigValue = std::variant<int, float, bool, std::string>;

        static ConfigManager& instance() {
            static ConfigManager s_instance;
            return s_instance;
        }

        ConfigManager(const ConfigManager&) = delete;
        ConfigManager& operator=(const ConfigManager&) = delete;

        bool loadFromFile(const std::string& filePath) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                Log::warn(std::format("Config Error: could not open '{}'", filePath));
                return false;
            }

            nlohmann::json rootJson;
            try {
                file >> rootJson;
            } catch (const nlohmann::json::parse_error& e) {
                Log::warn(std::format("Config JSON Parse Error: {}", e.what() ));
                return false;
            }

            auto flattened = rootJson.flatten();
            m_settings.clear();

            #ifdef DEBUG
            Log::print("[===LOADING CONFIGS===]");
            #endif
            for (auto& [key, value] : flattened.items()) {

                std::string cleanKey = key.substr(1);
                std::replace(cleanKey.begin(), cleanKey.end(), '/', '.');

                if (value.is_number_integer())      m_settings[cleanKey] = value.get<int>();
                else if (value.is_number_float())   m_settings[cleanKey] = value.get<float>();
                else if (value.is_boolean())        m_settings[cleanKey] = value.get<bool>();
                else if (value.is_string())         m_settings[cleanKey] = value.get<std::string>();

                #ifdef DEBUG
                Log::colourKeys(cleanKey);
                #endif
            }
            return true;
        }

        bool has(const std::string& key) const {
            return m_settings.contains(key);
        }


        // honestly will refactor later lol
        template<typename T>
        T get(const std::string& key, std::optional<T> defaultValue = std::nullopt) const {

            if (!has(key)) {
                if (defaultValue.has_value()) return defaultValue.value();
                Log::throwRuntimeError("Config: key not found '" + key + "'");
            }

            auto it = m_settings.find(key);

            if (!std::holds_alternative<T>(it->second)) {
                if (defaultValue.has_value()) {
                    Log::warn(std::format("Config: type mismatch for '{}' using default.", key));
                    return defaultValue.value();
                }

                Log::throwRuntimeError(std::format("Config: type mismatch for '{}'", key));
            }

            return std::get<T>(it->second);
        }

    private:
        ConfigManager() = default;
        std::unordered_map<std::string, ConfigValue> m_settings;
    };

}