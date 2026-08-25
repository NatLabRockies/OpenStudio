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

/** \brief A single-speed fluid cooler.
 *
 * \par EnergyPlus object
 * \epobject{group-condenser-equipment.html#fluidcoolersinglespeed,FluidCooler:SingleSpeed}
 *
 * \par Important behavior
 * The outdoor-air inlet node relationship maintains the EnergyPlus OutdoorAir node declaration and plant placement is supply-side only.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::FluidCoolerSingleSpeed</code>.
 *
 * \par Known limitations
 * Autosized-value getters cannot resolve SQL sizing results.
 */
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
