/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDCOOLERTWOSPEED_HPP
#define EPMODEL_FLUIDCOOLERTWOSPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class FluidCoolerTwoSpeed_Impl;
  }

  class EPMODEL_API FluidCoolerTwoSpeed : public StraightComponent
  {
   public:
    explicit FluidCoolerTwoSpeed(const Model& model);

    virtual ~FluidCoolerTwoSpeed() override = default;
    FluidCoolerTwoSpeed(const FluidCoolerTwoSpeed& other) = default;
    FluidCoolerTwoSpeed(FluidCoolerTwoSpeed&& other) = default;
    FluidCoolerTwoSpeed& operator=(const FluidCoolerTwoSpeed&) = default;
    FluidCoolerTwoSpeed& operator=(FluidCoolerTwoSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> performanceInputMethodValues();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical two-speed fluid-cooler scalar surface, outdoor-air inlet relationship, and plant-supply
    //   placement rule are present, while resolved autosized-value lookup remains out of scope.
    // - Canonical Counterpart: openstudio::model::FluidCoolerTwoSpeed.
    // - Implemented Parity: The preserved API matches the canonical high/low speed performance, capacity, temperature, autosize-token, and optional
    //   outdoor-air Node accessors with matching default behavior; inherited `addToNode(...)` follows the canonical plant-supply-only insertion
    //   contract. The Node API owns only field A5 and its generated `OutdoorAir:NodeList` declaration, preserves caller-owned Nodes and direct
    //   `OutdoorAir:Node` objects, and lets direct declarations take precedence over conflicting NodeList rows.
    // - Documented Delta: The `autosized*()` getters remain intentionally unresolved because epmodel does not yet expose SQL-backed sizing results.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `FluidCooler:TwoSpeed` fields used by the forward translator. Configured A5
    //   is an optional NodeType field and remains blank at construction; the canonical forward translator emits it when present.
    // - Evidence: `src/model/FluidCoolerTwoSpeed.hpp`, `src/model/FluidCoolerTwoSpeed.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateFluidCoolerTwoSpeed.cpp`.
    // - Remaining Parity Work: Wire `autosized*()` to resolved sizing results without changing the preserved scalar signatures.
    boost::optional<Node> outdoorAirInletNode() const;
    bool setOutdoorAirInletNode(const Node& node);
    void resetOutdoorAirInletNode();

    std::string performanceInputMethod() const;
    bool setPerformanceInputMethod(const std::string& performanceInputMethod);

    boost::optional<double> highFanSpeedUfactorTimesAreaValue() const;
    bool isHighFanSpeedUfactorTimesAreaValueAutosized() const;
    bool setHighFanSpeedUfactorTimesAreaValue(double highFanSpeedUfactorTimesAreaValue);
    void autosizeHighFanSpeedUfactorTimesAreaValue();
    boost::optional<double> autosizedHighFanSpeedUfactorTimesAreaValue() const;

    boost::optional<double> lowFanSpeedUfactorTimesAreaValue() const;
    bool isLowFanSpeedUfactorTimesAreaValueAutosized() const;
    bool setLowFanSpeedUfactorTimesAreaValue(double lowFanSpeedUfactorTimesAreaValue);
    void autosizeLowFanSpeedUfactorTimesAreaValue();
    boost::optional<double> autosizedLowFanSpeedUfactorTimesAreaValue() const;

    double lowFanSpeedUFactorTimesAreaSizingFactor() const;
    bool setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor);

    double highSpeedNominalCapacity() const;
    bool setHighSpeedNominalCapacity(double highSpeedNominalCapacity);

    boost::optional<double> lowSpeedNominalCapacity() const;
    bool isLowSpeedNominalCapacityAutosized() const;
    bool setLowSpeedNominalCapacity(double lowSpeedNominalCapacity);
    void autosizeLowSpeedNominalCapacity();
    boost::optional<double> autosizedLowSpeedNominalCapacity() const;

    double lowSpeedNominalCapacitySizingFactor() const;
    bool setLowSpeedNominalCapacitySizingFactor(double lowSpeedNominalCapacitySizingFactor);

    double designEnteringWaterTemperature() const;
    bool setDesignEnteringWaterTemperature(double designEnteringWaterTemperature);

    double designEnteringAirTemperature() const;
    bool setDesignEnteringAirTemperature(double designEnteringAirTemperature);

    double designEnteringAirWetbulbTemperature() const;
    bool setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature);

    boost::optional<double> designWaterFlowRate() const;
    bool isDesignWaterFlowRateAutosized() const;
    bool setDesignWaterFlowRate(double designWaterFlowRate);
    void autosizeDesignWaterFlowRate();
    boost::optional<double> autosizedDesignWaterFlowRate() const;

    boost::optional<double> highFanSpeedAirFlowRate() const;
    bool isHighFanSpeedAirFlowRateAutosized() const;
    bool setHighFanSpeedAirFlowRate(double highFanSpeedAirFlowRate);
    void autosizeHighFanSpeedAirFlowRate();
    boost::optional<double> autosizedHighFanSpeedAirFlowRate() const;

    boost::optional<double> highFanSpeedFanPower() const;
    bool isHighFanSpeedFanPowerAutosized() const;
    bool setHighFanSpeedFanPower(double highFanSpeedFanPower);
    void autosizeHighFanSpeedFanPower();
    boost::optional<double> autosizedHighFanSpeedFanPower() const;

    boost::optional<double> lowFanSpeedAirFlowRate() const;
    bool isLowFanSpeedAirFlowRateAutosized() const;
    bool setLowFanSpeedAirFlowRate(double lowFanSpeedAirFlowRate);
    void autosizeLowFanSpeedAirFlowRate();
    boost::optional<double> autosizedLowFanSpeedAirFlowRate() const;

    double lowFanSpeedAirFlowRateSizingFactor() const;
    bool setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor);

    boost::optional<double> lowFanSpeedFanPower() const;
    bool isLowFanSpeedFanPowerAutosized() const;
    bool setLowFanSpeedFanPower(double lowFanSpeedFanPower);
    void autosizeLowFanSpeedFanPower();
    boost::optional<double> autosizedLowFanSpeedFanPower() const;

    double lowFanSpeedFanPowerSizingFactor() const;
    bool setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor);

   protected:
    using ImplType = detail::FluidCoolerTwoSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FluidCoolerTwoSpeed(std::shared_ptr<detail::FluidCoolerTwoSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
