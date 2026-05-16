cmake_minimum_required(VERSION 3.28)
project(vk_one_engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake_modules/compile_shaders.cmake)

add_subdirectory(include/vk_one)


add_executable(vk_one_engine src/main.cpp)

target_sources(vk_one_engine
        PRIVATE
        # src/app
        src/app/application.cpp

        # src/engine/core
        src/engine/core/window.cpp

        # src/engine/renderer
        src/engine/renderer/pipeline.cpp
        src/engine/renderer/memory_allocator.cpp
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





