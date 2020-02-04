#include <stack>
#include <iostream>
#include <cstring>

char expr1[] = "a/(b[i-1][j+1] + c[i+1][j-1]) *2";
char expr2[] = "a/(b[i-1][j+1])+ c[i+1][j-1]) *2";

bool parenCheck(const char* expr,int lo,int hi)
{
    std::stack<char> S;
    for(int i=lo;i<=hi;++i){
        switch(expr[i]){
            case '(':
            case '[':
            case '{':
                S.push(expr[i]);
                break;
            case ')':
                if(S.empty()||S.top()!='(')
                    return false;
                else
                    S.pop();
                break;
            case ']':
                //std::cout<<"]\n";
                if(S.empty() || S.top()!='[')
                    return false;
                else
                    S.pop();
                break;
            case '}':
                if(S.empty() || S.top()!='{')
                    return false;
                else
                    S.pop();
                //break;
            default: break;
        }
    }
    if(S.empty()) return true;
    else return false;
}

int main()
{
    bool ans = parenCheck(expr1, 0, 32);
    if(ans)
        std::cout<<"True\n";
    else
        std::cout<<"False\n";
}