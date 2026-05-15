cmake_minimum_required(VERSION 4.1)
project(vulkanone)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(vulkanone src/main.cpp)

target_sources(vulkanone
        PUBLIC
        FILE_SET CXX_MODULES FILES
        src/application.cppm
        src/window.cppm
        src/config.cppm
        PRIVATE
        src/application.cpp
        src/window.cpp
)


find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(nlohmann_json REQUIRED)

target_link_libraries(vulkanone
        PRIVATE
        Vulkan::Vulkan
        glfw
        glm::glm
        nlohmann_json::nlohmann_json
)
