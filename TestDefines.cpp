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

/// @file TestDefines.cpp
/// @brief Source de TestDefines
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#include "Defines.h"
#include <iostream>

int main(void) {
 	Fenyx::Types::TriBool trb;
    Fenyx::Types::TriBool trb2(true, false);
    Fenyx::Types::TriBool trb3(trb2);

    if (trb2 != trb3)             std::cout << "Test KO." << std::endl;
    if (trb2.GetValue() != false) std::cout << "Test KO." << std::endl;

    std::cout << "TRB1 => " << trb << std::endl;
    std::cout << "TRB2 => " << trb2 << std::endl;
    std::cout << "TRB3 => " << trb3 << std::endl;

    std::cout << "Test OK." << std::endl;

    return 0;
}

