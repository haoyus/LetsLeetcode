#include "SmartPtr.h"
#include <iostream>

using namespace std;

int main()
{
    double* p = new double(5);

    cout << *p << endl;

    delete p;
    cout << *p << endl;
    delete p;

    cout << (*p = 6) <<endl;

    cout << "done\n";

    double data[] = {1,2,3};
    cout << data[3];
}