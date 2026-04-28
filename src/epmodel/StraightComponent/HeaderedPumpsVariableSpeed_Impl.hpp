/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEADEREDPUMPSVARIABLESPEED_IMPL_HPP
#define EPMODEL_HEADEREDPUMPSVARIABLESPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API HeaderedPumpsVariableSpeed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~HeaderedPumpsVariableSpeed_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

      boost::optional<double> totalRatedFlowRate() const;
      bool isTotalRatedFlowRateAutosized() const;
      bool setTotalRatedFlowRate(double totalRatedFlowRate);
      void autosizeTotalRatedFlowRate();
      boost::optional<double> autosizedTotalRatedFlowRate() const;

      int numberofPumpsinBank() const;
      bool setNumberofPumpsinBank(int numberofPumpsinBank);

      std::string flowSequencingControlScheme() const;
      bool setFlowSequencingControlScheme(const std::string& flowSequencingControlScheme);

      double ratedPumpHead() const;
      bool setRatedPumpHead(double ratedPumpHead);

      boost::optional<double> ratedPowerConsumption() const;
      bool isRatedPowerConsumptionAutosized() const;
      bool setRatedPowerConsumption(double ratedPowerConsumption);
      void autosizeRatedPowerConsumption();
      boost::optional<double> autosizedRatedPowerConsumption() const;

      double motorEfficiency() const;
      bool setMotorEfficiency(double motorEfficiency);

      double fractionofMotorInefficienciestoFluidStream() const;
      bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);

      double coefficient1ofthePartLoadPerformanceCurve() const;
      bool setCoefficient1ofthePartLoadPerformanceCurve(double coefficient1ofthePartLoadPerformanceCurve);

      double coefficient2ofthePartLoadPerformanceCurve() const;
      bool setCoefficient2ofthePartLoadPerformanceCurve(double coefficient2ofthePartLoadPerformanceCurve);

      double coefficient3ofthePartLoadPerformanceCurve() const;
      bool setCoefficient3ofthePartLoadPerformanceCurve(double coefficient3ofthePartLoadPerformanceCurve);

      double coefficient4ofthePartLoadPerformanceCurve() const;
      bool setCoefficient4ofthePartLoadPerformanceCurve(double coefficient4ofthePartLoadPerformanceCurve);

      double minimumFlowRateFraction() const;
      bool setMinimumFlowRateFraction(double minimumFlowRateFraction);

      std::string pumpControlType() const;
      bool setPumpControlType(const std::string& pumpControlType);

      double skinLossRadiativeFraction() const;
      bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);

      std::string designPowerSizingMethod() const;
      bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

      double designElectricPowerPerUnitFlowRate() const;
      bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);

      double designShaftPowerPerUnitFlowRatePerUnitHead() const;
      bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);

      std::string endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
