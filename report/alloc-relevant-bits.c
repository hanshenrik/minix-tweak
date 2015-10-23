[...]

/* ## start tweak ## */
#define _NR_LISTS 4
PRIVATE struct quick_fit_list {
  struct hole *holes[_NR_HOLES];
  int hole_count;
};

PRIVATE struct quick_fit_list *quick_fit_table[_NR_LISTS];
PRIVATE int alloc_algorithm = 0; /* 0 = First fit, 1 = Best fit, 2 = Quick fit */
/* ## end tweak ## */

[...]

/*==================================================================*
 *				alloc_mem_f		            *
 *==================================================================*/
PUBLIC phys_clicks alloc_mem_f(phys_clicks clicks, u32_t memflags)
{
/* ## start tweak ## */
/* Allocate a block of memory from the free list using (0) first, (1)
 * best or (2) quick fit, based on value of alloc_algorithm (0, 1 or
 * 2). The block consists of a sequence of contiguous bytes, whose
 * length in clicks is given by 'clicks'.  A pointer to the block is
 * returned.  The block is always on a click boundary.  This
 * procedure is called when memory is needed for FORK or EXEC.
 */
  register struct hole *hp, *prev_ptr, *candidate_hole;
  phys_clicks old_base, mem = NO_MEM, align_clicks = 0;
  int s;

  if(memflags & PAF_ALIGN64K) {
  	align_clicks = (64 * 1024) / CLICK_SIZE;
    clicks += align_clicks;
  }

  if(vm_paged) {
  	vm_assert(CLICK_SIZE == VM_PAGE_SIZE);
  	mem = alloc_pages(clicks, memflags);
  } else {
    CHECKHOLES;

    switch(alloc_algorithm) {
      default:
      case(0): /* First fit */
        prev_ptr = NIL_HOLE;
        hp = hole_head;
        while (hp != NIL_HOLE) {
          if (hp->h_len >= clicks) { /* We found a hole that is big enough. Use it. */
            old_base = hp->h_base;  /* remember where it started */
            hp->h_base += clicks; /* bite a piece off */
            hp->h_len -= clicks;  /* ditto */

            /* Delete the hole if used up completely. */
            if (hp->h_len == 0) del_slot(prev_ptr, hp);

            /* Anything special needs to happen? */
            if(memflags & PAF_CLEAR) {
              if ((s= sys_memset(0, CLICK_SIZE*old_base,
              CLICK_SIZE*clicks)) != OK)   {
              vm_panic("alloc_mem: sys_memset failed", s);
              }
            }

            /* Return the start address of the acquired block. */
            CHECKHOLES;
            mem = old_base;
            break;
          }

          prev_ptr = hp;
          hp = hp->h_next;
        }
        break;
      case(1): /* Best fit */
        candidate_hole = hp;
        prev_ptr = hp;
        hp = hp->h_next;
        while (hp != NIL_HOLE) {
          if (hp->h_len >= clicks && hp->h_len < candidate_hole->h_len) {
            candidate_hole = hp;
          }

          prev_ptr = hp;
          hp = hp->h_next;
        }
        /* we've gone through the whole list, candidate_hole is now the smallest big enough hole */
        old_base = candidate_hole->h_base;  /* remember where it started */
        candidate_hole->h_base += clicks; /* bite a piece off */
        candidate_hole->h_len -= clicks;  /* ditto */
        
        /* Delete the hole if used up completely. */
        if (candidate_hole->h_len == 0) del_slot(prev_ptr, candidate_hole);

        /* Anything special needs to happen? */
        if(memflags & PAF_CLEAR) {
          if ((s= sys_memset(0, CLICK_SIZE*old_base,
          CLICK_SIZE*clicks)) != OK)   {
          vm_panic("alloc_mem: sys_memset failed", s);
          }
        }

        /* Return the start address of the acquired block. */
        CHECKHOLES;
        mem = old_base;
        
        break;
      case(2): /* Quick fit */
        if (clicks >= 32) {
          /* 32/8 will exceed _NR_LISTS, so use hole from last list, the one that contains holes of sizes 32KB-> */
          mem = pop_hole_from_list(quick_fit_table[_NR_LISTS-1]);
        }
        else {
          /* use hole from list at index (clicks/8) in quick_fit_table */
          mem = pop_hole_from_list(quick_fit_table[(clicks/8)]);
        }
        break;
    }
    /* ## end tweak ## */
  }

  if(mem == NO_MEM)
  	return mem;

CHECKHOLES;

  if(align_clicks) {
  	phys_clicks o;
  	o = mem % align_clicks;
  	if(o > 0) {
  		phys_clicks e;
  		e = align_clicks - o;
	  	FREE_MEM(mem, e);
	  	mem += e;
	}
  }
CHECKHOLES;

  return mem;
}


/* ## start tweak ## */

/*==================================================================*
*        pop_hole_from_list                                         *
/*==================================================================*/
PRIVATE phys_clicks pop_hole_from_list(struct quick_fit_list *qfl) {
  /* make a copy of the h_base, so we can return it later */
  phys_clicks old_base = qfl->holes[qfl->hole_count-1]->h_base;

  /* free the memory the hole took up in the list and decrement the list's hole_count */
  free(qfl->holes[qfl->hole_count-1]);
  qfl->hole_count--;

  return old_base;
}

/*==================================================================*
 *        init_quick_fit_table                                      *
/*==================================================================*/
 /*
 * Using 4 lists, assuming h_len is represented as KB
 * 0: 0-8KB
 * 1: 8-16KB
 * 2: 16-32KB
 * 3: 32KB->
 */
PRIVATE void init_quick_fit_table(void) {
  register struct hole *hp, *prev_ptr;
  int i;

  /* allocate memory to each list in the table, initially there are 0 holes in each list */
  for (i = 0; i < _NR_LISTS; i++) {
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

/*==================================================================*
*        assign_hole_to_list                                        *
/*==================================================================*/
PRIVATE void assign_hole_to_list(struct hole *h) {
  if (h->h_len >= 32) {
    /* h_len/8 will exceed _NR_LISTS, so assign to last list, the one that contains holes of size 32KB-> */
    add_hole_to_list(quick_fit_table[_NR_LISTS-1], h);
  }
  else {
    /* assign to list at index (h_len/8) in quick_fit_table */
    add_hole_to_list(quick_fit_table[(h->h_len) / 8], h);
  }
}

/*==================================================================*
*        add_hole_to_list                                           *
/*==================================================================*/
PRIVATE void add_hole_to_list(struct quick_fit_list *qfl, struct hole *h) {
  /* add given hole to next free place in given quick_fit_list and increase the hole_count of that list */
  qfl->holes[qfl->hole_count++] = h;
}

/* ## end tweak ## */

[...]

/*==================================================================*
 *				mem_init                            *
/*==================================================================*/
PUBLIC void mem_init(chunks)
struct memory *chunks;		/* list of free memory chunks */
{
  [...]

  /* ## start tweak ## */
  init_quick_fit_table();
  /* ## end tweak ## */
}

[...]
