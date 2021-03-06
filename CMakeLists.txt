# Build
cmake_minimum_required(VERSION 3.10)

project(keyring VERSION 0.0.1 LANGUAGES CXX)

include(GNUInstallDirs)

include(FindPkgConfig)

include_directories(thirdparty)
include_directories(include)

file(GLOB src_files src/*.cc)
add_library(${PROJECT_NAME} STATIC ${src_files})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

if(APPLE)
        FIND_LIBRARY(SECURITY Security)
        target_link_libraries(${PROJECT_NAME} PUBLIC ${SECURITY})
endif(APPLE)

if(UNIX AND NOT APPLE)
        set(LINUX TRUE)
endif()

if(LINUX)
        pkg_check_modules(LIBSECRET libsecret-1)
        message("libsecret: ${LIBSECRET_INCLUDE_DIRS}")
        target_include_directories(${PROJECT_NAME} PUBLIC ${LIBSECRET_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBSECRET_LIBRARIES})
endif()

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_executable(test src/test_main.cc)
target_link_libraries(test keyring)


# Install
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)

if(NOT INCLUDE_INSTALL_DIR)
  set(INCLUDE_INSTALL_DIR include/keyring)
endif()
set(LIBRARY_INSTALL_DIR lib)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
  PATH_VARS INCLUDE_INSTALL_DIR LIBRARY_INSTALL_DIR)

install(EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
