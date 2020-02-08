/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>

/* ADTs */
#include "adts/list.h"
#include "adts/orderedCollection.h"
#include "adts/queue.h"
#include "adts/stack.h"

/* Implementations of above ADTs */
#include "adts/stlList.h"
#include "linkedQueue.h"
#include "linkedStack.h"

#include "maze.h"

using namespace std;

Maze::Maze(int width, int height) {
  this->width = width;
  this->height = height;

  //initializing the Positions, the arrays of Positions, and the array of
  //arrays of positions
  this->positions = new Position**[width];
  for (int i = 0; i < width; i++) {
    this->positions[i] = new Position*[height];
    for (int j = 0; j < height; j++) {
      this->positions[i][j] = new Position(i, j);
    }
  }
}

Maze::~Maze() {
  //deleting the Positions, the arrays of Positions, and the array of
  //arrays of positions
  for (int i = 0; i < this->width; i ++) {
    for (int j = 0; j < this->height; j++) {
      delete this->positions[i][j];
    }
    delete[] this->positions[i];
  }
  delete[] this->positions;
}

int Maze::getWidth() {
  return this->width;
}

int Maze::getHeight() {
  return this->height;
}

bool Maze::isWall(int x, int y) {
  return this->positions[x][y]->isWall();
}

void Maze::setWall(int x, int y) {
  this->positions[x][y]->setWall();
}

List<Position*>* Maze::solveBreadthFirst() {
  //create a pointer called exploration that points to a LinkedQueue
  //which stores all the empty grids
  OrderedCollection<Position*>* exploration = new LinkedQueue<Position*>();
  //create a pointer called solution that points to a list of positions
  //which are the path
  List<Position*>* solution = solve(exploration);
  delete exploration;
  return solution;
}

List<Position*>* Maze::solveDepthFirst() {
  OrderedCollection<Position*>* exploration = new LinkedStack<Position*>();
  List<Position*>* solution = solve(exploration);
  delete exploration;
  return solution;
}

List<Position*>* Maze::solve(OrderedCollection<Position*>* exploration) {
  //add starting position
  exploration->insert(this->positions[0][0]);
  //set starting position as visited
  this->positions[0][0]->setVisited();

  //while there are positions left in exploration:
  while (!exploration->isEmpty()) {
    //take a position in the exploration and call it current position (curPos)
    Position* curPos = exploration->remove();
    int i = curPos->getX();
    int j = curPos->getY();
    //if the position is not the exit:
    if (i != this->width - 1 || j != this->height - 1) {
      //get all the neighboring grids of the current position
      List<Position*>* neighbors = getNeighbors(curPos);
      for (int x = 0; x < neighbors->getSize(); x++) {
        //for each neighbor, if is not a wall, set it as visited,
        //set curPos as the previous grid, and add the neighbor to exploration
        if (!neighbors->get(x)->isWall()) {
          neighbors->get(x)->setVisited();
          neighbors->get(x)->setPrevious(curPos);
          exploration->insert(neighbors->get(x));
        }
      }
      delete neighbors;
    } else if (this->positions[i][j]->isVisited()) {
      //if the exit grid has been visited, we create a pointer called
      //solution which points to a list
      List<Position*>* solution = new STLList<Position*>();
      //set the exit to lastPost
      Position* lastPost = this->positions[i][j];
      //while the previous position is not nullptr:
      //add last post to the solution,
      //and set the previous position as lastPost
      while (lastPost->getPrevious() != nullptr) {
        solution->insertFirst(lastPost);
        lastPost = lastPost->getPrevious();
      }
      //add the start position
      solution->insertFirst(lastPost);
      return solution;
    }
  }
  //if we break the while loop without returning, then there's no solution
  //to the maze, return nullptr
  return nullptr;
}


List<Position*>* Maze::getNeighbors(Position* position) {
  List<Position*>* neighbors = new STLList<Position*>();
  int i = position->getX();
  int j = position->getY();
  //check up
  if (j-1 >= 0 && !this->positions[i][j-1]->isVisited()) {
    neighbors->insertLast(this->positions[i][j-1]);
  }
  //check left
  if (i-1 >= 0 && !this->positions[i-1][j]->isVisited()) {
    neighbors->insertLast(this->positions[i-1][j]);
  }
  //check right
  if (i+1 <= this->width - 1 && !this->positions[i+1][j]->isVisited()) {
    neighbors->insertLast(this->positions[i+1][j]);
  }
  //check down
  if (j+1 <= this->height - 1 && !this->positions[i][j+1]->isVisited()) {
    neighbors->insertLast(this->positions[i][j+1]);
  }
  return neighbors;
}
