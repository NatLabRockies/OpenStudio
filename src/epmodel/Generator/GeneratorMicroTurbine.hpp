/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORMICROTURBINE_HPP
#define EPMODEL_GENERATORMICROTURBINE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GeneratorMicroTurbine_Impl;
}

class EPMODEL_API GeneratorMicroTurbine : public ModelObject
{
 public:
  explicit GeneratorMicroTurbine(const Model& model);

  virtual ~GeneratorMicroTurbine() override = default;
  GeneratorMicroTurbine(const GeneratorMicroTurbine& other) = default;
  GeneratorMicroTurbine(GeneratorMicroTurbine&& other) = default;
  GeneratorMicroTurbine& operator=(const GeneratorMicroTurbine&) = default;
  GeneratorMicroTurbine& operator=(GeneratorMicroTurbine&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> validFuelTypeValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::GeneratorMicroTurbine scalar accessor names/signatures.
  // - Field Mapping: Preserved scalar APIs map directly to EnergyPlus Generator:MicroTurbine scalar fields.
  // - Field Mapping: maximumFullLoadElectricalPowerOutput preserves model fallback behavior and delegates to
  //   Reference Electrical Power Output when the E+ field is blank.
  // - API: GeneratorMicroTurbineHeatRecovery-linked scalar semantics remain on the counterpart heat-recovery class.
  // - Field Mapping: ForwardTranslateGeneratorMicroTurbine evidence shows heat-recovery scalar fields are populated
  //   from GeneratorMicroTurbineHeatRecovery and are excluded from this scalar-only pass.
  // - TODO(parity): Add excluded relationship and heat-recovery-linked APIs in a dedicated parity pass.
  double referenceElectricalPowerOutput() const;
  bool setReferenceElectricalPowerOutput(double referenceElectricalPowerOutput);

  double minimumFullLoadElectricalPowerOutput() const;
  bool isMinimumFullLoadElectricalPowerOutputDefaulted() const;
  bool setMinimumFullLoadElectricalPowerOutput(double minimumFullLoadElectricalPowerOutput);
  void resetMinimumFullLoadElectricalPowerOutput();

  double maximumFullLoadElectricalPowerOutput() const;
  bool isMaximumFullLoadElectricalPowerOutputDefaulted() const;
  bool setMaximumFullLoadElectricalPowerOutput(double maximumFullLoadElectricalPowerOutput);
  void resetMaximumFullLoadElectricalPowerOutput();

  double referenceElectricalEfficiencyUsingLowerHeatingValue() const;
  bool setReferenceElectricalEfficiencyUsingLowerHeatingValue(double referenceElectricalEfficiencyUsingLowerHeatingValue);

  double referenceCombustionAirInletTemperature() const;
  bool isReferenceCombustionAirInletTemperatureDefaulted() const;
  bool setReferenceCombustionAirInletTemperature(double referenceCombustionAirInletTemperature);
  void resetReferenceCombustionAirInletTemperature();

  double referenceCombustionAirInletHumidityRatio() const;
  bool isReferenceCombustionAirInletHumidityRatioDefaulted() const;
  bool setReferenceCombustionAirInletHumidityRatio(double referenceCombustionAirInletHumidityRatio);
  void resetReferenceCombustionAirInletHumidityRatio();

  double referenceElevation() const;
  bool isReferenceElevationDefaulted() const;
  bool setReferenceElevation(double referenceElevation);
  void resetReferenceElevation();

  std::string fuelType() const;
  bool isFuelTypeDefaulted() const;
  bool setFuelType(const std::string& fuelType);
  void resetFuelType();

  double fuelHigherHeatingValue() const;
  bool isFuelHigherHeatingValueDefaulted() const;
  bool setFuelHigherHeatingValue(double fuelHigherHeatingValue);
  void resetFuelHigherHeatingValue();

  double fuelLowerHeatingValue() const;
  bool isFuelLowerHeatingValueDefaulted() const;
  bool setFuelLowerHeatingValue(double fuelLowerHeatingValue);
  void resetFuelLowerHeatingValue();

  double standbyPower() const;
  bool isStandbyPowerDefaulted() const;
  bool setStandbyPower(double standbyPower);
  void resetStandbyPower();

  double ancillaryPower() const;
  bool isAncillaryPowerDefaulted() const;
  bool setAncillaryPower(double ancillaryPower);
  void resetAncillaryPower();

  boost::optional<double> referenceExhaustAirMassFlowRate() const;
  bool setReferenceExhaustAirMassFlowRate(double referenceExhaustAirMassFlowRate);
  void resetReferenceExhaustAirMassFlowRate();

  boost::optional<double> nominalExhaustAirOutletTemperature() const;
  bool setNominalExhaustAirOutletTemperature(double nominalExhaustAirOutletTemperature);
  void resetNominalExhaustAirOutletTemperature();

 protected:
  using ImplType = detail::GeneratorMicroTurbine_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GeneratorMicroTurbine(std::shared_ptr<detail::GeneratorMicroTurbine_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
