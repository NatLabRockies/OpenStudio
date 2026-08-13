/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANZONEEXHAUST_HPP
#define EPMODEL_FANZONEEXHAUST_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class FanZoneExhaust_Impl;
  }

  class EPMODEL_API FanZoneExhaust : public ZoneHVACComponent
  {
   public:
    explicit FanZoneExhaust(const Model& model);

    virtual ~FanZoneExhaust() override = default;
    FanZoneExhaust(const FanZoneExhaust& other) = default;
    FanZoneExhaust(FanZoneExhaust&& other) = default;
    FanZoneExhaust& operator=(const FanZoneExhaust&) = default;
    FanZoneExhaust& operator=(FanZoneExhaust&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> systemAvailabilityManagerCouplingModeValues();

    // Schema Alignment Notes:
    // - Status: Partial Topology Parity. The exhaust-fan scalar and schedule fields plus direct thermal-zone lifecycle are aligned; the wider exhaust-system surface remains bounded.
    // - Canonical Counterpart: openstudio::model::FanZoneExhaust.
    // - Implemented Parity: Scalar and schedule getters/setters map directly to the EnergyPlus object. Inherited `addToThermalZone`, `thermalZone`, and `removeFromThermalZone` preserve zone equipment and exhaust-node ownership through movement and save/load.
    // - Documented Delta: AirflowNetwork helpers are not yet exposed on this wrapper.
    // - Field/Storage Mapping: Scalar values are stored directly on the EnergyPlus object. Thermal-zone ownership is projected through `ZoneHVAC:EquipmentList` and `ZoneHVAC:EquipmentConnections` exhaust-node rows; transient inlet/outlet nodes are removed when orphaned.
    // - Evidence: `src/model/FanZoneExhaust.hpp`, `src/model/FanZoneExhaust.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateFanZoneExhaust.cpp`, and `src/epmodel/test/FanZoneExhaust_GTest.cpp`.
    // - Remaining Parity Work: Bound AirflowNetwork and air-loop exhaust-system ownership separately.
    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    double fanTotalEfficiency() const;
    bool setFanTotalEfficiency(double fanTotalEfficiency);

    double fanEfficiency() const;
    bool setFanEfficiency(double fanTotalEfficiency);

    double pressureRise() const;
    bool setPressureRise(double pressureRise);

    boost::optional<double> maximumFlowRate() const;
    bool setMaximumFlowRate(double maximumFlowRate);
    void resetMaximumFlowRate();

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

    boost::optional<Schedule> flowFractionSchedule() const;
    bool setFlowFractionSchedule(Schedule& schedule);
    void resetFlowFractionSchedule();

    std::string systemAvailabilityManagerCouplingMode() const;
    bool setSystemAvailabilityManagerCouplingMode(const std::string& systemAvailabilityManagerCouplingMode);

    boost::optional<Schedule> minimumZoneTemperatureLimitSchedule() const;
    bool setMinimumZoneTemperatureLimitSchedule(Schedule& schedule);
    void resetMinimumZoneTemperatureLimitSchedule();

    boost::optional<Schedule> balancedExhaustFractionSchedule() const;
    bool setBalancedExhaustFractionSchedule(Schedule& schedule);
    void resetBalancedExhaustFractionSchedule();

   protected:
    using ImplType = detail::FanZoneExhaust_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FanZoneExhaust(std::shared_ptr<detail::FanZoneExhaust_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
