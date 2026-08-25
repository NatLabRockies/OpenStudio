/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATER_HPP
#define EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboardRadiant.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Model;
  class ModelObject;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class ZoneHVACBaseboardRadiantConvectiveWater_Impl;
  }

/** \brief A hot-water radiant-convective baseboard heater serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-radiative-convective-units.html#zonehvacbaseboardradiantconvectivewater,ZoneHVAC:Baseboard:RadiantConvective:Water} and
 * \epobject{group-radiative-convective-units.html#zonehvac-baseboard-radiantconvective-water-design,ZoneHVAC:Baseboard:RadiantConvective:Water:Design}
 *
 * \par Important behavior
 * heatingCoil() is a transient view over parent-owned fields; design sizing and convergence fields are on the design companion, while surface rows are derived from the attached zone.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACBaseboardRadiantConvectiveWater</code>.
 * EPModel exposes the EnergyPlus design-capacity and rated-water fields
 * directly; the Model wrapper presents the usual baseboard surface without
 * those additional design-field methods.
 *
 * \par Known limitations
 * Surface coverage is not maintained as a first-class public collection after later zone or surface edits; the transient coil is accessed through its parent.
 */
  class EPMODEL_API ZoneHVACBaseboardRadiantConvectiveWater : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACBaseboardRadiantConvectiveWater(const Model& model);

    virtual ~ZoneHVACBaseboardRadiantConvectiveWater() override = default;
    ZoneHVACBaseboardRadiantConvectiveWater(const ZoneHVACBaseboardRadiantConvectiveWater& other) = default;
    ZoneHVACBaseboardRadiantConvectiveWater(ZoneHVACBaseboardRadiantConvectiveWater&& other) = default;
    ZoneHVACBaseboardRadiantConvectiveWater& operator=(const ZoneHVACBaseboardRadiantConvectiveWater&) = default;
    ZoneHVACBaseboardRadiantConvectiveWater& operator=(ZoneHVACBaseboardRadiantConvectiveWater&&) = default;

    static IddObjectType iddObjectType();


    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    double fractionRadiant() const;
    bool setFractionRadiant(double fractionRadiant);

    double fractionofRadiantEnergyIncidentonPeople() const;
    bool setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople);

    CoilHeatingWaterBaseboardRadiant heatingCoil() const;
    bool setHeatingCoil(HVACComponent& heatingCoil);

    std::vector<ModelObject> children() const;

    // Additive direct accessors for the flattened parent EnergyPlus fields.
    boost::optional<double> ratedAverageWaterTemperature() const;
    bool isRatedAverageWaterTemperatureDefaulted() const;
    bool setRatedAverageWaterTemperature(double ratedAverageWaterTemperature);
    void resetRatedAverageWaterTemperature();

    boost::optional<double> ratedWaterMassFlowRate() const;
    bool isRatedWaterMassFlowRateDefaulted() const;
    bool setRatedWaterMassFlowRate(double ratedWaterMassFlowRate);
    void resetRatedWaterMassFlowRate();

    boost::optional<double> heatingDesignCapacity() const;
    bool isHeatingDesignCapacityAutosized() const;
    bool setHeatingDesignCapacity(double heatingDesignCapacity);
    void autosizeHeatingDesignCapacity();

    boost::optional<double> maximumWaterFlowRate() const;
    bool isMaximumWaterFlowRateAutosized() const;
    bool setMaximumWaterFlowRate(double maximumWaterFlowRate);
    void autosizeMaximumWaterFlowRate();

    boost::optional<ThermalZone> thermalZone() const override;
    bool addToThermalZone(ThermalZone& thermalZone);
    void removeFromThermalZone();

   protected:
    using ImplType = detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACBaseboardRadiantConvectiveWater(std::shared_ptr<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
