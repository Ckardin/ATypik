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

/// @file Int.cpp
/// @brief Source de Int
/// @author F&nµx
/// @version 1.0
/// @date 22/08/2025

#include "Int.h"

#include <iostream>

namespace Fenyx::Types
{

/// @brief NextPow2 - Trouve la prochaine puissance de 2 d'un nombre
///
/// @param n: nombre de départ
///
/// @return La prochaine puissance de supérieure ou égale à n.
DWORD NextPow2(DWORD n) {
	if (n == 0) return 1;

	n -= 1;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;

	return n + 1;
}

/// @brief Int - Constructeur
///
/// Constructeur de la classe Int.
Int::Int() {
	v.Clear(); v[0] = 0;
	sign = true;
}

/// @brief Int - Constructeur
///
/// @param[in] value: valeur à affecter
///
/// Constructeur d'affectation de la classe Int.
Int::Int(const int value) {
	v.Clear();
	sign = (value >= 0);

	v[0] = (value >= 0) ? value : -value;
}

/// @brief Int - Constructeur
///
/// @param[in] other: valeur à copier
///
/// Constructeur de copie de la classe Int.
Int::Int(const Int& other) {
	const DWORD n = other.v.GetSize();
	v.Clear(); sign = other.sign;

	v.SetCapacity(n, 0);
	for (QWORD i = 0; i < n; i = i + 1) v[i] = other.v[i];
}

/// @brief Int - Constructeur
///
/// @param[in] other: tableau de DWORD à affecter
/// @param[in] sg: signe du nombre à affecter
///
/// Constructeur d'affectation brute de la classe Int.
Int::Int(const DTable<DWORD> &other, const bool sg) {
	const DWORD n = other.GetSize();
	v.Clear(); sign = sg;

	v.SetCapacity(n, 0);
	for (QWORD i = 0; i < n; i = i + 1) v[i] = other[i];
}

/// @brief Int - Constructeur
///
/// @param[in] value: valeur unitaire à affecter
///
/// Constructeur d'affectation unitaire de la classe Int.
Int::Int(const DWORD value) {
	v.Clear();
	sign = true;

	v[0] = value;
}

/// @brief GetTab - Permet de récupérer le tableau de DWORD
///
/// @return Un tableau de DWORD représentant la valeur absolue du nombre stocké.
DTable<DWORD> Int::GetTab() const {
	const DWORD n = v.GetSize();
	DTable<DWORD> ret;

	ret.Clear(); ret.SetCapacity(n, 0);
	for (QWORD i = 0; i < n; i = i + 1) ret[i] = v[i];

	return ret;
}

/// @brief GetL64 - Récupère les 64 bits de poids faible
///
/// @return Un QWORD représentant les 64 bits de poids faible du nombre stocké.
QWORD Int::GetL64() const {
	const QWORD p0 = (!v.IsEmpty())    ? v[0] : 0;
	const QWORD p1 = (v.GetSize() > 1) ? v[1] : 0;

	return ((p1 << 32) | p0);
}

/// @brief GetStr - Convertit le nombre stocké en chaine de caractères
///
/// @return Une chaîne de caractères décimaux représentant le nombre stocké.
std::string Int::GetStr() const {
	const DWORD n = v.GetSize();
	// ReSharper disable once CppJoinDeclarationAndAssignment
	Int A, r;

	A.v.SetCapacity(n, 0);
	for (QWORD i = 0; i < n; i = i + 1) A.v[i] = v[i];
	std::string ret = "";

	if (A.IsZero()) return "0";

	while (!A.IsZero()) {
		r = A % 10;
		A /= 10;

		ret.push_back(static_cast<char>('0' + r.v[0]));
	}

	if (!sign) ret.push_back('-');

	std::reverse(ret.begin(), ret.end());
	return ret;
}

/// @brief IsZero - Test si le nombre vaut 0 ou pas
///
/// @return True si le nombre stocké vaut 0, false sinon.
bool Int::IsZero() const {
	return (v.GetSize() == 1 && v[0] == 0);
}

/// @brief IsEven - Test si le nombre est pair
///
/// @return True si pair, false sinon.
bool Int::IsEven() const {
	return ((v[0] & 1) == 0);
}

/// @brief IsOdd - Test si le nombre est impair
///
/// @return True si impair, false sinon.
bool Int::IsOdd() const {
	return ((v[0] & 1) == 1);
}

/// @brief IsNeg - Test si le nombre est négatif
///
/// @return True si négatif, false sinon.
bool Int::IsNeg() const {
	return !sign;
}

/// @brief operator= - Opérateur d'affectation entre Int
///
/// @param[in] other: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator=(const Int& other) {
	const DWORD n = other.v.GetSize();
	v.Clear(); sign = other.sign;

	v.SetCapacity(n, 0);
	for (QWORD i = 0; i < n; i = i + 1) v[i] = other.v[i];

	return *this;
}

/// @brief operator= - Opérateur d'affectation unitaire
///
/// @param[in] other: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator=(const DWORD other) {
	v.Clear(); sign = true;
	v[0] = other;

	return *this;
}

