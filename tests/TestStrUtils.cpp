/// English version
/*
Copyright (C) 2025 BOUCARD NICOLLE Jody

This file is part of ATypik.

ATypik is free library: you can redistribute it and/or modify it under the terms of the GNU General
Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

ATypik is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License along with ATypik. If not, see
<https://www.gnu.org/licenses/>.
*/

/// Version française
/*
Copyright (C) 2025 BOUCARD NICOLLE Jody

Ce fichier fait partie de ATypik.

ATypik est une bilbiothèque libre; vous pouvez le redistribuer ou le modifier suivant les termes de la GNU General
Public License telle que publiée par la Free Software Foundation, soit la version 3 de la licence, soit (à votre
gré) toute version ultérieure.

ATypik est distribué dans l'espoir qu'il sera utile, mais SANS AUCUNE GARANTIE; sans même la
garantie tacite de QUALITÉ MARCHANDE ou d'ADÉQUATION À UN BUT PARTICULIER. Consultez la GNU
General Public License pour plus de détails.

Vous devez avoir reçu une copie de la GNU General Public License en même temps que ATypik. Si ce n'est pas le cas, consultez
<http://www.gnu.org/licenses>.
*/

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

    // std::cout << "Test CompleteNbr() => ";
    if (Fenyx::Types::CompleteNbr(n1) != "09") {
      	std::cout << "Test StrUtils => KO (CompleteNbr)" <<std::endl;
        return -1;
    }
    // else                                       std::cout << "OK" <<std::endl;

	// std::cout << "Test IsNum() => ";
	if (!Fenyx::Types::IsNum(hex2.c_str()[2])) {
        std::cout << "Test StrUtils => KO (Num verify)" <<std::endl;
        return -2;
    }
	// else                                       std::cout << "OK" <<std::endl;

	// std::cout << "Test IsHex() => ";
	if (!Fenyx::Types::IsHex(hex1.c_str()[2])) {
        std::cout << "Test StrUtils => KO (Hex verify)" <<std::endl;
        return -3;
    }
	// else                                       std::cout << "OK" <<std::endl;

	// std::cout << "Test IsNumS() => ";
	if (!Fenyx::Types::IsNumS(hex2)) {
        std::cout << "Test StrUtils => KO (Num string verify)" <<std::endl;
        return -4;
    }
	// else                             std::cout << "OK" <<std::endl;

	// std::cout << "Test IsHexS() => ";
	if (!Fenyx::Types::IsHexS(hex1)) {
        std::cout << "Test StrUtils => KO (Hex string verify)" <<std::endl;
        return -5;
    }
	// else                             std::cout << "OK" <<std::endl;

	// std::cout << "Test HexN() => ";
	if (const Fenyx::Types::BYTE t = Fenyx::Types::HexN(hex1.c_str()[2], err); t != 10 || err){
        std::cout << "Test StrUtils => KO (Hex converting)" <<std::endl;
        return -6;
    }
	// else                             std::cout << "OK" <<std::endl;

    std::cout << "Test StrUtils => OK" <<std::endl;

    return 0;
}

