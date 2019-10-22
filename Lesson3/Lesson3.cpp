//**************************************************************************/
// Copyright (c) 1998-2018 Autodesk, Inc.
// All rights reserved.
// 
// Use of this software is subject to the terms of the Autodesk license 
// agreement provided at the time of installation or download, or which 
// otherwise accompanies this software in either electronic or hard copy form.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "lesson3.h"

#include "ui_plugin_form.h"
#include "qmessagebox.h"
#include "qobject.h"

#define SAMPLEREF_CLASS_ID Class_ID(0xa940aed4, 0x6046c0cd)

class SampleRef : public UtilityObj, public QObject, public ReferenceMaker 
{
public:
	// Constructor/Destructor
	SampleRef();
	virtual ~SampleRef();

	virtual void DeleteThis() override {}
	
	virtual void BeginEditParams(Interface *ip,IUtil *iu) override;
	virtual void EndEditParams(Interface *ip,IUtil *iu) override;

	// This callback is executed whenever
	// a new node is selected in the scene.
	void SelectionSetChanged(Interface *ip, IUtil *iu) override;

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
		static SampleRef theSample;
		return &theSample;
	}

private:
	void DoSomething();
	QWidget *widget;
	Ui::PluginRollup ui;
	IUtil* iu;

	// Our reference pointer.
	INode* mpMyNode;
	// A small function to set the text on our
	// dialog to the currently referenced nodes name.
	// s is the input string to be displayed.
	void SetText(const MSTR& s);
};


class UtilitySampleClassDesc : public ClassDesc2 
{
public:
	virtual int           IsPublic() override                       { return TRUE; }
	virtual void*         Create(BOOL /*loading = FALSE*/) override { return SampleRef::GetInstance(); }
	virtual const TCHAR * ClassName() override                      { return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID     SuperClassID() override                   { return UTILITY_CLASS_ID; }
	virtual Class_ID      ClassID() override                        { return SAMPLEREF_CLASS_ID; }
	virtual const TCHAR*  Category() override                       { return GetString(IDS_CATEGORY); }

	virtual const TCHAR*  InternalName() override                   { return _T("SampleRef"); } // Returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE     HInstance() override                      { return hInstance; } // Returns owning module handle


};

ClassDesc2* GetUtilitySampleDesc()
{
	static UtilitySampleClassDesc UtilitySampleDesc;
	return &UtilitySampleDesc; 
}




//--- UtilitySample -------------------------------------------------------
SampleRef::SampleRef()
	: iu(nullptr)
{

}

SampleRef::~SampleRef()
{

}

#pragma region lesson functions

void SampleRef::BeginEditParams(Interface* ip,IUtil* iu) 
{
	this->iu = iu;
	widget = new QWidget;
	ui.setupUi(widget);

	// We can connect UI signals here using Qt Functor syntax
	QObject::connect(ui.pushButton, &QPushButton::clicked, this, &SampleRef::DoSomething);
	ip->AddRollupPage(*widget, L"Referenced Node");

}

void SampleRef::EndEditParams(Interface* ip,IUtil*)
{
	this->iu = nullptr;
	ip->DeleteRollupPage(*widget);

	ip->PopPrompt();
}

void SampleRef::SelectionSetChanged(Interface *ip, IUtil *iu)
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
		if (tmp != NULL)
		{
			mpMyNode = tmp;
			MSTR s(tmp->GetName());
			s += _T(" is being observed now.");
			SetText(s);
		}
		else
		{
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
	if (mpMyNode)
	{
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
	// ui is the instance of our Rollup UI

	ui.NodeName_Label->setText(s);	
}


void SampleRef::Init(HWND /*handle*/)
{

}

void SampleRef::Destroy(HWND /*handle*/)
{

}

void SampleRef::DoSomething()
{
	int spin_value = ui.spinBox->value();
	QMessageBox::information(widget, "Dialog", QString("Spinner value: %1").arg(spin_value));
}
