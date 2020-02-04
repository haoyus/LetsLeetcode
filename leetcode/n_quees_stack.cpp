#include <stack>
#include <iostream>

using std::stack;
using std::cout;
using std::endl;

//queen struct
struct Queen
{
    int x,y;

    Queen(int xx=0,int yy=0):x(xx),y(yy){};

    bool operator== (const Queen& q) const{
        return x==q.x || y==q.y || (x+y==q.x+q.y) || (x-y==q.x-q.y);
    };

    bool operator!= (const Queen& q) const{
        return !(*this == q);
    };

    void announce(){std::cout<<x<<", "<<y<<"\n";};
    void draw(){
        switch(y){
            case 0: 
                cout<<"'x',' ',' ',' '\n"; break;
            case 1:
                cout<<"' ','x',' ',' '\n";
                break;
            case 2:
                cout<<"' ',' ','x',' '\n";
                break;
            case 3:
                cout<<"' ',' ',' ','x'\n";
                break;
            default: cout<<"error\n";break;
        }
    }
};

//try place next queen
bool foundConflict(stack<Queen> team,const Queen& q)
{
    while(!team.empty()){
        if(team.top()==q)
            return true;
        else
            team.pop();
    }
    return false;
}

//print one answer
void printOneAns(stack<Queen> ans){
    while (!ans.empty())
    {
        ans.top().announce();
        ans.pop();
    }
    cout<<"----------\n";
}


//find all solutions
/**
 * 1. Init with q=(0,0)
 * 2. IF q has no conflict with stack AND q in range, place q in stack then go to next row by ++q.x
 * 3. ELSE IF q has conflict, Probe next column by ++q.y
 * 4. Check if q.y goes out of range, IF so, Backtrack to previous row by q=pop(), and Trim by ++q.y.
 *                                    Do same thing when reached a solution
 * 5. Iterate to 2, try to accumulate stack
 * 6. End finding solutions when run out of options at root
 * 7. add a print in 2
*/
void placeQueens(int N)
{
    int soluNum = 0;
    stack<Queen> solution;
    Queen q(0,0);

    do {
        if(!foundConflict(solution,q) && q.y<N)//dont have to check x<N because backtracking when solution reach N
        {//current queen y in range(MUST Check!) and No conflict with existing queens
            solution.push(q);//place current queen
            q.x++;           //Then go to next row and start from column 0
            q.y = 0;
        }
        else {
            q.y++;//try next column of same row
        }

        //print one solution
        if (solution.size() >= N) {
            cout << "Solution " << ++soluNum << std::endl;
            printOneAns(solution);
        }

        //if y reached N still conflict, OR reached a solution
        if (q.y >= N || solution.size() >= N) {
            q = solution.top();//go back one row, and try next column on that row
            solution.pop();
            q.y++;//may already going out of range
        }

    } while (!(q.x == 0 && q.y >= N));//do while 1st row still in range, i.e. havent run out of options at root
}



int main()
{
    placeQueens(5);
}




void placeQueens2(int N)
{
    stack<Queen> solu;
    Queen q;

    do
    {
        if (solu.size() >= N || q.y >= N)
        {
            q = solu.top();
            solu.pop();
            q.y++;
        }
        else
        {
            //2-3
        }
    } while (q.x > 0 || q.y < N);
}