add_library(vk_one INTERFACE)

target_sources(vk_one INTERFACE
        app/application.h

        engine/config.h

        engine/core/instance.hpp
        engine/core/window.h

        engine/renderer/memory_allocator.hpp
        engine/renderer/pipeline.hpp
)

target_include_directories(vk_one INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
        $<INSTALL_INTERFACE:include>

)