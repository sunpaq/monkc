#include "MCIO.h"

/* MCFile */

method(MCFile, readFromBegin, off_t offset, size_t nbytes)
{
	//use pread/pwrite for atomic operation
	return pread(this->fd, this->buffer, nbytes, offset);
}

method(MCFile, readAtLastPosition, off_t offset, size_t nbytes)
{
	return pread(this->fd, this->buffer, nbytes, offset);
}

method(MCFile, readFromEnd, off_t offset, size_t nbytes)
{
	return pread(this->fd, this->buffer, nbytes, offset);
}

method(MCFile, writeToBegin, off_t offset, void* buf, size_t nbytes)
{
	return pwrite(this->fd, buf, nbytes, offset);
}

method(MCFile, writeToLastTime, off_t offset, void* buf, size_t nbytes)
{
	return pwrite(this->fd, buf, nbytes, offset);
}

method(MCFile, writeToEnd, off_t offset, void* buf, size_t nbytes)
{
	return pwrite(this->fd, buf, nbytes, offset);
}

method(MCFile, duplicateFd, xxx) returns(int fd)
{
	return dup(this->fd);
}

method(MCFile, duplicateFdTo, int fd) returns(int newfd)
{
	return dup2(this->fd, fd);
}

void MCFile_flushAllCacheToDisk()
{
	void sync(void);
}

int MCFile_flushAFileCacheToDisk(int fd)
{
	return fsync(fd);
}

method(MCFile, bye, xxx)
{
	//release this->buffer
	free(this->buffer);
	close(this->fd);
}

method(MCFile, printAttribute, xxx)
{
	printf("uid:%d gid:%d size:%d st_mode:%o lmtime:%s", 
		this->attribute.st_uid, 
		this->attribute.st_gid,
		this->attribute.st_size,
		this->attribute.st_mode,
		ctime(&this->attribute.st_mtime));
}

method(MCFile, checkPermissionUseRealIDOfProcess, int mode)
{
	int res;
	if ((res = access(this->pathname, mode)) != -1)
		return YES;
	return NO;
}

constructor(MCFile, char* pathname, int oflag)
{
	link_class(MCFile, MCObject, nil)
	{
		have_method(MCFile, readFromBegin);
		have_method(MCFile, readFromEnd);
		have_method(MCFile, readAtLastPosition);

		have_method(MCFile, writeToBegin);
		have_method(MCFile, writeToLastTime);
		have_method(MCFile, writeToEnd);

		have_method(MCFile, duplicateFd);
		have_method(MCFile, duplicateFdTo);
		have_method(MCFile, printAttribute);
		have_method(MCFile, bye);
		have_method(MCFile, checkPermissionUseRealIDOfProcess);
	}

	if((this->fd = open(pathname, oflag))==-1)
		return nil;
	this->pathname = pathname;
	if(fstat(this->fd, &this->attribute)<0)
		return nil;
	this->buffer = malloc(this->attribute.st_blksize*10);
	return this;
}

BOOL MCFile_isFileExist(char* pathname)
{
	//file exist test
	int res;
	if ((res = access(pathname, F_OK)) != -1)
		return YES;
	return NO;
}

BOOL MCFile_chmod(char* pathname, mode_t mode)
{
	int res;
	if ((res = chmod(pathname, mode))!= -1)
		return YES;
	return NO;
}

BOOL MFFile_truncateFileTo(char* pathname, off_t length)
{
	int res;
	if ((res = truncate(pathname, length))!= -1)
		return YES;
	return NO;
}

mode_t MCFile_setNewFilePermissionMask4Process(mode_t cmask)
{
	return umask(cmask);
}

MCFile* MCFile_newReadOnly(char* pathname)
{
	return new(MCFile, pathname, O_RDONLY|O_CREAT);
}

MCFile* MCFile_newWriteOnly(char* pathname, BOOL isClear)
{
	if(isClear)
		return new(MCFile, pathname, O_WRONLY|O_CREAT|O_TRUNC);
	else
		return new(MCFile, pathname, O_WRONLY|O_CREAT);
}

