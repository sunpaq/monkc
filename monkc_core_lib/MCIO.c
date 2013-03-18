#include "MCIO.h"

/* MCFile */

constructor(MCFile, char* pathname, int oflag)
{
	link_class(MCFile, MCObject, nil)
	{
		//can only be used by call()
		// binding(MCFile, readFromBegin, off_t offset, size_t nbytes);
		// binding(MCFile, readAtLastPosition, off_t offset, size_t nbytes);
		// binding(MCFile, readFromEnd, off_t offset, size_t nbytes);

		// binding(MCFile, writeToBegin, off_t offset, void* buf, size_t nbytes);
		// binding(MCFile, writeToLastTime, off_t offset, void* buf, size_t nbytes);
		// binding(MCFile, writeToEnd, off_t offset, void* buf, size_t nbytes);

		binding(MS(2,I,P), MCFile, duplicateFd, xxx); returns(int fd);
		binding(MS(2,I,I), MCFile, duplicateFdTo, int fd); returns(int newfd);
		binding(MSNA, MCFile, printAttribute, xxx);
		binding(MSNA, MCFile, bye, xxx);
		binding(MS(2,I,I), MCFile, checkPermissionUseRealIDOfProcess, int mode); returns(BOOL)
	}

	if((this->fd = open(pathname, oflag, 0774))==-1)
		return nil;
	this->pathname = pathname;
	if(fstat(this->fd, &this->attribute)<0)
		return nil;
	this->buffer = malloc(this->attribute.st_blksize*10);
	return this;
}

// typedef enum _MCStreamType{
// 	readonly_fullbuffered,
// 	readwrite_fullbuffered,
// 	readonly_linebuffered,
// 	readwrite_linebuffered
// }MCStreamType;
constructor(MCStream, MCStreamType type, CString path)
{
	link_class(MCStream, MCObject, nil)
	{
		binding(MSNA, MCStream, bye, xxx);
		binding(MS(2,I,P), MCStream, getFileDescriptor, xxx); returns(int)

		binding(MS(2,I,P), MCStream, getChar, xxx); returns(int)
		binding(MS(2,P,I), MCStream, putChar, int charCode);
		binding(MS(2,I,I), MCStream, pushbackChar, int charCodeToBePushBack); returns(int charCode/EOF)

		binding(MS(2,P,P), MCStream, getCString, MCCharBuffer* recvBuffer); returns(CString/nil)
		binding(MS(2,P,P), MCStream, putCString, MCCharBuffer* sendBuffer); returns(CString/nil)
		binding(MS(2,P,P), MCStream, getMCString, xxx);                     returns(Handle(MCString))
		binding(MS(2,P,P), MCStream, putMCString, MCString* str);           returns(Handle(MCString)/nil)

		//binding(MS(2,P,P), MCStream, getBianryObject, void* recvBuffer,  size_t objectSize, size_t numberOfObjs); returns(size_t)
		//binding(MCStream, putBianryObject, void* sendBuffer,  size_t objectSize, size_t numberOfObjs); returns(size_t)

		//binding(MCStream, tellOffset, xxx); returns(off_t)
		//binding(MCStream, seekFromBegin, off_t offset); returns(BOOL)
		//binding(MCStream, seekFromCurrent, off_t offset); returns(BOOL)
		//binding(MCStream, seekFromEnd, off_t offset); returns(BOOL)
	}
	//FILE *fopen(const char *restrict pathname, const char *restrict type);
	//type:
	//r/w/a/ & b & +
	//int setvbuf(FILE *restrict fp, char *restrict buf, int mode, size_t size);
	//[NULL _IOFBF/_IOLBF/_IONBF BUFSIZ]

	char* rw_type="w+";
	int buff_mode=_IOFBF;
	switch(type){
		case readonly_fullbuffered:
			rw_type="w";
		break;
		case readonly_linebuffered:
			rw_type="w";buff_mode=_IOLBF;
		break;
		case readwrite_fullbuffered:
			//default
		break;
		case readwrite_linebuffered:
			buff_mode=_IOLBF;
		break;
	}

	if((this->fileObject = fopen(path, rw_type))!=nil)
		setvbuf(this->fileObject, NULL, buff_mode, BUFSIZ);
	else
		return nil;
	return this;
}

constructor(MCSelect, long second, long microsecond)
{
	link_class(MCSelect, MCObject, nil)
	{
		binding(MS(2,I,P), MCSelect, waitForFdsetChange, xxx); returns(int: >0 success =0 timeout <0 error)
		binding(MS(3,P,I,I), MCSelect, addFd, MCSelect_fd_type type, int fd);
		binding(MS(3,P,I,I), MCSelect, removeFd, MCSelect_fd_type type, int fd);
		binding(MS(3,I,I,I), MCSelect, isFdReady, MCSelect_fd_type type, int fd); returns(BOOL)
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
	mc_free(this->buffer);
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


/* MCProcess */


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


/* MCStream */


method(MCStream, bye, xxx)
{
	//0=OK/EOF=ERROR
	if(fclose(this->fileObject))
		error_log("close file error");
	//other clean up works

}

method(MCStream, getFileDescriptor, xxx) returns(int)
{
	return fileno(this->fileObject);
}

method(MCStream, getChar, xxx) returns(int)
{
	return fgetc(this->fileObject);
}

method(MCStream, putChar, int charCode)
{
	return fputc(charCode, this->fileObject);
}

method(MCStream, pushbackChar, int charCodeToBePushBack) returns(int charCode/EOF)
{
	return ungetc(charCodeToBePushBack, this->fileObject);
}

method(MCStream, getCString, MCCharBuffer* recvBuffer) returns(CString/nil)
{
	return fgets(recvBuffer->data, recvBuffer->size, this->fileObject);
}

method(MCStream, putCString, MCCharBuffer* sendBuffer) returns(CString/nil)
{
	return fputs(sendBuffer->data, this->fileObject);
}

method(MCStream, getMCString, xxx)                     returns(Handle(MCString))
{
	char buff[1024];
	fgets(buff, sizeof(buff), this->fileObject);
	return new(MCString, &buff[0]);
}

method(MCStream, putMCString, MCString* str)           returns(Handle(MCString)/nil)
{
	return fputs(str->buff, this->fileObject);
}

method(MCStream, getBianryObject, void* recvBuffer,  size_t objectSize, size_t numberOfObjs) returns(size_t)
{
	//size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
	return fread(recvBuffer, objectSize, numberOfObjs, this->fileObject);
}

method(MCStream, putBianryObject, void* sendBuffer,  size_t objectSize, size_t numberOfObjs) returns(size_t)
{
	//size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
	return fwrite(sendBuffer, objectSize, numberOfObjs, this->fileObject);
}

method(MCStream, tellOffset, xxx) returns(off_t)
{
	//off_t ftello(FILE *fp);
	return ftello(this->fileObject);
}

method(MCStream, seekFromBegin, off_t offset) returns(BOOL)
{
	//int fseeko(FILE *fp, off_t offset, int whence);//SEEK_SET/SEEK_CUR/SEEK_END
	return fseeko(this->fileObject, offset, SEEK_SET);
}

method(MCStream, seekFromCurrent, off_t offset) returns(BOOL)
{
	return fseeko(this->fileObject, offset, SEEK_CUR);
}

method(MCStream, seekFromEnd, off_t offset) returns(BOOL)
{
	return fseeko(this->fileObject, offset, SEEK_END);
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


