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

/// @file Tabs.h
/// @brief Header de Tabs
/// @author F&nµx
/// @version 2.5
/// @date 29/03/2025

#ifndef TABS_H
#define TABS_H

#include <cassert>
#include <memory>
#include <algorithm>
#include "Defines.h"

namespace Fenyx::Types
{

template<class U, class V>
/// @brief Pair - Classe qui permet de gérer une paire de 2 valeurs
class Pair
{
public:
    Pair() = default;
    Pair(const U &f, const V &s);

    U First();
    V Second();

    void Set(const U &f, const V &s);
    void SetFirst(const U &f);
    void SetSecond(const V &s);

    ~Pair() = default;

private:
    U first;
    V second;
};

template<class T, DWORD s>
class STable;

template<class T, DWORD s>
bool operator==(const STable<T, s> &t1, const STable<T, s> &t2);

template<class T, DWORD s>
bool operator!=(const STable<T, s> &t1, const STable<T, s> &t2);


template<class T>
class DTable;

template<class T>
bool operator==(const DTable<T> &t1, const DTable<T> &t2);

template<class T>
bool operator!=(const DTable<T> &t1, const DTable<T> &t2);


template<class K, class V>
class MTable;

template<class K, class V>
bool operator==(const MTable<K, V> &t1, const MTable<K, V> &t2);

template<class K, class V>
bool operator!=(const MTable<K, V> &t1, const MTable<K, V> &t2);


template<class T>
/// @brief Stack - Classe qui permet de gérer une pile de données
class Stack
{
public:
    Stack();
    Stack(const Stack &s);

    T const& Top();
    void Pop();
    void Push(const T &v);

    DWORD GetSize();

    ~Stack() = default;

private:
    DTable<T> stack;
};



template<class T, DWORD s>
/// @brief STable - Classe qui permet de gérer un tableau de taille fixe
///
/// /!\ Le tableau est aligné sur 32 octets (pour les intrinsics AVX2)
class STable
{
public:
    explicit STable();
    STable(STable&& oth) noexcept;

    [[nodiscard]] DWORD GetSize() const;
    [[nodiscard]] T const& GetValue(DWORD idx);
    [[nodiscard]] T* GetPtr() const;

    T& operator[](DWORD idx);
    T const& operator[](DWORD idx) const;
    STable& operator=(STable&& oth) noexcept;

    ~STable() = default;

private:
    std::unique_ptr<T[], decltype(&std::free)> data;

  	DWORD s_tab;

friend bool operator==<T, s>(const STable<T, s> &t1, const STable<T, s> &t2);
friend bool operator!=<T, s>(const STable<T, s> &t1, const STable<T, s> &t2);
};

template<class T>
/// @brief DTable - Classe qui permet de gérer un tableau de taille dynamique
///
/// /!\ Le tableau est aligné sur 32 octets (pour les intrinsics AVX2)
class DTable
{
public:
    explicit DTable();
    DTable(DTable&& oth) noexcept;

    [[nodiscard]] DWORD GetSize() const;
    [[nodiscard]] T const& GetValue(DWORD idx);
    [[nodiscard]] T* GetPtr() const;
    bool SetCapacity(DWORD cap, T val);
    void Erase(DWORD idx);
    void Clear();

    [[nodiscard]] bool IsEmpty() const;

    T& operator[](DWORD idx);
    T const& operator[](DWORD idx) const;
    DTable& operator=(DTable&& oth) noexcept;

    ~DTable() = default;

private:
    std::unique_ptr<T[], decltype(&std::free)> data;

    DWORD s_tab;
    DWORD c_tab;

friend bool operator==<T>(const DTable<T> &t1, const DTable<T> &t2);
friend bool operator!=<T>(const DTable<T> &t1, const DTable<T> &t2);
};



template<class K, class V>
/// @brief MTable - Classe qui permet de gérer un tableau associatif clé/valeur
class MTable
{
public:
    explicit MTable();
    MTable(MTable&& oth) noexcept;

