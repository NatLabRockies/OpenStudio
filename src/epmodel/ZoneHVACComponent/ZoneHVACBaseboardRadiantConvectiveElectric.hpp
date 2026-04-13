/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEELECTRIC_HPP
#define EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEELECTRIC_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class ZoneHVACBaseboardRadiantConvectiveElectric_Impl;
  }

  class EPMODEL_API ZoneHVACBaseboardRadiantConvectiveElectric : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACBaseboardRadiantConvectiveElectric(const Model& model);

    virtual ~ZoneHVACBaseboardRadiantConvectiveElectric() override = default;
    ZoneHVACBaseboardRadiantConvectiveElectric(const ZoneHVACBaseboardRadiantConvectiveElectric& other) = default;
    ZoneHVACBaseboardRadiantConvectiveElectric(ZoneHVACBaseboardRadiantConvectiveElectric&& other) = default;
    ZoneHVACBaseboardRadiantConvectiveElectric& operator=(const ZoneHVACBaseboardRadiantConvectiveElectric&) = default;
    ZoneHVACBaseboardRadiantConvectiveElectric& operator=(ZoneHVACBaseboardRadiantConvectiveElectric&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatingDesignCapacityMethodValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical availability-schedule and scalar field groups are present, and thermal-zone attachment matches
    //   the canonical wrapper shape. Derived surface coverage is still not exposed directly on the public epmodel wrapper.
    // - Canonical Counterpart: openstudio::model::ZoneHVACBaseboardRadiantConvectiveElectric.
    // - Implemented Parity: `availabilitySchedule`, `heatingDesignCapacityMethod`, heating-capacity scalars, `autosizedHeatingDesignCapacity`,
    //   `efficiency`, `fractionRadiant`, `fractionofRadiantEnergyIncidentonPeople`, and the thermal-zone attach/remove APIs preserve the
    //   canonical wrapper behavior.
    // - Documented Delta: Canonical model derives the emitted radiant surface fractions from all surfaces in the attached thermal zone.
    //   Epmodel does not yet expose that derived surface coverage as a first-class public API on this wrapper.
    // - Field/Storage Mapping: The scalar fields map directly to the underlying EnergyPlus object. Surface membership remains derived from
    //   the attached thermal zone and is emitted through the parent object's extensible rows at translation time.
    // - Evidence: `src/model/ZoneHVACBaseboardRadiantConvectiveElectric.hpp`, `src/model/ZoneHVACBaseboardRadiantConvectiveElectric.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACBaseboardRadiantConvectiveElectric.cpp`, and `src/epmodel/test/ZoneHVACBaseboardRadiantConvectiveElectric_GTest.cpp`.
    // - Remaining Parity Work: If surface and envelope relationships become a stronger first-class concern in epmodel, decide whether the
    //   canonical derived surface coverage should become directly inspectable here.

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    std::string heatingDesignCapacityMethod() const;
    bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);

    boost::optional<double> heatingDesignCapacity() const;
    bool isHeatingDesignCapacityAutosized() const;
    bool setHeatingDesignCapacity(double heatingDesignCapacity);
    void autosizeHeatingDesignCapacity();
    boost::optional<double> autosizedHeatingDesignCapacity() const;

    double heatingDesignCapacityPerFloorArea() const;
    bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);

    double fractionofAutosizedHeatingDesignCapacity() const;
    bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);

    double efficiency() const;
    bool setEfficiency(double efficiency);

    double fractionRadiant() const;
    bool setFractionRadiant(double fractionRadiant);

    double fractionofRadiantEnergyIncidentonPeople() const;
    bool setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople);

    boost::optional<ThermalZone> thermalZone() const override;
    bool addToThermalZone(ThermalZone& thermalZone);
    void removeFromThermalZone();

   protected:
    using ImplType = detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACBaseboardRadiantConvectiveElectric(std::shared_ptr<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
