# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(MyProject)

# Указываем директорию с исходниками
include_directories(src)

# Google Test
find_package(GTest REQUIRED)

# Установим, чтобы все тесты сохранялись в папке build/tests/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

# Тесты для MyClass1
add_executable(run_tests_DynamicArray
    tests/test_DynamicArray.cpp
    src/DynamicArray.h
)
target_link_libraries(run_tests_DynamicArray GTest::GTest GTest::Main)

add_executable(run_tests_ForwardList
    tests/test_ForwardList.cpp
    src/ForwardList.h
)
target_link_libraries(run_tests_ForwardList GTest::GTest GTest::Main)

# Добавьте аналогичные секции для других тестов...