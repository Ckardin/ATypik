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
/// @version 4.1
/// @date 19/12/2025

#include "Int.h"

#include <iostream>

namespace Fenyx::Types
{

const Int Zero  = 0;
const Int One   = 1;
const Int slimb = One << 32;
const Int sl2   = One << 64;

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
Int::Int(const Int &other) {
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
/// @param[in] tstr: std::string à affecter
///
/// Constructeur d'affectation de chaine de la classe Int.
Int::Int(const std::string &tstr) {
	if (tstr.empty()) return;

	DTable<DWORD> dblk;
	// ReSharper disable two CppJoinDeclarationAndAssignment
	DWORD strt, len;
	QWORD carry, c;
	dblk.Clear();

	size_t p = 0;
	if (tstr[0] == '-') {
		sign = false;
		p = 1;
	} else if (tstr[0] == '+') {
		sign = true;
		p = 1;
	} else sign = true;

	std::string str = tstr.substr(p);

	const DWORD strs = str.size();
	for (sDWORD i = strs; i > 0; i -= 9) {
		strt = ((i - 9) > 0) ? (i - 9) : 0;
		len  = i - strt;

		dblk[dblk.GetSize()] = std::stoul(str.substr(strt, len));
	}

	v.Clear();
	while (!(dblk.GetSize() == 1 && dblk[0] == 0)) {
		carry = 0;

		for (sDWORD i = dblk.GetSize() - 1; i >= 0; i = i - 1) {
			c = dblk[i] + carry * bs109;
			dblk[i] = static_cast<DWORD>(c / b32);
			carry = c % b32;
		}

		v[v.GetSize()] = static_cast<DWORD>(carry);
		while (dblk.GetSize() > 1 && dblk[dblk.GetSize() - 1] == 0) dblk.Erase(dblk.GetSize() - 1);
	}
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

/// @brief Int - Constructeur
///
/// @param[in] value: valeur unitaire à affecter
///
/// Constructeur d'affectation unitaire sur QWORD de la classe Int.
Int::Int(const QWORD value) {
	v.Clear();
	sign = true;

	v[0] = static_cast<DWORD>(value);
	v[1] = static_cast<DWORD>(value >> 32);
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

/// @brief GetSize - Permets de connaitre la taille en mots
///
/// @return La taille (en mots) du nombre stocké.
DWORD Int::GetSize() const {
	return v.GetSize();
}

/// @brief GetL32 - Récupère le mot de poids faible
///
/// @return Un DWORD représentant le mot de poids faible du nombre stocké.
DWORD Int::GetL32() const {
	if (v.IsEmpty() || (v.GetSize() == 1 && v[0] == 0)) return 0;

	return v[0];
}

/// @brief GetL64 - Récupère les 64 bits de poids faible
///
/// @return Un QWORD représentant les 64 bits de poids faible du nombre stocké.
QWORD Int::GetL64() const {
	const QWORD p0 = (!v.IsEmpty())    ? v[0] : 0;
	const QWORD p1 = (v.GetSize() > 1) ? v[1] : 0;

	return ((p1 << 32) | p0);
}

/// @brief GetOpposite - Récupère l'opposé du nombre stocké
///
/// @return L'opposé du nombre stocké.
Int Int::GetOpposite() const {
	const DWORD m = v.GetSize();
	Int ret;

	ret.v.SetCapacity(m, 0);
	for (QWORD i = 0; i < m; i = i + 1) ret.v[i] = v[i];

	ret.sign = !sign;
	return ret;
}

/// @brief GetStr - Convertit le nombre stocké en chaine de caractères
///
/// @return Une chaîne de caractères décimaux représentant le nombre stocké.
std::string Int::GetStr() const {
	if (v.GetSize() == 1 && v[0] == 0) return "0";

	DTable<DWORD> blks; blks.Clear();
	std::string ret = "";
	char tbuf[10];
	QWORD a, r;
	Int tA;

	tA.v.Clear(); tA.v.SetCapacity(v.GetSize(), 0);
	for (QWORD i = 0; i < v.GetSize(); i = i + 1) tA.v[i] = v[i];

	while (!tA.IsZero()) {
		r = 0;
		for (sQWORD i = tA.v.GetSize() - 1; i >= 0; i = i - 1) {
			a       = (r << 32) | tA.v[i];
			tA.v[i] = static_cast<DWORD>(a / bs109);
			r       = a % bs109;
		}

		blks[blks.GetSize()] = static_cast<DWORD>(r);
		tA.Normalize();
	}

	if (!sign) ret += "-";

	bool fblk = true;
	for (sQWORD i = blks.GetSize() - 1; i >= 0; i = i - 1) {
		if (fblk) {
			ret += toString<DWORD>(blks[i]);
			fblk = false;
		} else {
			snprintf(tbuf, sizeof(tbuf), "%09u", blks[i]);
			ret += tbuf;
		}
	}

	return ret;
} // OPTIMISATION IA => Calcul avec division 10^9 (pas intuitif en algorithmique)

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

QWORD Int::BitLength() const {
	const DWORD ns = v.GetSize();

	return ((32 * ns) - __builtin_clz(v[ns - 1]));
}

Bit Int::GetBit(const QWORD n) const {
	const DWORD ns = v.GetSize();
	const QWORD nbl = n / 32, nbb = n % 32;

	if (const QWORD nb = (32 * ns) - __builtin_clz(v[ns - 1]); n >= nb) return {};
	const DWORD x = v[nbl];

	return Bit((x >> nbb) & 1u);
}

void Int::SetBit(const QWORD n, const Bit &b) {
	const DWORD ns = v.GetSize();
	const QWORD nbl = n / 32, nbb = n % 32;

	if (const QWORD nb = (32 * ns) - __builtin_clz(v[ns - 1]); n < nb) {
		const DWORD x = v[nbl];
		v[nbl] = ((x & ~(1u << nbb)) | (static_cast<DWORD>(b.GetValue()) << nbb));
	}
}

/// @brief TrailZero - Compte le nombre de zéros à partir du LSB
///
/// @return Le nombre de zéros de poids faible.
DWORD Int::TrailZero() const {
	const DWORD n = v.GetSize();
	DWORD ret = 0, c, i = 0;

	for (QWORD j = 0; j < n; j = j + 1) {
		// ReSharper disable once CppJoinDeclarationAndAssignment
		c = v[i];

		if (c != 0) {
			ret += __builtin_ctz(c);
			break;
		}

		ret += 32;
		i   += 1;
	}

	return ret;
}

/// @brief DivMod - Donne le quotient et le reste d'une div euclidienne
///
/// @param A: l-value
/// @param B: r-value
///
/// @return Une Pair avec First qui est le quotient (A / B) et Second qui est le reste (A % B)
///
/// /!\ Ne fait pas appel aux opérateurs, recréer la logique des op / et %.
Pair<Int, Int> Int::DivMod(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize(), nq = nA - nB + 1, nr = nB;
	Int Q, R;

	Q.v.SetCapacity(nq, 0);
	R.v.SetCapacity(nr, 0);

	Pair<Int, Int> tqr = Div(A, B);
	Q = tqr.First(); R = tqr.Second();

	Q.Normalize(); R.Normalize();
	return {Q, R};
}


/// @brief Square - Applique une puissance de 2
///
/// @param A: u-value
///
/// @return Un Int représentant A^2.
///
/// /!\ Ne fait pas appel aux opérateurs, bypass la gestion à une fonction interne.
Int Int::Square(const Int& A) {
	return Sqr(A, A.sign, A.sign);
}

/// @brief operator= - Opérateur d'affectation entre Int
///
/// @param[in] other: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator=(const Int &other) {
	const DWORD n = other.v.GetSize();
	v.Clear(); sign = other.sign;

	v.SetCapacity(n, 0);
	for (QWORD i = 0; i < n; i = i + 1) v[i] = other.v[i];

	return *this;
}

/// @brief operator= - Opérateur d'affectation de chaine
///
/// @param[in] tstr: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator=(const std::string &tstr) {
	if (tstr.empty()) return *this;

	DTable<DWORD> dblk;
	// ReSharper disable two CppJoinDeclarationAndAssignment
	DWORD strt, len;
	QWORD carry, c;
	dblk.Clear();

	size_t p = 0;
	if (tstr[0] == '-') {
		sign = false;
		p = 1;
	} else if (tstr[0] == '+') {
		sign = true;
		p = 1;
	} else sign = true;

	std::string str = tstr.substr(p);

	const DWORD strs = str.size();
	for (sDWORD i = strs; i > 0; i -= 9) {
		strt = ((i - 9) > 0) ? (i - 9) : 0;
		len  = i - strt;

		dblk[dblk.GetSize()] = std::stoul(str.substr(strt, len));
	}

	v.Clear(); carry = 0;
	while (!(dblk.GetSize() == 1 && dblk[0] == 0)) {
		carry = 0;

		for (sDWORD i = dblk.GetSize() - 1; i >= 0; i = i - 1) {
			c = dblk[i] + carry * bs109;
			dblk[i] = static_cast<DWORD>(c / b32);
			carry = c % b32;
		}

		v[v.GetSize()] = static_cast<DWORD>(carry);
		while (dblk.GetSize() > 1 && dblk[dblk.GetSize() - 1] == 0) dblk.Erase(dblk.GetSize() - 1);
	}

	return *this;
} // OPTIMISATION IA => Calcul avec division 10^9 (pas intuitif en algorithmique)

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

/// @brief operator= - Opérateur d'affectation unitaire sur QWORD
///
/// @param[in] other: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator=(const QWORD other) {
	v.Clear(); sign = true;

	v[0] = static_cast<DWORD>(other);
	v[1] = static_cast<DWORD>(other >> 32);

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
Int& Int::operator+=(const Int &B) {
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
Int& Int::operator-=(const Int &B) {
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
		if (const sDWORD c = CmpAbs(A, B); c == 0) {
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
Int& Int::operator*=(const Int &B) {
	const DWORD nA = v.GetSize(), nB = B.v.GetSize();
	Int A, tA, tB;
	bool tie = true;

	A.v.SetCapacity(nA, 0);
	for (QWORD i = 0; i < nA; i = i + 1) A.v[i] = v[i];
	A.sign = sign;

	{
		if (nA != nB) tie = false;

		for (QWORD i = 0; i < nA; i = i + 1) {
			if (A.v[i] != B.v[i]) tie = false;
		}
	} // No call to CmpAbs or similar for optimize stack exchange + Constant-time compare

	if (tie) {
		tA = Sqr(A, A.sign, B.sign);
		const DWORD ntA = tA.v.GetSize();

		for (QWORD i = 0; i < ntA; i = i + 1) v[i] = tA.v[i];
	} else {
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
	}

	Normalize();
	return *this;
}

/// @brief operator/= - Opérateur d'affectation divisible
///
/// @param[in] B: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator/=(const Int &B) {
	const DWORD nA = v.GetSize(), nB = B.v.GetSize(), nr = nA - nB + 1;
	Int ret, A;

	A.v.SetCapacity(nA, 0);
	for (QWORD i = 0; i < v.GetSize(); i = i + 1) A.v[i] = v[i];
	A.sign = sign;

	ret.v.SetCapacity(nr, 0);

	Pair<Int, Int> tqr = Div(A, B);
	ret = tqr.First();

	v.Clear(); const DWORD nrt = ret.v.GetSize();
	for (QWORD i = 0; i < nrt; i = i + 1) v[i] = ret.v[i];
	sign = ret.sign;

	Normalize();
	return *this;
}

Int Int::Add(const Int &A, const Int &B) {
	Int ret;
	// ReSharper disable three CppJoinDeclarationAndAssignment
	QWORD carry = 0, a, b, sum;
	const DWORD n = (A.v.GetSize() > B.v.GetSize()) ? A.v.GetSize() : B.v.GetSize(), nA = A.v.GetSize(), nB = B.v.GetSize();

	ret.v.SetCapacity(n, 0);

	for (QWORD i = 0; i < n; i = i + 1) {
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
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize();
	// ReSharper disable three CppJoinDeclarationAndAssignment
	sQWORD borrow = 0, a, b, tsub;
	Int ret;

	ret.v.SetCapacity(nA, 0);

	for (QWORD i = 0; i < nA; i = i + 1) {
		a = A.v[i];
		b = (i < nB) ? B.v[i] : 0;
		tsub = a - b - borrow;

		if (tsub < 0) {
			tsub += b32;
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

Int Int::Sqr(const Int &A, const bool sA, const bool sB) {
	const DWORD nA = A.v.GetSize();
	Int tA, ret;

	tA.v.SetCapacity(A.v.GetSize(), 0);
	ret.v.SetCapacity(2 * nA, 0);

	for (QWORD i = 0; i < nA; i = i + 1) tA.v[i] = A.v[i];
	tA.sign = true;

	if (nA <= 64) ret = LongSqr(tA);
	else          ret = KaratsubaSqr(tA);

	ret.sign = (sA == sB);

	ret.Normalize();
	return ret;
}

Pair<Int, Int> Int::Div(const Int &A, const Int &B) {
	const DWORD m = A.v.GetSize(), n = B.v.GetSize();
	Pair<Int, Int> tqr;
	Int tA, tB, Q, R;
	bool calcdv = true, calck = true;

	tA.v.SetCapacity(m, 0); tB.v.SetCapacity(n, 0);
	for (QWORD i = 0; i < m; i = i + 1) tA.v[i] = A.v[i];
	for (QWORD i = 0; i < n; i = i + 1) tB.v[i] = B.v[i];

	tA.sign = true; tB.sign = true;

	if (B.IsZero()) throw std::runtime_error("Division by zero");
	if (A.IsZero() || CmpAbs(A, B) == -1) {
		Q = 0; R = A;
		calcdv = false;
	}
	if (B == Int(1)) {
		Q = A; R = 0;
		Q.sign = (A.sign == B.sign);
		calcdv = false;
	}

	if (const Int tts = Sub(tA, tB); tts == tB) {
		Q = 2; R = 0;
	} else if (tts < tB) {
		Q = 1; R = tts;
	} else {
		if (calcdv) {
			if (n == 1) {
				Pair<Int, DWORD> tqrp = SmallDiv(A, B.v[0]);
				Q = tqrp.First(); R = tqrp.Second();

				calck = false;
			}

			if (calck) {
				tqr = KnuthD(tA, tB);

				Q = tqr.First(); R = tqr.Second();
			}
		}
	}

	Q.sign = (A.sign == B.sign);
	R.sign = A.sign;

	Q.Normalize(); R.Normalize();
	return {Q, R};
}

Int Int::KaratsubaSqr(const Int &A) {
	const DWORD n = A.v.GetSize();
	const DWORD m = (n + 1) / 2;

	if (n <= 64) return LongSqr(A);

	const Int A0 = A.Slice(0, m).ExtByZero(m);
	const Int A1 = A.Slice(m, A.v.GetSize() - m);

	const Int z0 = KaratsubaSqr(A0);
	Int z1       = KaratsubaSqr(A0 + A1);
	const Int z2 = KaratsubaSqr(A1);
	z1 = z1 - z0 - z2;

	Int ret = z0 + z1.WShift(m) + z2.WShift(2 * m);

	ret.Normalize();
	return ret;
}

Int Int::LongSqr(const Int &A) {
	const DWORD n = A.v.GetSize(), n2 = 2 * n;
	QWORD p, b, im, i, j;
	SWORD acc = 0, carry = 0, ai, aj;
	Int ret;

	ret.v.SetCapacity(n2 + 8, 0);

	const DWORD tnk = n2 - 1;
	for (DWORD k = 0; k < tnk; k = k + 1) {
		im  = (k >= (n - 1)) ? (k - (n - 1)) : 0;
		acc = carry;

		i = im; j = k - i; ai = A.v[i]; aj = A.v[j];
		while (i < j) {
			acc += (ai * aj << 1);
			i += 1; j -= 1;

			ai = A.v[i]; aj = A.v[j];
		}

		if (i == j && i < n) acc += (ai * aj);

		ret.v[k] = static_cast<DWORD>(acc);
		carry    = (acc >> 32);
	}

	b = tnk;
	while (carry) {
		p = static_cast<QWORD>(ret.v[b])
		  + static_cast<QWORD>(carry & 0xFFFFFFFFFFFFFFFFull);
		ret.v[b] = static_cast<DWORD>(p);
		carry = (carry >> 32) + static_cast<SWORD>(p >> 32);

		b += 1;
	}

	ret.Normalize();
	return ret;
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
} // OPTIMISATION IA => Calcul de z1 et B-Reduc

Int Int::LongMul(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize();
	QWORD carry = 0, p, b;
	Int ret;

	ret.v.SetCapacity(nA + nB, 0);

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

	if (B == 0) return Zero;
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
} // OPTIMISATION IA => Super algo, je ne connaissais pas :)

Pair<Int, Int> Int::KnuthD(const Int &A, const Int &B) {
	const DWORD n = B.v.GetSize(), lz = __builtin_clz(B.v[n - 1]);
	Int Q, R, Bq, tA(A.BLShift(lz)), tB(B.BLShift(lz));
	const DWORD m = tA.v.GetSize() - n, m1 = m + 1, nn1 = n - 1, nn2 = n - 2, mn2 = m + n + 2;
	QWORD num, d, qest, rest;

	Q.v.SetCapacity(m + 1, 0);
	R.v.SetCapacity(n, 0);

	for (sQWORD j = m1; j >= 0; j = j - 1) {
		tA.v.SetCapacity(m + n + 2, 0);
		for (QWORD i = tA.v.GetSize(); i < mn2; i = i + 1) tA.v[i] = 0;

		if (tA.v.GetSize() < mn2) throw std::runtime_error("Div Size Error: m=" + toString<DWORD>(m) + ", n="
																					+ toString<DWORD>(n) + ", sA="
																					+ toString<DWORD>(tA.v.GetSize()) + ".");

		num = (static_cast<QWORD>(tA.v[j + n]) << 32) + tA.v[j + n - 1];
		d   = tB.v[nn1];

		qest = num / d; rest = num % d;
		while (qest == b32 || ((qest * static_cast<QWORD>(tB.v[nn2])) > ((rest << 32) + tA.v[j + n - 2]))) {
			qest -= 1;
			rest += d;
			if (rest >= b32) break;
		}

		Bq = Mul(tB, Int(qest)).WShift(j);
		if (tA < Bq) {
			tA += tB.WShift(j);
			qest -= 1;
		}

		tA -= Bq;
		Q.v[j] = static_cast<DWORD>(qest);
	}

	R = tA.BRShift(lz);

	Q.Normalize(); R.Normalize();
	return {Q, R};
} // OPTIMISATION IA => Subtilités d'un algo que je connais bien (merci Mr Knuth, vous êtes Le Goat)

Pair<Int, DWORD> Int::SmallDiv(const Int &A, const DWORD B) {
	bool calcdv = true;
	QWORD r = 0, c;
	Int q;

	q.v.SetCapacity(A.v.GetSize(), 0);

	if (B == 0) throw std::runtime_error("Division by zero");
	if (CmpAbs(A, Int(B)) == -1) {
		q = 0; r = A.v[0];
		calcdv = false;
	}

	if (calcdv) {
		for (sQWORD i = A.v.GetSize() - 1; i >= 0; i = i - 1) {
			c = (r << 32) | A.v[i];
			q.v[i] = static_cast<DWORD>(c / B);
			r = c % B;
		}
	}

	q.Normalize();
	return {q, static_cast<DWORD>(r)};
} // OPTIMISATION IA => Idem que SmallMul

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

Int Int::Abs() const {
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

	ret.sign = sign;
	return ret;
}

Int Int::BLShift(const DWORD b) const {
	const DWORD nw = b / 32, nb = b % 32, asize = v.GetSize(), fi = asize + nw + (nb ? 1 : 0);
	DWORD c = 0;
	QWORD x;
	Int ret;

	if (IsZero() || b == 0) {
		for (QWORD i = 0; i < asize; i = i + 1) ret.v[i] = v[i];
		ret.Normalize();
		return ret;
	}

	ret.v.SetCapacity(fi, 0);
	for (QWORD i = 0; i < asize; i = i + 1) {
		x = (static_cast<QWORD>(v[i]) << nb) | c;
		ret.v[i + nw] = static_cast<DWORD>(x);

		c = static_cast<DWORD>(x >> 32);
	}

	if (nb && c != 0) ret.v[asize + nw] = c;

	ret.Normalize();
	return ret;
}

Int Int::BRShift(const DWORD b) const {
	const DWORD nw = b / 32, nb = b % 32, asize = v.GetSize(), fi = asize - nw, nb32 = 32 - nb;
	DWORD c = 0, xc;
	Int ret;

	if (IsZero() || b == 0) {
		for (QWORD i = 0; i < asize; i = i + 1) ret.v[i] = v[i];
		ret.Normalize();
		return ret;
	}

	if (b >= (asize * 32)) return {0};

	ret.v.SetCapacity(fi, 0);
	for (sQWORD i = fi - 1; i >= 0; i = i - 1) {
		xc = static_cast<QWORD>(v[i + nw]);
		ret.v[i] = static_cast<DWORD>((xc >> nb) | (static_cast<QWORD>(c) << nb32));
		c = static_cast<DWORD>(xc & ((1ULL << nb) - 1));
	}

	ret.Normalize();
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




Int Int::BarrettReduce(const Int &T, const Int &N, const Int &Mu) {
	const DWORD k = N.v.GetSize(), ts = T.v.GetSize(), km1 = k - 1, kp1 = k + 1;
	Int q1, q2, q3, r1, r2, ret, q3n, bk1;

	bk1.v.SetCapacity(k + 2, 0);
	bk1.v[k + 1] = 1;

	q1 = T.BRShift(32 * km1);
	q2 = Mul(q1, Mu);
	q3 = q2.BRShift(32 * kp1);

	r1.v.SetCapacity(kp1, 0);
	for (QWORD i = 0; i < kp1; i = i + 1) r1.v[i] = (i < ts) ? T.v[i] : 0;

	r2.v.SetCapacity(kp1, 0);
	q3n = Mul(q3, N); const DWORD q3ns = q3n.v.GetSize();
	for (QWORD i = 0; i < kp1; i = i + 1) r2.v[i] = (i < q3ns) ? q3n.v[i] : 0;

	ret = r1 - r2;
	if (!ret.sign) ret += bk1;

	while (ret >= N) ret -= N;

	ret.Normalize();
	return ret;
}

/// @brief GetMu - Calcule la constante Mu d'un module
///
/// @param[in] N: module
///
/// @return La constante Mu liée à [N].
Int GetMu(const Int &N) {
	const DWORD k = N.v.GetSize();

	Int b2k;
	b2k.v.SetCapacity(2 * k + 1, 0);
	b2k.v[2 * k] = 1;

	Int Mu = b2k / N;

	Mu.Normalize();
	return Mu;
}

/// @brief MMul - Opérateur de multiplication Barrett
///
/// @param[in] A: l-value
/// @param[in] B: r-value
/// @param[in] N: module
/// @param[in] Mu: constante liée à [N]
///
/// @return Le résultat de ([A] * [B]) % [N].
///
/// /!\ [A] et [B] doivent être positifs et avoir une taille < ou = à celle de N.
Int MMul(const Int &A, const Int &B, const Int &N, const Int &Mu) {
	const Int T = Int::Mul(A, B);

	return Int::BarrettReduce(T, N, Mu);
}

/// @brief MSqr - Opérateur de mise au carré Barrett
///
/// @param[in] A: u-value
/// @param[in] N: module
/// @param[in] Mu: constante liée à [N]
///
/// @return Le résultat de [A]^2 % [N].
///
/// /!\ [A] doit être positif et avoir une taille < ou = à celle de N.
Int MSqr(const Int &A, const Int &N, const Int &Mu) {
	const Int T = Int::Sqr(A, A.sign, A.sign);

	return Int::BarrettReduce(T, N, Mu);
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
	bool tie = true;

	{
		if (nA != nB) tie = false;

		for (QWORD i = 0; i < nA; i = i + 1) {
			if (A.v[i] != B.v[i]) tie = false;
		}
	} // No call to CmpAbs or similar for optimize stack exchange + Constant-time compare

	if (tie) {
		ret = Int::Sqr(A, A.sign, B.sign);
	} else {
		tA.sign = true, tB.sign = true;

		tA.v.SetCapacity(nA, 0); tB.v.SetCapacity(nB, 0);
		for (QWORD i = 0; i < nA; i = i + 1) tA.v[i] = A.v[i];
		for (QWORD i = 0; i < nB; i = i + 1) tB.v[i] = B.v[i];

		ret.v.SetCapacity(nr, 0);
		tA.Normalize(); tB.Normalize();

		ret = Int::Mul(tA, tB);
		ret.sign = (A.sign == B.sign);
	}

	ret.Normalize();
	return ret;
}

/// @brief operator/ - Opérateur de division
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le quotient de la division euclidienne de [A] par [B].
Int operator/(const Int &A, const Int &B) {
	const DWORD nA = A.v.GetSize(), nB = B.v.GetSize(), nr = nA - nB + 1;
	Int ret;

	ret.v.SetCapacity(nr, 0);

	Pair<Int, Int> tqr = Int::Div(A, B);
	ret = tqr.First();

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
	const DWORD nB = B.v.GetSize(), nr = nB;
	Int ret;

	ret.v.SetCapacity(nr, 0);
	if (B == Int(2)) return {A.v[0] & 1};

	Pair<Int, Int> tqr = Int::Div(A, B);
	ret = tqr.Second();

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
	for (QWORD i = 0; i < nw; i = i + 1) ret.v[i] = 0;

	ret.sign = A.sign;
	ret.Normalize();

	return ret;
} // OPTIMISATION IA => Prise en compte des nombres négatifs

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

	if (b >= (asize * 32)) return ((A.sign) ? Int(0) : Int(-1));

	ret.v.SetCapacity(fi, 0);
	for (QWORD i = fi; i > 0; i = i - 1) {
		xc = A.v[i - 1 + nw];
		ret.v[i - 1] = (xc >> nb) | c;

		c = nb ? (xc << nb32) : 0;
	}

	ret.sign = A.sign;
	if (!A.sign) {
		Int ob(1); ob = ob << b;
		if (!((A % ob).IsZero())) ret -= Int(1);
	}

	ret.Normalize();
	return ret;
} // OPTIMISATION IA => Prise en compte des nombres négatifs

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
} // OPTIMISATION IA => Opti justement, sur les différents if/else

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
} // OPTIMISATION IA => Opti justement, sur les différents if/else

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

