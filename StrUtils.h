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

/// @file StrUtils.h
/// @brief Header de StrUtils
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#ifndef STRUTILS_H
#define STRUTILS_H

#include <sstream>
#include "Tabs.h"

namespace Fenyx::Types
{

extern const STable<char, 16> HexConv;

std::ostream& operator<<(std::ostream& os, SWORD const& v);
std::ostream& operator<<(std::ostream& os, sSWORD const& v);

std::istream& operator>>(std::istream& is, SWORD& v);
std::istream& operator>>(std::istream& is, sSWORD& v);

template<class T>
std::string toString(T const& t);
template<class T>
std::string toHexString(T const& t);
template<class T>
T fromString(std::string const& s);

std::string CompleteNbr(allpnum nbr);

bool IsNum(char c);
bool IsHex(char c);
bool IsNumS(std::string const& str);
bool IsHexS(std::string const& str);
DWORD HexN(char c, bool &err);
std::string DecTHex(std::string str, bool &err);
std::string DecFHex(std::string const& str, bool &err);



template<class T>
std::string toString(T const& t) {
	std::ostringstream oss;
	oss << t;

	return oss.str();
}

template<class T>
std::string toHexString(T const& t) {
	std::ostringstream oss;
	oss << std::hex << t;

	return oss.str();
}

template<class T>
T fromString(std::string const& s) {
	T ret;
	std::istringstream iss(s);

	iss >> ret;
	return ret;
}

}

#endif //STRUTILS_H
