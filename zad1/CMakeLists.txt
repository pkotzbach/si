cmake_minimum_required(VERSION 3.10)
project(si)
include(FetchContent)
FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
add_executable(
    si 
    zad1.cpp
    dataProviders.cpp
    factory.cpp
    algorithm.cpp
)
target_link_libraries(si PRIVATE nlohmann_json::nlohmann_json)