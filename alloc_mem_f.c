PUBLIC phys_clicks alloc_mem_f(phys_clicks clicks, u32_t memflags)
{
/* Allocate a block of memory from the free list using first fit. The block
 * consists of a sequence of contiguous bytes, whose length in clicks is
 * given by 'clicks'.  A pointer to the block is returned.  The block is
 * always on a click boundary.  This procedure is called when memory is
 * needed for FORK or EXEC.
 */
  register struct hole *hp, *prev_ptr;
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
        prev_ptr = NIL_HOLE;
  hp = hole_head;
  while (hp != NIL_HOLE) {
    if (hp->h_len >= clicks) {
      /* We found a hole that is big enough.  Use it. */
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