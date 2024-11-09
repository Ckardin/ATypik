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
/// @version 1.0
/// @date 02/11/2024

#include "AlgoMath.h"

namespace Fenyx::Types
{

InfInt NaivePow    (InfInt const& a, InfInt const& b) {
	InfInt p = 1;

	for (InfInt i = 1; i <= b; i = i + 1) p *= a;

	return p;
}

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

InfInt Pow2        (InfInt const& n) {
	InfInt p = 1;

	for (InfInt i = 0; i < n; i = i + 1) p = p * 2;

	return p;
}

InfInt Pow16       (InfInt const& n) {
	InfInt p = 1;

	for (InfInt i = 0; i < n; i = i + 1) p = p * 16;

	return p;
}

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

InfInt F_PowM      (InfInt const& a, InfInt const& b, InfInt const& m) {
	InfInt p, x = a, n = b;

	for (p = 1; n > 0; n = n / 2) {
		if (n % 2 != 0) p = (p * x) % m;
		x = (x * x) % m;
	}

	return p;
}

InfInt RandTestMR  (InfInt const& n) {
	std::random_device rd;
	InfInt ret = rd();

	ret = n % ret;
	if (ret >= (n - 2) || ret <= 2) ret = InfInt(2) + (ret % (n - 4));

	return ret;
}

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

bool   MillerRabin (InfInt const& n, const BYTE k) {
	if (n <= 1 || n == 4) return false;
	if (n <= 3)             return true;

	for (WORD i = 0; i < k; i = i + 1) {
		if (InfInt a = RandTestMR(n); MillerTest(n, a)) return false;
	}

	return true;
}

void   ExtEuclide  (InfInt const& a, InfInt const& b, InfInt &r, InfInt &u, InfInt &v) {
	InfInt tr = a, tr_ = b, tu = 1, tv = 0, tu_ = 0, tv_ = 1;
	InfInt q = 0, rs = 0, us = 0, vs = 0;

	while (tr_ != 0) {
		q   = tr / tr_;
		rs  = tr;  us = tu;  vs  = tv;
		tr  = tr_; tu = tu_; tv  = tv_;
		tr_ = rs - (q * tr_); tu_ = us - (q * tu_); tv_ = vs - (q * tv_);
	}

	r = tr; u = tu; v = tv;
}


Complex::Complex() {
	re = im = 0;
}

Complex::Complex(InfInt const& r, InfInt const& u) {
	re = r; im = u;
}

Complex::Complex(Complex const& oth) {
	re = oth.re; im = oth.im;
}

bool Complex::IsReal() const {
	return (im == 0);
}

bool Complex::IsImag() const {
	return (re == 0);
}

InfInt Complex::Real() const {
	return re;
}

InfInt Complex::Imag() const {
	return im;
}

Complex& Complex::operator=(Complex const& oth) = default;

Complex& Complex::operator+=(Complex const& oth) {
	re = re + oth.re; im = im + oth.im;
	return *this;
}

Complex& Complex::operator-=(Complex const& oth) {
	re = re - oth.re; im = im - oth.im;
	return *this;
}

Complex& Complex::operator*=(Complex const& oth) {
	re = (re * oth.re) - (im * oth.im);
	im = (re * oth.im) + (im * oth.re);
	return *this;
}

Complex& Complex::operator/=(Complex const& oth) {
	const Complex conjugate(oth.re, -oth.im);
	const Complex div_d((re * conjugate.re) - (im * conjugate.im), (re * conjugate.im) + (im * conjugate.re));
	const InfInt div_c = (oth.re * oth.re) - (oth.im * oth.im);

	re = div_d.re / div_c;
	im = div_d.im / div_c;

	return *this;
}


Complex operator+(Complex const& lhs, Complex const& rhs) {
	Complex ret;

	ret.re = lhs.re + rhs.re;
	ret.im = lhs.im + rhs.im;

	return ret;
}

Complex operator-(Complex const& lhs, Complex const& rhs) {
	Complex ret;

	ret.re = lhs.re - rhs.re;
	ret.im = lhs.im - rhs.im;

	return ret;
}

Complex operator*(Complex const& lhs, Complex const& rhs) {
	Complex ret;

	ret.re = (lhs.re * rhs.re) - (lhs.im * rhs.im);
	ret.im = (lhs.re * rhs.im) + (lhs.im * rhs.re);

	return ret;
}

Complex operator/(Complex const& lhs, Complex const& rhs) {
	const Complex conjugate(rhs.re, -rhs.im);
	const Complex div_d((lhs.re * conjugate.re) - (lhs.im * conjugate.im), (lhs.re * conjugate.im) + (lhs.im * conjugate.re));
	const InfInt div_c = (rhs.re * rhs.re) - (rhs.im * rhs.im);
	Complex ret;

	ret.re = lhs.re / div_c;
	ret.im = lhs.im / div_c;

	return ret;
}

bool operator==(Complex const& lhs, Complex const& rhs) {
	return ((lhs.re == rhs.re) && (lhs.im == rhs.im));
}

bool operator!=(Complex const& lhs, Complex const& rhs) {
	return ((lhs.re != rhs.re) || (lhs.im != rhs.im));
}

std::ostream& operator<<(std::ostream& os, Complex const& rhs) {
	const InfInt r = rhs.re;
	const InfInt i = rhs.im;

	os << "(" << r << " ";
	if (i < 0) os << "- " << (-i);
	else         os << "+ " << i;
	os << "i)";

	return os;
}

std::istream& operator>>(std::istream& is, Complex& rhs) {
	const std::regex v_str("^\([0-9]+ [+-]{1} [0-9]+i\)$");
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

