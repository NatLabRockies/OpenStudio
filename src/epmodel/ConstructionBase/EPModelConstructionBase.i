#ifndef EPMODEL_ConstructionBase_I
#define EPMODEL_ConstructionBase_I

#ifdef SWIGPYTHON
  %module openstudioepmodelconstructionbase
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(ConstructionBase, <epmodel/ConstructionBase/ConstructionBase.hpp>, 0, 0)
EPMODELOBJECT_WRAP(ConstructionAirBoundary, <epmodel/ConstructionBase/ConstructionAirBoundary.hpp>, 0, 1)
EPMODELOBJECT_WRAP(CFactorUndergroundWallConstruction, <epmodel/ConstructionBase/CFactorUndergroundWallConstruction.hpp>, 0, 1)
EPMODELOBJECT_WRAP(FFactorGroundFloorConstruction, <epmodel/ConstructionBase/FFactorGroundFloorConstruction.hpp>, 0, 1)

#endif
