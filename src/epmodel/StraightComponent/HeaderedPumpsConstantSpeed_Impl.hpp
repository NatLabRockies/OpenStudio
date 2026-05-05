/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_HEADEREDPUMPSCONSTANTSPEED_IMPL_HPP
#define EPMODEL_HEADEREDPUMPSCONSTANTSPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API HeaderedPumpsConstantSpeed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~HeaderedPumpsConstantSpeed_Impl() override = default;

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
