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

#include "Lesson5b.h"

#define SampleGObject2_CLASS_ID	Class_ID(0xa8abe205, 0x2dd52bb8)

#define PBLOCK_REF	0

class SampleGObject2 : public SimpleObject2
{
public:
	// Parameter block handled by parent
		float objSize;

	//Constructor/Destructor
	SampleGObject2();
	virtual ~SampleGObject2();

	// Parameter block handled by parent

	// From BaseObject
	virtual CreateMouseCallBack* GetCreateMouseCallBack();

	// From Object
	virtual BOOL HasUVW();
	virtual void SetGenUVW(BOOL sw);
	virtual int CanConvertToType(Class_ID obtype);
	virtual Object* ConvertToType(TimeValue t, Class_ID obtype);
	virtual void GetCollapseTypes(Tab<Class_ID>& clist,Tab<TSTR*>& nlist);
	virtual int IntersectRay(TimeValue t, Ray& ray, float& at, Point3& norm);

	// From Animatable
	virtual void BeginEditParams( IObjParam  *ip, ULONG flags,Animatable *prev);
	virtual void EndEditParams( IObjParam *ip, ULONG flags,Animatable *next);

	// From SimpleObject
	virtual void BuildMesh(TimeValue t);
	virtual void InvalidateUI();

	//From Animatable
	virtual Class_ID ClassID() {return SampleGObject2_CLASS_ID;}
	virtual SClass_ID SuperClassID() { return GEOMOBJECT_CLASS_ID; }
	virtual void GetClassName(TSTR& s) {s = GetString(IDS_CLASS_NAME);}

	virtual RefTargetHandle Clone( RemapDir& remap );

	virtual int NumParamBlocks() { return 1; }					// return number of ParamBlocks in this instance
	virtual IParamBlock2* GetParamBlock(int /*i*/) { return pblock2; } // return i'th ParamBlock
	virtual IParamBlock2* GetParamBlockByID(BlockID id) { return (pblock2->ID() == id) ? pblock2 : NULL; } // return id'd ParamBlock

	void DeleteThis() { delete this; }
};



