#include <iostream>
#include <gmpxx.h> // GMP C++ wrapper
#include "../src/Int.h"

using namespace Fenyx::Types;

struct DivergCount {
    WORD add = 0;
    WORD sub = 0;
    WORD mul = 0;
    WORD sqr = 0;
    WORD div = 0;
    WORD mod = 0;
    WORD lsh = 0;
    WORD rsh = 0;
};

void TestOperators(const Int &A, const Int &B, DivergCount &dc, const DWORD si, const bool d) {
    const mpz_class gmpA(A.GetStr());
    const mpz_class gmpB(B.GetStr());
    const Int tB(si / 4);

    mpz_class c = gmpA + gmpB;
    if ((A + B).GetStr() != c.get_str()) {
        if (d) std::cout << "[Erreur] Addition diverge" <<std::endl;
        dc.add++;
    }

    c = gmpA - gmpB;
    if ((A - B).GetStr() != c.get_str()) {
        if (d) std::cout << "[Erreur] Soustraction diverge" <<std::endl;
        dc.sub++;
    }

    c = gmpA * gmpB;
    if ((A * B).GetStr() != c.get_str()) {
        if (d) std::cout << "[Erreur] Multiplication diverge" <<std::endl;
        dc.mul++;
    }

    c = gmpA * gmpA;
    if (Int::Square(A).GetStr() != c.get_str()) {
        if (d) std::cout << "[Erreur] Mise au carre diverge" <<std::endl;
        dc.sqr++;
    }

    c = gmpA / gmpB;
    if ((A / B).GetStr() != c.get_str()) {
        if (d) std::cout << "[Erreur] Division diverge" <<std::endl;
        dc.div++;
    }

    c = gmpA % gmpB;
    if ((A % B).GetStr() != c.get_str()) {
        if (d) std::cout << "[Erreur] Modulo diverge" <<std::endl;
        dc.mod++;
    }

    mpz_mul_2exp(c.get_mpz_t(), gmpA.get_mpz_t(), tB.GetL64());
    if ((A << tB.GetL64()).GetStr() != c.get_str()) {
        if (d) std::cout << "[Erreur] LeftShift diverge" <<std::endl;
        dc.lsh++;
    }

    mpz_fdiv_q_2exp(c.get_mpz_t(), gmpA.get_mpz_t(), tB.GetL64());
    if ((A >> tB.GetL64()).GetStr() != c.get_str()) {
        if (d) std::cout << "[Erreur] RightShift diverge" <<std::endl;
        dc.rsh++;
    }
}

int main(const int argc, char* argv[]) {
    std::random_device rd;
    DivergCount tDiverg;
    bool debug = false;
    DWORD trd;

    if (argc > 1) {
        if (std::string(argv[1]) == "debug") debug = true;
    }

    std::cout << "" <<std::endl;
    std::cout << "" <<std::endl;
    std::cout << "=== Test {Int} sur grandes valeurs ===" <<std::endl;
    std::cout << "" <<std::endl;

    for (DWORD sz : {64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384}) {
        if (debug) std::cout << "--- Test avec taille " << sz << " bits ---" <<std::endl;

        Int A = Int::Random(sz, rd);
        Int B = Int::Random(sz / 2, rd);
        trd = rd() % 2;
        A = (trd == 0) ? A : A.GetOpposite();
        trd = rd() % 2;
        B = (trd == 0) ? B : B.GetOpposite();
        if (B.IsZero()) B = Int{1};

        TestOperators(A, B, tDiverg, sz, debug);
    }

    if (debug) {
        std::cout << "--- Synthese des divergences ---" <<std::endl;
        std::cout << "Add: " << tDiverg.add << std::endl;
        std::cout << "Sub: " << tDiverg.sub << std::endl;
        std::cout << "Mul: " << tDiverg.mul << std::endl;
        std::cout << "Sqr: " << tDiverg.sqr << std::endl;
        std::cout << "Div: " << tDiverg.div << std::endl;
        std::cout << "Mod: " << tDiverg.mod << std::endl;
        std::cout << "Lsh: " << tDiverg.lsh << std::endl;
        std::cout << "Rsh: " << tDiverg.rsh << std::endl;
    } else {
        std::cout << "Test Add => ";
        if (tDiverg.add > 0) std::cout << "KO --> " << tDiverg.add << " divergence(s)" <<std::endl;
        else                 std::cout << "OK" <<std::endl;

        std::cout << "Test Sub => ";
        if (tDiverg.sub > 0) std::cout << "KO --> " << tDiverg.sub << " divergence(s)" <<std::endl;
        else                 std::cout << "OK" <<std::endl;

        std::cout << "Test Mul => ";
        if (tDiverg.mul > 0) std::cout << "KO --> " << tDiverg.mul << " divergence(s)" <<std::endl;
        else                 std::cout << "OK" <<std::endl;

        std::cout << "Test Sqr => ";
        if (tDiverg.sqr > 0) std::cout << "KO --> " << tDiverg.sqr << " divergence(s)" <<std::endl;
        else                 std::cout << "OK" <<std::endl;

        std::cout << "Test Div => ";
        if (tDiverg.div > 0) std::cout << "KO --> " << tDiverg.div << " divergence(s)" <<std::endl;
        else                 std::cout << "OK" <<std::endl;

        std::cout << "Test Mod => ";
        if (tDiverg.mod > 0) std::cout << "KO --> " << tDiverg.mod << " divergence(s)" <<std::endl;
        else                 std::cout << "OK" <<std::endl;

        std::cout << "Test Lsh => ";
        if (tDiverg.lsh > 0) std::cout << "KO --> " << tDiverg.lsh << " divergence(s)" <<std::endl;
        else                 std::cout << "OK" <<std::endl;

        std::cout << "Test Rsh => ";
        if (tDiverg.rsh > 0) std::cout << "KO --> " << tDiverg.rsh << " divergence(s)" <<std::endl;
        else                 std::cout << "OK" <<std::endl;
    }

    return 0;
}

