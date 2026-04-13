/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACHIGHTEMPERATURERADIANT_HPP
#define EPMODEL_ZONEHVACHIGHTEMPERATURERADIANT_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class ZoneHVACHighTemperatureRadiant_Impl;
  }

  class EPMODEL_API ZoneHVACHighTemperatureRadiant : public ZoneHVACComponent
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
    // - Status: Partial Parity. The scalar radiant fields are aligned, and epmodel now preserves the canonical public
    //   schedule API on top of the EnergyPlus-backed parent object.
    // - Canonical Counterpart: openstudio::model::ZoneHVACHighTemperatureRadiant.
    // - Implemented Parity: `availabilitySchedule`, `maximumPowerInput`, `fuelType`, `combustionEfficiency`, the
    //   radiant/latent/lost fractions, `temperatureControlType`, `heatingThrottlingRange`,
    //   `heatingSetpointTemperatureSchedule`, and `fractionofRadiantEnergyIncidentonPeople`.
    // - Field/Storage Mapping: Scalar values and schedules are stored directly on the EnergyPlus object.
    // - Evidence: `src/model/ZoneHVACHighTemperatureRadiant.hpp`, `src/model/ZoneHVACHighTemperatureRadiant.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACHighTemperatureRadiant.cpp`, and `src/epmodel/test/ZoneHVACHighTemperatureRadiant_GTest.cpp`.
    // - Remaining Parity Work: Revisit only if we later decide to surface the emitted EnergyPlus per-surface weighting rows directly.

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    boost::optional<double> maximumPowerInput() const;
    bool setMaximumPowerInput(double maximumPowerInput);
    bool isMaximumPowerInputAutosized() const;
    void autosizeMaximumPowerInput();
    boost::optional<double> autosizedMaximumPowerInput() const;

    std::string fuelType() const;
    bool setFuelType(const std::string& fuelType);
    bool isFuelTypeDefaulted() const;
    void resetFuelType();

    double combustionEfficiency() const;
    bool setCombustionEfficiency(double combustionEfficiency);
    bool isCombustionEfficiencyDefaulted() const;
    void resetCombustionEfficiency();

    double fractionofInputConvertedtoRadiantEnergy() const;
    bool setFractionofInputConvertedtoRadiantEnergy(double fractionofInputConvertedtoRadiantEnergy);
    bool isFractionofInputConvertedtoRadiantEnergyDefaulted() const;
    void resetFractionofInputConvertedtoRadiantEnergy();

    double fractionofInputConvertedtoLatentEnergy() const;
    bool setFractionofInputConvertedtoLatentEnergy(double fractionofInputConvertedtoLatentEnergy);
    bool isFractionofInputConvertedtoLatentEnergyDefaulted() const;
    void resetFractionofInputConvertedtoLatentEnergy();

    double fractionofInputthatIsLost() const;
    bool setFractionofInputthatIsLost(double fractionofInputthatIsLost);
    bool isFractionofInputthatIsLostDefaulted() const;
    void resetFractionofInputthatIsLost();

    std::string temperatureControlType() const;
    bool setTemperatureControlType(const std::string& temperatureControlType);
    bool isTemperatureControlTypeDefaulted() const;
    void resetTemperatureControlType();

    double heatingThrottlingRange() const;
    bool setHeatingThrottlingRange(double heatingThrottlingRange);
    bool isHeatingThrottlingRangeDefaulted() const;
    void resetHeatingThrottlingRange();

    boost::optional<Schedule> heatingSetpointTemperatureSchedule() const;
    bool setHeatingSetpointTemperatureSchedule(Schedule& schedule);
    void resetHeatingSetpointTemperatureSchedule();

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
