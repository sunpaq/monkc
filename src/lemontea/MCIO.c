#include "MCIO.h"

/* MCFile */

loader(MCFile)
{
binding(MCFile, void, initWithPathName, char* pathname, int oflag);

binding(MCFile, int, readFromBegin, off_t offset, size_t nbytes);
binding(MCFile, int, readAtLastPosition, off_t offset, size_t nbytes);
binding(MCFile, int, readFromEnd, off_t offset, size_t nbytes);
binding(MCFile, int, writeToBegin, off_t offset, void* buf, size_t nbytes);
binding(MCFile, int, writeToLastTime, off_t offset, void* buf, size_t nbytes);
binding(MCFile, int, writeToEnd, off_t offset, void* buf, size_t nbytes);

binding(MCFile, int, duplicateFd, xxx);
binding(MCFile, int, duplicateFdTo, int fd);
binding(MCFile, void, printAttribute, xxx);
binding(MCFile, void, bye, xxx);
binding(MCFile, int, checkPermissionUseRealIDOfProcess, int mode);
return class;
}

initer(MCFile)
{
	this->fd = 0;
	this->pathname = "";
	this->buffer = nil;
	//this->attribute;
	return this;
}

method(MCFile, 
void, initWithPathName, char* pathname, int oflag)
{
	if((this->fd = open(pathname, oflag, 0774))==-1)
		return;
	this->pathname = pathname;
	if(fstat(this->fd, &this->attribute)<0)
		return;
	this->buffer = malloc(this->attribute.st_blksize*10);
	return;
}

// typedef enum _MCStreamType{
// 	readonly_fullbuffered,
// 	readwrite_fullbuffered,
// 	readonly_linebuffered,
// 	readwrite_linebuffered
// }MCStreamType;
loader(MCStream)
{
binding(MCStream, MCStream*, newWithPath, MCStreamType type, char* path);
binding(MCStream, void, bye, xxx);
binding(MCStream, int, getFileDescriptor, xxx);

binding(MCStream, int, getChar, xxx);
binding(MCStream, int, putChar, int charCode);
binding(MCStream, int, pushbackChar, int charCodeToBePushBack);

binding(MCStream, char*, getCString, MCCharBuffer* recvBuffer);
binding(MCStream, char*, putCString, MCCharBuffer* sendBuffer);
binding(MCStream, MCString*, getMCString, xxx);
binding(MCStream, MCString*, putMCString, MCString* str);

binding(MCStream, size_t, getBianryObject, void* recvBuffer,  size_t objectSize, size_t numberOfObjs);
binding(MCStream, size_t, putBianryObject, void* sendBuffer,  size_t objectSize, size_t numberOfObjs);

binding(MCStream, off_t, tellOffset, xxx);
binding(MCStream, int, seekFromBegin, off_t offset);
binding(MCStream, int, seekFromCurrent, off_t offset);
binding(MCStream, int, seekFromEnd, off_t offset);
return class;
}

initer(MCStream)
{
	//do nothing
	return this;
}

