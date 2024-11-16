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

int main(void) {
	std::string hex1 = "2DA89756425412F";
	std::string hex2 = "289756425412";
   	Fenyx::Types::allpnum n1;
    bool err = false;
    n1.emplace<1>(9);

    std::cout << "Test CompleteNbr() => " << std::endl;
    if (Fenyx::Types::CompleteNbr(n1) != "09") std::cout << "KO" <<std::endl;
    else                                       std::cout << "OK" <<std::endl;

	std::cout << "Test IsNum() => " << std::endl;
	if (!Fenyx::Types::IsNum(hex2.c_str()[2])) std::cout << "KO" <<std::endl;
	else                                       std::cout << "OK" <<std::endl;

	std::cout << "Test IsHex() => " << std::endl;
	if (!Fenyx::Types::IsHex(hex1.c_str()[2])) std::cout << "KO" <<std::endl;
	else                                       std::cout << "OK" <<std::endl;

	std::cout << "Test IsNumS() => " << std::endl;
	if (!Fenyx::Types::IsNumS(hex2)) std::cout << "KO" <<std::endl;
	else                             std::cout << "OK" <<std::endl;

	std::cout << "Test IsHexS() => " << std::endl;
	if (!Fenyx::Types::IsHexS(hex1)) std::cout << "KO" <<std::endl;
	else                             std::cout << "OK" <<std::endl;

	std::cout << "Test HexN() => " << std::endl;
	if (Fenyx::Types::BYTE t = Fenyx::Types::HexN(hex1.c_str()[2], err); t != 11 || err) std::cout << "KO" <<std::endl;
	else                                                                                 std::cout << "OK" <<std::endl;

    return 0;
}

