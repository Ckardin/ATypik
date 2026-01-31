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

/// @file ll_Wrp.h
/// @brief Header de ll_Wrp
/// @author F&nµx
/// @version 6.0
/// @date 06/01/2025

#ifndef LL_WRP_H
#define LL_WRP_H

#include <algorithm>
#include <functional>
#include <iostream>

#if defined(__x86_64__)
#include <immintrin.h>
#elif defined(__aarch64__)
#include <arm_neon.h>
#endif

#include "StrUtils.h"

#if defined(__GNUC__) || defined(__clang__)
  #define ALWAYS_INLINE inline __attribute__((always_inline))
#else
  #define ALWAYS_INLINE inline
#endif

#define ATTR_BMI1   __attribute__((target("bmi")))
#define ATTR_BMI2   __attribute__((target("bmi2")))
#define ATTR_ADX    __attribute__((target("adx")))
#define ATTR_LZCNT  __attribute__((target("lzcnt")))
#define ATTR_AVX2   __attribute__((target("avx2")))
#define ATTR_SSE2   __attribute__((target("sse2")))

namespace Fenyx::Types::CPU
{

ALWAYS_INLINE ATTR_ADX BYTE addwc_adx(const DWORD a, const DWORD b, const DWORD ci, DWORD &r) {
	return _addcarry_u32(ci, a, b, &r);
}

ALWAYS_INLINE BYTE addwc_arm(const DWORD a, const DWORD b, const DWORD ci, DWORD &r) {
	return __builtin_addc(a, b, ci, &r);
}

ALWAYS_INLINE BYTE addwc_flb(const DWORD a, const DWORD b, const DWORD ci, DWORD &r) {
	const QWORD t = static_cast<QWORD>(a) + static_cast<QWORD>(b) + static_cast<QWORD>(ci);
	r = static_cast<DWORD>(t);
	return (t >> 32) & 1;
}


ALWAYS_INLINE ATTR_ADX BYTE subwb_adx(const DWORD a, const DWORD b, const DWORD bi, DWORD &r) {
	return _subborrow_u32(bi, a, b, &r);
}

ALWAYS_INLINE BYTE subwb_arm(const DWORD a, const DWORD b, const DWORD bi, DWORD &r) {
	return __builtin_subc(a, b, bi, &r);
}

ALWAYS_INLINE BYTE subwb_flb(const DWORD a, const DWORD b, const DWORD bi, DWORD &r) {
	const QWORD t = static_cast<QWORD>(a) - static_cast<QWORD>(b) - static_cast<QWORD>(bi);
	r = static_cast<DWORD>(t);
	return (t >> 63) & 1;
}


ALWAYS_INLINE ATTR_LZCNT BYTE cntlz_int(const DWORD a) {
	return a ? _lzcnt_u32(a) : 32;
}

ALWAYS_INLINE BYTE cntlz_arm(const DWORD a) {
	return a ? __builtin_clz(a) : 32;
}

ALWAYS_INLINE BYTE cntlz_flb(const DWORD a) {
	if (a == 0) return 32;
	DWORD n = 0, mask = 0x80000000u;

	while ((a & mask) == 0) {
		mask >>= 1;
		n += 1;
	}

	return n;
}


ALWAYS_INLINE ATTR_BMI1 BYTE cnttz_bmi(const DWORD a) {
	return a ? _tzcnt_u32(a) : 32;
}

ALWAYS_INLINE BYTE cnttz_arm(const DWORD a) {
	return a ? __builtin_ctz(a) : 32;
}

ALWAYS_INLINE BYTE cnttz_flb(DWORD a) {
	if (a == 0) return 32;
	DWORD n = 0;

	while ((a & 1) == 0) {
		a >>= 1;
		n += 1;
	}

	return n;
}


ALWAYS_INLINE ATTR_AVX2 void and_avx2(DWORD *a, DWORD *b, DWORD *r, const DWORD idx) {
	const __m256i simd_a = _mm256_load_si256(reinterpret_cast<__m256i*>(a));
	const __m256i simd_b = _mm256_load_si256(reinterpret_cast<__m256i*>(b));
	_mm256_store_si256(reinterpret_cast<__m256i*>(r + idx), _mm256_and_si256(simd_a, simd_b));
}

ALWAYS_INLINE ATTR_SSE2 void and_sse2(DWORD *a, DWORD *b, DWORD *r, const DWORD idx) {
	const __m128i simd_a = _mm_load_si128(reinterpret_cast<__m128i*>(a));
	const __m128i simd_b = _mm_load_si128(reinterpret_cast<__m128i*>(b));
	_mm_store_si128(reinterpret_cast<__m128i*>(r + idx), _mm_and_si128(simd_a, simd_b));
}

#if defined(__aarch64__)
ALWAYS_INLINE void and_arm(DWORD *a, DWORD *b, DWORD *r, const DWORD idx) {
	const uint32x4_t simd_a = vld1q_u32(a);
	const uint32x4_t simd_b = vld1q_u32(b);
	vst1q_u32(r + idx, vandq_u32(simd_a, simd_b));
}
#endif

ALWAYS_INLINE void and_flb(DWORD *a, DWORD *b, DWORD *r, const DWORD idx) {
	r[idx] = (a[0] & b[0]);
}


ALWAYS_INLINE ATTR_AVX2 void ior_avx2(DWORD *a, DWORD *b, DWORD *r, const DWORD idx) {
	const __m256i simd_a = _mm256_load_si256(reinterpret_cast<__m256i*>(a));
	const __m256i simd_b = _mm256_load_si256(reinterpret_cast<__m256i*>(b));
	_mm256_store_si256(reinterpret_cast<__m256i*>(r + idx), _mm256_or_si256(simd_a, simd_b));
}

ALWAYS_INLINE ATTR_SSE2 void ior_sse2(DWORD *a, DWORD *b, DWORD *r, const DWORD idx) {
	const __m128i simd_a = _mm_load_si128(reinterpret_cast<__m128i*>(a));
	const __m128i simd_b = _mm_load_si128(reinterpret_cast<__m128i*>(b));
	_mm_store_si128(reinterpret_cast<__m128i*>(r + idx), _mm_or_si128(simd_a, simd_b));
}

#if defined(__aarch64__)
ALWAYS_INLINE void ior_arm(DWORD *a, DWORD *b, DWORD *r, const DWORD idx) {
	const uint32x4_t simd_a = vld1q_u32(a);
	const uint32x4_t simd_b = vld1q_u32(b);
	vst1q_u32(r + idx, vorrq_u32(simd_a, simd_b));
#endif

ALWAYS_INLINE void ior_flb(DWORD *a, DWORD *b, DWORD *r, const DWORD idx) {
	r[idx] = (a[0] | b[0]);
}


ALWAYS_INLINE ATTR_AVX2 void xor_avx2(DWORD *a, DWORD *b, DWORD *r, const DWORD idx) {
	const __m256i simd_a = _mm256_load_si256(reinterpret_cast<__m256i*>(a));
	const __m256i simd_b = _mm256_load_si256(reinterpret_cast<__m256i*>(b));
	_mm256_store_si256(reinterpret_cast<__m256i*>(r + idx), _mm256_xor_si256(simd_a, simd_b));
}

ALWAYS_INLINE ATTR_SSE2 void xor_sse2(DWORD *a, DWORD *b, DWORD *r, const DWORD idx) {
	const __m128i simd_a = _mm_load_si128(reinterpret_cast<__m128i*>(a));
	const __m128i simd_b = _mm_load_si128(reinterpret_cast<__m128i*>(b));
	_mm_store_si128(reinterpret_cast<__m128i*>(r + idx), _mm_xor_si128(simd_a, simd_b));
}

#if defined(__aarch64__)
ALWAYS_INLINE void xor_arm(DWORD *a, DWORD *b, DWORD *r, const DWORD idx) {
	const uint32x4_t simd_a = vld1q_u32(a);
	const uint32x4_t simd_b = vld1q_u32(b);
	vst1q_u32(r + idx, veorq_u32(simd_a, simd_b));
}
#endif

ALWAYS_INLINE void xor_flb(DWORD *a, DWORD *b, DWORD *r, const DWORD idx) {
	r[idx] = (a[0] ^ b[0]);
}


extern BYTE (*addwc)(DWORD a, DWORD b, DWORD ci, DWORD &r);
extern BYTE (*subwb)(DWORD a, DWORD b, DWORD bi, DWORD &r);
extern BYTE (*cntlz)(DWORD a);
extern BYTE (*cnttz)(DWORD a);

extern void (*and_op)(DWORD *a, DWORD *b, DWORD *r, DWORD idx);
extern void (*ior_op)(DWORD *a, DWORD *b, DWORD *r, DWORD idx);
extern void (*xor_op)(DWORD *a, DWORD *b, DWORD *r, DWORD idx);

extern BYTE CPU_ALIGN;

extern bool s_adx;
extern bool s_bmi1;
extern bool s_bmi2;
extern bool s_avx2;
extern bool s_sse2;
extern bool s_lzcnt;

extern bool c_arm;
extern bool c_x86;

void InitCPUFeatures();

}

#endif // LL_WRP_H
