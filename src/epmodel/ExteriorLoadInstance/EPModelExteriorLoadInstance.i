#ifndef EPMODEL_ExteriorLoadInstance_I
#define EPMODEL_ExteriorLoadInstance_I

#ifdef SWIGPYTHON
  %module openstudioepmodelexteriorloadinstance
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(ExteriorLights, <epmodel/ExteriorLoadInstance/ExteriorLights.hpp>)
EPMODELOBJECT_WRAP(ExteriorFuelEquipment, <epmodel/ExteriorLoadInstance/ExteriorFuelEquipment.hpp>)
EPMODELOBJECT_WRAP(ExteriorWaterEquipment, <epmodel/ExteriorLoadInstance/ExteriorWaterEquipment.hpp>)

#endif
