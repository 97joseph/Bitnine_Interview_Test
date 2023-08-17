#ifndef HZRDPTRS_H_
#define HZRDPTRS_H_

#include "list.h"

 struct hprectype {
  bool active;
  unsigned int rcount; /*retired count*/
  struct listtype *rlist; /*retired list*/
  void *HP[K];
  struct hprectype *next;
};
/* i don't like typedefs, we should change this too... but i'm afraid
   of hp being a very common shorthand */
typedef struct _HP{
  struct hprectype *headHPRec;
  int H;
} HP;

int R(int H) ;
void scan(HP *hp, struct hprectype *myhprec) ;
void help_scan(HP *hp, struct hprectype *myhprec) ;
HP *HP_init() ;
struct hprectype *newHPRec() ;
struct hprectype *allocate_HPRec(HP *hp) ;
void retire_HPRec(struct hprectype *myhprec) ;
void retire_node(HP *hp, struct hprectype *myhprec, void *node) ;

#endif