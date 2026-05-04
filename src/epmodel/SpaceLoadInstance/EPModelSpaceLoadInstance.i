#ifndef EPMODEL_SpaceLoadInstance_I
#define EPMODEL_SpaceLoadInstance_I

#ifdef SWIGPYTHON
  %module openstudioepmodelspaceloadinstance
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(ElectricEquipment, <epmodel/SpaceLoadInstance/ElectricEquipment.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ElectricEquipmentITEAirCooled, <epmodel/SpaceLoadInstance/ElectricEquipmentITEAirCooled.hpp>, 0, 1)
EPMODELOBJECT_WRAP(GasEquipment, <epmodel/SpaceLoadInstance/GasEquipment.hpp>, 0, 1)
EPMODELOBJECT_WRAP(HotWaterEquipment, <epmodel/SpaceLoadInstance/HotWaterEquipment.hpp>, 0, 1)
EPMODELOBJECT_WRAP(SteamEquipment, <epmodel/SpaceLoadInstance/SteamEquipment.hpp>, 0, 1)
EPMODELOBJECT_WRAP(OtherEquipment, <epmodel/SpaceLoadInstance/OtherEquipment.hpp>, 0, 1)
EPMODELOBJECT_WRAP(Lights, <epmodel/SpaceLoadInstance/Lights.hpp>, 0, 1)
EPMODELOBJECT_WRAP(People, <epmodel/SpaceLoadInstance/People.hpp>, 0, 1)
EPMODELOBJECT_WRAP(WaterUseEquipment, <epmodel/SpaceLoadInstance/WaterUseEquipment.hpp>, 0, 1)

#endif
