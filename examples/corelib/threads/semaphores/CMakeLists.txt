# Generated from semaphores.pro.

cmake_minimum_required(VERSION 3.14)
project(semaphores LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(INSTALL_EXAMPLEDIR "examples/corelib/threads/semaphores")

find_package(Qt6 COMPONENTS Core)

add_executable(semaphores
    semaphores.cpp
)
target_link_libraries(semaphores PUBLIC
    Qt::Core
)

install(TARGETS semaphores
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
