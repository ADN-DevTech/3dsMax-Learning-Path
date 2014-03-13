#include "SampleGeometricObject.h"

void SampleGObject::BuildMesh(TimeValue t)
{
	ivalid = FOREVER;
	objSize = 2.0;
	mesh.setNumVerts(4);
	mesh.setNumFaces(3);
	mesh.setVert(0,objSize*Point3(0.0,0.0,0.0)); 
	mesh.setVert(1,objSize*Point3(10.0,0.0,0.0)); 
	mesh.setVert(2,objSize*Point3(0.0,10.0,0.0)); 
	mesh.setVert(3,objSize*Point3(0.0,0.0,10.0)); 

	mesh.faces[0].setVerts(0, 1, 2);
	mesh.faces[0].setEdgeVisFlags(1,1,0);
	mesh.faces[0].setSmGroup(2);
	mesh.faces[1].setVerts(3, 1, 0);
	mesh.faces[1].setEdgeVisFlags(1,1,0);
	mesh.faces[1].setSmGroup(2);
	mesh.faces[2].setVerts(0, 2, 3);
	mesh.faces[2].setEdgeVisFlags(1,1,0);
	mesh.faces[2].setSmGroup(4);

	mesh.InvalidateGeomCache();
}

