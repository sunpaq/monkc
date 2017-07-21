#ifndef SimpleServer_
#define SimpleServer_

#include "monkc.h"
#include "MCSocket.h"

class(SimpleServer, MCObject,
	const char* configFilePath;
	MCSocket* socket;
	char* ip;
	char* port;
)

method(SimpleServer, void, bye, voida);
method(SimpleServer, SimpleServer*, initWithConfigFile, const char* filepath);
method(SimpleServer, void, start, voida);
method(SimpleServer, void, stop, voida);
method(SimpleServer, void, restart, voida);

#endif



