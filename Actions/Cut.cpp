#include "Cut.h"
#include "..\ApplicationManager.h"

Cut::Cut(ApplicationManager* pApp, Component* CompSelected, Component*& CompcutAppMang, int& CopyOrcut) : Action(pApp), CutComp(CompcutAppMang)
{
    ComponentToBeCut = CompSelected;
    copyorcut = CopyOrcut;
}

Cut::~Cut(void)
{}

void Cut::ReadActionParameters()
{
    //Get a Pointer to the Output Interfaces
    Output *pOut = pManager->GetOutput();

    //Print Action Message
    pOut->PrintMsg("Cut a Componenet: Componenet is Cut");

}

void Cut::Execute()
{
    //Get Center point of the Gate
    ReadActionParameters();
   
    Output* pOut = pManager->GetOutput();

    //Calculate the rectangle Corners
    if (ComponentToBeCut)
    {
        if (dynamic_cast<Connection*>(ComponentToBeCut))
        {
            pOut->PrintMsg("Error, Cannot Cut a Connection");
        }
        else
            CutComp = ComponentToBeCut;
    }
    else
        pOut->PrintMsg("Cannot Cut, Please Select a Component first");
    
    copyorcut = 2;
}

void Cut::Undo()
{}

void Cut::Redo()
{}