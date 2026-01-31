#include <iostream>
#include <gmpxx.h> // GMP C++ wrapper
#include <iomanip>
#include <random>
#include "../src/Int.h"

using namespace Fenyx::Types;

struct DivergCount {
    WORD add = 0;
    WORD sub = 0;
    WORD mul = 0;
    WORD sqr = 0;
    WORD mgr = 0;
    WORD sgr = 0;
    WORD div = 0;
    WORD mod = 0;
    WORD lsh = 0;
    WORD rsh = 0;
    WORD aop = 0;
    WORD oop = 0;
    WORD xop = 0;
};

const WORD sz[] = { 128, 256, 512, 1024, 2048, 4096, 8192, 16384 };

void PrintRawVar(const mpz_class &gv, const Int &mv) {
    DWORD tgv[1024];
    size_t cgv;

    mpz_export(tgv, &cgv, -1, sizeof(DWORD), 0, 0, gv.get_mpz_t());
    DTable<DWORD> tmv = mv.GetTab();

    const size_t cgv1 = cgv - 1;
    const DWORD smv   = tmv.GetSize(), smv1 = smv - 1;

    std::cout << "" <<std::endl;
    std::cout << "Tab GMP: [ ";
    for (size_t i = 0; i < cgv; i = i + 1) {
        std::cout << tgv[i];
        if (i != cgv1) std::cout << ", ";
    }
    std::cout << " ]" << std::endl;

    std::cout << "" <<std::endl;
    std::cout << "Tab Moi: [ ";
    for (size_t i = 0; i < smv; i = i + 1) {
        std::cout << tmv[i];
        if (i != smv1) std::cout << ", ";
    }
    std::cout << " ]" << std::endl;
}

std::string GetDivergSizes(const std::string &op, const STable<DivergCount, 8> &tdg) {
    std::string ret = "(";
    WORD count = 0;

    for (WORD i = 0; i < 8; i = i + 1) {
        if (op == "Add")      count = tdg[i].add;
        else if (op == "Sub") count = tdg[i].sub;
        else if (op == "Mul") count = tdg[i].mul;
        else if (op == "Sqr") count = tdg[i].sqr;
        else if (op == "Mgr") count = tdg[i].mgr;
        else if (op == "Sgr") count = tdg[i].sgr;
        else if (op == "Div") count = tdg[i].div;
        else if (op == "Mod") count = tdg[i].mod;
        else if (op == "Lsh") count = tdg[i].lsh;
        else if (op == "Rsh") count = tdg[i].rsh;
        else if (op == "And") count = tdg[i].aop;
        else if (op == "Ior") count = tdg[i].oop;
        else if (op == "Xor") count = tdg[i].xop;

        if (count != 0) ret += toString(sz[i]);
        if (i != 7 && count != 0) ret += ", ";
    }

    ret += ")";
    return ret;
}

void TestOperators(const Int &A, const Int &B, const Int &N, DivergCount &dc, const DWORD si) {
    const Int Mu = GetMu(N), A2 = (A.IsNeg()) ? A.GetOpposite() : A, B2 = (B.IsNeg()) ? B.GetOpposite() : B;

    const mpz_class gmpA(A.GetStr()), gmpB(B.GetStr());
    const mpz_class gmp2A = (gmpA < 0) ? mpz_class(A2.GetStr()) : gmpA;
    const mpz_class gmp2B = (gmpB < 0) ? mpz_class(B2.GetStr()) : gmpB;
    const mpz_class gmpN(N.GetStr());
    const mpz_class gmpR(Mu.GetStr());
    const Int tB(si / 4);

    mpz_class c = gmpA + gmpB; mpz_class diff = c - mpz_class((A + B).GetStr());
    if (diff != 0) dc.add++;

    c = gmpA - gmpB; diff = c - mpz_class((A - B).GetStr());
    if (diff != 0) dc.sub++;

    c = gmpA * gmpB; diff = c - mpz_class((A * B).GetStr());
    if (diff != 0) dc.mul++;

    c = gmpA * gmpA; diff = c - mpz_class(Int::Square(A).GetStr());
    if (diff != 0) dc.sqr++;

    mpz_class mul = gmp2A * gmp2B;
    mpz_mod(c.get_mpz_t(), mul.get_mpz_t(), gmpN.get_mpz_t()); diff = c - mpz_class(MMul(A2, B2, N, Mu).GetStr());
    if (diff != 0) dc.mgr++;

    mul = gmp2A * gmp2A;
    mpz_mod(c.get_mpz_t(), mul.get_mpz_t(), gmpN.get_mpz_t()); diff = c - mpz_class(MSqr(A2, N, Mu).GetStr());
    if (diff != 0) dc.sgr++;

    c = gmpA / gmpB; diff = c - mpz_class((A / B).GetStr());
    if (diff != 0) dc.div++;

    c = gmpA % gmpB; diff = c - mpz_class((A % B).GetStr());
    if (diff != 0) dc.mod++;

    mpz_mul_2exp(c.get_mpz_t(), gmpA.get_mpz_t(), tB.GetL64()); diff = c - mpz_class((A << tB.GetL64()).GetStr());
    if (diff != 0) dc.lsh++;

    mpz_fdiv_q_2exp(c.get_mpz_t(), gmpA.get_mpz_t(), tB.GetL64()); diff = c - mpz_class((A >> tB.GetL64()).GetStr());
    if (diff != 0) dc.rsh++;

    mpz_and(c.get_mpz_t(), gmp2A.get_mpz_t(), gmp2B.get_mpz_t()); diff = c - mpz_class((A2 & B2).GetStr());
    if (diff != 0) dc.aop++;

    mpz_ior(c.get_mpz_t(), gmp2A.get_mpz_t(), gmp2B.get_mpz_t()); diff = c - mpz_class((A2 | B2).GetStr());
    if (diff != 0) dc.oop++;

    mpz_xor(c.get_mpz_t(), gmp2A.get_mpz_t(), gmp2B.get_mpz_t()); diff = c - mpz_class((A2 ^ B2).GetStr());
    if (diff != 0) dc.xop++;
}

