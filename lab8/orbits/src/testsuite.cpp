/**
 * @file test_solver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Simple test suite for Solver.
 *
 * @section License
 * Copyright (c) 2013-2014 California Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the California Institute of Technology.
 *
 */

#include "Solver.hpp"
#include <cstdio>
#include <cmath>

using namespace Solver;


double f1(double xi)
{
    return xi + 2;
}
double fp1(double xi)
{
    return 1;
}

double f2(double xi)
{
    return pow(xi, 2) + 6 * xi + 5;
}
double fp2(double xi)
{
    return 2 * xi + 6;
}

double f3(double xi)
{
    return 4* pow(xi, 4) - 5 * pow(xi, 3) - 6 * pow(xi, 2) - 7 * xi + 8;
}
double fp3(double xi)
{
    return 16 * pow(xi, 3) - 15 * pow(xi, 2) - 12 * xi - 7;
}

double f4(double xi)
{
    if (xi > 0){
        return log(xi);
    }else{
        return -1;
    }
}
double fp4(double xi)
{
    if (xi > 0){
        return 1/xi;
    }else{
        return 0;
    }
}

int main()
{
    /* Do your testing here. */
    printf("Function 1 is f(x) = x + 2\nanswer should be x = -2\n");
    double sol1 = newton_raphson(f1, fp1, 5);
    printf("newton raphson soln is %g\n", sol1);
    sol1 = bisection(f1, -10, 10);
    printf("bisection soln is %g\n\n", sol1);

    printf("Function 2 is f(x) = x^2 + 6x + 5\nanswer should be x = -1 or x = -5\n");
    double sol2 = newton_raphson(f2, fp2, 5);
    printf("newton raphson soln is %g\n", sol2);
    sol2 = bisection(f2, -4, 10);
    printf("bisection soln is %g\n\n", sol2);

    printf("Function 3 is f(x) = 4x^4 - 5x^3 - 6x^2 - 7x + 8\nanswer should be x = 0.665 or x = 2.132\n");
    double sol3 = newton_raphson(f3, fp3, 0);
    printf("newton raphson soln is %g\n", sol3);
    sol3 = bisection(f3, -5, 2);
    printf("bisection soln is %g\n\n", sol3);

    printf("Function 4 (non-analytic) is f(x) = ln(x) if x > 0 and "
            " -1 if x <= 0. \nanswer should be x = 1\n");
    double sol4 = newton_raphson(f4, fp4, 1);
    printf("newton raphson soln is %g\n", sol4);
    sol4 = bisection(f4, -1, 3);
    printf("bisection soln is %g\n", sol4);

    return 0;
}
