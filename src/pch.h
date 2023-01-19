#ifndef SOC_PCH_H
#define SOC_PCH_H

#include <sqlite3.h>

#ifdef _WIN32
#include <Windows.h>
// Windows.h has a macro called 'max' so you need to undefine it: #undef max after you included it
// https://cplusplus.com/forum/beginner/15186/
#undef max
#endif

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


#endif // SOC_PCH_H
