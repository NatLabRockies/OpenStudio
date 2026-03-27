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
    // - Status: Partial Parity. The scalar field groups and thermal-zone attachment behavior are present, but the remaining relationship and surface-link surface is still incomplete.
    // - Canonical Counterpart: openstudio::model::ZoneHVACBaseboardRadiantConvectiveElectric.
    // - Implemented Parity: `heatingDesignCapacityMethod`, heating-capacity scalars, `efficiency`, `fractionRadiant`, `fractionofRadiantEnergyIncidentonPeople`, and the thermal-zone attach/remove APIs preserve the main canonical wrapper behavior.
    // - Documented Delta: Availability schedule, heating coil, and extensible surface entries are relationship-only and remain outside this public wrapper surface.
    // - Field/Storage Mapping: The scalar fields map directly to the underlying EnergyPlus object, while surface membership is tracked through thermal-zone topology and child-object state.
    // - Evidence: `src/model/ZoneHVACBaseboardRadiantConvectiveElectric.hpp`, `src/model/ZoneHVACBaseboardRadiantConvectiveElectric.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACBaseboardRadiantConvectiveElectric.cpp`, and `src/epmodel/test/ZoneHVACBaseboardRadiantConvectiveElectric_GTest.cpp`.
    // - Remaining Parity Work: Add explicit relationship helpers for schedules, heating coil links, and extensible surfaces if those canonical behaviors need to become first-class.

    std::string heatingDesignCapacityMethod() const;
    bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);

    boost::optional<double> heatingDesignCapacity() const;
    bool isHeatingDesignCapacityAutosized() const;
    bool setHeatingDesignCapacity(double heatingDesignCapacity);
    void autosizeHeatingDesignCapacity();

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
