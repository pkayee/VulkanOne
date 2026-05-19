cmake_minimum_required(VERSION 3.28)
project(VulkanOne)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake_modules/compile_shaders.cmake)

add_subdirectory(include/vk_one)
set(SOURCE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/app"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/engine/core"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/engine/renderer"
)
set(SOURCE_FILES "")

add_executable(VulkanOne src/main.cpp)

foreach (dir IN LISTS SOURCE_DIRS)
    file(GLOB local_files CONFIGURE_DEPENDS "${dir}/*.cpp")

    foreach (file IN LISTS local_files)
        list(APPEND SOURCE_FILES "${file}")
    endforeach ()
endforeach ()

target_sources(VulkanOne PRIVATE ${SOURCE_FILES})

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(nlohmann_json REQUIRED)

target_link_libraries(VulkanOne
        PRIVATE
        vk_one
        Vulkan::Vulkan
        glfw
        glm::glm
        nlohmann_json::nlohmann_json
)

target_precompile_headers(VulkanOne PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/vk_one/engine/renderer/pch.h)

target_compile_definitions(VulkanOne PRIVATE
        CONFIG_PATH="${CMAKE_SOURCE_DIR}/src/engine/configs.json"
)

target_compile_definitions(VulkanOne PUBLIC DEBUG)



