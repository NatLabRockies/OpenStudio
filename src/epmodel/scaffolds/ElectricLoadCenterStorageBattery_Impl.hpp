/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERSTORAGEBATTERY_IMPL_HPP
#define EPMODEL_ELECTRICLOADCENTERSTORAGEBATTERY_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ElectricLoadCenterStorageBattery_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ElectricLoadCenterStorageBattery_Impl() override = default;

      double radiativeFraction() const;
      bool isRadiativeFractionDefaulted() const;
      bool setRadiativeFraction(double radiativeFraction);
      void resetRadiativeFraction();

      int numberofBatteryModulesinParallel() const;
      bool isNumberofBatteryModulesinParallelDefaulted() const;
      bool setNumberofBatteryModulesinParallel(int numberofBatteryModulesinParallel);
      void resetNumberofBatteryModulesinParallel();

      int numberofBatteryModulesinSeries() const;
      bool isNumberofBatteryModulesinSeriesDefaulted() const;
      bool setNumberofBatteryModulesinSeries(int numberofBatteryModulesinSeries);
      void resetNumberofBatteryModulesinSeries();

      boost::optional<double> maximumModuleCapacity() const;
      bool setMaximumModuleCapacity(double maximumModuleCapacity);
      void resetMaximumModuleCapacity();

      double initialFractionalStateofCharge() const;
      bool isInitialFractionalStateofChargeDefaulted() const;
      bool setInitialFractionalStateofCharge(double initialFractionalStateofCharge);
      void resetInitialFractionalStateofCharge();

      boost::optional<double> fractionofAvailableChargeCapacity() const;
      bool setFractionofAvailableChargeCapacity(double fractionofAvailableChargeCapacity);
      void resetFractionofAvailableChargeCapacity();

      boost::optional<double> changeRatefromBoundChargetoAvailableCharge() const;
      bool setChangeRatefromBoundChargetoAvailableCharge(double changeRatefromBoundChargetoAvailableCharge);
      void resetChangeRatefromBoundChargetoAvailableCharge();

      boost::optional<double> fullyChargedModuleOpenCircuitVoltage() const;
      bool setFullyChargedModuleOpenCircuitVoltage(double fullyChargedModuleOpenCircuitVoltage);
      void resetFullyChargedModuleOpenCircuitVoltage();

      boost::optional<double> fullyDischargedModuleOpenCircuitVoltage() const;
      bool setFullyDischargedModuleOpenCircuitVoltage(double fullyDischargedModuleOpenCircuitVoltage);
      void resetFullyDischargedModuleOpenCircuitVoltage();

      boost::optional<double> moduleInternalElectricalResistance() const;
      bool setModuleInternalElectricalResistance(double moduleInternalElectricalResistance);
      void resetModuleInternalElectricalResistance();

      boost::optional<double> maximumModuleDischargingCurrent() const;
      bool setMaximumModuleDischargingCurrent(double maximumModuleDischargingCurrent);
      void resetMaximumModuleDischargingCurrent();

      boost::optional<double> moduleCutoffVoltage() const;
      bool setModuleCutoffVoltage(double moduleCutoffVoltage);
      void resetModuleCutoffVoltage();

      double moduleChargeRateLimit() const;
      bool isModuleChargeRateLimitDefaulted() const;
      bool setModuleChargeRateLimit(double moduleChargeRateLimit);
      void resetModuleChargeRateLimit();

      bool batteryLifeCalculation() const;
      bool isBatteryLifeCalculationDefaulted() const;
      bool setBatteryLifeCalculation(bool batteryLifeCalculation);
      void resetBatteryLifeCalculation();

      int numberofCycleBins() const;
      bool isNumberofCycleBinsDefaulted() const;
      bool setNumberofCycleBins(int numberofCycleBins);
      void resetNumberofCycleBins();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
