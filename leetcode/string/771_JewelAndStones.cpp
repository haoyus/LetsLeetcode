#include <string>

using std::string;

class Solution {
public:
    int numJewelsInStones(string& J, string S) {
        int num = 0;
        for(int i=0; i<J.length(); ++i){
            for(auto itr = S.begin(); itr!=S.end(); ){
                if(J[i] == *itr) {
                    ++num;
                    itr = S.erase(itr);
                }
                else
                    ++itr;
            }
        }
        
        return num;
    }
};