#include <iostream>
#include "../src/Int.h"

int Test(const Fenyx::Types::Int &A, const Fenyx::Types::Int &B, const Fenyx::Types::Int &C, const Fenyx::Types::Int &E, int s, int d, int m, int q, int r);

int main() {
	Fenyx::Types::Int A(2000000000), B(50), C(20000), E(51);
	int ret;

	std::cout << "Following tests are most important, DON'T IGNORE IT !!!" <<std::endl;
	std::cout << "" <<std::endl;
	std::cout << "" <<std::endl;
	std::cout << "" <<std::endl;
	std::cout << "" <<std::endl;

	std::cout << "Int tests" <<std::endl;
 	std::cout << "--- A/B Positifs ---" <<std::endl;
	std::cout << "" <<std::endl;

	ret = Test(A, B, C, E, 2000000050, 1999999950, 1000000, 40000000, 14);
	if (ret != 0) return ret;

	std::cout << "" <<std::endl;
	std::cout << "" <<std::endl;
	std::cout << "" <<std::endl;
	std::cout << "--- B Negatif ---" <<std::endl;
	std::cout << "" <<std::endl;

	B = Fenyx::Types::Int(-50); E = Fenyx::Types::Int(-51);
	ret = Test(A, B, C, E, 1999999950, 2000000050, -1000000, -40000000, 14);
	if (ret != 0) return ret;

	std::cout << "" <<std::endl;
	std::cout << "" <<std::endl;
	std::cout << "" <<std::endl;
	std::cout << "--- A Negatif ---" <<std::endl;
	std::cout << "" <<std::endl;

	A = Fenyx::Types::Int(-2000000000); B = Fenyx::Types::Int(50); C = Fenyx::Types::Int(-20000); E = Fenyx::Types::Int(51);
	ret = Test(A, B, C, E, -1999999950, -2000000050, -1000000, -40000000, 14);
	if (ret != 0) return ret;

	std::cout << "" <<std::endl;
	std::cout << "" <<std::endl;
	std::cout << "" <<std::endl;
	std::cout << "--- A/B Negatifs ---" <<std::endl;
	std::cout << "" <<std::endl;

	B = Fenyx::Types::Int(-50); E = Fenyx::Types::Int(-51);
	ret = Test(A, B, C, E, -2000000050, -1999999950, 1000000, 40000000, 14);
	if (ret != 0) return ret;

	return 0;
}

int Test(const Fenyx::Types::Int &A, const Fenyx::Types::Int &B, const Fenyx::Types::Int &C, const Fenyx::Types::Int &E, const int s, const int d, const int m, const int q, const int r) {
	Fenyx::Types::Int S = A + B;
	Fenyx::Types::Int D = A - B;
	Fenyx::Types::Int M = C * B;
	Fenyx::Types::Int Q = A / B;
	Fenyx::Types::Int R = A % E;

	if (S != Fenyx::Types::Int(s)) {
		std::cout << "Test Add => KO (" << S.GetStr() << ")" << std::endl;
		return -1;
	}
	std::cout << "Test Add => OK (" << S.GetStr() << ")" << std::endl;

	if (D != Fenyx::Types::Int(d)) {
		std::cout << "Test Sub => KO (" << D.GetStr() << ")" << std::endl;
		return -2;
	}
	std::cout << "Test Sub => OK (" << D.GetStr() << ")" << std::endl;

	if (M != Fenyx::Types::Int(m)) {
		std::cout << "Test Mul => KO (" << M.GetStr() << ")" << std::endl;
		return -3;
	}
	std::cout << "Test Mul => OK (" << M.GetStr() << ")" << std::endl;

	if (Q != Fenyx::Types::Int(q)) {
		std::cout << "Test Div => KO (" << Q.GetStr() << ")" << std::endl;
		return -4;
	}
	std::cout << "Test Div => OK (" << Q.GetStr() << ")" << std::endl;

	if (R != Fenyx::Types::Int(r)) {
		std::cout << "Test Mod => KO (" << R.GetStr() << ")" << std::endl;
		return -5;
	}
	std::cout << "Test Mod => OK (" << R.GetStr() << ")" << std::endl;

	return 0;
}

