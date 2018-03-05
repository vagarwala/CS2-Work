/**
 * @file debugging1.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2014-2015
 * @copyright This code is in the public domain.
 *
 * @brief An example of the utility of print statements in debugging.
 */

/*
 * The code runs until b is 0. For each run through
 * the loop, it checks if b is odd (if (b & 1) != 0). If so, it
 * adds a to x. Then a is bitshifted left (multiplying it by 2) 
 * and b is bitshifted right (dividing it by 2).
 * In this case, the variable x ends up being 14790.
 * It is always the product of a and b at the end of this program.
 * this program just adds multiples of a of the form a * 2^n,
 * where the 2^n's make up b in binary, so that this computes a*b.
 */


#include <iostream>

using namespace std;

/**
 * @brief Does a thing.
 *
 * Does a thing, I dunno, you tell me.
 */
int main(int argc, char ** argv)
{
    // Much of the following is intentionally undocumented.
    // Part of the assignment is to figure out what is going on.
    // You may need to look up some operators!
    unsigned int a = 174, b = 85, x = 0;

    // This construct is known as a 'while loop'.
    // The interior of the loop is run if, and while,
    // the given condition is true.
    // The program proceeds past the loop if, and when,
    // the given condition is found to be false just before any iteration
    // of the interior of the loop.
    while (b != 0)
    {
        // This construct is known as a conditional statement
        // ('if' statement).
        // The interior of the statement is run exactly once in its entirety
        // if the given condition is found to be true.
        // Note that 'true' is defined as nonzero,
        // and 'false' is defined as zero.
        if ((b & 1) != 0)
        {
            x += a;
        }
        a <<= 1;
        b >>= 1;
        cout << "a: " << a << "  b: " << b << "  x: " << x << endl;
    }

    // Question for you now: so what is x anyway?

    return 0;
}
