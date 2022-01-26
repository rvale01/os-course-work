#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);
void halt (void);
void exit (int status);
int exec (const char *cmd_line);
int open (const char *file);
int filesize (int fd);
int read (int fd, void *buffer, unsigned size);
int write (int fd, const void *buffer, unsigned size);
void close (int fd);
void seek (int fd, unsigned position);
unsigned tell (int fd);



#endif /* userprog/syscall.h */
