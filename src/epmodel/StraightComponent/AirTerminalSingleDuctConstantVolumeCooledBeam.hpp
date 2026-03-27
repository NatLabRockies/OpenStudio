/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMECOOLEDBEAM_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMECOOLEDBEAM_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirTerminalSingleDuctConstantVolumeCooledBeam_Impl;
}

class EPMODEL_API AirTerminalSingleDuctConstantVolumeCooledBeam : public StraightComponent
{
 public:
  explicit AirTerminalSingleDuctConstantVolumeCooledBeam(const Model& model);

  virtual ~AirTerminalSingleDuctConstantVolumeCooledBeam() override = default;
  AirTerminalSingleDuctConstantVolumeCooledBeam(const AirTerminalSingleDuctConstantVolumeCooledBeam& other) = default;
  AirTerminalSingleDuctConstantVolumeCooledBeam(AirTerminalSingleDuctConstantVolumeCooledBeam&& other) = default;
  AirTerminalSingleDuctConstantVolumeCooledBeam& operator=(const AirTerminalSingleDuctConstantVolumeCooledBeam&) = default;
  AirTerminalSingleDuctConstantVolumeCooledBeam& operator=(AirTerminalSingleDuctConstantVolumeCooledBeam&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> cooledBeamTypeValues();

  // Schema Alignment Notes:
  // - Status: Scalar Parity. The cooled-beam scalar surface is aligned, while the schedule, coil, and node-link surface remains intentionally narrower.
  // - Canonical Counterpart: openstudio::model::AirTerminalSingleDuctConstantVolumeCooledBeam.
  // - Implemented Parity: `cooledBeamType`, `supplyAirVolumetricFlowRate`, `maximumTotalChilledWaterVolumetricFlowRate`, `numberofBeams`, `beamLength`, `designInletWaterTemperature`, `designOutletWaterTemperature`, and `coefficientofInductionKin` preserve the canonical scalar contract with matching autosize/autocalculate behavior.
  // - Documented Delta: Availability schedule, cooling-coil, and node-link accessors are not exposed as public methods yet.
  // - Field/Storage Mapping: The preserved scalars map directly to EnergyPlus `AirTerminal:SingleDuct:ConstantVolume:CooledBeam` fields.
  // - Evidence: `src/model/AirTerminalSingleDuctConstantVolumeCooledBeam.hpp`, `src/model/AirTerminalSingleDuctConstantVolumeCooledBeam.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirTerminalSingleDuctConstantVolumeCooledBeam.cpp`, and `src/epmodel/test/AirTerminalSingleDuctConstantVolumeCooledBeam_GTest.cpp`.
  // - Remaining Parity Work: Add the omitted schedule, coil, and node-link helpers when relationship parity expands.
  std::string cooledBeamType() const;
  bool setCooledBeamType(const std::string& cooledBeamType);

  boost::optional<double> supplyAirVolumetricFlowRate() const;
  bool isSupplyAirVolumetricFlowRateDefaulted() const;
  bool isSupplyAirVolumetricFlowRateAutosized() const;
  bool setSupplyAirVolumetricFlowRate(double supplyAirVolumetricFlowRate);
  void resetSupplyAirVolumetricFlowRate();
  void autosizeSupplyAirVolumetricFlowRate();

  boost::optional<double> maximumTotalChilledWaterVolumetricFlowRate() const;
  bool isMaximumTotalChilledWaterVolumetricFlowRateDefaulted() const;
  bool isMaximumTotalChilledWaterVolumetricFlowRateAutosized() const;
  bool setMaximumTotalChilledWaterVolumetricFlowRate(double maximumTotalChilledWaterVolumetricFlowRate);
  void resetMaximumTotalChilledWaterVolumetricFlowRate();
  void autosizeMaximumTotalChilledWaterVolumetricFlowRate();

  boost::optional<int> numberofBeams() const;
  bool isNumberofBeamsDefaulted() const;
  bool isNumberofBeamsAutosized() const;
  bool setNumberofBeams(int numberofBeams);
  void resetNumberofBeams();
  void autosizeNumberofBeams();

  boost::optional<double> beamLength() const;
  bool isBeamLengthDefaulted() const;
  bool isBeamLengthAutosized() const;
  bool setBeamLength(double beamLength);
  void resetBeamLength();
  void autosizeBeamLength();

  double designInletWaterTemperature() const;
  bool isDesignInletWaterTemperatureDefaulted() const;
  bool setDesignInletWaterTemperature(double designInletWaterTemperature);
  void resetDesignInletWaterTemperature();

  double designOutletWaterTemperature() const;
  bool isDesignOutletWaterTemperatureDefaulted() const;
  bool setDesignOutletWaterTemperature(double designOutletWaterTemperature);
  void resetDesignOutletWaterTemperature();

  boost::optional<double> coefficientofInductionKin() const;
  bool isCoefficientofInductionKinDefaulted() const;
  bool isCoefficientofInductionKinAutocalculated() const;
  bool setCoefficientofInductionKin(double coefficientofInductionKin);
  void resetCoefficientofInductionKin();
  void autocalculateCoefficientofInductionKin();

protected:
  using ImplType = detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirTerminalSingleDuctConstantVolumeCooledBeam(std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