/// @brief operator= - Opérateur d'affectation
///
/// @param[in] other: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator=(const int other) {
	v.Clear();

	sign = (other >= 0);
	v[0] = (other >= 0) ? other : -other;

	return *this;
}

/// @brief operator+= - Opérateur d'affectation additif
///
/// @param[in] B: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator+=(const Int& B) {
	const DWORD nA = v.GetSize(), nB = B.v.GetSize(), nr = (nA > nB) ? nA : nB;
	Int ret, A, tA, tB;

	A.v.SetCapacity(nA, 0);
	for (QWORD i = 0; i < nA; i = i + 1) A.v[i] = v[i];
	A.sign = sign;

	tA.sign = true, tB.sign = true;

	tA.v.SetCapacity(nA, 0); tB.v.SetCapacity(nB, 0);
	for (QWORD i = 0; i < nA; i = i + 1) tA.v[i] = A.v[i];
	for (QWORD i = 0; i < nB; i = i + 1) tB.v[i] = B.v[i];

	ret.v.SetCapacity(nr, 0);
	tA.Normalize(); tB.Normalize();

	if (A.sign == B.sign) {
		ret = Add(A, B);
		ret.sign = A.sign;
	} else {
		if (CmpAbs(A, B) >= 0) {
			ret = Sub(tA, tB);
			ret.sign = A.sign;
		} else {
			ret = Sub(tB, tA);
			ret.sign = B.sign;
		}
	}

	v.Clear(); const DWORD nrt = ret.v.GetSize();
	for (QWORD i = 0; i < nrt; i = i + 1) v[i] = ret.v[i];
	sign = ret.sign;

	Normalize();
	return *this;
}

/// @brief operator-= - Opérateur d'affectation soustractif
///
/// @param[in] B: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator-=(const Int& B) {
	const DWORD nA = v.GetSize(), nB = B.v.GetSize(), nr = (nA > nB) ? nA : nB;
	Int ret, A, tA, tB;

	A.v.SetCapacity(nA, 0);
	for (QWORD i = 0; i < nA; i = i + 1) A.v[i] = v[i];
	A.sign = sign;

	tA.sign = true, tB.sign = true;

	tA.v.SetCapacity(nA, 0); tB.v.SetCapacity(nB, 0);
	for (QWORD i = 0; i < nA; i = i + 1) tA.v[i] = A.v[i];
	for (QWORD i = 0; i < nB; i = i + 1) tB.v[i] = B.v[i];

	ret.v.SetCapacity(nr, 0);
	tA.Normalize(); tB.Normalize();

	if (A.sign != B.sign) {
		ret = Add(tA, tB);
		ret.sign = A.sign;
	} else {
		const sDWORD c = CmpAbs(A, B);

		if (c == 0) {
			ret = 0;
			ret.sign = true;
		} else {
			if (c > 0) {
				ret = Sub(tA, tB);
				ret.sign = A.sign;
			} else {
				ret = Sub(tB, tA);
				ret.sign = !A.sign;
			}
		}
	}

	v.Clear(); const DWORD nrt = ret.v.GetSize();
	for (QWORD i = 0; i < nrt; i = i + 1) v[i] = ret.v[i];
	sign = ret.sign;

	Normalize();
	return *this;
}

/// @brief operator*= - Opérateur d'affectation multiplicatif
///
/// @param[in] B: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator*=(const Int& B) {
	const DWORD nA = v.GetSize(), nB = B.v.GetSize();
	Int A, tA, tB;

	A.v.SetCapacity(nA, 0);
	for (QWORD i = 0; i < nA; i = i + 1) A.v[i] = v[i];
	A.sign = sign;

	tA.sign = true, tB.sign = true;

	tA.v.SetCapacity(nA, 0); tB.v.SetCapacity(nB, 0);
	for (QWORD i = 0; i < nA; i = i + 1) tA.v[i] = A.v[i];
	for (QWORD i = 0; i < nB; i = i + 1) tB.v[i] = B.v[i];

	tA.Normalize(); tB.Normalize();

	Int ret = Mul(tA, tB);
	ret.sign = (A.sign == B.sign);

	v.Clear(); const DWORD nrt = ret.v.GetSize();
	for (QWORD i = 0; i < nrt; i = i + 1) v[i] = ret.v[i];
	sign = ret.sign;

	Normalize();
	return *this;
}

