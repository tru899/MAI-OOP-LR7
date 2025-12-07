cmake_minimum_required(VERSION 3.14)
project(laba7_proj
    VERSION 1.0.0
    LANGUAGES CXX
)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка директорий
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${INCLUDE_DIR})

# Поиск исходных файлов библиотеки
file(GLOB_RECURSE LIBRARY_SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)

# Создание библиотеки
add_library(laba7_proj_lib ${LIBRARY_SOURCES})

# Создание исполняемого файла
add_executable(laba7_proj_exe main.cpp)

# Связывание библиотеки с исполняемым файлом
target_link_libraries(laba7_proj_exe PRIVATE laba7_proj_lib)

# Настройка компилятора (опционально)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(laba7_proj_lib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(laba7_proj_exe PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавление тестов
enable_testing()

# Тестовый исполняемый файл
file(GLOB TEST_SOURCES test/*.cpp)
add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests
    PRIVATE
        laba7_proj_lib
        gtest
        gtest_main
)

# Добавление тестов в тестовый набор
add_test(NAME FiguresProjectTests COMMAND tests)
