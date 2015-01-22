#include "MCContext.h"
#include "MCBuffer.h"
#include "MCString.h"

#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <utime.h>
#include <time.h>
#include <dirent.h>
#include <ftw.h>
#include <errno.h>

/* MCFile */

#ifndef MCFile_
#define MCFile_

monkc(MCFile);
	int fd;
	char* pathname;
	void* buffer;
	struct stat attribute;
end(MCFile);
/*
O_RDONLY
O_WRONLY | O_TRUNC //truncate the file(have write permission) length to 0
O_RDWR | O_TRUNC
O_APPEND
O_CREAT | O_EXCL //use together to create lock file! it is atomic operation
*/
method(MCFile, MCFile*, initWithPathName, char* pathname, int oflag);

method(MCFile, size_t, readFromBegin, off_t offset, size_t nbytes);
method(MCFile, size_t, readAtLastPosition, off_t offset, size_t nbytes);
method(MCFile, size_t, readFromEnd, off_t offset, size_t nbytes);
method(MCFile, size_t, writeToBegin, off_t offset, void* buf, size_t nbytes);
method(MCFile, size_t, writeToLastTime, off_t offset, void* buf, size_t nbytes);
method(MCFile, size_t, writeToEnd, off_t offset, void* buf, size_t nbytes);

method(MCFile, int, duplicateFd, xxx);
method(MCFile, int, duplicateFdTo, int fd);
method(MCFile, void, printAttribute, xxx);
method(MCFile, void, bye, xxx);
method(MCFile, int, checkPermissionUseRealIDOfProcess, int mode);
/*
R_OK
W_OK
X_OK
F_OK ---> if file exist
*/
int MCFile_isFileExit(char* pathname);
int MCFile_chmod(char* pathname, mode_t mode);
int MFFile_truncateFileTo(char* pathname, off_t length);
mode_t MCFile_setNewFilePermissionMask4Process(mode_t cmask);
void MCFile_flushAllCacheToDisk();
int MCFile_flushAFileCacheToDisk(int fd);
int MCFile_createSymbolLink(char* pathname, char* linkname);
int MCFile_createDirectory(char* pathname);
int MCFile_removeDirectory(char* pathname);

int MCProcess_changeCurrentWorkingDir(char* pathname);
int MCProcess_changeCurrentWorkingDirByFd(int fd);
char* MCProcess_getCurrentWorkingDir(MCCharBuffer* buff);

MCFile* MCFile_newReadOnly(char* pathname);
MCFile* MCFile_newWriteOnly(char* pathname, int isClear);
MCFile* MCFile_newReadWrite(char* pathname, int isClear);

#endif

/* MCStream */

typedef enum _MCStreamType{
	readonly_fullbuffered,
	readwrite_fullbuffered,
	readonly_linebuffered,
	readwrite_linebuffered
}MCStreamType;
//default is a wide-char fully-buffered stream
#ifndef MCStream_
#define MCStream_

monkc(MCStream);
	FILE* fileObject;
end(MCStream);

method(MCStream, MCStream*, newWithPath, MCStreamType type, char* path);
method(MCStream, void, bye, xxx);
method(MCStream, int, getFileDescriptor, xxx);

method(MCStream, int, getChar, xxx);
method(MCStream, int, putChar, int charCode);
method(MCStream, int, pushbackChar, int charCodeToBePushBack);

method(MCStream, char*, getCString, MCCharBuffer* recvBuffer);
method(MCStream, char*, putCString, MCCharBuffer* sendBuffer);
method(MCStream, MCString*, getMCString, xxx);
method(MCStream, int, putMCString, MCString* str);

method(MCStream, size_t, getBianryObject, void* recvBuffer,  size_t objectSize, size_t numberOfObjs);
method(MCStream, size_t, putBianryObject, void* sendBuffer,  size_t objectSize, size_t numberOfObjs);

method(MCStream, off_t, tellOffset, xxx);
method(MCStream, int, seekFromBegin, off_t offset);
method(MCStream, int, seekFromCurrent, off_t offset);
method(MCStream, int, seekFromEnd, off_t offset);

#endif

/* MCByteStream */

#ifndef MCByteStream_
#define MCByteStream_

monkc(MCByteStream) extends(MCStream);
end(MCByteStream);

method(MCByteStream, void, bye, xxx);
method(MCByteStream, MCByteStream*, newWithPath, MCStreamType type, char* path);
#endif