method(MCStream, 
MCStream*, newWithPath, MCStreamType type, char* path)
{
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


loader(MCSelect)
{
	binding(MCSelect, void, initWithSecondAndMicrosec, long second, long microsecond);
	binding(MCSelect, int, waitForFdsetChange, xxx);
	binding(MCSelect, void, addFd, MCSelect_fd_type type, int fd);
	binding(MCSelect, void, removeFd, MCSelect_fd_type type, int fd);
	binding(MCSelect, int, isFdReady, MCSelect_fd_type type, int fd);
	return class;
}

initer(MCSelect)
{
	FD_ZERO(&this->readfd_set);
	FD_ZERO(&this->writefd_set);
	FD_ZERO(&this->exceptionfd_set);

	FD_ZERO(&this->readfd_result_set);
	FD_ZERO(&this->writefd_result_set);
	FD_ZERO(&this->exceptionfd_result_set);
	return this;
}

method(MCSelect, 
void, initWithSecondAndMicrosec, long second, long microsecond)
{
	//timeout.tv_sec
	//timeout.tv_usec
	this->timeout.tv_sec = second;
	this->timeout.tv_usec = microsecond;
	return;
}

method(MCFile, int, readFromBegin, off_t offset, size_t nbytes)
{
	//use pread/pwrite for atomic operation
	return pread(this->fd, this->buffer, nbytes, offset);
}

method(MCFile, int, readAtLastPosition, 
	off_t offset, size_t nbytes)
{
	return pread(this->fd, this->buffer, nbytes, offset);
}

method(MCFile, int, readFromEnd, 
	off_t offset, size_t nbytes)
{
	return pread(this->fd, this->buffer, nbytes, offset);
}

method(MCFile, int, writeToBegin, 
	off_t offset, void* buf, size_t nbytes)
{
	return pwrite(this->fd, buf, nbytes, offset);
}

method(MCFile, int, writeToLastTime, 
	off_t offset, void* buf, size_t nbytes)
{
	return pwrite(this->fd, buf, nbytes, offset);
}

method(MCFile, int, writeToEnd, 
	off_t offset, void* buf, size_t nbytes)
{
	return pwrite(this->fd, buf, nbytes, offset);
}

method(MCFile, int, duplicateFd, xxx)
{
	return dup(this->fd);
}

method(MCFile, int, duplicateFdTo, int fd)
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

method(MCFile, void, bye, xxx)
{
	//release this->buffer
	free(this->buffer);
	close(this->fd);
}

method(MCFile, void, printAttribute, xxx)
{
	printf("uid:%d gid:%d size:%d st_mode:%o lmtime:%s", 
		this->attribute.st_uid, 
		this->attribute.st_gid,
		this->attribute.st_size,
		this->attribute.st_mode,
		ctime(&this->attribute.st_mtime));
}

method(MCFile, int, checkPermissionUseRealIDOfProcess, int mode)
{
	int res;
	if ((res = access(this->pathname, mode)) != -1)
		return 1;
	return 0;
}

int MCFile_isFileExist(char* pathname)
{
	//file exist test
	int res;
	if ((res = access(pathname, F_OK)) != -1)
		return 1;
	return 0;
}

int MCFile_chmod(char* pathname, mode_t mode)
{
	int res;
	if ((res = chmod(pathname, mode))!= -1)
		return 1;
	return 0;
}

int MFFile_truncateFileTo(char* pathname, off_t length)
{
	int res;
	if ((res = truncate(pathname, length))!= -1)
		return 1;
	return 0;
}

mode_t MCFile_setNewFilePermissionMask4Process(mode_t cmask)
{
	return umask(cmask);
}

MCFile* MCFile_newReadOnly(char* pathname)
{
	return ff(new(MCFile), newWithPathName, pathname, O_RDONLY|O_CREAT);
}

MCFile* MCFile_newWriteOnly(char* pathname, int isClear)
{
	if(isClear)
		return ff(new(MCFile), newWithPathName, pathname, O_WRONLY|O_CREAT|O_TRUNC);
	else
		return ff(new(MCFile), newWithPathName, pathname, O_WRONLY|O_CREAT);
}

MCFile* MCFile_newReadWrite(char* pathname, int isClear)
{
	if(isClear)
		return ff(new(MCFile), newWithPathName, pathname, O_RDWR|O_CREAT|O_TRUNC);
	else
		return ff(new(MCFile), newWithPathName, pathname, O_RDWR|O_CREAT);
}

int MCFile_createSymbolLink(char* pathname, char* linkname)
{
	int res;
	if ((res = symlink(pathname, linkname))!= -1)
		return 1;
	return 0;
}

int MCFile_createDirectory(char* pathname)
{
	int res;
	if ((res = mkdir(pathname, S_IRWXU))!= -1)
		return 1;
	return 0;
}

int MCFile_removeDirectory(char* pathname)
{
	int res;
	if ((res = rmdir(pathname))!= -1)
		return 1;
	return 0;
}


/* MCProcess */


int MCProcess_changeCurrentWorkingDir(char* pathname)
{
	int res;
	if ((res = chdir(pathname))!= -1)
		return 1;
	return 0;
}

int MCProcess_changeCurrentWorkingDirByFd(int fd)
{
	int res;
	if ((res = fchdir(fd))!= -1)
		return 1;
	return 0;
}

char* MCProcess_getCurrentWorkingDir(MCCharBuffer* buff)
{
	return getcwd(buff->data, buff->size);
}


/* MCStream */


method(MCStream, void, bye, xxx)
{
	//0=OK/EOF=ERROR
	if(fclose(this->fileObject))
		error_log("close file error");
	//other clean up works

}

method(MCStream, int, getFileDescriptor, xxx)
{
	return fileno(this->fileObject);
}

method(MCStream, int, getChar, xxx)
{
	return fgetc(this->fileObject);
}

method(MCStream, int, putChar, int charCode)
{
	return fputc(charCode, this->fileObject);
}

method(MCStream, 
int, pushbackChar, int charCodeToBePushBack)
{
	return ungetc(charCodeToBePushBack, this->fileObject);
}

method(MCStream, 
char*, getCString, MCCharBuffer* recvBuffer)
{
	return fgets(recvBuffer->data, recvBuffer->size, this->fileObject);
}

method(MCStream, 
char*, putCString, MCCharBuffer* sendBuffer)
{
	return fputs(sendBuffer->data, this->fileObject);
}

method(MCStream, 
MCString*, getMCString, xxx)
{
	char buff[1024];
	fgets(buff, sizeof(buff), this->fileObject);
	return ff(new(MCString), initWithCString, &buff[0]);
}

method(MCStream,
MCString*, putMCString, MCString* str)
{
	return fputs(str->buff, this->fileObject);
}

method(MCStream, 
size_t, getBianryObject, void* recvBuffer,  size_t objectSize, size_t numberOfObjs)
{
	//size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
	return fread(recvBuffer, objectSize, numberOfObjs, this->fileObject);
}

method(MCStream, 
size_t, putBianryObject, void* sendBuffer,  size_t objectSize, size_t numberOfObjs)
{
	//size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
	return fwrite(sendBuffer, objectSize, numberOfObjs, this->fileObject);
}

method(MCStream, 
off_t, tellOffset, xxx)
{
	//off_t ftello(FILE *fp);
	return ftello(this->fileObject);
}

method(MCStream, 
int, seekFromBegin, off_t offset)
{
	//int fseeko(FILE *fp, off_t offset, int whence);//SEEK_SET/SEEK_CUR/SEEK_END
	return fseeko(this->fileObject, offset, SEEK_SET);
}

method(MCStream, 
int, seekFromCurrent, off_t offset)
{
	return fseeko(this->fileObject, offset, SEEK_CUR);
}

method(MCStream, 
int, seekFromEnd, off_t offset)
{
	return fseeko(this->fileObject, offset, SEEK_END);
}



/* MCSelect */



method(MCSelect, int, waitForFdsetChange, xxx)
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

method(MCSelect, 
void, addFd, MCSelect_fd_type type, int fd)
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

method(MCSelect, 
void, removeFd, MCSelect_fd_type type, int fd)
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

method(MCSelect, 
int, isFdReady, MCSelect_fd_type type, int fd)
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


