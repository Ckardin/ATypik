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
/// @version 4.1
/// @date 19/12/2025

#ifndef INT_H
#define INT_H

#include "ll_Wrp.h"

namespace Fenyx::Types
{

inline constexpr QWORD b32 = (1ULL << 32);
inline constexpr DWORD bs109 = 1000000000ULL;

DWORD NextPow2(DWORD n);

/// @brief Int - Classe qui permet la prise en charge de grands nombres entiers relatifs
class Int
{
public:
	Int();

	Int(int value);
	Int(const Int &other);
	Int(const DTable<DWORD> &other, bool sg);
	Int(const std::string &tstr);
	Int(DWORD value);
	Int(QWORD value);

	[[nodiscard]] DTable<DWORD> GetTab() const;
	[[nodiscard]] DWORD GetSize() const;
	[[nodiscard]] DWORD GetL32() const;
	[[nodiscard]] QWORD GetL64() const;
	[[nodiscard]] Int GetOpposite() const;
	[[nodiscard]] std::string GetStr() const;
	[[nodiscard]] bool IsZero() const;
	[[nodiscard]] bool IsEven() const;
	[[nodiscard]] bool IsOdd() const;
	[[nodiscard]] bool IsNeg() const;
	[[nodiscard]] Int Abs() const;

	[[nodiscard]] QWORD BitLength() const;
	[[nodiscard]] Bit GetBit(QWORD n) const;
	void SetBit(QWORD n, const Bit &b);

	[[nodiscard]] DWORD TrailZero() const;
	static Pair<Int, Int> DivMod(const Int &A, const Int &B);
	static Int Square(const Int& A);

	[[nodiscard]] static bool CTComp(const Int& A, const Int& B);

	Int& operator=(const Int &other);
	Int& operator=(const std::string &tstr);
	Int& operator=(DWORD other);
	Int& operator=(QWORD other);
	Int& operator=(int other);

	Int& operator+=(const Int &B);
	Int& operator-=(const Int &B);
	Int& operator*=(const Int &B);
	Int& operator/=(const Int &B);

	template<class Rdr>
	static Int Random(DWORD bits, Rdr&& rdr);

	/// ADD
	///
	/// SI 2 neg => Addition, signe (-)
	/// SI 1 neg => Soustraction avec plus grand
	///				--> Si plus petit a signe (-), alors signe (+)
	///				--> Si plus grand a signe (-), alors signe (-)
	///	SI 0 neg => Addition, signe (+)

	///	SUB
	///
	///	SI 2 neg => Soustraction avec plus grand, signe (-) si |A| > |B|, signe (+) sinon
	///	SI 1 neg => Addition, signe (-) si A neg, signe (+) sinon
	///	SI 0 neg => Soustraction avec plus grand, signe (-) si |A| < |B|, signe (+) sinon

private:
	static Int Add(const Int &A, const Int &B);
	static Int Sub(const Int &A, const Int &B);
	static Int Mul(const Int &A, const Int &B);
	static Int Sqr(const Int &A, bool sA, bool sB);
	static Pair<Int, Int> Div(const Int &A, const Int &B);
	static Int KaratsubaSqr(const Int &A);
	static Int LongSqr(const Int &A);
	static Int Karatsuba(const Int &A, const Int &B);
	static Int LongMul(const Int &A, const Int &B);
	static Int SmallMul(const Int &A, DWORD B);
	static Pair<Int, Int> KnuthD(const Int &A, const Int &B);
	static Pair<Int, DWORD> SmallDiv(const Int &A, DWORD B);
	static sDWORD CmpAbs(const Int &A, const Int &B);

	template<typename BOp, typename FOp>
	static Int VectBinOp(const Int& A, const Int &B, BOp bop, FOp fop);

	[[nodiscard]] Int WShift(DWORD b) const;
	[[nodiscard]] Int BLShift(DWORD b) const;
	[[nodiscard]] Int BRShift(DWORD b) const;
	[[nodiscard]] Int ExtByZero(DWORD s) const; // POURQUOI C'EST LÀ ???
	[[nodiscard]] Int Slice(DWORD strt, DWORD len) const;

