#pragma once



#include <vk_one/engine/renderer/pch.h>

namespace vk_one {
#ifdef DEBUG
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = false;
#endif

    class Log {
    public:
        enum class Color {
            RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, RANDOM, AUTO
        };

        static void print(const std::string& msg, Color color = Color::WHITE) {
            std::cerr << resolveColor(color, msg) << msg << RESET << "\n";
            std::cerr.flush();
        }

        static void info(const std::string& msg, Color color = Color::GREEN) {
            std::cerr << resolveColor(color, msg) << "[INFO] " << msg << RESET << "\n";
            std::cerr.flush();
        }

        static void warn(const std::string& msg, Color color = Color::YELLOW) {
            std::cerr << resolveColor(color, msg) << "[WARN] " << msg << RESET << "\n";
        }

        static void error(const std::string& msg, Color color = Color::RED) {
            std::cerr << resolveColor(color, msg) << "[ERROR] " << msg << RESET << "\n";
        }

        static void throwRuntimeError(
            const std::string& msg, Color color = Color::RED,
            const char* file = __builtin_FILE(),
            int line = __builtin_LINE())
        {
            std::ostringstream errorString;
            std::string err = std::format("[RUNTIME_ERROR] {}:{} ", file, line);
            errorString << resolveColor(color, msg) << err << msg << RESET;
            throw std::runtime_error(errorString.str());
        }

        static void colourKeys(const std::string& key, const std::string& value = "",
        Color color = Color::AUTO)
        {
            std::cerr << resolveColor(color, key) << key;

            if (!value.empty())
                std::cerr << " : " << value;

            std::cerr << RESET << "\n";
            std::cerr.flush();
        }

    private:
        static constexpr const char* RESET   = "\033[0m";
        static constexpr const char* COLORS[] = {
            "\033[31m",  // RED
            "\033[32m",  // GREEN
            "\033[33m",  // YELLOW
            "\033[34m",  // BLUE
            "\033[35m",  // MAGENTA
            "\033[36m",  // CYAN
            "\033[37m",  // WHITE
        };

        static const char* resolveColor(Color color, const std::string& msg) {
            switch (color) {
                case Color::RED:     return COLORS[0];
                case Color::GREEN:   return COLORS[1];
                case Color::YELLOW:  return COLORS[2];
                case Color::BLUE:    return COLORS[3];
                case Color::MAGENTA: return COLORS[4];
                case Color::CYAN:    return COLORS[5];
                case Color::WHITE:   return COLORS[6];
                case Color::RANDOM:  return randomColor();
                case Color::AUTO:    return autoColor(msg);
                default:             return COLORS[6];
            }
        }

        static const char* autoColor(const std::string& key) {
            std::string prefix = key.substr(0, key.find('.'));

            static std::unordered_map<std::string, const char*> prefixColors;
            static size_t colorIndex = 0;

            if (!prefixColors.contains(prefix))
                prefixColors[prefix] = COLORS[colorIndex++ % 6];

            return prefixColors[prefix];
        }

        static const char* randomColor() {
            static std::mt19937 rng(std::random_device{}());
            static std::uniform_int_distribution<size_t> dist(0, 5);
            return COLORS[dist(rng)];
        }
    };

    inline void VK_CHECK_SUCCESS(VkResult result, const char* message) {
        if (result != VK_SUCCESS) {
            Log::throwRuntimeError(message);
        }
    }
}