/* MCStdinStream */

#ifndef MCStdinStream_
#define MCStdinStream_

monkc(MCStdinStream) extends(MCStream);
end(MCStdinStream);

method(MCStdinStream, void, bye, xxx);
#endif

/* MCStdoutStream */

#ifndef MCStdoutStream_
#define MCStdoutStream_

monkc(MCStdoutStream) extends(MCStream);
end(MCStdoutStream);

method(MCStdoutStream, void, bye, xxx);
#endif

/* MCStderrStream */

#ifndef MCStdoutStream_
#define MCStdoutStream_

monkc(MCStdoutStream) extends(MCStream);
end(MCStdoutStream);

method(MCStdoutStream, void, bye, xxx);
#endif

#ifndef MCStderrStream_
#define MCStderrStream_

monkc(MCStderrStream) extends(MCStream);
end(MCStderrStream);

method(MCStderrStream, void, bye, xxx);
#endif

/* MCSelect */

typedef enum _MCSelect_fd_type{
	MCSelect_Readfd,
	MCSelect_Writefd,
	MCSelect_Exceptionfd,
}MCSelect_fd_type;

#ifndef MCSelect_
#define MCSelect_ 

monkc(MCSelect);
	int maxfd;
	fd_set readfd_set;
	fd_set writefd_set;
	fd_set exceptionfd_set;
	fd_set readfd_result_set;
	fd_set writefd_result_set;
	fd_set exceptionfd_result_set;
	struct timeval timeout;
end(MCSelect);

method(MCSelect, void, initWithSecondAndMicrosec, long second, long microsecond);
method(MCSelect, int, waitForFdsetChange, xxx);
method(MCSelect, void, addFd, MCSelect_fd_type type, int fd);
method(MCSelect, void, removeFd, MCSelect_fd_type type, int fd);
method(MCSelect, int, isFdReady, MCSelect_fd_type type, int fd);

#endif


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

int stat(const char *restrict pathname, struct stat *restrict buf);	//for file path
int fstat(int filedes, struct stat *buf);                          	//for file descriptor
int lstat(const char *restrict pathname, struct stat *restrict buf);//for symbolic link

struct stat {
	mode_t st_mode; 		//file type & mode (permissions)
	ino_t st_ino; 			//i-node number (serial number)
	dev_t st_dev; 			//device number (file system)
	dev_t st_rdev; 			//device number for special files
	nlink_t st_nlink; 		//number of links
	uid_t st_uid; 			//user ID of owner
	gid_t st_gid; 			//group ID of owner
	off_t st_size; 			//size in bytes, for regular files
	time_t st_atime; 		//time of last access
	time_t st_mtime; 		//time of last modification
	time_t st_ctime; 		//time of last file status change
	blksize_t st_blksize; 	//best I/O block size
	blkcnt_t st_blocks;  	//number of disk blocks allocated
};

//types of file:
1. Regular file               ---> S_ISREG(file_stat.st_mode)
2. Directory file             ---> S_ISDIR(file_stat.st_mode)
3. Block Special File         ---> S_ISCHR(file_stat.st_mode)
4. Character Special File     ---> S_ISBLK(file_stat.st_mode)
5. FIFO(named pipe)           ---> S_ISFIFO(file_stat.st_mode)
6. Socket                     ---> S_ISLNK(file_stat.st_mode)
7. Symbolic Link              ---> S_ISSOCK(file_stat.st_mode)

//add by POSIX.1 they use struct stat as parameter(linux not implemented)
8. Message Queue              ---> S_TYPEISMQ(file_stat)
9. Semaphore                  ---> S_TYPEISSEM(file_stat)
10.Shared Memory Object       ---> S_TYPEISSHM(file_stat)

//if the owner of the file is the superuser and if the file's set-user-ID bit is set, then while that
program file is running as a process, it has superuser privileges.
S_ISUID() //st_uid
S_ISGID() //st_gid

//st_mode value also encodes the access permission bits for the file.
S_IRUSR //user read
S_IWUSR //user write
S_IXUSR //user execute

S_IRGRP //group read
S_IWGRP //group write
S_IXGRP //group execute

S_IROTH //other read
S_IWOTH //other write
S_IXOTH //other execute

//for process:
real user ID
effective user ID
saved user ID

//sequence for access permission check by kernel:
if(process.effective_uid==0)
	candoAnything();
