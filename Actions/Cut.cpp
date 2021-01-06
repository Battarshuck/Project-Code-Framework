#include "Cut.h"
#include "..\ApplicationManager.h"

Cut::Cut(ApplicationManager* pApp, Component* CompSelected, Component*& CompcutAppMang, int*& CopyOrcut) : Action(pApp), CutComp(CompcutAppMang),CopyOrCut_ptr(CopyOrcut)
{
    ComponentToBeCut = CompSelected;
}

Cut::~Cut(void)
{}

void Cut::ReadActionParameters()
{}

void Cut::Execute()
{   
    Output* pOut = pManager->GetOutput();

    //Calculate the rectangle Corners
    if (ComponentToBeCut)
    {
        if (dynamic_cast<Connection*>(ComponentToBeCut))
        {
            pOut->PrintMsg("Error, Cannot Cut a Connection");
        }
        else 
        {
            CutComp = ComponentToBeCut;
            *CopyOrCut_ptr = 2;
            //Print Action Message
            pOut->PrintMsg("Cut a Componenet: Componenet is Cut");
        }
            
    }
    else
        pOut->PrintMsg("Cannot Cut, Please Select a Component first");
    
}

void Cut::Undo()
{}

void Cut::Redo()
{}