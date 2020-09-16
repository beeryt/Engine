cmake_minimum_required(VERSION 3.3)
project(engine)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

option(BUILD_DOCS "Build documentation" OFF)
if (BUILD_DOCS)
  # check if doxygen is installed
  find_package(Doxygen REQUIRED)

  # configure the doxygen config file
  set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

  # create doxygen target
  add_custom_target(doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating documentation with Doxygen"
    VERBATIM)
endif()

add_library(glad libs/glad/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)
target_link_libraries(glad ${CMAKE_DL_LIBS})

add_library(engine src/engine/Engine.cpp src/engine/EngineTime.cpp)
target_include_directories(engine PUBLIC src/engine/include)
target_compile_options(engine PUBLIC -Wall -Wextra -g -Og)
set_property(TARGET engine PROPERTY CXX_STANDARD 17)

add_library(platform src/platform/Platform.cpp)
target_include_directories(platform PUBLIC src/platform/include)
target_compile_options(platform PUBLIC -Wall -Wextra -g -Og)
target_link_libraries(platform glm glad)
set_property(TARGET platform PROPERTY CXX_STANDARD 17)

add_executable(main src/main.cpp)
target_compile_options(main PUBLIC -Wall -Wextra -g -Og)
target_link_libraries(main engine platform SDL2::Main)
set_property(TARGET main PROPERTY CXX_STANDARD 17)
