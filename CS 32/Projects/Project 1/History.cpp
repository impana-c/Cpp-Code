//
//  History.cpp
//  Project 1
//
//  Created by Impana on 1/12/23.
//
#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols){
    m_rows = nRows;
    m_cols = nCols;
    for (int r = 0; r < m_rows; r++){
        for(int c = 0; c < m_cols; c++){
            m_grid[r][c] = 0;
        }
    }
}

bool History::record(int r, int c){
    r--; //set to index 0
    c--; //set to index 0
    if (r >= 0 && r<m_rows && c>=0 && c<m_cols){
        m_grid[r][c]++;
    }
    return false;
}
void History::display() const{
    clearScreen();
    for (int r = 0; r < m_rows; r++){
        for (int c = 0; c < m_cols; c++)
            if (1 <= m_grid[r][c] && m_grid[r][c] < 26){
                char x = 'A' + m_grid[r][c] - 1;
                cout << x;
            } else if (m_grid[r][c] >= 26){
                cout << 'Z';
            } else{
                cout << '.';
            }
        cout << endl;
    }
    cout << endl;
}
