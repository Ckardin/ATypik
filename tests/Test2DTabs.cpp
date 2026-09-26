/// English version
/*
Copyright (C) 2026 BOUCARD NICOLLE Jody

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
Copyright (C) 2026 BOUCARD NICOLLE Jody

Ce fichier fait partie de ATypik.

ATypik est une bibliothèque libre; vous pouvez le redistribuer ou le modifier suivant les termes de la GNU General
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
/// @brief Source de Test2DTabs
/// @author F&nµx
/// @version 1.0
/// @date 26/09/2026

#include "../src/StrUtils.h"
#include "../src/Tabs2D.h"
#include <iostream>

int main() {
	Fenyx::Types::STable2D<Fenyx::Types::WORD, 7, 13> s1;
	Fenyx::Types::DSTable<Fenyx::Types::WORD, 13> d1;
	// ReSharper disable once CppJoinDeclarationAndAssignment
	Fenyx::Types::WORD exp;

	for (Fenyx::Types::BYTE i = 0; i < 7; i = i + 1) {
		for (Fenyx::Types::BYTE j = 0; j < 13; j = j + 1) {
			s1[{i, j}] = i * 100 + j;
			d1[{i, j}] = i * 100 + j;
		}
	}

	if (s1[{2, 7}] != 207 || d1[{2, 7}] != 207) {
		std::cout << "Test Tabs2D => KO (Index access)" << std::endl;
		return -6;
	}

	for (Fenyx::Types::BYTE i = 0; i < 7; i = i + 1) {
		for (Fenyx::Types::BYTE j = 0; j < 13; j = j + 1) {
			exp = i * 100 + j;

			if (s1[{i, j}] != exp || d1[{i, j}] != exp) {
				std::cout << "Test Tabs2D => KO (Data verify)(" << +i << ":" << +j << ")" << std::endl;
				return -7;
			}
		}
	}

	s1[{1, 2}] = 12345;
	d1[{1, 2}] = 12345;

	if (s1[{1, 2}] != 12345 ||
		d1[{1, 2}] != 12345 ||
		s1[{1, 3}] == 12345 ||
		s1[{2, 1}] == 12345 ||
		d1[{1, 3}] == 12345 ||
		d1[{2, 1}] == 12345) {

		std::cout << "Test Tabs2D => KO (Index isolation)" << std::endl;
		return -8;
	}

	if (s1.GetSize() != d1.GetSize()) {
		std::cout << "Test Tabs2D => KO (Size verify)" << std::endl;
		return -9;
	}

	for (Fenyx::Types::BYTE i = 0; i < 50; i = i + 1) {
		for (Fenyx::Types::BYTE j = 0; j < 13; j = j + 1) {
			d1[{i, j}] = i * 100 + j;
		}
	}

	for (Fenyx::Types::BYTE i = 0; i < 50; i = i + 1) {
		for (Fenyx::Types::BYTE j = 0; j < 13; j = j + 1) {
			exp = i * 100 + j;

			if (d1[{i, j}] != exp) {
				std::cout << "Test Tabs2D => KO (Resize preservation)" << std::endl;
				return -10;
			}
		}
	}

	std::cout << "Test Tabs2D   => OK (Align: " << +d1.GetAlign() << ")" <<std::endl;

	return 0;
}

