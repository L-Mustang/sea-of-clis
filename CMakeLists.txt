cmake_minimum_required(VERSION 3.8)
project(sea-of-clis)


find_package(unofficial-sqlite3 REQUIRED)

add_executable(${PROJECT_NAME}
	"src/main.cpp"
	"src/ship.cpp"
	"src/harbor.cpp"
    "src/goods.cpp"
	"src/filesystem/sqlite_3.cpp"
	"src/player.cpp"
	"src/cannons_light.cpp"
	"src/cannons_medium.cpp"
	"src/cannons_heavy.cpp"
	"src/cannons.cpp"
	"src/cannons_small.cpp"
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_include_directories(${PROJECT_NAME} PRIVATE
	"src"
)

target_precompile_headers(${PROJECT_NAME} PRIVATE
	"src/pch.h"
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		unofficial::sqlite3::sqlite3
)

add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_CURRENT_SOURCE_DIR}/db/handelsschepen.db
		${CMAKE_CURRENT_BINARY_DIR}/db/handelsschepen.db
)