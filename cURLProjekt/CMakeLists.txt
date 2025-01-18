cmake_minimum_required(VERSION 3.26)
project(cURLProjekt)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/muell/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

add_executable(cURLProjekt
        main.cpp
        MainController.cpp
        WeatherAPI.cpp
        GoogleMapsAPI.cpp
        CurlUtils.cpp
)

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR})

target_link_libraries(cURLProjekt CURL::libcurl)

set(CMAKE_GENERATOR "MinGW Makefiles")
