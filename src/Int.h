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

/// @file Int.h
/// @brief Header de Int
/// @author F&nµx
/// @version 1.0
/// @date 22/08/2025

#ifndef INT_H
#define INT_H

#include <algorithm>
#include "Tabs.h"
#include "StrUtils.h"

namespace Fenyx::Types
{

inline constexpr QWORD b32 = (1ULL << 32);
inline constexpr DWORD bs109 = 1000000000;

DWORD NextPow2(DWORD n);

/// @brief Int - Classe qui permets la prise en charge de grands nombres entiers relatifs
class Int
{
public:
	Int();

	Int(int value);
	Int(const Int &other);
	Int(const DTable<DWORD> &other, bool sg);
	Int(DWORD value);
	Int(QWORD value);

	[[nodiscard]] DTable<DWORD> GetTab() const;
	[[nodiscard]] QWORD GetL64() const;
	[[nodiscard]] Int GetOpposite() const;
	[[nodiscard]] std::string GetStr() const; // A OPTIMISER
	[[nodiscard]] bool IsZero() const;
	[[nodiscard]] bool IsEven() const;
	[[nodiscard]] bool IsOdd() const;
	[[nodiscard]] bool IsNeg() const;
	[[nodiscard]] Int Abs() const;

	[[nodiscard]] DWORD TrailZero() const;
	static Pair<Int, Int> DivMod(const Int &A, const Int &B);

	Int& operator=(const Int &other);
	Int& operator=(DWORD other);
	Int& operator=(QWORD other);
	Int& operator=(int other);

	Int& operator+=(const Int &B);
	Int& operator-=(const Int &B);
	Int& operator*=(const Int &B);
	Int& operator/=(const Int &B);

	static Int Random(DWORD bits); // For test only

	/// ADD
	///
	/// SI 2 neg => Addition, signe (-)
	/// SI 1 neg => Soustraction avec plus grand
	///				--> Si plus petit a signe (-), alors signe (+)
	///				--> Si plus grand a signe (-), alors signe (-)
	///	SI 0 neg => Addition, signe (+)

	///	SUB
	///
	///	SI 2 neg => Soustraction avec plus grand, signe (-) si A > B, signe (+) sinon
	///	SI 1 neg => Addition, signe (-) si A neg, signe (+) sinon
	///	SI 0 neg => Soustraction avec plus grand, signe (-) si A < B, signe (+) sinon

private:
	static Int Add(const Int &A, const Int &B); // A OPTIMISER
	static Int Sub(const Int &A, const Int &B); // A OPTIMISER
	static Int Mul(const Int &A, const Int &B);
	static Pair<Int, Int> Div(const Int &A, const Int &B);
	static Int Karatsuba(const Int &A, const Int &B);
	static Int LongMul(const Int &A, const Int &B);
	static Int SmallMul(const Int &A, DWORD B);
	// static Pair<Int, Int> BurnikelZiegler(const Int &A, const Int &B);
	static Pair<Int, Int> KnuthD(const Int &A, const Int &B);
	static Pair<Int, DWORD> SmallDiv(const Int &A, DWORD B);
	static sDWORD CmpAbs(const Int &A, const Int &B);
	[[nodiscard]] Int WShift(DWORD b) const;
	[[nodiscard]] Int BLShift(DWORD b) const;
	[[nodiscard]] Int BRShift(DWORD b) const;
	[[nodiscard]] Int ExtByZero(DWORD s) const; // POURQUOI C'EST LÀ ???
	[[nodiscard]] Int Slice(DWORD strt, DWORD len) const;

	void Normalize();

	DTable<DWORD> v;
	bool sign;

friend Int operator+(const Int &A, const Int &B);
friend Int operator-(const Int &A, const Int &B);
friend Int operator*(const Int &A, const Int &B);
friend Int operator/(const Int &A, const Int &B);
friend Int operator%(const Int &A, const Int &B);

friend Int operator<<(const Int &A, DWORD b);
friend Int operator>>(const Int &A, DWORD b);
friend Int operator&(const Int &A, const Int &B);
friend Int operator|(const Int &A, const Int &B);
friend Int operator^(const Int &A, const Int &B);

friend bool operator==(const Int &A, const Int &B);
friend bool operator!=(const Int &A, const Int &B);
friend bool operator<(const Int &A, const Int &B);
friend bool operator>(const Int &A, const Int &B);
friend bool operator<=(const Int &A, const Int &B);
friend bool operator>=(const Int &A, const Int &B);
};

extern const Int Zero;
extern const Int One;
extern const Int slimb;

}

#endif //INT_H