	static Int BarrettReduce(const Int &T, const Int &N, const Int &Mu);

	void Normalize();

	DTable<DWORD> v;
	bool sign;

friend Int GetMu(const Int &N);
friend Int MMul(const Int &A, const Int &B, const Int &N, const Int &Mu);
friend Int MSqr(const Int &A, const Int &N, const Int &Mu);

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

friend std::ostream& operator<<(std::ostream &os, const Int &A);
};

extern const Int Zero;
extern const Int One;
extern const Int slimb;
extern const Int sl2;

template<class Rdr>
Int Int::Random(const DWORD bits, Rdr&& rdr) {
	static_assert(std::is_invocable_r_v<DWORD, Rdr&>, "Random generator must be invocable as DWORD()");

	const DWORD w = (bits + 31) / 32;
	// ReSharper disable once CppJoinDeclarationAndAssignment
	// ReSharper disable once CppTooWideScope
	DWORD mask;
	Int ret;

	ret.v.SetCapacity(w, 0);
	for (QWORD i = 0; i < w; i = i + 1) ret.v[i] = static_cast<DWORD>(std::invoke(rdr));

	const DWORD excess = (w * 32) - bits;
	if (excess > 0) {
		mask = (1u << (32 - excess)) - 1;
		ret.v[ret.v.GetSize() - 1] &= mask;
	}

	ret.v[ret.v.GetSize() - 1] |= (1u << (31 - excess));

	ret.Normalize();
	return ret;
}

template<typename BOp, typename FOp>
Int Int::VectBinOp(const Int& A, const Int &B, BOp bop, FOp fop) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize(), n = (nA >= nB) ? nA : nB, nm = (n == nA) ? nB : nA;
	Int ret;

	ret.v.SetCapacity(n, 0);

#if defined(__AVX2__) || defined(__SSE2__) || defined(__ARM_NEON)
	DWORD* a = A.v.GetPtr();
	DWORD* b = B.v.GetPtr();
	DWORD* r = ret.v.GetPtr();
#endif

#if defined(__AVX2__)
	const DWORD fif = (nm & ~7);
	// ReSharper disable three CppJoinDeclarationAndAssignment
	__m256i simd_a, simd_b, simd_r;

	for (DWORD i = 0; i < fif; i += 8) {
		simd_a = _mm256_load_si256(reinterpret_cast<__m256i*>(a + i));
		simd_b = _mm256_load_si256(reinterpret_cast<__m256i*>(b + i));
		simd_r = bop(simd_a, simd_b);
		_mm256_store_si256(reinterpret_cast<__m256i*>(r + i), simd_r);
	}
#elif defined(__SSE2__)
	const DWORD fif = (nm & ~3);
	// ReSharper disable three CppJoinDeclarationAndAssignment
	__m128i simd_a, simd_b, simd_r;

	for (DWORD i = 0; i < fif; i += 4) {
		simd_a = _mm_load_si128(reinterpret_cast<__m128i*>(a + i));
		simd_b = _mm_load_si128(reinterpret_cast<__m128i*>(b + i));
		simd_r = bop(simd_a, simd_b);
		_mm_store_si128(reinterpret_cast<__m128i*>(r + i), simd_r);
	}
#elif defined(__ARM_NEON)
	const DWORD fif = (nm & ~3);
	// ReSharper disable three CppJoinDeclarationAndAssignment
	uint32x4_t simd_a, simd_b, simd_r;

	for (DWORD i = 0; i < fif; i = i + 4) {
		simd_a = vld1q_u32(a + i);
		simd_b = vld1q_u32(b + i);
		simd_r = bop(simd_a, simd_b);
		vst1q_u32(r + i, simd_r);
	}
#else
	const DWORD fif = nm;
	for (DWORD i = 0; i < fif; i = i + 1) ret.v[i] = bop(A.v[i], B.v[i]);
#endif

	for (QWORD i = nm; i < n; i = i + 1) ret.v[i] = fop(A, B, i);

	ret.Normalize();
	return ret;
}

}

#endif //INT_H
