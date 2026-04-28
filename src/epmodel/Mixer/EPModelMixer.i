#ifndef EPMODEL_Mixer_I
#define EPMODEL_Mixer_I

#ifdef SWIGPYTHON
  %module openstudioepmodelmixer
#endif

%include <epmodel/EPModel_Common_Include.i>
%import <epmodel/EPModel.i>
%import <epmodel/HVACComponent/EPModelHVACComponent.i>

EPMODELOBJECT_WRAP(Mixer, <epmodel/Mixer/Mixer.hpp>)
EPMODELOBJECT_WRAP(AirLoopHVACReturnPlenum, <epmodel/Mixer/AirLoopHVACReturnPlenum.hpp>)
EPMODELOBJECT_WRAP(AirLoopHVACZoneMixer, <epmodel/Mixer/AirLoopHVACZoneMixer.hpp>)
EPMODELOBJECT_WRAP(ConnectorMixer, <epmodel/Mixer/ConnectorMixer.hpp>)
EPMODELOBJECT_WRAP(AirTerminalDualDuctConstantVolume, <epmodel/Mixer/AirTerminalDualDuctConstantVolume.hpp>)
EPMODELOBJECT_WRAP(AirTerminalDualDuctVAV, <epmodel/Mixer/AirTerminalDualDuctVAV.hpp>)
EPMODELOBJECT_WRAP(AirTerminalDualDuctVAVOutdoorAir, <epmodel/Mixer/AirTerminalDualDuctVAVOutdoorAir.hpp>)

#endif
