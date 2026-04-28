#ifndef EPMODEL_Inverter_I
#define EPMODEL_Inverter_I

#ifdef SWIGPYTHON
  %module openstudioepmodelinverter
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>

EPMODELOBJECT_WRAP(ElectricLoadCenterInverterLookUpTable, <epmodel/Inverter/ElectricLoadCenterInverterLookUpTable.hpp>)
EPMODELOBJECT_WRAP(ElectricLoadCenterInverterPVWatts, <epmodel/Inverter/ElectricLoadCenterInverterPVWatts.hpp>)
EPMODELOBJECT_WRAP(ElectricLoadCenterInverterSimple, <epmodel/Inverter/ElectricLoadCenterInverterSimple.hpp>)

#endif
