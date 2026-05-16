include_guard(GLOBAL)

find_program(GLSLANG glslangValidator REQUIRED)

set(SHADER_DIR "${CMAKE_SOURCE_DIR}/assets/shaders/src")
set(SHADER_BUILD_DIR "${CMAKE_SOURCE_DIR}/assets/shaders/build")

file(GLOB SHADERS
        "${SHADER_DIR}/*.vert"
        "${SHADER_DIR}/*.frag"
)

function(compileShaders TARGET_NAME)
    file(GLOB SHADERS
            "${SHADER_DIR}/*.vert"
            "${SHADER_DIR}/*.frag"
    )
    
    foreach(SHADER ${SHADERS})
        get_filename_component(SHADER_NAME ${SHADER} NAME)
        set(OUTPUT "${SHADER_BUILD_DIR}/${SHADER_NAME}.spv")

        add_custom_command(
                OUTPUT ${OUTPUT}
                COMMAND ${CMAKE_COMMAND} -E make_directory ${SHADER_BUILD_DIR}
                COMMAND ${GLSLANG} -V ${SHADER} -o ${OUTPUT}
                DEPENDS ${SHADER}
                COMMENT "Compiling shader: ${SHADER_NAME}"
        )

        target_sources(${TARGET_NAME} PRIVATE ${OUTPUT})
    endforeach()
endfunction()