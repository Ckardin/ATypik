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

namespace Fenyx::Types
{

/// @brief Int - Constructeur
///
/// Constructeur de la classe Int.
Int::Int() {
	v.Clear();
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

	v[0] = (value > 0) ? value : 0 - value;
}

/// @brief Int - Constructeur
///
/// @param[in] other: valeur à copier
///
/// Constructeur de copie de la classe Int.
Int::Int(const Int& other) {
	v.Clear();
	sign = other.sign;

	for (QWORD i = 0; i < other.v.GetSize(); i = i + 1) v[i] = other.v[i];
}

/// @brief Int - Constructeur
///
/// @param[in] other: tableau de DWORD à affecter
/// @param[in] sg: signe du nombre à affecter
///
/// Constructeur d'affectation brute de la classe Int.
Int::Int(const DTable<DWORD> &other, bool sg) {
	v.Clear();
	sign = sg;

	for (QWORD i = 0; i < other.GetSize(); i = i + 1) v[i] = other[i];
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
	DTable<DWORD> ret;

	for (QWORD i = 0; i < v.GetSize(); i = i + 1) ret[i] = v[i];

	return ret;
}

/// @brief GetL64 - Récupère les 64 bits de poids faible
///
/// @return Un QWORD représentant les 64 bits de poids faible du nombre stocké.
QWORD Int::GetL64() {
	const QWORD p0 = (!v.IsEmpty())    ? v[0] : 0;
	const QWORD p1 = (v.GetSize() > 1) ? v[1] : 0;

	return ((p1 << 32) | p0);
}

/// @brief GetStr - Convertit le nombre stocké en chaine de caractères
///
/// @return Une chaîne de caractères décimaux représentant le nombre stocké.
std::string Int::GetStr() const {
	Int A;
	for (QWORD i = 0; i < v.GetSize(); i = i + 1) A.v[i] = v[i];
	std::string ret = "";
	// ReSharper disable once CppJoinDeclarationAndAssignment
	DWORD r;

	auto SmallDiv = [&A](const DWORD d) -> DWORD {
		QWORD rem = 0, cur = 0;

		for (sQWORD i = A.v.GetSize() - 1; i >= 0; i = i - 1) {
			cur = (rem << 32) | A.v[i];
			A.v[i] = static_cast<DWORD>(cur / d);
			rem = cur % d;
		}

		A.Normalize();

		return static_cast<DWORD>(rem);
	};

	while (!(A.IsZero())) {
		r = SmallDiv(10);
		ret.push_back(static_cast<char>('0' + r));
	}

	if (ret.empty()) ret = "0";
	else             std::reverse(ret.begin(), ret.end());

	if (!sign) ret.insert(ret.begin(), '-');

	return ret;
}

/// @brief IsZero - Test si le nombre vaut 0 ou pas
///
/// @return True si le nombre stocké vaut 0, false sinon.
bool Int::IsZero() const {
	return (v.GetSize() == 1 && v[0] == 0);
}

/// @brief operator= - Opérateur d'affectation entre Int
///
/// @param[in] other: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator=(const Int& other) {
	v.Clear();
	sign = other.sign;

	for (QWORD i = 0; i < other.v.GetSize(); i = i + 1) v[i] = other.v[i];

	return *this;
}

/// @brief operator= - Opérateur d'affectation unitaire
///
/// @param[in] other: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator=(const DWORD other) {
	v.Clear();
	sign = true;

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

	v[0] = (other > 0) ? other : 0 - other;

	return *this;
}

/// @brief operator+= - Opérateur d'affectation additif
///
/// @param[in] B: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator+=(const Int& B) {
	Int A;

	for (QWORD i = 0; i < v.GetSize(); i = i + 1) A.v[i] = v[i];
	A.sign = sign;

	Int ret = ChooseOpSign(A, B, 1);

	v.Clear();
	for (QWORD i = 0; i < ret.v.GetSize(); i = i + 1) v[i] = ret.v[i];
	sign = ret.sign;

	return *this;
}

/// @brief operator-= - Opérateur d'affectation soustractif
///
/// @param[in] B: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator-=(const Int& B) {
	Int A;

	for (QWORD i = 0; i < v.GetSize(); i = i + 1) A.v[i] = v[i];
	A.sign = sign;

	Int ret = ChooseOpSign(A, B, 2);

	v.Clear();
	for (QWORD i = 0; i < ret.v.GetSize(); i = i + 1) v[i] = ret.v[i];
	sign = ret.sign;

	return *this;
}

