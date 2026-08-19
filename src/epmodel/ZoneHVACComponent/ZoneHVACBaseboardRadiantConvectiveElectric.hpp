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

/** \brief An electric radiant-convective baseboard heater serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-radiative-convective-units.html#zonehvacbaseboardradiantconvectiveelectric,ZoneHVAC:Baseboard:RadiantConvective:Electric}
 *
 * \par Important behavior
 * Availability, heating-capacity, efficiency, radiant-fraction, and thermal-zone attachment methods are available.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACBaseboardRadiantConvectiveElectric</code>.
 *
 * \par Known limitations
 * Surface coverage is derived from the attached zone and emitted through extensible rows, not exposed as a separate public collection.
 */
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
