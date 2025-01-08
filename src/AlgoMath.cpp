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

/// @file AlgoMath.cpp
/// @brief Source de AlgoMath
/// @author F&nµx
/// @version 2.0
/// @date 08/01/2025

#include "AlgoMath.h"

namespace Fenyx::Types
{

/// @brief NaivePow - Exponentiation naive
///
/// @param[in] a: base
/// @param[in] b: exposant
///
/// @return Un InfInt correspondant à [a] puissance [b].
InfInt NaivePow    (InfInt const& a, InfInt const& b) {
	InfInt p = 1;

	for (InfInt i = 1; i <= b; i = i + 1) p *= a;

	return p;
}

/// @brief Pow - Exponentiation rapide
///
/// @param[in] x: base
/// @param[in] n: exposant
///
/// @return Un InfInt correspondant à [x] puissance [n].
InfInt Pow         (InfInt const& x, InfInt const& n) {
	InfInt p = 1, a = x, e = n;

	if (n == 0 || x == 1) return 1;
	if (n < 0  || x == 0) return 0;
	if (n == 1)             return x;

	if (n < 20 && x < 1000) NaivePow(x, n);

	while (e != 0) {
		if ((e % 2) == 0) {
			a = a * a;
			e = e / 2;
		} else {
			p = p * a;
			e = (e - 1);
		}
	}

	return p;
}

/// @brief Pow2 - Exponention avec une base 2
///
/// @param[in] n: puissance à appliquer
///
/// @return Un InfInt correspondant à 2 puissance [n].
InfInt Pow2        (InfInt const& n) {
	InfInt p = 1;

	for (InfInt i = 0; i < n; i = i + 1) p = p * 2;

	return p;
}

/// @brief Pow16 - Exponention avec une base 16
///
/// @param[in] n: puissance à appliquer
///
/// @return Un InfInt correspondant à 16 puissance [n].
InfInt Pow16       (InfInt const& n) {
	InfInt p = 1;

	for (InfInt i = 0; i < n; i = i + 1) p = p * 16;

	return p;
}

/// @brief W_PowM - Exponentiation modulaire rapide (avec boucle while)
///
/// @param[in] a: base
/// @param[in] b: exposant
/// @param[in] m: modulo
///
/// @return Un InfInt correspondant à ([a] puissance [b]) modulo [m].
InfInt W_PowM      (InfInt const& a, InfInt const& b, InfInt const& m) {
	InfInt p = 1, x = a, n = b;
	x = x % m;

	while (n > 0) {
		if ((n % 2) != 0) p = (p * x) % m;

		n = n / 2;
		x = (x * x) % m;
	}

	return p;
}

/// @brief F_PowM - Exponentiation modulaire rapide (avec boucle for)
///
/// @param[in] a: base
/// @param[in] b: exposant
/// @param[in] m: modulo
///
/// @return Un InfInt correspondant à ([a] puissance [b]) modulo [m].
InfInt F_PowM      (InfInt const& a, InfInt const& b, InfInt const& m) {
	InfInt p, x = a, n = b;

	for (p = 1; n > 0; n = n / 2) {
		if (n % 2 != 0) p = (p * x) % m;
		x = (x * x) % m;
	}

	return p;
}

/// @brief RandTestMR - Génère un témoin de Miller valide
///
/// @param[in] n: nombre concerné par le test
///
/// @return Témoin de Miller valide et pseudo-aléatoire.
///
/// /!\ Utilise random_device().
InfInt RandTestMR  (InfInt const& n) {
	std::random_device rd;
	InfInt ret = rd();

	ret = n % ret;
	if (ret >= (n - 2) || ret <= 2) ret = InfInt(2) + (ret % (n - 4));

	return ret;
}

/// @brief MillerTest - Effectue le Test de Miller-Rabin (sur un témoin)
///
/// @param[in] n: nombre à tester
/// @param[in] a: témoin de Miller
///
/// @return false si [n] est probablement premier, true sinon.
bool   MillerTest  (InfInt const& n, InfInt const& a) {
	InfInt d = n - 1;
	while ((d % 2) == 0) d /= 2;

	InfInt x = W_PowM(a, d, n);

	if (x == 1 || x == (n - 1)) return false;

	while (d != (n - 1)) {
		x = W_PowM(x, 2, n);
		d = d * 2;

		if (x == (n - 1)) return false;
	}

	return true;
}

/// @brief MillerRabin - Effectue le test de Miller-Rabin complet
///
/// @param[in] n: nombre à tester
/// @param[in] k: nombre d'itérations du test
///
/// @return true si [n] est probablement premier, false sinon.
bool   MillerRabin (InfInt const& n, const BYTE k) {
	if (n <= 1 || n == 4) return false;
	if (n <= 3)             return true;

	for (WORD i = 0; i < k; i = i + 1) {
		if (InfInt a = RandTestMR(n); MillerTest(n, a)) return false;
	}

	return true;
}

/// @brief Fermat_2 - Effectue le test de Fermat (en 2)
///
/// @param[in] n: nombre à tester
///
/// @return true si [n] est probablement premier, false sinon.
bool   Fermat_2    (InfInt const& n) {
	if (F_PowM(2, n - 1, n) == (InfInt(1) % n)) return true;
	return false;
}

/// @brief SolovayStrassen - Effectue le test de Solovay-Strassen
///
/// @param[in] n: nombre à tester
/// @param[in] k: nombre d'itérations du test
///
/// @return true si [n] est probablement premier, false sinon.
bool   SolovayStrassen(InfInt const& n, BYTE k) {
	const InfInt bt = (n - 1) - 2, m = (n - 1) / 2;
	InfInt a = 0, x = 0;
	std::random_device rd;

	for (WORD i = 0; i < k; i = i + 1) {
		a = (InfInt(rd()) * bt) + 2;
		x = a / n;

		if (x == 0 || (x % n) != (F_PowM(a, m, n))) return false;
	}

	return true;
}

/// @brief ExtEuclide - Algorithme d'Euclide étendu
///
/// @param[in] a: nombre 1
/// @param[in] b: nombre 2
/// @param[out] u: coefficient de Bézout
/// @param[out] v: coefficient de Bézout
///
/// @return Le PGCD de [a] et [b]
InfInt ExtEuclide  (InfInt const& a, InfInt const& b, InfInt &u, InfInt &v) {
	InfInt tr = a, tr_ = b, tu = 1, tv = 0, tu_ = 0, tv_ = 1;
	InfInt q = 0, rs = 0, us = 0, vs = 0;

	while (tr_ != 0) {
		q   = tr / tr_;
		rs  = tr;  us = tu;  vs  = tv;
		tr  = tr_; tu = tu_; tv  = tv_;
		tr_ = rs - (q * tr_); tu_ = us - (q * tu_); tv_ = vs - (q * tv_);
	}

	u = tu; v = tv;

	return tr;
}

/// @brief SquareRt - Donne la racine carrée d'un DWORD
///
/// @param[in] n: nombre concerné
///
/// @return La racine carrée de [n].
///
/// /!\ Utilise l'algorithme rapide (avec manipulation des bits).
DWORD SquareRt(DWORD n) {
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
Complex::Complex(InfInt const& r, InfInt const& u) {
	re = r; im = u;
}

/// @brief Complex - Constructeur de copie
///
/// @param[in] oth: nombre complexe de copie
///
/// Constructeur de copie de la classe Complex.
Complex::Complex(Complex const& oth) {
	re = oth.re; im = oth.im;
}

/// @brief IsReal - Test si le nombre complexe est "réel pur"
///
/// @return true si le nombre est "réel pur", false sinon.
bool Complex::IsReal() const {
	return (im == 0);
}

/// @brief IsImag - Test si le nombre complexe est "imaginaire pur"
///
/// @return true si le nombre est "imaginaire pur", false sinon
bool Complex::IsImag() const {
	return (re == 0);
}

/// @brief Real - Récupères la partie réelle d'un nombre complexe
///
/// @return La partie réelle du nombre complexe.
InfInt Complex::Real() const {
	return re;
}

/// @brief Imag - Récupères la partie imaginaire d'un nombre complexe
///
/// @return La partie imaginaire du nombre complexe.
InfInt Complex::Imag() const {
	return im;
}

/// @brief operator= - Opérateur d'affectation
///
/// @param[in] oth: nombre à affecter
///
/// @return Une référence sur le Complex affecté.
Complex& Complex::operator=(Complex const& oth) = default;

/// @brief operator+= - Opérateur d'affectation additive
///
/// @param[in] oth: Complex à affecter
///
/// @return Une référence sur le Complex affecté.
Complex& Complex::operator+=(Complex const& oth) {
	re = re + oth.re; im = im + oth.im;
	return *this;
}

/// @brief operator-= - Opérateur d'affectation soustrative
///
/// @param[in] oth: Complex à affecter
///
/// @return Une référence sur le Complex affecté.
Complex& Complex::operator-=(Complex const& oth) {
	re = re - oth.re; im = im - oth.im;
	return *this;
}

/// @brief operator*= - Opérateur d'affectation multiplicative
///
/// @param[in] oth: Complex à affecter
///
/// @return Une référence sur le Complex affecté.
Complex& Complex::operator*=(Complex const& oth) {
	re = (re * oth.re) - (im * oth.im);
	im = (re * oth.im) + (im * oth.re);
	return *this;
}

/// @brief operator/= - Opérateur d'affectation divisant
///
/// @param[in] oth: Complex à affecter
///
/// @return Une référence sur le Complex affecté.
Complex& Complex::operator/=(Complex const& oth) {
	const Complex conjugate(oth.re, -oth.im);
	const Complex div_d((re * conjugate.re) - (im * conjugate.im), (re * conjugate.im) + (im * conjugate.re));
	const InfInt div_c = (oth.re * oth.re) - (oth.im * oth.im);

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
Complex operator+(Complex const& lhs, Complex const& rhs) {
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
Complex operator-(Complex const& lhs, Complex const& rhs) {
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
Complex operator*(Complex const& lhs, Complex const& rhs) {
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
Complex operator/(Complex const& lhs, Complex const& rhs) {
	const Complex conjugate(rhs.re, -rhs.im);
	const Complex div_d((lhs.re * conjugate.re) - (lhs.im * conjugate.im), (lhs.re * conjugate.im) + (lhs.im * conjugate.re));
	const InfInt div_c = (rhs.re * rhs.re) - (rhs.im * rhs.im);
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
bool operator==(Complex const& lhs, Complex const& rhs) {
	return ((lhs.re == rhs.re) && (lhs.im == rhs.im));
}

/// @brief operator!= - Opérateur d'inégalité entre Complex
///
/// @param[in] lhs: lhs
/// @param[in] rhs: rhs
///
/// @return true si différents, false sinon.
bool operator!=(Complex const& lhs, Complex const& rhs) {
	return ((lhs.re != rhs.re) || (lhs.im != rhs.im));
}

/// @brief operator<< - Opérateur de flux de sortie pour Complex
///
/// @param[in] os: flux de sortie
/// @param[in] rhs: Complex concerné
///
/// @return Une référence sur le flux de sortie affecté.
std::ostream& operator<<(std::ostream& os, Complex const& rhs) {
	const InfInt r = rhs.re;
	const InfInt i = rhs.im;

	os << "(" << r << " ";
	if (i < 0) os << "- " << (-i);
	else         os << "+ " << i;
	os << "i)";

	return os;
}

/// @brief operator>> - Opérateur de flux d'entrée pour Complex
///
/// @param[in] is: flux d'entrée
/// @param[in] rhs: Complex concerné
///
/// @return Une référence sur le flux d'entrée affecté.
std::istream& operator>>(std::istream& is, Complex& rhs) {
	const std::regex v_str("^\([0-9]+ [+-]{1} [0-9]+i)$");
	std::string str_, n1, p, n2;
	is >> str_;

	if (!regex_match(str_, v_str)) {
		rhs.re = rhs.im = 0;
		return is;
	}

	str_.erase(str_.begin());
	str_.erase(str_.size() - 2, 2);

	std::istringstream iss(str_);
	std::getline(iss, n1, ' ');
	std::getline(iss, p, ' ');
	std::getline(iss, n2, ' ');

	const InfInt tr(n1);
	const InfInt ti(n2);
	rhs.re = tr;
	rhs.im = (p == "+") ? ti : -ti;

	return is;
}

}

