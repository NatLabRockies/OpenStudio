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
class ModelObject;
class Node;
class Schedule;

namespace detail {
class AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl;
}

class EPMODEL_API AirTerminalSingleDuctConstantVolumeFourPipeBeam : public StraightComponent
{
 public:
  explicit AirTerminalSingleDuctConstantVolumeFourPipeBeam(const Model& model);
  AirTerminalSingleDuctConstantVolumeFourPipeBeam(const Model& model, ModelObject& coolingCoil, ModelObject& heatingCoil);

  virtual ~AirTerminalSingleDuctConstantVolumeFourPipeBeam() override = default;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam(const AirTerminalSingleDuctConstantVolumeFourPipeBeam& other) = default;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam(AirTerminalSingleDuctConstantVolumeFourPipeBeam&& other) = default;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam& operator=(const AirTerminalSingleDuctConstantVolumeFourPipeBeam&) = default;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam& operator=(AirTerminalSingleDuctConstantVolumeFourPipeBeam&&) = default;

  static IddObjectType iddObjectType();
  bool addToNode(Node& node);

  // Schema Alignment Notes:
  // - Status: Partial Parity. The scalar surface is aligned, and the availability-schedule, coil, and current zone-branch insertion path are exposed,
  //   while the family-specific autosized-result helpers and broader canonical local-topology helpers remain intentionally narrower.
  // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctConstantVolumeFourPipeBeam.
  // - Implemented Parity: `primaryAirAvailabilitySchedule`, `coolingAvailabilitySchedule`, `heatingAvailabilitySchedule`, `setCoolingCoil`,
  //   `setHeatingCoil`, `addToNode`, `designPrimaryAirVolumeFlowRate`, `designChilledWaterVolumeFlowRate`, `designHotWaterVolumeFlowRate`,
  //   `zoneTotalBeamLength`, and `ratedPrimaryAirFlowRateperBeamLength` preserve the canonical field contract that is practical here.
  // - Documented Delta: The cooling and heating coils are surfaced as raw epmodel `ModelObject` targets because epmodel does not yet provide dedicated
  //   `CoilCoolingFourPipeBeam` / `CoilHeatingFourPipeBeam` wrappers; the underlying object lists still enforce the correct target types.
  // - Field/Storage Mapping: The availability schedules, coil targets, preserved scalars, and inherited straight-component inlet/outlet node fields all
  //   store directly on the EnergyPlus `AirTerminal:SingleDuct:ConstantVolume:FourPipeBeam` object. `addToNode` uses the current epmodel zone-branch path
  //   and registers the terminal on the owning thermal-zone equipment list when one is resolved.
  // - Evidence: `src/model/AirTerminalSingleDuctConstantVolumeFourPipeBeam.hpp`, `src/model/AirTerminalSingleDuctConstantVolumeFourPipeBeam.cpp`,
  //   `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeFourPipeBeam.cpp`, and the focused epmodel tests.
  // - Remaining Parity Work: Expose the family-specific autosized-result query helpers and the broader canonical local-topology helpers if shared
  //   infrastructure or dedicated wrappers later make them practical.
  Schedule primaryAirAvailabilitySchedule() const;
  bool setPrimaryAirAvailabilitySchedule(Schedule& schedule);

  Schedule coolingAvailabilitySchedule() const;
  bool setCoolingAvailabilitySchedule(Schedule& schedule);

  Schedule heatingAvailabilitySchedule() const;
  bool setHeatingAvailabilitySchedule(Schedule& schedule);

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

  boost::optional<ModelObject> coolingCoil() const;
  bool setCoolingCoil(ModelObject& coolingCoil);

  boost::optional<ModelObject> heatingCoil() const;
  bool setHeatingCoil(ModelObject& heatingCoil);

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
