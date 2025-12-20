#include <chrono>
#include <iostream>
#include "../src/Int.h"

using Clock = std::chrono::high_resolution_clock;
using namespace Fenyx;

template <typename F>
double TimeIt(F&& func) {
    const auto start = Clock::now();
    func();
    const auto end = Clock::now();

    return std::chrono::duration<double, std::micro>(end - start).count();
}

void BenchAdd(const Types::DWORD bits) {
    std::random_device rdr;

    const Types::Int a = Types::Int::Random(bits, rdr);
    const Types::Int b = Types::Int::Random(bits, rdr);

    const double t = TimeIt([&]() { volatile Types::Int c = a + b; });

    std::cout << "Add " << bits << " bits: " << t << " us" <<std::endl;
}

void BenchSub(const Types::DWORD bits) {
    std::random_device rdr;

    const Types::Int a = Types::Int::Random(bits, rdr);
    const Types::Int b = Types::Int::Random(bits, rdr);

    const double t = TimeIt([&]() { volatile Types::Int c = a - b; });

    std::cout << "Sub " << bits << " bits: " << t << " us" <<std::endl;
}

void BenchMul(const Types::DWORD bits) {
    std::random_device rdr;

    const Types::Int a = Types::Int::Random(bits, rdr);
    const Types::Int b = Types::Int::Random(bits, rdr);

    const double t = TimeIt([&]() { volatile Types::Int c = a * b; });

    std::cout << "Mul " << bits << " bits: " << t << " us" <<std::endl;
}

void BenchSqr(const Types::DWORD bits) {
    std::random_device rdr;

    const Types::Int a = Types::Int::Random(bits, rdr);

    const double t = TimeIt([&]() { volatile Types::Int c = Types::Int::Square(a); });

    std::cout << "Sqr " << bits << " bits: " << t << " us" <<std::endl;
}

void BenchMgr(const Types::DWORD bits) {
    std::random_device rdr;

    const Types::Int a = Types::Int::Random(bits, rdr);
    const Types::Int b = Types::Int::Random(bits, rdr);
    Types::Int n = Types::Int::Random(bits * 2, rdr);
    if (n.IsEven()) n = n + Types::One;
    const Types::Int mu = GetMu(n);

    const double t1 = TimeIt([&]() { volatile Types::Int c = MMul(a, b, n, mu); });
    std::cout << "Mml " << bits << " bits: " << t1 << " us" <<std::endl;

    const double t2 = TimeIt([&]() { volatile Types::Int c = MSqr(a, n, mu); });
    std::cout << "Msq " << bits << " bits: " << t2 << " us" <<std::endl;
}

void BenchDiv(const Types::DWORD bits) {
    std::random_device rdr;

    const Types::Int a = Types::Int::Random(bits, rdr);
    const Types::Int b = Types::Int::Random(bits / 2, rdr);

    const double t = TimeIt([&]() { volatile Types::Int c = a / b; });

    std::cout << "Div " << bits << " bits: " << t << " us" <<std::endl;
}

void BenchMod(const Types::DWORD bits) {
    std::random_device rdr;

    const Types::Int a = Types::Int::Random(bits, rdr);
    const Types::Int b = Types::Int::Random(bits / 2, rdr);

    const double t = TimeIt([&]() { volatile Types::Int c = a % b; });

    std::cout << "Mod " << bits << " bits: " << t << " us" <<std::endl;
}

int main() {
    std::cout << "" <<std::endl;
    std::cout << "" <<std::endl;
    std::cout << "=== Benchmark pour Int ===" <<std::endl;
    std::cout << "" <<std::endl;

    for (Types::DWORD bits : {128, 512, 1024, 2048, 4096, 8192, 16384}) {
        BenchAdd(bits);
        BenchSub(bits);
        BenchMul(bits);
        BenchSqr(bits);
        BenchMgr(bits);
        BenchDiv(bits);
        BenchMod(bits);
    }

    return 0;
}
