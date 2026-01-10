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
#include <immintrin.h>
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

namespace Fenyx::Types
{

ALWAYS_INLINE ATTR_ADX BYTE addwc(const DWORD a, const DWORD b, const DWORD ci, DWORD &r) {
#if defined(__x86_64__) && defined(__ADX__)
	return _addcarry_u32(ci, a, b, &r);
#elif defined(__aarch64__)
	return __builtin_addc(a, b, ci, &r);
#else
	QWORD t = static_cast<QWORD>(a) + static_cast<QWORD>(b) + static_cast<QWORD>(ci);
	r = static_cast<DWORD>(t);
	return (t >> 32) & 1;
#endif
}

ALWAYS_INLINE ATTR_ADX BYTE subwb(const DWORD a, const DWORD b, const DWORD bi, DWORD &r) {
#if defined(__x86_64__) && defined(__ADX__)
	return _subborrow_u32(bi, a, b, &r);
#elif defined(__aarch64__)
	return __builtin_subc(a, b, bi, &r);
#else
	QWORD t = static_cast<QWORD>(a) - static_cast<QWORD>(b) - static_cast<QWORD>(bi);
	r = static_cast<DWORD>(t);
	return (t >> 63) & 1;
#endif
}

ALWAYS_INLINE ATTR_LZCNT BYTE cntlz(const DWORD a) {
#if defined(__x86_64__) && defined(__LZCNT__)
	return a ? _lzcnt_u32(a) : 32;
#elif defined(__aarch64__)
	return a ? __builtin_clz(a) : 32;
#else
	if (a == 0) return 32;
	DWORD n = 0, mask = 0x80000000u;

	while ((a & mask) == 0) {
		mask >>= 1;
		n += 1;
	}

	return n;
#endif
}

ALWAYS_INLINE ATTR_BMI1 BYTE cnttz(DWORD a) {
#if defined(__x86_64__) && defined(__BMI__)
	return a ? _tzcnt_u32(a) : 32;
#elif defined(__aarch64__)
	return a ? __builtin_ctz(a) : 32;
#else
	if (a == 0) return 32;
	DWORD n = 0;

	while ((a & 1) == 0) {
		a >>= 1;
		n += 1;
	}

	return n;
#endif
}

}

#endif // LL_WRP_H
