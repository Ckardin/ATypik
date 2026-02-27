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

/// @file Math.cpp
/// @brief Source de Math
/// @author F&nµx
/// @version 3.0
/// @date 08/01/2025

#include "Math.h"

namespace Fenyx::Types
{

/// @brief NaivePow - Exponentiation naive
///
/// @param[in] a: base
/// @param[in] b: exposant
///
/// @return Un Int correspondant à [a] puissance [b].
Int NaivePow    (const Int &a, const DWORD b) {
	Int p(1);

	for (QWORD i = 1; i <= b; i = i + 1) p *= a;

	return p;
}

/// @brief Pow - Exponentiation rapide
///
/// @param[in] x: base
/// @param[in] n: exposant
///
/// @return Un Int correspondant à [x] puissance [n].
Int Pow         (const Int &x, const Int &n) {
	Int p = 1, a = x, e = n;

	if (n == Zero || x == One)  return One;
	if (n < Zero  || x == Zero) return Zero;
	if (n == One)               return x;

	if (n < 20 && x < 1000) return NaivePow(x, n.GetL64());

	while (!e.IsZero()) {
		if (e.IsOdd()) p *= a;

		e = e >> 1;
		if (!e.IsZero()) a = Int::Square(a);
	}

	return p;
}

/// @brief Pow2 - Exponentiation avec une base 2
///
/// @param[in] n: puissance à appliquer
///
/// @return Un Int correspondant à 2 puissance [n].
Int Pow2        (const DWORD n) {
	return (One << n);
}

/// @brief Pow16 - Exponentiation avec une base 16
///
/// @param[in] n: puissance à appliquer
///
/// @return Un Int correspondant à 16 puissance [n].
Int Pow16       (const DWORD n) {
	return (One << (4 * n));
}

/// @brief PowM - Exponentiation modulaire rapide (avec boucle for)
///
/// @param[in] a: base
/// @param[in] b: exposant
/// @param[in] m: module
/// @param[in] mu: valeur liée au module
///
/// @return Un Int correspondant à ([a] puissance [b]) modulo [m].
Int PowM        (const Int &a, const Int &b, const Int &m, const Int &mu) {
	Int p, x = a, n = b;

	for (p = 1; n > Zero; n = n >> 1) {
		if (n.IsOdd()) p = MMul(p, x, m, mu);
		x = MSqr(x, m, mu);
	}

	return p;
}

/// @brief ExtEuclide - Algorithme d'Euclide étendu
///
/// @param[in] a: nombre 1
/// @param[in] b: nombre 2
/// @param[out] u: coefficient de Bézout de a
/// @param[out] v: coefficient de Bézout de b
///
/// @return Le PGCD de [a] et [b].
Int ExtEuclide  (const Int &a, const Int &b, Int &u, Int &v) {
	if (a.IsZero() && b.IsZero()) {
		u = Zero; v = Zero;
		return Zero;
	}

	Int signA = (a < Zero) ? -1 : 1;
	Int signB = (b < Zero) ? -1 : 1;

	if (a.IsZero()) {
		u = Zero; v = signB;
		return b;
	}
	if (b.IsZero()) {
		u = signA; v = Zero;
		return a;
	}

	Int rp = a, r = b, sp = 1, s = 0, tp = 0, t = 1;
	Int q = 0, tr = 0, ts = 0, tt = 0, rem = 0;

	while (!r.IsZero()) {
		q = rp / r;
		rem = rp - q * r;

		if (rem < Zero) {
			rem += r.Abs();
			q   -= (r > Zero) ? One : Int(-1);
		}

		tr = r; r = rem;        rp = tr;
		ts = s; s = sp - q * s; sp = ts;
		tt = t; t = tp - q * t; tp = tt;
	}

	if (rp < Zero) {
		rp = rp.GetOpposite();
		sp = sp.GetOpposite();
		tp = tp.GetOpposite();
	}

	u = sp; v = tp;
	return rp;
}

Int Stein       (const Int &a, const Int &b) {
	if (a.IsZero()) return b.Abs();
	if (b.IsZero()) return a.Abs();

	DWORD shift = 0;
	Int A(a.Abs()), B(b.Abs());

	while (A.IsEven() && B.IsEven()) {
		A = A >> 1; B = B >> 1;
		shift += 1;
	}

	while (!A.IsZero()) {
		while (A.IsEven()) A = A >> 1;
		while (B.IsEven()) B = B >> 1;

		if (A >= B) A -= B;
		else        B -= A;
	}

	return (B << shift);
}

/// @brief SquareRt - Donne la racine carrée d'un DWORD
///
/// @param[in] n: nombre concerné
///
/// @return La racine carrée de [n].
///
/// /!\ Utilise l'algorithme rapide (avec manipulation des bits).
DWORD SquareRt(const DWORD n) {
	DWORD a = 0, b = n, d = 0;

	for (DWORD c = 1 << 30; c; c >>= 2) {
		d = a + c; a >>= 1;

		if (b >= d) {
			b -= d; a += c;
		}
	}

	return a;
}


/// @brief Complex - Constructeur par défaut
///
/// Constructeur par défaut de la classe Complex.
Complex::Complex() {
	re = im = 0;
}

/// @brief Complex - Constructeur d'affectation
///
/// @param[in] r: partie réelle
/// @param[in] u: partie imaginaire
///
/// Constructeur d'affectation de la classe Complex.
Complex::Complex(const Int &r, const Int &u) {
	re = r; im = u;
}

/// @brief Complex - Constructeur de copie
///
/// @param[in] oth: nombre complexe à copier
///
/// Constructeur de copie de la classe Complex.
Complex::Complex(const Complex &oth) {
	re = oth.re; im = oth.im;
}

/// @brief IsReal - Test si le nombre complexe est "réel pur"
///
/// @return true si le nombre est "réel pur", false sinon.
bool Complex::IsReal() const {
	return (im == Zero);
}

/// @brief IsImag - Test si le nombre complexe est "imaginaire pur"
///
/// @return true si le nombre est "imaginaire pur", false sinon
bool Complex::IsImag() const {
	return (re == Zero);
}

/// @brief Real - Récupères la partie réelle d'un nombre complexe
///
/// @return La partie réelle du nombre complexe.
Int Complex::Real() const {
	return re;
}

/// @brief Imag - Récupères la partie imaginaire d'un nombre complexe
///
/// @return La partie imaginaire du nombre complexe.
Int Complex::Imag() const {
	return im;
}

/// @brief operator= - Opérateur d'affectation
///
/// @param[in] oth: nombre à affecter
///
/// @return Une référence sur le Complex affecté.
Complex& Complex::operator=(const Complex &oth) = default;

/// @brief operator+= - Opérateur d'affectation additive
///
/// @param[in] oth: Complex à affecter
///
/// @return Une référence sur le Complex affecté.
Complex& Complex::operator+=(const Complex &oth) {
	re = re + oth.re; im = im + oth.im;
	return *this;
}

/// @brief operator-= - Opérateur de soustraction avec affectation
///
/// @param[in] oth: Complex à affecter
///
/// @return Une référence sur le Complex affecté.
Complex& Complex::operator-=(const Complex &oth) {
	re = re - oth.re; im = im - oth.im;
	return *this;
}

/// @brief operator*= - Opérateur d'affectation multiplicative
///
/// @param[in] oth: Complex à affecter
///
/// @return Une référence sur le Complex affecté.
Complex& Complex::operator*=(const Complex &oth) {
	re = (re * oth.re) - (im * oth.im);
	im = (re * oth.im) + (im * oth.re);
	return *this;
}

/// @brief operator/= - Opérateur d'affectation divisant
///
/// @param[in] oth: Complex à affecter
///
/// @return Une référence sur le Complex affecté.
Complex& Complex::operator/=(const Complex &oth) {
	const Complex conjugate(oth.re, Int(oth.im).GetOpposite());
	const Complex div_d((re * conjugate.re) - (im * conjugate.im), (re * conjugate.im) + (im * conjugate.re));
	const Int div_c = (oth.re * oth.re) - (oth.im * oth.im);

	re = div_d.re / div_c;
	im = div_d.im / div_c;

	return *this;
}


/// @brief operator+ - Opérateur d'addition
///
/// @param[in] lhs: lhs
/// @param[in] rhs: rhs
///
/// @return Un Complex égal à (lhs + rhs).
Complex operator+(const Complex &lhs, const Complex &rhs) {
	Complex ret;

	ret.re = lhs.re + rhs.re;
	ret.im = lhs.im + rhs.im;

	return ret;
}

/// @brief operator- - Opérateur de soustraction
///
/// @param[in] lhs: lhs
/// @param[in] rhs: rhs
///
/// @return Un Complex égal à (lhs - rhs).
Complex operator-(const Complex &lhs, const Complex &rhs) {
	Complex ret;

	ret.re = lhs.re - rhs.re;
	ret.im = lhs.im - rhs.im;

	return ret;
}

/// @brief operator* - Opérateur de multiplication
///
/// @param[in] lhs: lhs
/// @param[in] rhs: rhs
///
/// @return Un Complex égal à (lhs * rhs).
Complex operator*(const Complex &lhs, const Complex &rhs) {
	Complex ret;

	ret.re = (lhs.re * rhs.re) - (lhs.im * rhs.im);
	ret.im = (lhs.re * rhs.im) + (lhs.im * rhs.re);

	return ret;
}

/// @brief operator/ - Opérateur de division
///
/// @param[in] lhs: lhs
/// @param[in] rhs: rhs
///
/// @return Un Complex égal à (lhs / rhs).
Complex operator/(const Complex &lhs, const Complex &rhs) {
	const Complex conjugate(rhs.re, Int(rhs.im).GetOpposite());
	const Complex div_d((lhs.re * conjugate.re) - (lhs.im * conjugate.im), (lhs.re * conjugate.im) + (lhs.im * conjugate.re));
	const Int div_c = (rhs.re * rhs.re) - (rhs.im * rhs.im);
	Complex ret;

	ret.re = lhs.re / div_c;
	ret.im = lhs.im / div_c;

	return ret;
}

/// @brief operator== - Test d'égalité entre Complex
///
/// @param[in] lhs: lhs
/// @param[in] rhs: rhs
///
/// @return true si égaux, false sinon.
bool operator==(const Complex &lhs, const Complex &rhs) {
	return ((lhs.re == rhs.re) && (lhs.im == rhs.im));
}

/// @brief operator!= - Opérateur d'inégalité entre Complex
///
/// @param[in] lhs: lhs
/// @param[in] rhs: rhs
///
/// @return true si différents, false sinon.
bool operator!=(const Complex &lhs, const Complex &rhs) {
	return ((lhs.re != rhs.re) || (lhs.im != rhs.im));
}

/// @brief operator<< - Opérateur de flux de sortie pour Complex
///
/// @param[in] os: flux de sortie
/// @param[in] rhs: Complex concerné
///
/// @return Une référence sur le flux de sortie affecté.
std::ostream& operator<<(std::ostream& os, const Complex &rhs) {
	const Int r = rhs.re;
	const Int i = rhs.im;

	os << "(" << r.GetStr() << " ";
	if (i < Zero) os << "- " << (Int(i).GetOpposite()).GetStr();
	else          os << "+ " << i.GetStr();
	os << "i)";

	return os;
}

}

