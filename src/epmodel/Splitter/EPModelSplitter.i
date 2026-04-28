#ifndef EPMODEL_Splitter_I
#define EPMODEL_Splitter_I

#ifdef SWIGPYTHON
  %module openstudioepmodelsplitter
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/HVACComponent/EPModelHVACComponent.i>

EPMODELOBJECT_WRAP(Splitter, <epmodel/Splitter/Splitter.hpp>)
EPMODELOBJECT_WRAP(AirLoopHVACSupplyPlenum, <epmodel/Splitter/AirLoopHVACSupplyPlenum.hpp>)
EPMODELOBJECT_WRAP(AirLoopHVACZoneSplitter, <epmodel/Splitter/AirLoopHVACZoneSplitter.hpp>)
EPMODELOBJECT_WRAP(ConnectorSplitter, <epmodel/Splitter/ConnectorSplitter.hpp>)

#endif
