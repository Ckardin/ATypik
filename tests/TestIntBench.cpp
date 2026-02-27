#include <chrono>
#include <iostream>
#include <iomanip>
#include <random>
#include "../src/Int.h"

using Clock = std::chrono::steady_clock;
using namespace Fenyx;

template <typename F>
double TimeIt(F&& func) {
    const auto start = Clock::now();
    func();
    const auto end = Clock::now();

    return std::chrono::duration<double, std::micro>(end - start).count();
}

void BenchAdd(const Types::DWORD bits, const Types::WORD ncnt) {
    std::random_device rdr;
    double mbt = 0.00;

    for (Types::WORD i = 0; i < ncnt; i = i + 1) {
        const Types::Int a = Types::Int::Random(bits, rdr);
        const Types::Int b = Types::Int::Random(bits, rdr);

        std::cout << "\rBench Add "
                      << std::setw(3) << i + 1 << " / " << ncnt << " ("
                      << std::setw(5) << bits << " bits)"
                      << std::string(20, ' ')
                      << std::flush;
        mbt += TimeIt([&]() { volatile Types::Int c = a + b; });
    }

    mbt = mbt / ncnt;
    std::cout << "\rAdd " << std::setw(5) << bits << " bits: " << std::setw(8) << std::fixed
              << std::setprecision(2) << mbt << " us" << std::string(25, ' ') <<std::endl;
}

void BenchSub(const Types::DWORD bits, const Types::WORD ncnt) {
    std::random_device rdr;
    double mbt = 0.00;

    for (Types::WORD i = 0; i < ncnt; i = i + 1) {
        const Types::Int a = Types::Int::Random(bits, rdr);
        const Types::Int b = Types::Int::Random(bits, rdr);

        std::cout << "\rBench Sub "
                      << std::setw(3) << i + 1 << " / " << ncnt << " ("
                      << std::setw(5) << bits << " bits)"
                      << std::string(20, ' ')
                      << std::flush;
        mbt += TimeIt([&]() { volatile Types::Int c = a - b; });
    }

    mbt = mbt / ncnt;
    std::cout << "\rSub " << std::setw(5) << bits << " bits: " << std::setw(8) << std::fixed
                          << std::setprecision(2) << mbt << " us" << std::string(25, ' ') <<std::endl;
}

void BenchMul(const Types::DWORD bits, const Types::WORD ncnt) {
    std::random_device rdr;
    double mbt = 0.00;

    for (Types::WORD i = 0; i < ncnt; i = i + 1) {
        const Types::Int a = Types::Int::Random(bits, rdr);
        const Types::Int b = Types::Int::Random(bits, rdr);

        std::cout << "\rBench Mul "
                      << std::setw(3) << i + 1 << " / " << ncnt << " ("
                      << std::setw(5) << bits << " bits)"
                      << std::string(20, ' ')
                      << std::flush;
        mbt += TimeIt([&]() { volatile Types::Int c = a * b; });
    }

    mbt = mbt / ncnt;
    std::cout << "\rMul " << std::setw(5) << bits << " bits: " << std::setw(8) << std::fixed
                          << std::setprecision(2) << mbt << " us" << std::string(25, ' ') <<std::endl;
}

void BenchSqr(const Types::DWORD bits, const Types::WORD ncnt) {
    std::random_device rdr;
    double mbt = 0.00;

    for (Types::WORD i = 0; i < ncnt; i = i + 1) {
        const Types::Int a = Types::Int::Random(bits, rdr);

        std::cout << "\rBench Sqr "
                      << std::setw(3) << i + 1 << " / " << ncnt << " ("
                      << std::setw(5) << bits << " bits)"
                      << std::string(20, ' ')
                      << std::flush;
        mbt += TimeIt([&]() { volatile Types::Int c = Types::Int::Square(a); });
    }

    mbt = mbt / ncnt;
    std::cout << "\rSqr " << std::setw(5) << bits << " bits: " << std::setw(8) << std::fixed
                          << std::setprecision(2) << mbt << " us" << std::string(25, ' ') <<std::endl;
}

void BenchMgr(const Types::DWORD bits, const Types::WORD ncnt) {
    std::random_device rdr;
    double mbt = 0.00, mbt2 = 0.00;

    for (Types::WORD i = 0; i < ncnt; i = i + 1) {
        const Types::Int a = Types::Int::Random(bits, rdr);
        const Types::Int b = Types::Int::Random(bits, rdr);
        Types::Int n = Types::Int::Random(bits * 2, rdr);
        if (n.IsEven()) n = n + Types::One;
        const Types::Int mu = GetMu(n);

        std::cout << "\rBench Mml/Msq "
                      << std::setw(3) << i + 1 << " / " << ncnt << " ("
                      << std::setw(5) << bits << " bits)"
                      << std::string(20, ' ')
                      << std::flush;
        mbt  += TimeIt([&]() { volatile Types::Int c = MMul(a, b, n, mu); });
        mbt2 += TimeIt([&]() { volatile Types::Int c = MSqr(a, n, mu); });
    }

    mbt = mbt / ncnt; mbt2 = mbt2 / ncnt;
    std::cout << "\rMml " << std::setw(5) << bits << " bits: " << std::setw(8) << std::fixed
                          << std::setprecision(2) << mbt << " us" << std::string(25, ' ') <<std::endl;
    std::cout << "Msq " << std::setw(5) << bits << " bits: " << std::setw(8) << std::fixed
                        << std::setprecision(2) << mbt2 << " us" << std::string(25, ' ') <<std::endl;
}

