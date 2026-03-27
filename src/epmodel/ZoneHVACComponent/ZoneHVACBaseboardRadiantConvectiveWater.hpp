/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATER_HPP
#define EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATER_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <boost/optional.hpp>
#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
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
    // - Status: Partial Parity. The scalar field surface and thermal-zone attachment behavior are present, but the schedule/coils/surface links remain relationship-driven.
    // - Canonical Counterpart: openstudio::model::ZoneHVACBaseboardRadiantConvectiveWater.
    // - Implemented Parity: `ratedAverageWaterTemperature`, `ratedWaterMassFlowRate`, `heatingDesignCapacity`, `maximumWaterFlowRate`, and the thermal-zone attach/remove APIs map directly to the canonical wrapper behavior.
    // - Documented Delta: Availability schedule, heating coil, and extensible surface entries are omitted because they are relationship-only wiring rather than scalar fields.
    // - Field/Storage Mapping: EnergyPlus stores the scalar values directly on the object, while thermal-zone membership and surface coverage are maintained through explicit topology and child-object state.
    // - Evidence: `src/model/ZoneHVACBaseboardRadiantConvectiveWater.hpp`, `src/model/ZoneHVACBaseboardRadiantConvectiveWater.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneHVACBaseboardRadiantConvectiveWater.cpp`, and `src/epmodel/test/ZoneHVACBaseboardRadiantConvectiveWater_GTest.cpp`.
    // - Remaining Parity Work: Add explicit relationship helpers only if canonical surface handling becomes a first-class epmodel concern.

    // ratedAverageWaterTemperature accessors
    boost::optional<double> ratedAverageWaterTemperature() const;
    bool isRatedAverageWaterTemperatureDefaulted() const;
    bool setRatedAverageWaterTemperature(double ratedAverageWaterTemperature);
    void resetRatedAverageWaterTemperature();

    // ratedWaterMassFlowRate accessors
    boost::optional<double> ratedWaterMassFlowRate() const;
    bool isRatedWaterMassFlowRateDefaulted() const;
    bool setRatedWaterMassFlowRate(double ratedWaterMassFlowRate);
    void resetRatedWaterMassFlowRate();

    // heatingDesignCapacity accessors
    boost::optional<double> heatingDesignCapacity() const;
    bool isHeatingDesignCapacityAutosized() const;
    bool setHeatingDesignCapacity(double heatingDesignCapacity);
    void autosizeHeatingDesignCapacity();

    // maximumWaterFlowRate accessors
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