/// @brief operator/= - Opérateur d'affectation divisible
///
/// @param[in] B: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator/=(const Int& B) {
	const DWORD nA = v.GetSize(), nB = B.v.GetSize(), nr = nA - nB + 1;
	Int ret, A, tA, tB;

	A.v.SetCapacity(nA, 0);
	for (QWORD i = 0; i < v.GetSize(); i = i + 1) A.v[i] = v[i];
	A.sign = sign;

	tA.sign = true, tB.sign = true;

	tA.v.SetCapacity(nA, 0); tB.v.SetCapacity(nB, 0);
	for (QWORD i = 0; i < nA; i = i + 1) tA.v[i] = A.v[i];
	for (QWORD i = 0; i < nB; i = i + 1) tB.v[i] = B.v[i];

	ret.v.SetCapacity(nr, 0);
	tA.Normalize(); tB.Normalize();

	if (tB.IsZero()) throw std::runtime_error("Division by zero");
	if (tA.IsZero() || tA < tB) {
		v.Clear(); v[0] = 0;
		sign = true;

		Normalize();
		return *this;
	}
	if (tB == Int(1)) {
		v.Clear(); const DWORD nrt = ret.v.GetSize();
		for (QWORD i = 0; i < nrt; i = i + 1) v[i] = tA.v[i];

		Normalize();
		return *this;
	}

	if (tB.v.GetSize() == 1) {
		Pair<Int, DWORD> qr = SmallDiv(tA, tB.v[0]);
		ret = qr.First();
	} else {
		Pair<Int, Int> qr = BurnikelZiegler(tA, tB);
		ret = qr.First();
	}

	ret.sign = (sign == B.sign);

	v.Clear(); const DWORD nrt = ret.v.GetSize();
	for (QWORD i = 0; i < nrt; i = i + 1) v[i] = ret.v[i];
	sign = ret.sign;

	Normalize();
	return *this;
}

/// @brief operator- - Opérateur de négativité
///
/// @return Une référence sur le Int affecté.
///
/// Ne fait qu'inverser le signe, pas de calcul supplémentaire.
Int& Int::operator-() {
	sign = !sign;

	return *this;
}

Int Int::Random(const DWORD bits) { // For test only
	const DWORD words = (bits + 31) / 32;
	// ReSharper disable once CppJoinDeclarationAndAssignment
	// ReSharper disable once CppTooWideScope
	DWORD mask;
	Int ret;

	thread_local std::mt19937_64 rng(std::random_device{}());
	std::uniform_int_distribution<DWORD> dist(0, 0xFFFFFFFF);

	for (QWORD i = 0; i < words; i = i + 1) ret.v[i] = dist(rng);

	const DWORD excess = words * 32 - bits;
	if (excess > 0) {
		mask = (1u << (32 - excess)) - 1;
		ret.v[ret.v.GetSize() - 1] &= mask;
	}

	ret.v[ret.v.GetSize() - 1] |= (1u << (31 - excess));

	ret.Normalize();
	return ret;
}

Int Int::Add(const Int &A, const Int &B) {
	Int ret;
	// ReSharper disable three CppJoinDeclarationAndAssignment
	QWORD carry = 0, a, b, sum;
	const DWORD n = (A.v.GetSize() > B.v.GetSize()) ? A.v.GetSize() : B.v.GetSize(), nA = A.v.GetSize(), nB = B.v.GetSize();

	ret.v.SetCapacity(n, 0);

	for (QWORD i = 0; i < n; i = i +1) {
		a = (i < nA) ? A.v[i] : 0;
		b = (i < nB) ? B.v[i] : 0;
		sum = a + b + carry;

		ret.v[i] = static_cast<uint32_t>(sum);
		carry = sum >> 32;
	}

	if (carry) ret.v[ret.v.GetSize()] = static_cast<uint32_t>(carry);

	ret.Normalize();
	return ret;
}

Int Int::Sub(const Int &A, const Int &B) {
	Int ret;
	// ReSharper disable three CppJoinDeclarationAndAssignment
	sQWORD borrow = 0, a, b, tsub, l132 = (1LL << 32);
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize();

	ret.v.SetCapacity(nA, 0);

	for (QWORD i = 0; i < nA; i = i + 1) {
		a = A.v[i];
		b = (i < nB) ? B.v[i] : 0;
		tsub = a - b - borrow;

		if (tsub < 0) {
			tsub += l132;
			borrow = 1;
		} else borrow = 0;

		ret.v[i] = static_cast<DWORD>(tsub);
	}

	ret.Normalize();
	return ret;
}

Int Int::Mul(const Int &A, const Int &B) {
	if (const DWORD n = (A.v.GetSize() > B.v.GetSize()) ? A.v.GetSize() : B.v.GetSize(); n <= 64) return LongMul(A, B);
	return Karatsuba(A, B);
}

Int Int::Karatsuba(const Int &A, const Int &B) {
	const DWORD n = (A.v.GetSize() > B.v.GetSize()) ? A.v.GetSize() : B.v.GetSize();
	const DWORD m = (n + 1) / 2;

	if (n <= 64) return LongMul(A, B);

	Int A0 = A.Slice(0, m).ExtByZero(m);
	Int A1 = A.Slice(m, A.v.GetSize() - m);
	Int B0 = B.Slice(0, m).ExtByZero(m);
	Int B1 = B.Slice(m, B.v.GetSize() - m);

	Int z0 = Karatsuba(A0, B0);
	Int z1 = Karatsuba(A0 + A1, B0 + B1);
	Int z2 = Karatsuba(A1, B1);
	z1 = z1 - z0 - z2;

	Int ret = z0 + z1.WShift(m) + z2.WShift(2 * m);

	ret.Normalize();
	return ret;
}

