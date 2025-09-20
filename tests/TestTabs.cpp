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

/// @file TestTabs.cpp
/// @brief Source de TestTabs
/// @author F&nµx
/// @version 1.0
/// @date 16/11/2024

#include "../src/StrUtils.h"
#include <iostream>

int main() {
	Fenyx::Types::STable<Fenyx::Types::BYTE, 10> s1;
	Fenyx::Types::DTable<Fenyx::Types::BYTE> d1;
	Fenyx::Types::MTable<std::string, Fenyx::Types::BYTE> m1;

	if (s1.GetFatal() || d1.GetFatal() || m1.GetFatal()) {
		std::cout << "Test Tabs => KO (Memory limit)" <<std::endl;
		return -1;
	}

	for (Fenyx::Types::BYTE i = 0; i < 10; ++i) s1[i] = i;

	for (Fenyx::Types::BYTE i = 0; i < 10; ++i) {
		d1[i] = i;
		if (d1.GetFatal()) {
			std::cout << "Test Tabs => KO (Storage loop-num)" <<std::endl;
			return -2;
		}
	}

	for (Fenyx::Types::WORD i = 0; i < 10; ++i) {
		m1["v" + Fenyx::Types::toString<Fenyx::Types::WORD>(i)] = static_cast<Fenyx::Types::BYTE>(i);
		if (m1.GetFatal()) {
			std::cout << "Test Tabs => KO (Map idx-calc)" <<std::endl;
			return -3;
		}
	}

	if (s1[1] != 1 || d1[1] != 1 || m1["v1"] != 1) {
		std::cout << "Test Tabs => KO (Index access)" <<std::endl;
		return -4;
	}

	if (s1.GetSize() != d1.GetSize() || d1.GetSize() != m1.GetSize()) {
		std::cout << "Test Tabs => KO (Size verify)" <<std::endl;
		return -5;
	}

	std::cout << "Test Tabs => OK" <<std::endl;

	return 0;
}

