#ifndef SOC_PCH_H
#define SOC_PCH_H

#if defined USE_LIBS && defined _WIN32
	#define WIN32_LEAN_AND_MEAN // prevents windows.h from adding unnecessary includes
	#define NOMINMAX // prevents windows.h from defining min/max as macros
	#include <Windows.h>
	#ifdef USE_CRT
		#define _CRTDBG_MAP_ALLOC
		#include <stdlib.h>
		#include <crtdbg.h>
		#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) // Very dodgy, could lead to undefined behaviour
	#endif // USE_CRT
#endif // defined USE_LIBS && defined _WIN32

#include <sqlite3.h>

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include <map>
#include <set>
#include <functional>
#include <algorithm>


#endif // SOC_PCH_H
