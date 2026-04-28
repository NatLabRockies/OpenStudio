#ifndef EPMODEL_ConstructionBase_I
#define EPMODEL_ConstructionBase_I

#ifdef SWIGPYTHON
  %module openstudioepmodelconstructionbase
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(ConstructionAirBoundary, <epmodel/ConstructionBase/ConstructionAirBoundary.hpp>)
EPMODELOBJECT_WRAP(CFactorUndergroundWallConstruction, <epmodel/ConstructionBase/CFactorUndergroundWallConstruction.hpp>)
EPMODELOBJECT_WRAP(FFactorGroundFloorConstruction, <epmodel/ConstructionBase/FFactorGroundFloorConstruction.hpp>)

#endif
