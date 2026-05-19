add_library(vk_one INTERFACE)

target_include_directories(vk_one
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
        $<INSTALL_INTERFACE:include>
)

