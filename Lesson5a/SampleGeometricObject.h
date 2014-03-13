#include "Simpobj.h"
#define SampleGObject_CLASS_ID    Class_ID(0x666ec2ec, 0xa3406b51)

class SampleGObject : public SimpleObject2 {
public:

	SampleGObject() 
		: objSize(2.0) 
	{ }

	// Member variable
	double objSize;

	// From BaseObject
	CreateMouseCallBack* GetCreateMouseCallBack() { return NULL; }

	// From SimpleObject
	void BuildMesh(TimeValue t);

	//From Animatable
	Class_ID ClassID() {return SampleGObject_CLASS_ID;}        
	SClass_ID SuperClassID() { return GEOMOBJECT_CLASS_ID; }
	void GetClassName(TSTR& s) { s = _T("Sample Geometric Object");}

	void DeleteThis() { delete this; }        
};