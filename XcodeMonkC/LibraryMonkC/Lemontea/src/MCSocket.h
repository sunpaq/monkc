#include "MCContext.h"
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
/* 
[ Server Program Skeleton (UDP) ]

getaddrinfo(&result) <--- get a list of address structures.
for(every address in linklist)
	sfd = socket(&result)
	bind(sfd, &result) <--- if successful bind the socket, break.
	close(sfd)         <--- if fail close this socket.
freeaddrinfo(&result)
for(;;)
	recvfrom(sfd)
	sendto(sfd)

[ Client Program Skeleton (UDP) ]

getaddrinfo(argv[1], argv[2], &result) <--- get a list of address structures.
for(every address in linklist)
	sfd = socket(&result)
	connect(sfd, &result) <--- if successful connect the socket, break.
	close(sfd)            <--- if fail close this socket.
freeaddrinfo(&result)
for(;;)
	write(sfd)
	read(sfd)

[ 1. address match and connect step ]
[ 2. transport data over connection step ]

[ protocol families (domain) ]
AF_UNIX, AF_LOCAL
AF_INET, AF_INET6
AF_IPX
AF_NETLINK
AF_X25
AF_AX25
AF_ATMPVC
AF_APPLETALK
AF_PACKET

[ socket type ]
SOCK_STREAM
SOCK_DGRAM
SOCK_SEQPACKET
SOCK_RAW
SOCK_RDM
SOCK_PACKET
//linux adds:
SOCK_STREAM | SOCK_NONBLOCK
SOCK_STREAM | SOCK_CLOEXEC

[ official protocol number (etc/protocols) ]
ip 0
tcp 6
udp 17

[ socket() errors ]
EACCES
EAFNOSUPPORT
EINVAL
EMFILE
ENFILE
ENOBUFS
ENOMEM
EPROTONOSUPPORT

old_unconnected_socket_fd <--- 	socket() 		//create my socket
								bind()   		//bind socket to my address
								listen() 		//mark the socket active to be connect. comming request may buffered in the queue
new_connected_socket_fd   <--- 	accept(old_fd) 	//start loop and block to wait for a client? or get the first request from queue.
                                         		//the new socket is inherit from old one, but without "listening" status
                                         		//and have the client address for sendback
                                         		//the old socket is unaffected for the 2nd client to connect
                                         		//server deal every request by one thread 

struct addrinfo {
   int              ai_flags;
   int              ai_family;
   int              ai_socktype;
   int              ai_protocol;
   size_t           ai_addrlen;
   struct sockaddr *ai_addr; <--- this is the sockaddr struct used by bind() or connect()
   char            *ai_canonname;
   struct addrinfo *ai_next;
};

APIs

int     socket(int domain, int type, int protocol);
int     bind(int socket, const struct sockaddr *address, socklen_t address_len);
int     listen(int socket, int backlog);
int     accept(int socket, struct sockaddr *address, socklen_t *address_len);

int     connect(int socket, const struct sockaddr *address, socklen_t address_len);

//usurally use the default File IO APIs to read()/write()/close() sfd
//the following APIs provide more features

ssize_t recv(int socket, void *buffer, size_t length, int flags);
ssize_t recvfrom(int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len);
ssize_t recvmsg(int socket, struct msghdr *message, int flags);

ssize_t send(int socket, const void *message, size_t length, int flags);
ssize_t sendto(int socket, const void *message, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len);
ssize_t sendmsg(int socket, const struct msghdr *message, int flags);

int     setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);
int     getsockopt(int socket, int level, int option_name, void *option_value, socklen_t *option_len);
int     socketpair(int domain, int type, int protocol, int socket_vector[2]);
int     getpeername(int socket, struct sockaddr *address, socklen_t *address_len);
int     getsockname(int socket, struct sockaddr *address, socklen_t *address_len);
int     shutdown(int socket, int how);

[ Server      Client ]

socket()      socket()

bind()        connect() <--- if bind() is not called connect will call bind() first? linux default timeout is 75s?
listen()
accept()

[ IO APIs ]
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
ssize_t read(int fd, void *buf, size_t count);

read()        read() 
write()       write()
close()       close()

<< UNIX Network Programming >>

*/
#define MCSocket_Queue_Length 50
typedef enum _MCSocketType{
	MCSocket_Server_TCP,
	MCSocket_Server_UDP,
	MCSocket_Client_TCP,
	MCSocket_Client_UDP,
}MCSocketType;

#ifndef MCSocketClientInfo_
#define MCSocketClientInfo_

monkc(MCSocketClientInfo);
	int returnSfd;
	struct sockaddr address;
	socklen_t address_len;
end(MCSocketClientInfo);

method(MCSocketClientInfo, void, dumpInfo, xxx);
method(MCSocketClientInfo, void, bye, xxx);
#endif

#ifndef MCSocket_ 
#define MCSocket_

monkc(MCSocket);
	int sfd;
	int isServer;
	struct addrinfo peeraddrinfo;
end(MCSocket);

method(MCSocket, MCSocket*, initWithTypeIpPort, MCSocketType socket_type, char* ip, char* port);
method(MCSocket, int, listeningStart, xxx);
method(MCSocket, MCSocketClientInfo*, acceptARequest, xxx);
method(MCSocket, void, recv, xxx);
method(MCSocket, void, recvfrom, xxx);
method(MCSocket, void, recvmsg, xxx);
method(MCSocket, void, send, xxx);
method(MCSocket, void, sendto, xxx);
method(MCSocket, void, sendmsg, xxx);
method(MCSocket, void, bye, xxx);
#endif
