/**
 * a frog jump up to top of stairs. it can jump 1 or 2 stairs at a time.
 * now there's a n-stair for it to jump, how many ways are there in total?
*/

#include <iostream>
#include <cstring>

// O(2^n) recursion
unsigned long f(int n)
{
    if(n<=2)
        return n;
    
    return f(n-1) + f(n-2);
}

// better recursion
unsigned long better_f(int n,unsigned long *array)
{
    if(n<=2)
        return n;

    if(0!=array[n-1])
        return array[n-1];
    else{
        array[n-1] = better_f(n-1,array)+better_f(n-2,array);
        return array[n-1];
    }
}

int main()
{
    int n = 45;
    unsigned long tmp[n];
    memset(tmp,0,n*sizeof(unsigned long));
    //for(int i=0;i<n;++i) tmp[i]=0;
    unsigned long ans = better_f(n,tmp);
    //unsigned long ans = f(n);
    std::cout<<"Input: "<<n<<" Ans: "<<ans<<std::endl;
}