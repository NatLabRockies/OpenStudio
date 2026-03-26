/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEBEAM_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMEFOURPIPEBEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl;
}

class EPMODEL_API AirTerminalSingleDuctConstantVolumeFourPipeBeam : public StraightComponent
{
 public:
  explicit AirTerminalSingleDuctConstantVolumeFourPipeBeam(const Model& model);

  virtual ~AirTerminalSingleDuctConstantVolumeFourPipeBeam() override = default;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam(const AirTerminalSingleDuctConstantVolumeFourPipeBeam& other) = default;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam(AirTerminalSingleDuctConstantVolumeFourPipeBeam&& other) = default;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam& operator=(const AirTerminalSingleDuctConstantVolumeFourPipeBeam&) = default;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam& operator=(AirTerminalSingleDuctConstantVolumeFourPipeBeam&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: designPrimaryAirVolumeFlowRate, designChilledWaterVolumeFlowRate, designHotWaterVolumeFlowRate, zoneTotalBeamLength,
  //   and ratedPrimaryAirFlowRateperBeamLength map directly to E+ AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam N1-N5 fields.
  // - Field Mapping: schedule/node/coil/curve fields and coil-owned scalar fields are relationship fields and are intentionally excluded.
  // - ForwardTranslator evidence: translateAirTerminalSingleDuctConstantVolumeFourPipeBeam writes these scalar fields directly.
  // - TODO(parity): Add relationship and coil-coupled APIs incrementally after scalar scaffold saturation.
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

 protected:
  using ImplType = detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirTerminalSingleDuctConstantVolumeFourPipeBeam(std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
