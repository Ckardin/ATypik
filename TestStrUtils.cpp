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

/// @file TestStrUtils.cpp
/// @brief Source de TestUtils
/// @author F&nµx
/// @version 1.0
/// @date 16/11/2024

#include "StrUtils.h"
#include <iostream>

int main() {
	const std::string hex1 = "2DA89756425412F";
	const std::string hex2 = "2897564254012";
   	Fenyx::Types::allpnum n1;
    bool err = false;
    n1.emplace<2>(9);

    std::cout << "Test CompleteNbr() => ";
    if (Fenyx::Types::CompleteNbr(n1) != "09") std::cout << "KO" <<std::endl;
    else                                       std::cout << "OK" <<std::endl;

	std::cout << "Test IsNum() => ";
	if (!Fenyx::Types::IsNum(hex2.c_str()[2])) std::cout << "KO" <<std::endl;
	else                                       std::cout << "OK" <<std::endl;

	std::cout << "Test IsHex() => ";
	if (!Fenyx::Types::IsHex(hex1.c_str()[2])) std::cout << "KO" <<std::endl;
	else                                       std::cout << "OK" <<std::endl;

	std::cout << "Test IsNumS() => ";
	if (!Fenyx::Types::IsNumS(hex2)) std::cout << "KO" <<std::endl;
	else                             std::cout << "OK" <<std::endl;

	std::cout << "Test IsHexS() => ";
	if (!Fenyx::Types::IsHexS(hex1)) std::cout << "KO" <<std::endl;
	else                             std::cout << "OK" <<std::endl;

	std::cout << "Test HexN() => ";
	if (const Fenyx::Types::BYTE t = Fenyx::Types::HexN(hex1.c_str()[2], err); t != 10 || err) std::cout << "KO" <<std::endl;
	else                                                                                          std::cout << "OK" <<std::endl;

    return 0;
}

