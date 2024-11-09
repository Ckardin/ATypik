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

/// @file AlgoMath.h
/// @brief Header de AlgoMath
/// @author F&nµx
/// @version 1.0
/// @date 09/11/2024

#ifndef ALGOMATH_H
#define ALGOMATH_H

#include "Utils.h" // for <random> include and [Defines]
#include "InfInt.h"

namespace Fenyx::Types
{

InfInt Pow         (InfInt const& x, InfInt const& n);
InfInt Pow2        (InfInt const& n);
InfInt Pow16       (InfInt const& n);
InfInt PowM        (InfInt const& a, InfInt const& b, InfInt const& m);
InfInt PowM2       (InfInt const& a, InfInt const& b, InfInt const& m);
InfInt RandTestMR  (InfInt const& n);
bool   MillerTest  (InfInt const& n, InfInt const& a);
bool   MillerRabin (InfInt const& n, BYTE k = 48);
void   ExtEuclide  (InfInt const& a, InfInt const& b, InfInt &r, InfInt &u, InfInt &v);

}

#endif //ALGOMATH_H
