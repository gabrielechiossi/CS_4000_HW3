//
// Example Stub for Class file for CS 4000, HW #3
//
//
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <array>
using namespace std;
#ifndef CS4000_GAME_OF_LIFE
#define CS4000_GAME_OF_LIFE
class GameOfLife {
public:
  vector<vector<int> > SimulateLife(vector<vector<int> > &board, int life_cycles);
  vector<vector<int> > nextGrid(vector<vector<int> > &board, int life_cycles);
  int checkNeighbor(vector<vector<int> > &board, int x, int y);
};
#endif
