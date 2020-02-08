/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <iostream>
#include <string>
#include <utility>

#include "maze.h"
#include "mazeUtils.h"

using namespace std;

int main(int argc, char** argv) {
  if (argc != 3) {
    //if there's more than 3 arguments, print error message
    cout << "You can only provides two arguments" << endl;
  } else {
    string filename = argv[1];
    string searchType = argv[2];
    if (searchType != "depth" && searchType != "breadth") {
    //if the third argument is not a search type, print error message
    cout << "Search type can only be depth or breadth" << endl;
    } else {
      try {
        Maze* maze = loadMap(filename);
        List<Position*>* solution;

        //solve the maze using the desired type of method
        if (searchType == "depth") {
          solution = maze->solveDepthFirst();
        } else if (searchType == "breadth") {
          solution = maze->solveBreadthFirst();
        }

        if (solution != nullptr) {
          //if the maze has a solution, call renderAnswer and print it
          string answer = renderAnswer(maze, solution);
          cout << answer << endl;
        } else {
          //if the maze has no solution, print a message
          cout << "There's no solution to this maze" << endl;
        }

        delete maze;
        delete solution;
      } catch (runtime_error e) {
        //if the filename is invalid or any other error happens while
        //calling loadmap or renderAnswer, throw error
        cout << "cannot open the file" << endl;
      }
  }
  return 0;
  }
}
