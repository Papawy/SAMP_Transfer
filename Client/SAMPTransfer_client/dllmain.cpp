#include <Windows.h>
#include <iostream>

#include "Client.h"

Client clientMod(sf::seconds(1));
/*
__declspec(dllexport) void startMod()
{
	
	core.reset(new Core);
	core->getProgram()->start();
	core.reset();
	
}*/

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			//DisableThreadLibraryCalls(hinstDLL);
			clientMod.readCommandLine(GetCommandLineA());
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			/*if (core)
			{
				core->getProgram()->stop();
			}*/
			break;
		}
	}
	return TRUE;
}