#ifndef EPMODEL_Loop_I
#define EPMODEL_Loop_I

#ifdef SWIGPYTHON
  %module openstudioepmodelloop
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/ParentObject/EPModelParentObject.i>

EPMODELOBJECT_WRAP(Loop, <epmodel/Loop/Loop.hpp>)
EPMODELOBJECT_WRAP(AirLoopHVAC, <epmodel/Loop/AirLoopHVAC.hpp>)
EPMODELOBJECT_WRAP(PlantLoop, <epmodel/Loop/PlantLoop.hpp>)

#endif
