#include <iostream>
#include "Rational.h"

using std::cout;
using std::cin;

int main()
{
    Rational r1(1,1), r2(2,2);

    r1+=r2;
    r1.report();

    cout << "Press any key to exit\n";
    char c;
    cin >> c;
    return 0;
}