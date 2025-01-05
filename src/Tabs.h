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
/// @version 1.0
/// @date 02/11/2024

#ifndef TABS_H
#define TABS_H

#include "Defines.h"

namespace Fenyx::Types
{

template<class T, DWORD s>
/// @brief STable - Classe qui permet de gérer un tableau de taille fixe
class STable
{
public:
    explicit STable(T defv);

    [[nodiscard]] DWORD GetSize() const;
    [[nodiscard]] T GetValue(DWORD idx);
    [[nodiscard]] bool GetFatal() const;
    [[nodiscard]] bool GetError();

    T& operator[](DWORD idx);

    ~STable();

private:
    T *data;

  	DWORD s_tab;
    DWORD c_tab;
    T v_def;
    bool error;
    bool fatal;
};

template<class T>
/// @brief DTable - Classe qui permet de gérer un tableau de taille dynamique
class DTable
{
public:
    explicit DTable(T defv);

    [[nodiscard]] DWORD GetSize() const;
    [[nodiscard]] T GetValue(DWORD idx);
    [[nodiscard]] bool GetFatal() const;
    [[nodiscard]] bool GetError();
    void Erase(DWORD idx);
    void Clear();

    T& operator[](DWORD idx);

    ~DTable();

private:
    T* data;

    DWORD s_tab;
    DWORD c_tab;
    T v_def;
    bool error;
    bool fatal;
};

template<class K, class V>
/// @brief MTable - Classe qui permet de gérer un tableau associatif clé/valeur
class MTable
{
public:
    explicit MTable(K defv_k, V defv_v);

    [[nodiscard]] DWORD GetSize() const;
    [[nodiscard]] V GetValue(K key);
    [[nodiscard]] bool GetFatal() const;
    [[nodiscard]] bool GetError();
    void Erase(K const& idx);
    void Clear();

    V& operator[](K idx);

    ~MTable();

private:
    DWORD IsExist(K const& idx);

    K* keys;
    V* values;

