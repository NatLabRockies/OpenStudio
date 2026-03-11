/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACHIGHTEMPERATURERADIANT_HPP
#define EPMODEL_ZONEHVACHIGHTEMPERATURERADIANT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneHVACHighTemperatureRadiant_Impl;
  }

  class EPMODEL_API ZoneHVACHighTemperatureRadiant : public ModelObject
  {
   public:
    explicit ZoneHVACHighTemperatureRadiant(const Model& model);

    virtual ~ZoneHVACHighTemperatureRadiant() override = default;
    ZoneHVACHighTemperatureRadiant(const ZoneHVACHighTemperatureRadiant& other) = default;
    ZoneHVACHighTemperatureRadiant(ZoneHVACHighTemperatureRadiant&& other) = default;
    ZoneHVACHighTemperatureRadiant& operator=(const ZoneHVACHighTemperatureRadiant&) = default;
    ZoneHVACHighTemperatureRadiant& operator=(ZoneHVACHighTemperatureRadiant&&) = default;

    static IddObjectType iddObjectType();
    static std::vector<std::string> fuelTypeValues();
    static std::vector<std::string> temperatureControlTypeValues();

    // Schema Alignment Notes:
    // - API: maximumPowerInput, fuelType, combustionEfficiency, fractionofInputConvertedtoRadiantEnergy,
    //   fractionofInputConvertedtoLatentEnergy, fractionofInputthatIsLost, temperatureControlType,
    //   heatingThrottlingRange, and fractionofRadiantEnergyIncidentonPeople map directly to the EnergyPlus
    //   ZoneHVAC:HighTemperatureRadiant fields enumerated by ZoneHVAC_HighTemperatureRadiantFields in
    //   ForwardTranslateZoneHVACHighTemperatureRadiant.cpp; the translator also forces HeatingDesignCapacityMethod to
    //   "HeatingDesignCapacity" and routes scheduled relationships separately.
    // - Field Mapping: availability schedule, zone membership, heater schedule, and extensible surface groups stay
    //   relationship-only and are intentionally excluded from this scalar-focused API.

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

   protected:
    using ImplType = detail::ZoneHVACHighTemperatureRadiant_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACHighTemperatureRadiant(std::shared_ptr<detail::ZoneHVACHighTemperatureRadiant_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
