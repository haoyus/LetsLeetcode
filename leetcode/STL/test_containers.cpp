#include <unordered_set>
#include <iostream>

using std::unordered_set;
using std::cout;
using std::endl;

int main()
{
    unordered_set<int> uoset;
    for(int i = 0; i<10; ++i){
        uoset.insert(i*i);
    }

    auto itr = uoset.find(5);
    if(itr != uoset.end())
        cout << "found!" << endl;
    else
        cout << "not found!\n";
    
    return 0;
}