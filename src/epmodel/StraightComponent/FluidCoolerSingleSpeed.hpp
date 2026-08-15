/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDCOOLERSINGLESPEED_HPP
#define EPMODEL_FLUIDCOOLERSINGLESPEED_HPP

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
    class FluidCoolerSingleSpeed_Impl;
  }

  class EPMODEL_API FluidCoolerSingleSpeed : public StraightComponent
  {
   public:
    explicit FluidCoolerSingleSpeed(const Model& model);

    virtual ~FluidCoolerSingleSpeed() override = default;
    FluidCoolerSingleSpeed(const FluidCoolerSingleSpeed& other) = default;
    FluidCoolerSingleSpeed(FluidCoolerSingleSpeed&& other) = default;
    FluidCoolerSingleSpeed& operator=(const FluidCoolerSingleSpeed&) = default;
    FluidCoolerSingleSpeed& operator=(FluidCoolerSingleSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> performanceInputMethodValues();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. The canonical single-speed fluid-cooler scalar surface, outdoor-air inlet relationship, and plant-supply
    //   placement rule are present, while resolved autosized-value lookup remains out of scope.
    // - Canonical Counterpart: openstudio::model::FluidCoolerSingleSpeed.
    // - Implemented Parity: The preserved API matches the canonical performance, capacity, temperature, autosize-token, and optional outdoor-air Node
    //   accessors with matching default behavior; inherited `addToNode(...)` follows the canonical plant-supply-only insertion contract. The Node API
    //   owns only field A5 and its generated `OutdoorAir:NodeList` declaration, preserves caller-owned Nodes and direct `OutdoorAir:Node` objects, and
    //   lets direct declarations take precedence over conflicting NodeList rows.
    // - Documented Delta: The `autosized*()` getters remain intentionally unresolved because epmodel does not yet expose SQL-backed sizing results.
    // - Field/Storage Mapping: Scalar accessors and `outdoorAirInletNode()` map directly to EnergyPlus `FluidCooler:SingleSpeed` fields. Configured A5
    //   is an optional NodeType field and remains blank at construction; the outdoor-air claim is bounded to the canonical Model API and configured
    //   IDD because its current forward translator does not emit that field.
    // - Evidence: `src/model/FluidCoolerSingleSpeed.hpp`, `src/model/FluidCoolerSingleSpeed.cpp`, and EnergyPlus `FluidCooler:SingleSpeed` field A5.
    // - Remaining Parity Work: Wire `autosized*()` to resolved sizing results without changing the preserved scalar signatures.
    boost::optional<Node> outdoorAirInletNode() const;
    bool setOutdoorAirInletNode(const Node& node);
    void resetOutdoorAirInletNode();

    std::string performanceInputMethod() const;
    bool setPerformanceInputMethod(const std::string& performanceInputMethod);

    boost::optional<double> designAirFlowRateUfactorTimesAreaValue() const;
    bool isDesignAirFlowRateUfactorTimesAreaValueAutosized() const;
    bool setDesignAirFlowRateUfactorTimesAreaValue(double designAirFlowRateUfactorTimesAreaValue);
    void autosizeDesignAirFlowRateUfactorTimesAreaValue();
    boost::optional<double> autosizedDesignAirFlowRateUfactorTimesAreaValue() const;

    double nominalCapacity() const;
    bool setNominalCapacity(double nominalCapacity);

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

    boost::optional<double> designAirFlowRate() const;
    bool isDesignAirFlowRateAutosized() const;
    bool setDesignAirFlowRate(double designAirFlowRate);
    void autosizeDesignAirFlowRate();
    boost::optional<double> autosizedDesignAirFlowRate() const;

    boost::optional<double> designAirFlowRateFanPower() const;
    bool isDesignAirFlowRateFanPowerAutosized() const;
    bool setDesignAirFlowRateFanPower(double designAirFlowRateFanPower);
    void autosizeDesignAirFlowRateFanPower();
    boost::optional<double> autosizedDesignAirFlowRateFanPower() const;

   protected:
    using ImplType = detail::FluidCoolerSingleSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FluidCoolerSingleSpeed(std::shared_ptr<detail::FluidCoolerSingleSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
