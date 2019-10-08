#include <stack>
#include <iostream>

using std::stack;
using std::cout;
using std::endl;

static char digit[] =
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
static char digits[] = "0123456789ABCDEF";

// recursion
void recursionConvert(stack<char>& S,int n,int base)
{
    if(n>0){
        S.push(digits[n%base]);
        recursionConvert(S,n/base,base);
    }
}

// iteration
void iterConvert(stack<char>& S,int n,int base)
{
    while(n>0){
        S.push(digit[n%base]);
        n /= base;
    }
}

int main()
{
    int n = 12345, base = 8;
    stack<char> output1,output2;

    std::cout<<std::oct<<n<<"\n";

    recursionConvert(output1, n, base);
    iterConvert(output2, n, base);

    while(!output1.empty()){
        cout<<output1.top();
        output1.pop();
    } cout<<endl;

    while (!output2.empty())
    {
        cout << output2.top();
        output2.pop();
    }
    cout << endl;
}