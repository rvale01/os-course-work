#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}


static void
syscall_handler (struct intr_frame *f UNUSED)
{
  struct thread *cur = thread_current ();
  int syscall_num;
  int *sp = f->esp;
  
 
  syscall_num = *sp;
  printf ("system call (%d)!\n",syscall_num);
  if (syscall_num == SYS_EXIT )
  {	/* Read the exit code */
	  sp = (f->esp + 4);

	  cur->exit_code = *sp;
	  thread_exit ();
  }
}
