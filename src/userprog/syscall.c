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
//  printf ("system call (%d)!\n",syscall_num);
  if (syscall_num == SYS_EXIT )
  {	/* Read the exit code */
	  sp = (f->esp + 4);

	  cur->exit_code = *sp;
	  thread_exit ();
  }

  if (syscall_num == SYS_WRITE )
  {
	int fd;
	char * buffer;
	unsigned size;

	sp = (f->esp + 4);
	fd = *sp;
        sp = (f->esp + 8);
        buffer = *sp;
	sp = (f->esp + 12);
	size = *sp;
	//printf("fd %d size %d buf %x\n", fd, size, buffer);
	if(fd == 1)
	{
          putbuf(buffer, size);
	}
  }	  
}
