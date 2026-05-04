#ifndef EPMODEL_ElectricalStorage_I
#define EPMODEL_ElectricalStorage_I

#ifdef SWIGPYTHON
  %module openstudioepmodelelectricalstorage
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(ElectricLoadCenterStorageSimple, <epmodel/ElectricalStorage/ElectricLoadCenterStorageSimple.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ElectricLoadCenterStorageLiIonNMCBattery, <epmodel/ElectricalStorage/ElectricLoadCenterStorageLiIonNMCBattery.hpp>, 0, 1)

#endif
