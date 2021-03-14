#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <array>
#include <omp.h>
#include "GameOfLife.h"
using namespace std;


vector<vector<int> > GameOfLife::SimulateLife(vector<vector<int> > &board, int life_cycles){
    vector<vector<int> > present = board;
    vector<vector<int> > future = board;
    for(int i = 0; i < life_cycles; i++){
        future = nextGrid(present);
        present = future;
    }
    return present;
}

vector<vector<int> > GameOfLife::nextGrid(vector<vector<int> > &board){
    vector<vector<int> > futureGrid = board;
    #pragma omp parallel for num_threads(4)
    for(int x = 0; x < board.size(); x++){
        for(int y = 0; y < board.size(); y++){
            int neighbor = checkNeighbor(board, x, y);

            if((board[x][y] == 1) && (neighbor >= 4)){
                futureGrid[x][y] = 0;
            }else if((board[x][y] == 1) && (neighbor == 0 || neighbor == 1)){
                futureGrid[x][y] = 0;
            }else if((board[x][y] == 1 || board[x][y] == 2) && (neighbor == 2 || neighbor == 3)){
                futureGrid[x][y] = board[x][y];
            }else if((board[x][y] == 0) && (neighbor == 3)){
                futureGrid[x][y] = 1;
            }else{
                futureGrid[x][y] = board[x][y];
            }
        }
    }
    
    return futureGrid;
}

int GameOfLife::checkNeighbor(vector<vector<int> > &board, int x, int y){
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