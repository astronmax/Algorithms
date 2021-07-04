# --[ Project ] ---------------------------------------------------------------
project(algorithms LANGUAGES CXX)
cmake_minimum_required(VERSION 3.0)

# --[ Library ] ---------------------------------------------------------------
set(LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

set(LIB_MODULES  ${LIB_MODULES} ${LIB_DIR}/data_structures)

add_library(${PROJECT_NAME} INTERFACE)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
target_include_directories(${PROJECT_NAME} INTERFACE ${LIB_MODULES})