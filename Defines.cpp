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

/// @file Defines.cpp
/// @brief Source de Defines
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#include "Defines.h"


namespace Fenyx::Types
{

TriBool::TriBool(TriBool const& b) {
    if(b.n.has_value()) n = b.n.value();
    else                n.reset();
}

TriBool::TriBool(const bool u, bool v) {
    if(u) n.reset();
    else  n = v;
}

void TriBool::SetValue(const bool u, bool v) {
    if(u) n.reset();
    else  n = v;
}

bool TriBool::IsUndef() const {
    return !(n.has_value());
}

bool TriBool::GetValue() const {
    return (n.has_value()) ? n.value() : false;
}

TriBool& TriBool::operator= (TriBool const& b) {
    if(!(b.n.has_value())) n.reset();
    else                   n = b.n.value();

    return *this;
}

TriBool& TriBool::operator|=(TriBool const& b) {
    if (b.n.has_value()    && n.has_value()) n = n.value() | b.n.value();
    if (!(b.n.has_value()) && n.has_value()) n = n.value() | false;
    if (b.n.has_value()   && !n.has_value()) n = b.n.value();

    return *this;
}

TriBool& TriBool::operator&=(TriBool const& b) {
    if (b.n.has_value()    && n.has_value()) n = n.value() & b.n.value();
    if (!(b.n.has_value()) && n.has_value()) n = n.value() & false;
    if (b.n.has_value()   && !n.has_value()) n = b.n.value();

    return *this;
}

TriBool& TriBool::operator^=(TriBool const& b) {
    if (b.n.has_value()    && n.has_value()) n = n.value() ^ b.n.value();
    if (!(b.n.has_value()) && n.has_value()) n = n.value() ^ false;
    if (b.n.has_value()   && !n.has_value()) n = b.n.value();

    return *this;
}

TriBool& TriBool::operator~ () {
    if (n.has_value()) n = (n.value() != true);
    else               n = true;

    return *this;
}


TriBool operator|(TriBool const& b1, TriBool const& b2) {
    TriBool ret;
    ret.n.reset();

    if (b1.n.has_value()    && b2.n.has_value()) ret.n = b1.n.value() | b2.n.value();
    if (!(b2.n.has_value()) && b1.n.has_value()) ret.n = b1.n.value() | false;
    if (b2.n.has_value()   && !b1.n.has_value()) ret.n = b2.n.value();

    return ret;
}

TriBool operator&(TriBool const& b1, TriBool const& b2) {
    TriBool ret;
    ret.n.reset();

    if (b1.n.has_value()    && b2.n.has_value()) ret.n = b1.n.value() & b2.n.value();
    if (!(b2.n.has_value()) && b1.n.has_value()) ret.n = b1.n.value() & false;
    if (b2.n.has_value()   && !b1.n.has_value()) ret.n = b2.n.value();

    return ret;
}

TriBool operator^(TriBool const& b1, TriBool const& b2) {
    TriBool ret;
    ret.n.reset();

    if (b1.n.has_value()    && b2.n.has_value()) ret.n = b1.n.value() ^ b2.n.value();
    if (!(b2.n.has_value()) && b1.n.has_value()) ret.n = b1.n.value() ^ false;
    if (b2.n.has_value()   && !b1.n.has_value()) ret.n = b2.n.value();

    return ret;
}

bool operator==(TriBool const& b1, TriBool const& b2) {
    if (b1.n.has_value() && b2.n.has_value()) return (b1.n.value() == b2.n.value());

    return false;
}

bool operator!=(TriBool const& b1, TriBool const& b2) {
    return !(b1 == b2);
}

bool operator==(TriBool const& b1, bool const& b2) {
    if (b1.n.has_value()) return b1.n.value() == b2;

    return false;
}

bool operator!=(TriBool const& b1, bool const& b2) {
    return !(b1 == b2);
}

bool operator==(bool const& b1, TriBool const& b2) {
    if (b2.n.has_value()) return b2.n.value() == b1;

    return false;
}

bool operator!=(bool const& b1, TriBool const& b2) {
    return !(b1 == b2);
}

std::ostream& operator<<(std::ostream& os, TriBool const& b) {
    if (!(b.n.has_value())) {
        os << "U";
        return os;
    }

    return os;
}

std::istream& operator>>(std::istream& is, TriBool& b) {
    std::string t;

    is >> t;

    if (t == "U") b.n.reset();
    else {
        if(t == "T") b.n = true;
        else         b.n = false;
    }

    return is;
}

}

