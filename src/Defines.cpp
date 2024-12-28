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

/// @brief TriBool - Contructeur de copie
///
/// @param[in] b: TriBool de copie
///
/// Constructeur de copie de la classe TriBool.
TriBool::TriBool(TriBool const& b) {
    if(b.n.has_value()) n = b.n.value();
    else                n.reset();
}

/// @brief TriBool - Constructeur d'affectation
///
/// @param[in] u: booléan (true si indéfini, false sinon)
/// @param[in] v: booléan (valeur à affecter)
///
/// Constructeur d'affectation de la classe TriBool.
TriBool::TriBool(const bool u, bool v) {
    if(u) n.reset();
    else  n = v;
}

/// @brief SetValue - Affecter une valeur au tri-booléan
///
/// @param[in] u: booléan (true si indéfini, false sinon)
/// @param[in] v: booléan (valeur à affecter)
void TriBool::SetValue(const bool u, bool v) {
    if(u) n.reset();
    else  n = v;
}

/// @brief IsUndef - Test si le tri-booléan est indéfini ou pas
///
/// @return true si indéfini, false sinon.
bool TriBool::IsUndef() const {
    return !(n.has_value());
}

/// @brief GetValue - Récupères la valeur du tri-booléan
///
/// @return false si indéfini, la valeur du tri-booléan sinon.
bool TriBool::GetValue() const {
    return (n.has_value()) ? n.value() : false;
}

/// @brief operator= - Opérateur d'affectation
///
/// @param[in] b: TriBool à affecter
///
/// @return Une référence sur le TriBool affecté.
TriBool& TriBool::operator= (TriBool const& b) {
    if(!(b.n.has_value())) n.reset();
    else                   n = b.n.value();

    return *this;
}

/// @brief operator|= - Opérateur d'affectation avec OR
///
/// @param[in] b: TriBool à affecter
///
/// @return Une référence sur le TriBool affecté.
TriBool& TriBool::operator|=(TriBool const& b) {
    if (b.n.has_value()    && n.has_value()) n = n.value() | b.n.value();
    if (!(b.n.has_value()) && n.has_value()) n = n.value() | false;
    if (b.n.has_value()   && !n.has_value()) n = b.n.value();

    return *this;
}

/// @brief operator&= - Opérateur d'affectation avec AND
///
/// @param[in] b: TriBool à affecter
///
/// @return Une réference sur le TriBool affecté.
TriBool& TriBool::operator&=(TriBool const& b) {
    if (b.n.has_value()    && n.has_value()) n = n.value() & b.n.value();
    if (!(b.n.has_value()) && n.has_value()) n = n.value() & false;
    if (b.n.has_value()   && !n.has_value()) n = b.n.value();

    return *this;
}

/// @brief operator^= - Opérateur d'affectation avec XOR
///
/// @param[in] b: TriBool à affecter
///
/// @return Une réference sur le TriBool affecté.
TriBool& TriBool::operator^=(TriBool const& b) {
    if (b.n.has_value()    && n.has_value()) n = n.value() ^ b.n.value();
    if (!(b.n.has_value()) && n.has_value()) n = n.value() ^ false;
    if (b.n.has_value()   && !n.has_value()) n = b.n.value();

    return *this;
}

/// @brief operator~ - Opérateur NO
///
/// @return Une référence sur le TriBool affecté.
TriBool& TriBool::operator~ () {
    if (n.has_value()) n = (n.value() != true);
    else               n = true;

    return *this;
}


/// @brief operator| - Opérateur OR
///
/// @param[in] b1: lhs
/// @param[in] b2: rhs
///
/// @return Un TriBool égal à (b1 OR b2).
TriBool operator|(TriBool const& b1, TriBool const& b2) {
    TriBool ret;
    ret.n.reset();

    if (b1.n.has_value()    && b2.n.has_value()) ret.n = b1.n.value() | b2.n.value();
    if (!(b2.n.has_value()) && b1.n.has_value()) ret.n = b1.n.value() | false;
    if (b2.n.has_value()   && !b1.n.has_value()) ret.n = b2.n.value();

    return ret;
}

