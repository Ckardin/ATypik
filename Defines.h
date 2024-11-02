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

/// @file Defines.h
/// @brief Header de Defines
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#ifndef DEFINES_H
#define DEFINES_H

#include <optional>
#include <variant>

namespace Fenyx
{
namespace Types
{

typedef uint8_t      BYTE;
typedef uint16_t     WORD;
typedef uint32_t    DWORD;
typedef uint64_t    QWORD;
typedef __uint128_t SWORD;

typedef int8_t      sBYTE;
typedef int16_t     sWORD;
typedef int32_t    sDWORD;
typedef int64_t    sQWORD;
typedef __int128_t sSWORD;

using allpnum = std::variant<unsigned int, BYTE, WORD, DWORD, QWORD, SWORD>;
using allnum  = std::variant<unsigned int, BYTE, WORD, DWORD, QWORD, SWORD, int, sBYTE, sWORD, sDWORD, sQWORD, sSWORD>;

using barray = std::array<BYTE, 17>;


std::ostream& operator<<(std::ostream& os, SWORD const& v);
std::ostream& operator<<(std::ostream& os, sSWORD const& v);

std::istream& operator>>(std::istream& is, SWORD& v);
std::istream& operator>>(std::istream& is, sSWORD& v);

}
}

#endif //DEFINES_H
