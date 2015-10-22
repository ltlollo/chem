/* Copyright (c) 2015 ltlollo
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SOLVER_H
#define SOLVER_H

#include <algorithm>
#include <assert.h>
#include "parser.h"

template<typename T> using mat_t = std::vector<std::vector<T>>;

template<typename T> T gcd(T a, T b);
template<typename T> T gcd(const std::vector<T> &v);
template<typename T> int solve(const mat_t<Elem> &form, std::vector<T> &res);

template<typename T> int
solve(const mat_t<Elem> &form, std::vector<T> &res) {
    std::vector<std::size_t> elems;
    std::size_t nelems_plsone = 1;
    for (const auto &c : form) {
        for (const auto &v : c) {
            if (!(elems.size() > (std::size_t)v.ele)) {
                elems.resize(v.ele+1, 0);
            }
            if (elems[v.ele] == 0) {
                elems[v.ele] = nelems_plsone++;
            }
        }
    }
    auto cols = form.size();
    mat_t<T> mat(nelems_plsone-1, std::vector<T>(cols, 0));
    for (std::size_t i = 0; i < form.size(); ++i) {
        for (std::size_t j = 0; j < form[i].size(); ++j) {
            mat[elems[form[i][j].ele]-1][i] += form[i][j].n;
        }
    }
    for (std::size_t i = 0; i < std::min(mat.size(), cols-1); ++i) {
        auto zeros = std::partition(mat.begin()+i, mat.end(),
            [=](const auto &ele){
            return ele[i] != 0;
        });
        if (zeros == mat.begin()+i) {
            return -1;
        }
        for (auto curr = zeros-1; curr != mat.begin()+i; curr--) {
            auto prev = curr-1;
            auto gcd_pivs = gcd((*prev)[i], (*curr)[i]);
            auto prev_pivot = (*prev)[i]/gcd_pivs,
                 curr_pivot = (*curr)[i]/gcd_pivs;
            for (std::size_t j = i; j < cols; ++j) {
                (*curr)[j] *= prev_pivot;
            }
            for (std::size_t j = i; j < cols; ++j) {
                (*prev)[j] *= curr_pivot;
            }
            for (std::size_t j = i; j < cols; ++j) {
                (*curr)[j] -= (*prev)[j];
            }
        }
    }
    mat.erase(std::remove_if(mat.begin(), mat.end(), [](const auto &v){
        return std::all_of(v.begin(), v.end(), [](const auto e) {
            return !e;
        });
    }), mat.end());
    if (mat.empty()) {
        return -1;
    }
    T acc = 1;
    for (std::size_t i = 0; i < mat.size(); ++i) {
        acc *= (mat[i][i]/gcd(acc, mat[i][i]));
    }
    for (std::size_t i = 0; i < mat.size(); ++i) {
        T p = acc/mat[i][i];
        mat[i][i] = acc;
        for (std::size_t j = i+1; j < mat[i].size(); ++j) {
            mat[i][j] *= p;
        }
    }
    res = std::vector<T>(cols, 0);
    for (std::size_t i = mat.size(); i; --i) {
        auto cur = i-1;
        if (i == mat.size()) {
            res[i]   = mat[cur][cur] > 0 ?  mat[cur][cur] : -mat[cur][cur];
            res[cur] = mat[cur][cur] > 0 ? -mat[cur][i]   :  mat[cur][i];
            continue;
        }
        for (std::size_t j = i; j < cols; ++j) {
            res[cur] -= res[j]*mat[cur][j];
        }
        if (res[cur] % mat[cur][cur] != 0) {
            return -1;
        }
        res[cur] /= mat[cur][cur];
    }
    if (std::any_of(res.begin(), res.end(), [](const auto e) { return !e; })) {
        return -1;
    }
    auto p = gcd(res);
    for (auto &e : res) {
        e /= p;
    }
    return 0;
}

template<typename T> T gcd(T a, T b) {
    T tmp = a;
    while (b) {
        a = b;
        b = tmp%b;
        tmp = a;
    }
    return a;
}

template<typename T> T gcd(const std::vector<T> &v) {
    assert(v.size() > 0);
    if (v.size() == 1) {
        return v[1];
    }
    auto res = gcd(v[0], v[1]);
    for (std::size_t i = 1; i < v.size()-1; ++i) {
        res = gcd(res, v[i+1]);
    }
    return res;
}

#endif // SOLVER_H
