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

/// @file Utils.h
/// @brief Source de Utils
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#include "Utils.h"

namespace Fenyx::Types
{

/// @brief GetTimestamp - Récupères le timestamp en secondes
///
/// @return Un DWORD représentant le timestamp en secondes.
DWORD GetTimestamp() {
	using namespace std::chrono;
	return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}

/// @brief GetTimestampMilli - Récupères le timestamp en millisecondes
///
/// @return Un QWORD représentant le timestamp en millisecondes.
QWORD GetTimestampMilli() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
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

/// @brief MicroChaoCrypt - Renvoie un nombre pseudo-aléatoire de 32 bits
///
/// @param[in] orand: valeur de pivot pour le générateur
///
/// @return Un DWORD contenant le nombre pseudo-aléatoire généré.
///
/// Utilise une version (très) simplifiée de l'algorithme ChaoCrypt.
DWORD MicroChaoCrypt(const DWORD orand) {
	std::random_device rdev;

	const DWORD t1 = rdev();
	const DWORD t2 = rdev() % 32;

	allnum t;
	t.emplace<0>(0);
	BytesArray(t);

	return ((t1 << t2) ^ orand);
}

}

