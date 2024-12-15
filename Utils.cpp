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
/// @brief Source de Utils
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#include "Utils.h"

namespace Fenyx::Types
{

DWORD GetTimestamp() {
	using namespace std::chrono;

	return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}

QWORD GetTimestampMilli() {
	using namespace std::chrono;

	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

char toChar(BYTE a) {
	return static_cast<char>(a);
}

BYTE toAscii(char c) {
	return static_cast<BYTE>(c);
}

DWORD MicroChaoCrypt(const DWORD orand) {
	std::random_device rdev;

	const DWORD t1 = rdev();
	const DWORD t2 = rdev() % 32;

	allnum t;
	t.emplace<0>(0);
	BytesArray(t);

	return ((t1 << t2) ^ orand);
}

}

