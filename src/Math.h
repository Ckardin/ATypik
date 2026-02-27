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

/// @file Math.h
/// @brief Header de Math
/// @author F&nµx
/// @version 3.0
/// @date 08/01/2025

#ifndef ALGOMATH_H
#define ALGOMATH_H

#include <regex>
#include "Int.h"

namespace Fenyx::Types
{

Int NaivePow    (const Int &a, DWORD b);
Int Pow         (const Int &x, const Int &n);
Int Pow2        (DWORD n);
Int Pow16       (DWORD n);
Int PowM        (const Int &a, const Int &b, const Int &m, const Int &mu);
Int ExtEuclide  (const Int &a, const Int &b, Int &u, Int &v);
Int Stein       (const Int &a, const Int &b);
DWORD SquareRt(DWORD n);


/// @brief Complex - Classe qui permet de gérer les nombres complexes
class Complex {
public:
	Complex();
	Complex(const Int &r, const Int &u);
	Complex(const Complex &oth);

	[[nodiscard]] bool IsReal() const;
	[[nodiscard]] bool IsImag() const;
	[[nodiscard]] Int Real() const;
	[[nodiscard]] Int Imag() const;

	Complex& operator=(const Complex &oth);
	Complex& operator+=(const Complex &oth);
	Complex& operator-=(const Complex &oth);
	Complex& operator*=(const Complex &oth);
	Complex& operator/=(const Complex &oth);

private:
	Int re;
	Int im;

	friend Complex operator+(const Complex &lhs, const Complex &rhs);
	friend Complex operator-(const Complex &lhs, const Complex &rhs);
	friend Complex operator*(const Complex &lhs, const Complex &rhs);
	friend Complex operator/(const Complex &lhs, const Complex &rhs);

	friend bool operator==(const Complex &lhs, const Complex &rhs);
	friend bool operator!=(const Complex &lhs, const Complex &rhs);

	friend std::ostream& operator<<(std::ostream& os, const Complex &rhs);
};

}

#endif //ALGOMATH_H
