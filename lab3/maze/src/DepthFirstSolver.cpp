/**
 * @file DepthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements depth-first search.
 *
 * @section License
 * Copyright (c) 2014-2015 California Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the California Institute of Technology.
 *
 */

#include "DepthFirstSolver.hpp"

/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
DepthFirstSolver::DepthFirstSolver(class MazeSolverApp *app)
{
    stack = new CoordinateStack(app);
    init();
}

/**
 * @brief Initializes the solver (student-implemented).
 */
void DepthFirstSolver::init()
{
    // add (0, 0) to stack
    stackitem *item = new stackitem();
    Coordinate * coord = new Coordinate(0, 0);
    item->c = *coord;
    (*stack).push(item);
    // initialize visited to all false
    for(int i = 0; i < WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            visited[i][j] = false;
        }
    }
}

/**
 * @brief Deinitializes the solver.
 */
DepthFirstSolver::~DepthFirstSolver()
{
    deinit();
}


/**
 * @brief Deinitializes the solver (student-implemented).
 */
void DepthFirstSolver::deinit()
{
    delete stack;
}

/**
 * @brief Solves the maze given by `maze`.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 */
void DepthFirstSolver::solve(MazeGrid *maze)
{
    /* TODO: Solve the maze.
     *
     * You are provided a `visited` member variable that you can use to
     * track which cells you have already visited; you are responsible for
     * maintaining it, filling it with useful information, and using it
     * in a consistent way. */
    while(!stack->is_empty()){
        stackitem * current = stack->peek();
        stackitem * next = new stackitem();
        int x = current->c.x;
        int y = current->c.y;
        Coordinate * coord = new Coordinate(current->c.x, current->c.y);
        next->c = *coord;
        visited[x][y] = true;
        if(x == WIDTH - 1 && y == HEIGHT - 1){
            return;
        }
        int possible_moves = maze->get_possible_moves(x, y);
        if (possible_moves & N && !visited[x][y-1]){
            next->c.y--;
            stack->push(next);
        } else if(possible_moves & E && !visited[x + 1][y]){
            next->c.x++;
            stack->push(next);
        } else if(possible_moves & S && !visited[x][y+1]){
            next->c.y++;
            stack->push(next);
        }else if (possible_moves & W && !visited[x - 1][y]){
            next->c.x--;
            stack->push(next);
        }else{
            delete next;
            delete coord;
            stackitem * item = stack->pop();
            delete item;
        }
    }
}

/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 */
vector<Coordinate> DepthFirstSolver::get_path()
{
    vector<Coordinate> list;

    stackitem * current = stack->peek();

    while(current != nullptr){
        Coordinate *coord = new Coordinate(current->c.x, current->c.y);
        list.push_back(*coord);
        current = current->next;
    }

    return list;
}

