#include <stdio.h>
#include <stdlib.h>

#define NO_HOLES 128
#define NO_LISTS 8

typedef unsigned int phys_clicks;

struct hole {
  struct hole *h_next;          /* pointer to next entry on the list */
  phys_clicks h_base;           /* where does the hole begin? */
  phys_clicks h_len;            /* how big is the hole? */
  int freelist;
  int holelist;
};

struct qf_list {
  struct hole *holes[NO_HOLES];
  int hole_count;
};

struct qf_list *qf_table[NO_LISTS];

void initQFTable() {
  int i;
  for (i = 0; i < 8; i++) {
    qf_table[i] = malloc(sizeof(struct qf_list));
  }
}

void addHole(struct qf_list *qfl, struct hole *h) {
  qfl->holes[qfl->hole_count++] = h;
}

int main(int argc, char *argv[]) {

  return 0;
}