
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

#define NIL_HOLE (struct hole *) 0

PRIVATE struct quick_fit_list {
  int hole_count;
  struct hole *holes[NO_HOLES]; /* use _NR_HOLES */
};

PRIVATE struct quick_fit_list *quick_fit_table[NO_LISTS];

PRIVATE struct hole hole[_NR_HOLES];
PRIVATE struct hole *hole_head; /* pointer to first hole */
phys_clicks old_base;

PRIVATE void init_quick_fit_table() {
  register struct hole *hp, *prev_ptr;
  int i;

  /* allocate memory to each list in the table, initially there are 0 holes in each list */
  for (i = 0; i < NO_LISTS; i++) {
    quick_fit_table[i] = malloc(sizeof(struct quick_fit_list));
    quick_fit_table[i]->hole_count = 0;
  }

  /* assign each hole in holes to it's appropriate quick_fit_list */
  prev_ptr = NIL_HOLE;
  hp = hole_head;
  while (hp != NIL_HOLE) {
    assign_hole_to_list(hp);
    CHECKHOLES;

    prev_ptr = hp;
    hp = hp->h_next;
  }
}

PRIVATE void assign_hole_to_list(struct hole *h) {
  if (h->h_len >= 32) {
    /* h_len/4 will exceed NO_LISTS, so assign to last list, the one that contains holes of size 28-> */
    add_hole_to_list(quick_fit_table[NO_LISTS-1], h);
  }
  else {
    /* assign to list at index (h_len/4) in quick_fit_table */
    add_hole_to_list(quick_fit_table[(h->h_len) / 4], h);
  }
}

PRIVATE void add_hole_to_list(struct quick_fit_list *qfl, struct hole *h) {
  /* add given hole to next free place in given quick_fit_list and increase the hole_count of that list */
  qfl->holes[qfl->hole_count++] = h;
}

PRIVATE phys_clicks pop_hole_from_list(struct quick_fit_list *qfl) {
  /* make a copy of the h_base, so we can return it later */
  phys_clicks old_base = qfl->holes[qfl->hole_count-1]->h_base;

  /* free the memory the hole took up in the list and decrement the list's hole_count */
  free(qfl->holes[qfl->hole_count-1]);
  qfl->hole_count--;

  return old_base;
}

PRIVATE void quick_fit_alloc(phys_clicks clicks) {
  if (clicks >= 32) {
    /* 32/4 will exceed NO_LISTS, so use hole from last list, the one that contains holes of size 28-> */
    mem = pop_hole_from_list(quick_fit_table[NO_LISTS-1]);
  }
  else {
    /* use hole from list at index (clicks/4) in quick_fit_table */
    mem = pop_hole_from_list(quick_fit_table[(h->h_len) / 4]);
  }
}

int main(int argc, char *argv[]) {
  phys_clicks clicks = 10;
  quick_fit_alloc(clicks);
  return 0;
}