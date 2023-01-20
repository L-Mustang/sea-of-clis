cmake_minimum_required(VERSION 3.8)
project(sea-of-clis)

# Delete the CMake cache after changing this option for it to have effect
option(USE_WIN32 "Use the Win32 API for platform-specific console clearing" ON)

find_package(unofficial-sqlite3 REQUIRED)

add_executable(${PROJECT_NAME}
	"${CMAKE_CURRENT_SOURCE_DIR}/icon.rc"
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

if(WIN32 AND USE_WIN32)
message("Building with Win32 support")
target_compile_definitions(${PROJECT_NAME} PRIVATE
	# Prevents Windows.h from adding unnecessary includes    
	WIN32_LEAN_AND_MEAN
	# Prevents Windows.h from defining min/max as macros 
	NOMINMAX
	# Include Windows.h
	USE_WIN32
)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "sea_of_clis")

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