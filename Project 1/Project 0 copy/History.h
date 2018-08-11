//
//  History.h
//  Project 0
//
//  Created by Elizabeth Han on 1/16/17.
//  Copyright © 2017 Elizabeth Han. All rights reserved.
//

#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

class Arena;

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_rows;
    int m_cols;
    int m_count[MAXROWS][MAXCOLS];
    
    
};

#endif /* HISTORY_INCLUDED */
