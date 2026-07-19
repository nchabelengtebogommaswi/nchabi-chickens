cmake_minimum_required(VERSION 3.20)

project(NchabiChickens)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Place all executables inside ./bin
#
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_package(PostgreSQL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(nlohmann_json REQUIRED)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)

find_library(
        CPP_HTTPLIB_LIBRARY
        cpp-httplib
        REQUIRED
)

add_executable(
        NchabiChickens
        src/main.cpp
        src/database/DatabaseConnection.cpp
        include/models/SalesOrderItem.h
        include/models/EggProduction.h
        include/models/Chicken.h
        include/models/Customer.h
        include/models/Product.h
        include/models/Inventory.h
        include/models/SalesOrder.h
        include/models/Delivery.h
)

target_include_directories(
        NchabiChickens
        PRIVATE
        include
        ${PostgreSQL_INCLUDE_DIRS}
        ${SQLITE3_INCLUDE_DIRS}
)

target_link_libraries(
        NchabiChickens
        PRIVATE
        nlohmann_json::nlohmann_json
        ${PostgreSQL_LIBRARIES}
        ${SQLITE3_LIBRARIES}
        ${CPP_HTTPLIB_LIBRARY}
)