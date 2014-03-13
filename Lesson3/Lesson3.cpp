//**************************************************************************/
// Copyright (c) 2013 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin, Modified to show the name of the 
//              currently selected node in the view port. 
// AUTHOR: Mo Alian and Christopher Diggins
//***************************************************************************/

#include "Lesson3.h"

#define SampleRef_CLASS_ID	Class_ID(0xa940aed4, 0x6046c0cd)


class SampleRef : public UtilityObj , public ReferenceMaker
{
public:
		
	//Constructor/Destructor
	SampleRef();
	virtual ~SampleRef();

	virtual void DeleteThis() { }
	
	virtual void BeginEditParams(Interface *ip,IUtil *iu);
	virtual void EndEditParams(Interface *ip,IUtil *iu);

	// This callback is executed whenever
	// a new node is selected in the scene.
	void SelectionSetChanged(Interface *ip,IUtil *iu);

	// Return how many references we support
	int NumRefs();

	// Max calls this function to see what references we hold
	ReferenceTarget* GetReference(int i);

	// Max calls this function to set a reference on us
	void SetReference(int i, ReferenceTarget* pTarget);

	// Max calls this function to let us know of a changed state on our references.
	RefResult NotifyRefChanged(const Interval &changeInt, RefTargetHandle hTarget, PartID& partID, RefMessage message, BOOL propagate);

	virtual void Init(HWND hWnd);
	virtual void Destroy(HWND hWnd);
	
	// Singleton access
	static SampleRef* GetInstance() { 
		static SampleRef theSampleRef;
		return &theSampleRef; 
	}

private:

	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND   hPanel;
	IUtil* iu;

	// Our reference pointer.
	INode* mpMyNode;	

	// A small function to set the text on our
	// dialog to the currently referenced nodes name.
	// s is the input string to be displayed.
	void SetText(const MSTR& s);

};


class SampleRefClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 	{ return SampleRef::GetInstance(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return UTILITY_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return SampleRef_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("SampleRef"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GetSampleRefDesc() { 
	static SampleRefClassDesc SampleRefDesc;
	return &SampleRefDesc; 
}




//--- SampleRef -------------------------------------------------------
SampleRef::SampleRef()
	: hPanel(nullptr)
	, iu(nullptr)
{
	
}

SampleRef::~SampleRef()
{

}

#pragma region lesson functions

void SampleRef::BeginEditParams(Interface* ip,IUtil* iu) 
{
	DbgAssert(hPanel == NULL);
	hPanel = ip->AddRollupPage(hInstance,	// A handle to our Dll
		MAKEINTRESOURCE(IDD_PANEL),			// The dialog to load from the Dll's resource
		(DLGPROC)DefWindowProc,				// A windows defined dialog proc (does nothing)
		_T("Referenced Node"));					// The rollup's title

	if (ip->GetSelNodeCount() > 0)
		ReplaceReference(0, ip->GetSelNode(0));
}
	
void SampleRef::EndEditParams(Interface* ip,IUtil*)
{
	this->iu = nullptr;
	ip->DeleteRollupPage(hPanel);
	hPanel = nullptr;
}

void SampleRef::SelectionSetChanged(Interface *ip,IUtil *iu)
{
	if (ip->GetSelNodeCount() > 0)
	{
		ReplaceReference(0, ip->GetSelNode(0));
	}
	else
	{
		ReplaceReference(0, NULL);
	}
}

// For this step, we are implementing these functions
// to maintain our single reference: NumRefs(), GetReference(),
// SetReference() and NotifyRefChanged().

int SampleRef::NumRefs()
{
	return 1;
}

// Max calls this function to see what references we hold
ReferenceTarget* SampleRef::GetReference(int i)
{
	return mpMyNode;	//we have only one reference in this plug-in
}

// Max calls this function to set a reference on us
// NOTE: we should never call it directly. Use ReplaceReference()
//       when you need to change your reference.
void SampleRef::SetReference(int i, ReferenceTarget* pTarget)
{
	switch (i)
	{
	case 0:				//we have only one reference in this plug-in
		{
			INode* tmp = dynamic_cast<INode*>(pTarget);
			if (tmp != NULL) {
				mpMyNode = tmp;
				MSTR s(tmp->GetName());
				s += _T(" is being observed now.");
				SetText(s);
			}
			else {
				SetText(_T("No node is currently being observed."));
			}
		}
		break;
	}
}

// Max calls this function to let us know of a changed state on our references.
RefResult SampleRef::NotifyRefChanged(const Interval &changeInt,		// this parameter is never used
	RefTargetHandle hTarget,	// Our reference who is notifying us.
	PartID& partID,				// Can be additional information, depending on the message
	RefMessage message,			// Whats happened?  This is the important info!
	BOOL propagate)
{
	// Should be true, but just in case
	if (mpMyNode) {
		MSTR s(mpMyNode->GetName());
		s += _T(" is changed.");
		SetText(s);
	}
	return REF_SUCCEED;
}

#pragma endregion

#pragma region Private Functions 

void SampleRef::SetText(const MSTR& s)
{
	// MSTR is the main string class in 3ds Max SDK.
    // hPanel is a data member pointing to the rollout page and
    // IDC_NODENAME is the name of the static text field in that rollout page.
	SetDlgItemText(hPanel, IDC_NODENAME, s.data());	
}

void SampleRef::Init(HWND /*handle*/)
{

}

void SampleRef::Destroy(HWND /*handle*/)
{

}

INT_PTR CALLBACK SampleRef::DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
		case WM_INITDIALOG:
			SampleRef::GetInstance()->Init(hWnd);
			break;

		case WM_DESTROY:
			SampleRef::GetInstance()->Destroy(hWnd);
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
