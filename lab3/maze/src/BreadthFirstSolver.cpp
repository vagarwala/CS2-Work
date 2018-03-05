/**
 * @file BreadthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements breadth-first search.
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

#include "BreadthFirstSolver.hpp"

#include <algorithm>
#include <vector>

using namespace std;

/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
BreadthFirstSolver::BreadthFirstSolver(class MazeSolverApp *app)
{
    queue = new CoordinateQueue(app);
    init();
}

/**
 * @brief Initializes the solver (student-implemented).
 */
void BreadthFirstSolver::init()
{
    /* TODO: Write your initialization code here! */
    queueitem *item = new queueitem();
    Coordinate * coord = new Coordinate(0, 0);
    item->c = *coord;
    (*queue).enqueue(item);

    for(int i = 0; i< WIDTH; i++){
        for (int j = 0; j < HEIGHT; j++){
            visited[i][j].visited = false;
            Coordinate * coord = new Coordinate(-1, -1);
            visited[i][j].from = *coord;
        }
    }
}

/**
 * @brief Deinitializes the solver.
 */
BreadthFirstSolver::~BreadthFirstSolver()
{
    deinit();
}

/**
 * @brief Deinitializes the solver (student-implemented).
 */
void BreadthFirstSolver::deinit()
{
    /* TODO: Write your cleanup code here! */
    delete queue;
}

/**
 * @brief Solve the maze given by `maze`.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 */
void BreadthFirstSolver::solve(MazeGrid *maze)
{
    /* TODO: Solve the maze.
     *
     * You are provided a member variable `visited` that stores
     * (bool, Coordinate) pairs describing whether a square has already
     * been checked and the square immediately preceding it in the path.
     * You are responsible for maintaining this array, filling it with
     * useful information, and using it in a consistent way. */
    queueitem * end;
    while(!queue->is_empty()){
        queueitem * current = queue->dequeue();
        queueitem * next;
        Coordinate * coord;
        int x = current->c.x;
        int y = current->c.y;
        visited[x][y].visited = true;
        if(x == WIDTH - 1 && y == HEIGHT - 1){
            end = current;
            break;
        }

        int possible_moves = maze->get_possible_moves(x, y);
        if(possible_moves & N && !visited[x][y - 1].visited){
            next = new queueitem();
            coord = new Coordinate(x, y - 1);
            next->c = *coord;
            visited[x][y - 1].from = current->c;
            queue->enqueue(next);
        }
        if (possible_moves & E && !visited[x + 1][y].visited){
            next = new queueitem();
            coord = new Coordinate(x + 1, y);
            next->c = *coord;
            visited[x + 1][y].from = current->c;
            queue->enqueue(next);
        }
        if (possible_moves & S && !visited[x][y + 1].visited){
            next = new queueitem();
            coord = new Coordinate(x, y + 1);
            next->c = *coord;
            visited[x][y + 1].from = current->c;
            queue->enqueue(next);
        }
        if (possible_moves & W && !visited[x - 1][y].visited){
            next = new queueitem();
            coord = new Coordinate(x - 1, y);
            next->c = *coord;
            visited[x - 1][y].from = current->c;
            queue->enqueue(next);
        }

    }

    while (!queue->is_empty()){
        delete queue->dequeue();
    }
    queue->enqueue(end);
    while(visited[queue->peek_last()->c.x][queue->peek_last()->c.y].from.x != -1){
        queueitem * prev = new queueitem();
        prev->c = visited[queue->peek_last()->c.x][queue->peek_last()->c.y].from;
        queue->enqueue(prev);
    }
    return;
}

/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 */
vector<Coordinate> BreadthFirstSolver::get_path()
{
    vector<Coordinate> list;

    /* TODO: Find the current path through the maze and return it as a vector.
     * For a BFS, this is a little tricky -- the top element in the queue
     * only tells you the last point in the path; you need to trace back up
     * using the `visited` member array. */

    queueitem * current = queue->peek();

    while(current != nullptr){
        Coordinate *coord = new Coordinate(current->c.x, current->c.y);
        list.push_back(*coord);
        current = current->next;
    }

    reverse(list.begin(), list.end());

    return list;
}

