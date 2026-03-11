/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_PUMPVARIABLESPEED_IMPL_HPP
#define EPMODEL_PUMPVARIABLESPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API PumpVariableSpeed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~PumpVariableSpeed_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      std::vector<std::string> pumpControlTypeValues() const;
      std::vector<std::string> designPowerSizingMethodValues() const;
      std::vector<std::string> vfdControlTypeValues() const;

      boost::optional<double> ratedFlowRate() const;
      bool isRatedFlowRateDefaulted() const;
      bool isRatedFlowRateAutosized() const;

      double ratedPumpHead() const;
      bool isRatedPumpHeadDefaulted() const;

      boost::optional<double> ratedPowerConsumption() const;
      bool isRatedPowerConsumptionDefaulted() const;
      bool isRatedPowerConsumptionAutosized() const;

      double motorEfficiency() const;
      bool isMotorEfficiencyDefaulted() const;

      double fractionofMotorInefficienciestoFluidStream() const;
      bool isFractionofMotorInefficienciestoFluidStreamDefaulted() const;

      double coefficient1ofthePartLoadPerformanceCurve() const;
      bool isCoefficient1ofthePartLoadPerformanceCurveDefaulted() const;

      double coefficient2ofthePartLoadPerformanceCurve() const;
      bool isCoefficient2ofthePartLoadPerformanceCurveDefaulted() const;

      double coefficient3ofthePartLoadPerformanceCurve() const;
      bool isCoefficient3ofthePartLoadPerformanceCurveDefaulted() const;

      double coefficient4ofthePartLoadPerformanceCurve() const;
      bool isCoefficient4ofthePartLoadPerformanceCurveDefaulted() const;

      double minimumFlowRate() const;
      bool isMinimumFlowRateDefaulted() const;

      std::string pumpControlType() const;
      bool isPumpControlTypeDefaulted() const;

      boost::optional<double> impellerDiameter() const;

      boost::optional<std::string> vFDControlType() const;

      double skinLossRadiativeFraction() const;

      std::string designPowerSizingMethod() const;

      double designElectricPowerPerUnitFlowRate() const;

      double designShaftPowerPerUnitFlowRatePerUnitHead() const;

      double designMinimumFlowRateFraction() const;

      std::string endUseSubcategory() const;

      bool setRatedFlowRate(double ratedFlowRate);
      void resetRatedFlowRate();
      void autosizeRatedFlowRate();

      bool setRatedPumpHead(double ratedPumpHead);
      void resetRatedPumpHead();

      bool setRatedPowerConsumption(double ratedPowerConsumption);
      void resetRatedPowerConsumption();
      void autosizeRatedPowerConsumption();

      bool setMotorEfficiency(double motorEfficiency);
      void resetMotorEfficiency();

      bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);
      void resetFractionofMotorInefficienciestoFluidStream();

      bool setCoefficient1ofthePartLoadPerformanceCurve(double coefficient1ofthePartLoadPerformanceCurve);
      void resetCoefficient1ofthePartLoadPerformanceCurve();

      bool setCoefficient2ofthePartLoadPerformanceCurve(double coefficient2ofthePartLoadPerformanceCurve);
      void resetCoefficient2ofthePartLoadPerformanceCurve();

      bool setCoefficient3ofthePartLoadPerformanceCurve(double coefficient3ofthePartLoadPerformanceCurve);
      void resetCoefficient3ofthePartLoadPerformanceCurve();

      bool setCoefficient4ofthePartLoadPerformanceCurve(double coefficient4ofthePartLoadPerformanceCurve);
      void resetCoefficient4ofthePartLoadPerformanceCurve();

      bool setMinimumFlowRate(double minimumFlowRate);
      void resetMinimumFlowRate();

      bool setPumpControlType(const std::string& pumpControlType);
      void resetPumpControlType();

      bool setImpellerDiameter(double impellerDiameter);
      void resetImpellerDiameter();

      bool setVFDControlType(const std::string& vFDControlType);
      void resetVFDControlType();

      bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);

      bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);
      bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);
      bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);
      bool setDesignMinimumFlowRateFraction(double designMinimumFlowRateFraction);
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
