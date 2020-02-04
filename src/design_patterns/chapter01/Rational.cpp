#include "Rational.h"
#include <iostream>

using std::cout;

Rational& Rational::operator+=(const Rational& rhs)
{
    n_ = n_*rhs.d_+rhs.n_*d_;

    reduce();
    return *this;
}

void Rational::reduce()
{

}

void Rational::report()
{
    cout << "N: " << n_ << ", D: " << d_ << "\n";
}

int main()
{
    Rational r1(1,1), r2(2,2);

    r1+=r2;
    r1.report();
    return 0;
}