void BenchDiv(const Types::DWORD bits, const Types::WORD ncnt) {
    std::random_device rdr;
    double mbt = 0.00;

    for (Types::WORD i = 0; i < ncnt; i = i + 1) {
        const Types::Int a = Types::Int::Random(bits, rdr);
        const Types::Int b = Types::Int::Random(bits / 2, rdr);

        std::cout << "\rBench Div "
                      << std::setw(3) << i + 1 << " / " << ncnt << " ("
                      << std::setw(5) << bits << " bits)"
                      << std::string(20, ' ')
                      << std::flush;
        mbt += TimeIt([&]() { volatile Types::Int c = a / b; });
    }

    mbt = mbt / ncnt;
    std::cout << "\rDiv " << std::setw(5) << bits << " bits: " << std::setw(8) << std::fixed
                          << std::setprecision(2) << mbt << " us" << std::string(25, ' ') <<std::endl;
}

void BenchMod(const Types::DWORD bits, const Types::WORD ncnt) {
    std::random_device rdr;
    double mbt = 0.00;

    for (Types::WORD i = 0; i < ncnt; i = i + 1) {
        const Types::Int a = Types::Int::Random(bits, rdr);
        const Types::Int b = Types::Int::Random(bits / 2, rdr);

        std::cout << "\rBench Mod "
                      << std::setw(3) << i + 1 << " / " << ncnt << " ("
                      << std::setw(5) << bits << " bits)"
                      << std::string(20, ' ')
                      << std::flush;
        mbt += TimeIt([&]() { volatile Types::Int c = a % b; });
    }

    mbt = mbt / ncnt;
    std::cout << "\rMod " << std::setw(5) << bits << " bits: " << std::setw(8) << std::fixed
                          << std::setprecision(2) << mbt << " us" << std::string(25, ' ') <<std::endl;
}

void BenchLop(const Types::DWORD bits, const Types::WORD ncnt) {
    std::random_device rdr;
    double mbta = 0.00, mbto = 0.00, mbtx = 0.00;

    for (Types::WORD i = 0; i < ncnt; i = i + 1) {
        const Types::Int a = Types::Int::Random(bits, rdr);
        const Types::Int b = Types::Int::Random(bits, rdr);

        std::cout << "\rBench And/Or/Xor "
                      << std::setw(3) << i + 1 << " / " << ncnt << " ("
                      << std::setw(5) << bits << " bits)"
                      << std::string(20, ' ')
                      << std::flush;
        mbta += TimeIt([&]() { volatile Types::Int c = a & b; });
        mbto += TimeIt([&]() { volatile Types::Int c = a | b; });
        mbtx += TimeIt([&]() { volatile Types::Int c = a ^ b; });
    }

    mbta = mbta / ncnt; mbto = mbto / ncnt; mbtx = mbtx / ncnt;
    std::cout << "\rAnd " << std::setw(5) << bits << " bits: " << std::setw(8) << std::fixed
                          << std::setprecision(2) << mbta << " us" << std::string(25, ' ') <<std::endl;
    std::cout << "Ior " << std::setw(5) << bits << " bits: " << std::setw(8) << std::fixed
                        << std::setprecision(2) << mbto << " us" << std::string(25, ' ') <<std::endl;
    std::cout << "Xor " << std::setw(5) << bits << " bits: " << std::setw(8) << std::fixed
                        << std::setprecision(2) << mbtx << " us" << std::string(25, ' ') <<std::endl;
}

int main() {
    std::cout.setf(std::ios::unitbuf);
    const Types::WORD cntb = 128;

    std::cout << "" <<std::endl;
    std::cout << "" <<std::endl;
    std::cout << "=== Benchmark pour Int ===" <<std::endl;
    std::cout << "" <<std::endl;

    for (Types::DWORD bits : {128, 256, 512, 1024, 2048, 4096, 8192, 16384}) {
        BenchAdd(bits, cntb);
        BenchSub(bits, cntb);
        BenchLop(bits, cntb);
        BenchMul(bits, cntb);
        BenchSqr(bits, cntb);
        BenchMgr(bits, cntb);
        BenchDiv(bits, cntb);
        BenchMod(bits, cntb);

        std::cout << "" <<std::endl;
    }

    return 0;
}
