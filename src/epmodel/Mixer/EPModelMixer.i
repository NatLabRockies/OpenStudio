#ifndef EPMODEL_Mixer_I
#define EPMODEL_Mixer_I

#ifdef SWIGPYTHON
  %module openstudioepmodelmixer
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/HVACComponent/EPModelHVACComponent.i>

EPMODELOBJECT_WRAP(Mixer, <epmodel/Mixer/Mixer.hpp>, 0, 0)
EPMODELOBJECT_WRAP(AirLoopHVACReturnPlenum, <epmodel/Mixer/AirLoopHVACReturnPlenum.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AirLoopHVACZoneMixer, <epmodel/Mixer/AirLoopHVACZoneMixer.hpp>, 0, 1)
EPMODELOBJECT_WRAP(ConnectorMixer, <epmodel/Mixer/ConnectorMixer.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AirTerminalDualDuctConstantVolume, <epmodel/Mixer/AirTerminalDualDuctConstantVolume.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AirTerminalDualDuctVAV, <epmodel/Mixer/AirTerminalDualDuctVAV.hpp>, 0, 1)
EPMODELOBJECT_WRAP(AirTerminalDualDuctVAVOutdoorAir, <epmodel/Mixer/AirTerminalDualDuctVAVOutdoorAir.hpp>, 0, 1)

#endif