Int Int::LongMul(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize();
	QWORD carry = 0, p, b;
	Int ret;

	ret.v.SetCapacity(A.v.GetSize() + B.v.GetSize(), 0);

	for (QWORD i = 0; i < nA; i = i + 1) {
		carry = 0;

		for (QWORD j = 0; j < nB || carry; j = j + 1) {
			b = (j < nB) ? B.v[j] : 0;
			p = static_cast<QWORD>(ret.v[i + j])
			    + (static_cast<QWORD>(A.v[i]) * b) + carry;

			ret.v[i + j] = static_cast<DWORD>(p);
			carry = (p >> 32);
		}
	}

	ret.Normalize();
	return ret;
}

Int Int::SmallMul(const Int &A, const DWORD B) {
	const DWORD n = A.v.GetSize();
	QWORD carry, p;
	Int ret;

	if (B == 0) return {0};
	if (B == 1) {
		ret = A;
		ret.Normalize();
		return ret;
	}

	ret.v.SetCapacity(n, 0);

	carry = 0;
	for (QWORD i = 0; i < n; i = i + 1) {
		p = static_cast<QWORD>(A.v[i]) * B + carry;
		ret.v[i] = static_cast<DWORD>(p);

		carry = (p >> 32);
	}

	while (carry != 0) {
		ret.v[ret.v.GetSize()] = static_cast<DWORD>(carry);
		carry >>= 32;
	}

	ret.Normalize();
	ret.sign = A.sign;
	return ret;
}

Pair<Int, Int> Int::BurnikelZiegler(const Int &A, const Int &B) {
	const DWORD lz = __builtin_clz(B.v[B.v.GetSize() - 1]), m = A.v.GetSize(), n = B.v.GetSize();
	if (B == Int(0)) throw std::runtime_error("Division by zero");
	if (n <= 256) return SchoolDiv(A, B);

	const Int sub = Sub(A, B);
	if (sub < B) return {1, sub};
	if (sub == B) return {2, 0};

	Int tA(A << lz), tB(B << lz), Q, R, Qpart;
	DWORD k, t, npA, npB, tp, ablk, si, sw, sstqr;
	DTable<Int> bA, bB, tbA;
	Pair<Int, Int> tqr;
	QWORD rem;

	Q.v.Clear(); R.v.Clear();

	k   = NextPow2((n + 1) / 2);
	t   = (n + k - 1) / k;
	npB = t * k;
	npA = ((m + k - 1) / k) * k;

	if (npA < npB) npA = npB; // For precaution only !

	for (QWORD i = m; i < npA; i = i + 1) tA.v[i] = 0;
	for (QWORD i = n; i < npB; i = i + 1) tB.v[i] = 0;

	bA.Clear(); bB.Clear();

	tp = npA / k;
	for (QWORD i = 0; i < tp; i = i + 1) {
		for (QWORD j = 0; j < k; j = j + 1) {
			bA[i].v[j] = tA.v[(i * k) + j];
		}
	}

	for (QWORD i = 0; i < t; i = i + 1) {
		for (QWORD j = 0; j < k; j = j + 1) {
			bB[i].v[j] = tB.v[(i * k) + j];
		}
	}

	sQWORD i = tp;
	while (i > 0) {
		rem = i;

		if (t == 1) ablk = (rem >= 2) ? 2 : rem;
		else        ablk = (rem >= 3) ? 3 : rem;

		si = i - ablk;

		tbA.Clear();
		for (QWORD j = 0; j < ablk; j = j + 1) tbA[j] = bA[si + j];

		if (ablk == 1)      tqr = SchoolDiv(tbA[0], bB[0]);
		else if (ablk == 2) tqr = BZ21(tbA, bB);
		else                tqr = BZ32(tbA, bB);

		sw = 0;
		for (DWORD w = 0; w < si; w = w + 1) sw += bA[w].v.GetSize();
		Qpart = tqr.First().WShift(sw);
		Q     = Q + Qpart;

		sstqr = tqr.Second().v.GetSize();
		for (QWORD j = 0; j < sstqr; j = j + 1) bA[si + j] = tqr.Second().v[j];

		i -= ablk;
	}

	const DWORD tpB = bA.GetSize();
	for (QWORD j = 0; j < tpB; j = j + 1) {
		for (QWORD l = 0; l < k; l = l + 1) {
			R.v[j * k + l] = bA[j].v[l];
		}
	}

	R = (R >> lz);

	Q.Normalize(); R.Normalize();
	return {Q, R};
}

