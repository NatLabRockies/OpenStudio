#ifndef EPMODEL_Loop_I
#define EPMODEL_Loop_I

#ifdef SWIGPYTHON
  %module openstudioepmodelloop
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/ParentObject/EPModelParentObject.i>
%import <epmodel/HVACComponent/EPModelHVACComponent.i>

%{
  #include <epmodel/Loop/AirLoopHVAC_Impl.hpp>
%}

EPMODELOBJECT_WRAP(Loop, <epmodel/Loop/Loop.hpp>, 0, 0)
EPMODELOBJECT_WRAP(AirLoopHVAC, <epmodel/Loop/AirLoopHVAC.hpp>, 0, 1)
EPMODELOBJECT_WRAP(PlantLoop, <epmodel/Loop/PlantLoop.hpp>, 0, 1)

#endif
