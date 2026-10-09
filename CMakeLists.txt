cmake_minimum_required(VERSION 3.25)

project(LogeshwariMart)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================
# Dependencies
# =========================

find_package(Drogon CONFIG REQUIRED)
find_package(unofficial-sodium CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# =========================
# Main Application
# =========================

add_executable(LogeshwariMart

    src/main.cpp
    src/MigrationRunner.cpp

    src/service/AuthService.cpp
    src/service/ChatbotService.cpp
    src/service/MockAIProvider.cpp
    src/service/AIProviderFactory.cpp
    src/service/GeminiAIProvider.cpp

    src/repository/UserRepository.cpp
    src/repository/ProductRepository.cpp
    src/repository/CartRepository.cpp
    src/repository/OrderRepository.cpp
    src/repository/AdminRepository.cpp
    src/repository/ReviewRepository.cpp

    src/controller/AuthController.cpp
    src/controller/ProductController.cpp
    src/controller/CartController.cpp
    src/controller/OrderController.cpp
    src/controller/AdminController.cpp
    src/controller/ReviewController.cpp
    src/controller/ChatbotController.cpp
    src/controller/HealthController.cpp

    # Authentication filter
    src/filter/AuthFilter.cpp
)

target_include_directories(LogeshwariMart PRIVATE
    src
)

target_link_libraries(LogeshwariMart PRIVATE
    Drogon::Drogon
    unofficial-sodium::sodium
    spdlog::spdlog
)

# =========================
# GoogleTest
# =========================

enable_testing()

add_executable(LogeshwariMartTests
    test/AuthTest.cpp
)

target_link_libraries(LogeshwariMartTests PRIVATE
    GTest::gtest
    GTest::gtest_main
)

add_test(
    NAME AuthTest
    COMMAND LogeshwariMartTests
)

# =========================
# Password Hash Generator
# =========================

add_executable(GenerateHash
    src/generate_hash.cpp
)

target_link_libraries(GenerateHash PRIVATE
    unofficial-sodium::sodium
)

# =========================
# Static Analysis - clang-tidy
# =========================

find_program(CLANG_TIDY_EXE
    NAMES clang-tidy
)
message(STATUS "CLANG_TIDY_EXE=${CLANG_TIDY_EXE}")

if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()
# =========================
# Static Analysis - Cppcheck
# =========================

find_program(CPPCHECK_EXE
    NAMES cppcheck
)

if(CPPCHECK_EXE)
    add_custom_target(cppcheck
        COMMAND ${CPPCHECK_EXE}
            --enable=warning,style,performance,portability
            --inline-suppr
            --suppress=missingIncludeSystem
            --suppress=throwInEntryPoint
            --language=c++
            --std=c++20
            -I ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/src
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running Cppcheck static analysis"
    )
endif()
# =========================
# Explicit clang-tidy target
# =========================

if(CLANG_TIDY_EXE)
    add_custom_target(clang-tidy
        COMMAND "${CLANG_TIDY_EXE}"
            -p "${CMAKE_BINARY_DIR}"
            "${CMAKE_SOURCE_DIR}/src/main.cpp"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        COMMENT "Running clang-tidy static analysis"
    )
endif()
# Enable C++ exception handling for MSVC
target_compile_options(LogeshwariMart PRIVATE /EHsc)

if(MSVC)
    target_compile_options(LogeshwariMart PRIVATE /EHsc)
    target_compile_definitions(LogeshwariMart PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
