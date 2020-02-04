#pragma once

class Rational
{
public:
    Rational(const long n, const long d) : n_(n), d_(d) {}

public:
    Rational& operator+=(const Rational& rhs);
    void report();

private:
    long n_;
    long d_;
    void reduce();


};