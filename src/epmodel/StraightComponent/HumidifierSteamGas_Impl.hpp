/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HUMIDIFIERSTEAMGAS_IMPL_HPP
#define EPMODEL_HUMIDIFIERSTEAMGAS_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  class Node;
  class Schedule;
  namespace detail {

    class EPMODEL_API HumidifierSteamGas_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~HumidifierSteamGas_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      bool addToNode(Node& node) override;

      boost::optional<Schedule> availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);
      void resetAvailabilitySchedule();

      // Rated Capacity
      boost::optional<double> ratedCapacity() const;
      bool isRatedCapacityAutosized() const;
      bool setRatedCapacity(double ratedCapacity);
      void autosizeRatedCapacity();
      boost::optional<double> autosizedRatedCapacity() const;

      // Rated Gas Use Rate
      boost::optional<double> ratedGasUseRate() const;
      bool isRatedGasUseRateAutosized() const;
      bool setRatedGasUseRate(double ratedGasUseRate);
      void resetRatedGasUseRate();
      void autosizeRatedGasUseRate();
      boost::optional<double> autosizedRatedGasUseRate() const;

      // Thermal Efficiency
      double thermalEfficiency() const;
      bool isThermalEfficiencyDefaulted() const;
      bool setThermalEfficiency(double thermalEfficiency);
      void resetThermalEfficiency();

      // Rated Fan Power
      boost::optional<double> ratedFanPower() const;
      bool setRatedFanPower(double ratedFanPower);
      void resetRatedFanPower();

      // Auxiliary Electric Power
      double auxiliaryElectricPower() const;
      bool isAuxiliaryElectricPowerDefaulted() const;
      bool setAuxiliaryElectricPower(double auxiliaryElectricPower);
      void resetAuxiliaryElectricPower();

      // Inlet Water Temperature Option
      std::string inletWaterTemperatureOption() const;
      bool isInletWaterTemperatureOptionDefaulted() const;
      bool setInletWaterTemperatureOption(const std::string& inletWaterTemperatureOption);
      void resetInletWaterTemperatureOption();

      std::vector<std::string> inletWaterTemperatureOptionValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
