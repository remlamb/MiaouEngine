cmake_minimum_required(VERSION 3.22)
project(MiaouEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(IMGUI CONFIG REQUIRED)

# Add a CMake option to enable or disable Tracy Profiler
option(USE_TRACY "Use Tracy Profiler" OFF)

if (USE_TRACY)
    # Enable Tracy profiling by setting the preprocessor directive
    add_compile_definitions(TRACY_ENABLE)
    # Include Tracy's headers for the entire project
    include_directories(libs/TracyProfiler/tracy)

    # Add the Tracy source code as part of the project
    add_library(tracyClient STATIC libs/TracyProfiler/TracyClient.cpp)
endif()

option(ENABLE_ADDRESS_SANITIZER "Enable AddressSanitizer" OFF)

IF(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2 /Oi /Oy-")

    # Check if AddressSanitizer is enabled
    if(ENABLE_ADDRESS_SANITIZER)
        # Enable AddressSanitizer flags and options
        add_compile_options(/fsanitize=address /DEBUG)
    endif()
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps -march=haswell -ffast-math")

    # Check if AddressSanitizer is enabled
    if(ENABLE_ADDRESS_SANITIZER)
        # Enable AddressSanitizer flags and options
        add_compile_options(-fsanitize=address)
    endif()
ENDIF()


file(GLOB_RECURSE COMMON_SRC_FILES common/include/*.h common/src/*.cpp)
add_library(Common ${COMMON_SRC_FILES})
set_target_properties(Common PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Common PUBLIC common/include/)
target_include_directories(Common PUBLIC libs/Math/include/)


file(GLOB_RECURSE PHYSICS_SRC_FILES physics/include/*.h physics/src/*.cpp)
add_library(PhysicsEngineLib ${PHYSICS_SRC_FILES})
set_target_properties(PhysicsEngineLib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(PhysicsEngineLib PUBLIC physics/include/)
target_include_directories(PhysicsEngineLib PUBLIC libs/Math/include/)
target_link_libraries(PhysicsEngineLib PUBLIC Common)


if (USE_TRACY)
    target_compile_definitions(PhysicsEngineLib PUBLIC TRACY_ENABLE)
    # Link the TracyClient library
    target_link_libraries(PhysicsEngineLib PRIVATE tracyClient)
endif()

file(GLOB_RECURSE GRAPHICS_SRC_FILES graphics/include/*.h graphics/src/*.cpp)
add_library(GraphicsLib ${GRAPHICS_SRC_FILES})
set_target_properties(PhysicsEngineLib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(GraphicsLib PUBLIC graphics/include/)
target_include_directories(GraphicsLib PUBLIC libs/Math/include/)
target_link_libraries(GraphicsLib PUBLIC SDL2::SDL2)
target_link_libraries(GraphicsLib PUBLIC PhysicsEngineLib SDL2::SDL2 Common imgui::imgui)



file(GLOB_RECURSE SAMPLES_SRC_FILES samples/include/*.h samples/src/*.cpp)
add_library(Samples ${SAMPLES_SRC_FILES})
set_target_properties(PhysicsEngineLib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Samples PUBLIC samples/include/)
target_link_libraries(Samples PUBLIC PhysicsEngineLib)
target_link_libraries(Samples PUBLIC GraphicsLib)
target_link_libraries(Samples PUBLIC Common)

if (USE_TRACY)
    target_compile_definitions(Samples PUBLIC TRACY_ENABLE)
    # Link the TracyClient library
    target_link_libraries(Samples PRIVATE tracyClient)
endif()

# Disable SDL main
add_definitions(-DSDL_MAIN_HANDLED)

add_executable(Main main.cpp)
target_link_libraries(Main PUBLIC Samples)

if (USE_TRACY)
    target_compile_definitions(Main PUBLIC TRACY_ENABLE)
    # Link the TracyClient library
    target_link_libraries(Main PRIVATE tracyClient)
endif()

# Tests
SET(TEST_DIR ${CMAKE_SOURCE_DIR}/physics_engine_tests)
file(GLOB TEST_FILES ${TEST_DIR}/*.cpp )

foreach(test_file ${TEST_FILES} )
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})

    target_link_libraries(${test_name} PUBLIC PhysicsEngineLib)
    target_link_libraries(${test_name} PRIVATE GTest::gtest GTest::gtest_main)
endforeach()