#include"Undo.h"
#include "..\ApplicationManager.h"

undo::undo(ApplicationManager* pApp) :Action(pApp)
{
}

undo::~undo(void)
 {

 }

 void undo::Execute()
 {
	 Output* pOut = pManager->GetOutput();
	 
	 pManager->undofn();
 }

 void undo::ReadActionParameters()
 {

 }
 void undo::Undo()
 {

 }
 void undo::Redo()
 {

 }