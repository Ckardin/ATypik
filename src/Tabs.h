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
DWORD STable<T, s>::GetSize() const {
    return s_tab;
}

template<class T, DWORD s>
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
bool STable<T, s>::GetFatal() const {
    return fatal;
}

template<class T, DWORD s>
bool STable<T, s>::GetError() {
    if (error) {
        if (!fatal) error = false;
        return true;
    }

    return false;
}

template<class T, DWORD s>
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
STable<T, s>::~STable() {
    if (!fatal) delete[] data;
}


template<class T>
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
DWORD DTable<T>::GetSize() const {
    return s_tab;
}

    template<class T>
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
bool DTable<T>::GetFatal() const {
    return fatal;
}

template<class T>
bool DTable<T>::GetError() {
    if (error) {
        if (!fatal) error = false;
        return true;
    }

    return false;
}

template<class T>
void DTable<T>::Erase(DWORD idx) {
    for (DWORD i = idx; i < s_tab; i++) data[i] = data[i + 1];
    if (idx < s_tab) s_tab -= 1;
}

template<class T>
void DTable<T>::Clear() {
    if (!fatal) s_tab = 0;
}

template<class T>
T& DTable<T>::operator[](DWORD idx) {
    if (!fatal) {
        T* temp_d;

        if (idx >= c_tab) {
            if (s_tab != 0) {
                temp_d = new T[s_tab];
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
DTable<T>::~DTable() {
    if (!fatal) delete[] data;
}


template<class K, class V>
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
DWORD MTable<K, V>::GetSize() const {
    return s_tab;
}

template<class K, class V>
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
bool MTable<K, V>::GetFatal() const {
    return fatal;
}

template<class K, class V>
bool MTable<K, V>::GetError() {
    if (error) {
        if (!fatal) error = false;
        return true;
    }

    return false;
}

template<class K, class V>
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
void MTable<K, V>::Clear() {
    if (!fatal) s_tab = 0;
}

template<class K, class V>
V& MTable<K, V>::operator[](K idx) {
    if (!fatal) {
        K* temp_k; V* temp_v;

        if (const DWORD idx_i = IsExist(idx); idx_i != s_tab) return values[idx_i];

        if (s_tab == c_tab) {
            if (s_tab != 0) {
                temp_k = new K[s_tab]; temp_v = new V[s_tab];
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
