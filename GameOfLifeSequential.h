/**
 *   @file: GameOfLifeSequential.h
 * @author: Gabriele Chiossi
 *   @date: 03/11/21
 */
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <iomanip>
#include <thread>
#include <vector>
#include <array>
#include <omp.h>
using namespace std;
#ifndef CS4000_GAME_OF_LIFE
#define CS4000_GAME_OF_LIFE
class GameOfLife {
public:
  //function given to set up the game and how many times we have to update the baord
  vector<vector<int> > SimulateLife(vector<vector<int> > &board, int life_cycles);
  //nextGrid scan the all Grid and gets the future Grid
  vector<vector<int> > nextGrid(vector<vector<int> > &board);
  //checkNeighbor checks for any alive neighbor around the cell pass in with x, y
  int checkNeighbor(vector<vector<int> > &board, int x, int y);
};
#endif
