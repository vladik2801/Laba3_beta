cmake_minimum_required(VERSION 3.10)
project(labwork_3_sorokin)

set(CMAKE_CXX_STANDARD 17)

# Указываем директорию с заголовочными файлами
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Создаем библиотеку для работы с песчаными ямами
add_library(sandpile src/sandpile.cpp)

# Создаем библиотеку для работы с BMP
add_library(create_bmp src/create_bmp.cpp)

# Создаем библиотеку для парсинга
add_library(parsing src/parsing.cpp)


# Создаем исполняемый файл
add_executable(main src/main.cpp)

# Связываем исполняемый файл с библиотеками
target_link_libraries(main PRIVATE sandpile create_bmp parsing)

