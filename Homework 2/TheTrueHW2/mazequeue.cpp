//
//  main.cpp
//  HW2.0
//
//  Created by Elizabeth Han on 2/5/17.
//  Copyright © 2017 Elizabeth Han. All rights reserved.
//

#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};



bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    
    Coord start(sr, sc);
    queue<Coord> coordQueue;
    coordQueue.push(start);
    maze[sr][sc] = '@';
    while (!coordQueue.empty())
    {
        Coord view = coordQueue.front();
        coordQueue.pop();
        
        
        if (view.r() == er && view.c()== ec)
        {
            return true;
        }
        else
        {
            if (view.r()!=0 && maze[view.r()-1][view.c()] != '@' && maze[view.r()-1][view.c()] != 'X') // NORTH
            {
                coordQueue.push(Coord(view.r()-1, view.c()));
                maze[view.r()-1][view.c()] = '@';
            }
            if (view.c()!=nCols && maze[view.r()][view.c()+1]!= '@' && maze[view.r()][view.c()+1]!= 'X') //EAST
            {
                coordQueue.push(Coord(view.r(), view.c()+1));
                maze[view.r()][view.c()+1] = '@';
                
            }
            if (view.r()!=nRows && maze[view.r()+1][view.c()]!= '@' && maze[view.r()+1][view.c()]!= 'X') //SOUTH
            {
                coordQueue.push(Coord(view.r()+1, view.c()));
                maze[view.r()+1][view.c()] = '@';
                
            }
            if (view.c()!=0 && maze[view.r()][view.c()-1]!= '@'&& maze[view.r()][view.c()-1]!= 'X')
            {
                coordQueue.push(Coord(view.r(), view.c()-1));
                maze[view.r()][view.c()-1] = '@';
                
            }
        }
        
        
    }
    return false;
    
}

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise


int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };
    
    
    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    
    for (int r =0; r!=10; r++)
    {
        for (int c=0; c!=10;c++)
            cout <<maze[r][c];
        cout << endl;
    }
    
}
