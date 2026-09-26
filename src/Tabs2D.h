/// English version
/*
Copyright (C) 2026 BOUCARD NICOLLE Jody

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
Copyright (C) 2026 BOUCARD NICOLLE Jody

Ce fichier fait partie de ATypik.

ATypik est une bibliothèque libre; vous pouvez le redistribuer ou le modifier suivant les termes de la GNU General
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

/// @file Tabs2D.h
/// @brief Header de Tabs2D
/// @author F&nµx
/// @version 1.0
/// @date 26/09/2026

#ifndef TABS2D_H
#define TABS2D_H

#include "Tabs.h"

namespace Fenyx::Types
{

typedef Pair<DWORD, DWORD> IDX2D;

template<class T, DWORD m, DWORD n>
class STable2D;

template<class T, DWORD m, DWORD n>
bool operator==(const STable2D<T, m, n> &t1, const STable2D<T, m, n> &t2);

template<class T, DWORD m, DWORD n>
bool operator!=(const STable2D<T, m, n> &t1, const STable2D<T, m, n> &t2);


template<class T, DWORD s>
class DSTable;

template<class T, DWORD s>
bool operator==(const DSTable<T, s> &t1, const DSTable<T, s> &t2);

template<class T, DWORD s>
bool operator!=(const DSTable<T, s> &t1, const DSTable<T, s> &t2);



template<class T, DWORD m, DWORD n>
/// @brief STable2D - Classe qui permet de gérer un tableau de taille fixe en 2D
///
/// /!\ Le tableau est aligné sur 32 octets (pour les intrinsics AVX2)
class STable2D
{
public:
	explicit STable2D();
	STable2D(STable2D&& oth) noexcept;
	STable2D(const STable2D &oth);

	[[nodiscard]] DWORD GetSize() const;
	[[nodiscard]] BYTE GetAlign() const;
	[[nodiscard]] T const& GetValue(const IDX2D &idx);
	[[nodiscard]] T* GetPtr() const;

	T& operator[](const IDX2D &idx);
	T const& operator[](const IDX2D &idx) const;
	STable2D& operator=(STable2D&& oth) noexcept;
	STable2D& operator=(const STable2D& oth);

	~STable2D() = default;

private:
	std::unique_ptr<T[], decltype(&std::free)> data;

	DWORD s_tabm;
	DWORD s_tabn;
	BYTE sa;
	BYTE sa1;

	friend bool operator==<T, m, n>(const STable2D<T, m, n> &t1, const STable2D<T, m, n> &t2);
	friend bool operator!=<T, m, n>(const STable2D<T, m, n> &t1, const STable2D<T, m, n> &t2);
};

template<class T, DWORD s>
/// @brief DSTable - Classe qui permet de gérer un tableau de taille dynamique en 2D
///
/// /!\ Le tableau est aligné sur la valeur maximale possible en fonction du CPU (pour les intrinsics)
class DSTable
{
public:
	explicit DSTable();
	DSTable(DSTable&& oth) noexcept;
	DSTable(const DSTable &oth);

	[[nodiscard]] DWORD GetSize() const;
	[[nodiscard]] BYTE GetAlign() const;
	[[nodiscard]] T const& GetValue(const IDX2D &idx);
	[[nodiscard]] T* GetPtr() const;
	void SetSize(DWORD siz, T val);
	void Erase(DWORD idx);
	void Clear();

	void PushBack(const STable<T, s> &val);
	STable<T, s> PopBack();

	[[nodiscard]] bool IsEmpty() const;

	T& operator[](const IDX2D &idx);
	T const& operator[](const IDX2D &idx) const;
	DSTable& operator=(DSTable&& oth) noexcept;
	DSTable& operator=(const DSTable& oth);

	~DSTable() = default;

private:
	std::unique_ptr<T[], decltype(&std::free)> data;

	DWORD s_tab;
	DWORD s_tabs;
	DWORD ne;
	BYTE sa;
	BYTE sa1;

	friend bool operator==<T>(const DSTable<T, s> &t1, const DSTable<T, s> &t2);
	friend bool operator!=<T>(const DSTable<T, s> &t1, const DSTable<T, s> &t2);
};




template<class T, DWORD m, DWORD n>
/// @brief STable2D - Constructeur
///
/// Constructeur par défaut de la classe STable2D
STable2D<T, m, n>::STable2D() : data(nullptr, &std::free), s_tabm(m), s_tabn(n) {
    sa  = CPU::CPU_ALIGN * 4;
    sa1 = sa - 1;

    static const std::size_t s_byt = m * n * sizeof(T);
    static const std::size_t s_arr = ((s_byt + sa1) / sa) * sa;

    T *tmp = static_cast<T*>(std::aligned_alloc(sa, s_arr));
    if (!tmp) throw std::bad_alloc();

    data.reset(tmp);
    if (!data) s_tabm = 0;
}

template<class T, DWORD m, DWORD n>
/// @brief STable2D - Constructeur de déplacement
///
/// @param[in] oth: STable2D à déplacer
///
/// Constructeur de déplacement de la classe STable2D
STable2D<T, m, n>::STable2D(STable2D&& oth) noexcept : data(std::move(oth.data)), s_tabm(oth.s_tabm), s_tabn(oth.s_tabn), sa(oth.sa), sa1(oth.sa1) {
    oth.data.reset();
    oth.s_tabm = 0;
    oth.s_tabn = 0;
    oth.sa     = 0;
    oth.sa1    = 0;
}

template<class T, DWORD m, DWORD n>
/// @brief STable - Constructeur de copie
///
/// @param[in] oth: STable2D à copier
///
/// Constructeur de copie de la classe STable2D
STable2D<T, m, n>::STable2D(const STable2D &oth) : data(nullptr, &std::free), s_tabm(m), s_tabn(n) {
    sa = CPU::CPU_ALIGN * 4;
    sa1 = sa - 1;

    static const std::size_t s_byt = m * n * sizeof(T);
    static const std::size_t s_arr = ((s_byt + sa1) / sa) * sa;

    T *tmp = static_cast<T*>(std::aligned_alloc(sa, s_arr));
    if (!tmp) throw std::bad_alloc();

    data.reset(tmp);
    if (!data) s_tabm = 0;

    for (QWORD i = 0; i < s_tabm; i = i + 1) {
        for (QWORD j = 0; j < s_tabn; j = j + 1) {
            data[i * n + j] = oth.data[i * n + j];
        }
    }
}

template<class T, DWORD m, DWORD n>
/// @brief GetSize - Donne la taille du tableau principal
///
/// @return Un DWORD contenant la taille du tableau principal.
DWORD STable2D<T, m, n>::GetSize() const {
    return s_tabm;
}

template<class T, DWORD m, DWORD n>
/// @brief GetAlign - Donne l'alignement mémoire optimal
///
/// @return Un BYTE contenant l'alignement mémoire du tableau.
BYTE STable2D<T, m, n>::GetAlign() const {
    return sa;
}

template<class T, DWORD m, DWORD n>
/// @brief GetValue - Donne la valeur contenue à un index spécifique
///
/// @param[in] idx: index 2D
///
/// @return La valeur contenue à t[idx] si existe, lève une exception sinon.
T const& STable2D<T, m, n>::GetValue(const IDX2D &idx) {
    const DWORD i = idx.First(), j = idx.Second();
    std::ostringstream ossm;

    if (i >= s_tabm) {
        ossm << i;

        throw std::out_of_range("STable2D/GetValue(): [idx] (" + ossm.str() + ")(j) is out of range");
    }

    if (j >= s_tabn) {
        std::ostringstream ossn;
        ossm << i; ossn << j;

        throw std::out_of_range("STable2D/GetValue(): [idx] (" + ossm.str() + ")(" + ossn.str() + ") is out of range");
    }

    return data[i * n + j];
}

template<class T, DWORD m, DWORD n>
/// @brief GetPtr - Récupères le pointeur brut
///
/// @return Le pointeur brut du tableau si réussi, nullptr sinon.
T* STable2D<T, m, n>::GetPtr() const {
    if (s_tabm == 0) return nullptr;

    return data.get();
}

template<class T, DWORD m, DWORD n>
/// @brief operator[] - Opérateur d'indexation du tableau (en écriture)
///
/// @param[in] idx: index 2D
///
/// @return Une référence sur la valeur contenue à t[idx] si existe, lève une exception sinon.
T& STable2D<T, m, n>::operator[](const IDX2D &idx) {
    const DWORD i = idx.First(), j = idx.Second();
    std::ostringstream ossm;

    if (i >= s_tabm) {
        ossm << i;

        throw std::out_of_range("STable2D/op[](&): [idx] (" + ossm.str() + ")(j) is out of range");
    }

    if (j >= s_tabn) {
        std::ostringstream ossn;
        ossm << i; ossn << j;

        throw std::out_of_range("STable2D/op[](&): [idx] (" + ossm.str() + ")(" + ossn.str() + ") is out of range");
    }

    return data[i * n + j];
}

template<class T, DWORD m, DWORD n>
/// @brief operator[] - Opérateur d'indexation du tableau (en lecture)
///
/// @param[in] idx: index 2D
///
/// @return Une référence constante sur la valeur contenue à t[idx] si existe, lève une exception sinon.
T const& STable2D<T, m, n>::operator[](const IDX2D &idx) const {
    const DWORD i = idx.First(), j = idx.Second();
    std::ostringstream ossm;

    if (i >= s_tabm) {
        ossm << i;

        throw std::out_of_range("STable2D/op[](const): [idx] (" + ossm.str() + ")(j) is out of range");
    }

    if (j >= s_tabn) {
        std::ostringstream ossn;
        ossm << i; ossn << j;

        throw std::out_of_range("STable2D/op[](const): [idx] (" + ossm.str() + ")(" + ossn.str() + ") is out of range");
    }

    return data[i * n + j];
}

template<class T, DWORD m, DWORD n>
/// @brief operator= - Opérateur de déplacement entre STable2D
///
/// @param[in] oth: STable2D à déplacer
///
/// @return Une référence sur le STable2D affecté.
STable2D<T, m, n>& STable2D<T, m, n>::operator=(STable2D&& oth) noexcept {
    if (this != &oth) {
        data   = std::move(oth.data);
        s_tabm = oth.s_tabm;
        s_tabn = oth.s_tabn;
        sa     = oth.sa;
        sa1    = oth.sa1;

        oth.data.reset();
        oth.s_tabm = 0;
        oth.sa     = 0;
        oth.sa1    = 0;
    }

    return *this;
}

template<class T, DWORD m, DWORD n>
/// @brief operator= - Opérateur de copie entre STable2D
///
/// @param[in] oth: STable à copier
///
/// @return Une référence sur le STable2D affecté.
STable2D<T, m, n>& STable2D<T, m, n>::operator=(const STable2D& oth) {
    if (this != &oth) {
        for (QWORD i = 0; i < s_tabm; i = i + 1) {
            for (QWORD j = 0; j < s_tabn; j = j + 1) {
                data[i * n + j] = oth.data[i * n + j];
            }
        }
    }

    return *this;
}

template<class T, DWORD m, DWORD n>
/// @brief operator== - Opérateur d'égalité entre STable2D
///
/// @param[in] t1: lhs
/// @param[in] t2: rhs
///
/// @return true si égaux, false sinon.
bool operator==(const STable2D<T, m, n> &t1, const STable2D<T, m, n> &t2) {
	const DWORD t1sm = t1.s_tabm, t1sn = t1.s_tabn;
	if (t1sm != t2.s_tabm) return false;

	for (QWORD i = 0; i < t1sm; i = i + 1) {
		for (QWORD j = 0; j < t1sn; j = j + 1) {
			if (t1.data[i * n + j] != t2.data[i * n + j]) return false;
		}
	}

	return true;
}

template<class T, DWORD m, DWORD n>
/// @brief operator!= - Opérateur d'inégalité entre STable2D
///
/// @param[in] t1: lhs
/// @param[in] t2: rhs
///
/// @return true si différents, false sinon.
bool operator!=(const STable2D<T, m, n> &t1, const STable2D<T, m, n> &t2) {
	const DWORD t1sm = t1.s_tabm, t1sn = t1.s_tabn;
	if (t1sm != t2.s_tabm) return true;

	for (QWORD i = 0; i < t1sm; i = i + 1) {
		for (QWORD j = 0; j < t1sn; j = j + 1) {
			if (t1.data[i * n + j] != t2.data[i * n + j]) return true;
		}
	}

	return false;
}



template<class T, DWORD s>
/// @brief DSTable - Constructeur
///
/// Constructeur par défaut de la classe DSTable
DSTable<T, s>::DSTable() : data(nullptr, &std::free), s_tab(0), s_tabs(s), ne(0) {
	sa  = CPU::CPU_ALIGN * 4;
	sa1 = sa - 1;

	const std::size_t s_byt = 2 * s * sizeof(T);
	const std::size_t s_arr = ((s_byt + sa1) / sa) * sa;
	ne                      = s_arr / sizeof(T);

	T* tmp = static_cast<T*>(std::aligned_alloc(sa, s_arr));
	if (!tmp) throw std::bad_alloc();

	data.reset(tmp);
	s_tab = 0;
}

template<class T, DWORD s>
/// @brief DSTable - Constructeur de déplacement
///
/// @param[in] oth: DSTable à déplacer
///
/// Constructeur de déplacement de la classe DSTable
DSTable<T, s>::DSTable(DSTable&& oth) noexcept : data(std::move(oth.data)), s_tab(oth.s_tab), s_tabs(oth.s_tabs), ne(oth.ne), sa(oth.sa), sa1(oth.sa1) {
	oth.data.reset();
	oth.s_tab  = 0;
	oth.s_tabs = 0;
	oth.ne     = 0;
	oth.sa     = 0;
	oth.sa1    = 0;
}

template<class T, DWORD s>
/// @brief DSTable - Constructeur de copie
///
/// @param[in] oth: DSTable à copier
///
/// Constructeur de copie de la classe DSTable
DSTable<T, s>::DSTable(const DSTable &oth) : data(nullptr, &std::free), s_tab(0), s_tabs(s), ne(0) {
	sa = CPU::CPU_ALIGN * 4;
	sa1 = sa - 1;

	const DWORD ots = oth.s_tab, ns = (ots > 0) ? ots : 2;

	const std::size_t s_byt = ns * s * sizeof(T);
	const std::size_t s_arr = ((s_byt + sa1) / sa) * sa;
	ne                      = s_arr / sizeof(T);

	T* tmp = static_cast<T*>(std::aligned_alloc(sa, s_arr));
	if (!tmp) throw std::bad_alloc();
	data.reset(tmp);

	for (QWORD i = 0; i < ots; i = i + 1) {
		for (QWORD j = 0; j < s; j = j + 1) {
			data[i * s + j] = oth.data[i * s + j];
		}
	}

	s_tab = ots;
}

template<class T, DWORD s>
/// @brief GetSize - Donne la taille du tableau principal
///
/// @return Un DWORD contenant la taille du tableau principal.
DWORD DSTable<T, s>::GetSize() const {
	return s_tab;
}

template<class T, DWORD s>
/// @brief GetAlign - Donne l'alignement mémoire optimal
///
/// @return Un BYTE contenant l'alignement mémoire du tableau.
BYTE DSTable<T, s>::GetAlign() const {
	return sa;
}

template<class T, DWORD s>
/// @brief GetValue - Donne la valeur contenue à un index spécifique
///
/// @param[in] idx: index 2D
///
/// @return La valeur contenue à t[idx] si existe, lève une exception sinon.
T const& DSTable<T, s>::GetValue(const IDX2D &idx) {
	const DWORD i = idx.First(), j = idx.Second();
	std::ostringstream ossm;

	if (i >= s_tab) {
		ossm << i;

		throw std::out_of_range("DSTable/op[](const): [idx] (" + ossm.str() + ")(j) is out of range");
	}

	if (j >= s_tabs) {
		std::ostringstream ossn;
		ossm << i; ossn << j;

		throw std::out_of_range("DSTable/op[](const): [idx] (" + ossm.str() + ")(" + ossn.str() + ") is out of range");
	}

	return data[i * s + j];
}

template<class T, DWORD s>
/// @brief GetPtr - Récupères le pointeur brut
///
/// @return Le pointeur brut du tableau si réussi, nullptr sinon.
T* DSTable<T, s>::GetPtr() const {
	return data.get();
}

template<class T, DWORD s>
/// @brief SetSize - Pré-alloue au minimum une certaine taille
///
/// @param siz: nouvelle taille du tableau
/// @param val: valeur à écrire sur la nouvelle taille
void DSTable<T, s>::SetSize(const DWORD siz, T val) {
	const DWORD ns = siz * s, sst = s_tab * s;
	bool ral = true;

	if (ns <= ne) {
		for (QWORD i = sst; i < ns; i = i + 1) data[i] = val;
		ral = false;
	}

	if (ral) {
		const std::size_t s_byt = ns * sizeof(T);
		const std::size_t s_arr = ((s_byt + sa1) / sa) * sa;
		ne                      = s_arr / sizeof(T);

		T* tmp = static_cast<T*>(std::aligned_alloc(sa, s_arr));
		if (!tmp) throw std::bad_alloc();

		for (QWORD i = 0; i < sst; i = i + 1)  tmp[i] = data[i];
		for (DWORD i = sst; i < ne; i = i + 1) tmp[i] = val;

		data.reset(tmp);
	}

	s_tab = siz;
}

template<class T, DWORD s>
/// @brief Erase - Efface un tableau secondaire
///
/// @param[in] idx: index du tableau à effacer
///
/// Ne fais rien si l'index demandé est en dehors du tableau.
void DSTable<T, s>::Erase(const DWORD idx) {
	const DWORD ns = s_tab - 1;
	if (idx >= s_tab) return;

	for (QWORD i = idx; i < ns; i = i + 1) {
		for (QWORD j = 0; j < s; j = j + 1) {
			data[i * s + j] = data[(i + 1) * s + j];
		}
	}

	s_tab -= 1;
}

template<class T, DWORD s>
/// @brief Clear - Vide le contenu du tableau
///
/// Pas de réallocation mémoire, seule la taille est remise à 0.
void DSTable<T, s>::Clear() {
	s_tab = 0;
}

template<class T, DWORD s>
/// @brief PushBack - Ajoute un élément à la fin du tableau principal
///
/// @param[in] val: tableau secondaire à ajouter
void DSTable<T, s>::PushBack(const STable<T, s> &val) {
	const DWORD ns = (s_tab + 1) * s;

	if (ns > ne) {
		const std::size_t s_byt = ns * sizeof(T);
		const std::size_t s_arr = ((s_byt + sa1) / sa) * sa;
		ne                      = s_arr / sizeof(T);

		T* tmp = static_cast<T*>(std::aligned_alloc(sa, s_arr));
		if (!tmp) throw std::bad_alloc();

		for (QWORD i = 0; i < s_tab; i = i + 1) {
			for (QWORD j = 0; j < s; j = j + 1) {
				tmp[i * s + j] = data[i * s + j];
			}
		}

		data.reset(tmp);
	}

	const DWORD sst = s_tab * s;
	for (QWORD j = sst; j < ns; j = j + 1) data[j] = val[j - sst];

	s_tab += 1;
}

template<class T, DWORD s>
/// @brief PopBack - Retourne et supprime le dernier élément
///
/// @return Le dernier tableau secondaire contenu dans le tableau principal.
STable<T, s> DSTable<T, s>::PopBack() {
	if (s_tab == 0) throw std::runtime_error("PopBack when empty");

	const DWORD i = s_tab - 1;
	STable<T, s> ret;

	for (QWORD j = 0; j < s; j = j + 1) ret[j] = data[i * s + j];
	s_tab -= 1;

	return ret;
}

template<class T, DWORD s>
/// @brief IsEmpty - Test si le tableau principal est vide
///
/// @return True si tableau vide, false sinon.
///
/// Ne test que la taille, pas la capacité (pour des raisons logiques, pardi !)
bool DSTable<T, s>::IsEmpty() const {
	return (s_tab == 0);
}

template<class T, DWORD s>
/// @brief operator[] - Opérateur d'indexation du tableau (en écriture)
///
/// @param[in] idx: index 2D
///
/// @return Une référence sur t[idx] si [j] est correct, lève une exception sinon.
T& DSTable<T, s>::operator[](const IDX2D &idx) {
	const DWORD id = idx.First(), jd = idx.Second();

	if (const DWORD ns = (id + 1) * s; ns > ne) {
		const std::size_t s_byt = ns * sizeof(T);
		const std::size_t s_arr = ((s_byt + sa1) / sa) * sa;
		ne                      = s_arr / sizeof(T);

		T* tmp = static_cast<T*>(std::aligned_alloc(sa, s_arr));
		if (!tmp) throw std::bad_alloc();

		for (QWORD i = 0; i < s_tab; i = i + 1) {
			for (QWORD j = 0; j < s; j = j + 1) {
				tmp[i * s + j] = data[i * s + j];
			}
		}

		data.reset(tmp);
	}

	if (jd >= s_tabs) {
		std::ostringstream ossm, ossn;
		ossm << id; ossn << jd;

		throw std::out_of_range("DStable/op[](&): [idx] (" + ossm.str() + ")(" + ossn.str() + ") is out of range");
	}

	if (id >= s_tab) s_tab = id + 1;
	return data[id * s + jd];
}

template<class T, DWORD s>
/// @brief operator[] - Opérateur d'indexation du tableau (en lecture)
///
/// @param[in] idx: index
///
/// @return Une référence constante sur la valeur contenue à t[idx] si existe, lève une exception sinon.
T const& DSTable<T, s>::operator[](const IDX2D &idx) const {
	const DWORD i = idx.First(), j = idx.Second();
	std::ostringstream ossm;

	if (i >= s_tab) {
		ossm << i;

		throw std::out_of_range("DSTable/op[](const): [idx] (" + ossm.str() + ")(j) is out of range");
	}

	if (j >= s_tabs) {
		std::ostringstream ossn;
		ossm << i; ossn << j;

		throw std::out_of_range("DSTable/op[](const): [idx] (" + ossm.str() + ")(" + ossn.str() + ") is out of range");
	}

	return data[i * s + j];
}

template<class T, DWORD s>
/// @brief operator= - Opérateur de déplacement entre DSTable
///
/// @param[in] oth: DSTable à déplacer
///
/// @return Une référence sur le DSTable affecté.
DSTable<T, s> & DSTable<T, s>::operator=(DSTable&& oth) noexcept {
	if (this != &oth) {
		data   = std::move(oth.data);
		s_tab  = oth.s_tab;
		s_tabs = oth.s_tabs;
		ne     = oth.ne;
		sa     = oth.sa;
		sa1    = oth.sa1;

		oth.data.reset();
		oth.s_tab  = 0;
		oth.s_tabs = 0;
		oth.ne     = 0;
		oth.sa     = 0;
		oth.sa1    = 0;
	}

	return *this;
}

template<class T, DWORD s>
/// @brief operator= - Opérateur de copie entre DSTable
///
/// @param[in] oth: DSTable à copier
///
/// @return Une référence sur le DSTable affecté.
DSTable<T, s>& DSTable<T, s>::operator=(const DSTable& oth) {
	if (this != &oth) {
		const DWORD ots = oth.s_tab, ns = (ots > 0) ? ots : 2;

		const std::size_t s_byt = ns * s * sizeof(T);
		const std::size_t s_arr = ((s_byt + sa1) / sa) * sa;
		ne                      = s_arr / sizeof(T);

		T* tmp = static_cast<T*>(std::aligned_alloc(sa, s_arr));
		if (!tmp) throw std::bad_alloc();
		data.reset(tmp);

		for (QWORD i = 0; i < ots; i = i + 1) {
			for (QWORD j = 0; j < s; j = j + 1) {
				data[i * s + j] = oth.data[i * s + j];
			}
		}

		s_tab = ots;
	}

	return *this;
}

template<class T, DWORD s>
/// @brief operator== - Opérateur d'égalité entre DSTable
///
/// @param[in] t1: lhs
/// @param[in] t2: rhs
///
/// @return true si égaux, false sinon.
bool operator==(const DSTable<T, s> &t1, const DSTable<T, s> &t2) {
	const DWORD t1sm = t1.s_tab, t1sn = t1.s_tabs;
	if (t1sm != t2.s_tab) return false;

	for (QWORD i = 0; i < t1sm; i = i + 1) {
		for (QWORD j = 0; j < t1sn; j = j + 1) {
			if (t1.data[i * s + j] != t2.data[i * s + j]) return false;
		}
	}

	return true;
}

template<class T, DWORD s>
/// @brief operator== - Opérateur d'inégalité entre DSTable
///
/// @param[in] t1: lhs
/// @param[in] t2: rhs
///
/// @return true si différents, false sinon.
bool operator!=(const DSTable<T, s> &t1, const DSTable<T, s> &t2) {
	const DWORD t1sm = t1.s_tab, t1sn = t1.s_tabs;
	if (t1sm != t2.s_tab) return true;

	for (QWORD i = 0; i < t1sm; i = i + 1) {
		for (QWORD j = 0; j < t1sn; j = j + 1) {
			if (t1.data[i * s + j] != t2.data[i * s + j]) return true;
		}
	}

	return false;
}

}

#endif //TABS2D_H
