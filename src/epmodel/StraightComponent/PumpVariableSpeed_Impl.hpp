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
      bool addToNode(Node& node) override;

      std::vector<std::string> pumpControlTypeValues() const;
      std::vector<std::string> designPowerSizingMethodValues() const;
      std::vector<std::string> vfdControlTypeValues() const;

      boost::optional<double> ratedFlowRate() const;
      bool isRatedFlowRateDefaulted() const;
      bool isRatedFlowRateAutosized() const;
      bool setRatedFlowRate(double ratedFlowRate);
      void resetRatedFlowRate();
      void autosizeRatedFlowRate();

      double ratedPumpHead() const;
      bool isRatedPumpHeadDefaulted() const;
      bool setRatedPumpHead(double ratedPumpHead);
      void resetRatedPumpHead();

      boost::optional<double> ratedPowerConsumption() const;
      bool isRatedPowerConsumptionDefaulted() const;
      bool isRatedPowerConsumptionAutosized() const;
      bool setRatedPowerConsumption(double ratedPowerConsumption);
      void resetRatedPowerConsumption();
      void autosizeRatedPowerConsumption();

      double motorEfficiency() const;
      bool isMotorEfficiencyDefaulted() const;
      bool setMotorEfficiency(double motorEfficiency);
      void resetMotorEfficiency();

      double fractionofMotorInefficienciestoFluidStream() const;
      bool isFractionofMotorInefficienciestoFluidStreamDefaulted() const;
      bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);
      void resetFractionofMotorInefficienciestoFluidStream();

      double coefficient1ofthePartLoadPerformanceCurve() const;
      bool isCoefficient1ofthePartLoadPerformanceCurveDefaulted() const;
      bool setCoefficient1ofthePartLoadPerformanceCurve(double coefficient1ofthePartLoadPerformanceCurve);
      void resetCoefficient1ofthePartLoadPerformanceCurve();

      double coefficient2ofthePartLoadPerformanceCurve() const;
      bool isCoefficient2ofthePartLoadPerformanceCurveDefaulted() const;
      bool setCoefficient2ofthePartLoadPerformanceCurve(double coefficient2ofthePartLoadPerformanceCurve);
      void resetCoefficient2ofthePartLoadPerformanceCurve();

      double coefficient3ofthePartLoadPerformanceCurve() const;
      bool isCoefficient3ofthePartLoadPerformanceCurveDefaulted() const;
      bool setCoefficient3ofthePartLoadPerformanceCurve(double coefficient3ofthePartLoadPerformanceCurve);
      void resetCoefficient3ofthePartLoadPerformanceCurve();

      double coefficient4ofthePartLoadPerformanceCurve() const;
      bool isCoefficient4ofthePartLoadPerformanceCurveDefaulted() const;
      bool setCoefficient4ofthePartLoadPerformanceCurve(double coefficient4ofthePartLoadPerformanceCurve);
      void resetCoefficient4ofthePartLoadPerformanceCurve();

      double minimumFlowRate() const;
      bool isMinimumFlowRateDefaulted() const;
      bool setMinimumFlowRate(double minimumFlowRate);
      void resetMinimumFlowRate();

      std::string pumpControlType() const;
      bool isPumpControlTypeDefaulted() const;
      bool setPumpControlType(const std::string& pumpControlType);
      void resetPumpControlType();

      boost::optional<double> impellerDiameter() const;
      bool setImpellerDiameter(double impellerDiameter);
      void resetImpellerDiameter();

      boost::optional<std::string> vFDControlType() const;
      bool setVFDControlType(const std::string& vFDControlType);
      void resetVFDControlType();

      double skinLossRadiativeFraction() const;
      bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);

      std::string designPowerSizingMethod() const;
      bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

      double designElectricPowerPerUnitFlowRate() const;
      bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);

      double designShaftPowerPerUnitFlowRatePerUnitHead() const;
      bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);

      double designMinimumFlowRateFraction() const;
      bool setDesignMinimumFlowRateFraction(double designMinimumFlowRateFraction);

      std::string endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
