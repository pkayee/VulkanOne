cmake_minimum_required(VERSION 3.28)
project(vulkanone)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(vulkanone src/main.cpp)

target_sources(vulkanone
        PRIVATE
        src/application.cpp
        src/window.cpp
        src/window.h
        src/application.h
        src/config.h
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
