/*
 -------------------------------------
 File:    queue.c
 Queue data structure
 -------------------------------------
 Author:  Chandler Mayberry
 Version  2021-03-01
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"

void enqueue(QUEUE *qp, NODE *np) {
	//push onto queue rear
	if (qp->front != NULL && qp->rear != NULL) {
		qp->rear->next = np;
		qp->rear = np;
	} else {
		qp->front = np;
		qp->rear = np;
	}

	return;
}

NODE* dequeue(QUEUE *qp) {
	//grab next in queue
	NODE *front_return = qp->front;

	//if the queue isnt empty:
	if (front_return != NULL) {
		qp->front = qp->front->next;

		//if the front is now null then the rear must be null too
		if (qp->front == NULL)
			qp->rear = NULL;
	}

	return front_return;

}

void clean_queue(QUEUE *qp) {

	//if the queue isnt empty:
	if (qp->front != NULL) {
		//go to each node in the queue
		//clean node using the common clean method
		while (qp->front != NULL) {
			clean(&qp->front);
		}
	}

	return;
}
