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
	barray bytes(0);

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

