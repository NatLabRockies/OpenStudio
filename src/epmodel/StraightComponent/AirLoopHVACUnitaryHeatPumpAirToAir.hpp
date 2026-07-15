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

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar controls and direct object-link fields are aligned, and the owned internal air path is now maintained through parent-owned epmodel nodes.
    // - Canonical Counterpart: openstudio::model::AirLoopHVACUnitaryHeatPumpAirToAir.
    // - Implemented Parity: Availability schedule, controlling zone, supply fan, heating coil, cooling coil, supplemental heating coil,
    //   supply-air-fan operating mode schedule, constructor-with-components, and the scalar airflow/control fields preserve the main canonical
    //   wrapper contract. The owned fan/cooling/heating/supplemental chain now shares a stable parent-maintained air path, with direct access
    //   to the meaningful outlet node roles on the compound, and child traversal matches the canonical owned-component slice.
    // - Documented Delta: `fanOutletNode()`, `coolingCoilOutletNode()`, and `heatingCoilOutletNode()` are additive epmodel conveniences so
    //   callers can inspect and rename the meaningful internal outlet roles owned by the compound, even when those roles alias the parent
    //   outlet in a valid configuration. Broader topology convenience beyond the owned serial air path remains intentionally omitted.
    // - Field/Storage Mapping: Scalar values map directly to EnergyPlus unitary heat-pump fields, while schedule, fan, coil, zone, and
    //   internal-node relationships are explicit parent-owned object links in epmodel.
    // - Evidence: `src/model/AirLoopHVACUnitaryHeatPumpAirToAir.hpp`, `src/model/AirLoopHVACUnitaryHeatPumpAirToAir.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACUnitaryHeatPumpAirToAir.cpp`, and `src/epmodel/test/AirLoopHVACUnitaryHeatPumpAirToAir_GTest.cpp`.
    // - Remaining Parity Work: Add any remaining topology conveniences only if the canonical wrapper still exposes them directly.
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
