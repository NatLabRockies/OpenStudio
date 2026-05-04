#ifndef EPMODEL_SpaceLoad_I
#define EPMODEL_SpaceLoad_I

#ifdef SWIGPYTHON
  %module openstudioepmodelspaceload
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(SpaceInfiltrationDesignFlowRate, <epmodel/SpaceLoad/SpaceInfiltrationDesignFlowRate.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SpaceInfiltrationFlowCoefficient, <epmodel/SpaceLoad/SpaceInfiltrationFlowCoefficient.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SpaceInfiltrationEffectiveLeakageArea, <epmodel/SpaceLoad/SpaceInfiltrationEffectiveLeakageArea.hpp>, 0, 1)

#endif
