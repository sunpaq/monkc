#include "MCContext.h"
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/stat.h>

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

(Mac OS) mac have no O_SYNC instead they use O_FSYNC and do not support O_DSYNC, O_RSYNC
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

//atomic extention: make lseek and read one atomic operation
ssize_t pread(int filedes, void *buf, size_t nbytes, off_t offset);
ssize_t pwrite(int filedes, const void *buf, size_t nbytes, off_t offset);

int dup(int filedes);
int dup2(int filedes, int filedes2);// "dup-to"

//flush cache in kernel to disk
void sync(void);
int fsync(int filedes);
int fdatasync(int filedes);

cmd:
F_DUPFD                  //Duplicate an existing descriptor
F_GETFD F_SETFD          //Get/set file descriptor flags -> FD_CLOEXEC
F_GETFL F_SETFL          //Get/set file status flags 
                         (O_RDONLY/O_WRONLY/O_RDWR/O_APPEND/O_NONBLOCK/O_SYNC/O_DSYNC/O_RSYNC/O_FSYNC/O_ASYNC)
F_GETOWN F_SETOWN        //Get/set asynchronous I/O ownership
						 (Get the process ID or process group ID currently receiving the SIGIO and SIGURG signals.)
F_GETLK F_SETLK F_SETLKW //Get/set record locks (APUE14.3)

int fcntl(int filedes, int cmd, ... );//fcntl is useful when we only know the file descriptor or want to modify the descriptor flags

//Each device driver can define its own set of ioctl commands
//OS provide generic ioctl commands:
DIOxxx <sys/disklabel.h> //disk labels
FIOxxx <sys/filio.h> //file I/O
MTIOxxx <sys/mtio.h> //mag tape I/O
SIOxxx <sys/sockio.h> //socket I/O
TIOxxx <sys/ttycom.h> //terminal I/O

int ioctl(int filedes, int request, ...);//Single UNIX Specification only as an extension for dealing with STREAMS devices

/dev/fd:
fd = open("/dev/fd/0", mode); == fd = dup(0); //mode is no-use 

int stat(const char *restrict pathname, struct stat *restrict buf);
int fstat(int filedes, struct stat *buf);
int lstat(const char *restrict pathname, struct stat *restrict buf);

*/

#ifndef _MCFile
#define _MCFile _MCObject;\
	int fd;\
	char* pathname;\
	void* buffer;\

class(MCFile);

method(MCFile, readFromBegin, off_t offset, size_t nbytes);
method(MCFile, readFromLastTime, off_t offset, size_t nbytes);
method(MCFile, readFromEnd, off_t offset, size_t nbytes);

method(MCFile, writeToBegin, off_t offset, void* buf, size_t nbytes);
method(MCFile, writeToLastTime, off_t offset, void* buf, size_t nbytes);
method(MCFile, writeToEnd, off_t offset, void* buf, size_t nbytes);

method(MCFile, duplicateFd, xxx); returns(int fd);
method(MCFile, duplicateFdTo, int fd); returns(int newfd);

method(MCFile, bye, xxx);
constructor(MCFile, char* pathname, size_t buffersize, int oflag);

BOOL MCFile_isFileExit(char* pathname);
MCFile* MCFile_newReadOnly(char* pathname, size_t buffersize);
MCFile* MCFile_newWriteOnly(char* pathname, size_t buffersize);
MCFile* MCFile_newReadWrite(char* pathname, size_t buffersize);

void MCFile_flushAllCacheToDisk();
int MCFile_flushAFileCacheToDisk(int fd); returns(int result);

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