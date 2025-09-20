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
bool operator==(const STable<T, s>& t1, const STable<T, s>& t2);

template<class T, DWORD s>
bool operator!=(const STable<T, s>& t1, const STable<T, s>& t2);


template<class T>
class DTable;

template<class T>
bool operator==(const DTable<T>& t1, const DTable<T>& t2);

template<class T>
bool operator!=(const DTable<T>& t1, const DTable<T>& t2);


template<class K, class V>
class MTable;

template<class K, class V>
bool operator==(const MTable<K, V>& t1, const MTable<K, V>& t2);

template<class K, class V>
bool operator!=(const MTable<K, V>& t1, const MTable<K, V>& t2);


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
class STable
{
public:
    explicit STable();
    STable(STable&& oth) noexcept;

    [[nodiscard]] DWORD GetSize() const;
    [[nodiscard]] T const& GetValue(DWORD idx);
    [[nodiscard]] bool GetFatal() const;
    [[nodiscard]] bool GetError();
    void SetDefaultValue(T defv);

    T& operator[](DWORD idx);
    T const& operator[](DWORD idx) const;
    STable& operator=(STable&& oth) noexcept;

    ~STable() = default;

private:
    std::unique_ptr<T[]> data;

  	DWORD s_tab;
    DWORD c_tab;
    T v_def;
    bool error;
    bool fatal;

friend bool operator==<T, s>(const STable<T, s>& t1, const STable<T, s>& t2);
friend bool operator!=<T, s>(const STable<T, s>& t1, const STable<T, s>& t2);
};

template<class T>
/// @brief DTable - Classe qui permet de gérer un tableau de taille dynamique
class DTable
{
public:
    explicit DTable();
    DTable(DTable&& oth) noexcept;

    [[nodiscard]] DWORD GetSize() const;
    [[nodiscard]] T const& GetValue(DWORD idx);
    [[nodiscard]] bool GetFatal() const;
    [[nodiscard]] bool GetError();
    void SetDefaultValue(T defv);
    void SetCapacity(DWORD cap, T val);
    void Erase(DWORD idx);
    void Clear();

    [[nodiscard]] bool IsEmpty() const;

    T& operator[](DWORD idx);
    T const& operator[](DWORD idx) const;
    DTable& operator=(DTable&& oth) noexcept;

    ~DTable() = default;

private:
    std::unique_ptr<T[]> data;

