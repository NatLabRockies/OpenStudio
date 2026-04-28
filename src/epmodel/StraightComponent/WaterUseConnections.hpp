/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERUSECONNECTIONS_HPP
#define EPMODEL_WATERUSECONNECTIONS_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class WaterUseEquipment;

  namespace detail {
    class WaterUseConnections_Impl;
  }

  class EPMODEL_API WaterUseConnections : public StraightComponent
  {
   public:
    explicit WaterUseConnections(const Model& model);

    virtual ~WaterUseConnections() override = default;
    WaterUseConnections(const WaterUseConnections& other) = default;
    WaterUseConnections(WaterUseConnections&& other) = default;
    WaterUseConnections& operator=(const WaterUseConnections&) = default;
    WaterUseConnections& operator=(WaterUseConnections&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> drainWaterHeatExchangerTypeValues();
    static std::vector<std::string> drainWaterHeatExchangerDestinationValues();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical water-use-connections wrapper surface is present.
    // - Canonical Counterpart: openstudio::model::WaterUseConnections.
    // - Implemented Parity: Hot/cold supply-temperature schedule relationships, water-use-equipment extensible ownership, plant-demand-only
    //   placement behavior, and the drain-water-heat-exchanger scalar accessors now match the canonical counterpart.
    // - Documented Delta: The EnergyPlus-only supply and reclamation storage-tank fields remain intentionally unwrapped because the canonical
    //   `openstudio::model::WaterUseConnections` surface does not expose them either.
    // - Field/Storage Mapping: Schedule relationships use direct object-list pointers plus shared epmodel schedule-type validation,
    //   equipment membership uses `WaterUse:Connections` extensible rows, and drain-water helpers map directly to the matching scalar
    //   fields consumed by the forward translator.
    // - Evidence: `src/model/WaterUseConnections.hpp`, `src/model/WaterUseConnections.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateWaterUseConnections.cpp`.
    // - Remaining Parity Work: None for the current canonical counterpart surface.
    boost::optional<Schedule> hotWaterSupplyTemperatureSchedule() const;
    bool setHotWaterSupplyTemperatureSchedule(Schedule& hotWaterSupplyTemperatureSchedule);
    void resetHotWaterSupplyTemperatureSchedule();

    boost::optional<Schedule> coldWaterSupplyTemperatureSchedule() const;
    bool setColdWaterSupplyTemperatureSchedule(Schedule& coldWaterSupplyTemperatureSchedule);
    void resetColdWaterSupplyTemperatureSchedule();

    std::vector<WaterUseEquipment> waterUseEquipment() const;
    bool addWaterUseEquipment(const WaterUseEquipment& waterUseEquipment);
    bool removeWaterUseEquipment(WaterUseEquipment& waterUseEquipment);

    std::string drainWaterHeatExchangerType() const;
    bool setDrainWaterHeatExchangerType(const std::string& drainWaterHeatExchangerType);

    std::string drainWaterHeatExchangerDestination() const;
    bool setDrainWaterHeatExchangerDestination(const std::string& drainWaterHeatExchangerDestination);

    boost::optional<double> drainWaterHeatExchangerUFactorTimesArea() const;
    bool setDrainWaterHeatExchangerUFactorTimesArea(double drainWaterHeatExchangerUFactorTimesArea);
    void resetDrainWaterHeatExchangerUFactorTimesArea();

   protected:
    using ImplType = detail::WaterUseConnections_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    explicit WaterUseConnections(std::shared_ptr<detail::WaterUseConnections_Impl> impl);
  };

  using OptionalWaterUseConnections = boost::optional<WaterUseConnections>;
  using WaterUseConnectionsVector = std::vector<WaterUseConnections>;

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_WATERUSECONNECTIONS_HPP
