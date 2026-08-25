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

/** \brief A high-temperature radiant heater serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-radiative-convective-units.html#zonehvachightemperatureradiant,ZoneHVAC:HighTemperatureRadiant}
 *
 * \par Important behavior
 * Availability, fuel, efficiency, radiant/latent/lost fractions, temperature control, throttling, setpoint schedule, and thermal-zone methods are available.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACHighTemperatureRadiant</code>.
 *
 * \par Known limitations
 * Emitted per-surface weighting rows are not exposed as a separate public collection.
 */
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
