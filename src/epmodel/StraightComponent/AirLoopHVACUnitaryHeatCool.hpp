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

    // Schema Alignment Notes:
    // - Status: Partial Parity.
    // - Canonical Counterpart: None; this is an EnergyPlus-native type. Its contract follows the fully implemented canonical unitary siblings.
    // - Implemented Parity: The wrapper is a supply-side StraightComponent. Its availability and operating-mode schedules, controlling
    //   zone, fan, heating coil, cooling coil, and optional reheat coil are typed relationships. The unitary owns the HVAC children and
    //   maintains their serial air path for blow-through and draw-through fan placement.
    // - Field Mapping: Scalar APIs map directly to AirLoopHVAC:UnitaryHeatCool numeric/choice fields. Object type/name pairs are
    //   synchronized by typed relationship mutation and canonicalization.
    // - Evidence: The sibling AirLoopHVACUnitaryHeatPumpAirToAir and AirLoopHVACUnitaryHeatCoolVAVChangeoverBypass wrappers provide the ownership,
    //   supply-connection, and contained-air-path contracts.
    // - Remaining Parity Work: Add broader topology conveniences only when another supported unitary contract establishes their semantics.
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
