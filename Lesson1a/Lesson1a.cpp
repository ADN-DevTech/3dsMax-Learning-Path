//**************************************************************************/
// Copyright (c) 1998-2018 Autodesk, Inc.
// All rights reserved.
// 
// Use of this software is subject to the terms of the Autodesk license 
// agreement provided at the time of installation or download, or which 
// otherwise accompanies this software in either electronic or hard copy form.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: Drew Avis
//***************************************************************************/

#include "lesson1a.h"

#include "ui_plugin_form.h"
#include "qmessagebox.h"
#include "qobject.h"

#define UTILITYSAMPLE_CLASS_ID Class_ID(0x5c3ac3d1, 0xc370b077)

class UtilitySample : public UtilityObj, public QObject 
{
public:
	// Constructor/Destructor
	UtilitySample();
	virtual ~UtilitySample();

	virtual void DeleteThis() override {}
	
	virtual void BeginEditParams(Interface *ip,IUtil *iu) override;
	virtual void EndEditParams(Interface *ip,IUtil *iu) override;

	virtual void Init(HWND hWnd);
	virtual void Destroy(HWND hWnd);
	
	// Singleton access
	static UtilitySample* GetInstance() { 
		static UtilitySample theSample;
		return &theSample;
	}

private:
	void DoSomething();
	QWidget *widget;
	Ui::PluginRollup ui;
	IUtil* iu;
};


class UtilitySampleClassDesc : public ClassDesc2 
{
public:
	virtual int           IsPublic() override                       { return TRUE; }
	virtual void*         Create(BOOL /*loading = FALSE*/) override { return UtilitySample::GetInstance(); }
	virtual const TCHAR * ClassName() override                      { return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID     SuperClassID() override                   { return UTILITY_CLASS_ID; }
	virtual Class_ID      ClassID() override                        { return UTILITYSAMPLE_CLASS_ID; }
	virtual const TCHAR*  Category() override                       { return GetString(IDS_CATEGORY); }

	virtual const TCHAR*  InternalName() override                   { return _T("lesson1a"); } // Returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE     HInstance() override                      { return hInstance; } // Returns owning module handle


};

ClassDesc2* GetUtilitySampleDesc()
{
	static UtilitySampleClassDesc UtilitySampleDesc;
	return &UtilitySampleDesc; 
}




//--- UtilitySample -------------------------------------------------------
UtilitySample::UtilitySample()
	: iu(nullptr)
{

}

UtilitySample::~UtilitySample()
{

}

void UtilitySample::BeginEditParams(Interface* ip,IUtil* iu) 
{
	this->iu = iu;
	widget = new QWidget;
	ui.setupUi(widget);

	// We can connect UI signals here using Qt Functor syntax
	QObject::connect(ui.pushButton, &QPushButton::clicked, this, &UtilitySample::DoSomething);
	ip->AddRollupPage(*widget, L"Plug-in Rollup");

	ip->PushPrompt(_M("Hello World from Lesson 1.  Called from BeginEditParams()"));
}

void UtilitySample::EndEditParams(Interface* ip,IUtil*)
{
	this->iu = nullptr;
	ip->DeleteRollupPage(*widget);

	ip->PopPrompt();
}

void UtilitySample::Init(HWND /*handle*/)
{

}

void UtilitySample::Destroy(HWND /*handle*/)
{

}

void UtilitySample::DoSomething()
{
	int spin_value = ui.spinBox->value();
	QMessageBox::information(widget, "Dialog", QString("Spinner value: %1").arg(spin_value));
}