/// @brief operator*= - Opérateur d'affectation multiplicatif
///
/// @param[in] B: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator*=(const Int& B) {
	Int A;

	for (QWORD i = 0; i < v.GetSize(); i = i + 1) A.v[i] = v[i];
	A.sign = sign;

	Int ret = ChooseOpSign(A, B, 0);

	v.Clear();
	for (QWORD i = 0; i < ret.v.GetSize(); i = i + 1) v[i] = ret.v[i];
	sign = ret.sign;

	return *this;
}

/// @brief operator/= - Opérateur d'affectation divisible
///
/// @param[in] B: r-value
///
/// @return Une référence sur le Int affecté.
Int& Int::operator/=(const Int& B) {
	Int A;

	for (QWORD i = 0; i < v.GetSize(); i = i + 1) A.v[i] = v[i];
	A.sign = sign;

	Int ret = ChooseOpSign(A, B, 3);

	v.Clear();
	for (QWORD i = 0; i < ret.v.GetSize(); i = i + 1) v[i] = ret.v[i];
	sign = ret.sign;

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

Int Int::Add(const Int &A, const Int &B) {
	Int ret;
	// ReSharper disable three CppJoinDeclarationAndAssignment
	QWORD carry = 0, a, b, sum;
	const DWORD n = (A.v.GetSize() > B.v.GetSize()) ? A.v.GetSize() : B.v.GetSize();

	ret.v.SetCapacity(n);

	for (QWORD i = 0; i < n; i = i +1) {
		a = (i < A.v.GetSize()) ? A.v[i] : 0;
		b = (i < B.v.GetSize()) ? B.v[i] : 0;
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
	sQWORD borrow = 0, a, b, tsub;
	const DWORD n = A.v.GetSize();

	ret.v.SetCapacity(n);

	for (QWORD i = 0; i < n; i = i + 1) {
		a = A.v[i];
		b = (i < B.v.GetSize()) ? B.v[i] : 0;
		tsub = a - b - borrow;

		if (tsub < 0) {
			tsub += (1LL << 32);
			borrow = 1;
		} else borrow = 0;

		ret.v[i] = static_cast<DWORD>(tsub);
	}

	ret.Normalize();

	return ret;
}

Int Int::Karatsuba(const Int &A, const Int &B) {
	const DWORD n = (A.v.GetSize() > B.v.GetSize()) ? A.v.GetSize() : B.v.GetSize();
	const DWORD m = n / 2;

	if (n <= 32) return LongMul(A, B);

	const Int A0 = A.Slice(0, m);
	const Int A1 = A.Slice(m, A.v.GetSize() - m);
	const Int B0 = B.Slice(0, m);
	const Int B1 = B.Slice(m, B.v.GetSize() - m);

	Int z0 = Karatsuba(A0, B0);
	Int z1 = Karatsuba(A0 - A1, B0 - B1);
	Int z2 = Karatsuba(A1, B1);
	z1 = (z0 + z2) - z1;

	Int ret = (z0 << (2 * m * 32)) + (z1 << (m * 32)) + z2;

	/*const Int z0 = Karatsuba(A0, B0);
	const Int z2 = Karatsuba(A1, B1);
	Int z1       = Karatsuba(A0 + A1, B0 + B1);
	z1 -= z0;
	z1 -= z2;

	Int ret = (z2 << (2 * m * 32)) + (z1 << (m * 32)) + z0;*/

	ret.Normalize();

	return ret;
}

Int Int::LongMul(const Int &A, const Int &B) {
	QWORD carry = 0;
	SWORD cur;
	Int ret;

	ret.v.SetCapacity(A.v.GetSize() + B.v.GetSize());

	for (QWORD i = 0; i < A.v.GetSize(); i = i + 1) {
		carry = 0;

		for (QWORD j = 0; j < B.v.GetSize() || carry; j = j + 1) {
			cur = static_cast<SWORD>(ret.v[i + j])
			    + static_cast<SWORD>(A.v[i]) * ((j < B.v.GetSize()) ? B.v[j] : 0) + carry;

			ret.v[i + j] = static_cast<DWORD>(cur);
			carry = static_cast<QWORD>(cur >> 32);
		}
	}

	ret.Normalize();

	return ret;
}

Pair<Int, Int> Int::BurnikelZiegler(const Int &A, const Int &B) {
	if (B.IsZero()) throw std::runtime_error("Division by zero");
	if (A.IsZero()) return {Int(0), B};
	if (A < B)      return {Int(0), A};

	const DWORD n = A.v.GetSize();
	const DWORD k = n / 2;

	if (const DWORD m = B.v.GetSize(); n <= (2 * m)) return LongDiv(A, B);

	Int A0 = A.Slice(k, n - k);
	Int A1 = A.Slice(0, k);

	Pair<Int, Int> qrh = BurnikelZiegler(A0, B);
	Int rp = (qrh.Second() << (32 * k)) + A1;

	Pair<Int, Int> qrl = BurnikelZiegler(rp, B);
	Int Q = (qrh.First() << (32 * k)) + qrl.First();

	return {Q, qrl.Second()};
}

Pair<Int, Int> Int::LongDiv(const Int &A, const Int &B) {
	if (B.IsZero()) throw std::runtime_error("Division by zero");
	if (A.IsZero()) return {Int(0), B};
	if (A < B)      return {Int(0), A};

	QWORD q, rh0, rh1, bh, carry;
	SWORD t, t1;
	Int Q, R, P;
	Q.v.SetCapacity(A.v.GetSize());

	for (sQWORD i = A.v.GetSize() - 1; i >= 0; i = i - 1) {
		R = R << 32;

		if (!R.v.IsEmpty()) R.v[0] = A.v[i];
		else                R.v[R.v.GetSize()] = A.v[i];

		R.Normalize();

		q = 0;
		if (R >= B) {
			rh0 = (R.v.GetSize() > B.v.GetSize()) ? R.v[R.v.GetSize() - 1] : 0;
			rh1 = (R.v.GetSize() > (B.v.GetSize() - 1)) ? R.v[B.v.GetSize() - 1] : 0;
			bh  = B.v[B.v.GetSize() - 1];

			t = (static_cast<SWORD>(rh0) << 32) + rh1;
			q = (bh == 0) ? 0xFFFFFFFFull : static_cast<QWORD>(t / bh);
			if (q > 0xFFFFFFFFull) q = 0xFFFFFFFFull;

			P.v.SetCapacity(B.v.GetSize());
			carry = 0;
			for (QWORD j = 0; j < B.v.GetSize(); j = j + 1) {
				t1 = (static_cast<SWORD>(B.v[j]) * q) + carry;

				P.v[j] = static_cast<DWORD>(t1);
				carry  = static_cast<QWORD>(t1 >> 32);
			}

			if (carry) P.v[P.v.GetSize()] = static_cast<DWORD>(carry);
			P.Normalize();

			while (R < P) {
				q = q - 1;
				P -= B;
			}

			R -= P;
		}

		Q.v[i] = static_cast<DWORD>(q);
	}

	Q.Normalize();
	R.Normalize();

	return {Q, R};
}

sDWORD Int::CmpAbs(const Int &A, const Int &B) {
	if (A.v.GetSize() < B.v.GetSize()) return -1;
	if (A.v.GetSize() > B.v.GetSize()) return 1;

	for (sQWORD i = A.v.GetSize() - 1; i >= 0; i = i - 1) {
		if (A.v[i] < B.v[i]) return -1;
		if (A.v[i] > B.v[i]) return 1;
	}

	return 0;
}

Int Int::Slice(const DWORD strt, const DWORD len) const {
	Int ret;
	DWORD final = 0;

	if (strt >= v.GetSize()) {
		for (QWORD i = 0; i < v.GetSize(); i = i + 1) ret.v[i] = v[i];
	}
	if ((strt + len) > v.GetSize()) final = v.GetSize();
	else							final = strt + len;

	for (QWORD i = strt; i < final; i = i + 1) ret.v[i - strt] = v[i];

	return ret;
}

void Int::Normalize() {
	while (v.GetSize() > 1 && v[v.GetSize() - 1] == 0) v.Erase(v.GetSize() - 1);

	if (v.GetSize() == 0)              v[0] = 0;
	if (v.GetSize() == 1 && v[0] == 0) sign = true;
}

Int Int::ChooseOpSign(const Int &A, const Int &B, const BYTE op) {
	Int ret, tA, tB;

	tA.sign = true, tB.sign = true;
	for (QWORD i = 0; i < A.v.GetSize(); i = i + 1) tA.v[i] = A.v[i];
	for (QWORD i = 0; i < B.v.GetSize(); i = i + 1) tB.v[i] = B.v[i];

	if (op == 0) {
		ret = Karatsuba(tA, tB);
		ret.sign = (A.sign == B.sign);
	} else if (op == 1) {
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
	} else if (op == 2) {
		if (A.sign != B.sign) {
			ret = Add(A, B);
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
	} else if (op == 3) {
		Pair<Int, Int> qr = BurnikelZiegler(tA, tB);

		ret = qr.First();
		ret.sign = (A.sign == B.sign);
	} else if (op == 4) {
		Pair<Int, Int> qr = BurnikelZiegler(tA, tB);

		ret = qr.Second();
		ret.sign = true;
	} else {
		ret = Karatsuba(tA, tB);
		ret.sign = (A.sign == B.sign);
	}

	ret.Normalize();

	return ret;
}


/// @brief operator+ - Opérateur d'addition
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le résultat de [A] + [B].
Int operator+(const Int &A, const Int &B) {
	Int ret;

	ret = Int::ChooseOpSign(A, B, 1);

	return ret;
}

/// @brief operator- - Opérateur de soustraction
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le résultat de [A] - [B].
Int operator-(const Int &A, const Int &B) {
	Int ret;

	ret = Int::ChooseOpSign(A, B, 2);

	return ret;
}

/// @brief operator* - Opérateur de multiplication
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le résultat de [A] * [B].
Int operator*(const Int &A, const Int &B) {
	Int ret;

	ret = Int::ChooseOpSign(A, B, 0);

	return ret;
}

/// @brief operator/ - Opérateur de division
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le résultat de la division euclidienne de [A] par [B], uniquement le quotient.
Int operator/(const Int &A, const Int &B) {
	Int ret;

	ret = Int::ChooseOpSign(A, B, 3);

	return ret;
}

/// @brief operator% - Opérateur modulo
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le reste de la division euclidienne de [A] par [B].
Int operator%(const Int &A, const Int &B) {
	Int ret;

	ret = Int::ChooseOpSign(A, B, 4);

	return ret;
}

/// @brief operator<< - Opérateur de décalage à gauche
///
/// @param[in] A: l-value
/// @param[in] b: nombre de bits à décaler
///
/// @return Le résultat de l'opération binaire [A] << [b].
Int operator<<(const Int &A, DWORD b) {
	const DWORD sh_word = b / 32, sh_bits = b % 32;
	DWORD carry = 0;
	// ReSharper disable once CppJoinDeclarationAndAssignment
	QWORD temp;
	Int ret;

	for (QWORD i = 0; i < A.v.GetSize(); i = i + 1) {
		temp = (static_cast<QWORD>(A.v[i]) << sh_bits) | carry;
		ret.v[i + sh_word] = static_cast<DWORD>(temp & 0xFFFFFFFF);
		carry = static_cast<DWORD>(temp >> 32);
	}

	if (carry) ret.v[A.v.GetSize() + sh_word] = carry;

	return ret;
}

/// @brief operator>> - Opérateur de décalage à droite
///
/// @param[in] A: l-value
/// @param[in] b: nombre de bits à décaler
///
/// @return Le résultat de l'opération binaire [A] >> [b].
Int operator>>(const Int &A, DWORD b) {
	const DWORD sh_word = b / 32, sh_bits = b % 32;
	DWORD carry = 0;
	// ReSharper disable once CppJoinDeclarationAndAssignment
	QWORD temp;
	Int ret;

	if (sh_word >= A.v.GetSize()) return 0;

	for (sQWORD i = A.v.GetSize() - 1; (i + 1) > sh_word; i = i - 1) {
		temp = (static_cast<QWORD>(A.v[i]) << 32) >> sh_bits;
		temp |= carry;
		ret.v[i - sh_word] = static_cast<DWORD>(temp & 0xFFFFFFFF);
		carry = static_cast<DWORD>(static_cast<QWORD>(A.v[i]) >> sh_bits);
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
	const DWORD n = (A.v.GetSize() >= B.v.GetSize()) ? A.v.GetSize() : B.v.GetSize();
	Int ret;
	DWORD t0, t1;

	for (QWORD i = 0; i < n; i = i + 1) {
		// ReSharper disable once CppJoinDeclarationAndAssignment
		t0 = (i < A.v.GetSize()) ? A.v[i] : 0;
		// ReSharper disable once CppJoinDeclarationAndAssignment
		t1 = (i < B.v.GetSize()) ? B.v[i] : 0;

		ret.v[i] = t0 & t1;
	}

	return ret;
}

/// @brief operator| - Opérateur OU logique
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le résultat de l'opération binaire [A] | [B].
Int operator|(const Int &A, const Int &B) {
	const DWORD n = (A.v.GetSize() >= B.v.GetSize()) ? A.v.GetSize() : B.v.GetSize();
	Int ret;
	DWORD t0, t1;

	for (QWORD i = 0; i < n; i = i + 1) {
		// ReSharper disable once CppJoinDeclarationAndAssignment
		t0 = (i < A.v.GetSize()) ? A.v[i] : 0;
		// ReSharper disable once CppJoinDeclarationAndAssignment
		t1 = (i < B.v.GetSize()) ? B.v[i] : 0;

		ret.v[i] = t0 | t1;
	}

	return ret;
}

/// @brief operator^ - Opérateur XOR logique
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return Le résultat de l'opération binaire [A] ^ [B].
Int operator^(const Int &A, const Int &B) {
	const DWORD n = (A.v.GetSize() >= B.v.GetSize()) ? A.v.GetSize() : B.v.GetSize();
	Int ret;
	DWORD t0, t1;

	for (QWORD i = 0; i < n; i = i + 1) {
		// ReSharper disable once CppJoinDeclarationAndAssignment
		t0 = (i < A.v.GetSize()) ? A.v[i] : 0;
		// ReSharper disable once CppJoinDeclarationAndAssignment
		t1 = (i < B.v.GetSize()) ? B.v[i] : 0;

		ret.v[i] = t0 ^ t1;
	}

	return ret;
}

/// @brief operator== - Opérateur d'égalité entre Int
///
/// @param[in] A: l-value
/// @param[in] B: r-value
///
/// @return True si [A] = [B], false sinon.
bool operator==(const Int &A, const Int &B) {
	if (A.v.GetSize() != B.v.GetSize()) return false;
	if (A.sign != B.sign)               return false;

	for (QWORD i = 0; i < A.v.GetSize(); i = i + 1) {
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
	if (A.v.GetSize() != B.v.GetSize()) return true;
	if (A.sign != B.sign)               return true;

	for (QWORD i = 0; i < A.v.GetSize(); i = i + 1) {
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
	if (A.sign && !(B.sign)) return false;
	if (!(A.sign) && B.sign) return true;

	if (A.sign && B.sign) {
		if (A.v.GetSize() < B.v.GetSize()) return true;
		if (A.v.GetSize() > B.v.GetSize()) return false;

		for (sQWORD i = A.v.GetSize() - 1; i >= 0; i = i - 1) {
			if (A.v[i] < B.v[i]) return true;
			if (A.v[i] > B.v[i]) return false;
		}
	} else {
		if (A.v.GetSize() < B.v.GetSize()) return false;
		if (A.v.GetSize() > B.v.GetSize()) return true;

		for (sQWORD i = A.v.GetSize() - 1; i >= 0; i = i - 1) {
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
	if (A.sign && !(B.sign)) return true;
	if (!(A.sign) && B.sign) return false;

	if (A.sign && B.sign) {
		if (A.v.GetSize() < B.v.GetSize()) return false;
		if (A.v.GetSize() > B.v.GetSize()) return true;

		for (sQWORD i = A.v.GetSize() - 1; i >= 0; i = i - 1) {
			if (A.v[i] < B.v[i]) return false;
			if (A.v[i] > B.v[i]) return true;
		}
	} else {
		if (A.v.GetSize() < B.v.GetSize()) return true;
		if (A.v.GetSize() > B.v.GetSize()) return false;

		for (sQWORD i = A.v.GetSize() - 1; i >= 0; i = i - 1) {
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