if(process.effective_uid==file.owner_id) //process owned the file
	if(S_IRUSR(file.st_mode))
		canRead();
	if(S_IWUSR(file.st_mode))
		canWrite();
	if(S_IXUSR(file.st_mode))
		canExecute();
if(process.effective_gid==file.group_id)
	if(S_IRGRP(file.st_mode))
		canRead();
	if(S_IWGRP(file.st_mode))
		canWrite();
	if(S_IXGRP(file.st_mode))
		canExecute();
else
	if(S_IROTH(file.st_mode))
		canRead();
	if(S_IWOTH(file.st_mode))
		canWrite();
	if(S_IXOTH(file.st_mode))
		canExecute();

@The user ID of a new file is set to the effective user ID of the process.
@The group ID of a new file is different between OSs

//permission check use real ID instead of effective ID:
R_OK
W_OK
X_OK
F_OK ---> if file exist
int access(const char *pathname, int mode);//0 Ok -1 ERROR

//default permissions for new files of a process:
mode_t umask(mode_t cmask);
//example: umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
//shell-command: umask
				 > 0002
				 umask -S
				 > u=rwx,g=rwx,o=rx

//change the file access permissions for an existing file.

<S_IRWXU read, write, and execute by user (owner)>
<S_IRWXG read, write, and execute by group>
<S_IRWXO read, write, and execute by other (world)>

S_ISUID set-user-ID on execution
S_ISGID set-group-ID on execution
S_ISVTX saved-text (sticky bit)

S_IRUSR read by user (owner)
S_IWUSR write by user (owner)
S_IXUSR execute by user (owner)

S_IRGRP read by group
S_IWGRP write by group
S_IXGRP execute by group

S_IROTH read by other (world)
S_IWOTH write by other (world)
S_IXOTH execute by other (world)

int chmod(const char *pathname, mode_t mode);
int fchmod(int filedes, mode_t mode);

//change the file owner. on many systems only the superuser can change the file owner
int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int filedes, uid_t owner, gid_t group);
int lchown(const char *pathname, uid_t owner, gid_t group);

-rw-rwSrw- 1 sar
//Note that the ls command lists the group-execute permission as S to
//signify that the set-group-ID bit is set without the group-execute bit being set.

//truncate file
int truncate(const char *pathname, off_t length);
int ftruncate(int filedes, off_t length);

//Hard links (point to the i-node, Only the superuser can create a hard link to a directory)
int link(const char *existingpath, const char *newpath);
//This function creates a new directory entry, newpath, 
//that references the existing file existingpath.
int unlink(const char *pathname);
//This function removes the directory entry and decrements the link count of the file referenced by pathname.

//ISO C functions
int remove(const char *pathname);
int rename(const char *oldname, const char *newname);

//Symbolic Link
int symlink(const char *actualpath, const char *sympath);
ssize_t readlink(const char* restrict pathname, char *restrict buf, size_t bufsize);
//Because the open function follows a symbolic link, we need a way to open the link itself 
//and read the name in the link. This function combines the actions of open, read, and close.

//change time
int utime(const char *pathname, const struct utimbuf *times);
struct utimbuf {
	time_t actime; // access time
	time_t modtime; // modification time
}

//dirs
int mkdir(const char *pathname, mode_t mode);
//normally want at least one of the execute bits enabled, 
//to allow access to filenames within the directory.
int rmdir(const char *pathname);

//POSIX
DIR *opendir(const char *pathname);
struct dirent *readdir(DIR *dp);
struct dirent {
	ino_t d_ino; // i-node number
	char d_name[NAME_MAX + 1]; // null-terminated filename
}
void rewinddir(DIR *dp);
int closedir(DIR *dp);
//XSI
long telldir(DIR *dp);
void seekdir(DIR *dp, long loc);

//File tree walk (ftw, nftw)
int ftw(const char *dirpath,
        int (*fn) (const char *fpath, const struct stat *sb, int typeflag),
        int nopenfd);

//pwd: process working directory (Every process has a current working directory.)
int chdir(const char *pathname);
int fchdir(int filedes);
char *getcwd(char *buf, size_t size);

*/

