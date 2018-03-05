/**
 * @file CoordinateQueue.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for queue class that stores Coordinate objects.
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

#include "CoordinateQueue.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

#define ANIMATION_DELAY     (25)

/**
 * @brief Initializes the queue.
 *
 * @param[in] app Reference to the MazeSolverApp; needed
 * to render moves.
 */
#ifndef TESTSUITE
CoordinateQueue::CoordinateQueue(class MazeSolverApp *app)
{
    this->app = app;
    init();
}
#else
CoordinateQueue::CoordinateQueue()
{
    init();
}
#endif

/**
 * @brief Initializes the queue (student-implemented).
 */
void CoordinateQueue::init()
{
   front = nullptr;
   rear = nullptr;
}

/**
 * @brief Deinitializes the queue.
 */
CoordinateQueue::~CoordinateQueue()
{
    deinit();
}

/**
 * @brief Deinitializes the queue (student-implemented).
 */
void CoordinateQueue::deinit()
{
    while(!is_empty()){
        queueitem *item = dequeue();
        delete item;
    }
}

/**
 * @brief Enqueues an item by adding it to the bottom of the
 * queue.
 *
 * @param[in] c Coordinate to enqueue onto the queue.
 */
void CoordinateQueue::enqueue(queueitem *q)
{
    /* Do the operation. */
    do_enqueue(q);

#ifndef TESTSUITE
    /* Update the display, if necessary. */
    SDL_Delay(ANIMATION_DELAY);
    this->app->OnRender();
#endif
}

/**
 * @brief Do the actual enqueue operation (student-implemented).
 *
 * @param[in] c Coordinate to enqueue onto the queue.
 */
void CoordinateQueue::do_enqueue(queueitem *q)
{
    if(is_empty()){
        front = rear = q;
    }
    rear->next = q;
    rear = q;

}

/**
 * @brief Dequeues an item by removing it from the top.
 *
 * @return The dequeued Coordinate.
 */
queueitem* CoordinateQueue::dequeue()
{
    /* Do the operation. */
    return do_dequeue();
}

/**
 * @brief Do the actual dequeue operation (student-implemented).
 *
 * @return The dequeued Coordinate.
 */
queueitem* CoordinateQueue::do_dequeue()
{
    /* TODO: Write your dequeue operation here! */
    if(is_empty()){
        cout << "can't dequeue!" << endl;
        return nullptr;
    }
    queueitem* front_previous = front;
    front = front->next;
    return front_previous;

}

/**
 * @brief Returns the item at the front of the queue without
 * removing it.
 *
 * @return The first Coordinate in the queue.
 */
queueitem* CoordinateQueue::peek()
{
    /* TODO: Write your peek code here! */
    return front;
}

queueitem* CoordinateQueue::peek_last()
{
    /* TODO: Write your peek code here! */
    return rear;
}

/**
 * @brief Returns true is the queue is empty, false otherwise.
 *
 * @return Boolean indicating whether the queue is empty.
 */
bool CoordinateQueue::is_empty()
{
    /* TODO: Is the queue empty??? */
    return (front == nullptr);
}

