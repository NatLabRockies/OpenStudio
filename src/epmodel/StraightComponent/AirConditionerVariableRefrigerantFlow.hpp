/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOW_HPP
#define EPMODEL_AIRCONDITIONERVARIABLEREFRIGERANTFLOW_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class AirConditionerVariableRefrigerantFlow_Impl;
  }

  class EPMODEL_API AirConditionerVariableRefrigerantFlow : public StraightComponent
  {
   public:
    explicit AirConditionerVariableRefrigerantFlow(const Model& model);

    virtual ~AirConditionerVariableRefrigerantFlow() override = default;
    AirConditionerVariableRefrigerantFlow(const AirConditionerVariableRefrigerantFlow& other) = default;
    AirConditionerVariableRefrigerantFlow(AirConditionerVariableRefrigerantFlow&& other) = default;
    AirConditionerVariableRefrigerantFlow& operator=(const AirConditionerVariableRefrigerantFlow&) = default;
    AirConditionerVariableRefrigerantFlow& operator=(AirConditionerVariableRefrigerantFlow&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatingPerformanceCurveOutdoorTemperatureTypeValues();
    static std::vector<std::string> defrostStrategyValues();
    static std::vector<std::string> condenserTypeValues();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Partial Parity. Core VRF scalar controls and sizing/performance fields are aligned, but terminal, schedule, curve, and zone-link APIs remain intentionally hidden.
    // - Canonical Counterpart: openstudio::model::AirConditionerVariableRefrigerantFlow.
    // - Implemented Parity: `grossRatedTotalCoolingCapacity`, `grossRatedCoolingCOP`, `grossRatedHeatingCapacity`, `ratedHeatingCapacitySizingRatio`, `heatingPerformanceCurveOutdoorTemperatureType`, `heatPumpWasteHeatRecovery`, `numberofCompressors`, `defrostStrategy`, `condenserType`, and demand-side `addToNode` preserve the canonical scalar contract and current plant-loop insertion behavior.
    // - Documented Delta: Terminal attachments, schedules, curves, and other relationship-style helpers are not exposed yet. `addToNode` is intentionally limited to PlantLoop demand-side insertion, and no broader VRF topology parity is claimed here.
    // - Field/Storage Mapping: Most preserved scalar methods map directly to EnergyPlus `AirConditioner:VariableRefrigerantFlow` fields. `condenserType()` follows the canonical defaulted readback behavior by deriving `AirCooled` versus `WaterCooled` from current plant-loop attachment when the stored field is blank.
    // - Evidence: `src/model/AirConditionerVariableRefrigerantFlow.hpp`, `src/model/AirConditionerVariableRefrigerantFlow.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirConditionerVariableRefrigerantFlow.cpp`, and `src/epmodel/test/AirConditionerVariableRefrigerantFlow_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted terminal, schedule, curve, and zone-link accessors when relationship parity is in scope.
    boost::optional<double> grossRatedTotalCoolingCapacity() const;
    bool setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity);
    bool isGrossRatedTotalCoolingCapacityAutosized() const;
    void autosizeGrossRatedTotalCoolingCapacity();

    double grossRatedCoolingCOP() const;
    bool setGrossRatedCoolingCOP(double grossRatedCoolingCOP);

    boost::optional<double> grossRatedHeatingCapacity() const;
    bool setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity);
    bool isGrossRatedHeatingCapacityAutosized() const;
    void autosizeGrossRatedHeatingCapacity();

    double ratedHeatingCapacitySizingRatio() const;
    bool setRatedHeatingCapacitySizingRatio(double ratedHeatingCapacitySizingRatio);

    std::string heatingPerformanceCurveOutdoorTemperatureType() const;
    bool setHeatingPerformanceCurveOutdoorTemperatureType(const std::string& heatingPerformanceCurveOutdoorTemperatureType);

    bool heatPumpWasteHeatRecovery() const;
    bool setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery);

    int numberofCompressors() const;
    bool setNumberofCompressors(int numberofCompressors);

    std::string defrostStrategy() const;
    bool setDefrostStrategy(const std::string& defrostStrategy);

    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);
    bool isCondenserTypeDefaulted() const;
    void resetCondenserType();

   protected:
    using ImplType = detail::AirConditionerVariableRefrigerantFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirConditionerVariableRefrigerantFlow(std::shared_ptr<detail::AirConditionerVariableRefrigerantFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
