#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief Solves the given quadratic equation.
 *
 * This function, given real coefficients A, B, C to the equation
 * A*x*x + B*x + C = 0, returns the real part of a solution to the
 * equation thus defined. Where two real solutions exist, the one
 * closer to positive infinity is chosen.
 *
 * @param a the quadratic coefficient.
 * @param b the linear coefficient.
 * @param c the constant coefficient.
 *
 * @return the real part of a solution to the defined quadratic equation,
 *         as described.
 */

double qfsolve(double a, double b, double c)
{
    // calculate the part under the sqrt
	double root = pow(b, 2) - 4 * a * c;
    if (root < 0) // if the solutions are complex, return real part
        return -b / (2 * a);
    // if both solutions are real, return larger solution
    return (-b + sqrt(root)) / (2 * a);
}

/**
 * @brief Test of the qfsolve function.
 *
 * here are several test cases.
 */

int main(int argc, char ** argv)
{
	//should print -1
    cout << "Input: 1, 2, 1. Output: " << qfsolve(1, 2, 1) << endl;
    // should print -0.5
    cout << "Input: 1, 1, 1. Output: " << qfsolve(1, 1, 1) << endl;
    // should print approx. -0.71922
    cout << "Input: 2, 7, 4. Output: " << qfsolve(2, 7, 4) << endl;
    // should print -0.25
    cout << "Input: 6, 3, 2. Output: " << qfsolve(6, 3, 2) << endl;
    // should print -0.125
    cout << "Input: 12, 3, 4. Output: " << qfsolve(12, 3, 4) << endl;
    return 0;
}