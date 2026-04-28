/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PUMPCONSTANTSPEED_IMPL_HPP
#define EPMODEL_PUMPCONSTANTSPEED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {
  class Node;
  namespace detail {

    class EPMODEL_API PumpConstantSpeed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~PumpConstantSpeed_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

      boost::optional<double> ratedFlowRate() const;
      bool isRatedFlowRateAutosized() const;
      bool setRatedFlowRate(double ratedFlowRate);
      void resetRatedFlowRate();
      void autosizeRatedFlowRate();
      boost::optional<double> autosizedRatedFlowRate() const;

      double ratedPumpHead() const;
      bool isRatedPumpHeadDefaulted() const;
      bool setRatedPumpHead(double ratedPumpHead);
      void resetRatedPumpHead();

      boost::optional<double> ratedPowerConsumption() const;
      bool isRatedPowerConsumptionAutosized() const;
      bool setRatedPowerConsumption(double ratedPowerConsumption);
      void resetRatedPowerConsumption();
      void autosizeRatedPowerConsumption();
      boost::optional<double> autosizedRatedPowerConsumption() const;

      double motorEfficiency() const;
      bool isMotorEfficiencyDefaulted() const;
      bool setMotorEfficiency(double motorEfficiency);
      void resetMotorEfficiency();

      double fractionofMotorInefficienciestoFluidStream() const;
      bool isFractionofMotorInefficienciestoFluidStreamDefaulted() const;
      bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);
      void resetFractionofMotorInefficienciestoFluidStream();

      std::string pumpControlType() const;
      bool isPumpControlTypeDefaulted() const;
      bool setPumpControlType(const std::string& pumpControlType);
      void resetPumpControlType();

      boost::optional<double> impellerDiameter() const;
      bool setImpellerDiameter(double impellerDiameter);
      void resetImpellerDiameter();

      boost::optional<double> rotationalSpeed() const;
      bool setRotationalSpeed(double rotationalSpeed);
      void resetRotationalSpeed();

      boost::optional<double> skinLossRadiativeFraction() const;
      bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);
      void resetSkinLossRadiativeFraction();

      std::string designPowerSizingMethod() const;
      bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

      double designElectricPowerPerUnitFlowRate() const;
      bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);

      double designShaftPowerPerUnitFlowRatePerUnitHead() const;
      bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);

      std::string endUseSubcategory() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);

     private:
      bool m_isRatedFlowRateAutosized = true;
      bool m_isRatedPowerConsumptionAutosized = true;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
