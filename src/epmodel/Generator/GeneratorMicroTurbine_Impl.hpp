/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GENERATORMICROTURBINE_IMPL_HPP
#define EPMODEL_GENERATORMICROTURBINE_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GeneratorMicroTurbine_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GeneratorMicroTurbine_Impl() override = default;

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

  std::vector<std::string> validFuelTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
