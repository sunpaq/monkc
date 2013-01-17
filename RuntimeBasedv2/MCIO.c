#include "MCIO.h"

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
	super_init(this, MCObject, nil);

	link_class(MCSelect, MCObject)
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

