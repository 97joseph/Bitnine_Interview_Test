#include <stdbool.h>
#include <malloc.h>
#include <stdlib.h>

#include "list.h"
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
struct listtype *list_init() {
  struct listtype *list = malloc(sizeof(struct listtype));
  list->head = list->tail = 0;
  for (int i = 0; i < L; i++)
    list->list[i] = NULL;
  return list;
}

int list_push(struct listtype *list, void *node) {
  int pos = (list->head + 1) & (L - 1); /*circular list*/
  if (pos != list->tail) {
    list->list[list->head] = node;
	list->head = pos;
	return pos;
  }
  else return -1;
}
void *list_pop(struct listtype *list) {
  if (list->head != list->tail) {
    void *tmpval = list->list[list->tail];
	list->list[list->tail] = NULL;
    list->tail = (list->tail++) & (L - 1);
    return tmpval;
  }
  else {
	void *tmpval = list->list[list->tail];
	list->list[list->tail] = NULL;
	return tmpval;
  }
}
bool list_lookup(struct listtype *list, void *node) {
/* we could do something better here, but, given the small size of L,
   is not worth it. */
  for (int i = 0; i < L; i++)
    if (list->list[i] == node) return true;
  return false;
}
/*return the number of elements*/
int list_popall(struct listtype *list, void **output) {
  int length = 0;
  if (list->tail <= list->head) length = list->head - list->tail;
  else length = L - list->tail + list->head;
  for (int i = list->tail; i < list->head; (i++) & (L-1))
    output[i] = list->list[i];

  list->head = list->tail = 0;
  return length;
}