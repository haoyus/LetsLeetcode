#include <iostream>

struct C
{
    C(int aa) : a(aa) { std::cout << "A construct was made with "<<a<<"\n"; };
    C(const C &) { std::cout << "A copy was made.\n"; }
    C& operator=(const C& c){this->a = c.a;std::cout<<"Asign was made.\n";}
    int a;
};

C F(int x)
{
    C c(0);
    c.a = x*5;
    return c;
};

C FF()
{
    return F(1);
}

int main()
{
    //C obj;
    C obj1 = FF();//return optimization, obj1 constructed in stack with 1?
    std::cout <<obj1.a<<"\n";
    C obj2(obj1);
    std::cout<<obj2.a<<"\n";
}