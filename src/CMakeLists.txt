include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5)

set(BUILD_EXAMPLES
    OFF
    CACHE BOOL "Disable building raylib examples")
set(BUILD_TESTS
    OFF
    CACHE BOOL "Disable building raylib tests")

FetchContent_MakeAvailable(raylib)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sort.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Add compiler options to enable all warnings
target_compile_options(
  ${PROJECT_NAME}
  PRIVATE -Wall
          -Wextra
          -Wpedantic
          -Werror
          -Wno-missing-field-initializers
          -Wno-unused-parameter
          -march=native)