Pair<Int, Int> Int::BZ32(const DTable<Int> &A, const DTable<Int> &B) {
	const DWORD lz = __builtin_clz(B[1].v[B[1].v.GetSize() - 1]), n = B[0].v.GetSize();
	Pair<Int, Int> tqr;
	DTable<Int> tA, tB, ttA, ttB;
	Int Q, R, b(1);
	b = (b << 32);

	if (n <= 128) return SchoolDiv(A[0] + A[1].WShift(n) + A[2].WShift(2 * n), B[0] + B[1].WShift(n));

	tA.Clear(); tB.Clear();
	const Int ttpA = (A[0] + A[1].WShift(n) + A[2].WShift(2 * n)) << lz;
	const Int ttpB = (B[0] + B[1].WShift(n)) << lz;

	tA[0] = ttpA.Slice(0, n);
	tA[1] = ttpA.Slice(n, n);
	tA[2] = ttpA.Slice(2 * n, n);

	tB[0] = ttpB.Slice(0, n);
	tB[1] = ttpB.Slice(n, n);

	ttA.Clear(); ttB.Clear();
	ttB[0] = tB[1];
	ttA[0] = tA[1];
	ttA[1] = tA[2];

	if (tA[2] < tB[1]) tqr = BZ21(ttA, ttB);
	else               tqr.Set(b.WShift(n) - Int(1), (tA[2] - tB[1]).WShift(n) + tA[1] + tB[1]);

	R = tqr.Second().WShift(n) + tA[0] - (tqr.First() * tB[0]);
	Q = tqr.First();

	const Int cB = tB[1].WShift(n) + tB[0];
	while (R < Int(0) || R >= cB) {
		if (R < Int(0)) {
			R += cB;
			Q -= Int(1);
		} else if (R >= cB) {
			R -= cB;
			Q += Int(1);
		}
	}

	Q.Normalize();
	R = (R >> lz);
	R.Normalize();

	return {Q, R};
}

Pair<Int, Int> Int::BZ21(const DTable<Int> &A, const DTable<Int> &B) {
	const DWORD lz = __builtin_clz(B[0].v[B[0].v.GetSize() - 1]), nta = A[0].v.GetSize(), ntb = B[0].v.GetSize();
	Pair<Int, Int> tqr1, tqr2;
	DTable<Int> tA, tB, ttA, ttB, t21a;
	Int Q, R, b(1);
	b = (b << 32);

	if (nta <= 128) return SchoolDiv(A[0] + A[1].WShift(nta), B[0]);

	tA.Clear(); tB.Clear();
	tB[0] = (B[0] << lz);

	const Int ttpA = (A[0] + A[1].WShift(nta)) << lz;
	tA[0] = ttpA.Slice(0, nta);
	tA[1] = ttpA.Slice(nta, nta);

	const DWORD ha = nta / 2;
	const DWORD la = nta - ha;
	const DWORD hb = ntb / 2;
	const DWORD lb = ntb - hb;

	ttA.Clear(); ttB.Clear();
	ttA[0] = tA[0].Slice(0, ha);
	ttA[1] = tA[0].Slice(ha, la);
	ttA[2] = tA[1].Slice(0, ha);
	ttA[3] = tA[1].Slice(ha, la);

	ttB[0] = tB[0].Slice(0, hb);
	ttB[1] = tB[0].Slice(hb, lb);

	t21a.Clear();
	t21a[0] = ttA[1]; t21a[1] = ttA[2]; t21a[2] = ttA[3];

	tqr1 = BZ32(t21a, ttB);

	t21a.Clear();
	Int rl = tqr1.Second().Slice(0, ttB[0].v.GetSize());
	Int rh = tqr1.Second().Slice(ttB[0].v.GetSize(), tqr1.Second().v.GetSize() - ttB[0].v.GetSize());

	t21a[0] = ttA[0]; t21a[1] = rl; t21a[2] = rh;
	tqr2 = BZ32(t21a, ttB);

	Q = tqr1.First().WShift(ntb) + tqr2.First();
	R = (tqr2.Second() >> lz);

	Q.Normalize(); R.Normalize();
	return {Q, R};
}

Pair<Int, Int> Int::SchoolDiv(const Int &A, const Int &B) {
	const DWORD lz = __builtin_clz(B.v[B.v.GetSize() - 1]), m = A.v.GetSize(), n = B.v.GetSize();
	Int tA((A << lz)), tB((B << lz)), b(1), Q, R, qB;
	QWORD qest, rest, ta;
	b = (b << 32);

	if (m < n) return {Int(0), A};
	if (m == n) {
		if (A < B) return {Int(0), A};
		return {Int(1), A - B};
	}
	if (n == 1) {
		Pair<Int, DWORD> qrt = SmallDiv(A, B.v[0]);
		Q = qrt.First(); R = qrt.Second();

		Q.Normalize(); R.Normalize();
		return {Q, R};
	}

	const QWORD bl64 = b.GetL64();
	for (sQWORD j = (m - n); j >= 0; j = j - 1) {
		ta   = (static_cast<QWORD>(tA.v[j + n]) << 32) | tA.v[j + n - 1];
		qest = ta / tB.v[n - 1];
		rest = ta % tB.v[n - 1];

		if (qest >= bl64) qest = bl64 - 1;

		while ((qest * tB.v[n - 2]) > (bl64 * rest + tA.v[j + n - 2])) {
			qest -= 1;
			rest += tB.v[n - 1];
			if (rest >= bl64) break;
		}

		qB = tB * Int(static_cast<DWORD>(qest));
		qB = qB.WShift(j);

		if (tA >= qB) {
			tA -= qB;
			Q.v[j] = static_cast<DWORD>(qest);
		} else {
			tA = tA - qB + tB.WShift(j);
			Q.v[j] = static_cast<DWORD>(qest - 1);
		}
	}

	R = (tA >> lz);

	Q.Normalize(); R.Normalize();
	return {Q, R};
}

