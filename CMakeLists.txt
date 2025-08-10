cmake_minimum_required(VERSION 3.31)
project(TheCherno)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
list(FILTER SRC_FILES EXCLUDE REGEX "src/vendor/glm/.*")
list(FILTER SRC_FILES EXCLUDE REGEX "src/vendor/imgui/main.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

# define path to GLFW
set(GLFW_ROOT_DIR ${PROJECT_SOURCE_DIR}/Dependencies/GLFW)
# Point the directory containing glfw3.lib
set(GLFW_LIBRARY_DIR ${GLFW_ROOT_DIR}/lib-vc2022)

find_library(GLFW_LIBRARY_FILE
        NAMES glfw3
        PATHS ${GLFW_LIBRARY_DIR}
        NO_DEFAULT_PATH
)

if (NOT GLFW_LIBRARY_FILE)
    message(FATAL_ERROR "GLFW lib not found in ${GLFW_LIBRARY_DIR}. Searched for 'glfw3'.")
else ()
    message(STATUS "Found GLFW library: ${GLFW_LIBRARY_FILE}")
endif ()

# define path to GLEW
set(GLEW_ROOT_DIR ${PROJECT_SOURCE_DIR}/Dependencies/GLEW)
# Point the directory containing glew.lib
set(GLEW_LIBRARY_DIR ${GLEW_ROOT_DIR}/lib/Release/Win32)

find_library(GLEW_LIBRARY_FILE
        NAMES glew32s
        PATHS ${GLEW_LIBRARY_DIR}
        NO_DEFAULT_PATH
)

if (NOT GLEW_LIBRARY_FILE)
    message(FATAL_ERROR "GLEW lib not found in ${GLEW_LIBRARY_DIR}. Searched for 'glew'.")
else ()
    message(STATUS "Found GLEW library: ${GLEW_LIBRARY_FILE}")
endif ()

# link libs
target_link_libraries(${PROJECT_NAME} PUBLIC
        ${GLFW_LIBRARY_FILE}
        opengl32
        ${GLEW_LIBRARY_FILE}
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${GLFW_ROOT_DIR}/include
        ${GLEW_ROOT_DIR}/include
        ${PROJECT_SOURCE_DIR}/src/vendor/glm
)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_STATIC)