    DWORD s_tab;
    DWORD c_tab;
    K kv_def;
    V vv_def;
    bool error;
    bool fatal;
};

using barray = STable<BYTE, 17>;

#ifdef LITTLE_ENDIAN
    void SwapBytes(barray &bytes);
#endif // LITTLE_ENDIAN

barray BytesArray(allnum data);



template<class T, DWORD s>
/// @brief STable - Constructeur
///
/// @param[in] defv: valeur par défaut des emplacements du tableau
///
/// Constructeur de la classe STable.
STable<T, s>::STable(T defv) {
    data = nullptr;
    data = new T[s];

    if (data == nullptr) {
        error = fatal = true;
        s_tab = c_tab = 0;
    } else {
        error = fatal = false;
        s_tab = c_tab = s;
    }

    v_def = defv;
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
T STable<T, s>::GetValue(DWORD idx) {
    if (!fatal) {
        if (idx >= s_tab) {
            error = true;
            return v_def;
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
/// @brief operator[] - Opérateur d'indexation du tableau
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
/// @brief ~STable - Destructeur
///
/// Destructeur de la classe STable.
STable<T, s>::~STable() {
    if (!fatal) delete[] data;
}


template<class T>
/// @brief DTable - Constructeur
///
/// @param[in] defv: valeur par défaut des emplacements du tableau
///
/// Constructeur de la classe DTable.
DTable<T>::DTable(T defv) {
    data = nullptr;
    data = new T[2];

    if (data == nullptr) {
        error = fatal = true;
        s_tab = c_tab = 0;
    } else {
        error = fatal = false;
        s_tab = 0; c_tab = 2;
        data[0] = data[1] = defv;
    }

    v_def = defv;
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
T DTable<T>::GetValue(DWORD idx) {
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
/// @brief Erase - Efface une valeur
///
/// @param[in] idx: index de la valeur à effacer
///
/// Ne fais rien si l'index demandé est en dehors du tableau.
void DTable<T>::Erase(DWORD idx) {
    for (DWORD i = idx; i < s_tab; i++) data[i] = data[i + 1];
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
/// @brief operator[] - Opérateur d'indexation du tableau
///
/// @param[in] idx: index
///
/// @return Une référence sur la valeur contenue à t[idx] si existe, [v_def] sinon.
T& DTable<T>::operator[](DWORD idx) {
    if (!fatal) {
        T* temp_d = new T[s_tab];

        if (idx >= c_tab) {
            if (s_tab != 0) {
                if (temp_d == nullptr) {
                    error = fatal = true; s_tab = 0;
                    return v_def;
                }

                for (DWORD i = 0; i < s_tab; ++i) temp_d[i] = data[i];
            }
            delete[] data; data = nullptr;

            data = new T[idx + 1];
            if (data == nullptr) {
                error = true; fatal = true;
                return v_def;
            }

            if (s_tab != 0) for (DWORD i = 0; i < s_tab; ++i) data[i] = temp_d[i];
            c_tab = idx + 1;
        }

        if (idx >= s_tab) {
            for (QWORD i = s_tab; i < idx + 1; i++) data[i] = v_def;
            s_tab = idx + 1;
        }

        return data[idx];
    }

    return v_def;
}

template<class T>
/// @brief ~DTable - Destructeur
///
/// Destructeur de la classe DTable.
DTable<T>::~DTable() {
    if (!fatal) delete[] data;
}


template<class K, class V>
/// @brief MTable - Constructeur
///
/// @param[in] defv_k: valeur par défaut des clés
/// @param[in] defv_v: valeur par défaut des emplacements du tableau
///
/// Constructeur de la classe MTable.
MTable<K, V>::MTable(K defv_k, V defv_v) {
    keys = nullptr; values = nullptr;
    keys = new K[2]; values = new V[2];

    if (keys == nullptr || values == nullptr) {
        if (keys != nullptr)   delete[] keys; // NOLINT(*-delete-null-pointer)
        if (values != nullptr) delete[] values; // NOLINT(*-delete-null-pointer)
        error = fatal = true;
        s_tab = c_tab = 0;
    } else {
        error = fatal = false;
        s_tab = 0; c_tab = 2;
        keys[0]   = keys[1]   = defv_k;
        values[0] = values[1] = defv_v;
    }

    kv_def = defv_k;
    vv_def = defv_v;
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
V MTable<K, V>::GetValue(K key) {
    if (!fatal) {
        DWORD idx = IsExist(key);
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
/// @brief Erase - Efface une valeur
///
/// @param[in] idx: clé associée à la valeur à effacer
///
/// Ne fais rien si la clé demandée n'est pas dans le tableau.
void MTable<K, V>::Erase(K const& idx) {
    if (!fatal) {
        const DWORD idx_i = IsExist(idx);

        if  (idx_i == s_tab)                  return;
        for (DWORD i = idx_i; i < s_tab; ++i) keys[i]   = keys[i + 1];
        for (DWORD i = idx_i; i < s_tab; ++i) values[i] = values[i + 1];

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
/// @brief operator[] - Opérateur d'indexation du tableau
///
/// @param[in] idx: clé
///
/// @return Une référence sur la valeur associée à idx si existe, [vv_def] sinon.
V& MTable<K, V>::operator[](K idx) {
    if (!fatal) {
        K* temp_k = new K[s_tab]; V* temp_v = new V[s_tab];

        if (const DWORD idx_i = IsExist(idx); idx_i != s_tab) return values[idx_i];

        if (s_tab == c_tab) {
            if (s_tab != 0) {
                if (temp_k == nullptr || temp_v == nullptr) {
                    if (temp_k != nullptr) delete[] temp_k; // NOLINT(*-delete-null-pointer)
                    if (temp_v != nullptr) delete[] temp_v; // NOLINT(*-delete-null-pointer)
                    error = fatal = true; s_tab = 0;
                    return vv_def;
                }

                for (DWORD i = 0; i < s_tab; ++i) temp_k[i] = keys[i];
                for (DWORD i = 0; i < s_tab; ++i) temp_v[i] = values[i];
            }
            delete[] keys;   keys   = nullptr;
            delete[] values; values = nullptr;

            keys = new K[c_tab + 1]; values = new V[c_tab + 1];
            if (keys == nullptr || values == nullptr) {
                if (keys != nullptr)   delete[] keys; // NOLINT(*-delete-null-pointer)
                if (values != nullptr) delete[] values; // NOLINT(*-delete-null-pointer)

                error = fatal = true; s_tab = 0;
                return vv_def;
            }

            if (s_tab != 0) {
                for (DWORD i = 0; i < s_tab; ++i) keys[i]   = temp_k[i];
                for (DWORD i = 0; i < s_tab; ++i) values[i] = temp_v[i];
            }

            c_tab += 1;
        }
        s_tab += 1; keys[s_tab - 1] = idx;

        return values[s_tab - 1];
    }

    return vv_def;
}

template<class K, class V>
/// @brief ~MTable - Destructeur
///
/// Destructeur de la classe MTable.
MTable<K, V>::~MTable() {
    if (!fatal) {
        delete[] keys;
        delete[] values;
    }
}

template<class K, class V>
DWORD MTable<K, V>::IsExist(K const& idx) {
    for (DWORD i = 0; i < s_tab; ++i) {
        if (keys[i] == idx) return i;
    }

    return s_tab;
}

}

#endif //TABS_H