/// @brief operator& - Opérateur AND
///
/// @param[in] b1: lhs
/// @param[in] b2: rhs
///
/// @return Un TriBool égal à (b1 AND b2).
TriBool operator&(TriBool const& b1, TriBool const& b2) {
    TriBool ret;
    ret.n.reset();

    if (b1.n.has_value()    && b2.n.has_value()) ret.n = b1.n.value() & b2.n.value();
    if (!(b2.n.has_value()) && b1.n.has_value()) ret.n = b1.n.value() & false;
    if (b2.n.has_value()   && !b1.n.has_value()) ret.n = b2.n.value();

    return ret;
}

/// @brief operator^ - Opérateur XOR
///
/// @param[in] b1: lhs
/// @param[in] b2: rhs
///
/// @return Un TriBool égal à (b1 XOR b2).
TriBool operator^(TriBool const& b1, TriBool const& b2) {
    TriBool ret;
    ret.n.reset();

    if (b1.n.has_value()    && b2.n.has_value()) ret.n = b1.n.value() ^ b2.n.value();
    if (!(b2.n.has_value()) && b1.n.has_value()) ret.n = b1.n.value() ^ false;
    if (b2.n.has_value()   && !b1.n.has_value()) ret.n = b2.n.value();

    return ret;
}

/// @brief operator== - Test d'égalité entre TriBool
///
/// @param[in] b1: lhs
/// @param[in] b2: rhs
///
/// @return true si égaux, false sinon.
bool operator==(TriBool const& b1, TriBool const& b2) {
    if (b1.n.has_value() && b2.n.has_value()) return (b1.n.value() == b2.n.value());

    return false;
}

/// @brief operator!= - Test d'inégalité entre TriBool
///
/// @param[in] b1: lhs
/// @param[in] b2: rhs
///
/// @return true si différents, false sinon.
bool operator!=(TriBool const& b1, TriBool const& b2) {
    return !(b1 == b2);
}

/// @brief operator== - Test d'égalité entre TriBool et bool
///
/// @param[in] b1: lhs
/// @param[in] b2: rhs
///
/// @return true si égaux, false sinon.
bool operator==(TriBool const& b1, bool const& b2) {
    if (b1.n.has_value()) return b1.n.value() == b2;

    return false;
}

/// @brief operator!= - Test d'ínégalité entre TriBool et bool
///
/// @param[in] b1: lhs
/// @param[in] b2: rhs
///
/// @return true si différents, false sinon.
bool operator!=(TriBool const& b1, bool const& b2) {
    return !(b1 == b2);
}

/// @brief operator== - Test d'égalité entre bool et TriBool
///
/// @param[in] b1: lhs
/// @param[in] b2: rhs
///
/// @return true si égaux, false sinon.
bool operator==(bool const& b1, TriBool const& b2) {
    if (b2.n.has_value()) return b2.n.value() == b1;

    return false;
}

/// @brief operator!= - Test d'inégalité entre bool et TriBool
///
/// @param[in] b1: lhs
/// @param[in] b2: rhs
///
/// @return true si différents, false sinon.
bool operator!=(bool const& b1, TriBool const& b2) {
    return !(b1 == b2);
}

/// @brief operator<< - Opérateur de flux de sortie pour TriBool
///
/// @param[in] os: flux de sortie
/// @param[in] b: TriBool concerné
///
/// @return Une référence sur le flux de sortie affecté.
std::ostream& operator<<(std::ostream& os, TriBool const& b) {
    if (!(b.n.has_value())) {
        os << "U";
        return os;
    }

    if (b.n.value() == true) os << "T";
    else                     os << "F";

    return os;
}

/// @brief operator>> - Opérateur de flux d'entrée pour TriBool
///
/// @param[in] is: flux d'entrée
/// @param[in] b: TriBool concerné
///
/// @return Une référence sur le flux d'entrée affecté.
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

