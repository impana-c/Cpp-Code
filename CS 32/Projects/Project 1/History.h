//
//  History.h
//  Project 1
//
//  Created by Impana on 1/12/23.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
{
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int m_grid[MAXROWS][MAXCOLS];
        int m_rows;
        int m_cols;
};

#endif /* History_h */
