#include "MCSocket.h"

static void create_and_bind_socket(MCSocket* this, MCSocketType socket_type, char* ip, char* port);

constructor(MCSocketClientInfo, xxx)
{
	link_class(MCSocketClientInfo, MCObject, nil)
	{
		binding(MCSocketClientInfo, dumpInfo, xxx);
		binding(MCSocketClientInfo, bye, xxx);
	}
	return this;
}

method(MCSocketClientInfo, dumpInfo, xxx)
{
	printf("accept a client: %s\n", this->address.sa_data);
}

method(MCSocketClientInfo, bye, xxx)
{
	//nothing to do
}

constructor(MCSocket, MCSocketType socket_type, char* ip, char* port)
{
	link_class(MCSocket, MCObject, nil)
	{
		binding(MCSocket, listeningStart, xxx);//listen
		binding(MCSocket, acceptARequest, xxx); returns(MCSocketClientInfo*)
		//have_method(MCSocket, connectServer, xxx);

		binding(MCSocket, recv, xxx);
		binding(MCSocket, recvfrom, xxx);
		binding(MCSocket, recvmsg, xxx);
		binding(MCSocket, send, xxx);
		binding(MCSocket, sendto, xxx);
		binding(MCSocket, sendmsg, xxx);

		binding(MCSocket, bye, xxx);
	}

	create_and_bind_socket(this, socket_type, ip, port);
	return this;
}



static void create_and_bind_socket(MCSocket* this, MCSocketType socket_type, char* ip, char* port)
{
	//int sfd = ;
	//BOOL isServer;
	struct addrinfo hint, *result;
	runtime_log("begin prepare hint.\n");

	//prepare hint
	memset(&hint, 0, sizeof(struct addrinfo));
	hint.ai_family = AF_UNSPEC;
	hint.ai_protocol = IPPROTO_IP;
	switch(socket_type){
		case MCSocket_Server_TCP:
			hint.ai_socktype = SOCK_STREAM;
			hint.ai_flags = AI_PASSIVE;
			this->isServer = YES;
		break;
		case MCSocket_Server_UDP:
			hint.ai_socktype = SOCK_DGRAM;
			hint.ai_flags = AI_PASSIVE;
			this->isServer = YES;
		break;
		case MCSocket_Client_TCP:
			hint.ai_socktype = SOCK_STREAM;
			this->isServer = NO;
		break;
		case MCSocket_Client_UDP:
			hint.ai_socktype = SOCK_DGRAM;
			this->isServer = NO;
		break;
	}
	//get addrinfo linklist
	if(getaddrinfo(ip, port, &hint, &result)){
		error_log("can not getaddrinfo, return nil\n");
		return -1;
	}
	runtime_log("get the addrinfo linklist.\n");

	//try every addrinfo in list to create and bind until success
	struct addrinfo* iterator;
	for(iterator = result; iterator!=nil; iterator = iterator->ai_next)
	{		
		this->sfd = socket(iterator->ai_family, iterator->ai_socktype, iterator->ai_protocol);
		if (this->isServer)
		{
			if (this->sfd==-1)
				continue;
			if (!bind(this->sfd, iterator->ai_addr, iterator->ai_addrlen))
			{
				//memcpy(&this->peeraddrinfo, iterator, sizeof(struct addrinfo));
				break;//bind success
			}			
				
		}else{
			if (this->sfd==-1)
				continue;
			if (!connect(this->sfd, iterator->ai_addr, iterator->ai_addrlen))
				break;//connect success
		}
		close(this->sfd);
	}
	//free linklist
	freeaddrinfo(result);
	//return socket fd
	//return sfd;
}

method(MCSocket, bye, xxx)
{
	//
	close(this->sfd);
}

method(MCSocket, listeningStart, xxx)
{
	if(this->isServer!=YES)return -1;
	return listen(this->sfd, MCSocket_Queue_Length);
}

method(MCSocket, acceptARequest, xxx) returns(MCSocketClientInfo)
{
	if (this->isServer!=YES)return -1;
	MCSocketClientInfo* clientinfo = new(MCSocketClientInfo, nil);
	clientinfo->returnSfd = accept(this->sfd, &clientinfo->address, &clientinfo->address_len);
	return clientinfo;
}

// method(MCSocket, connectServer, xxx)
// {
// 	if (this->isServer==YES)return -1;
// 	int ret = connect(this->sfd, this->peeraddrinfo.ai_addr, this->peeraddrinfo.ai_addrlen);
// 	error_log("connectted: return-%d\n", ret);
// 	return ret;
// }

method(MCSocket, recv, xxx)
{

}
method(MCSocket, recvfrom, xxx)
{

}
method(MCSocket, recvmsg, xxx)
{

}
method(MCSocket, send, xxx)
{

}
method(MCSocket, sendto, xxx)
{

}
method(MCSocket, sendmsg, xxx)
{

}

