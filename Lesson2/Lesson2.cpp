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

#include "Lesson2.h"

#define Lesson2_CLASS_ID	Class_ID(0x1f75565c, 0x8d3eebc4)

class Lesson2 : public SceneExport {
	public:
		
		static HWND hParams;
		
		int				ExtCount();					// Number of extensions supported
		const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
		const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
		const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
		const TCHAR *	AuthorName();				// ASCII Author name
		const TCHAR *	CopyrightMessage();			// ASCII Copyright message
		const TCHAR *	OtherMessage1();			// Other message #1
		const TCHAR *	OtherMessage2();			// Other message #2
		unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
		void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

		BOOL SupportsOptions(int ext, DWORD options);
		int				DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);

		//Constructor/Destructor
		Lesson2();
		~Lesson2();	

private:

		//////////////////////////////////////////////////////////////////////////
		// Export max entities

		// Export a Max Node.  This recursive function will iterate
		// the max scene tree, and export the interesting information
		// from each node visited.
		void Export(INode* pNode, int iTreeDepth = 0);

		//////////////////////////////////////////////////////////////////////////
		// Output Utilities

		// Our output section.  Because we are a simple text writer,
		// we are simply going to pipe our messages to a text file.
		FILE* m_pFile;

		// Initialize our out stream.  This function must be
		// called before commencing the export process
		BOOL BeginWriting(const TCHAR* pPath);

		// Finalize our out stream.  This function must be
		// called before finishing the export process
		void EndWriting();

		// A simple printf wrapper function to encapsulate
		// writing to the file.
		void Write(int indent, const MCHAR* pMsg, ...);

};



class Lesson2ClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new Lesson2(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return Lesson2_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("Lesson2"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};

static Lesson2ClassDesc Lesson2Desc;
ClassDesc2* GetLesson2Desc() { return &Lesson2Desc; }





INT_PTR CALLBACK Lesson2OptionsDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) {
	static Lesson2 *imp = NULL;

	switch(message) {
		case WM_INITDIALOG:
			imp = (Lesson2 *)lParam;
			CenterWindow(hWnd,GetParent(hWnd));
			return TRUE;

		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return 1;
	}
	return 0;
}


//--- Lesson2 -------------------------------------------------------
Lesson2::Lesson2()
{
	m_pFile = NULL; // Dont forget to initialize
}

Lesson2::~Lesson2() 
{
	DbgAssert(m_pFile == NULL); // And check we cleaned up
}

int Lesson2::ExtCount()
{
	return 1;
}

const TCHAR *Lesson2::Ext(int n)
{		
	return _T("txt");
}

const TCHAR *Lesson2::LongDesc()
{
	return _T("Basic ASCII Scene Exporter");
}
	
const TCHAR *Lesson2::ShortDesc() 
{			
	return _T("Lesson2-ASCII");
}

const TCHAR *Lesson2::AuthorName()
{			
	return _T("Your Name");
}

const TCHAR *Lesson2::CopyrightMessage() 
{	
	return _T("Copyright: Your Studio");
}

const TCHAR *Lesson2::OtherMessage1() 
{		
	//TODO: Return Other message #1 if any
	return _T("");
}

const TCHAR *Lesson2::OtherMessage2() 
{		
	//TODO: Return other message #2 in any
	return _T("");
}

unsigned int Lesson2::Version()
{				
	#pragma message(TODO("Return Version number * 100 (i.e. v3.01 = 301)"))
	return 100;
}

void Lesson2::ShowAbout(HWND hWnd)
{			
	// Optional
}

BOOL Lesson2::SupportsOptions(int ext, DWORD options)
{
	#pragma message(TODO("Decide which options to support.  Simply return true for each option supported by each Extension the exporter supports."))
	return TRUE;
}


int	Lesson2::DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts, DWORD options)
{

	if (BeginWriting(name))
	{

		INode* pRootNode = i->GetRootNode();

		//Export tree.
		Export(pRootNode);

		EndWriting();

		return TRUE; // We have successfully exported to our file!
	}

	// If we are here, something in the export failed.
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
// Max Entity Export

void Lesson2::Export(INode* pNode, int iTreeDepth /* = 0 */)
{
	// First step to export: What are we exporting?
	// Here we are going to export the basic scene tree,
	// identifying each node by name.

	MCHAR * pNodeName = const_cast<MCHAR*>(pNode->GetName());
	int nChildren = pNode->NumberOfChildren();

	// Write out this node as [NodeName] : XX Children
	Write(iTreeDepth, _T("[%s] : %i children"), pNodeName, nChildren);

	// Recursively call the children
	iTreeDepth++;
	for (int i = 0; i < nChildren; i++)
	{
		Export(pNode->GetChildNode(i), iTreeDepth);
	}
}
//////////////////////////////////////////////////////////////////////////
// Writing utility functions

BOOL Lesson2::BeginWriting(const TCHAR *pPath)
{
	// Check we are not currently writing
	DbgAssert(m_pFile == NULL);

	errno_t lErr = _tfopen_s(&m_pFile, pPath, TEXT("w"));
	return lErr == 0;
}

void Lesson2::EndWriting()
{
	DbgAssert(m_pFile != NULL);

	fclose(m_pFile);
	m_pFile = NULL;
}

void Lesson2::Write(int indent, const MCHAR * pMsg, ...)
{
	DbgAssert(m_pFile != NULL);

	// first, write in the indent
	for (int i = 0; i < indent; i++) _ftprintf(m_pFile, _T("\t"));

	// Write the message, passing in our variable
	// parameters to a function that wraps printf
	va_list vargs;
	va_start(vargs, pMsg);
	vfwprintf(m_pFile, pMsg, vargs);
	va_end(vargs);

	// Finish the line
	_ftprintf (m_pFile, _T("\n"));
}
