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
      bool setMinimumFullLoadElectricalPowerOutput(double minimumFullLoadElectricalPowerOutput);
      bool isMinimumFullLoadElectricalPowerOutputDefaulted() const;
      void resetMinimumFullLoadElectricalPowerOutput();

      double maximumFullLoadElectricalPowerOutput() const;
      bool setMaximumFullLoadElectricalPowerOutput(double maximumFullLoadElectricalPowerOutput);
      bool isMaximumFullLoadElectricalPowerOutputDefaulted() const;
      void resetMaximumFullLoadElectricalPowerOutput();

      double referenceElectricalEfficiencyUsingLowerHeatingValue() const;
      bool setReferenceElectricalEfficiencyUsingLowerHeatingValue(double referenceElectricalEfficiencyUsingLowerHeatingValue);

      double referenceCombustionAirInletTemperature() const;
      bool setReferenceCombustionAirInletTemperature(double referenceCombustionAirInletTemperature);
      bool isReferenceCombustionAirInletTemperatureDefaulted() const;
      void resetReferenceCombustionAirInletTemperature();

      double referenceCombustionAirInletHumidityRatio() const;
      bool setReferenceCombustionAirInletHumidityRatio(double referenceCombustionAirInletHumidityRatio);
      bool isReferenceCombustionAirInletHumidityRatioDefaulted() const;
      void resetReferenceCombustionAirInletHumidityRatio();

      double referenceElevation() const;
      bool setReferenceElevation(double referenceElevation);
      bool isReferenceElevationDefaulted() const;
      void resetReferenceElevation();

      std::string fuelType() const;
      bool setFuelType(const std::string& fuelType);
      bool isFuelTypeDefaulted() const;
      void resetFuelType();

      double fuelHigherHeatingValue() const;
      bool setFuelHigherHeatingValue(double fuelHigherHeatingValue);
      bool isFuelHigherHeatingValueDefaulted() const;
      void resetFuelHigherHeatingValue();

      double fuelLowerHeatingValue() const;
      bool setFuelLowerHeatingValue(double fuelLowerHeatingValue);
      bool isFuelLowerHeatingValueDefaulted() const;
      void resetFuelLowerHeatingValue();

      double standbyPower() const;
      bool setStandbyPower(double standbyPower);
      bool isStandbyPowerDefaulted() const;
      void resetStandbyPower();

      double ancillaryPower() const;
      bool setAncillaryPower(double ancillaryPower);
      bool isAncillaryPowerDefaulted() const;
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
