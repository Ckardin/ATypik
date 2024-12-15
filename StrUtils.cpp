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

/// @file StrUtils.h
/// @brief Source de StrUtils
/// @author F&nµx
/// @version 1.0
/// @date 02/11/2024

#include "StrUtils.h"

namespace Fenyx::Types
{

std::ostream& operator<<(std::ostream& os, SWORD const& v) {
	SWORD n = v;
	std::string ret = ""; // NOLINT(*-redundant-string-init)
	STable<char, 10> chars('0');

	if (chars.GetFatal()) return os;
	for (BYTE i = 0 ; i < 10 ; ++i) chars[i] = toChar(i + 48);

	while (n != 0) {
		ret += chars[(n % 10)];
		n /= 10;
	}

	os << ret;
	return os;
}

std::ostream& operator<<(std::ostream& os, sSWORD const& v) {
	sSWORD n = v;
	std::string ret = ""; // NOLINT(*-redundant-string-init)
	STable<char, 10> chars('0');

	if (chars.GetFatal()) return os;
	for (BYTE i = 0 ; i < 10 ; ++i) chars[i] = toChar(i + 48);

	if (n < 0) {
		ret += "-";
		n = -(n);
	}

	while (n != 0) {
		ret += chars[(n % 10)];
		n /= 10;
	}

	os << ret;
	return os;
}

std::istream& operator>>(std::istream& is, SWORD& v) {
	std::string t;
	is >> t;

	v = 0;
	for (std::string::size_type i = 0; i < t.length(); ++i) {
		const auto temp_c = static_cast<SWORD>(pow(10, static_cast<double>((t.length() - 1)) - static_cast<double>(i)));
		v += fromString<BYTE>(std::string{t[i]}) * temp_c;
	}

	return is;
}

std::istream& operator>>(std::istream& is, sSWORD& v) {
	bool neg = false;
	std::string t;
	is >> t;

	if (t.at(0) == '-') {
		neg = true;
		t.erase(0, 1);
	}

	v = 0;
	for (std::string::size_type i = 0; i < t.length(); ++i) {
		const auto temp_c = static_cast<sSWORD>(pow(10, static_cast<double>((t.length() - 1)) - static_cast<double>(i)));
		v += fromString<BYTE>(std::string{t[i]}) * temp_c;
	}

	if (neg) v *= -1;
	return is;
}


std::string CompleteNbr(allpnum nbr) {
	return std::visit([](auto && v) -> std::string {
		using T = std::decay_t<decltype(v)>;
		return (v < 10) ? std::string("0" + toString<T>(v)) : toString<T>(v);
	}, nbr);
}

bool IsNum(char c) {
	STable<char, 16> HexConv('0');

	if (HexConv.GetFatal()) return false;
	for (BYTE i = 0 ; i < 10; ++i) HexConv[i] = toChar(i + 48);
	for (BYTE i = 10; i < 16; ++i) HexConv[i] = toChar((i - 10) + 65);

	for (BYTE i = 0; i < 10; ++i) {
		if(c == HexConv[i]) return true;
	}

	return false;
}

bool IsHex(char c) {
	STable<char, 16> HexConv('0');

	if (HexConv.GetFatal()) return false;
	for (BYTE i = 0 ; i < 10; ++i) HexConv[i] = toChar(i + 48);
	for (BYTE i = 10; i < 16; ++i) HexConv[i] = toChar((i - 10) + 65);

	for (BYTE i = 0; i < 16; ++i) {
		if(c == HexConv[i]) return true;
	}

	return false;
}

bool IsNumS(std::string const& str) {
	for (std::string::size_type i = 0; i < str.length(); ++i) {
		if(!IsNum(str[i])) return false;
	}

	return true;
}

bool IsHexS(std::string const& str) {
	for (std::string::size_type i = 0; i < str.length(); ++i) {
		if(!IsHex(str[i])) return false;
	}

	return true;
}

BYTE HexN(const char c, bool &err) {
	STable<char, 16> HexConv('0');

	if (HexConv.GetFatal()) {
		err = true; return 0;
	}
	for (BYTE i = 0 ; i < 10; ++i) HexConv[i] = toChar(i + 48);
	for (BYTE i = 10; i < 16; ++i) HexConv[i] = toChar((i - 10) + 65);

	if (!IsHex(c)) {
		err = true; return 0;
	}

	for (BYTE i = 0; i < 16; i = i + 1) {
		if(c == HexConv[i]) {
			err = false; return i;
		}
	}

	err = false;
	return 0;
}

/*
std::string DecTHex(std::string str, bool &err) {

}

std::string DecFHex(std::string const& str, bool &err) {

}
*/

}

