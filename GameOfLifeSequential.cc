/**
 *   @file: GameOfLifeSequential.cc
 * @author: Gabriele Chiossi
 *   @date: 03/11/21
 */
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <array>
#include "GameOfLifeSequential.h"
using namespace std;

//SimulateLife we initialize all the varibles needed and execute the Conway games of life life_cycles times
vector<vector<int> > GameOfLife::SimulateLife(vector<vector<int> > &board, int life_cycles){
    vector<vector<int> > present = board;
    vector<vector<int> > future = board;
    //in this for loop below we find the next Grid with the updated cell and save it to present Grid
    for(int i = 0; i < life_cycles; i++){
        //nextGrid is basically the hearth of this program and this is where most of the operation
        //take place
        future = nextGrid(present);
        present = future;
    }
    return present;
}

//nextGrid is the hearth of the algorithm where most of th works happens
vector<vector<int> > GameOfLife::nextGrid(vector<vector<int> > &board){
    vector<vector<int> > futureGrid = board;
    //here is where we scan the matrix and try to find the position x and y of every cell
    for(int x = 0; x < board.size(); x++){
        for(int y = 0; y < board.size(); y++){
            //for each cell we first find how many neighbor it has with checkNeighbor then
            //we update the cell based on the rules given in futureGrid
            int neighbor = checkNeighbor(board, x, y);
            if((board[x][y] == 1) && (neighbor >= 4)){
                //alive and with more than 4 neighbor gets set to dead
                futureGrid[x][y] = 0;
            }else if((board[x][y] == 1) && (neighbor == 0 || neighbor == 1)){
                //alive and with 0 or 1 neighbor gets set to dead
                futureGrid[x][y] = 0;
            }else if((board[x][y] == 1 || board[x][y] == 2) && (neighbor == 2 || neighbor == 3)){
                //alive or immortal and with 2 or 3 neighbor gets copy from the current matrix
                //becasue nothing changed based on Conway's rule
                futureGrid[x][y] = board[x][y];
            }else if((board[x][y] == 0) && (neighbor == 3)){
                //dead and with 3 neighbor gets set to alive
                futureGrid[x][y] = 1;
            }else{
                //if it gets to the else means it didn't trig any of the past condition and it stay
                //the same in the futureGrid too
                futureGrid[x][y] = board[x][y];
            }
        }
    }
    
    return futureGrid;
}
//checkNeighbor finds the neighbor of each cell x, y pass from nextGrid
int GameOfLife::checkNeighbor(vector<vector<int> > &board, int x, int y){
    //this is a bruteforce solution
    //in fact we check all 8 directions if a neighbor is found we increment alive by one
    //checked all the 8 locations arund the cell we return the number of alive neighbor
    //to nextGrid
    //we use the formula (n+i+/-1) mod n when x or y have to be incremented by one
    int alive = 0;
    for(int i = 0; i < 8; i++){
        if(i == 0){
            int posx = (((x + board.size())+1)%(board.size()));
                if(board[posx][y] == (1 || 2)){
                    alive++;
                }
        }else if(i == 1){
            int posx = (((x + board.size())-1)%(board.size()));
            if(board[posx][y] == (1 || 2)){
                alive++;
            }
        }else if(i == 2){
            int posx = (((x + board.size())-1)%(board.size()));;
            int posy = (((y + board.size())+1)%(board.size()));
            if(board[posx][posy] == (1 || 2)){
                alive++;
            }
        }else if(i == 3){
            int posx = (((x + board.size())-1)%(board.size()));;
            int posy = (((y + board.size())-1)%(board.size()));;
            if(board[posx][posy] == (1 || 2)){
                alive++;
            }
        }else if(i == 4){
            int posx = (((x + board.size())+1)%(board.size()));
            int posy = (((y + board.size())+1)%(board.size()));
            if(board[posx][posy] == (1 || 2)){
                alive++;
            }
        }else if(i == 5){
            int posx = (((x + board.size())+1)%(board.size()));
            int posy = (((y + board.size())-1)%(board.size()));
            if(board[posx][posy] == (1 || 2)){
                alive++;
            }
        }else if(i == 6){
            int posy = (((y + board.size())+1)%(board.size()));
            if(board[x][posy] == (1 || 2)){
                alive++;
            }
        }else if(i == 7){
            int posy = (((y + board.size())-1)%(board.size()));
            if(board[x][posy] == (1 || 2)){
                alive++;
            }
        }
    }
    return alive;
}