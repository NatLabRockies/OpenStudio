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
  // - Status: Scalar Parity. The four-pipe beam scalar surface is aligned, while schedule, node, coil, and curve helpers remain intentionally narrower.
  // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctConstantVolumeFourPipeBeam.
  // - Implemented Parity: `designPrimaryAirVolumeFlowRate`, `designChilledWaterVolumeFlowRate`, `designHotWaterVolumeFlowRate`, `zoneTotalBeamLength`, and `ratedPrimaryAirFlowRateperBeamLength` preserve the canonical scalar contract.
  // - Documented Delta: Schedule, node, coil, and curve helpers, plus coil-owned scalar fields, are not exposed as public methods yet.
  // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus `AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam` fields.
  // - Evidence: `src/model/AirTerminalSingleDuctConstantVolumeFourPipeBeam.hpp`, `src/model/AirTerminalSingleDuctConstantVolumeFourPipeBeam.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeFourPipeBeam.cpp`, and canonical equipment-list/topology behavior in `src/epmodel/test/IDF_SmallOffice_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted schedule, node, coil, and curve helpers when relationship parity expands.
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
