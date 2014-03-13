#pragma once

#include "Max.h"

#include "istdplug.h"
#include "iparamb2.h"
#include "iparamm2.h"
#include <maxtypes.h>
#include <utilapi.h>

extern HINSTANCE hInstance;

class SampleUtil : public UtilityObj 
{
public:
	SampleUtil() { }
	virtual ~SampleUtil() { }
	virtual void DeleteThis() { }		
	virtual void BeginEditParams(Interface *ip,IUtil *iu);
	virtual void EndEditParams(Interface *ip,IUtil *iu);
	
	static SampleUtil* GetInstance() 
	{ 
		static SampleUtil theUtilitySample;
		return &theUtilitySample; 
	}

private:
	Interface *ip;
};


class UtilitySampleClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 	{ return SampleUtil::GetInstance(); }
	virtual const TCHAR *	ClassName() 			{ return _T("Lesson1b-SampleUtil"); }
	virtual SClass_ID SuperClassID() 				{ return UTILITY_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return Class_ID(0x6a287c04, 0x76533d12); }
	virtual const TCHAR* Category() 				{ return _T("Learning Path"); }
	virtual const TCHAR* InternalName() 			{ return _T("Lesson1b-SampleUtil"); }
	virtual HINSTANCE HInstance() 					{ return hInstance; }
};
