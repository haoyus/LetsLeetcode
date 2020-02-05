#include "Rational.h"
#include <iostream>

using std::cout;
using std::cin;

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

