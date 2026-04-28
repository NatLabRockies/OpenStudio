#ifndef EPMODEL_SpaceLoadInstance_I
#define EPMODEL_SpaceLoadInstance_I

#ifdef SWIGPYTHON
  %module openstudioepmodelspaceloadinstance
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(ElectricEquipment, <epmodel/SpaceLoadInstance/ElectricEquipment.hpp>)
EPMODELOBJECT_WRAP(ElectricEquipmentITEAirCooled, <epmodel/SpaceLoadInstance/ElectricEquipmentITEAirCooled.hpp>)
EPMODELOBJECT_WRAP(GasEquipment, <epmodel/SpaceLoadInstance/GasEquipment.hpp>)
EPMODELOBJECT_WRAP(HotWaterEquipment, <epmodel/SpaceLoadInstance/HotWaterEquipment.hpp>)
EPMODELOBJECT_WRAP(SteamEquipment, <epmodel/SpaceLoadInstance/SteamEquipment.hpp>)
EPMODELOBJECT_WRAP(OtherEquipment, <epmodel/SpaceLoadInstance/OtherEquipment.hpp>)
EPMODELOBJECT_WRAP(Lights, <epmodel/SpaceLoadInstance/Lights.hpp>)
EPMODELOBJECT_WRAP(People, <epmodel/SpaceLoadInstance/People.hpp>)
EPMODELOBJECT_WRAP(WaterUseEquipment, <epmodel/SpaceLoadInstance/WaterUseEquipment.hpp>)

#endif
