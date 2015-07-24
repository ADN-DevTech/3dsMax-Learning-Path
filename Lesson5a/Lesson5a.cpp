//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "Lesson5a.h"

#include "SampleGeometricObject.h"

#define Lesson5a_CLASS_ID	Class_ID(0x8a013aa7, 0x80b131c0)


class Lesson5a : public UtilityObj 
{
public:

	//Constructor/Destructor
	Lesson5a();
	virtual ~Lesson5a();

	virtual void DeleteThis() { }

	virtual void BeginEditParams(Interface *ip,IUtil *iu);
	virtual void EndEditParams(Interface *ip,IUtil *iu);

	virtual void Init(HWND hWnd);
	virtual void Destroy(HWND hWnd);

	// Singleton access
	static Lesson5a* GetInstance() { 
		static Lesson5a theLesson5a;
		return &theLesson5a; 
	}

private:

	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND   hPanel;
	IUtil* iu;
};


class Lesson5aClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 	{ return Lesson5a::GetInstance(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return UTILITY_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return Lesson5a_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("Lesson5a"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle


};


ClassDesc2* GetLesson5aDesc() { 
	static Lesson5aClassDesc Lesson5aDesc;
	return &Lesson5aDesc; 
}




//--- Lesson5a -------------------------------------------------------
Lesson5a::Lesson5a()
	: hPanel(nullptr)
	, iu(nullptr)
{

}

Lesson5a::~Lesson5a()
{

}

void Lesson5a::BeginEditParams(Interface* ip,IUtil* iu) 
{
	this->iu = iu;
	hPanel = ip->AddRollupPage(
		hInstance,
		MAKEINTRESOURCE(IDD_PANEL),
		DlgProc,
		GetString(IDS_PARAMS),
		0);

	// Create an object 
	// SampleGObject* myGeomObj = new SampleGObject();
	SampleGObject* myGeomObj = (SampleGObject*)ip->CreateInstance(GEOMOBJECT_CLASS_ID, SampleGObject_CLASS_ID);
	INode* node = ip->CreateObjectNode(myGeomObj);
	TimeValue t (0);
	Matrix3 tm(1);
	node->SetNodeTM(t,tm);
}

void Lesson5a::EndEditParams(Interface* ip,IUtil*)
{
	this->iu = nullptr;
	ip->DeleteRollupPage(hPanel);
	hPanel = nullptr;
}

void Lesson5a::Init(HWND /*handle*/)
{

}

void Lesson5a::Destroy(HWND /*handle*/)
{

}

INT_PTR CALLBACK Lesson5a::DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
	case WM_INITDIALOG:
		Lesson5a::GetInstance()->Init(hWnd);
		break;

	case WM_DESTROY:
		Lesson5a::GetInstance()->Destroy(hWnd);
		break;

	case WM_COMMAND:
#pragma message(TODO("React to the user interface commands.  A utility plug-in is controlled by the user from here."))
		break;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MOUSEMOVE:
		GetCOREInterface()->RollupMouseMessage(hWnd,msg,wParam,lParam);
		break;

	default:
		return 0;
	}
	return 1;
}