Pair<Int, DWORD> Int::SmallDiv(const Int &A, const DWORD B) {
	Int q;
	QWORD r = 0, c;

	if (B == 0) throw std::runtime_error("Division by zero");
	if (A < Int(B)) {
		q = 0; r = A.v[0];

		q.Normalize();
		return {q, static_cast<DWORD>(r)};
	}

	for (sQWORD i = A.v.GetSize() - 1; i >= 0; i = i - 1) {
		c = (r << 32) | A.v[i];
		q.v[i] = static_cast<DWORD>(c / B);
		r = c % B;
	}

	q.Normalize();

	return {q, static_cast<DWORD>(r)};
}

sDWORD Int::CmpAbs(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize();

	if (nA < nB) return -1;
	if (nA > nB) return 1;

	for (sQWORD i = nA - 1; i >= 0; i = i - 1) {
		if (A.v[i] < B.v[i]) return -1;
		if (A.v[i] > B.v[i]) return 1;
	}

	return 0;
}

Int Int::Abs() {
	const DWORD n = v.GetSize();
	Int ret;

	ret.v.SetCapacity(n, 0);
	for (QWORD i = 0; i < n; i = i + 1) ret.v[i] = v[i];
	ret.sign = true;

	ret.Normalize();
	return ret;
}

Int Int::WShift(const DWORD b) const {
	const sQWORD fi = (v.GetSize() + b) - 1;
	Int ret;

	ret.v.SetCapacity(fi + 1, 0);
	for (sQWORD i = fi; i >= 0; i = i - 1) ret.v[i] = ((i - b) >= 0) ? v[i - b] : 0;

	return ret;
}

Int Int::ExtByZero(const DWORD s) const {
	const DWORD n = v.GetSize();
	Int ret;

	for (QWORD i = 0; i < n; i = i + 1) ret.v[i] = v[i];
	for (QWORD i = n; i < s; i = i + 1) ret.v[i] = 0;

	return ret;
}

Int Int::Slice(const DWORD strt, const DWORD len) const {
	const DWORD n = v.GetSize();
	Int ret;

	if (strt >= n) return ret;

	const DWORD fi = ((strt + len) > n) ? n : (strt + len);
	ret.v.SetCapacity(fi - strt, 0);

	for (DWORD i = strt; i < fi; i = i + 1) ret.v[i - strt] = v[i];

	ret.Normalize();
	return ret;
}

void Int::Normalize() {
	while (v.GetSize() > 1 && v[v.GetSize() - 1] == 0) v.Erase(v.GetSize() - 1);

	if (v.GetSize() == 0)              v[0] = 0;
	if (v.GetSize() == 1 && v[0] == 0) sign = true;
}


/// @brief operator+ - Opérateur d'addition
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le résultat de [A] + [B].
Int operator+(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize(), nr = (nA > nB) ? nA : nB;
	Int ret, tA, tB;

	tA.sign = true, tB.sign = true;

	tA.v.SetCapacity(nA, 0); tB.v.SetCapacity(nB, 0);
	for (QWORD i = 0; i < nA; i = i + 1) tA.v[i] = A.v[i];
	for (QWORD i = 0; i < nB; i = i + 1) tB.v[i] = B.v[i];

	ret.v.SetCapacity(nr, 0);
	tA.Normalize(); tB.Normalize();

	if (A.sign == B.sign) {
		ret = Int::Add(A, B);
		ret.sign = A.sign;
	} else {
		if (Int::CmpAbs(A, B) >= 0) {
			ret = Int::Sub(tA, tB);
			ret.sign = A.sign;
		} else {
			ret = Int::Sub(tB, tA);
			ret.sign = B.sign;
		}
	}

	ret.Normalize();
	return ret;
}

/// @brief operator- - Opérateur de soustraction
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le résultat de [A] - [B].
Int operator-(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize(), nr = (nA > nB) ? nA : nB;
	Int ret, tA, tB;

	tA.sign = true, tB.sign = true;

	tA.v.SetCapacity(nA, 0); tB.v.SetCapacity(nB, 0);
	for (QWORD i = 0; i < nA; i = i + 1) tA.v[i] = A.v[i];
	for (QWORD i = 0; i < nB; i = i + 1) tB.v[i] = B.v[i];

	ret.v.SetCapacity(nr, 0);
	tA.Normalize(); tB.Normalize();

	if (A.sign != B.sign) {
		ret = Int::Add(tA, tB);
		ret.sign = A.sign;
	} else {
		const sDWORD c = Int::CmpAbs(A, B);

		if (c == 0) {
			ret = 0;
			ret.sign = true;
		} else {
			if (c > 0) {
				ret = Int::Sub(tA, tB);
				ret.sign = A.sign;
			} else {
				ret = Int::Sub(tB, tA);
				ret.sign = !A.sign;
			}
		}
	}

	ret.Normalize();
	return ret;
}

/// @brief operator* - Opérateur de multiplication
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le résultat de [A] * [B].
Int operator*(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize(), nr = nA + nB;
	Int ret, tA, tB;

	tA.sign = true, tB.sign = true;

	tA.v.SetCapacity(nA, 0); tB.v.SetCapacity(nB, 0);
	for (QWORD i = 0; i < nA; i = i + 1) tA.v[i] = A.v[i];
	for (QWORD i = 0; i < nB; i = i + 1) tB.v[i] = B.v[i];

	ret.v.SetCapacity(nr, 0);
	tA.Normalize(); tB.Normalize();

	ret = Int::Mul(tA, tB);
	ret.sign = (A.sign == B.sign);

	ret.Normalize();
	return ret;
}

