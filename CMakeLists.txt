cmake_minimum_required(VERSION 3.16)

project(Night-Knight
    VERSION 1.0
    DESCRIPTION "Night Knight game"
    LANGUAGES C CXX
)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not supported. Use a separate build directory.")
endif()

if(POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME})
add_subdirectory(src)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)

# Some vendored dependencies still declare cmake_minimum_required() below 3.5.
# CMake 4 removed compatibility with those old policy versions, so raise the
# effective policy floor without editing third-party sources.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(FREEGLUT_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(FREEGLUT_BUILD_STATIC_LIBS OFF CACHE BOOL "" FORCE)
set(FREEGLUT_BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
add_subdirectory(libs/freeglut-3.6.0 EXCLUDE_FROM_ALL)
target_include_directories(freeglut PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/libs/freeglut-3.6.0/include>"
)

add_subdirectory(libs/glew-2.2.0/build/cmake EXCLUDE_FROM_ALL)
target_include_directories(glew PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/libs/glew-2.2.0/include>"
)
add_subdirectory(libs/glm EXCLUDE_FROM_ALL)

set(FT_DISABLE_ZLIB ON CACHE BOOL "" FORCE)
set(FT_DISABLE_BZIP2 ON CACHE BOOL "" FORCE)
set(FT_DISABLE_PNG ON CACHE BOOL "" FORCE)
set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "" FORCE)
set(FT_DISABLE_BROTLI ON CACHE BOOL "" FORCE)
add_subdirectory(libs/freetype-2.13.3 EXCLUDE_FROM_ALL)

add_subdirectory(libs/Simple-OpenGL-Image-Library-master EXCLUDE_FROM_ALL)
target_include_directories(SOIL PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/libs/Simple-OpenGL-Image-Library-master/src>"
)

add_library(irrKlang SHARED IMPORTED GLOBAL)
set_target_properties(irrKlang PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/libs/irrKlang/include"
)

set(IRRKLANG_PLUGIN_FILES)
if(WIN32)
    if(MINGW)
        set(IRRKLANG_BIN_DIR "${PROJECT_SOURCE_DIR}/libs/irrKlang/bin/win32-gcc")
        set_target_properties(irrKlang PROPERTIES
            IMPORTED_LOCATION "${IRRKLANG_BIN_DIR}/irrKlang.dll"
            IMPORTED_IMPLIB "${PROJECT_SOURCE_DIR}/libs/irrKlang/lib/Win32-gcc/libirrKlang.a"
        )
    else()
        set(IRRKLANG_BIN_DIR "${PROJECT_SOURCE_DIR}/libs/irrKlang/bin/win32-visualStudio")
        set_target_properties(irrKlang PROPERTIES
            IMPORTED_LOCATION "${IRRKLANG_BIN_DIR}/irrKlang.dll"
            IMPORTED_IMPLIB "${PROJECT_SOURCE_DIR}/libs/irrKlang/lib/Win32-visualStudio/irrKlang.lib"
        )
    endif()
    list(APPEND IRRKLANG_PLUGIN_FILES
        "${IRRKLANG_BIN_DIR}/ikpMP3.dll"
        "${IRRKLANG_BIN_DIR}/ikpFlac.dll"
    )
elseif(APPLE)
    set(IRRKLANG_BIN_DIR "${PROJECT_SOURCE_DIR}/libs/irrKlang/bin/macosx-gcc")
    set_target_properties(irrKlang PROPERTIES
        IMPORTED_LOCATION "${IRRKLANG_BIN_DIR}/libirrklang.dylib"
    )
    list(APPEND IRRKLANG_PLUGIN_FILES
        "${IRRKLANG_BIN_DIR}/ikpMP3.dylib"
        "${IRRKLANG_BIN_DIR}/ikpFLAC.dylib"
    )
else()
    set(IRRKLANG_BIN_DIR "${PROJECT_SOURCE_DIR}/libs/irrKlang/bin/linux-gcc")
    set_target_properties(irrKlang PROPERTIES
        IMPORTED_LOCATION "${IRRKLANG_BIN_DIR}/libIrrKlang.so"
    )
    list(APPEND IRRKLANG_PLUGIN_FILES
        "${IRRKLANG_BIN_DIR}/ikpMP3.so"
        "${IRRKLANG_BIN_DIR}/ikpFlac.so"
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    glew
    freeglut
    glm
    freetype
    SOIL
    irrKlang
)

set(ASSET_DIRS fonts images levels shaders sound)
foreach(asset_dir IN LISTS ASSET_DIRS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_SOURCE_DIR}/assets/${asset_dir}"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/${asset_dir}"
        VERBATIM
    )
endforeach()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:freeglut>"
        "$<TARGET_FILE:glew>"
        "$<TARGET_FILE:irrKlang>"
        ${IRRKLANG_PLUGIN_FILES}
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    VERBATIM
)
