cmake_minimum_required(VERSION 3.28)
project(vk_one_engine)

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


add_executable(vk_one_engine src/main.cpp)

foreach (dir IN LISTS SOURCE_DIRS)
    file(GLOB local_files CONFIGURE_DEPENDS "${dir}/*.cpp")

    foreach (file IN LISTS local_files)
        list(APPEND SOURCE_FILES "${file}")
    endforeach ()
endforeach ()

target_sources(vk_one_engine PRIVATE ${SOURCE_FILES})

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





