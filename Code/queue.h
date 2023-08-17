#ifndef QUEUE_H_
#define QUEUE_H_

#include "hzrdptrs.h"

/******************************************************************************* 
* * Lock-free concurrent queue *
*******************************************************************************/
struct qnode {
  int data;
  struct qnode *next;
};

struct queue {
  struct qnode *head;
  struct qnode *tail;
};

struct qnode *queue_newnode(int data) ;
struct queue *queue_init() ;
void queue_enqueue(struct queue *q, int d, struct hprectype *hprect) ;
int queue_dequeue(struct queue *q, struct hprectype *hprect, HP *hp) ;

#endif