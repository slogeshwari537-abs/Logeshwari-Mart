
cmake_minimum_required(VERSION 3.25)

project(LogeshwariMart)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Drogon CONFIG REQUIRED)
find_package(unofficial-sodium CONFIG REQUIRED)

add_executable(LogeshwariMart

    src/main.cpp

    src/service/AuthService.cpp
    src/service/ChatbotService.cpp

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
)

target_include_directories(LogeshwariMart PRIVATE
    src
)

target_link_libraries(LogeshwariMart PRIVATE
    Drogon::Drogon
    unofficial-sodium::sodium
)