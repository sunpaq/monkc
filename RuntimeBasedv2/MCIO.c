#include "MCIO.h"

/* MCFileManager */

method(MCFile, readFromBegin, off_t offset, size_t nbytes)
{
	//use pread/pwrite for atomic operation
	//lseek(this->fd, offset, SEEK_SET);
	return pread(this->fd, this->buffer, nbytes, offset);
}

method(MCFile, readFromLastTime, off_t offset, size_t nbytes)
{
	//lseek(this->fd, offset, SEEK_CUR);
	return pread(this->fd, this->buffer, nbytes, offset);
}

method(MCFile, readFromEnd, off_t offset, size_t nbytes)
{
	//lseek(this->fd, offset, SEEK_END);
	return pread(this->fd, this->buffer, nbytes, offset);
}

method(MCFile, writeToBegin, off_t offset, void* buf, size_t nbytes)
{
	//lseek(this->fd, offset, SEEK_SET);
	return pwrite(this->fd, buf, nbytes, offset);
}

method(MCFile, writeToLastTime, off_t offset, void* buf, size_t nbytes)
{
	//lseek(this->fd, offset, SEEK_CUR);
	return pwrite(this->fd, buf, nbytes, offset);
}

method(MCFile, writeToEnd, off_t offset, void* buf, size_t nbytes)
{
	//lseek(this->fd, offset, SEEK_END);
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

constructor(MCFile, char* pathname, size_t buffersize, int oflag)
{
	link_class(MCFile, MCObject, nil)
	{
		have_method(MCFile, readFromBegin);
		have_method(MCFile, readFromLastTime);
		have_method(MCFile, readFromEnd);
		have_method(MCFile, writeToBegin);
		have_method(MCFile, writeToLastTime);
		have_method(MCFile, writeToEnd);
		have_method(MCFile, bye);
	}

	if((this->fd = open(pathname, oflag))==-1)
		return nil;
	this->pathname = pathname;
	this->buffer = malloc(buffersize);

	return this;
}

BOOL MCFile_isFileExist(char* pathname)
{
	//file exist test
	int res;
	if ((res = open(pathname, O_RDONLY)) != -1)
	{
		close(res);
		return YES;
	}
	return NO;
}

MCFile* MCFile_newReadOnly(char* pathname, size_t buffersize)
{
	return new(MCFile, pathname, buffersize, O_RDONLY|O_CREAT);
}

MCFile* MCFile_newWriteOnly(char* pathname, size_t buffersize)
{
	return new(MCFile, pathname, buffersize, O_WRONLY|O_CREAT);
}

MCFile* MCFile_newReadWrite(char* pathname, size_t buffersize)
{
	return new(MCFile, pathname, buffersize, O_RDWR|O_CREAT);
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

