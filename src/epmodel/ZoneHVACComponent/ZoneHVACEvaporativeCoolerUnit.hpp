/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACEVAPORATIVECOOLERUNIT_HPP
#define EPMODEL_ZONEHVACEVAPORATIVECOOLERUNIT_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace boost {
template <typename T>
class optional;
}

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Model;
  class ModelObject;
  class Node;
  class Schedule;

  namespace detail {
    struct LoadContext;
    class ZoneHVACEvaporativeCoolerUnit_Impl;
  }  // namespace detail

/** \brief An evaporative-cooler unit serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-zone-forced-air-units.html#zonehvacevaporativecoolerunit,ZoneHVAC:EvaporativeCoolerUnit}
 *
 * \par Important behavior
 * The fan and one or two evaporative coolers share a parent-owned air path; EPModel exposes outdoor-air, fan-outlet, and cooler-outlet node roles.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneHVACEvaporativeCoolerUnit</code>.
 * EPModel adds explicit cooler outlet node roles and a <code>children()</code>
 * view over its contained fan/coolers; Model exposes an autosized design-flow
 * query that EPModel cannot resolve from SQL.
 *
 * \par Known limitations
 * Other relationship helpers and SQL-backed autosized design-flow results are not exposed.
 */
  class EPMODEL_API ZoneHVACEvaporativeCoolerUnit : public ZoneHVACComponent
  {
   public:
    explicit ZoneHVACEvaporativeCoolerUnit(const Model& model);

    virtual ~ZoneHVACEvaporativeCoolerUnit() override = default;
    ZoneHVACEvaporativeCoolerUnit(const ZoneHVACEvaporativeCoolerUnit& other) = default;
    ZoneHVACEvaporativeCoolerUnit(ZoneHVACEvaporativeCoolerUnit&& other) = default;
    ZoneHVACEvaporativeCoolerUnit& operator=(const ZoneHVACEvaporativeCoolerUnit&) = default;
    ZoneHVACEvaporativeCoolerUnit& operator=(ZoneHVACEvaporativeCoolerUnit&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> coolerUnitControlMethodValues();

    unsigned inletPort() const;
    unsigned outletPort() const;

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    HVACComponent supplyAirFan() const;
    bool setSupplyAirFan(const HVACComponent& hvacComponent);

    boost::optional<double> designSupplyAirFlowRate() const;
    bool isDesignSupplyAirFlowRateAutosized() const;
    bool setDesignSupplyAirFlowRate(double designSupplyAirFlowRate);
    void autosizeDesignSupplyAirFlowRate();

    std::string fanPlacement() const;
    bool setFanPlacement(const std::string& fanPlacement);

    std::string coolerUnitControlMethod() const;
    bool setCoolerUnitControlMethod(const std::string& coolerUnitControlMethod);

    double throttlingRangeTemperatureDifference() const;
    bool setThrottlingRangeTemperatureDifference(double throttlingRangeTemperatureDifference);

    double coolingLoadControlThresholdHeatTransferRate() const;
    bool setCoolingLoadControlThresholdHeatTransferRate(double coolingLoadControlThresholdHeatTransferRate);

    HVACComponent firstEvaporativeCooler() const;
    bool setFirstEvaporativeCooler(const HVACComponent& hvacComponent);

    boost::optional<HVACComponent> secondEvaporativeCooler() const;
    bool setSecondEvaporativeCooler(const HVACComponent& hvacComponent);
    void resetSecondEvaporativeCooler();

    double shutOffRelativeHumidity() const;
    bool setShutOffRelativeHumidity(double shutOffRelativeHumidity);

    boost::optional<Node> outdoorAirNode() const;
    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> firstEvaporativeCoolerOutletNode() const;
    boost::optional<Node> secondEvaporativeCoolerOutletNode() const;

    std::vector<ModelObject> children() const;

   protected:
    using ImplType = detail::ZoneHVACEvaporativeCoolerUnit_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneHVACEvaporativeCoolerUnit(std::shared_ptr<detail::ZoneHVACEvaporativeCoolerUnit_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
