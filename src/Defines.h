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