MCFile* MCFile_newReadWrite(char* pathname, BOOL isClear)
{
	if(isClear)
		return new(MCFile, pathname, O_RDWR|O_CREAT|O_TRUNC);
	else
		return new(MCFile, pathname, O_RDWR|O_CREAT);
}

BOOL MCFile_createSymbolLink(char* pathname, char* linkname)
{
	int res;
	if ((res = symlink(pathname, linkname))!= -1)
		return YES;
	return NO;
}

BOOL MCFile_createDirectory(char* pathname)
{
	int res;
	if ((res = mkdir(pathname, S_IRWXU))!= -1)
		return YES;
	return NO;
}

BOOL MCFile_removeDirectory(char* pathname)
{
	int res;
	if ((res = rmdir(pathname))!= -1)
		return YES;
	return NO;
}

BOOL MCProcess_changeCurrentWorkingDir(char* pathname)
{
	int res;
	if ((res = chdir(pathname))!= -1)
		return YES;
	return NO;
}

BOOL MCProcess_changeCurrentWorkingDirByFd(int fd)
{
	int res;
	if ((res = fchdir(fd))!= -1)
		return YES;
	return NO;
}

char* MCProcess_getCurrentWorkingDir(MCCharBuffer* buff)
{
	return getcwd(buff->data, buff->size);
}



/* MCSelect */



method(MCSelect, waitForFdsetChange, xxx)
{
	this->readfd_result_set = this->readfd_set;
	this->writefd_result_set = this->writefd_set;
	this->exceptionfd_result_set = this->exceptionfd_set;

	return select(this->maxfd + 1, 
		&this->readfd_result_set, 
		&this->writefd_result_set, 
		&this->exceptionfd_result_set, 
		(this->timeout.tv_usec==0 && this->timeout.tv_sec==0)? NULL : &this->timeout);
}

method(MCSelect, addFd, MCSelect_fd_type type, int fd)
{
	if(fd > this->maxfd) this->maxfd = fd;
	switch(type){
		case MCSelect_Readfd:
			FD_SET(fd, &this->readfd_set);
		break;
		case MCSelect_Writefd:
			FD_SET(fd, &this->writefd_set);
		break;
		case MCSelect_Exceptionfd:
			FD_SET(fd, &this->exceptionfd_set);
		break;
	}
}

method(MCSelect, removeFd, MCSelect_fd_type type, int fd)
{
	switch(type){
		case MCSelect_Readfd:
			FD_CLR(fd, &this->readfd_set);
		break;
		case MCSelect_Writefd:
			FD_CLR(fd, &this->writefd_set);
		break;
		case MCSelect_Exceptionfd:
			FD_CLR(fd, &this->exceptionfd_set);
		break;
	}
}

method(MCSelect, isFdReady, MCSelect_fd_type type, int fd)
{
	switch(type){
		case MCSelect_Readfd:
			return FD_ISSET(fd, &this->readfd_result_set);
		break;
		case MCSelect_Writefd:
			return FD_ISSET(fd, &this->writefd_result_set);
		break;
		case MCSelect_Exceptionfd:
			return FD_ISSET(fd, &this->exceptionfd_result_set);
		break;
	}
}

constructor(MCSelect, long second, long microsecond)
{
	link_class(MCSelect, MCObject, nil)
	{
		have_method(MCSelect, waitForFdsetChange);
		have_method(MCSelect, addFd);
		have_method(MCSelect, removeFd);
		have_method(MCSelect, isFdReady);
	}

	//timeout.tv_sec
	//timeout.tv_usec
	this->timeout.tv_sec = second;
	this->timeout.tv_usec = microsecond;

	FD_ZERO(&this->readfd_set);
	FD_ZERO(&this->writefd_set);
	FD_ZERO(&this->exceptionfd_set);

	FD_ZERO(&this->readfd_result_set);
	FD_ZERO(&this->writefd_result_set);
	FD_ZERO(&this->exceptionfd_result_set);

	return this;
}

