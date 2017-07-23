#ifndef SimpleServer_
#define SimpleServer_

#include "monkc.h"
#include "MCSocket.h"
#include "MCThread.h"

class(SimpleServer, MCObject,
	const char* configFilePath;
	MCSocket* socket;
	MCThread* worker;
	char* ip;
	char* port;
)

method(SimpleServer, void, bye, voida);
method(SimpleServer, SimpleServer*, initWithConfigFile, const char* filepath);
method(SimpleServer, void, start, voida);
method(SimpleServer, void, stop, voida);
method(SimpleServer, void, restart, voida);

#endif



