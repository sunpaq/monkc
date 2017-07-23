#include "SimpleServer.h"

static const char* template = "\
worker thread running...\n\
server[%s:%s] started\n\
please open another terminal and connet this Server by:\n\
------------------------\n\
telnet %s %s\n\
------------------------\n\
";

static const char* welcome = "\
---------------------------------\n\
Welcome to join Monk-C community!\n\
---------------------------------\n\
";

function(void, workerThread, voida)
{
	as(SimpleServer);
	printf(template, obj->ip, obj->port, obj->ip, obj->port);
	MCSocket_listeningStart(obj->socket, 0);

	MCSocketClientInfo client;
	while (1) {
		MCBool success = MCSocket_acceptARequest(obj->socket, &client);
		if (success) {
			MCSocketClientInfoDump(&client);
			ff(obj->socket, send, welcome);

			printf("close socket\n");
			close(client.returnSfd);
			break;
		}
	}
}

oninit(SimpleServer)
{
	if (init(MCObject)) {
		var(configFilePath) = "";
		var(socket) = new(MCSocket);
		//var(worker) = new(MCThread);
		//MCThread_initWithFPointerArgument(obj->worker, workerThread, obj);

		var(ip) = "127.0.0.1";
		var(port) = "1234";
		ff(obj->socket, initWithTypeIpPort, MCSocket_Server_TCP, obj->ip, obj->port);

		return obj;
	}
	return null;
}

method(SimpleServer, void, bye, voida)
{
	release(obj->socket);
	release(obj->worker);
}

method(SimpleServer, SimpleServer*, initWithConfigFile, const char* filepath)
{
	obj->configFilePath = filepath;
	//get ip and port from config file

	ff(obj->socket, initWithTypeIpPort, MCSocket_Server_TCP, obj->ip, obj->port);
	return obj;
}

method(SimpleServer, void, start, voida)
{
	printf("starting worker thread...\n");
	workerThread(obj, 0);
}

method(SimpleServer, void, stop, voida)
{
	
}

method(SimpleServer, void, restart, voida)
{

}

onload(SimpleServer)
{
	if (load(MCObject)) {
		binding(SimpleServer, void, bye, voida);
		binding(SimpleServer, SimpleServer*, initWithConfigFile, const char* filepath);
		binding(SimpleServer, void, start, voida);
		binding(SimpleServer, void, stop, voida);
		binding(SimpleServer, void, restart, voida);
		return cla;
	} else {
		return null;
	}
}