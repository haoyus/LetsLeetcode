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

//find one solution
void placeQueens(int N)
{
    stack<Queen> solution;
    Queen q(0,0);

    while(solution.size()<N){
        if(!foundConflict(solution,q) && q.y<N){
            solution.push(q);
            q.x++;
            q.y = 0;
        }
        else{
            q.y++;
        }
        if(q.y>=N){
            q = solution.top();
            solution.pop();
            q.y++;
        }
        
    }

    while(!solution.empty()){
        solution.top().announce();
        solution.pop();
    }
}

int main()
{
    placeQueens(4);
}