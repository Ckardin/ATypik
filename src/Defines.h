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

/// @file Defines.h
/// @brief Header de Defines
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#ifndef DEFINES_H
#define DEFINES_H

#include <variant>
#include <cstdint>
#include <optional>
#include <istream>

namespace Fenyx::Types
{

typedef uint8_t      BYTE;
typedef uint16_t     WORD;
typedef uint32_t    DWORD;
typedef uint64_t    QWORD;
typedef __uint128_t SWORD;

typedef int8_t      sBYTE;
typedef int16_t     sWORD;
typedef int32_t    sDWORD;
typedef int64_t    sQWORD;
typedef __int128_t sSWORD;

using allpnum = std::variant<unsigned int, BYTE, WORD, DWORD, QWORD, SWORD>;
using allnum  = std::variant<unsigned int, BYTE, WORD, DWORD, QWORD, SWORD, int, sBYTE, sWORD, sDWORD, sQWORD, sSWORD>;

/// @brief TriBool - Classe qui permet de gérer les tri-booléan
class TriBool
{
public:
    TriBool() = default;
    TriBool(TriBool const& b);
    explicit TriBool(bool u, bool v = false);

    void SetValue(bool u = true, bool v = false);
    [[nodiscard]] bool IsUndef() const;
    [[nodiscard]] bool GetValue() const;

    TriBool& operator= (TriBool const& b);
    TriBool& operator|=(TriBool const& b);
    TriBool& operator&=(TriBool const& b);
    TriBool& operator^=(TriBool const& b);
    TriBool& operator~ ();

private:
    std::optional<bool> n;

    friend TriBool operator|(const TriBool& b1, const TriBool& b2);
    friend TriBool operator&(const TriBool& b1, const TriBool& b2);
    friend TriBool operator^(const TriBool& b1, const TriBool& b2);

    friend bool operator==(const TriBool& b1, const TriBool& b2);
    friend bool operator!=(const TriBool& b1, const TriBool& b2);
    friend bool operator==(const TriBool& b1, const bool& b2);
    friend bool operator!=(const TriBool& b1, const bool& b2);
    friend bool operator==(const bool& b1, const TriBool& b2);
    friend bool operator!=(const bool& b1, const TriBool& b2);

    friend std::ostream& operator<<(std::ostream& os, TriBool const& b);
    friend std::istream& operator>>(std::istream& is, TriBool& b);
};

}


#endif //DEFINES_H
