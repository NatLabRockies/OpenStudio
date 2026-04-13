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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The direct EnergyPlus scalar surface and thermal-zone attachment behavior are present. Epmodel also preserves
    //   the canonical availability-schedule and heating-coil APIs by exposing the heating coil as a transient child view over the parent
    //   radiant object and its persisted EnergyPlus design companion.
    // - Canonical Counterpart: openstudio::model::ZoneHVACBaseboardRadiantConvectiveWater.
    // - Why This Type Is Slightly Different: canonical OpenStudio factors this family into one parent baseboard object plus a water heating
    //   coil child. EnergyPlus does not persist that coil separately. It flattens the coil state onto the parent
    //   `ZoneHVAC:Baseboard:RadiantConvective:Water` object plus a persisted `...:Design` companion object.
    // - Implemented Parity: The canonical availability-schedule, radiant-fraction, people-incident radiant-fraction, and heating-coil APIs are
    //   available on the parent. Epmodel also retains additive direct accessors for the flattened parent EnergyPlus fields so callers can
    //   inspect the raw storage shape when needed.
    // - Documented Delta: Surface coverage is still derived and emitted at translation time rather than preserved as a first-class canonical
    //   public API. The transient heating coil is a canonical child view over parent-owned storage, not a standalone persisted EnergyPlus object.
    // - Field/Storage Mapping: Availability schedule and the plant-side water nodes live on the EnergyPlus parent object. Design-side coil
    //   sizing and convergence fields live on the persisted `ZoneHVAC:Baseboard:RadiantConvective:Water:Design` companion object. The transient
    //   heating coil reads and writes through those parent-owned fields rather than owning separate EnergyPlus storage.
    // - Evidence: `src/model/ZoneHVACBaseboardRadiantConvectiveWater.hpp`, `src/model/ZoneHVACBaseboardRadiantConvectiveWater.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACBaseboardRadiantConvectiveWater.cpp`, and
    //   `src/epmodel/test/ZoneHVACBaseboardRadiantConvectiveWater_GTest.cpp`.
    // - Remaining Parity Work: If surface handling becomes a first-class epmodel concern, decide how much of the canonical derived surface
    //   behavior should become directly inspectable on the wrapper.

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
