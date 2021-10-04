#include <string>
#include <queue>
#include <map>
#include <unordered_set>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include<iostream>
#include<random>
#include<chrono>
#include<algorithm>
#include<cmath>
#include<stack>
#include<fstream>
using namespace std;
unordered_set<string> visited;
int search_number = 0;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
class puzzle
{
    public:
    int zerox;
    int zeroy;
    int board[4][4];
    int goal[4][4];
    int table[18][2];
    int step;
    int distance;
    string path;
    puzzle();
    bool isAnswer();
    string convert_to_string();
    int update_distance();
    friend bool operator <(const puzzle& A, const puzzle& B);
    void Print();
    ~puzzle(){};
};
puzzle::puzzle()
{
    zerox = 1;
    zeroy = 2;
    board[0][0] = 11;
    board[0][1] = 9;
    board[0][2] = 4;
    board[0][3] = 15;
    board[1][0] = 1;
    board[1][1] = 3;
    board[1][2] = 0;
    board[1][3] = 12;
    board[2][0] = 7;
    board[2][1] = 5;
    board[2][2] = 8;
    board[2][3]= 6;
    board[3][0]= 13;
    board[3][1]= 2;
    board[3][2]= 10;
    board[3][3]= 14;
    goal[0][0] = 1;
    goal[0][1] = 2;
    goal[0][2] = 3;
    goal[0][3] =4;
    goal[1][0] = 5;
    goal[1][1] = 6;
    goal[1][2] = 7;
    goal[1][3] = 8;
    goal[2][0] = 9;
    goal[2][1] = 10;
    goal[2][2] =11;
    goal[2][3]=12;
    goal[3][0]=13;
    goal[3][1]=14;
    goal[3][2]=15;
    goal[3][3]=0;
    step = 0;
    distance = 0;
    int n = 1;
    for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			table[n][0] = i;
			table[n++][1] = j;
		}
	}
}
bool puzzle::isAnswer()
{
    for(int i = 0; i<4;i++)
    {
        for(int j=0; j<4; j++)
        {
            if(board[i][j]!=goal[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
int puzzle::update_distance()
{
    int sum = 0;
    for(int i=0 ; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
           if(board[i][j]!=0)
           {
               sum+=(abs(table[board[i][j]][0]-i)+abs(table[board[i][j]][1]-j));
           }
        }
    }
    distance = sum;
    return distance;
}
string puzzle::convert_to_string()
{
    string st;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			st.push_back((char)(board[i][j]+'0'));
		}
	}
    return st;
}
bool operator <(const puzzle& A, const puzzle& B)
{
    return ((A.distance*3+A.step) > (B.distance*3+B.step));
}
void puzzle::Print()
{
    for(int i = 0; i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}
    cout <<"distance: "<<distance<<endl;
    cout<<"step: "<<step<<endl;
}
bool AStar(puzzle P)
{   
    visited.clear();
    priority_queue<puzzle>q;
    P.update_distance();
    q.push(P);
    while(!q.empty())
    {
        puzzle u = q.top();
        q.pop();
        search_number++;
        if(u.distance == 0)
        {
            cout<<u.path<<endl;
            return true;
        }
        for(int i=0; i<4;i++)
        {
            int x = u.zerox+dx[i];
            int y = u.zeroy+dy[i];
            if((x>=0)&&(y>=0)&&(x<=3)&&(y<=3))
            {
                puzzle v = u;
                swap(v.board[x][y],v.board[u.zerox][u.zeroy]);
                v.step = u.step + 1;
                v.zerox = x;
                v.zeroy = y;
                v.update_distance();
                if (i == 0) v.path.push_back('R');
				else if (i == 1) v.path.push_back('L');
				else if (i == 2) v.path.push_back('D');
				else if (i == 3) v.path.push_back('U');
                if(v.path.size() >=2)
                {
                    int prev = v.path.size()-1;
                    int preprev = v.path.size()-2;
                    if((v.path[prev] == 'U' && v.path[preprev] == 'D')
						||(v.path[prev] == 'D' && v.path[preprev] == 'U')
						||(v.path[prev] == 'L' && v.path[preprev] == 'R')
						||(v.path[prev] == 'R' && v.path[preprev] == 'L'))
					continue;
                }
                if(v.distance == 0)
                {
                    cout<<v.path<<endl;
                    cout<<v.step<<endl;
                    return true;
                }
                if(!visited.count(v.convert_to_string()))
                {
                    visited.insert(v.convert_to_string());
                    q.push(v);
                }
            }

        }


    }
    return false;
}

const int MAX_SEARCH_STEP=50;
stack<puzzle>s;
puzzle DFS(puzzle P)
{
    P.update_distance();
    s.push(P);
    while(!s.empty())
    {
        puzzle u =s.top();
        s.pop();
        if(u.distance == 0)
        {
           return u;
        }
        for(int i=0; i<=3; i++)
        {
            int x = u.zerox+dx[i];
            int y = u.zerox+dy[i];
            if(x>=0&&y>=0&&x<=3&&y<=3)
            {
                puzzle v = u;
                swap(v.board[x][y],v.board[u.zerox][u.zeroy]);
                v.step = u.step+1;
                v.zerox=x;
                v.zeroy=y;
                v.update_distance();
                if(v.step <= MAX_SEARCH_STEP)
                {
                    s.push(v);
                }
                
            }
        }
    }
  cout << "fail"<<endl;
  return P;
}
int main()
{
    puzzle A,B;
    AStar(A);
    cout<<search_number<<endl;
    //visited.insert(A.convert_to_string());
    //B = DDFS(A);
    cout<<B.path<<endl;
    return 0;
}