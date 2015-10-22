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

#include <algorithm>
#include "parser.h"

Token tokenize(const char **stream);
Token parse_comp(const char **stream, std::vector<Elem> &res, const bool lhs);
int parse_formula(const char *stream, std::vector<std::vector<Elem>> &res);

int
parse_formula(const char *stream, std::vector<std::vector<Elem>> &res) {
    res.resize(0);
    bool lhs = true;
    std::vector<Elem> comp;
    while (true) {
        switch (parse_comp(&stream, comp, lhs)) {
        default:
            return -1;
        case EOS:
            res.push_back(move(comp));
            return 0;
        case ARROW:
            lhs = false;
        case PLUS:
            if (comp.empty()) {
                return -1;
            }
            res.push_back(move(comp));
            comp = {};
            break;
        }
    }
}

Token
parse_comp(const char **stream, std::vector<Elem> &res, const bool lhs) {
    Token t;
    std::size_t pos = 0;
    while ((t = tokenize(stream)) > INV) {
        if (t >= Al) {
            pos = res.size();
            res.push_back(Elem{t - Al, lhs ? 1 : -1});
            continue;
        }
        if (t >= ZERO && t <= NINE) {
            num_t n = t - ZERO;
            while (**stream >= '0' && **stream <= '9') {
                num_t n_new = n * 10 + ((**stream) - '0');
                if (n_new < n) {
                    return INV;
                }
                n = n_new;
                (*stream)++;
            }
            if (res.empty() || t == INV || n == 0) {
                return INV;
            }
            for (std::size_t i = pos; i < res.size(); ++i) {
                if (std::abs(res[i].n) * n < std::abs(res[i].n)) {
                    return INV;
                }
                res[i].n *= n;
            }
            pos = res.size();
            continue;
        }
        switch (t) {
        default:
            return INV;
        case CONT:
            break;
        case ARROW:
            return ARROW;
        case PLUS:
            return PLUS;
        case RPAREN:
            return RPAREN;
        case LPAREN:
            pos = res.size();
            if (parse_comp(stream, res, lhs) != RPAREN) {
                return INV;
            }
            break;
        }
    }
    return t;
}

