cmake_minimum_required(VERSION 3.20)

project(cpp_printer
    VERSION 1.0.0
    DESCRIPTION "A lightweight C++ STL container printer"
    LANGUAGES CXX
)

include(CTest)

# --------------------------------------------------
# C++ standard
# --------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)


# --------------------------------------------------
# Library
# --------------------------------------------------

add_library(cpp_printer_library INTERFACE)

target_include_directories(cpp_printer_library
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_library(cpp_printer::cpp_printer ALIAS cpp_printer_library)


# --------------------------------------------------
# CLI
# --------------------------------------------------

add_executable(cpp_printer
    cli/main.cpp
    src/executable_path.cpp
)

target_link_libraries(cpp_printer
    PRIVATE
        cpp_printer::cpp_printer
)

set_target_properties(cpp_printer
    PROPERTIES
        OUTPUT_NAME cpp_printer
)

# --------------------------------------------------
# Tests
# --------------------------------------------------

if(BUILD_TESTING)
    add_executable(cpp_printer_tests
        tests/test_printers.cpp
    )

    target_link_libraries(cpp_printer_tests
        PRIVATE
            cpp_printer::cpp_printer
    )

    add_test(
        NAME cpp_printer_tests
        COMMAND cpp_printer_tests
    )
endif()


# --------------------------------------------------
# Installation
# --------------------------------------------------

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    TARGETS cpp_printer
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    RENAME cpp_printer
)

install(
    TARGETS cpp_printer_library
    EXPORT cpp_printerTargets
)

install(
    EXPORT cpp_printerTargets
    FILE cpp_printerTargets.cmake
    NAMESPACE cpp_printer::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cpp_printer
)

install(
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/docs/CPP_PRINTER.md
    DESTINATION
        ${CMAKE_INSTALL_DATADIR}/cpp_printer
)


# --------------------------------------------------
# Package configuration
# --------------------------------------------------

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpp_printerConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cpp_printerConfig.cmake
    INSTALL_DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/cpp_printer
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/cpp_printerConfig.cmake
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/cpp_printer
)