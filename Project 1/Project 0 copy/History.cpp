//
//  History.cpp
//  Project 0
//
//  Created by Elizabeth Han on 1/16/17.
//  Copyright © 2017 Elizabeth Han. All rights reserved.
//
#include <iostream>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
#include "globals.h"
#include "Arena.h"
#include "History.h"

using namespace std;

History :: History (int nRows, int nCols)
{
    nRows = m_rows;
    nCols = m_cols;
    
    int r, c;
    for (r = 1; r <= nRows; r++)
    {for (c = 1; c <= nCols; c++)
            m_count[r-1][c-1] = 0;
    }
}

bool History:: record(int r, int c)
{
    
    if (r < 1|| r > m_rows || c<1 || c > m_cols)
        return false;
    else
        m_count[r][c] = m_count[r][c]+1;
    return true;

}

void History:: display() const
{
    char m_display[MAXROWS][MAXCOLS];
    int r, c;
    for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
        {
            if (m_count[r-1][c-1]==0)
                m_display[r-1][c-1] = '.';
            else if (m_count[r-1][c-1]>=1||m_count[r-1][c-1]<=25)
                m_display[r-1][c-1] = 'A'+ m_count[r-1][c-1] -1;
            else if (m_count[r-1][c-1]>=26)
                m_display[r-1][c-1] = 'Z';
        }
        clearScreen();
        
        for (r = 1; r<= m_rows; r++)
        {
            for (c = 1; c <= m_cols; c++)
                cout << m_display[r-1][c-1];
            cout << endl;
        }
        
        clearScreen();
        cout << endl;
    }
        
}



    /*char k = 'A';
    
    // Fill displayGrid with dots (empty) and stars (poison pellets)
    for (r = 1; r <= 4; r++)
    {for (c = 1; c <= 4; c++)
        displayGrid[r-1][c-1] = k;
        k++;
     
    }
        
    }
    
    for (r = 1; r <= 4; r++)
    {for (c = 1; c <= 4; c++)
        cout << displayGrid[r-1][c-1];
        cout << endl;
        
    }
    
    
    

}
     */
/*
 
 char m_display[MAXROWS][MAXCOLS];
 int r, c;
 for (r = 1; r <= m_rows; r++)
 {
 for (c = 1; c <= m_cols; c++)
 {
 if (m_count[r-1][c-1]==0)
 m_display[r-1][c-1] = '.';
 else if (m_count[r-1][c-1]>=1||m_count[r-1][c-1]<=25)
 m_display[r-1][c-1] = 'A'+ m_count[r-1][c-1] -1;
 else if (m_count[r-1][c-1]>=26)
 m_display[r-1][c-1] = 'Z';
 }
 clearScreen();
 
 for (r = 1; r<= m_rows; r++)
 {
 for (c = 1; c <= m_cols; c++)
 cout << m_display[r-1][c-1];
 cout << endl;
 }
 
 clearScreen();
 cout << endl;
 }

 
 */

/*
 int r, c;
 
 for (r = 1; r <= m_rows; r++)
 {
 for (c = 1; c <= m_cols; c++)
 {
 cout << m_count[r][c];
 }
 cout << endl;
 }
 
 */


/*/ Fill displayGrid with dots (empty) and stars (poison pellets)
for (r = 1; r <= rows(); r++)
for (c = 1; c <= cols(); c++)
displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');

// Indicate each rat's position
for (int k = 0; k < m_nRats; k++)
{
    const Rat* rp = m_rats[k];
    char& gridChar = displayGrid[rp->row()-1][rp->col()-1];
    switch (gridChar)
    {
        case '.':  gridChar = 'R'; break;
        case 'R':  gridChar = '2'; break;
        case '9':  break;
        default:   gridChar++; break;  // '2' through '8'
    }
}*/
