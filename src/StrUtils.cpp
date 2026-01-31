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
/// @brief Source de StrUtils
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#include "StrUtils.h"

namespace Fenyx::Types
{

/// @brief operator<< - Opérateur de flux de sortie pour SWORD
/// 
/// @param[in] os: flux de sortie
/// @param[in] v: SWORD concerné
/// 
/// @return Une référence sur le flux de sortie affecté.
std::ostream& operator<<(std::ostream& os, const SWORD v) {
	SWORD n = v;
	std::string ret = ""; // NOLINT(*-redundant-string-init)
	STable<char, 10> chars;

	for (BYTE i = 0 ; i < 10 ; i = i + 1) chars[i] = toChar(i + 48);

	while (n != 0) {
		ret += chars[(n % 10)];
		n /= 10;
	}

	os << ret;
	return os;
}
	
/// @brief operator<< - Opérateur de flux de sortie pour sSWORD
/// 
/// @param[in] os: flux de sortie
/// @param[in] v: sSWORD concerné
/// 
/// @return Une référence sur le flux de sortie affecté.
std::ostream& operator<<(std::ostream& os, const sSWORD v) {
	sSWORD n = v;
	std::string ret = ""; // NOLINT(*-redundant-string-init)
	STable<char, 10> chars;

	for (BYTE i = 0 ; i < 10 ; i = i + 1) chars[i] = toChar(i + 48);

	if (n < 0) {
		ret += "-";
		n = -(n);
	}

	while (n != 0) {
		ret += chars[(n % 10)];
		n /= 10;
	}

	os << ret;
	return os;
}

/// @brief operator>> - Opérateur de flux d'entrée pour SWORD
/// 
/// @param[in] is: flux d'entrée
/// @param[in] v: SWORD concerné
/// 
/// @return Une référence sur le flux d'entrée affecté.
std::istream& operator>>(std::istream& is, SWORD& v) {
	std::string t;
	is >> t;

	v = 0;
	for (std::string::size_type i = 0; i < t.length(); i = i + 1) {
		const auto temp_c = static_cast<SWORD>(pow(10.0, static_cast<double>((t.length() - 1)) - static_cast<double>(i)));
		v += fromString<BYTE>(std::string{t[i]}) * temp_c;
	}

	return is;
}

/// @brief operator>> - Opérateur de flux d'entrée pour sSWORD
/// 
/// @param[in] is: flux d'entrée
/// @param[in] v: sSWORD concerné
/// 
/// @return Une référence sur le flux d'entrée affecté.
std::istream& operator>>(std::istream& is, sSWORD& v) {
	bool neg = false;
	std::string t;
	is >> t;

	if (t.at(0) == '-') {
		neg = true;
		t.erase(0, 1);
	}

	v = 0;
	for (std::string::size_type i = 0; i < t.length(); i = i + 1) {
		const auto temp_c = static_cast<sSWORD>(pow(10.0, static_cast<double>((t.length() - 1)) - static_cast<double>(i)));
		v += fromString<BYTE>(std::string{t[i]}) * temp_c;
	}

	if (neg) v *= -1;
	return is;
}

/// @brief toChar - Convertit un nombre ASCII en son caractère correspondant
///
/// @param[in] a: nombre ASCII à convertir
///
/// @return Le caractère convertit.
char toChar(const BYTE a) {
	return static_cast<char>(a);
}

/// @brief toASCII - Convertit un caractère en son équivalent ASCII
///
/// @param[in] c: caractère à convertir
///
/// @return Le nombre ASCCI convertit.
BYTE toAscii(const char c) {
	return static_cast<BYTE>(c);
}

/// @brief CompleteNbr - Rajoute un '0' avant un nombre inférieur à 10
/// 
/// @param[in] nbr: nombre à compléter
/// 
/// @return Un std::string avec le nombre tel quel si supérieur à 10, sinon avec un '0' rajouté devant.
std::string CompleteNbr(allpnum nbr) {
	return std::visit([](auto && v) -> std::string {
		using T = std::decay_t<decltype(v)>;
		return (v < 10) ? std::string("0" + toString<T>(v)) : toString<T>(v);
	}, nbr);
}

/// @brief IsNum - Test si un caractère représente un chiffre ou pas
/// 
/// @param[in] c: caractère à tester
/// 
/// @return true si [c] représente un chiffre (0-9), false sinon.
bool IsNum(const char c) {
	STable<char, 16> HexConv;

	for (BYTE i = 0 ; i < 10; i = i + 1) HexConv[i] = toChar(i + 48);
	for (BYTE i = 10; i < 16; i = i + 1) HexConv[i] = toChar((i - 10) + 65);

	for (BYTE i = 0; i < 10; i = i + 1) {
		if(c == HexConv[i]) return true;
	}

	return false;
}

/// @brief IsHex - Test si un caractère représente un chiffre hexadécimal ou pas
///
/// @param[in] c: caractère à tester
///
/// @return true si [c] représente un chiffre hexadécimal (0-9 ou A-F), false sinon.
bool IsHex(const char c) {
	STable<char, 16> HexConv;

	for (BYTE i = 0 ; i < 10; i = i + 1) HexConv[i] = toChar(i + 48);
	for (BYTE i = 10; i < 16; i = i + 1) HexConv[i] = toChar((i - 10) + 65);

	for (BYTE i = 0; i < 16; i = i + 1) {
		if(c == HexConv[i]) return true;
	}

	return false;
}

/// @brief IsNumS - Test si un std::string représente un nombre
///
/// @param[in] str: std::string à tester
///
/// @return true si [s] représente un nombre (suite de caractères de 0-9), false sinon.
bool IsNumS(const std::string &str) {
	for (std::string::size_type i = 0; i < str.length(); i = i + 1) {
		if(!IsNum(str[i])) return false;
	}

	return true;
}

/// @brief IsHexS - Test si un std::string représente un nombre hexadécimal
///
/// @param[in] str: std::string à tester
///
/// @return true si [s] représente un nombre hexadécimal (suite de caractères de 0-9 et A-F), false sinon.
bool IsHexS(const std::string &str) {
	for (std::string::size_type i = 0; i < str.length(); i = i + 1) {
		if(!IsHex(str[i])) return false;
	}

	return true;
}

/// @brief HexN - Donne la valeur en décimal (0-15) d'un caractère hexadécimal (0-F)
///
/// @param[in] c: caractère concerné
/// @param[out] err: reférence sur booléan (true si erreur, false sinon)
///
/// @return La valeur décimal si réussi, 0 sinon.
BYTE HexN(const char c, bool &err) {
	STable<char, 16> HexConv;

	for (BYTE i = 0 ; i < 10; i = i + 1) HexConv[i] = toChar(i + 48);
	for (BYTE i = 10; i < 16; i = i + 1) HexConv[i] = toChar((i - 10) + 65);

	if (!IsHex(c)) {
		err = true; return 0;
	}

	for (BYTE i = 0; i < 16; i = i + 1) {
		if(c == HexConv[i]) {
			err = false; return i;
		}
	}

	err = false;
	return 0;
}

/*
std::string DecTHex(std::string str, bool &err) {

}

std::string DecFHex(std::string const& str, bool &err) {

}
*/

}

