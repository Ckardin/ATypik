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
#include <iostream>
#include "Tabs.h"
#include "StrUtils.h"

namespace Fenyx::Types
{

/// @brief Int - Classe qui permets la prise en charge de grands nombres entiers relatifs
class Int
{
public:
	Int();

	Int(int value);
	Int(const Int& other);
	Int(const DTable<DWORD> &other, bool sg);
	Int(DWORD value);

	DTable<DWORD> GetTab() const;
	QWORD GetL64();
	std::string GetStr() const;
	bool IsZero() const;

	Int& operator=(const Int& other);
	Int& operator=(DWORD other);
	Int& operator=(int other);

	Int& operator+=(const Int& B);
	Int& operator-=(const Int& B);
	Int& operator*=(const Int& B);
	Int& operator/=(const Int& B);

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
	static Int Add(const Int &A, const Int &B);
	static Int Sub(const Int &A, const Int &B);
	static Int Karatsuba(const Int &A, const Int &B);
	static Int LongMul(const Int &A, const Int &B);
	static Pair<Int, Int> BurnikelZiegler(const Int &A, const Int &B);
	static Pair<Int, Int> LongDiv(const Int &A, const Int &B);
	static sDWORD CmpAbs(const Int &A, const Int &B);
	Int Slice(DWORD strt, DWORD len) const;

	void Normalize();

	static Int ChooseOpSign(const Int &A, const Int &B, BYTE op);

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

}

#endif //INT_H
