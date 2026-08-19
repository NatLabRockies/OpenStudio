/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIR_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATPUMPAIRTOAIR_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class HVACComponent;
  class ModelObject;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class AirLoopHVACUnitaryHeatPumpAirToAir_Impl;
  }

  /**
   * \brief Air-to-air heat-pump unitary system with typed fan, heating-coil, cooling-coil, and supplemental-heater links.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-unitary-equipment.html#airloophvacunitaryheatpumpairtoair,AirLoopHVAC:UnitaryHeatPump:AirToAir}.
   *
   * \par Important behavior
   * The supplied fan and coils are maintained as one parent-owned serial air path. Fan placement is persisted with
   * the unitary, and the outlet-node helpers expose the internal fan, cooling-coil, and heating-coil boundaries.
   *
   * \par OpenStudio Model API
   * Counterpart: `openstudio::model::AirLoopHVACUnitaryHeatPumpAirToAir`. The epmodel API covers the schedules,
   * controlling zone, child relationships, supplemental-heater controls, and autosized airflow methods, and adds
   * direct internal outlet-node access.
   *
   * \par Known limitations
   * The wrapper does not expose topology conveniences beyond its owned serial path.
   */
  class EPMODEL_API AirLoopHVACUnitaryHeatPumpAirToAir : public StraightComponent
  {
   public:
    explicit AirLoopHVACUnitaryHeatPumpAirToAir(const Model& model);
    AirLoopHVACUnitaryHeatPumpAirToAir(const Model& model, Schedule& availabilitySchedule, HVACComponent& supplyFan, HVACComponent& heatingCoil,
                                       HVACComponent& coolingCoil, HVACComponent& supplementalHeatingCoil);

    virtual ~AirLoopHVACUnitaryHeatPumpAirToAir() override = default;
    AirLoopHVACUnitaryHeatPumpAirToAir(const AirLoopHVACUnitaryHeatPumpAirToAir& other) = default;
    AirLoopHVACUnitaryHeatPumpAirToAir(AirLoopHVACUnitaryHeatPumpAirToAir&& other) = default;
    AirLoopHVACUnitaryHeatPumpAirToAir& operator=(const AirLoopHVACUnitaryHeatPumpAirToAir&) = default;
    AirLoopHVACUnitaryHeatPumpAirToAir& operator=(AirLoopHVACUnitaryHeatPumpAirToAir&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validFanPlacementValues();
    static std::vector<std::string> validDehumidificationControlTypeValues();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
    bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
    bool setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation);
    void autosizeSupplyAirFlowRateDuringCoolingOperation();

    boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
    bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
    bool setSupplyAirFlowRateDuringHeatingOperation(double n2);
    void autosizeSupplyAirFlowRateDuringHeatingOperation();

    boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;
    bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;
    bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
    void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
    void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

    boost::optional<ThermalZone> controllingZone() const;
    bool setControllingZone(ThermalZone& zone);
    void resetControllingZone();

    HVACComponent supplyAirFan() const;
    bool setSupplyAirFan(HVACComponent& hvacComponent);

    HVACComponent heatingCoil() const;
    bool setHeatingCoil(HVACComponent& hvacComponent);

    HVACComponent coolingCoil() const;
    bool setCoolingCoil(HVACComponent& hvacComponent);

    HVACComponent supplementalHeatingCoil() const;
    bool setSupplementalHeatingCoil(HVACComponent& hvacComponent);

    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> coolingCoilOutletNode() const;
    boost::optional<Node> heatingCoilOutletNode() const;

    boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater() const;
    bool isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const;
    bool setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater);
    void autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();

    double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
    bool isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const;
    bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    void resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();

    std::string fanPlacement() const;
    bool isFanPlacementDefaulted() const;
    bool setFanPlacement(const std::string& fanPlacement);
    void resetFanPlacement();

    boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
    bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
    void resetSupplyAirFanOperatingModeSchedule();

    std::string dehumidificationControlType() const;
    bool isDehumidificationControlTypeDefaulted() const;
    bool setDehumidificationControlType(const std::string& dehumidificationControlType);
    void resetDehumidificationControlType();

    double dXHeatingCoilSizingRatio() const;
    bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirLoopHVACUnitaryHeatPumpAirToAir(std::shared_ptr<detail::AirLoopHVACUnitaryHeatPumpAirToAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
