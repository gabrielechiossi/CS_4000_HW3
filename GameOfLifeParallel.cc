/**
 *   @file: GameOfLifeParallel.cc
 * @author: Gabriele Chiossi
 *   @date: 03/11/21
 */
#include <iostream>
#include <functional>
#include <cstdlib>
#include <array>
#include <unistd.h>
#include <iomanip>
#include <vector>
#include <thread>
#include <pthread.h>
#include "GameOfLifeParallel.h"
using namespace std;

//SimulateLife we initialize all the varibles needed and execute the Conway games of life life_cycles times
vector<vector<int> > GameOfLife::SimulateLife(vector<vector<int> > &board, int life_cycles){
    vector<vector<int> > present = board;
    vector<vector<int> > future = board;
    thread myThreads[4];

    //in this for loop below we find the next Grid with the updated cell and save it to present Grid
    for(int i = 0; i < life_cycles; i++){
        //nextGrid is basically the hearth of this program and this is where most of the operation
        //take place
        //we pass in myThreads becuase we are going to run Conway in parallel
        future = nextGrid(present, myThreads);
        present = future;
    }
    return present;
}

//nextGrid is used to give each thread the work to do and then call them to join
vector<vector<int> > GameOfLife::nextGrid(vector<vector<int> > &board, thread (&myThreads)[4]){
    vector<vector<int> > futureGrid = board;

    //thread myThreads[4];
    //we forced t to 4 threads and here we give each threads all the variables needed to find
    //the future Grid
    for(size_t i = 0; i < 4; i++){
        GameOfLife x;
        myThreads[i] = thread(&GameOfLife::Conway, &x, i, ref(board), ref(futureGrid));
    }
    //here we join all 4 threads
    for(auto &t : myThreads){
        t.join();
    }
    return futureGrid;
}
//Conway is the hearth of the algorithm where most of th works happens
void GameOfLife::Conway(int i, vector<vector<int> > &board, vector<vector<int> > &futureGrid){
    int neighbor[4];
    //here is where we scan the matrix and try to find the position x and y of every cell
    //we split the rows to the 4 threads
    for(int x = ((i*board.size())/4); x < ((i+1)*(board.size()))/4; x++){
        for(int y = 0 ; y < board.size(); y++){
            //for each cell we first find how many neighbor it has with checkNeighbor then
            //we update the cell based on the rules given in futureGrid
            //neighbor is an array so we avoid race condition by having multiple thread
            //using the same neighbor number
            neighbor[i] = checkNeighbor(board, x, y);
            if((board[x][y] == 1) && (neighbor[i] >= 4)){
                //alive and with more than 4 neighbor gets set to dead
                futureGrid[x][y] = 0;
            }else if((board[x][y] == 1) && (neighbor[i] == 0 || neighbor[i] == 1)){
                //alive and with 0 or 1 neighbor gets set to dead
                futureGrid[x][y] = 0;
            }else if((board[x][y] == 1 || board[x][y] == 2) && (neighbor[i] == 2 || neighbor[i] == 3)){
                //alive or immortal and with 2 or 3 neighbor gets copy from the current matrix
                //becasue nothing changed based on Conway's rule
                futureGrid[x][y] = board[x][y];
            }else if((board[x][y] == 0) && (neighbor[i] == 3)){
                //dead and with 3 neighbor gets set to alive
                futureGrid[x][y] = 1;
            }else{
                //if it gets to the else means it didn't trig any of the past condition and it stay
                //the same in the futureGrid too
                futureGrid[x][y] = board[x][y];
            }
        }
    }
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