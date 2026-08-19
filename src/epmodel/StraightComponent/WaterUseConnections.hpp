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

/** \brief Connections for water-use equipment and plant demand.
 *
 * \par EnergyPlus object
 * \epobject{group-water-systems.html#wateruseconnections,WaterUse:Connections}
 *
 * \par Important behavior
 * Hot/cold supply schedules, water-use-equipment extensible rows, drain-water heat-exchanger fields, and plant-demand placement map directly to WaterUse:Connections.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::WaterUseConnections</code>.
 *
 * \par Known limitations
 * EnergyPlus-only supply and reclamation storage-tank fields are not exposed.
 */
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
