#ifndef EPMODEL_Splitter_I
#define EPMODEL_Splitter_I

#ifdef SWIGPYTHON
  %module openstudioepmodelsplitter
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/HVACComponent/EPModelHVACComponent.i>

EPMODELOBJECT_WRAP(Splitter, <epmodel/Splitter/Splitter.hpp>, 0, 0)
EPMODELOBJECT_WRAP(AirLoopHVACSupplyPlenum, <epmodel/Splitter/AirLoopHVACSupplyPlenum.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AirLoopHVACZoneSplitter, <epmodel/Splitter/AirLoopHVACZoneSplitter.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ConnectorSplitter, <epmodel/Splitter/ConnectorSplitter.hpp>, 0, 1)

#endif
