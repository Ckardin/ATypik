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

/// @file Int.h
/// @brief Header de Int
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#ifndef INT_H
#define INT_H

#include "Tabs.h"

namespace Fenyx::Types
{

class Int
{
public:
  	Int();
    Int(Int const &oth);
    Int(allpnum const &oth);
    Int(std::string const &oth);

    [[nodiscard]] bool GetFatal() const;
    [[nodiscard]] bool GetError() const;

    Int &operator=(Int const &oth);
    Int &operator=(allpnum const &oth);
    Int &operator=(std::string const &oth);
    Int &operator+=(Int const &oth);
    Int &operator-=(Int const &oth);
    Int &operator*=(Int const &oth);
    Int &operator/=(Int const &oth);
    Int &operator%=(Int const &oth);
    Int &operator^=(Int const &oth);

    ~Int();

private:
	bool IsZero() const;
  	DTable<DWORD> *rawd;
    bool fatal;
    bool error;

    friend Int operator+(const Int& lhs, const Int& rhs);
    friend Int operator-(const Int& lhs, const Int& rhs);
    friend Int operator*(const Int& lhs, const Int& rhs);
    friend Int operator/(const Int& lhs, const Int& rhs);
    friend Int operator%(const Int& lhs, const Int& rhs);
    friend Int operator^(const Int& lhs, const Int& rhs);

    friend bool operator==(const Int& lhs, const Int& rhs);
    friend bool operator!=(const Int& lhs, const Int& rhs);
    friend bool operator<(const Int& lhs, const Int& rhs);
    friend bool operator>(const Int& lhs, const Int& rhs);
    friend bool operator<=(const Int& lhs, const Int& rhs);
    friend bool operator>=(const Int& lhs, const Int& rhs);

    friend Int operator<<(std::ostream& os, const Int& rhs);
    friend Int operator>>(std::istream& is, const Int& rhs);
};

}

#endif //INT_H
