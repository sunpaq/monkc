#include "MCContext.h"
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <sys/select.h>

/*
<< File I/O (Unbuffered I/O) >>: invoke a system call in kernel

create() will create a file for "write-only", 
so it is better to use open() with O_CREAT option

O_RDONLY
O_WRONLY | O_TRUNC //truncate the file(have write permission) length to 0
O_RDWR | O_TRUNC
O_APPEND
O_CREAT | O_EXCL //use together to create lock file! it is atomic operation

O_NOCTTY //(for terminal device path) do not allocate the device as the controlling terminal for this process
O_NONBLOCK //(for a FIFO, a block special file, or a character special file) nonblocking mode

O_DSYNC //sync write with device, but not sync file attribute (size, last-mod-date, ...) <fast>
O_RSYNC	//sync read with write
O_SYNC  //sync write with device, and include the file attributes <slow>

(Mac os) mac have no O_SYNC instead they use O_FSYNC and do not support O_DSYNC, O_RSYNC
(Linux) linux support the 3 flags, but all works the same as O_SYNC

_POSIX_NO_TRUNC
PATH_MAX
NAME_MAX
errno = ENAMETOOLONG

int open(const char *pathname, int oflag, ... ); //return value is guaranteed to be the lowest-numbered unused descriptor

SEEK_SET [0 	  +  offset]
SEEK_CUR [current +- offset]
SEEK_END [end     +- offset]

the off_t length is diff between platforms
sysconf
getconf

#define _FILE_OFFSET_BITS 32
#define _FILE_OFFSET_BITS 64

off_t lseek(int filedes, off_t offset, int whence); //whence means where, lseek-"l" means off_t is long int
                                                    //return -1 if error

STDIN_FILENO
STDOUT_FILENO

//the actual size readed (ssize_t) may less than required (size_t)
ssize_t read(int filedes, void *buf, size_t nbytes); //return 0 End of file
                                                     //return -1 if error

ssize_t write(int filedes, const void *buf, size_t nbytes); //return -1 if error

int close(int filedes); //return 0: OK -1: Error
*/

#ifndef _MCFile
#define _MCFile _MCObject;\
	int fd;\
	char* pathname;\
	void* buffer;\

class(MCFile);
method(MCFile, open, int oflag); returns(int)
method(MCFile, lseek, off_t offset, int whence); returns(off_t)
method(MCFile, read, size_t nbytes);
method(MCFile, write, void* buf, size_t nbytes);
method(MCFile, bye, xxx);

#endif



/*

<< Standard Buffered I/O >>



<< Advanced I/O >>

//int  pselect(int, fd_set *restrict, fd_set *restrict, fd_set *restrict,
//         const struct timespec *restrict, const sigset_t *restrict);
//int  select(int, fd_set *restrict, fd_set *restrict, fd_set *restrict,
//         struct timeval *restrict);

//FD_ZERO()
//FD_SET()
//FD_CLR()
//FD_ISSET()

*/
typedef enum _MCSelect_fd_type{
	MCSelect_Readfd,
	MCSelect_Writefd,
	MCSelect_Exceptionfd,
}MCSelect_fd_type;

#ifndef _MCSelect
#define _MCSelect _MCObject;\
	int maxfd;\
	fd_set readfd_set;\
	fd_set writefd_set;\
	fd_set exceptionfd_set;\
	fd_set readfd_result_set;\
	fd_set writefd_result_set;\
	fd_set exceptionfd_result_set;\
	struct timeval timeout;\

class(MCSelect);
method(MCSelect, waitForFdsetChange, xxx); returns(int: >0 success =0 timeout <0 error)
method(MCSelect, addFd, MCSelect_fd_type type, int fd);
method(MCSelect, removeFd, MCSelect_fd_type type, int fd);
method(MCSelect, isFdReady, MCSelect_fd_type type, int fd); returns(BOOL)
constructor(MCSelect, long second, long microsecond);

#endif

//MCPSelect ?