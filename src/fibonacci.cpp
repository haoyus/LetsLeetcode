#include <iostream>
#include <cstring>

//recursion with O(2^n)
int fibonacci(int n)
{
    if(n<=1)
        return 1;

    return fibonacci(n-1) + fibonacci(n-2);
}

int fib(int n,int* arr)
{
    if(n<=1)
        return 1;

    if(arr[n-1]!=0)
        return arr[n-1];
    else{
        arr[n-1] = fib(n-1,arr)+fib(n-2,arr);
        return arr[n-1];//as fib(n)
    }
}

//iteration
int fibo(int n)
{
    if(n<=1)
        return 1;

    int a1 = 1,a2 = 1,ans=0;
    for(int i=2;i<n+1;++i){
        ans = a1+a2;
        a1 = a2;
        a2 = ans;
    }
    return ans;
}

int main()
{
    int n = 40;
    int tmp[n];
    memset(tmp,0,n*sizeof(int));
    std::cout<<"init "<<tmp[0]<<std::endl;
    //int ans = fibonacci(50);
    int ans = fibo(n);
    std::cout<<"Input: "<<n<<" Ans: "<<ans<<std::endl;
    return ans;
}