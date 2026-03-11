/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMECOOLEDBEAM_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMECOOLEDBEAM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirTerminalSingleDuctConstantVolumeCooledBeam_Impl;
}

class EPMODEL_API AirTerminalSingleDuctConstantVolumeCooledBeam : public ModelObject
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
  // - API: Preserve openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: cooledBeamType and N1-N7 scalar APIs map directly to E+ AirTerminal:SingleDuct:ConstantVolume:CooledBeam fields.
  // - Field Mapping: Availability Schedule Name, Cooling Coil Name, and all node name fields are relationship fields and are intentionally excluded.
  // - ForwardTranslator evidence: translateAirTerminalSingleDuctConstantVolumeCooledBeam writes these scalar fields directly.
  // - TODO(parity): Add relationship APIs incrementally after scalar scaffold saturation.
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
