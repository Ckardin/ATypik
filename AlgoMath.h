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

/// @file AlgoMath.h
/// @brief Header de AlgoMath
/// @author F&nµx
/// @version 1.0
/// @date 09/11/2024

#ifndef ALGOMATH_H
#define ALGOMATH_H

#include "Utils.h" // for <random> include and [Defines]
#include "InfInt.h"
#include <regex>

namespace Fenyx::Types
{

InfInt NaivePow    (InfInt const& a, InfInt const& b);
InfInt Pow         (InfInt const& x, InfInt const& n);
InfInt Pow2        (InfInt const& n);
InfInt Pow16       (InfInt const& n);
InfInt W_PowM      (InfInt const& a, InfInt const& b, InfInt const& m);
InfInt F_PowM      (InfInt const& a, InfInt const& b, InfInt const& m);
InfInt ExtEuclide  (InfInt const& a, InfInt const& b, InfInt &u, InfInt &v);
InfInt RandTestMR  (InfInt const& n);
bool   MillerTest  (InfInt const& n, InfInt const& a);
bool   MillerRabin (InfInt const& n, BYTE k = 48);


class Complex {
public:
	Complex();
	Complex(InfInt const& r, InfInt const& u);
	Complex(Complex const& oth);

	[[nodiscard]] bool IsReal() const;
	[[nodiscard]] bool IsImag() const;
	[[nodiscard]] InfInt Real() const;
	[[nodiscard]] InfInt Imag() const;

	Complex& operator=(Complex const& oth);
	Complex& operator+=(Complex const& oth);
	Complex& operator-=(Complex const& oth);
	Complex& operator*=(Complex const& oth);
	Complex& operator/=(Complex const& oth);

private:
	InfInt re;
	InfInt im;

	friend Complex operator+(Complex const& lhs, Complex const& rhs);
	friend Complex operator-(Complex const& lhs, Complex const& rhs);
	friend Complex operator*(Complex const& lhs, Complex const& rhs);
	friend Complex operator/(Complex const& lhs, Complex const& rhs);

	friend bool operator==(Complex const& lhs, Complex const& rhs);
	friend bool operator!=(Complex const& lhs, Complex const& rhs);

	friend std::ostream& operator<<(std::ostream& os, Complex const& rhs);
	friend std::istream& operator>>(std::istream& is, Complex& rhs);
};

}

#endif //ALGOMATH_H
