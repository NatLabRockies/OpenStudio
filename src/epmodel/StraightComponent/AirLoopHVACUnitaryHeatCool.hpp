/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYHEATCOOL_HPP
#define EPMODEL_AIRLOOPHVACUNITARYHEATCOOL_HPP

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
  class Schedule;
  class ThermalZone;

  namespace detail {
    class AirLoopHVACUnitaryHeatCool_Impl;
  }

  /**
   * \brief Unitary air conditioner with separately typed fan, heating-coil, cooling-coil, and optional reheat-coil links.
   *
   * \par EnergyPlus object
   * Encapsulates \epobject{group-unitary-equipment.html#airloophvacunitaryheatcool,AirLoopHVAC:UnitaryHeatCool}.
   *
   * \par Important behavior
   * The child components form one parent-owned serial air path. Fan placement determines the path order, and the
   * outlet-node helpers expose the meaningful internal boundaries. `addToNode` inserts the compound on an air-loop
   * supply path.
   *
   * \par OpenStudio Model API
   * There is no separate `openstudio::model` counterpart for this EnergyPlus-native type. The API follows the
   * corresponding unitary Model wrappers for schedules, child relationships, control fields, and autosized supply
   * airflow fields, while adding direct access to the internal outlet nodes.
   *
   * \par Known limitations
   * Broader unitary topology conveniences are not exposed; use the typed child and node relationships for the
   * supported serial path.
   */
  class EPMODEL_API AirLoopHVACUnitaryHeatCool : public StraightComponent
  {
   public:
    explicit AirLoopHVACUnitaryHeatCool(const Model& model);
    AirLoopHVACUnitaryHeatCool(const Model& model, Schedule& availabilitySchedule, HVACComponent& supplyFan, HVACComponent& heatingCoil,
                               HVACComponent& coolingCoil);

    virtual ~AirLoopHVACUnitaryHeatCool() override = default;
    AirLoopHVACUnitaryHeatCool(const AirLoopHVACUnitaryHeatCool& other) = default;
    AirLoopHVACUnitaryHeatCool(AirLoopHVACUnitaryHeatCool&& other) = default;
    AirLoopHVACUnitaryHeatCool& operator=(const AirLoopHVACUnitaryHeatCool&) = default;
    AirLoopHVACUnitaryHeatCool& operator=(AirLoopHVACUnitaryHeatCool&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> supplyFanObjectTypeValues();
    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> heatingCoilObjectTypeValues();
    static std::vector<std::string> coolingCoilObjectTypeValues();
    static std::vector<std::string> dehumidificationControlTypeValues();
    static std::vector<std::string> reheatCoilObjectTypeValues();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
    bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
    void resetSupplyAirFanOperatingModeSchedule();

    boost::optional<ThermalZone> controllingZone() const;
    bool setControllingZone(ThermalZone& zone);
    void resetControllingZone();

    HVACComponent supplyFan() const;
    bool setSupplyFan(HVACComponent& hvacComponent);

    HVACComponent heatingCoil() const;
    bool setHeatingCoil(HVACComponent& hvacComponent);

    HVACComponent coolingCoil() const;
    bool setCoolingCoil(HVACComponent& hvacComponent);

    boost::optional<HVACComponent> reheatCoil() const;
    bool setReheatCoil(HVACComponent& hvacComponent);
    void resetReheatCoil();

    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> coolingCoilOutletNode() const;
    boost::optional<Node> heatingCoilOutletNode() const;

    bool addToNode(Node& node);
    boost::optional<double> maximumSupplyAirTemperature() const;
    bool isMaximumSupplyAirTemperatureDefaulted() const;
    bool isMaximumSupplyAirTemperatureAutosized() const;
    bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);
    void resetMaximumSupplyAirTemperature();
    void autosizeMaximumSupplyAirTemperature();

    boost::optional<double> coolingSupplyAirFlowRate() const;
    bool isCoolingSupplyAirFlowRateAutosized() const;
    bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
    void autosizeCoolingSupplyAirFlowRate();

    boost::optional<double> heatingSupplyAirFlowRate() const;
    bool isHeatingSupplyAirFlowRateAutosized() const;
    bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
    void autosizeHeatingSupplyAirFlowRate();

    boost::optional<double> noLoadSupplyAirFlowRate() const;
    bool isNoLoadSupplyAirFlowRateAutosized() const;
    bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
    void resetNoLoadSupplyAirFlowRate();
    void autosizeNoLoadSupplyAirFlowRate();

    std::string supplyFanObjectType() const;
    bool setSupplyFanObjectType(const std::string& supplyFanObjectType);

    std::string fanPlacement() const;
    bool setFanPlacement(const std::string& fanPlacement);
    bool isFanPlacementDefaulted() const;
    void resetFanPlacement();

    std::string heatingCoilObjectType() const;
    bool setHeatingCoilObjectType(const std::string& heatingCoilObjectType);

    std::string coolingCoilObjectType() const;
    bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

    std::string dehumidificationControlType() const;
    bool setDehumidificationControlType(const std::string& dehumidificationControlType);
    bool isDehumidificationControlTypeDefaulted() const;
    void resetDehumidificationControlType();

    boost::optional<std::string> reheatCoilObjectType() const;
    bool setReheatCoilObjectType(const std::string& reheatCoilObjectType);
    void resetReheatCoilObjectType();

   protected:
    using ImplType = detail::AirLoopHVACUnitaryHeatCool_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirLoopHVACUnitaryHeatCool(std::shared_ptr<detail::AirLoopHVACUnitaryHeatCool_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
