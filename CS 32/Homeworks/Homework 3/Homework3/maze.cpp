//
//  maze.cpp
//  Homework3
//
//  Created by Impana on 2/15/23.
//

#include <string>
#include <iostream>
#include <cassert>
using namespace std;

const char OPEN = '.';
const char SEEN = 'o';

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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if ((sr==er) && (sc==ec))
        return true;
    maze[sr][sc] = SEEN;
    
    if (sr < 0  ||  sr >= nRows  ||  sc < 0  || sc >= nCols  ||
        er < 0  ||  er >= nRows  ||  ec < 0  || ec >= nCols  ||  maze[er][ec] != OPEN)
       return false;
    
    if (maze[sr+1][sc] == OPEN){ //NORTH
        bool x = pathExists(maze, nRows, nCols, sr+1, sc, er, ec);
        if (x == true)
            return true;
    }
    if (maze[sr][sc+1] == OPEN){ //EAST
        bool x = pathExists(maze, nRows, nCols, sr, sc+1, er, ec);
        if (x == true)
            return true;
    }
    if (maze[sr-1][sc] == OPEN){ //SOUTH
        bool x = pathExists(maze, nRows, nCols, sr-1, sc, er, ec);
        if (x == true)
            return true;
    }
    if (maze[sr][sc-1] == OPEN){ //WEST
        bool x = pathExists(maze, nRows, nCols, sr, sc-1, er, ec);
        if (x == true)
            return true;
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
