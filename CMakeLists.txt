cmake_minimum_required(VERSION 3.0.2)

PROJECT(VTKDualSigmoid)

# Glob all the program file types together
file(GLOB CXX_FILES *.cxx)
file(GLOB HEADER_FILES *.h)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

# Include the current directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_executable(VTKDualSigmoid WIN32 ${CXX_FILES} ${HEADER_FILES})
target_link_libraries(VTKDualSigmoid ${VTK_LIBRARIES})