/// @brief operator/ - Opérateur de division
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le résultat de la division euclidienne de [A] par [B], uniquement le quotient.
Int operator/(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize(), nr = nA - nB + 1;
	Int ret, tA, tB;

	tA.sign = true, tB.sign = true;

	tA.v.SetCapacity(nA, 0); tB.v.SetCapacity(nB, 0);
	for (QWORD i = 0; i < nA; i = i + 1) tA.v[i] = A.v[i];
	for (QWORD i = 0; i < nB; i = i + 1) tB.v[i] = B.v[i];

	ret.v.SetCapacity(nr, 0);
	tA.Normalize(); tB.Normalize();

	if (tB.IsZero()) throw std::runtime_error("Division by zero");
	if (tA.IsZero() || tA < tB) {
		ret = 0;
		return ret;
	}
	if (tB == Int(1)) {
		ret = tA;
		ret.sign = A.sign;
		return ret;
	}

	if (tB.v.GetSize() == 1) {
		Pair<Int, DWORD> qr = Int::SmallDiv(tA, tB.v[0]);
		ret = qr.First();
	} else {
		Pair<Int, Int> qr = Int::BurnikelZiegler(tA, tB);
		ret = qr.First();
	}

	ret.sign = (A.sign == B.sign);

	ret.Normalize();
	return ret;
}

/// @brief operator% - Opérateur modulo
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le reste de la division euclidienne de [A] par [B].
Int operator%(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize(), nr = nB;
	Int ret, tA, tB;

	tA.sign = true, tB.sign = true;

	tA.v.SetCapacity(nA, 0); tB.v.SetCapacity(nB, 0);
	for (QWORD i = 0; i < nA; i = i + 1) tA.v[i] = A.v[i];
	for (QWORD i = 0; i < nB; i = i + 1) tB.v[i] = B.v[i];

	ret.v.SetCapacity(nr, 0);
	tA.Normalize(); tB.Normalize();

	if (tB.IsZero()) throw std::runtime_error("Division by zero");
	if (tA.IsZero()) {
		ret = tB;
		return ret;
	}
	if (tA < tB) {
		ret = tA;
		return ret;
	}

	if (B == Int(2)) ret = (tA.v[0] & 1);

	if (tB.v.GetSize() == 1) {
		Pair<Int, DWORD> qr = Int::SmallDiv(tA, tB.v[0]);
		ret = qr.Second();
	} else {
		Pair<Int, Int> qr = Int::BurnikelZiegler(tA, tB);
		ret = qr.Second();
	}

	ret.sign = (A.sign == B.sign);

	ret.Normalize();
	return ret;
}

/// @brief operator<< - Opérateur de décalage à gauche
///
/// @param[in] A: l-value
/// @param[in] b: nombre de bits à décaler
///
/// @return Le résultat de l'opération binaire [A] << [b].
Int operator<<(const Int &A, const DWORD b) {
	const DWORD nw = b / 32, nb = b % 32, asize = A.v.GetSize(), fi = asize + nw + (nb ? 1 : 0);
	DWORD c = 0;
	QWORD x;
	Int ret;

	if (A.IsZero() || b == 0) {
		ret = A;
		ret.Normalize();
		return ret;
	}

	ret.v.SetCapacity(fi, 0);
	for (QWORD i = 0; i < asize; i = i + 1) {
		x = (static_cast<QWORD>(A.v[i]) << nb) | c;
		ret.v[i + nw] = static_cast<DWORD>(x);

		c = static_cast<DWORD>(x >> 32);
	}

	if (nb) ret.v[asize + nw] = c;
	for (QWORD i = 0; i < nw; i++) ret.v[i] = 0;

	ret.Normalize();
	return ret;
}

/// @brief operator>> - Opérateur de décalage à droite
///
/// @param[in] A: l-value
/// @param[in] b: nombre de bits à décaler
///
/// @return Le résultat de l'opération binaire [A] >> [b].
Int operator>>(const Int &A, const DWORD b) {
	const DWORD nw = b / 32, nb = b % 32, asize = A.v.GetSize(), fi = asize - nw, nb32 = 32 - nb;
	DWORD c = 0, xc;
	Int ret;

	if (A.IsZero() || b == 0) {
		ret = A;
		ret.Normalize();
		return ret;
	}

	if (b >= (asize * 32)) return {0};

	ret.v.SetCapacity(fi, 0);
	for (QWORD i = fi; i > 0; i = i - 1) {
		xc = A.v[i - 1 + nw];
		ret.v[i - 1] = (xc >> nb) | c;

		c = nb ? (xc << nb32) : 0;
	}

	ret.Normalize();
	return ret;
}

