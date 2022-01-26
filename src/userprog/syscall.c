#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include <userprog/process.h>
#include <filesys/file.h> 
#include <filesys/filesys.h>
#define ARG_1 4
#define ARG_2 8
#define ARG_3 12
#define ERROR -1



static void syscall_handler (struct intr_frame *);
static int handle_write(int fd, const void * buffer, unsigned int lenght);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

void syscall_exit(int);
int open (const char *file);
int read (int fd, void *buffer, unsigned size);
void halt(void);
bool create (const char *file, unsigned initial_size);
int filesize (int fd);
bool remove (const char *file);
int exec (const char *cmd_line);




static void
syscall_handler (struct intr_frame *f UNUSED)
{
  struct thread *cur = thread_current ();
  int syscall_num;
  int *sp = f->esp;
  check_address(*sp, f ->esp);
  int syscall_number = *((int*)f->esp);
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

  void syscall_handler (struct intr_frame *f){
	  int code = (int)load_stack(f, ARG_CODE);
	  

	  switch (code) {
		  case SYS_READ:
			  break;
                 	  }
		  case SYS_EXIT:
			  {
			  handle_exit((int)load_stack(f,ARG_1));
			  break;
			  }
	          case SYS_WRITE:
			  {
			  int result = handle_write(
			 (int)load_stack(f,ARG_1),
			 (void *)load_stack(f, ARG_2),
			 (unsigned int)load_Stack(f, ARG_3));
			  f->esp = result;
			  break;
			  }
		  case SYS_EXEC:
			  {
			  f->eax = exec((const char*) load_stack(f,ARG_1));
			  break;
			  }
		  case SYS_OPEN:
			  {
			  f->eax = open((const char *)load_stack(f,ARG_1]);
			  break;
			  }
		  case SYS_HAL:
			  {
			  halt();
			  break;
			  }
	          case SYS_CLOSE:
			  {
			  get_argument(esp,arg,1);
			  close(arg[0]);
			  break;
			  }
		  case  SYS_CREATE:
		  {
		  f->eax = create((const char*)load_stack(f,ARG_1), (unsigned)load_stack(f,ARG_2));
		  break;
		  }
 }

}
 


void halt(void)
{
	shutdown_power_off():
}

int open(const char *file)
{
	int fd;
	struct file *new_file;
	new_file=filesys_open(file);

	if(new_file != NULL)
	{
		fd = process_add_file(new_file;
				return fd;
	}
	else
	{
	                        return -1;
	}


 }   

void
close(int fd)
{
       struct file *current_file;
       current_file = process_get_file(fd);
       if(current_file != NULL)
       {
              file_close(current_file);
	      thread_current()->file_descriptor[fd]=NULL;
       }

void syscall_exit(int status)
{
	struct thread *cur = thread_current();
	cur ->exit_status =status;
	thread_exit();
}
bool create (const char *file, unsigned initial_size)
{
	lock_acquire(&my_lock);
	bool success = filesys_create(file, initial_size);
	lock_release(&my_lock);
	return success:
}


int read (int fd, void*buffer, unssigned size)
{
	return 0;
}

bool remove (const char *file)
{
	lock_acquire(&my_lock);
	bool success = filesys_remove(file);
	lock_release(&my_lock);
	return success;
}

int exec (const char *cmd_line)
{
	int id = process_execute(cmd_line);
	return id;
}


}
