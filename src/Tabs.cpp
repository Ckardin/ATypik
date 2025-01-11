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

/// @file Tabs.cpp
/// @brief Source de Tabs
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#include "Tabs.h"

namespace Fenyx::Types
{

#ifdef LITTLE_ENDIAN
	void SwapBytes(barray &bytes) {
		BYTE temp, j;

		for(BYTE i = 1; i < (bytes[0] / 2); i = i + 1) {
			j = (bytes[0] - 1) - i;

			temp     = bytes[i];
			bytes[i] = bytes[j];
			bytes[j] = temp;
		}
	}
#endif // LITTLE_ENDIAN

/// @brief BytesArray - Convertit un nombre en tableau d'octets
///
/// @param[in] data: nombre à convertir
///
/// @return un STable d'octets représentant le nombre.
barray BytesArray(allnum data) {
	using T = std::decay_t<decltype(data)>;
	barray bytes;

	if (!bytes.GetFatal()) {
		bytes[0] = sizeof(T);
		std::visit([&bytes](auto && v) -> void {
			for(BYTE i = 1; i < static_cast<BYTE>(sizeof(T)); i = i + 1) bytes[i] = v >> (i * 8);
		}, data);

#ifdef LITTLE_ENDIAN
		SwapBytes(bytes);
#endif // LITTLE_ENDIAN
	}

	return bytes;
}

}