void PrintResult(const std::string &op, const WORD count, const STable<DivergCount, 8> &tdg, const std::string &sad = "") {
    std::cout << "Test " << op << " => ";
    if (count > 0) {
        std::cout << "KO --> " << count << " divergence(s)" << GetDivergSizes(op, tdg) << sad << std::endl;
    } else {
        std::cout << "OK" << sad << std::endl;
    }
}

int main() {
    const DWORD cntt = 128;
    STable<DivergCount, 8> tDiverg;
    std::random_device rd;

    std::cout << "" <<std::endl;
    std::cout << "" <<std::endl;
    std::cout << "=== Test {Int} sur grandes valeurs ===" <<std::endl;
    std::cout << "" <<std::endl;

    for (WORD i = 0; i < 8; i = i + 1) {
        for (WORD j = 0; j < cntt; j = j + 1) {
            Int A = Int::Random(sz[i], rd);
            Int B = Int::Random(sz[i] / 2, rd);
            Int N = Int::Random(sz[i] * 2, rd);
            if (N.IsEven()) N += One;

            A = (rd() % 2) ? A : A.GetOpposite();
            B = (rd() % 2) ? B : B.GetOpposite();
            if (B.IsZero()) B = One;

            std::cout << "\rTest "
                      << std::setw(3) << j + 1 << " / " << cntt << " ("
                      << std::setw(5) << sz[i] << " bits)"
                      << std::string(20, ' ')
                      << std::flush;
            TestOperators(A, B, N, tDiverg[i], sz[i]);
        }
    }

    std::cout << "\r";
    DivergCount fcnt;
    for (WORD i = 0; i < 8; i = i + 1) {
        fcnt.add += tDiverg[i].add;
        fcnt.sub += tDiverg[i].sub;
        fcnt.mul += tDiverg[i].mul;
        fcnt.sqr += tDiverg[i].sqr;
        fcnt.mgr += tDiverg[i].mgr;
        fcnt.sgr += tDiverg[i].sgr;
        fcnt.div += tDiverg[i].div;
        fcnt.mod += tDiverg[i].mod;
        fcnt.lsh += tDiverg[i].lsh;
        fcnt.rsh += tDiverg[i].rsh;
        fcnt.aop += tDiverg[i].aop;
        fcnt.oop += tDiverg[i].oop;
        fcnt.xop += tDiverg[i].xop;
    }

    PrintResult("Add", fcnt.add, tDiverg, std::string(50, ' '));
    PrintResult("Sub", fcnt.sub, tDiverg);
    PrintResult("Mul", fcnt.mul, tDiverg);
    PrintResult("Sqr", fcnt.sqr, tDiverg);
    PrintResult("Mgr", fcnt.mgr, tDiverg);
    PrintResult("Sgr", fcnt.sgr, tDiverg);
    PrintResult("Div", fcnt.div, tDiverg);
    PrintResult("Mod", fcnt.mod, tDiverg);
    PrintResult("Lsh", fcnt.lsh, tDiverg);
    PrintResult("Rsh", fcnt.rsh, tDiverg);
    PrintResult("And", fcnt.aop, tDiverg);
    PrintResult("Ior", fcnt.oop, tDiverg);
    PrintResult("Xor", fcnt.xop, tDiverg);

    return 0;
}

