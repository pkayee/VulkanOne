add_library(vk_one INTERFACE)

set(SOURCE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/app"
        "${CMAKE_CURRENT_SOURCE_DIR}/engine"
        "${CMAKE_CURRENT_SOURCE_DIR}/engine/core"
        "${CMAKE_CURRENT_SOURCE_DIR}/engine/renderer"
)
set(SOURCE_FILES "")

foreach (dir IN LISTS SOURCE_DIRS)
    file(GLOB local_files CONFIGURE_DEPENDS "${dir}/*.cpp")

    foreach (file IN LISTS local_files)
        list(APPEND SOURCE_FILES "${file}")
    endforeach ()
endforeach ()

target_sources(vk_one INTERFACE ${SOURCE_FILES})

target_include_directories(vk_one INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
        $<INSTALL_INTERFACE:include>

)