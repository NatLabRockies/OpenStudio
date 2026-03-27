/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACHIGHTEMPERATURERADIANT_IMPL_HPP
#define EPMODEL_ZONEHVACHIGHTEMPERATURERADIANT_IMPL_HPP

#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneHVACHighTemperatureRadiant_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACHighTemperatureRadiant_Impl() override = default;

      unsigned inletPort() const;
      unsigned outletPort() const;

      boost::optional<double> maximumPowerInput() const;
      bool isMaximumPowerInputAutosized() const;
      bool setMaximumPowerInput(double maximumPowerInput);
      void autosizeMaximumPowerInput();

      std::string fuelType() const;
      bool isFuelTypeDefaulted() const;
      bool setFuelType(const std::string& fuelType);
      void resetFuelType();

      double combustionEfficiency() const;
      bool isCombustionEfficiencyDefaulted() const;
      bool setCombustionEfficiency(double combustionEfficiency);
      void resetCombustionEfficiency();

      double fractionofInputConvertedtoRadiantEnergy() const;
      bool isFractionofInputConvertedtoRadiantEnergyDefaulted() const;
      bool setFractionofInputConvertedtoRadiantEnergy(double fractionofInputConvertedtoRadiantEnergy);
      void resetFractionofInputConvertedtoRadiantEnergy();

      double fractionofInputConvertedtoLatentEnergy() const;
      bool isFractionofInputConvertedtoLatentEnergyDefaulted() const;
      bool setFractionofInputConvertedtoLatentEnergy(double fractionofInputConvertedtoLatentEnergy);
      void resetFractionofInputConvertedtoLatentEnergy();

      double fractionofInputthatIsLost() const;
      bool isFractionofInputthatIsLostDefaulted() const;
      bool setFractionofInputthatIsLost(double fractionofInputthatIsLost);
      void resetFractionofInputthatIsLost();

      std::string temperatureControlType() const;
      bool isTemperatureControlTypeDefaulted() const;
      bool setTemperatureControlType(const std::string& temperatureControlType);
      void resetTemperatureControlType();

      double heatingThrottlingRange() const;
      bool isHeatingThrottlingRangeDefaulted() const;
      bool setHeatingThrottlingRange(double heatingThrottlingRange);
      void resetHeatingThrottlingRange();

      double fractionofRadiantEnergyIncidentonPeople() const;
      bool setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
