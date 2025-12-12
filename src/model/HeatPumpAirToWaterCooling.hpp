/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_HEATPUMPAIRTOWATERCOOLING_HPP
#define MODEL_HEATPUMPAIRTOWATERCOOLING_HPP

#include "ModelAPI.hpp"
#include "StraightComponent.hpp"

namespace openstudio {

namespace model {

  class Curve;
  class HeatPumpAirToWater;
  class HeatPumpAirToWaterCoolingSpeedData;
  class Schedule;

  namespace detail {

    class HeatPumpAirToWaterCooling_Impl;

  }  // namespace detail

  /** HeatPumpAirToWaterCooling is a StraightComponent that wraps the OpenStudio IDD object 'OS:HeatPump:AirToWater:Cooling'. */
  class MODEL_API HeatPumpAirToWaterCooling : public StraightComponent
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    explicit HeatPumpAirToWaterCooling(const Model& model);

    virtual ~HeatPumpAirToWaterCooling() = default;
    // Default the copy and move operators because the virtual dtor is explicit
    HeatPumpAirToWaterCooling(const HeatPumpAirToWaterCooling& other) = default;
    HeatPumpAirToWaterCooling(HeatPumpAirToWaterCooling&& other) = default;
    HeatPumpAirToWaterCooling& operator=(const HeatPumpAirToWaterCooling&) = default;
    HeatPumpAirToWaterCooling& operator=(HeatPumpAirToWaterCooling&&) = default;

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

    boost::optional<HeatPumpAirToWaterCoolingSpeedData> boosterModeOnSpeed() const;

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

    bool setBoosterModeOnSpeed(const HeatPumpAirToWaterCoolingSpeedData& boosterModeOnSpeed);

    void resetBoosterModeOnSpeed();

    //@}
    /** @name Other */
    //@{

    /** Return the performance data for each stage. **/
    std::vector<HeatPumpAirToWaterCoolingSpeedData> speeds() const;

    unsigned numberOfSpeeds() const;

    /*
     * Get the index of a given HeatPumpAirToWaterCoolingSpeedData (1-indexed)
     */
    boost::optional<unsigned> speedIndex(const HeatPumpAirToWaterCoolingSpeedData& speed) const;

    /*
     * Add a new speed after all of the existing speeds.
     */
    bool addSpeed(const HeatPumpAirToWaterCoolingSpeedData& speed);

    /*
     * Add a new HeatPumpAirToWaterCoolingSpeedData to the list which a given index (1 to x).
     * Internally calls addSpeed then setSpeedIndex, see remarks there
     */
    bool addSpeed(const HeatPumpAirToWaterCoolingSpeedData& speed, unsigned index);

    /*
     * You can shuffle the priority of a given HeatPumpAirToWaterCoolingSpeedData after having added it
     * If index is below 1, it's reset to 1.
     * If index is greater than the number of speeds, will reset to last
     */
    bool setSpeedIndex(const HeatPumpAirToWaterCoolingSpeedData& speed, unsigned index);

    /*
     * Set all speeds using a list of HeatPumpAirToWaterCoolingSpeedDatas
     * Internally calls addSpeed, and will return the global status, but will continue trying if there are problems
     * (eg: if you make a vector larger than the number of accepted speeds, or a vector that has a speed from another model, the valid speeds will be
     * added indeed, but it'll eventually return false)
     */
    bool setSpeeds(const std::vector<HeatPumpAirToWaterCoolingSpeedData>& speeds);

    /*
     * Removes all HeatPumpAirToWaterCoolingSpeedDatas in this object
     */
    void removeAllSpeeds();

    /*
     * Remove the given HeatPumpAirToWaterCoolingSpeedData from this object's speeds
     */
    bool removeSpeed(const HeatPumpAirToWaterCoolingSpeedData& speed);

    /*
     * Remove the HeatPumpAirToWaterCoolingSpeedData at the given index (1-indexed)
     */
    bool removeSpeed(unsigned index);

    // Convenience function to return the HeatPumpAirToWater object that reference this cooling coil if any
    boost::optional<HeatPumpAirToWater> heatPumpAirToWater() const;

    // Autosize methods
    boost::optional<double> autosizedRatedAirFlowRate() const;
    boost::optional<double> autosizedRatedWaterFlowRate() const;
    boost::optional<double> autosizedRatedCoolingCapacity() const;  // Convenience method

    //@}
   protected:
    /// @cond
    using ImplType = detail::HeatPumpAirToWaterCooling_Impl;

    explicit HeatPumpAirToWaterCooling(std::shared_ptr<detail::HeatPumpAirToWaterCooling_Impl> impl);

    friend class detail::HeatPumpAirToWaterCooling_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    /// @endcond
   private:
    REGISTER_LOGGER("openstudio.model.HeatPumpAirToWaterCooling");
  };

  /** \relates HeatPumpAirToWaterCooling*/
  using OptionalHeatPumpAirToWaterCooling = boost::optional<HeatPumpAirToWaterCooling>;

  /** \relates HeatPumpAirToWaterCooling*/
  using HeatPumpAirToWaterCoolingVector = std::vector<HeatPumpAirToWaterCooling>;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_HEATPUMPAIRTOWATERCOOLING_HPP
