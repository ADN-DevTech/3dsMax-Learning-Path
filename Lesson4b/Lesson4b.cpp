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
// DESCRIPTION: Appwizard generated plugin, modified to implement a 2D animation 
// controller
// AUTHOR: Mo Alian, Christopher Diggins and Kevin Vandecar
//***************************************************************************/

#include "Lesson4b.h"



#define PBLOCK_REF	0


SampleKFCtrl::SampleKFCtrl()
{
	// Create default X & Y controllers.  These classes are
	// implementations of the Control class that generate float values.
	mpXCtrl = NULL;
	mpYCtrl = NULL;

	ReplaceReference(kXCtrlRef, NewDefaultFloatController());
	ReplaceReference(kYCtrlRef, NewDefaultFloatController());

}

void SampleKFCtrl::SetReference(int i, ReferenceTarget* pTarget)
{
	switch (i)
	{
	case kXCtrlRef: mpXCtrl = (Control*)pTarget; break;
	case kYCtrlRef: mpYCtrl = (Control*)pTarget; break;
	}
}

ReferenceTarget* SampleKFCtrl::GetReference(int i)
{
	switch (i)
	{
	case kXCtrlRef: return mpXCtrl;
	case kYCtrlRef: return mpYCtrl;
	}
	return NULL;
}

RefResult SampleKFCtrl::NotifyRefChanged(const Interval& /*changeInt*/, RefTargetHandle /*hTarget*/, PartID& /*partID*/, RefMessage /*message*/, BOOL /*propagate*/)
{
	return REF_DONTCARE;
}

void SampleKFCtrl::Copy(Control* pFrom)
{
	// If the object we are about to control has been previously been
	// controlled by another controller, we get a chance to copy its
	// given key frames here. We might want to at least copy the 
	// position of the object at the time zero, so the object does not 
	// suddenly appear in a random coordination in the view port when
	// the animation starts.  
	// NOTE - remember, never assign directly to the pointer:
	// Control* pNewX = pFrom->GetXController();
	// Likewise for the Y controller:
	// Control* pNewY = pFrom->GetYController();

	//mpXCtrl = pFrom->GetXController();
	//mpYCtrl = pFrom->GetYController();

}

void SampleKFCtrl::GetValue(TimeValue t, void *ptr, Interval &valid, GetSetMethod method)
{
	//We read the values for our X & Y component from our referenced float controllers
	Point3 p3OurAbsValue(0, 0, 0);
	mpXCtrl->GetValue(t, &p3OurAbsValue.x, valid, CTRL_ABSOLUTE);
	mpYCtrl->GetValue(t, &p3OurAbsValue.y, valid, CTRL_ABSOLUTE);

	if (method == CTRL_ABSOLUTE)
	{
		Point3* p3InVal = (Point3*)ptr;
		*p3InVal = p3OurAbsValue;
	}
	else // CTRL_RELATIVE
	{
		Matrix3* m3InVal = (Matrix3*)ptr;
		m3InVal->PreTranslate(p3OurAbsValue);
	}
}


void SampleKFCtrl::SetValue(TimeValue t, void *ptr, int commit, GetSetMethod method)
{
	// We set the requested values on our referenced X & Y float controllers.
	// Max is trying to tell us what our value should be.  In turn, we need
	// to tell our subanims (our X & Y controllers) what their value should be.
	Point3* p3Val = (Point3*)ptr;
	mpXCtrl->SetValue(t, &p3Val->x, commit, CTRL_ABSOLUTE);
	mpYCtrl->SetValue(t, &p3Val->y, commit, CTRL_ABSOLUTE);
}

int SampleKFCtrl::NumSubs() { 
	return 2; 
}

Animatable* SampleKFCtrl::SubAnim(int i) { 

	switch (i)
	{
	case kXCtrlRef: return mpXCtrl;
	case kYCtrlRef: return mpYCtrl;
	}
	return NULL;

}

TSTR SampleKFCtrl::SubAnimName(int i)
{
	switch (i)
	{
	case kXCtrlRef: return _T("X Pos.");
	case kYCtrlRef: return _T("Y Pos.");
	}
	return _T("Unknown!");
}


class SampleKFCtrlClassDesc : public ClassDesc2
{
public:
	SampleKFCtrlClassDesc() {};
	~SampleKFCtrlClassDesc() {};

	// ClassDesc methods.  
	// Max calls these functions to figure out what kind of plugin this class represents

	// Return TRUE if the user can create this plug-in.
	int			IsPublic()			{ return TRUE; }	// We do want the user to see this plug-in

	// Return the class name of this plug-in
	const MCHAR* ClassName()		{ static const MSTR str(_T("Lesson4b-Sample Keyframe Controller")); return str; }

	// Return the SuperClassID - this ID should
	// match the implementation of the interface returned
	// by Create.
	SClass_ID	SuperClassID()		{ return CTRL_POSITION_CLASS_ID; }

	// Return the unique ID that identifies this class
	// This is required when saving.  Max stores the ClassID
	// reported by the actual plugin, and on reload it recreates
	// the appropriate class by matching the stored ClassID with
	// the matching ClassDesc
	//
	// You can generate random ClassID's using the gencid program
	// supplied with the Max SDK
	Class_ID	ClassID()			{ return SampleKFCtrl_CLASS_ID; }

	// If the plugin is an Object or Texture, this function returns
	// the category it can be assigned to.
	const MCHAR* Category()			{ static const MSTR str(_T("Learning Path")); return str; }

	// Return an instance of this plug-in.  Max will call this function
	// when it wants to start using our plug-in
	void*		Create(BOOL loading=FALSE)
	{
		return new SampleKFCtrl;
	}
};

/// This function returns a pointer to a class descriptor for our Utility
/// This is that informs max that our plug-in exists and is available to use
ClassDesc2* GetSampleKFCtrlClassDesc()
{
	static SampleKFCtrlClassDesc aSingleClassDesc;
	return &aSingleClassDesc;
}