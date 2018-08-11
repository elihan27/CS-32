//
//  main.cpp
//  Proj4.3
//
//  Created by Elizabeth Han on 2/13/17.
//  Copyright © 2017 Elizabeth Han. All rights reserved.
//




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
    
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = '@'; //marking visited space
  
    if (sr!=0 && maze[sr-1][sc] != '@' && maze[sr-1][sc] != 'X') // NORTH
    {
        if (pathExists(maze, nRows, nCols, sr-1, sc, er, ec)==true)
            return true;
    }
    if (sc!=nCols && maze[sr][sc+1]!= '@' && maze[sr][sc+1]!= 'X') //EAST
    {
        if (pathExists(maze, nRows, nCols, sr, sc+1, er, ec)== true)
            return true;
                
    }
    if (sr!=nRows && maze[sr+1][sc]!= '@' && maze[sr+1][sc]!= 'X') //SOUTH
    {
         if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec)== true)
             return true;
                
    }
    if (sc!=0 && maze[sr][sc-1]!= '@'&& maze[sr][sc-1]!= 'X')
    {
        if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec)== true)
            return true;

    }
    
        
    
    return false;
    
}

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise



