cmake_minimum_required(VERSION 3.15)

project(VentanaGris3D
    VERSION 1.0.0
    DESCRIPTION "Simulador de tanque 3D procedural con SDL2 y OpenGL"
    LANGUAGES CXX
)

# ------------------------------------------------------------
# Configuración del lenguaje
# ------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ejecutables en la carpeta bin del proyecto.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/bin"
)

# ------------------------------------------------------------
# Dependencias
# ------------------------------------------------------------

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)

# ------------------------------------------------------------
# Código fuente
# ------------------------------------------------------------

set(PROJECT_SOURCES
    Camera.cpp
    Tilemap.cpp
    CSprite.cpp
    TileUtils.cpp
    VentanaGris3D.cpp
    main.cpp
)

# ------------------------------------------------------------
# Ejecutable
# ------------------------------------------------------------

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

# ------------------------------------------------------------
# Inclusiones y bibliotecas
# ------------------------------------------------------------

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        PkgConfig::SDL2
        OpenGL::GL
        OpenGL::GLU
        GLEW::GLEW
        glm::glm
)

# ------------------------------------------------------------
# Opciones de compilación
# ------------------------------------------------------------

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
endif()

message(STATUS "Proyecto: ${PROJECT_NAME}")
message(STATUS "Estándar de C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "Directorio del ejecutable: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "Dependencias: SDL2, OpenGL, GLU, GLEW y GLM")
