cmake_minimum_required(VERSION 3.0.0)
project(Test VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Test main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Start GLFW

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if(MINGW)
    set(GLFW_LIBRARIES glfw3 opengl32)
else()
    set(GLFW_LIBRARIES glfw3 rt Xxf86vm Xrandr Xi X11 GL)
endif()

add_subdirectory(glfw-3.3.2)
target_link_libraries(Test glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(Test OpenGL::GL)