    DWORD s_tab;
    DWORD c_tab;
    T v_def;
    bool error;
    bool fatal;

friend bool operator==<T>(const DTable<T>& t1, const DTable<T>& t2);
friend bool operator!=<T>(const DTable<T>& t1, const DTable<T>& t2);
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
    [[nodiscard]] bool GetFatal() const;
    [[nodiscard]] bool GetError();
    void SetDefaultValue(K defv_k, V defv_v);
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
    K kv_def;
    V vv_def;
    bool error;
    bool fatal;

friend bool operator==<K, V>(const MTable<K, V>& t1, const MTable<K, V>& t2);
friend bool operator!=<K, V>(const MTable<K, V>& t1, const MTable<K, V>& t2);
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
/// Constructeur de la classe STable.
STable<T, s>::STable() {
    data = std::make_unique<T[]>(s);

    if (data.get() == nullptr) {
        error = fatal = true;
        s_tab = c_tab = 0;
    } else {
        error = fatal = false;
        s_tab = c_tab = s;
    }
}

template<class T, DWORD s>
/// @brief STable - Constructeur de déplacement
///
/// @param[in] oth: STable à déplacer
///
/// Constructeur de déplacement la classe STable
STable<T, s>::STable(STable&& oth) noexcept {
    s_tab = oth.s_tab;
    c_tab = oth.c_tab;
    v_def = oth.v_def;

    data = std::move(oth.data);
    error = oth.error;
    fatal = oth.fatal;
}

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
/// @return La valeur contenue à t[idx] si existe ou [v_def] sinon.
T const& STable<T, s>::GetValue(DWORD idx) {
    if (!fatal) {
        if (idx >= s_tab) {
            error = true;
            return data[s - 1];
        }

        return data[idx];
    }

    return v_def;
}

template<class T, DWORD s>
/// @brief GetFatal - Test si une erreur fatale est remontée
///
/// @return true si erreur fatale, false sinon.
bool STable<T, s>::GetFatal() const {
    return fatal;
}

template<class T, DWORD s>
/// @brief GetError - Test si une erreur (fatale ou non) est remontée
///
/// @return true si erreur, false sinon.
bool STable<T, s>::GetError() {
    if (error) {
        if (!fatal) error = false;
        return true;
    }

    return false;
}

template<class T, DWORD s>
/// @brief SetDefaultValue - Définit la valeur par défaut d'une case du tableau
///
/// @param[in] defv: valeur par défaut
void STable<T, s>::SetDefaultValue(T defv) {
    v_def = std::move(defv);
}

template<class T, DWORD s>
/// @brief operator[] - Opérateur d'indexation du tableau (en écriture)
///
/// @param[in] idx: index
///
/// @return Une référence sur la valeur contenue à t[idx] si existe, [v_def] sinon.
T& STable<T, s>::operator[](DWORD idx) {
    if (!fatal) {
        if (idx >= s_tab) {
            if (!error) error = true;
            return v_def;
        }

        return data[idx];
    }

    return v_def;
}

template<class T, DWORD s>
/// @brief operator[] - Opérateur d'indexation du tableau (en lecture)
///
/// @param[in] idx: index
///
/// @return Une référence constante sur la valeur contenue à t[idx] si existe, [v_def] sinon.
T const& STable<T, s>::operator[](DWORD idx) const {
    if (!fatal) {
        if (idx >= s_tab) return v_def;
        return data[idx];
    }

    return v_def;
}

template<class T, DWORD s>
/// @brief operator= - Opérateur de déplacement entre STable
///
/// @param[in] oth: STable à déplacer
///
/// @return Une référence sur le STable affecté.
STable<T, s>& STable<T, s>::operator=(STable&& oth) noexcept {
    if (this != &oth) {
        s_tab = oth.s_tab;
        c_tab = oth.c_tab;
        v_def = oth.v_def;

        data = std::move(oth.data);
        error = oth.error;
        fatal = oth.fatal;
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
bool operator==(const STable<T, s>& t1, const STable<T, s>& t2) {
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
bool operator!=(const STable<T, s>& t1, const STable<T, s>& t2) {
    return !(t1 == t2);
}


template<class T>
/// @brief DTable - Constructeur
///
/// Constructeur de la classe DTable.
DTable<T>::DTable() {
    data = std::make_unique<T[]>(2);

    if (data.get() == nullptr) {
        error = fatal = true;
        s_tab = c_tab = 0;
    } else {
        error = fatal = false;
        s_tab = 0; c_tab = 2;
    }
}

template<class T>
/// @brief DTable - Constructeur de déplacement
///
/// @param[in] oth: DTable à déplacer
///
/// Constructeur de déplacement la classe DTable
DTable<T>::DTable(DTable&& oth) noexcept {
    s_tab = oth.s_tab;
    c_tab = oth.c_tab;
    v_def = oth.v_def;

    data = std::move(oth.data);
    error = oth.error;
    fatal = oth.fatal;
}

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
/// @return La valeur contenue à t[idx] si existe ou [v_def] sinon.
T const& DTable<T>::GetValue(DWORD idx) {
    if (!fatal) {
        if (idx >= s_tab) {
            error = true;
            return v_def;
        }

        return data[idx];
    }

    return v_def;
}

template<class T>
/// @brief GetFatal - Test si une erreur fatale est remontée
///
/// @return true si erreur fatale, false sinon.
bool DTable<T>::GetFatal() const {
    return fatal;
}

template<class T>
/// @brief GetError - Test si une erreur (fatale ou non) est remontée
///
/// @return true si erreur, false sinon.
bool DTable<T>::GetError() {
    if (error) {
        if (!fatal) error = false;
        return true;
    }

    return false;
}

template<class T>
/// @brief SetDefaultValue - Définit la valeur par défaut d'une case du tableau
///
/// @param[in] defv: valeur par défaut
void DTable<T>::SetDefaultValue(T defv) {
    v_def = std::move(defv);
}

template<class T>
/// @brief SetCapacity - Pré-alloue une certaine taille
///
/// @param cap: capacité du tableau à pré-allouer
/// @param val: valeur à écrire sur la nouvelle taille
void DTable<T>::SetCapacity(DWORD cap, T val) {
    if (!fatal) {
        if (cap > c_tab) {
            // ReSharper disable once CppJoinDeclarationAndAssignment
            T* temp_d = data.release();

            if (temp_d == nullptr) {
                error = fatal = true;
                s_tab = 0; c_tab = 0;
                return;
            }

            data = std::make_unique<T[]>(cap);
            if (data.get() == nullptr) {
                error = true; fatal = true;
                s_tab = 0; c_tab = 0;
                return;
            }

            if (s_tab != 0) {
                for (QWORD i = 0; i < s_tab; i = i + 1) data[i] = std::move(temp_d[i]);
            }

            for (QWORD i = s_tab; i < cap; i = i + 1) data[i] = val;

            c_tab = cap;
            delete[] temp_d;
        }
    }
}

template<class T>
/// @brief Erase - Efface une valeur
///
/// @param[in] idx: index de la valeur à effacer
///
/// Ne fais rien si l'index demandé est en dehors du tableau.
void DTable<T>::Erase(const DWORD idx) {
    for (DWORD i = idx; i < (s_tab - 1); i = i + 1) data[i] = data[i + 1];
    if (idx < s_tab) s_tab -= 1;
}

template<class T>
/// @brief Clear - Vide le contenu du tableau
///
/// Pas de réallocation mémoire, seule la taille est remise à 0. Ne fais rien si erreur fatale.
void DTable<T>::Clear() {
    if (!fatal) s_tab = 0;
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
/// @return Une référence sur la valeur contenue à t[idx] si existe, [v_def] sinon.
T& DTable<T>::operator[](DWORD idx) {
    if (!fatal) {
        T* temp_d;

        if (idx >= c_tab) {
            // ReSharper disable once CppJoinDeclarationAndAssignment
            temp_d = data.release();

            if (temp_d == nullptr) {
                error = fatal = true;
                s_tab = 0; c_tab = 0;
                return v_def;
            }

            const DWORD ns = (s_tab > (idx + 1)) ? s_tab : (idx + 1);
            T* nd = new T[ns];

            for (QWORD i = 0; i < s_tab; i = i + 1) nd[i] = std::move(temp_d[i]);
            delete[] temp_d;

            data.reset(nd);
            c_tab = ns;

            if (data.get() == nullptr) {
                error = true; fatal = true;
                s_tab = 0; c_tab = 0;
                return v_def;
            }
        }

        if (idx >= s_tab) s_tab = idx + 1;

        return data[idx];
    }

    return v_def;
}

template<class T>
/// @brief operator[] - Opérateur d'indexation du tableau (en lecture)
///
/// @param[in] idx: index
///
/// @return Une référence constante sur la valeur contenue à t[idx] si existe, [v_def] sinon.
T const& DTable<T>::operator[](DWORD idx) const {
    if (!fatal) {
        if (idx >= s_tab) return v_def;
        return data[idx];
    }

    return v_def;
}

template<class T>
/// @brief operator= - Opérateur de déplacement entre DTable
///
/// @param[in] oth: DTable à déplacer
///
/// @return Une référence sur le DTable affecté.
DTable<T>& DTable<T>::operator=(DTable&& oth) noexcept {
    if (this != &oth) {
        s_tab = oth.s_tab;
        c_tab = oth.c_tab;
        v_def = oth.v_def;

        data = std::move(oth.data);
        error = oth.error;
        fatal = oth.fatal;
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
bool operator==(const DTable<T>& t1, const DTable<T>& t2) {
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
bool operator!=(const DTable<T>& t1, const DTable<T>& t2) {
    return !(t1 == t2);
}


template<class K, class V>
/// @brief MTable - Constructeur
///
/// Constructeur de la classe MTable.
MTable<K, V>::MTable() {
    keys   = std::make_unique<K[]>(2);
    values = std::make_unique<V[]>(2);

    if (keys.get() == nullptr || values.get() == nullptr) {
        error = fatal = true;
        s_tab = c_tab = 0;
    } else {
        error = fatal = false;
        s_tab = 0; c_tab = 2;
    }
}

template<class K, class V>
/// @brief MTable - Constructeur de déplacement
///
/// @param[in] oth: MTable à déplacer
///
/// Constructeur de déplacement la classe MTable
MTable<K, V>::MTable(MTable&& oth) noexcept {
    s_tab  = oth.s_tab;
    c_tab  = oth.c_tab;
    kv_def = oth.kv_def;
    vv_def = oth.vv_def;

    keys   = std::move(oth.keys);
    values = std::move(oth.values);
    error  = oth.error;
    fatal  = oth.fatal;
}

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
/// @return La valeur contenue à t[key] si existe ou [vv_def] sinon.
V const& MTable<K, V>::GetValue(K key) {
    if (!fatal) {
        const DWORD idx = IsExist(key);
        if (idx == s_tab) {
            error = true;
            return vv_def;
        }

        return values[idx];
    }

    return vv_def;
}

template<class K, class V>
/// @brief GetFatal - Test si une erreur fatale est remontée
///
/// @return true si erreur fatale, false sinon.
bool MTable<K, V>::GetFatal() const {
    return fatal;
}

template<class K, class V>
/// @brief GetError - Test si une erreur (fatale ou non) est remontée
///
/// @return true si erreur, false sinon.
bool MTable<K, V>::GetError() {
    if (error) {
        if (!fatal) error = false;
        return true;
    }

    return false;
}

template<class K, class V>
/// @brief SetDefaultValue - Définit la valeur par défaut d'une case du tableau
///
/// @param[in] defv_k: valeur par défaut des clés
/// @param[in] defv_v: valeur par défaut pour les valeurs associées aux clés
void MTable<K, V>::SetDefaultValue(K defv_k, V defv_v) {
    kv_def = std::move(defv_k);
    vv_def = std::move(defv_v);
}

template<class K, class V>
/// @brief Erase - Efface une valeur
///
/// @param[in] idx: clé associée à la valeur à effacer
///
/// Ne fais rien si la clé demandée n'est pas dans le tableau.
void MTable<K, V>::Erase(K const& idx) {
    if (!fatal) {
        const DWORD idx_i = IsExist(idx);

        if  (idx_i == s_tab)                              return;
        for (DWORD i = idx_i; i < (s_tab - 1); i = i + 1) keys[i]   = keys[i + 1];
        for (DWORD i = idx_i; i < (s_tab - 1); i = i + 1) values[i] = values[i + 1];

        s_tab -= 1;
    }
}

template<class K, class V>
/// @brief Clear - Vide le contenu du tableau
///
/// Pas de réallocation mémoire, seule la taille est remise à 0. Ne fais rien si erreur fatale.
void MTable<K, V>::Clear() {
    if (!fatal) s_tab = 0;
}

template<class K, class V>
/// @brief operator[] - Opérateur d'indexation du tableau (en écriture)
///
/// @param[in] idx: clé
///
/// @return Une référence sur la valeur associée à idx si existe, [vv_def] sinon.
V& MTable<K, V>::operator[](K idx) {
    if (!fatal) {
        K* temp_k; V* temp_v;

        if (const DWORD idx_i = IsExist(idx); idx_i != s_tab) return values[idx_i];

        if (s_tab == c_tab) {
            // ReSharper disable once CppJoinDeclarationAndAssignment
            temp_k = keys.release();
            // ReSharper disable once CppJoinDeclarationAndAssignment
            temp_v = values.release();

            if (temp_k == nullptr || temp_v == nullptr) {
                error = fatal = true;
                s_tab = 0; c_tab = 0;
                return vv_def;
            }

            keys   = std::make_unique<K[]>(c_tab + 1);
            values = std::make_unique<V[]>(c_tab + 1);

            if (keys == nullptr || values == nullptr) {
                error = fatal = true;
                s_tab = 0; c_tab = 0;
                return vv_def;
            }

            if (s_tab != 0) {
                for (QWORD i = 0; i < s_tab; i = i + 1) keys[i]   = std::move(temp_k[i]);
                for (QWORD i = 0; i < s_tab; i = i + 1) values[i] = std::move(temp_v[i]);
            }

            c_tab += 1;

            delete[] temp_k;
            delete[] temp_v;
        }
        s_tab += 1; keys[s_tab - 1] = idx;

        return values[s_tab - 1];
    }

    return vv_def;
}

template<class K, class V>
/// @brief operator[] - Opérateur d'indexation du tableau (en lecture)
///
/// @param[in] key: clé
///
/// @return Une référence constante sur la valeur associée à idx si existe, [vv_def] sinon.
V const& MTable<K, V>::operator[](K key) const {
    if (!fatal) {
        const DWORD idx = IsExist(key);
        if (idx == s_tab) return vv_def;

        return values[idx];
    }

    return vv_def;
}

template<class T, class V>
/// @brief operator= - Opérateur de déplacement entre MTable
///
/// @param[in] oth: MTable à déplacer
///
/// @return Une référence sur le MTable affecté.
MTable<T, V>& MTable<T, V>::operator=(MTable&& oth) noexcept {
    if (this != &oth) {
        s_tab  = oth.s_tab;
        c_tab  = oth.c_tab;
        kv_def = oth.kv_def;
        vv_def = oth.vv_def;

        keys   = std::move(oth.keys);
        values = std::move(oth.values);
        error  = oth.error;
        fatal  = oth.fatal;
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
/// @return true si égaux, false sinon.
bool operator==(const MTable<K, V>& t1, const MTable<K, V>& t2) {
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
/// @return true si inégaux, false sinon.
bool operator!=(const MTable<K, V>& t1, const MTable<K, V>& t2) {
    return !(t1 == t2);
}

}

#endif //TABS_H
