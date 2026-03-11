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
  namespace detail {

    class EPMODEL_API PumpConstantSpeed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~PumpConstantSpeed_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      boost::optional<double> ratedFlowRate() const;
      bool isRatedFlowRateAutosized() const;

      double ratedPumpHead() const;
      bool isRatedPumpHeadDefaulted() const;

      boost::optional<double> ratedPowerConsumption() const;
      bool isRatedPowerConsumptionAutosized() const;

      double motorEfficiency() const;
      bool isMotorEfficiencyDefaulted() const;

      double fractionofMotorInefficienciestoFluidStream() const;
      bool isFractionofMotorInefficienciestoFluidStreamDefaulted() const;

      std::string pumpControlType() const;
      bool isPumpControlTypeDefaulted() const;

      boost::optional<double> impellerDiameter() const;
      boost::optional<double> rotationalSpeed() const;
      boost::optional<double> skinLossRadiativeFraction() const;

      std::string designPowerSizingMethod() const;
      double designElectricPowerPerUnitFlowRate() const;
      double designShaftPowerPerUnitFlowRatePerUnitHead() const;
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

      bool setPumpControlType(const std::string& pumpControlType);
      void resetPumpControlType();

      bool setImpellerDiameter(double impellerDiameter);
      void resetImpellerDiameter();

      bool setRotationalSpeed(double rotationalSpeed);
      void resetRotationalSpeed();

      bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);
      void resetSkinLossRadiativeFraction();

      bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);
      bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);
      bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);
      bool setEndUseSubcategory(const std::string& endUseSubcategory);

      boost::optional<double> autosizedRatedFlowRate() const;
      boost::optional<double> autosizedRatedPowerConsumption() const;

     private:
      bool m_isRatedFlowRateAutosized = true;
      bool m_isRatedPowerConsumptionAutosized = true;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