class SampleGObject2ClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new SampleGObject2(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return GEOMOBJECT_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return SampleGObject2_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("SampleGObject2"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GetSampleGObject2Desc() { 
	static SampleGObject2ClassDesc SampleGObject2Desc;
	return &SampleGObject2Desc; 
}





enum { samplegobject2_params };


//TODO: Add enums for various parameters
enum { 
	pb_spin,
};




static ParamBlockDesc2 samplegobject2_param_blk ( samplegobject2_params, _T("params"),  0, GetSampleGObject2Desc(), 
	P_AUTO_CONSTRUCT + P_AUTO_UI, PBLOCK_REF, 
	//rollout
	IDD_PANEL, IDS_PARAMS, 0, 0, NULL,
	// params
	pb_spin, 			_T("spin"), 		TYPE_FLOAT, 	P_ANIMATABLE, 	IDS_SPIN, 
		p_default, 		0.1f, 
		p_range, 		0.0f,1000.0f, 
		p_ui, 			TYPE_SPINNER,		EDITTYPE_FLOAT, IDC_EDIT,	IDC_SPIN, 0.01f, 
		p_end,
	p_end
	);




//--- SampleGObject2 -------------------------------------------------------

SampleGObject2::SampleGObject2()
{
	GetSampleGObject2Desc()->MakeAutoParamBlocks(this);
}

SampleGObject2::~SampleGObject2()
{
}

void SampleGObject2::BeginEditParams(IObjParam* ip, ULONG flags, Animatable* prev)
{
	SimpleObject2::BeginEditParams(ip,flags,prev);
	GetSampleGObject2Desc()->BeginEditParams(ip, this, flags, prev);
}

void SampleGObject2::EndEditParams( IObjParam* ip, ULONG flags, Animatable* next )
{
	//TODO: Save plugin parameter values into class variables, if they are not hosted in ParamBlocks. 
	SimpleObject2::EndEditParams(ip,flags,next);
	GetSampleGObject2Desc()->EndEditParams(ip, this, flags, next);
}

//From Object
BOOL SampleGObject2::HasUVW() 
{ 
	//TODO: Return whether the object has UVW coordinates or not
	return TRUE; 
}

void SampleGObject2::SetGenUVW(BOOL sw) 
{
	if (sw==HasUVW()) 
		return;
	//TODO: Set the plugin's internal value to sw
}

//Class for interactive creation of the object using the mouse
class SampleGObject2CreateCallBack : public CreateMouseCallBack {
	IPoint2 sp0;              //First point in screen coordinates
	SampleGObject2* ob; //Pointer to the object 
	Point3 p0;                //First point in world coordinates

	Point3 p1;			//We added this point. Second point in world coordinates.

public:	
	int proc( ViewExp *vpt,int msg, int point, int flags, IPoint2 m, Matrix3& mat);
	void SetObj(SampleGObject2 *obj) {ob = obj;}
};

int SampleGObject2CreateCallBack::proc(ViewExp *vpt,int msg, int point, int /*flags*/, IPoint2 m, Matrix3& mat )
{
	// You can use DebugPrint() similar to the following line to get useful information 
	// on the program flow when you are debugging your plug-in project:
	//	DebugPrint("\nmousecallback::proc() called with: msg: %d point: %d flags: %d", msg, point, flags);
	TimeValue t (0);
    if (msg==MOUSE_POINT||msg==MOUSE_MOVE) {
        switch(point) 
        {
        case 0: // only happens with MOUSE_POINT msg
            ob->suspendSnap = TRUE;
            sp0 = m;
            p0 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
            mat.SetTrans(p0); // sets the pivot location
            ob->objSize = 0.0;
            break;
        case 1:
			{
            ob->suspendSnap = TRUE; 
            p1 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
            float speedFactor = 24.0f;
            ob->objSize = (Length(p1 - p0) / speedFactor);
            ob->mesh.InvalidateGeomCache();
            ob->BuildMesh(t);
            if (msg == 1)
                return CREATE_STOP;
            break;
			}
        case 2:			
            return CREATE_STOP;
        }
        ob->NotifyDependents(FOREVER, PART_ALL, REFMSG_CHANGE);
    } 
    else {
        if (msg == MOUSE_ABORT) return CREATE_ABORT;
    }
    return TRUE;
}

static SampleGObject2CreateCallBack SampleGObject2CreateCB;

//From BaseObject
CreateMouseCallBack* SampleGObject2::GetCreateMouseCallBack() 
{
	SampleGObject2CreateCB.SetObj(this);
	return(&SampleGObject2CreateCB);
}

//From SimpleObject
void SampleGObject2::BuildMesh(TimeValue /*t*/)
{
	//TODO: Implement the code to build the mesh representation of the object
	//      using its parameter settings at the time passed. The plug-in should 
	//      use the data member mesh to store the built mesh.
	//      SimpleObject ivalid member should be updated. This can be done while
	//      retrieving values from pblock2.
	ivalid = FOREVER;
}

void SampleGObject2::InvalidateUI() 
{
	// Hey! Update the param blocks
	pblock2->GetDesc()->InvalidateUI();
}

Object* SampleGObject2::ConvertToType(TimeValue t, Class_ID obtype)
{
	//TODO: If the plugin can convert to a nurbs surface then check to see 
	//      whether obtype == EDITABLE_SURF_CLASS_ID and convert the object
	//      to nurbs surface and return the object
	//      If no special conversion is needed remove this implementation.
	
	return SimpleObject::ConvertToType(t,obtype);
}

int SampleGObject2::CanConvertToType(Class_ID obtype)
{
	//TODO: Check for any additional types the plugin supports
	//      If no special conversion is needed remove this implementation.
	return SimpleObject::CanConvertToType(obtype);
}

// From Object
int SampleGObject2::IntersectRay(TimeValue /*t*/, Ray& /*ray*/, float& /*at*/, Point3& /*norm*/)
{
	//TODO: Return TRUE after you implement this method
	return FALSE;
}

void SampleGObject2::GetCollapseTypes(Tab<Class_ID>& clist,Tab<TSTR*>& nlist)
{
	Object::GetCollapseTypes(clist, nlist);
	//TODO: Append any any other collapse type the plugin supports
}

// From ReferenceTarget
RefTargetHandle SampleGObject2::Clone(RemapDir& remap) 
{
	SampleGObject2* newob = new SampleGObject2();	
	//TODO: Make a copy all the data and also clone all the references
	newob->ReplaceReference(0,remap.CloneRef(pblock2));
	newob->ivalid.SetEmpty();
	BaseClone(this, newob, remap);
	return(newob);
}
