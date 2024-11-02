/*
---------------------------------------------
|    ____                                   |
|   /\  _`\                                 |
|   \ \ \L\_\ __    ___   __  __   __  _    |
|    \ \  _\/'__`\/' _ `\/\ \/\ \ /\ \/'\   |
|     \ \ \/\  __//\ \/\ \ \ \_\ \\/>  </   |
|      \ \_\ \____\ \_\ \_\/`____ \/\_/\_\  |
|       \/_/\/____/\/_/\/_/`/___/> \//\/_/  |
|                             /\___/        |
|                             \/__/         |
|                                           |
---------------------------------------------
*/

/// @file Utils.h
/// @brief Header de Utils
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <chrono>
#include "Defines.h"

namespace Fenyx::Types
{

DWORD GetTimestamp();
QWORD GetTimestampMilli();

char toChar(BYTE a);
BYTE toAscii(char c);

DWORD MicroChaoCrypt(DWORD orand);

}

#endif //UTILS_H
