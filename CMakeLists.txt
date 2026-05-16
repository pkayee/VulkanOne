cmake_minimum_required(VERSION 3.28)
project(vk_one_engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake_modules/compile_shaders.cmake)

add_subdirectory(include/vk_one)


add_executable(vk_one_engine src/main.cpp
        src/engine/renderer/pipeline.cpp
        include/vk_one/engine/renderer/pipeline.hpp
        include/vk_one/engine/core/instance.hpp
        src/engine/core/instance.cpp
        include/vk_one/engine/renderer/memory_allocator.hpp
        src/engine/renderer/memory_allocator.cpp)

target_sources(vk_one_engine
        PRIVATE
        src/app/application.cpp
        src/engine/core/window.cpp
        include/vk_one/engine/core/window.h
        include/vk_one/app/application.h
        include/vk_one/engine/config.h
)



find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(nlohmann_json REQUIRED)

target_link_libraries(vk_one_engine
        PRIVATE
        vk_one
        Vulkan::Vulkan
        glfw
        glm::glm
        nlohmann_json::nlohmann_json
)





