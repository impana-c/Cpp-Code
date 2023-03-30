//
//  mazequeue.cpp
//  Homework2
//
//  Created by Impana on 2/7/23.
//

#include <queue>
#include <string>
#include <iostream>
using namespace std;


class Coord
{
  public:
    Coord(int r, int c) : m_row(r), m_col(c) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
  private:
    int m_row;
    int m_col;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    queue<Coord> coordStack;
    coordStack.push(Coord(sr,sc));
    (maze[sr])[sc] = 'D';
    
    while(!coordStack.empty()){
        int cr = (coordStack.front()).r();
        int cc = (coordStack.front()).c();
        cerr << "(" << cr << ", " << cc << ")" << endl;
        coordStack.pop();
        
        if ( (cr == er) && (cc == ec) )
            return true;
        if ( (cc+1 < nCols) && ((maze[cr])[cc+1] == '.') ){
            coordStack.push(Coord(cr,cc+1));
            (maze[cr])[cc+1] = 'D';
        }
        if ( (cr-1 >= 0) && ((maze[cr-1])[cc] == '.') ){
            coordStack.push(Coord(cr-1,cc));
            (maze[cr-1])[cc] = 'D';
        }
        if ( (cc-1 >= 0) && ((maze[cr])[cc-1] == '.') ){
            coordStack.push(Coord(cr,cc-1));
            (maze[cr])[cc-1] = 'D';
        }
        if ( (cr+1 < nRows) && ((maze[cr+1])[cc] == '.') ){
            coordStack.push(Coord(cr+1,cc));
            (maze[cr+1])[cc] = 'D';
        }
    }
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X..X...X.X",
        "X.XXXX.X.X",
        "X.X.X..X.X",
        "X...X.XX.X",
        "XXX......X",
        "X.X.XXXX.X",
        "X.XXX....X",
        "X...X..X.X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10,10, 5,3, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
