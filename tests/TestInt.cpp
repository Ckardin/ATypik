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

/// @file TestInt.cpp
/// @brief Source de TestInt
/// @author F&nµx
/// @version 1.0
/// @date 23/08/2025

#include <iostream>
#include "../src/Int.h"

int Test(const Fenyx::Types::Int &A, const Fenyx::Types::Int &B, const Fenyx::Types::Int &C, const Fenyx::Types::Int &E, int s, int d, int m, int q, int r, int sq);

int main() {
	Fenyx::Types::Int A(2000000000), B(50), C(20000), E(51);

	std::cout << "" <<std::endl;
	std::cout << "" <<std::endl;
	std::cout << "=== Test {Int} sur petites valeurs ===" <<std::endl;
	std::cout << "" <<std::endl;

	Fenyx::Types::sDWORD ret = Test(A, B, C, E, 2000000050, 1999999950, 1000000, 40000000, 14, 7);
	if (ret != 0) return ret;

	B = Fenyx::Types::Int(-50); E = Fenyx::Types::Int(-51);
	ret = Test(A, B, C, E, 1999999950, 2000000050, -1000000, -40000000, 14, 7);
	if (ret != 0) return ret;

	A = Fenyx::Types::Int(-2000000000); B = Fenyx::Types::Int(50); C = Fenyx::Types::Int(-20000); E = Fenyx::Types::Int(51);
	ret = Test(A, B, C, E, -1999999950, -2000000050, -1000000, -40000000, -14, 7);
	if (ret != 0) return ret;

	B = Fenyx::Types::Int(-50); E = Fenyx::Types::Int(-51);
	ret = Test(A, B, C, E, -2000000050, -1999999950, 1000000, 40000000, -14, 7);
	if (ret != 0) return ret;

	std::cout << "Test Int => OK" <<std::endl;

	return 0;
}

Fenyx::Types::sDWORD Test(const Fenyx::Types::Int &A, const Fenyx::Types::Int &B, const Fenyx::Types::Int &C, const Fenyx::Types::Int &E, const int s, const int d, const int m, const int q, const int r, const int sq) {
	const Fenyx::Types::Int S = A + B;
	const Fenyx::Types::Int D = A - B;
	const Fenyx::Types::Int M = C * B;
	const Fenyx::Types::Int Q = A / B;
	const Fenyx::Types::Int R = A % E;
	const Fenyx::Types::Int Sq = Fenyx::Types::Int::Sqrt(B);

	if (S != Fenyx::Types::Int(s)) {
		std::cout << "Test Add => KO (" << S.GetStr() << ")" << std::endl;
		return -1;
	}

	if (D != Fenyx::Types::Int(d)) {
		std::cout << "Test Sub => KO (" << D.GetStr() << ")" << std::endl;
		return -2;
	}

	if (M != Fenyx::Types::Int(m)) {
		std::cout << "Test Mul => KO (" << M.GetStr() << ")" << std::endl;
		return -3;
	}

	if (Q != Fenyx::Types::Int(q)) {
		std::cout << "Test Div => KO (" << Q.GetStr() << ")" << std::endl;
		return -4;
	}

	if (R != Fenyx::Types::Int(r)) {
		std::cout << "Test Mod => KO (" << R.GetStr() << ")" << std::endl;
		return -5;
	}

	if (Sq != Fenyx::Types::Int(sq)) {
		std::cout << "Test Sqt => KO (" << Sq.GetStr() << ")" << std::endl;
		return -6;
	}

	return 0;
}