/*
<<  Standard I/O Library  >> (Buffered I/O)


concept: 
1. Streams(in memory)
2. FILE Object
3. sigle-byte/multi-byte("wide") char
4. orientation: byte-oriented/wide oriented

check and change orientation:
#include <stdio.h>
#include <wchar.h>
int fwide(FILE *fp, int mode);
· If the mode argument is negative, fwide will try to make the specified stream byte-oriented.
· If the mode argument is positive, fwide will try to make the specified stream wide-oriented.
· If the mode argument is zero, fwide will not try to set the orientation, 
but will still return a value identifying the stream's orientation.

FILE* stdin  --->  fd = STDIN_FILENO
FILE* stdout --->  fd = STDOUT_FILENO
FILE* stderr --->  fd = STDERR_FILENO

Buffering:
1. Fully buffered: the whole file will be buffered in memory automatically.
2. Line buffered: buffer a line a char until /n. usually use for terminal.
3. Unbuffered: the same as write. usually use for standard error.

default:
1. standard error is unbuffered
2. streams open to terminal devices are line buffered
3. and all other streams are fully buffered.

change buffering:
void setbuf(FILE *restrict fp, char *restrict buf);
int setvbuf(FILE *restrict fp, char *restrict buf, int mode, size_t size);
[NULL _IOFBF/_IOLBF/_IONBF BUFSIZ]

flush:
int fflush(FILE *fp);
[NULL: it will flush all output stream buffer]

open a stream:
FILE *fopen(const char *restrict pathname, const char *restrict type);
FILE *freopen(const char *restrict pathname, const char *restrict type, FILE *restrict fp);
FILE *fdopen(int filedes, const char *type);
type:
r/w/a/ & b & +

close a stream:
int fclose(FILE *fp);

input/output functions:
int getc(FILE *fp);  //may be a macro implement, so do not fill *fp a expression
int fgetc(FILE *fp); //guaranteed to be a function. not macro, but function is slower than macro
int getchar(void);   //equal getc(stdin)
int putc(int c, FILE *fp);
int fputc(int c, FILE *fp);
int putchar(int c);

error check:
int ferror(FILE *fp);
int feof(FILE *fp);
void clearerr(FILE *fp);

pushback char / peek char:
int ungetc(int c, FILE *fp); //they don't get written back to the underlying file or device. 
//They are kept incore in the standard I/O library's buffer for the stream.

line I/O:
char *fgets(char *restrict buf, int n, FILE *restrict fp);
int fputs(const char *restrict str, FILE *restrict fp);
//never use the gets and puts to avoid buffer overflow and other bugs

binary I/O:
size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
//we need binary I/O functions because line-at-a-time functions will stop at a null/newline
//!!! the two function can not cross platform. binary file write on one system can not be read on the other

seek file:
1. long integer as offset
long ftell(FILE *fp);
int fseek(FILE *fp, long offset, int whence); //SEEK_SET/SEEK_CUR/SEEK_END
void rewind(FILE *fp); //set position to begin of the file

2. Single UNIX Specification: off_t as offset
off_t ftello(FILE *fp);
int fseeko(FILE *fp, off_t offset, int whence);

3. ISO C standard: fpos_t as offset
int fgetpos(FILE *restrict fp, fpos_t *restrict pos);
int fsetpos(FILE *fp, const fpos_t *pos);

4. Formatted I/O:
int   printf(const char *restrict format, ...); //write to standard I/O
int  fprintf(FILE *restrict fp, const char *restrict format, ...);  //write to FILE
int  sprintf(char *restrict buf, const char *restrict format, ...); //write to buffer, can overflow the buffer
int snprintf(char *restrict buf, size_t n, const char *restrict format, ...);//deal with buffer overflow

#include <stdarg.h>
int   vprintf(const char *restrict format, va_list arg);
int  vfprintf(FILE *restrict fp, const char *restrict format, va_list arg);
int  vsprintf(char *restrict buf, const char *restrict format, va_list arg);
int vsnprintf(char *restrict buf, size_t n, const char *restrict format, va_list arg);

int  scanf(const char *restrict format, ...);
int fscanf(FILE *restrict fp, const char *restrict format, ...);
int sscanf(const char *restrict buf, const char *restrict format, ...);

5. get file descriptor
int fileno(FILE *fp);

6. create tmp file 
(ISO C standard)
char *tmpnam(char *ptr);
FILE *tmpfile(void);

(Single UNIX Specification)
char *tempnam(const char *directory, const char *prefix);
int mkstemp(char *template);

7. alternative
fio, sfio
ASI
uClibc
newlibc
*/

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