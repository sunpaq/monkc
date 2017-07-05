#include "MCIO.h"

#pragma mark - MCFile unbuffered IO

void MCFile_flushAllCacheToDisk()
{
	sync();
}

int MCFile_flushAFileCacheToDisk(int fd)
{
    return fsync(fd);
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
    return ff(new(MCFile), initWithPathName, pathname, O_RDONLY|O_CREAT);
}

MCFile* MCFile_newWriteOnly(char* pathname, int isClear)
{
    if(isClear)
        return ff(new(MCFile), initWithPathName, pathname, O_WRONLY|O_CREAT|O_TRUNC);
    else
        return ff(new(MCFile), initWithPathName, pathname, O_WRONLY|O_CREAT);
}

MCFile* MCFile_newReadWrite(char* pathname, int isClear)
{
    if(isClear)
        return ff(new(MCFile), initWithPathName, pathname, O_RDWR|O_CREAT|O_TRUNC);
    else
        return ff(new(MCFile), initWithPathName, pathname, O_RDWR|O_CREAT);
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

oninit(MCFile)
{
    if (init(MCObject)) {
        obj->fd = 0;
        obj->pathname = "";
        obj->buffer = mull;
        //obj->attribute;
        return obj;
    }else{
        return mull;
    }
}

method(MCFile, MCFile*, initWithPathName, char* pathname, int oflag)
{
	if((obj->fd = open(pathname, oflag, 0774))==-1)
		return mull;
	obj->pathname = pathname;
	if(fstat(obj->fd, &obj->attribute)<0)
		return mull;
	obj->buffer = malloc(obj->attribute.st_blksize*10);
	return obj;
}

method(MCFile, MCFile*, initWithPathNameDefaultFlag, char* pathname)
{
    return MCFile_initWithPathName(address, obj, pathname, MCFileReadWriteTrunc);
}

method(MCFile, size_t, readAllFromBegin, off_t offset)
{
    return MCFile_readFromBegin(0, obj, offset, obj->attribute.st_size);
}

method(MCFile, size_t, readFromBegin, off_t offset, size_t nbytes)
{
    //use pread/pwrite for atomic operation
    return pread(obj->fd, obj->buffer, nbytes, offset);
}

method(MCFile, size_t, readAtLastPosition, off_t offset, size_t nbytes)
{
    return pread(obj->fd, obj->buffer, nbytes, offset);
}

method(MCFile, size_t, readFromEnd, off_t offset, size_t nbytes)
{
    return pread(obj->fd, obj->buffer, nbytes, offset);
}

method(MCFile, size_t, writeToBegin, off_t offset, void* buf, size_t nbytes)
{
    return pwrite(obj->fd, buf, nbytes, offset);
}

method(MCFile, size_t, writeToLastTime, off_t offset, void* buf, size_t nbytes)
{
    return pwrite(obj->fd, buf, nbytes, offset);
}

method(MCFile, size_t, writeToEnd, off_t offset, void* buf, size_t nbytes)
{
    return pwrite(obj->fd, buf, nbytes, offset);
}

method(MCFile, int, duplicateFd, voida)
{
    return dup(obj->fd);
}

method(MCFile, int, duplicateFdTo, int fd)
{
    return dup2(obj->fd, fd);
}

method(MCFile, void, bye, voida)
{
    //release obj->buffer
    free(obj->buffer);
    close(obj->fd);
}

method(MCFile, void, printAttribute, voida)
{
    printf("uid:%d gid:%d size:%lld st_mode:%o lmtime:%s",
           obj->attribute.st_uid,
           obj->attribute.st_gid,
           obj->attribute.st_size,
           obj->attribute.st_mode,
           ctime(&obj->attribute.st_mtime));
}

method(MCFile, int, checkPermissionUseRealIDOfProcess, int mode)
{
    int res;
    if ((res = access(obj->pathname, mode)) != -1)
        return 1;
    return 0;
}

onload(MCFile)
{
    if (load(MCObject)) {
        binding(MCFile, MCFile*, initWithPathName, char* pathname, int oflag);
        binding(MCFile, MCFile*, initWithPathNameDefaultFlag, char* pathname);
        
        binding(MCFile, size_t, readAllFromBegin, off_t offset);
        binding(MCFile, int, readFromBegin, off_t offset, size_t nbytes);
        binding(MCFile, int, readAtLastPosition, off_t offset, size_t nbytes);
        binding(MCFile, int, readFromEnd, off_t offset, size_t nbytes);
        binding(MCFile, int, writeToBegin, off_t offset, void* buf, size_t nbytes);
        binding(MCFile, int, writeToLastTime, off_t offset, void* buf, size_t nbytes);
        binding(MCFile, int, writeToEnd, off_t offset, void* buf, size_t nbytes);
        
        binding(MCFile, int, duplicateFd);
        binding(MCFile, int, duplicateFdTo, int fd);
        binding(MCFile, void, printAttribute);
        binding(MCFile, void, bye);
        binding(MCFile, int, checkPermissionUseRealIDOfProcess, int mode);
        return cla;
    }else{
        return mull;
    }
}

#pragma mark - MCStream buffered IO

oninit(MCStream)
{
    if (init(MCObject)) {
        obj->lineArray = mull;
        obj->lineLengthArray = mull;
        obj->lineCount = 0;
        return obj;
    }else{
        return mull;
    }
}

method(MCStream, MCStream*, initWithPath, MCStreamType type, const char* path)
{
    //FILE *fopen(const char *restrict pathname, const char *restrict type);
    //type:
    //r/w/a/ & b & +
    //int setvbuf(FILE *restrict fp, char *restrict buf, int mode, size_t size);
    //[NULL _IOFBF/_IOLBF/_IONBF BUFSIZ]
    
    obj->fileObject = fopen(path, type.fopenMode);
    if (obj->fileObject == NULL) {
        error_log("can not open file: %s\n", path);
        return mull;
    }
    //long size = MCStream_tellSize(0, obj, 0);
    
    char ichar;
    char linebuff[LINE_MAX]; unsigned i = 0;
    char* textbuff[LINE_MAX]; unsigned lcount = 0;
    
    while ((ichar=fgetc(obj->fileObject)) != EOF) {
        if (ichar != '\n') {
            if (ichar == ' ' || ichar == '\t' || ichar== '\r' || ichar == '\x0b') {
                linebuff[i++] = ' ';
            }else if (ichar == '\xff'){
                //skip this char
            }else{
                linebuff[i++] = ichar;
            }

        }else{
            linebuff[i] = '\n';
            linebuff[i+1] = '\0';
            MCCharBuffer* line = NewMCCharBuffer(sizeof(char) * i+1);
            CopyToCharBuffer(line, linebuff);
            line->data[i+1] = '\0';
            textbuff[lcount++] = (line->data);
            i = 0;
        }
    }
    
    obj->lineCount = lcount;
    obj->lineArray = (char**)malloc(sizeof(char*) * lcount);
    obj->lineLengthArray = (size_t*) malloc(sizeof(unsigned) * lcount);

    memcpy(obj->lineArray, &textbuff[0], sizeof(char*) * lcount);
    ff(obj, dump, mull);
    
    return obj;
}

method(MCStream, MCStream*, initWithPathDefaultType, const char* path)
{
    return MCStream_initWithPath(0, obj, MakeMCStreamType(MCStreamBuf_FullBuffered, MCStreamOpen_ReadWrite), path);
}

method(MCStream, void, bye, voida)
{
    //0=OK/EOF=ERROR
    if(fclose(obj->fileObject))
        error_log("close file error");
    //other clean up works
    
}

method(MCStream, int, getFileDescriptor, voida)
{
    return fileno(obj->fileObject);
}

method(MCStream, int, getChar, voida)
{
    return fgetc(obj->fileObject);
}

method(MCStream, int, putChar, int charCode)
{
    return fputc(charCode, obj->fileObject);
}

method(MCStream, int, pushbackChar, int charCodeToBePushBack)
{
    return ungetc(charCodeToBePushBack, obj->fileObject);
}

method(MCStream, char*, getCString, MCCharBuffer* recvBuffer)
{
    fgets(recvBuffer->data, cast(int, recvBuffer->size), obj->fileObject);
    return recvBuffer->data;
}

method(MCStream, char*, putCString, MCCharBuffer* sendBuffer)
{
    fputs(sendBuffer->data, obj->fileObject);
    return sendBuffer->data;
}

method(MCStream, MCString*, getMCString, voida)
{
    char buff[LINE_MAX];
    fgets(buff, sizeof(buff), obj->fileObject);
    return ff(new(MCString), initWithCString, &buff[0]);
}

method(MCStream, int, putMCString, MCString* str)
{
    return fputs(str->buff, obj->fileObject);
}

method(MCStream, size_t, getBianryObject, void* recvBuffer,  size_t objectSize, size_t numberOfObjs)
{
    //size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
    return fread(recvBuffer, objectSize, numberOfObjs, obj->fileObject);
}

method(MCStream, size_t, putBianryObject, void* sendBuffer,  size_t objectSize, size_t numberOfObjs)
{
    //size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
    return fwrite(sendBuffer, objectSize, numberOfObjs, obj->fileObject);
}

method(MCStream, off_t, tellOffset, voida)
{
    //off_t ftello(FILE *fp);
    return ftello(obj->fileObject);
}

method(MCStream, int, seekFromBegin, off_t offset)
{
    //int fseeko(FILE *fp, off_t offset, int whence);//SEEK_SET/SEEK_CUR/SEEK_END
    return fseeko(obj->fileObject, offset, SEEK_SET);
}

method(MCStream, int, seekFromCurrent, off_t offset)
{
    return fseeko(obj->fileObject, offset, SEEK_CUR);
}

method(MCStream, int, seekFromEnd, off_t offset)
{
    return fseeko(obj->fileObject, offset, SEEK_END);
}

method(MCStream, long, tellSize, voida)
{
    fseek(obj->fileObject, 0, SEEK_END);
    long size = ftell(obj->fileObject);
    rewind(obj->fileObject);
    return size;
}

method(MCStream, void, dump, voida)
{
    int i;
    for (i=0; i<obj->lineCount; i++) {
        printf("%s", (obj->lineArray)[i]);
    }
}

onload(MCStream)
{
    if (load(MCObject)) {
        binding(MCStream, MCStream*, initWithPath, MCStreamType type, char* path);
        binding(MCStream, MCStream*, initWithPathDefaultType, const char* path);
        
        binding(MCStream, void, bye);
        binding(MCStream, int, getFileDescriptor);
        
        binding(MCStream, int, getChar);
        binding(MCStream, int, putChar, int charCode);
        binding(MCStream, int, pushbackChar, int charCodeToBePushBack);
        
        binding(MCStream, char*, getCString, MCCharBuffer* recvBuffer);
        binding(MCStream, char*, putCString, MCCharBuffer* sendBuffer);
        binding(MCStream, MCString*, getMCString);
        binding(MCStream, MCString*, putMCString, MCString* str);
        
        binding(MCStream, size_t, getBianryObject, void* recvBuffer,  size_t objectSize, size_t numberOfObjs);
        binding(MCStream, size_t, putBianryObject, void* sendBuffer,  size_t objectSize, size_t numberOfObjs);
        
        binding(MCStream, off_t, tellOffset);
        binding(MCStream, int, seekFromBegin, off_t offset);
        binding(MCStream, int, seekFromCurrent, off_t offset);
        binding(MCStream, int, seekFromEnd, off_t offset);
        binding(MCStream, size_t, tellSize, voida);
        binding(MCStream, void, dump, voida);
        
        return cla;
    }else{
        return mull;
    }
}

#pragma mark - MCSelect

oninit(MCSelect)
{
    if (init(MCObject)) {
        FD_ZERO(&obj->readfd_set);
        FD_ZERO(&obj->writefd_set);
        FD_ZERO(&obj->exceptionfd_set);
        
        FD_ZERO(&obj->readfd_result_set);
        FD_ZERO(&obj->writefd_result_set);
        FD_ZERO(&obj->exceptionfd_result_set);
        return obj;
    }else{
        return mull;
    }
}

method(MCSelect, void, initWithSecondAndMicrosec, long second, long microsecond)
{
    //timeout.tv_sec
    //timeout.tv_usec
    obj->timeout.tv_sec = second;
    obj->timeout.tv_usec = cast(int, microsecond);
    return;
}

method(MCSelect, int, waitForFdsetChange, voida)
{
    obj->readfd_result_set = obj->readfd_set;
    obj->writefd_result_set = obj->writefd_set;
    obj->exceptionfd_result_set = obj->exceptionfd_set;
    
    return select(obj->maxfd + 1,
                  &obj->readfd_result_set,
                  &obj->writefd_result_set,
                  &obj->exceptionfd_result_set,
                  (obj->timeout.tv_usec==0 && obj->timeout.tv_sec==0)? NULL : &obj->timeout);
}

method(MCSelect, void, addFd, MCSelect_fd_type type, int fd)
{
    if(fd > obj->maxfd) obj->maxfd = fd;
    switch(type){
        case MCSelect_Readfd:
            FD_SET(fd, &obj->readfd_set);
            break;
        case MCSelect_Writefd:
            FD_SET(fd, &obj->writefd_set);
            break;
        case MCSelect_Exceptionfd:
            FD_SET(fd, &obj->exceptionfd_set);
            break;
    }
}

method(MCSelect, void, removeFd, MCSelect_fd_type type, int fd)
{
    switch(type){
        case MCSelect_Readfd:
            FD_CLR(fd, &obj->readfd_set);
            break;
        case MCSelect_Writefd:
            FD_CLR(fd, &obj->writefd_set);
            break;
        case MCSelect_Exceptionfd:
            FD_CLR(fd, &obj->exceptionfd_set);
            break;
    }
}

method(MCSelect, int, isFdReady, MCSelect_fd_type type, int fd)
{
    switch(type){
        case MCSelect_Readfd:
            return FD_ISSET(fd, &obj->readfd_result_set);
            break;
        case MCSelect_Writefd:
            return FD_ISSET(fd, &obj->writefd_result_set);
            break;
        case MCSelect_Exceptionfd:
            return FD_ISSET(fd, &obj->exceptionfd_result_set);
            break;
    }
}

onload(MCSelect)
{
    if (load(MCObject)) {
        binding(MCSelect, void, initWithSecondAndMicrosec, long second, long microsecond);
        binding(MCSelect, int, waitForFdsetChange);
        binding(MCSelect, void, addFd, MCSelect_fd_type type, int fd);
        binding(MCSelect, void, removeFd, MCSelect_fd_type type, int fd);
        binding(MCSelect, int, isFdReady, MCSelect_fd_type type, int fd);
        return cla;
    }else{
        return mull;
    }
}

#pragma mark - MCProgress

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







