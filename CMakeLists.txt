cmake_minimum_required(VERSION 3.15)
project(asteroid LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(asteroid
    src/asteroid.cpp
    src/earth.cpp
    src/logger.cpp
    src/main.cpp
    src/open_gl_manager.cpp
    src/renderer.cpp
    src/simulation_orchestrator.cpp
    src/simulator.cpp
    src/thread_manager.cpp
)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt")
set(GLFW_ROOT "/opt/homebrew/opt/glfw")
set(GLEW_ROOT "/opt/homebrew/opt/glew")

target_include_directories(asteroid PRIVATE
    include
    ${GLEW_ROOT}/include
    ${GLFW_ROOT}/include
)

target_link_libraries(asteroid
    ${GLFW_ROOT}/lib/libglfw.3.dylib
    ${GLEW_ROOT}/lib/libGLEW.dylib
    "-framework OpenGL"
)
