cmake_minimum_required(VERSION 3.22)

project(rectpack2D VERSION 1.0.0)

add_library(rectpack2D)

target_include_directories(rectpack2D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(EASTL CONFIG REQUIRED)
target_link_libraries(rectpack2D PUBLIC EASTL)

target_compile_options(rectpack2D PRIVATE
  -Wall
  -Werror
  -Wextra
  -Wno-error=unused-command-line-argument
  -Wno-error=missing-braces
)

OPTION(BUILD_EXAMPLES "Build examples" OFF)

if(BUILD_EXAMPLE)
	add_executable(example example/main.cpp)
    target_link_libraries(example PRIVATE rectpack2D)
endif()

install(DIRECTORY include/ DESTINATION include)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/rectpack2DConfigVersion.cmake
        COMPATIBILITY SameMajorVersion)
install(TARGETS rectpack2D EASTL
        EXPORT rectpack2DTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT rectpack2DTargets
        FILE "rectpack2DConfig.cmake"
        NAMESPACE rectpack2D::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rectpack2D)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/rectpack2DConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rectpack2D)