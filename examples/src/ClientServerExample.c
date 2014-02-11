#include "ClientServerExample.h"
#include "MCSocket.h"
#include "MCIO.h"

void mocha_clientsocket_test(MCContext* context)
{
	MCSocket* client = new(MCSocket);
	ff(client, initWithTypeIpPort, MCSocket_Client_TCP, "127.0.0.1", "4000");

	char sendbuff[1024];
	//char recvbuff[1024];
	
	for(;;){
		memset(sendbuff, 0, 1024);
		printf("%s\n", "to Server: (your message please)");
		ff(context, getUserInputString, sendbuff);
		char* str = strcat(sendbuff, "\n");

		write(client->sfd, str, strlen(str));
	}

	release(client);
}

static int readline(int fd, char* const recvbuff)
{
	char onechar;
	char* ptr = recvbuff;
	int RETURN_VAL_END_OF_FILE = 0;
	while(read(fd, &onechar, 1)!=RETURN_VAL_END_OF_FILE){
		(*ptr++)=onechar;
		if (onechar=='\n')return 0;
	}
	return -1;
}

void mocha_serversocket_test()
{
	MCSocket* server = new(MCSocket);
	ff(server, initWithTypeIpPort, MCSocket_Server_TCP, "127.0.0.1", "4000");

	ff(server, listeningStart, nil);
	printf("%s\n", "MC server start to listenning");

	char *sendbuff[1024];
	char *recvbuff[1024];

	//use select()
	MCSelect* fdcontroler = new(MCSelect);
	ff(fdcontroler, initWithSecondAndMicrosec, 0, 0);

	ff(fdcontroler, addFd, MCSelect_Readfd, server->sfd);

	int client_array[100];
	memset(client_array, 0, sizeof(client_array));
	int client_count = 0;

	for(;;){

		printf("%s\n", "wait for message...");
		if(ff(fdcontroler, waitForFdsetChange, nil)<=0)//no time out
		{
			//[<0] error [=0] time out
			error_log("select error, or time out!\n");
			release(fdcontroler);
			release(server);
			exit(-1);
		}

		if (ff(fdcontroler, isFdReady, MCSelect_Readfd, server->sfd))
		{
			MCSocketClientInfo* request = ff(server, acceptARequest, nil);
			//get a empty client slot
			int i;
			for (i = 0; i < 100; ++i){
				if(client_array[i]==0)
				{
					client_array[i] = request->returnSfd;
					break;
				}
			}
			
			printf("accept a client: %d Total[%d]\n", i, ++client_count);
			ff(fdcontroler, addFd, MCSelect_Readfd, client_array[i]);

			//TODO:
			release(request);
			continue;
		}

		int i;
		for(i=0; i<100; i++){

			if(client_array[i]==0)continue;

			if(ff(fdcontroler, isFdReady, MCSelect_Readfd, client_array[i])){
				memset(sendbuff, 0, 1024);
				memset(recvbuff, 0, 1024);

				if(readline(client_array[i], recvbuff[0])==-1){
					printf("a client quite: %d Total[%d]\n", i, --client_count);
					ff(fdcontroler, removeFd, MCSelect_Readfd, client_array[i]);
					close(client_array[i]);
					client_array[i]=0;
					break;
				}
				
				printf("get a message from: %d Total[%d] ---- %s", i, client_count, recvbuff[0]);
			}
		}
	}
	release(server);
}