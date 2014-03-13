#include "Lesson1b.h"

ClassDesc2* GetUtilitySampleDesc()
{ 
	static UtilitySampleClassDesc UtilitySampleDesc;
	return &UtilitySampleDesc; 
}

void SampleUtil::BeginEditParams(Interface* ip,IUtil* iu) 
{
	this->ip = ip;
	ip->PushPrompt(_M("Hello World from Lesson 1, created without using the Plugin Wizard."));
}

void SampleUtil::EndEditParams(Interface* ip,IUtil* iu) 
{
	this->ip = NULL;
	ip->PopPrompt();
}