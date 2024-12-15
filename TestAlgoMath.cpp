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

/// @file TestAlgoMath.cpp
/// @brief Source de TestAlgoMath
/// @author F&nµx
/// @version 1.0
/// @date 14/12/2024

#include "AlgoMath.h"
#include <iostream>

int test_c();

int main() {
	const InfInt a = 2, b = 16, m = 3;

	if (Fenyx::Types::NaivePow(a, b) != 65536) {
		std::cout << "Test KO." <<std::endl;
		return -1;
	}

	if (Fenyx::Types::Pow(a, b) != 65536) {
		std::cout << "Test KO." <<std::endl;
		return -2;
	}

	if (Fenyx::Types::Pow2(b) != 65536) {
		std::cout << "Test KO." <<std::endl;
		return -3;
	}

	if (Fenyx::Types::Pow16(a) != 256) {
		std::cout << "Test KO." <<std::endl;
		return -4;
	}

	if (Fenyx::Types::W_PowM(a, b, m) != 1) {
		std::cout << "Test KO." <<std::endl;
		return -5;
	}

	if (Fenyx::Types::F_PowM(a, b, m) != 1) {
		std::cout << "Test KO." <<std::endl;
		return -5;
	}

	if (!Fenyx::Types::MillerRabin(7877)) {
        std::cout << "Test KO." <<std::endl;
        return -6;
    }

    if (Fenyx::Types::MillerRabin(1234)) {
      	std::cout << "Test KO." <<std::endl;
        return -7;
    }

    if (InfInt u, v; Fenyx::Types::ExtEuclide(1457, 3475, u, v) != 1) {
      	std::cout << "Test KO." <<std::endl;
        return -8;
    }

    return test_c();
}

int test_c() {
 	Fenyx::Types::Complex a(3, 10), b(2, -8);

    if (a == b) {
      	std::cout << "Test KO." <<std::endl;
       	return -9;
    }

    if ((a + b) != Fenyx::Types::Complex(5, 2)) {
		std::cout << "Test KO." <<std::endl;
        std::cout << "+ => " << (a + b) <<std::endl;
        return -10;
    }

    if ((a - b) != Fenyx::Types::Complex(1, 18)) {
      	std::cout << "Test KO." <<std::endl;
        std::cout << "- => " << (a - b) <<std::endl;
        return -11;
    }

    if ((a * b) != Fenyx::Types::Complex(86, -4)) {
      	std::cout << "Test KO." <<std::endl;
        std::cout << "* => " << (a * b) <<std::endl;
        return -12;
    }

    if ((a / b) != Fenyx::Types::Complex(0, 0)) {
      	std::cout << "Test KO." <<std::endl;
        std::cout << "/ => " << (a / b) <<std::endl;
        return -13;
    }

    if (a.Real() != 3) {
      	std::cout << "Test KO." <<std::endl;
      	return -14;
    }

	if (a.Imag() != 10) {
		std::cout << "Test KO." <<std::endl;
		return -14;
	}

    a = Fenyx::Types::Complex(3, 0);
    if (!a.IsReal()) {
      	std::cout << "Test KO." <<std::endl;
        return -15;
    }

    a = Fenyx::Types::Complex(0, 10);
    if (!a.IsImag()) {
      	std::cout << "Test KO." <<std::endl;
        return -16;
    }

	std::cout << "Test OK." <<std::endl;

    return 0;
}

