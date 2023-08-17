#ifndef LIST_H_
#define LIST_H_
/*****************************************************************************/
/* List of elements */
/*****************************************************************************/
/*
  If the number of threads grows too much, the action of scanning the
  retire list of one hprec node against the HP list of every other node,
  could become inefficient. Since the HP list of all nodes combined could
  have potentially 4X the number of threads, we need and structure that
  allows fast construction and fast queries (eg. Hash Table).
  We are planning to make this improvement in future versions
*/
#define K 4 /*maximun number of hazard pointers per threads*/
#define L 256 /*initial size of the list (most be a power of 2)
                (approx. 3-4 times the expected number of threads)*/

struct listtype {
  void *list[L];
  int head;
  int tail;
};

struct listtype *list_init() ;
int list_push(struct listtype *list, void *node) ;
void *list_pop(struct listtype *list) ;
bool list_lookup(struct listtype *list, void *node) ;
int list_popall(struct listtype *list, void **output);

#endif