/// @brief operator& - Opérateur ET logique
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le résultat de l'opération binaire [A] & [B].
Int operator&(const Int &A, const Int &B) {
	const DWORD n = (A.v.GetSize() >= B.v.GetSize()) ? A.v.GetSize() : B.v.GetSize(), nA = A.v.GetSize(), nB = B.v.GetSize();
	Int ret;
	DWORD t0, t1;

	ret.v.SetCapacity(n, 0);
	for (QWORD i = 0; i < n; i = i + 1) {
		// ReSharper disable once CppJoinDeclarationAndAssignment
		t0 = (i < nA) ? A.v[i] : 0;
		// ReSharper disable once CppJoinDeclarationAndAssignment
		t1 = (i < nB) ? B.v[i] : 0;

		ret.v[i] = t0 & t1;
	}

	ret.Normalize();
	return ret;
}

/// @brief operator| - Opérateur OU logique
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le résultat de l'opération binaire [A] | [B].
Int operator|(const Int &A, const Int &B) {
	const DWORD n = (A.v.GetSize() >= B.v.GetSize()) ? A.v.GetSize() : B.v.GetSize(), nA = A.v.GetSize(), nB = B.v.GetSize();
	Int ret;
	DWORD t0, t1;

	ret.v.SetCapacity(n, 0);
	for (QWORD i = 0; i < n; i = i + 1) {
		// ReSharper disable once CppJoinDeclarationAndAssignment
		t0 = (i < nA) ? A.v[i] : 0;
		// ReSharper disable once CppJoinDeclarationAndAssignment
		t1 = (i < nB) ? B.v[i] : 0;

		ret.v[i] = t0 | t1;
	}

	ret.Normalize();
	return ret;
}

/// @brief operator^ - Opérateur XOR logique
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le résultat de l'opération binaire [A] ^ [B].
Int operator^(const Int &A, const Int &B) {
	const DWORD n = (A.v.GetSize() >= B.v.GetSize()) ? A.v.GetSize() : B.v.GetSize(), nA = A.v.GetSize(), nB = B.v.GetSize();
	Int ret;
	DWORD t0, t1;

	ret.v.SetCapacity(n, 0);
	for (QWORD i = 0; i < n; i = i + 1) {
		// ReSharper disable once CppJoinDeclarationAndAssignment
		t0 = (i < nA) ? A.v[i] : 0;
		// ReSharper disable once CppJoinDeclarationAndAssignment
		t1 = (i < nB) ? B.v[i] : 0;

		ret.v[i] = t0 ^ t1;
	}

	ret.Normalize();
	return ret;
}

/// @brief operator== - Opérateur d'égalité entre Int
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return True si [A] = [B], false sinon.
bool operator==(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize();

	if (nA != nB)         return false;
	if (A.sign != B.sign) return false;

	for (QWORD i = 0; i < nA; i = i + 1) {
		if (A.v[i] != B.v[i]) return false;
	}

	return true;
}

/// @brief operator!= - Opérateur d'inégalité entre Int
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return False si [A] = [B], true sinon.
bool operator!=(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize();

	if (nA != nB)         return true;
	if (A.sign != B.sign) return true;

	for (QWORD i = 0; i < nA; i = i + 1) {
		if (A.v[i] != B.v[i]) {
			return true;
		}
	}

	return false;
}

/// @brief operator< - Opérateur d'infériorité entre Int
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return True si [A] < [B], false sinon.
bool operator<(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize();

	if (A.sign && !(B.sign)) return false;
	if (!(A.sign) && B.sign) return true;

	if (A.sign && B.sign) {
		if (nA < nB) return true;
		if (nA > nB) return false;

		for (sQWORD i = nA - 1; i >= 0; i = i - 1) {
			if (A.v[i] < B.v[i]) return true;
			if (A.v[i] > B.v[i]) return false;
		}
	} else {
		if (nA < nB) return false;
		if (nA > nB) return true;

		for (sQWORD i = nA - 1; i >= 0; i = i - 1) {
			if (A.v[i] < B.v[i]) return false;
			if (A.v[i] > B.v[i]) return true;
		}
	}

	return false;
}

/// @brief operator> - Opérateur de supériorité entre Int
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return True si [A] > [B], false sinon.
bool operator>(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize();

	if (A.sign && !(B.sign)) return true;
	if (!(A.sign) && B.sign) return false;

	if (A.sign && B.sign) {
		if (nA < nB) return false;
		if (nA > nB) return true;

		for (sQWORD i = nA - 1; i >= 0; i = i - 1) {
			if (A.v[i] < B.v[i]) return false;
			if (A.v[i] > B.v[i]) return true;
		}
	} else {
		if (nA < nB) return true;
		if (nA > nB) return false;

		for (sQWORD i = nA - 1; i >= 0; i = i - 1) {
			if (A.v[i] < B.v[i]) return true;
			if (A.v[i] > B.v[i]) return false;
		}
	}

	return false;
}

/// @brief operator<= - Opérateur d'infériorité ou égalité
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return True si [A] <= [B], false sinon.
bool operator<=(const Int &A, const Int &B) {
	return ((A == B) || (A < B));
}

/// @brief operator>= - Opérateur de supériorité ou égalité
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return True si [A] >= [B], false sinon.
bool operator>=(const Int &A, const Int &B) {
	return ((A == B) || (A > B));
}

}

