#include "SimpleServer.h"

oninit(SimpleServer)
{
	if (init(MCObject)) {
		obj->socket = new(MCSocket);
		obj->ip = "127.0.0.1";
		obj->port = "80";
		return obj;
	} else {
		return null;
	}
}

method(SimpleServer, void, bye, voida)
{
	release(obj->socket);
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
	ff(obj->socket, listeningStart, 0);
	printf("Server[%s:%s] started\n", obj->ip, obj->port);
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