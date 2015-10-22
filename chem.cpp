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

#include <iostream>
#include <err.h>
#include <stdio.h>
#include "solver.h"

extern char *__progname;
static void usage(void);

int
main(int argc, char *[]) {
    if (argc != 1) {
        usage();
        return 1;
    }
    mat_t<Elem> res;
    std::vector<long long> sol;
    std::string form;
    while (std::getline(std::cin, form)) {
        if (parse_formula(form.c_str(), res) == -1) {
            warnx("invalid expression");
            continue;
        }
        if(solve(res, sol) == -1) {
            warnx("non solvable");
            continue;
        }
        printf("solution:");
        for (const auto &c : sol) {
            printf(" %lld", c);
        }
        printf("\n");
    }
    return 0;
}

static void usage(void) {
    (void)fprintf(stderr, "Usage: %s"
                  "\nScope: bring balance to the chemical forces"
                  "\n Options: none, reads the equations from stdin"
                  "\n", __progname);
}
