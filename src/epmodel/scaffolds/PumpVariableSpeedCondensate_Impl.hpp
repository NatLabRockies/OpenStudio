/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PUMPVARIABLESPEEDCONDENSATE_IMPL_HPP
#define EPMODEL_PUMPVARIABLESPEEDCONDENSATE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API PumpVariableSpeedCondensate_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~PumpVariableSpeedCondensate_Impl() override = default;

      boost::optional<double> designSteamVolumeFlowRate() const;
      bool isDesignSteamVolumeFlowRateAutosized() const;
      bool setDesignSteamVolumeFlowRate(double designSteamVolumeFlowRate);
      void resetDesignSteamVolumeFlowRate();
      void autosizeDesignSteamVolumeFlowRate();

      double designPumpHead() const;
      bool isDesignPumpHeadDefaulted() const;
      bool setDesignPumpHead(double designPumpHead);
      void resetDesignPumpHead();

      boost::optional<double> designPowerConsumption() const;
      bool isDesignPowerConsumptionAutosized() const;
      bool setDesignPowerConsumption(double designPowerConsumption);
      void resetDesignPowerConsumption();
      void autosizeDesignPowerConsumption();

      double motorEfficiency() const;
      bool isMotorEfficiencyDefaulted() const;
      bool setMotorEfficiency(double motorEfficiency);
      void resetMotorEfficiency();

      double fractionOfMotorInefficienciesToFluidStream() const;
      bool isFractionOfMotorInefficienciesToFluidStreamDefaulted() const;
      bool setFractionOfMotorInefficienciesToFluidStream(double fractionOfMotorInefficienciesToFluidStream);
      void resetFractionOfMotorInefficienciesToFluidStream();

      double coefficient1OfThePartLoadPerformanceCurve() const;
      bool isCoefficient1OfThePartLoadPerformanceCurveDefaulted() const;
      bool setCoefficient1OfThePartLoadPerformanceCurve(double coefficient1OfThePartLoadPerformanceCurve);
      void resetCoefficient1OfThePartLoadPerformanceCurve();

      double coefficient2OfThePartLoadPerformanceCurve() const;
      bool isCoefficient2OfThePartLoadPerformanceCurveDefaulted() const;
      bool setCoefficient2OfThePartLoadPerformanceCurve(double coefficient2OfThePartLoadPerformanceCurve);
      void resetCoefficient2OfThePartLoadPerformanceCurve();

      double coefficient3OfThePartLoadPerformanceCurve() const;
      bool isCoefficient3OfThePartLoadPerformanceCurveDefaulted() const;
      bool setCoefficient3OfThePartLoadPerformanceCurve(double coefficient3OfThePartLoadPerformanceCurve);
      void resetCoefficient3OfThePartLoadPerformanceCurve();

      double coefficient4OfThePartLoadPerformanceCurve() const;
      bool isCoefficient4OfThePartLoadPerformanceCurveDefaulted() const;
      bool setCoefficient4OfThePartLoadPerformanceCurve(double coefficient4OfThePartLoadPerformanceCurve);
      void resetCoefficient4OfThePartLoadPerformanceCurve();

      boost::optional<double> skinLossRadiativeFraction() const;
      bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);
      void resetSkinLossRadiativeFraction();

      std::string designPowerSizingMethod() const;
      bool isDesignPowerSizingMethodDefaulted() const;
      bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);
      void resetDesignPowerSizingMethod();

      double designElectricPowerPerUnitFlowRate() const;
      bool isDesignElectricPowerPerUnitFlowRateDefaulted() const;
      bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);
      void resetDesignElectricPowerPerUnitFlowRate();

      double designShaftPowerPerUnitFlowRatePerUnitHead() const;
      bool isDesignShaftPowerPerUnitFlowRatePerUnitHeadDefaulted() const;
      bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);
      void resetDesignShaftPowerPerUnitFlowRatePerUnitHead();

      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();

      std::vector<std::string> designPowerSizingMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
