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
# Включаем флаги для покрытия кода
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")

# Указываем директорию для отчетов
set(COVERAGE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/coverage)

# Флаги покрытия для компиляции и линковки
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")


# Добавляем пользовательскую цель для покрытия кода
add_custom_target(coverage
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND lcov --directory . --capture --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' '*/test/*' --output-file coverage.info.cleaned
    COMMAND genhtml coverage.info.cleaned --output-directory ${COVERAGE_OUTPUT_DIRECTORY}
    COMMAND echo "Coverage report generated in ${COVERAGE_OUTPUT_DIRECTORY}/index.html"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
# Директория для сохранения отчётов
set(COVERAGE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/coverage)

# Добавление пользовательской цели
add_custom_target(coverage
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND lcov --directory . --capture --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' '*/tests/*' --output-file coverage.cleaned.info
    COMMAND genhtml coverage.cleaned.info --output-directory ${COVERAGE_OUTPUT_DIRECTORY}
    COMMAND echo "Coverage report generated in ${COVERAGE_OUTPUT_DIRECTORY}/index.html"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)



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

add_executable(run_tests_LinkedList
    tests/test_LinkedList.cpp
    src/ForwardList.h
)
target_link_libraries(run_tests_LinkedList GTest::GTest GTest::Main)

# Добавьте аналогичные секции для других тестов...