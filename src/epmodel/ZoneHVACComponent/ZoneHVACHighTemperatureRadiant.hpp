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
    // - Status: Partial Parity. The scalar radiant fields are aligned, but zone and surface relationships remain separate.
    // - Canonical Counterpart: openstudio::model::ZoneHVACHighTemperatureRadiant.
    // - Implemented Parity: `maximumPowerInput`, `fuelType`, `combustionEfficiency`, the radiant/latent/lost fractions, `temperatureControlType`, `heatingThrottlingRange`, and `fractionofRadiantEnergyIncidentonPeople` map directly to the EnergyPlus object.
    // - Documented Delta: Availability schedule, zone membership, heater schedule, and extensible surface groups remain relationship-only.
    // - Field/Storage Mapping: Scalar values are stored directly on the EnergyPlus object, while zone and surface membership are maintained through topology and child-object state.
    // - Evidence: `src/model/ZoneHVACHighTemperatureRadiant.hpp`, `src/model/ZoneHVACHighTemperatureRadiant.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACHighTemperatureRadiant.cpp`, and `src/epmodel/test/ZoneHVACHighTemperatureRadiant_GTest.cpp`.
    // - Remaining Parity Work: Add any missing relationship helpers only if the canonical wrapper still exposes them directly.

    boost::optional<double> maximumPowerInput() const;
    bool setMaximumPowerInput(double maximumPowerInput);
    bool isMaximumPowerInputAutosized() const;
    void autosizeMaximumPowerInput();

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