    [[nodiscard]] DWORD GetSize() const;
    [[nodiscard]] V const& GetValue(K key);
    void Erase(K const& idx);
    void Clear();

    V& operator[](K idx);
    V const& operator[](K key) const;
    MTable& operator=(MTable&& oth) noexcept;

    ~MTable() = default;

private:
    DWORD IsExist(K const& idx);

    std::unique_ptr<K[]> keys;
    std::unique_ptr<V[]> values;

    DWORD s_tab;
    DWORD c_tab;

friend bool operator==<K, V>(const MTable<K, V> &t1, const MTable<K, V> &t2);
friend bool operator!=<K, V>(const MTable<K, V> &t1, const MTable<K, V> &t2);
};

using barray = STable<BYTE, 17>;

#ifdef LITTLE_ENDIAN
    void SwapBytes(barray &bytes);
#endif // LITTLE_ENDIAN

barray BytesArray(allnum data);



template<class U, class V>
/// @brief Pair - Constructeur
///
/// @param[in] f: f-value
/// @param[in] s: s-value
///
/// Constructeur de la classe Pair.
Pair<U, V>::Pair(const U &f, const V &s) {
    first  = f;
    second = s;
}

template<class U, class V>
/// @brief First - Récupère la première valeur de la paire
///
/// @return La première valeur contenue dans la paire.
U Pair<U, V>::First() {
    return first;
}

template<class U, class V>
/// @brief Second - Récupère la deuxième valeur de la paire
///
/// @return La deuxième valeur contenue dans la paire.
V Pair<U, V>::Second() {
    return second;
}

template<class U, class V>
/// @brief Set - Permet de modifier les deux valeurs
///
/// @param[in] f: f-value
/// @param[in] s: s-value
void Pair<U, V>::Set(const U &f, const V &s) {
    first  = f;
    second = s;
}

template<class U, class V>
/// @brief SetFirst - Permet de modifier la première valeur de la paire
///
/// @param[in] f: f-value
void Pair<U, V>::SetFirst(const U &f) {
    first = f;
}

template<class U, class V>
/// @brief SetFirst - Permet de modifier la deuxième valeur de la paire
///
/// @param[in] s: s-value
void Pair<U, V>::SetSecond(const V &s) {
    second = s;
}


template<class T>
/// @brief Stack - Constructeur
///
/// Constructeur de la classe Stack.
Stack<T>::Stack() {
    stack.Clear();
}

template<class T>
/// @brief Stack - Constructeur de copie
///
/// @param[in] s: Stack à copier
///
/// Constructeur de copie de la classe Stack.
Stack<T>::Stack(const Stack &s) {
    stack.Clear();

    for (QWORD i = 0; i < s.stack.GetSize(); i = i + 1) stack[i] = s.stack[i];
}

template<class T>
/// @brief Top - Récupères le haut de la pile
///
/// @return La valeur la plus haute dans la pile.
T const& Stack<T>::Top() {
    return stack[stack.GetSize() - 1];
}

template<class T>
/// @brief Pop - Retire la valeur haute de la pile
void Stack<T>::Pop() {
    stack.Erase(stack.GetSize() - 1);
}

template<class T>
/// @brief Push - Ajoute une valeur au-dessus de la pile
///
/// @param[in] v: valeur à ajouter
void Stack<T>::Push(const T &v) {
    stack[stack.GetSize()] = v;
}

template<class T>
/// @brief GetSize - Donne la taille du tableau
///
/// @return Un DWORD contenant la taille du tableau.
DWORD Stack<T>::GetSize() {
    return stack.GetSize();
}


template<class T, DWORD s>
/// @brief STable - Constructeur
///
/// Constructeur par défaut de la classe STable.
STable<T, s>::STable() : data(nullptr, &std::free), s_tab(s) {
    static const std::size_t s_byt = s * sizeof(T);
    static const std::size_t s_arr = ((s_byt + 31) / 32) * 32;

    data.reset(static_cast<T*>(std::aligned_alloc(32, s_arr)));

    if (!data) s_tab = 0;
}

template<class T, DWORD s>
/// @brief STable - Constructeur de déplacement
///
/// @param[in] oth: STable à déplacer
///
/// Constructeur de déplacement de la classe STable
STable<T, s>::STable(STable&& oth) noexcept : data(std::move(oth.data)), s_tab(oth.s_tab) {}

template<class T, DWORD s>
/// @brief GetSize - Donne la taille du tableau
///
/// @return Un DWORD contenant la taille du tableau.
DWORD STable<T, s>::GetSize() const {
    return s_tab;
}

template<class T, DWORD s>
/// @brief GetValue - Donne la valeur contenue à un index spécifique
///
/// @param[in] idx: index
///
/// @return La valeur contenue à t[idx] si existe ou dummy sinon.
T const& STable<T, s>::GetValue(DWORD idx) {
    static const T dummy{};

    return (idx < s_tab) ? data[idx] : dummy;
}

template<class T, DWORD s>
/// @brief GetPtr - Récupères le pointeur brut
///
/// @return Le pointeur brut du tableau si réussi, nullptr sinon.
T* STable<T, s>::GetPtr() const {
    if (s_tab == 0) return nullptr;

    return data.get();
}

template<class T, DWORD s>
/// @brief operator[] - Opérateur d'indexation du tableau (en écriture)
///
/// @param[in] idx: index
///
/// @return Une référence sur la valeur contenue à t[idx] si existe, dummy sinon.
T& STable<T, s>::operator[](DWORD idx) {
    static T dummy{};

    return (idx < s_tab) ? data[idx] : dummy;
}

template<class T, DWORD s>
/// @brief operator[] - Opérateur d'indexation du tableau (en lecture)
///
/// @param[in] idx: index
///
/// @return Une référence constante sur la valeur contenue à t[idx] si existe, dummy sinon.
T const& STable<T, s>::operator[](DWORD idx) const {
    static const T dummy{};

    return (idx < s_tab) ? data[idx] : dummy;
}

template<class T, DWORD s>
/// @brief operator= - Opérateur de déplacement entre STable
///
/// @param[in] oth: STable à déplacer
///
/// @return Une référence sur le STable affecté.
STable<T, s>& STable<T, s>::operator=(STable&& oth) noexcept {
    if (this != &oth) {
        data  = std::move(oth.data);
        s_tab = oth.s_tab;
    }

    return *this;
}

template<class T, DWORD s>
/// @brief operator== - Opérateur d'égalité entre STable
///
/// @param[in] t1: lhs
/// @param[in] t2: rhs
///
/// @return true si égaux, false sinon.
bool operator==(const STable<T, s> &t1, const STable<T, s> &t2) {
    if (t1.s_tab != t2.s_tab) return false;

    for (QWORD i = 0; i < t1.s_tab; i = i + 1) {
        if (t1.data[i] != t2.data[i]) return false;
    }

    return true;
}

template<class T, DWORD s>
/// @brief operator== - Opérateur d'inégalité entre STable
///
/// @param[in] t1: lhs
/// @param[in] t2: rhs
///
/// @return true si inégaux, false sinon.
bool operator!=(const STable<T, s> &t1, const STable<T, s> &t2) {
    if (t1.s_tab != t2.s_tab) return true;

    for (QWORD i = 0; i < t1.s_tab; i = i + 1) {
        if (t1.data[i] != t2.data[i]) return true;
    }

    return false;
}



template<class T>
/// @brief DTable - Constructeur
///
/// Constructeur par défaut de la classe DTable.
DTable<T>::DTable() : data(nullptr, &std::free), s_tab(0), c_tab(2) {
    const std::size_t s_byt = 2 * sizeof(T);
    const std::size_t s_arr = ((s_byt + 31) / 32) * 32;

    data.reset(static_cast<T*>(std::aligned_alloc(32, s_arr)));

    if (!data) c_tab = 0;
}

template<class T>
/// @brief DTable - Constructeur de déplacement
///
/// @param[in] oth: DTable à déplacer
///
/// Constructeur de déplacement de la classe DTable
DTable<T>::DTable(DTable&& oth) noexcept : data(std::move(oth.data)), s_tab(oth.s_tab), c_tab(oth.c_tab) {}

template<class T>
/// @brief GetSize - Donne la taille du tableau
///
/// @return Un DWORD contenant la taille du tableau.
DWORD DTable<T>::GetSize() const {
    return s_tab;
}

template<class T>
/// @brief GetValue - Donne la valeur contenue à un index spécifique
///
/// @param[in] idx: index
///
/// @return La valeur contenue à t[idx] si existe ou dummy sinon.
T const& DTable<T>::GetValue(DWORD idx) {
    static const T dummy{};

    return (idx < s_tab) ? data[idx] : dummy;
}

template<class T>
/// @brief GetPtr - Récupères le pointeur brut
///
/// @return Le pointeur brut du tableau si réussi, nullptr sinon.
T* DTable<T>::GetPtr() const {
    if (c_tab == 0) return nullptr;

    return data.get();
}

template<class T>
/// @brief SetCapacity - Pré-alloue une certaine taille
///
/// @param cap: capacité du tableau à pré-allouer
/// @param val: valeur à écrire sur la nouvelle taille
///
/// @return True si réussi, false sinon.
bool DTable<T>::SetCapacity(const DWORD cap, T val) {
    if (cap <= c_tab) return true;

    const std::size_t s_byt = cap * sizeof(T);
    const std::size_t s_arr = ((s_byt + 31) / 32) * 32;
    const DWORD ne = s_arr / sizeof(T);

    T* tmp = static_cast<T*>(std::aligned_alloc(32, s_arr));
    if (!tmp) return false;

    for (QWORD i = 0; i < s_tab; i = i + 1)   tmp[i] = std::move(data[i]);
    for (DWORD i = s_tab; i < cap; i = i + 1) tmp[i] = val;

    data.reset(tmp);
    c_tab = ne;

    return true;
}

template<class T>
/// @brief Erase - Efface une valeur
///
/// @param[in] idx: index de la valeur à effacer
///
/// Ne fais rien si l'index demandé est en dehors du tableau.
void DTable<T>::Erase(const DWORD idx) {
    const DWORD ns = s_tab - 1;
    if (idx >= s_tab) return;

    for (QWORD i = idx; i < ns; i = i + 1) data[i] = std::move(data[i + 1]);
    s_tab -= 1;
}

template<class T>
/// @brief Clear - Vide le contenu du tableau
///
/// Pas de réallocation mémoire, seule la taille est remise à 0.
void DTable<T>::Clear() {
    s_tab = 0;
}

template<class T>
/// @brief IsEmpty - Test si le tableau est vide
///
/// @return True si tableau vide, false sinon.
///
/// Ne test que la taille, pas la capacité (pour des raisons logiques, pardi !)
bool DTable<T>::IsEmpty() const {
    return (s_tab == 0);
}

template<class T>
/// @brief operator[] - Opérateur d'indexation du tableau (en écriture)
///
/// @param[in] idx: index
///
/// @return Une référence sur la valeur contenue à t[idx] si existe, un dummy sinon.
T& DTable<T>::operator[](DWORD idx) {
    const DWORD i1 = idx + 1, ns = (s_tab > i1) ? s_tab : i1;
    static T dummy{};

    if (idx >= c_tab) {
        const std::size_t s_byt = ns * sizeof(T);
        const std::size_t s_arr = ((s_byt + 31) / 32) * 32;
        const DWORD ne = s_arr / sizeof(T);

        T* tmp = static_cast<T*>(std::aligned_alloc(32, s_arr));
        if (!tmp) return dummy;

        for (QWORD i = 0; i < s_tab; i = i + 1)  tmp[i] = std::move(data[i]);
        for (DWORD i = s_tab; i < ns; i = i + 1) tmp[i] = T{};

        data.reset(tmp);
        c_tab = ne;
    }

    if (idx >= s_tab) s_tab = i1;
    return data[idx];
}

/* Pour info, [ns] sera toujours égal à [i1], mais comme le compilo est aveugle et pense que s_tab peut être supérieur
 * à c_tab, il génère un warning si je ne mets pas en place la variable [ns] pour tester si s_tab est dépassé... */

template<class T>
/// @brief operator[] - Opérateur d'indexation du tableau (en lecture)
///
/// @param[in] idx: index
///
/// @return Une référence constante sur la valeur contenue à t[idx] si existe, un dummy sinon.
T const& DTable<T>::operator[](DWORD idx) const {
    static const T dummy{};

    return (idx < s_tab) ? data[idx] : dummy;
}

template<class T>
/// @brief operator= - Opérateur de déplacement entre DTable
///
/// @param[in] oth: DTable à déplacer
///
/// @return Une référence sur le DTable affecté.
DTable<T>& DTable<T>::operator=(DTable&& oth) noexcept {
    if (this != &oth) {
        data  = std::move(oth.data);
        s_tab = oth.s_tab;
        c_tab = oth.c_tab;
    }

    return *this;
}

template<class T>
/// @brief operator== - Opérateur d'égalité entre DTable
///
/// @param[in] t1: lhs
/// @param[in] t2: rhs
///
/// @return true si égaux, false sinon.
bool operator==(const DTable<T> &t1, const DTable<T> &t2) {
    if (t1.s_tab != t2.s_tab) return false;

    for (QWORD i = 0; i < t1.s_tab; i = i + 1) {
        if (t1.data[i] != t2.data[i]) return false;
    }

    return true;
}

template<class T>
/// @brief operator== - Opérateur d'inégalité entre DTable
///
/// @param[in] t1: lhs
/// @param[in] t2: rhs
///
/// @return true si inégaux, false sinon.
bool operator!=(const DTable<T> &t1, const DTable<T> &t2) {
    if (t1.s_tab != t2.s_tab) return true;

    for (QWORD i = 0; i < t1.s_tab; i = i + 1) {
        if (t1.data[i] != t2.data[i]) return true;
    }

    return false;
}


template<class K, class V>
/// @brief MTable - Constructeur
///
/// Constructeur par défaut de la classe MTable.
MTable<K, V>::MTable() : s_tab(0), c_tab(2) {
    keys.reset(new (std::nothrow) K[c_tab]);
    if (!keys) c_tab = 0;

    values.reset(new (std::nothrow) V[c_tab]);
    if (!values) c_tab = 0;
}

template<class K, class V>
/// @brief MTable - Constructeur de déplacement
///
/// @param[in] oth: MTable à déplacer
///
/// Constructeur de déplacement de la classe MTable
MTable<K, V>::MTable(MTable&& oth) noexcept  : keys(std::move(oth.keys)), values(std::move(oth.values)), s_tab(oth.s_tab), c_tab(oth.c_tab) {}

template<class K, class V>
/// @brief GetSize - Donne la taille du tableau
///
/// @return Un DWORD contenant la taille du tableau.
DWORD MTable<K, V>::GetSize() const {
    return s_tab;
}

template<class K, class V>
/// @brief GetValue - Donne la valeur associée à une clé spécifique
///
/// @param[in] key: clé
///
/// @return La valeur contenue à t[key] si existe ou dummy sinon.
V const& MTable<K, V>::GetValue(K key) {
    static const V dummy{};
    const DWORD vi = IsExist(key);

    return (vi < s_tab) ? values[vi] : dummy;
}

template<class K, class V>
/// @brief Erase - Efface une valeur
///
/// @param[in] idx: clé associée à la valeur à effacer
///
/// Ne fais rien si la clé demandée n'est pas dans le tableau.
void MTable<K, V>::Erase(K const& idx) {
    const DWORD ns = s_tab - 1, vi = IsExists(idx);

    if (vi == s_tab) return;

    for (QWORD i = vi; i < ns; i = i + 1) {
        keys[i]   = std::move(keys[i + 1]);
        values[i] = std::move(keys[i + 1]);
    }

    s_tab -= 1;
}

template<class K, class V>
/// @brief Clear - Vide le contenu du tableau
///
/// Pas de réallocation mémoire, seule la taille est remise à 0.
void MTable<K, V>::Clear() {
    s_tab = 0;
}

template<class K, class V>
/// @brief operator[] - Opérateur d'indexation du tableau (en écriture)
///
/// @param[in] idx: clé
///
/// @return Une référence sur la valeur associée à idx si existe, dummy sinon.
V& MTable<K, V>::operator[](K idx) {
    static K dummyk{};
    static V dummyv{};

    const DWORD vi = IsExist(idx), c1 = c_tab + 1;

    if (vi >= c_tab) {
        K* tmpk = new (std::nothrow) K[c1];
        if (!tmpk) return dummyv;

        V* tmpv = new (std::nothrow) V[c1];
        if (!tmpv) {
            delete[] tmpk;
            return dummyv;
        }

        for (QWORD i = 0; i < s_tab; i = i + 1) {
            tmpk[i] = std::move(keys[i]);
            tmpv[i] = std::move(values[i]);
        }

        for (DWORD i = s_tab; i < c1; i = i + 1) {
            tmpk[i] = K{};
            tmpv[i] = V{};
        }

        keys.reset(tmpk);
        values.reset(tmpv);
        c_tab = c1;
    }

    if (vi == s_tab) s_tab += 1;

    keys[vi] = idx;
    return values[vi];
}

template<class K, class V>
/// @brief operator[] - Opérateur d'indexation du tableau (en lecture)
///
/// @param[in] key: clé
///
/// @return Une référence constante sur la valeur associée à idx si existe, dummy sinon.
V const& MTable<K, V>::operator[](K key) const {
    static const V dummy{};
    const DWORD vi = IsExist(key);

    return (vi < s_tab) ? values[vi] : dummy;
}

template<class T, class V>
/// @brief operator= - Opérateur de déplacement entre MTable
///
/// @param[in] oth: MTable à déplacer
///
/// @return Une référence sur le MTable affecté.
MTable<T, V>& MTable<T, V>::operator=(MTable&& oth) noexcept {
    if (this != &oth) {
        keys   = std::move(oth.keys);
        values = std::move(oth.values);
        s_tab  = oth.s_tab;
        c_tab  = oth.c_tab;
    }

    return *this;
}

template<class K, class V>
DWORD MTable<K, V>::IsExist(K const& idx) {
    for (QWORD i = 0; i < s_tab; i = i + 1) {
        if (keys[i] == idx) return i;
    }

    return s_tab;
}

template<class K, class V>
/// @brief operator== - Opérateur d'égalité entre MTable
///
/// @param[in] t1: lhs
/// @param[in] t2: rhs
///
/// @return True si égaux, false sinon.
bool operator==(const MTable<K, V> &t1, const MTable<K, V> &t2) {
    if (t1.s_tab != t2.s_tab) return false;

    for (QWORD i = 0; i < t1.s_tab; i = i + 1) {
        if (t1.keys[i] != t2.keys[i]) return false;
    }

    for (QWORD i = 0; i < t1.s_tab; i = i + 1) {
        if (t1.values[i] != t2.values[i]) return false;
    }

    return true;
}

template<class K, class V>
/// @brief operator== - Opérateur d'inégalité entre MTable
///
/// @param[in] t1: lhs
/// @param[in] t2: rhs
///
/// @return True si inégaux, false sinon.
bool operator!=(const MTable<K, V> &t1, const MTable<K, V> &t2) {
    if (t1.s_tab != t2.s_tab) return true;

    for (QWORD i = 0; i < t1.s_tab; i = i + 1) {
        if (t1.keys[i] != t2.keys[i]) return true;
    }

    for (QWORD i = 0; i < t1.s_tab; i = i + 1) {
        if (t1.values[i] != t2.values[i]) return true;
    }

    return false;
}

}

#endif //TABS_H
