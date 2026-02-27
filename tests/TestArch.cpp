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

/// @file TestArch.cpp
/// @brief Source de TestArch
/// @author F&nµx
/// @version 1.0
/// @date 30/01/2026

#include <iostream>
#include "../src/ll_Wrp.h"

int main () {
	Fenyx::Types::WORD comp = 0;

	std::cout << "CPUArch: ";
	if (Fenyx::Types::CPU::c_x86) {
		std::cout << "x86_64" <<std::endl;
		std::cout << "Support: ";
		comp += 5;

		if (Fenyx::Types::CPU::s_adx) {
			std::cout << "ADX "; comp += 10;
		}

		if (Fenyx::Types::CPU::s_lzcnt) {
			std::cout << "LZCNT "; comp += 5;
		}

		if (Fenyx::Types::CPU::s_bmi1) {
			std::cout << "BMI1 "; comp += 5;
		}

		if (Fenyx::Types::CPU::s_bmi2) std::cout << "BMI2 ";

		if (Fenyx::Types::CPU::s_sse2) {
			std::cout << "SSE2 "; comp += 60;
		}

		if (Fenyx::Types::CPU::s_avx2) {
			std::cout << "AVX2 "; comp += 15;
		}
	} else if (Fenyx::Types::CPU::c_arm) {
		std::cout << "AArch64" <<std::endl;
		std::cout << "Support: NEON";
		comp += 100;
	} else {
		std::cout << "Other" <<std::endl;
		std::cout << "Support: Unknown";
		comp += 5;
	}

	std::cout << "" <<std::endl;
	std::cout << "IntOpti: " << comp << "%" <<std::endl;

	return 0;
}

