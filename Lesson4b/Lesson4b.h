#pragma once

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
// DESCRIPTION: Includes for Plugins
// AUTHOR: 
//***************************************************************************/

#include "3dsmaxsdk_preinclude.h"
#include "resource.h"
#include <istdplug.h>
#include <iparamb2.h>
#include <iparamm2.h>
#include <maxtypes.h>
//SIMPLE TYPE


extern TCHAR *GetString(int id);

extern HINSTANCE hInstance;

#define SampleKFCtrl_CLASS_ID	Class_ID(0x753f97e3, 0xc9ee948c)

class SampleKFCtrl : public Control
{
private:

	Control* mpXCtrl;
	Control* mpYCtrl;

	enum MyRefs {
		kXCtrlRef,
		kYCtrlRef,
		kNumRefs
	};

public:

	SampleKFCtrl();
	~SampleKFCtrl() { DeleteAllRefs(); };

	SClass_ID SuperClassID() { return CTRL_POSITION_CLASS_ID; }
	Class_ID	ClassID()   { return SampleKFCtrl_CLASS_ID; }

	int NumSubs();
	Animatable* SubAnim(int i);
	TSTR SubAnimName(int i); 
	int NumRefs() { return kNumRefs; }
	void SetReference(int i, ReferenceTarget* pTarget);
	ReferenceTarget* GetReference(int i);
	RefResult NotifyRefChanged(const Interval& changeInt, RefTargetHandle hTarget, PartID& partID, RefMessage message, BOOL propagate);

	void Copy(Control* pFrom);

	void GetValue(TimeValue t, void *ptr, Interval &valid, GetSetMethod method);
	void SetValue(TimeValue t, void *ptr, int commit, GetSetMethod method);

	void CommitValue(TimeValue t) { mpXCtrl->CommitValue(t); mpYCtrl->CommitValue(t);}
	void RestoreValue(TimeValue t) { mpXCtrl->RestoreValue(t); mpYCtrl->RestoreValue(t);}

};