Token
tokenize(const char **stream) {
    if (**stream == '\0') {
        return EOS;
    }
    switch (*(*stream)++) {
    default:
        return INV;
    case 'A':
        switch (*(*stream)++) {
        default:
            return INV;
        case 'l':
            return Al;
        case 'm':
            return Am;
        case 'r':
            return Ar;
        case 's':
            return As;
        case 't':
            return At;
        case 'u':
            return Au;
        }
    case 'B':
        switch (*(*stream)++) {
        default:
            (*stream)--;
            return B;
        case 'a':
            return Ba;
        case 'e':
            return Be;
        case 'h':
            return Bh;
        case 'i':
            return Bi;
        case 'k':
            return Bk;
        case 'r':
            return Br;
        }
    case 'C':
        switch (*(*stream)++) {
        default:
            (*stream)--;
            return C;
        case 'a':
            return Ca;
        case 'd':
            return Cd;
        case 'e':
            return Ce;
        case 'f':
            return Cf;
        case 'l':
            return Cl;
        case 'm':
            return Cm;
        case 'n':
            return Cn;
        case 'o':
            return Co;
        case 'r':
            return Cr;
        case 's':
            return Cs;
        case 'u':
            return Cu;
        }
    case 'D':
        switch (*(*stream)++) {
        default:
            return INV;
        case 'b':
            return Db;
        case 's':
            return Ds;
        case 'y':
            return Dy;
        }
    case 'E':
        switch (*(*stream)++) {
        default:
            return INV;
        case 'r':
            return Er;
        case 's':
            return Es;
        case 'u':
            return Eu;
        }
    case 'F':
        switch (*(*stream)++) {
        default:
            (*stream)--;
            return F;
        case 'e':
            return Fe;
        case 'l':
            return Fl;
        case 'm':
            return Fm;
        case 'r':
            return Fr;
        }
    case 'G':
        switch (*(*stream)++) {
        default:
            return INV;
        case 'a':
            return Ga;
        case 'd':
            return Gd;
        case 'e':
            return Ge;
        }
    case 'H':
        switch (*(*stream)++) {
        default:
            (*stream)--;
            return H;
        case 'e':
            return He;
        case 'f':
            return Hf;
        case 'g':
            return Hg;
        case 'o':
            return Ho;
        case 's':
            return Hs;
        }
    case 'I':
        switch (*(*stream)++) {
        default:
            (*stream)--;
            return I;
        case 'n':
            return In;
        case 'r':
            return Ir;
        }
    case 'K':
        switch (*(*stream)++) {
        default:
            (*stream)--;
            return K;
        case 'r':
            return Kr;
        }
    case 'L':
        switch (*(*stream)++) {
        default:
            return INV;
        case 'a':
            return La;
        case 'i':
            return Li;
        case 'r':
            return Lr;
        case 'u':
            return Lu;
        case 'v':
            return Lv;
        }
    case 'M':
        switch (*(*stream)++) {
        default:
            return INV;
        case 'd':
            return Md;
        case 'g':
            return Mg;
        case 'n':
            return Mn;
        case 'o':
            return Mo;
        case 't':
            return Mt;
        }
    case 'N':
        switch (*(*stream)++) {
        default:
            (*stream)--;
            return N;
        case 'a':
            return Na;
        case 'b':
            return Nb;
        case 'd':
            return Nd;
        case 'e':
            return Ne;
        case 'i':
            return Ni;
        case 'o':
            return No;
        case 'p':
            return Np;
        }
    case 'O':
        switch (*(*stream)++) {
        default:
            (*stream)--;
            return O;
        case 's':
            return Os;
        }
    case 'P':
        switch (*(*stream)++) {
        default:
            (*stream)--;
            return P;
        case 'a':
            return Pa;
        case 'b':
            return Pb;
        case 'd':
            return Pd;
        case 'm':
            return Pm;
        case 'o':
            return Po;
        case 'r':
            return Pr;
        case 't':
            return Pt;
        case 'u':
            return Pu;
        }
    case 'R':
        switch (*(*stream)++) {
        default:
            return INV;
        case 'a':
            return Ra;
        case 'b':
            return Rb;
        case 'e':
            return Re;
        case 'f':
            return Rf;
        case 'g':
            return Rg;
        case 'h':
            return Rh;
        case 'n':
            return Rn;
        case 'u':
            return Ru;
        }
    case 'S':
        switch (*(*stream)++) {
        default:
            (*stream)--;
            return S;
        case 'b':
            return Sb;
        case 'c':
            return Sc;
        case 'e':
            return Se;
        case 'g':
            return Sg;
        case 'i':
            return Si;
        case 'm':
            return Sm;
        case 'n':
            return Sn;
        case 'r':
            return Sr;
        }
    case 'T':
        switch (*(*stream)++) {
        default:
            return INV;
        case 'a':
            return Ta;
        case 'b':
            return Tb;
        case 'c':
            return Tc;
        case 'e':
            return Te;
        case 'h':
            return Th;
        case 'i':
            return Ti;
        case 'l':
            return Tl;
        case 'm':
            return Tm;
        }
    case 'U':
        return U;
    case 'V':
        return V;
    case 'W':
        return W;
    case 'X':
        switch (*(*stream)++) {
        default:
            return INV;
        case 'e':
            return Xe;
        }
    case 'Y':
        switch (*(*stream)++) {
        default:
            (*stream)--;
            return Y;
        case 'b':
            return Yb;
        }
    case 'Z':
        switch (*(*stream)++) {
        default:
            return INV;
        case 'n':
            return Zn;
        case 'r':
            return Zr;
        }
    case ' ':
        return CONT;
    case '(':
        return LPAREN;
    case ')':
        return RPAREN;
    case '+':
        return PLUS;
    case '-':
        switch (*(*stream)++) {
        default:
            return INV;
        case '>':
            return ARROW;
        }
    case '0':
        return ZERO;
    case '1':
        return ONE;
    case '2':
        return TWO;
    case '3':
        return TREE;
    case '4':
        return FOUR;
    case '5':
        return FIVE;
    case '6':
        return SIX;
    case '7':
        return SEVEN;
    case '8':
        return EIGHT;
    case '9':
        return NINE;
    }
}
