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
// DESCRIPTION: A procedural controller plug-in.
// AUTHOR: Mo Alian, Christopher Diggins and Stephen Tyler
//***************************************************************************/

#include "Lesson4a.h"

#define SampleProCtrl_CLASS_ID	Class_ID(0x90cfe0f8, 0x63507dc4)

#define PBLOCK_REF	0


void SampleProCtrl::GetValue(TimeValue t, void *ptr, Interval &valid, GetSetMethod method)
{
	Point3 p3OurAbsValue(0, 0, 0);
	p3OurAbsValue.x = 15*sin((float)t/960);
	p3OurAbsValue.y = (float)t/192;
	valid.Set(t,t+1);
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


void SampleProCtrl::SetValue(TimeValue t, void *ptr, int commit, GetSetMethod method)
{
}

class SampleProCtrlClassDesc : public ClassDesc2
{
public:
	SampleProCtrlClassDesc() {};
	~SampleProCtrlClassDesc() {};

	// ClassDesc methods.  
	// Max calls these functions to figure out what kind of plugin this class represents

	// Return TRUE if the user can create this plug-in.
	int			IsPublic()			{ return TRUE; }	// We do want the user to see this plug-in

	// Return the class name of this plug-in
	const MCHAR* ClassName()		{ static const MSTR str(_T("Lesson4a-Sample Procedural Controller")); return str; }

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
	Class_ID	ClassID()			{ return Class_ID(0x1a343aa4, 0x368c480b); }

	// If the plugin is an Object or Texture, this function returns
	// the category it can be assigned to.
	const MCHAR* Category()			{ static const MSTR str(_T("Learning Path")); return str; }

	// Return an instance of this plug-in.  Max will call this function
	// when it wants to start using our plug-in
	void*		Create(BOOL loading=FALSE)
	{
		return new SampleProCtrl;
	}
};

// This function returns a pointer to a class descriptor for our Utility
// This is the function that informs max that our plug-in exists and is 
// available to use
ClassDesc2* GetSampleProCtrlClassDesc()
{
	static SampleProCtrlClassDesc aSingleClassDesc;
	return &aSingleClassDesc;
}

