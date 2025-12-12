/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_HEATPUMPAIRTOWATERHEATING_HPP
#define MODEL_HEATPUMPAIRTOWATERHEATING_HPP

#include "ModelAPI.hpp"
#include "StraightComponent.hpp"

namespace openstudio {

namespace model {

  class Curve;
  class HeatPumpAirToWater;
  class HeatPumpAirToWaterHeatingSpeedData;
  class Schedule;

  namespace detail {

    class HeatPumpAirToWaterHeating_Impl;

  }  // namespace detail

  /** HeatPumpAirToWaterHeating is a StraightComponent that wraps the OpenStudio IDD object 'OS:HeatPump:AirToWater:Heating'. */
  class MODEL_API HeatPumpAirToWaterHeating : public StraightComponent
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    explicit HeatPumpAirToWaterHeating(const Model& model);

    virtual ~HeatPumpAirToWaterHeating() = default;
    // Default the copy and move operators because the virtual dtor is explicit
    HeatPumpAirToWaterHeating(const HeatPumpAirToWaterHeating& other) = default;
    HeatPumpAirToWaterHeating(HeatPumpAirToWaterHeating&& other) = default;
    HeatPumpAirToWaterHeating& operator=(const HeatPumpAirToWaterHeating&) = default;
    HeatPumpAirToWaterHeating& operator=(HeatPumpAirToWaterHeating&&) = default;

    //@}

    static IddObjectType iddObjectType();

    static constexpr unsigned maximum_number_of_speeds = 5;

    /** @name Getters */
    //@{

    Schedule availabilitySchedule() const;

    double ratedInletAirTemperature() const;

    boost::optional<double> ratedAirFlowRate() const;

    bool isRatedAirFlowRateAutosized() const;

    double ratedLeavingWaterTemperature() const;

    boost::optional<double> ratedWaterFlowRate() const;

    bool isRatedWaterFlowRateAutosized() const;

    double minimumOutdoorAirTemperature() const;

    double maximumOutdoorAirTemperature() const;

    boost::optional<Curve> minimumLeavingWaterTemperatureCurve() const;

    boost::optional<Curve> maximumLeavingWaterTemperatureCurve() const;

    double sizingFactor() const;

    boost::optional<HeatPumpAirToWaterHeatingSpeedData> boosterModeOnSpeed() const;

    //@}
    /** @name Setters */
    //@{

    bool setAvailabilitySchedule(Schedule& availabilitySchedule);

    bool setRatedInletAirTemperature(double ratedInletAirTemperature);

    bool setRatedAirFlowRate(double ratedAirFlowRate);

    void autosizeRatedAirFlowRate();

    bool setRatedLeavingWaterTemperature(double ratedLeavingWaterTemperature);

    bool setRatedWaterFlowRate(double ratedWaterFlowRate);

    void autosizeRatedWaterFlowRate();

    bool setMinimumOutdoorAirTemperature(double minimumOutdoorAirTemperature);

    bool setMaximumOutdoorAirTemperature(double maximumOutdoorAirTemperature);

    bool setMinimumLeavingWaterTemperatureCurve(const Curve& minimumLeavingWaterTemperatureCurve);

    void resetMinimumLeavingWaterTemperatureCurve();

    bool setMaximumLeavingWaterTemperatureCurve(const Curve& maximumLeavingWaterTemperatureCurve);

    void resetMaximumLeavingWaterTemperatureCurve();

    bool setSizingFactor(double sizingFactor);

    bool setBoosterModeOnSpeed(const HeatPumpAirToWaterHeatingSpeedData& boosterModeOnSpeed);

    void resetBoosterModeOnSpeed();

    //@}
    /** @name Other */
    //@{

    /** Return the performance data for each stage. **/
    std::vector<HeatPumpAirToWaterHeatingSpeedData> speeds() const;

    unsigned numberOfSpeeds() const;

    /*
   * Get the index of a given HeatPumpAirToWaterHeatingSpeedData (1-indexed)
   */
    boost::optional<unsigned> speedIndex(const HeatPumpAirToWaterHeatingSpeedData& speed) const;

    /*
   * Add a new speed after all of the existing speeds.
   */
    bool addSpeed(const HeatPumpAirToWaterHeatingSpeedData& speed);

    /*
   * Add a new HeatPumpAirToWaterHeatingSpeedData to the list which a given index (1 to x).
   * Internally calls addSpeed then setSpeedIndex, see remarks there
   */
    bool addSpeed(const HeatPumpAirToWaterHeatingSpeedData& speed, unsigned index);

    /*
   * You can shuffle the priority of a given HeatPumpAirToWaterHeatingSpeedData after having added it
   * If index is below 1, it's reset to 1.
   * If index is greater than the number of speeds, will reset to last
   */
    bool setSpeedIndex(const HeatPumpAirToWaterHeatingSpeedData& speed, unsigned index);

    /*
   * Set all speeds using a list of HeatPumpAirToWaterHeatingSpeedDatas
   * Internally calls addSpeed, and will return the global status, but will continue trying if there are problems
   * (eg: if you make a vector larger than the number of accepted speeds, or a vector that has a speed from another model, the valid speeds will be
   * added indeed, but it'll eventually return false)
   */
    bool setSpeeds(const std::vector<HeatPumpAirToWaterHeatingSpeedData>& speeds);

    /*
   * Removes all HeatPumpAirToWaterHeatingSpeedDatas in this object
   */
    void removeAllSpeeds();

    /*
   * Remove the given HeatPumpAirToWaterHeatingSpeedData from this object's speeds
   */
    bool removeSpeed(const HeatPumpAirToWaterHeatingSpeedData& speed);

    /*
   * Remove the HeatPumpAirToWaterHeatingSpeedData at the given index (1-indexed)
   */
    bool removeSpeed(unsigned index);

    // Convenience function to return the HeatPumpAirToWater object that reference this heating coil if any
    boost::optional<HeatPumpAirToWater> heatPumpAirToWater() const;

    // Autosize methods
    boost::optional<double> autosizedRatedAirFlowRate() const;
    boost::optional<double> autosizedRatedWaterFlowRate() const;
    boost::optional<double> autosizedRatedHeatingCapacity() const;  // Convenience method

    //@}
   protected:
    /// @cond
    using ImplType = detail::HeatPumpAirToWaterHeating_Impl;

    explicit HeatPumpAirToWaterHeating(std::shared_ptr<detail::HeatPumpAirToWaterHeating_Impl> impl);

    friend class detail::HeatPumpAirToWaterHeating_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    /// @endcond
   private:
    REGISTER_LOGGER("openstudio.model.HeatPumpAirToWaterHeating");
  };

  /** \relates HeatPumpAirToWaterHeating*/
  using OptionalHeatPumpAirToWaterHeating = boost::optional<HeatPumpAirToWaterHeating>;

  /** \relates HeatPumpAirToWaterHeating*/
  using HeatPumpAirToWaterHeatingVector = std::vector<HeatPumpAirToWaterHeating>;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_HEATPUMPAIRTOWATERHEATING_HPP
