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

/// @file StrUtils.h
/// @brief Header de StrUtils
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#ifndef STRUTILS_H
#define STRUTILS_H

#include <sstream>
#include "Utils.h"

namespace Fenyx::Types
{

std::ostream& operator<<(std::ostream& os, SWORD const& v);
std::ostream& operator<<(std::ostream& os, sSWORD const& v);

std::istream& operator>>(std::istream& is, SWORD& v);
std::istream& operator>>(std::istream& is, sSWORD& v);

template<class T>
std::string toString(T const& t);
template<class T>
std::string toHexString(T const& t);
template<class T>
T fromString(std::string const& s);

std::string CompleteNbr(allpnum nbr);

bool IsNum(char c);
bool IsHex(char c);
bool IsNumS(std::string const& str);
bool IsHexS(std::string const& str);
BYTE HexN(char c, bool &err);
// std::string DecTHex(std::string str, bool &err);
// std::string DecFHex(std::string const& str, bool &err);



template<class T>
/// @brief toString - Convertit une donnée en std::string
///
/// @param[in] t: donnée à convertir
///
/// /!\ S'assurer que le type de la donnée à convertir possède une surcharge de l'opérateur [<<].
std::string toString(T const& t) {
	std::ostringstream oss;
	oss << t;

	return oss.str();
}

template<class T>
/// @brief toHexString - Convertit une donnée en std::string sous forme hexadécimale
///
/// @param[in] t: donnée à convertir
///
/// /!\ S'assurer que le type de la donnée à convertir possède une surcharge de l'opérateur [<<].
std::string toHexString(T const& t) {
	std::ostringstream oss;
	oss << std::hex << t;

	return oss.str();
}

template<class T>
/// @brief fromString - Convertit un std::string en une donnée
///
/// @param{in] s: std::string à convertir
///
/// /!\ S'assurer que le type de la donnée à convertir possède une surcharge de l'opérateur [>>].
T fromString(std::string const& s) {
	T ret;
	std::istringstream iss(s);

	iss >> ret;
	return ret;
}

}

#endif //STRUTILS_H
