cmake_minimum_required(VERSION 3.10)
project(print LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(keyring CONFIG REQUIRED)
message("keyring: ${keyring}")
include_directories(${keyring})

INCLUDE_DIRECTORIES(thirdparty)

add_executable(${PROJECT_NAME} src/main.cc)
target_link_libraries(${PROJECT_NAME} keyring::keyring)

add_custom_target(run
    COMMAND print
    DEPENDS print
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
