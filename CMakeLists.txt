cmake_minimum_required(VERSION 3.20)

project(cpp_printer
    VERSION 1.0.4
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

option(CPP_PRINTER_BUILD_CLI "Build and install the cpp_printer CLI" ON)
option(CPP_PRINTER_BUILD_EXAMPLES "Build example programs" ON)
option(CPP_PRINTER_BUILD_TESTS "Build test programs" ON)

# --------------------------------------------------
# Library
# --------------------------------------------------

add_library(cpp_printer_library INTERFACE)

set_target_properties(cpp_printer_library
    PROPERTIES
        EXPORT_NAME cpp_printer
)

target_include_directories(cpp_printer_library
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_library(cpp_printer::cpp_printer ALIAS cpp_printer_library)

# --------------------------------------------------
# CLI
# --------------------------------------------------

if(CPP_PRINTER_BUILD_CLI)
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
endif()

# --------------------------------------------------
# Examples
# --------------------------------------------------

if(CPP_PRINTER_BUILD_EXAMPLES)
    # Test cpp_printer (main original)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples/test_cpp_printer/main.cpp)
        add_executable(example_cpp_printer
            examples/test_cpp_printer/main.cpp
        )
        target_link_libraries(example_cpp_printer PRIVATE cpp_printer::cpp_printer)
    endif()

    # Tools examples
    add_executable(example_stats
        examples/test_tools/test_stats.cpp
    )
    target_link_libraries(example_stats PRIVATE cpp_printer::cpp_printer)
    
    add_executable(example_compare
        examples/test_tools/test_compare.cpp
    )
    target_link_libraries(example_compare PRIVATE cpp_printer::cpp_printer)
    
    add_executable(example_diff
        examples/test_tools/test_diff.cpp
    )
    target_link_libraries(example_diff PRIVATE cpp_printer::cpp_printer)
    
    add_executable(example_search
        examples/test_tools/test_search.cpp
    )
    target_link_libraries(example_search PRIVATE cpp_printer::cpp_printer)
    
    # Views examples
    add_executable(example_ascii
        examples/test_views/test_ascii.cpp
    )
    target_link_libraries(example_ascii PRIVATE cpp_printer::cpp_printer)
    
    add_executable(example_table
        examples/test_views/test_table.cpp
    )
    target_link_libraries(example_table PRIVATE cpp_printer::cpp_printer)
    
    add_executable(example_tree
        examples/test_views/test_tree.cpp
    )
    target_link_libraries(example_tree PRIVATE cpp_printer::cpp_printer)
endif()

# --------------------------------------------------
# Tests
# --------------------------------------------------

if(CPP_PRINTER_BUILD_TESTS)
    enable_testing()
    
    # Helper para agregar tests
    function(add_cpp_printer_test NAME SOURCE)
        add_executable(${NAME} ${SOURCE})
        target_link_libraries(${NAME} PRIVATE cpp_printer::cpp_printer)
        add_test(NAME ${NAME} COMMAND ${NAME})
    endfunction()
    
    # Tools tests
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_tools/test_stats_advanced.cpp)
        add_cpp_printer_test(test_stats_advanced
            tests/test_tools/test_stats_advanced.cpp
        )
    endif()
    
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_tools/test_compare_advanced.cpp)
        add_cpp_printer_test(test_compare_advanced
            tests/test_tools/test_compare_advanced.cpp
        )
    endif()
    
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_tools/test_diff_advanced.cpp)
        add_cpp_printer_test(test_diff_advanced
            tests/test_tools/test_diff_advanced.cpp
        )
    endif()
    
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_tools/test_search_advanced.cpp)
        add_cpp_printer_test(test_search_advanced
            tests/test_tools/test_search_advanced.cpp
        )
    endif()
    
    # Views tests
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_views/test_ascii_advanced.cpp)
        add_cpp_printer_test(test_ascii_advanced
            tests/test_views/test_ascii_advanced.cpp
        )
    endif()
    
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_views/test_table_advanced.cpp)
        add_cpp_printer_test(test_table_advanced
            tests/test_views/test_table_advanced.cpp
        )
    endif()
    
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_views/test_tree_advanced.cpp)
        add_cpp_printer_test(test_tree_advanced
            tests/test_views/test_tree_advanced.cpp
        )
    endif()
    
    # Test original (mantener compatibilidad)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_printers.cpp)
        add_executable(cpp_printer_tests
            tests/test_printers.cpp
        )
        target_link_libraries(cpp_printer_tests PRIVATE cpp_printer::cpp_printer)
        add_test(NAME cpp_printer_tests COMMAND cpp_printer_tests)
    endif()
endif()

# --------------------------------------------------
# Installation
# --------------------------------------------------

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

if(CPP_PRINTER_BUILD_CLI)
    install(
        TARGETS cpp_printer
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        RENAME cpp_printer
    )
endif()

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
        ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE
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

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/cpp_printerConfigVersion.cmake
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/cpp_printerConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cpp_printerConfigVersion.cmake
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/cpp_printer
)

# --------------------------------------------------
# Información de compilación
# --------------------------------------------------

message(STATUS "cpp_printer version: ${PROJECT_VERSION}")
message(STATUS "Build CLI: ${CPP_PRINTER_BUILD_CLI}")
message(STATUS "Build Examples: ${CPP_PRINTER_BUILD_EXAMPLES}")
message(STATUS "Build Tests: ${CPP_PRINTER_BUILD_TESTS}")

if(CPP_PRINTER_BUILD_TESTS)
    message(STATUS "Tests enabled. Run 'ctest' to execute all tests.")
endif()

# --------------------------------------------------
# Targets personalizados
# --------------------------------------------------

# Target para ejecutar todos los ejemplos
add_custom_target(run_examples
    COMMAND echo "Running examples..."
    COMMAND $<TARGET_FILE:example_cpp_printer>
    COMMAND $<TARGET_FILE:example_stats>
    COMMAND $<TARGET_FILE:example_compare>
    COMMAND $<TARGET_FILE:example_diff>
    COMMAND $<TARGET_FILE:example_search>
    COMMAND $<TARGET_FILE:example_ascii>
    COMMAND $<TARGET_FILE:example_table>
    COMMAND $<TARGET_FILE:example_tree>
    DEPENDS 
        example_cpp_printer
        example_stats
        example_compare
        example_diff
        example_search
        example_ascii
        example_table
        example_tree
)

# Target para ejecutar todos los tests
if(CPP_PRINTER_BUILD_TESTS)
    add_custom_target(run_tests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -V
        DEPENDS 
            test_stats_advanced
            test_compare_advanced
            test_diff_advanced
            test_search_advanced
            test_ascii_advanced
            test_table_advanced
            test_tree_advanced
            cpp_printer_tests
    )
endif()
