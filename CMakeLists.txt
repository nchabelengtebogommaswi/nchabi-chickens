cmake_minimum_required(VERSION 3.20)

project(
        NchabiChickens
        VERSION 1.0.0
        DESCRIPTION "Nchabi Chickens Backend"
        LANGUAGES CXX
)

#
# C++ Standard
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#
# Output directory
#
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

#
# Packages
#
find_package(PkgConfig REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Catch2 3 REQUIRED)

pkg_check_modules(SQLITE3 REQUIRED sqlite3)

find_library(
        CPP_HTTPLIB_LIBRARY
        cpp-httplib
        REQUIRED
)

###############################################################
# Core Library
###############################################################

add_library(
        NchabiCore

        src/database/DatabaseConnection.cpp
        src/database/Statement.cpp

        src/repository/ChickenRepository.cpp
        include/controllers/ChickenController.h
        include/services/ChickenService.h
        src/services/ChickenService.cpp
        src/controllers/ChickenController.cpp
        src/controllers/ChickenController.cpp
)

target_include_directories(
        NchabiCore
        PUBLIC
        include
)

target_link_libraries(
        NchabiCore
        PUBLIC
        ${SQLITE3_LIBRARIES}
        ${PostgreSQL_LIBRARIES}
        nlohmann_json::nlohmann_json
)

###############################################################
# Main Application
###############################################################

add_executable(
        NchabiChickens

        src/main.cpp
        include/controllers/ChickenController.h
        include/services/ChickenService.h
        src/services/ChickenService.cpp
        src/controllers/ChickenController.cpp
        src/controllers/ChickenController.cpp
)

target_link_libraries(
        NchabiChickens
        PRIVATE
        NchabiCore
        ${CPP_HTTPLIB_LIBRARY}
)

###############################################################
# Unit Tests
###############################################################

add_executable(
        NchabiChickensTests

        tests/fixtures/DatabaseFixture.cpp

        tests/repository/ChickenRepositoryFixtureTest.cpp
)

target_include_directories(
        NchabiChickensTests
        PRIVATE
        include
        tests
)

target_compile_definitions(
        NchabiChickensTests
        PRIVATE
        PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
)

target_link_libraries(
        NchabiChickensTests
        PRIVATE
        NchabiCore
        Catch2::Catch2WithMain
)

###############################################################
# CTest
###############################################################

include(CTest)

enable_testing()

include(Catch)

catch_discover_tests(NchabiChickensTests)