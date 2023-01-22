cmake_minimum_required(VERSION 3.8)
project(sea-of-clis)

# delete the cmake cache after changing these options for it to have effect
option(USE_LIBS "Use the Win32 API, C Run-time, Clang AddressSanitizer for platform-specific console clearing and debugging features" ON)
option(USE_CRT "Use the C Run-time library for memory leak detection" OFF)
option(USE_ASAN "Use AddressSanitizer" OFF)

find_package(unofficial-sqlite3 REQUIRED)

add_executable(${PROJECT_NAME}
	"${CMAKE_CURRENT_SOURCE_DIR}/icon.rc"
	"src/main.cpp"
	"src/ship.cpp"
	"src/harbor.cpp"
    "src/goods.cpp"
	"src/filesystem/sqlite_3.cpp"
	"src/game.cpp"
	"src/cannons_light.cpp"
	"src/cannons_medium.cpp"
	"src/cannons_heavy.cpp"
	"src/cannons.cpp"
	"src/cannons_small.cpp"
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

if(USE_LIBS)
	message("Building with lib support")
	target_compile_definitions(${PROJECT_NAME} PRIVATE
		USE_LIBS # include Windows.h
	)

	if(USE_ASAN)
		message("Building with AdressSanitizer support")
		if(MSVC)
			target_compile_options(${PROJECT_NAME} PUBLIC /fsanitize=address)
		else() # ^^^ msvc / other vvv
			target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
			target_link_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
		endif() # MSVC
	endif() # USE ASAN
	if(USE_CRT)
		message("Building with CRT support for memory leak detection")
		target_compile_definitions(${PROJECT_NAME} PRIVATE
			USE_CRT
		)
	endif() # USE_CRT
endif() # USE_LIBS



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