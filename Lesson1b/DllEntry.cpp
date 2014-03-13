#include "Lesson1b.h"

extern ClassDesc2* GetUtilitySampleDesc();

HINSTANCE hInstance;

BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID /*lpvReserved*/)
{
	if( fdwReason == DLL_PROCESS_ATTACH )
	{
		// Hang on to this DLL's instance handle.
		hInstance = hinstDLL;
		//Further notifications from OS get disabled for this DLL here. 
		//This means that if other threads are created in the same OS process and 
		//decide to load the same dll, the DLLMain() will not be called anymore.//
		DisableThreadLibraryCalls(hInstance);
	}
	return(TRUE);
}

__declspec( dllexport ) int LibNumberClasses()
{
	return 1;
}

__declspec( dllexport ) ULONG LibVersion()
{
	return VERSION_3DSMAX;
}

__declspec( dllexport ) const TCHAR* LibDescription()
{
	return _T("Lesson 1: a sample utility plug-in, without using the plug-in wizard.");
}

__declspec( dllexport ) ClassDesc* LibClassDesc(int i)
{
	switch(i) {
	case 0: return GetUtilitySampleDesc();
	default: return 0;
	}
}
