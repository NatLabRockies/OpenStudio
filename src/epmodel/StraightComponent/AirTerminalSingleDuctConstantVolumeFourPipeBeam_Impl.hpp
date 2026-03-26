/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEBEAM_IMPL_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEBEAM_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

    class EPMODEL_API AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

  boost::optional<double> designPrimaryAirVolumeFlowRate() const;
  bool isDesignPrimaryAirVolumeFlowRateAutosized() const;
  bool setDesignPrimaryAirVolumeFlowRate(double designPrimaryAirVolumeFlowRate);
  void autosizeDesignPrimaryAirVolumeFlowRate();

  boost::optional<double> designChilledWaterVolumeFlowRate() const;
  bool isDesignChilledWaterVolumeFlowRateAutosized() const;
  bool setDesignChilledWaterVolumeFlowRate(double designChilledWaterVolumeFlowRate);
  void autosizeDesignChilledWaterVolumeFlowRate();

  boost::optional<double> designHotWaterVolumeFlowRate() const;
  bool isDesignHotWaterVolumeFlowRateAutosized() const;
  bool setDesignHotWaterVolumeFlowRate(double designHotWaterVolumeFlowRate);
  void autosizeDesignHotWaterVolumeFlowRate();

  boost::optional<double> zoneTotalBeamLength() const;
  bool isZoneTotalBeamLengthAutosized() const;
  bool setZoneTotalBeamLength(double zoneTotalBeamLength);
  void autosizeZoneTotalBeamLength();

  double ratedPrimaryAirFlowRateperBeamLength() const;
  bool isRatedPrimaryAirFlowRateperBeamLengthDefaulted() const;
  bool setRatedPrimaryAirFlowRateperBeamLength(double ratedPrimaryAirFlowRateperBeamLength);
  void resetRatedPrimaryAirFlowRateperBeamLength();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
