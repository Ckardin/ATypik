/// English version
/*
Copyright (C) 2025 BOUCARD NICOLLE Jody

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
Copyright (C) 2025 BOUCARD NICOLLE Jody

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

/// @file ll_Wrp.cpp
/// @brief Source de ll_Wrp
/// @author F&nµx
/// @version 6.0
/// @date 30/01/2026

#include "ll_Wrp.h"

namespace Fenyx::Types::CPU
{

BYTE (*addwc)(DWORD a, DWORD b, DWORD ci, DWORD &r)     = addwc_flb;
BYTE (*subwb)(DWORD a, DWORD b, DWORD bi, DWORD &r)     = subwb_flb;
BYTE (*cntlz)(DWORD a)                                  = cntlz_flb;
BYTE (*cnttz)(DWORD a)                                  = cnttz_flb;

void (*and_op)(DWORD *a, DWORD *b, DWORD *r, DWORD idx) = and_flb;
void (*ior_op)(DWORD *a, DWORD *b, DWORD *r, DWORD idx) = ior_flb;
void (*xor_op)(DWORD *a, DWORD *b, DWORD *r, DWORD idx) = xor_flb;

BYTE CPU_ALIGN = 1;

bool s_adx   = false;
bool s_bmi1  = false;
bool s_bmi2  = false;
bool s_avx2  = false;
bool s_sse2  = false;
bool s_lzcnt = false;

bool c_arm  = false;
bool c_x86  = false;

void InitCPUFeatures() {
#if defined(__x86_64__)
	c_x86 = true;

	if (__builtin_cpu_supports("adx")) {
		s_adx = true;
		addwc = addwc_adx;
		subwb = subwb_adx;
	}

	if (__builtin_cpu_supports("bmi")) {
		s_bmi1 = true;
		cnttz  = cnttz_bmi;
	}

	if (__builtin_cpu_supports("bmi2")) s_bmi2 = true;
	if (__builtin_cpu_supports("sse2")) {
		s_sse2 = true;
		and_op = and_sse2;
		ior_op = ior_sse2;
		xor_op = xor_sse2;

		CPU_ALIGN = 4;
	}

	if (__builtin_cpu_supports("avx2")) {
		s_avx2 = true;
		and_op = and_avx2;
		ior_op = ior_avx2;
		xor_op = xor_avx2;

		CPU_ALIGN = 8;
	}

	if (__builtin_cpu_supports("lzcnt")) {
		s_lzcnt = true;
		cntlz   = cntlz_int;
	}
#elif defined (__aarch64__)
	c_arm = true;

	addwc = addwc_arm;
	subwb = subwb_arm;
	cntlz = cntlz_arm;
	cnttz = cnttz_arm;

	and_op = and_arm;
	ior_op = ior_arm;
	xor_op = xor_arm;

	CPU_ALIGN = 4;
#endif
}

static void CPUInit() { InitCPUFeatures(); }
[[maybe_unused]] static bool init = (CPUInit(), true);

}

