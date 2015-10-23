[...]

/* ## start tweak ## */
#include <unistd.h>

PRIVATE int get_nr_of_running_processes(void) {
  struct kinfo kinfo;
  getsysinfo(PM_PROC_NR, SI_KINFO, &kinfo);
  printf("## kinfo.nr_procs = %d\n", kinfo.nr_procs);
  return kinfo.nr_procs;
}

PRIVATE int get_quantum_size(void) {
  int current_number_of_processes, dynamic_quanta_size;
  
  current_number_of_processes = get_nr_of_running_processes();

  /* few processes running */
  if (current_number_of_processes < 5) {
    dynamic_quanta_size = 2;
  }
  /* medium number of processes */
  else if (current_number_of_processes >= 5 && current_number_of_processes < 20) {
    dynamic_quanta_size = 8;
  }
  /* many processes running */
  else {
    dynamic_quanta_size = 16;
  }
  printf("## dynamic_quanta_size should be %d based on current_number_of_processes = %d\n", dynamic_quanta_size, current_number_of_processes);
  return dynamic_quanta_size;
}

/*==================================================================*
 *				do_fork                             *
 *==================================================================*/
PUBLIC int do_fork(message *msg)
{
  int r, proc, s, childproc, fullvm, quantum_size;
  struct vmproc *vmp, *vmc;

  [...]

  quantum_size = get_quantum_size();
  
  /* The child is basically a copy of the parent. */
  origpt = vmc->vm_pt;
  *vmc = *vmp;
  vmc->vm_slot = childproc;
  vmc->vm_regions = NULL;
  vmc->vm_endpoint = NONE;	/* In case someone tries to use it. */
  vmc->vm_pt = origpt;
  vmc->vm_flags &= ~VMF_HASPT;
  /* probably set a field in vmc to quantum_size,
   * instead of just copying it from the parent (init) */

/* ## end tweak ## */
  
  [...]

  SANITYCHECK(SCL_FUNCTIONS);
  return OK;
}

