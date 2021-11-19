/*
-------------------------------------
File:    queue.h
file description
queue data structure _init
-------------------------------------
Author:  Chandler Mayberry
Version  2021-03-01
-------------------------------------
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "common.h"

typedef struct queue {
  NODE *front;
  NODE *rear;
} QUEUE; 

void enqueue(QUEUE *qp, NODE *np);
NODE *dequeue(QUEUE *qp);
void clean_queue(QUEUE *qp);

#endif /* QUEUE_H_ */
