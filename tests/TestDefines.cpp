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

/// @file TestDefines.cpp
/// @brief Source de TestDefines
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#include "../src/Defines.h"
#include <iostream>
#include <sstream>

int main(void) {
 	Fenyx::Types::TriBool trb;
    Fenyx::Types::TriBool trb2(false, false);
    Fenyx::Types::TriBool trb3(trb2);

    if (trb2 != trb3) {
      	std::cout << "Test TriBool => KO (equality verify)" << std::endl;
        return -1;
   	}
    if (trb2.GetValue() != false) {
      	std::cout << "Test TriBool => KO (value verify)" << std::endl;
        return -2;
    }

	std::string s_trb, s_trb2, s_trb3;
	std::ostringstream oss0, oss1, oss2;

	oss0 << trb;
	s_trb = oss0.str();

	oss1 << trb2;
	s_trb2 = oss1.str();

	oss2 << trb3;
	s_trb3 = oss2.str();

    if (s_trb != "U" || s_trb2 != "F" || s_trb3 != "F") {
	    std::cout << "Test TriBool => KO (String converting)" << std::endl;
    	return -3;
    }

    std::cout << "Test TriBool => OK" << std::endl;

    return 0;
}

