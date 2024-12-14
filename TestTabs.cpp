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

/// @file TestTabs.cpp
/// @brief Source de TestTabs
/// @author F&nµx
/// @version 1.0
/// @date 16/11/2024

#include "StrUtils.h"
#include <iostream>

int main() {
	Fenyx::Types::STable<Fenyx::Types::BYTE, 10> s1(0);
	Fenyx::Types::DTable<Fenyx::Types::BYTE> d1(0);
	Fenyx::Types::MTable<std::string, Fenyx::Types::BYTE> m1("", 0);

	if (s1.GetFatal() || d1.GetFatal() || m1.GetFatal()) {
		std::cout << "Test KO." <<std::endl;
		return -1;
	}

	for (Fenyx::Types::BYTE i = 0; i < 10; ++i) s1[i] = i;

	for (Fenyx::Types::BYTE i = 0; i < 10; ++i) {
		d1[i] = i;
		if (d1.GetFatal()) {
			std::cout << "Test KO." <<std::endl;
			return -2;
		}
	}

	for (Fenyx::Types::WORD i = 0; i < 10; ++i) {
		m1["v" + Fenyx::Types::toString<Fenyx::Types::WORD>(i)] = static_cast<Fenyx::Types::BYTE>(i);
		if (m1.GetFatal()) {
			std::cout << "Test KO." <<std::endl;
			return -3;
		}
	}

	if (s1[1] != 1 || d1[1] != 1 || m1["v1"] != 1) {
		std::cout << "Test KO." <<std::endl;
		return -4;
	}

	if (s1.GetSize() != d1.GetSize() || d1.GetSize() != m1.GetSize()) {
		std::cout << "Test KO." <<std::endl;
		return -5;
	}

	std::cout << "Test OK." <<std::endl;

	return 0;
}

