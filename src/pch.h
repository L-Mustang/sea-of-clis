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

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>


#endif // SOC_PCH_H
