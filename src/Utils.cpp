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

/// @brief GetTimestampMilli - Réceupères le timestamp en millisecondes
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
char toChar(BYTE a) {
	return static_cast<char>(a);
}

/// @brief toASCII - Convertit un caractère en son équivalent ASCII
///
/// @param[in] c: caractère à convertir
///
/// @return Le nombre ASCCI convertit.
BYTE toAscii(char c) {
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

