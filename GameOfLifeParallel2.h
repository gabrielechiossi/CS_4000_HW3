/**
 *   @file: GameOfLifeParallel.h
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
#include <pthread.h>
#include <mutex>
using namespace std;
#ifndef CS4000_GAME_OF_LIFE
#define CS4000_GAME_OF_LIFE
class GameOfLife {
public:
  //function given to set up the game and how many times we have to update the baord
  vector<vector<int> > SimulateLife(vector<vector<int> > &board, int life_cycles);
  //nextGrid scan the all Grid and gets the future Grid
  void nextGrid(int i, int life_cycles, vector<vector<int> > &board, vector<vector<int> > &final);
  int checkNeighbor(vector<vector<int> > &board, int x, int y);
  //Conway used in the parallel version to scan the Grid and gets the future Grid
  void Conway(vector<vector<int> > &board, vector<vector<int> > &futureGrid, int i);
};
#endif
