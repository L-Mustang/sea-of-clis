cmake_minimum_required(VERSION 3.8)
project (sea-of-clis)


find_package(unofficial-sqlite3 REQUIRED)

add_executable(${PROJECT_NAME}
src/main.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    unofficial::sqlite3::sqlite3
)
