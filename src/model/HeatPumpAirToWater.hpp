/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_HEATPUMPAIRTOWATER_HPP
#define MODEL_HEATPUMPAIRTOWATER_HPP

#include "ModelAPI.hpp"
#include "StraightComponent.hpp"

namespace openstudio {

namespace model {

  class Schedule;
  class Curve;
  class HeatPumpAirToWaterHeating;
  class HeatPumpAirToWaterCooling;
  class PlantLoop;

  namespace detail {

    class HeatPumpAirToWater_Impl;

  }  // namespace detail

  /** HeatPumpAirToWater is a StraightComponent that wraps the OpenStudio IDD object 'OS:HeatPump:AirToWater'. */
  class MODEL_API HeatPumpAirToWater : public StraightComponent
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    explicit HeatPumpAirToWater(const Model& model);

    virtual ~HeatPumpAirToWater() = default;
    // Default the copy and move operators because the virtual dtor is explicit
    HeatPumpAirToWater(const HeatPumpAirToWater& other) = default;
    HeatPumpAirToWater(HeatPumpAirToWater&& other) = default;
    HeatPumpAirToWater& operator=(const HeatPumpAirToWater&) = default;
    HeatPumpAirToWater& operator=(HeatPumpAirToWater&&) = default;

    //@}

    static IddObjectType iddObjectType();

    static std::vector<std::string> operatingModeControlMethodValues();

    static std::vector<std::string> operatingModeControlOptionforMultipleUnitValues();

    static std::vector<std::string> heatPumpDefrostControlValues();

    static std::vector<std::string> controlTypeValues();

    /** @name Getters */
    //@{

    std::string operatingModeControlMethod() const;

    std::string operatingModeControlOptionforMultipleUnit() const;

    boost::optional<Schedule> operatingModeControlSchedule() const;

    double minimumPartLoadRatio() const;

    boost::optional<std::string> airInletNodeName() const;

    boost::optional<std::string> airOutletNodeName() const;

    double maximumOutdoorDryBulbTemperatureForDefrostOperation() const;

    std::string heatPumpDefrostControl() const;

    double heatPumpDefrostTimePeriodFraction() const;

    double resistiveDefrostHeaterCapacity() const;

    boost::optional<Curve> defrostEnergyInputRatioFunctionofTemperatureCurve() const;

    int heatPumpMultiplier() const;

    std::string controlType() const;

    double crankcaseHeaterCapacity() const;

    boost::optional<Curve> crankcaseHeaterCapacityFunctionofTemperatureCurve() const;

    double maximumAmbientTemperatureforCrankcaseHeaterOperation() const;

    boost::optional<HeatPumpAirToWaterHeating> heatingOperationMode() const;

    boost::optional<HeatPumpAirToWaterCooling> coolingOperationMode() const;

    //@}
    /** @name Setters */
    //@{

    bool setOperatingModeControlMethod(const std::string& operatingModeControlMethod);

    bool setOperatingModeControlOptionforMultipleUnit(const std::string& operatingModeControlOptionforMultipleUnit);

    bool setOperatingModeControlSchedule(Schedule& operatingModeControlSchedule);

    void resetOperatingModeControlSchedule();

    bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

    bool setAirInletNodeName(const std::string& airInletNodeName);

    void resetAirInletNodeName();

    bool setAirOutletNodeName(const std::string& airOutletNodeName);

    void resetAirOutletNodeName();

    bool setMaximumOutdoorDryBulbTemperatureForDefrostOperation(double maximumOutdoorDryBulbTemperatureForDefrostOperation);

    bool setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl);

    bool setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction);

    bool setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity);

    bool setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& defrostEnergyInputRatioFunctionofTemperatureCurve);

    void resetDefrostEnergyInputRatioFunctionofTemperatureCurve();

    bool setHeatPumpMultiplier(int heatPumpMultiplier);

    bool setControlType(const std::string& controlType);

    bool setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity);

    bool setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& crankcaseHeaterCapacityFunctionofTemperatureCurve);

    void resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();

    bool setMaximumAmbientTemperatureforCrankcaseHeaterOperation(double maximumAmbientTemperatureforCrankcaseHeaterOperation);

    bool setHeatingOperationMode(const HeatPumpAirToWaterHeating& heatingOperationMode);

    void resetHeatingOperationMode();

    bool setCoolingOperationMode(const HeatPumpAirToWaterCooling& coolingOperationMode);

    void resetCoolingOperationMode();

    //@}
    /** @name Other */
    //@{

    // If there is a Cooling Operation Mode attached, it will lookup the PlantLoop it is connected to
    boost::optional<PlantLoop> coolingLoop() const;

    // If there is a Heating Operation Mode attached, it will lookup the PlantLoop it is connected to
    boost::optional<PlantLoop> heatingLoop() const;

    // Autosize methods
    boost::optional<double> autosizedRatedAirFlowRateinHeatingMode() const;
    boost::optional<double> autosizedRatedWaterFlowRateinHeatingMode() const;
    boost::optional<double> autosizedRatedAirFlowRateinCoolingMode() const;
    boost::optional<double> autosizedRatedWaterFlowRateinCoolingMode() const;
    boost::optional<double> autosizedRatedHeatingCapacity() const;
    boost::optional<double> autosizedRatedCoolingCapacity() const;

    //@}
   protected:
    /// @cond
    using ImplType = detail::HeatPumpAirToWater_Impl;

    explicit HeatPumpAirToWater(std::shared_ptr<detail::HeatPumpAirToWater_Impl> impl);

    friend class detail::HeatPumpAirToWater_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    /// @endcond
   private:
    REGISTER_LOGGER("openstudio.model.HeatPumpAirToWater");
  };

  /** \relates HeatPumpAirToWater*/
  using OptionalHeatPumpAirToWater = boost::optional<HeatPumpAirToWater>;

  /** \relates HeatPumpAirToWater*/
  using HeatPumpAirToWaterVector = std::vector<HeatPumpAirToWater>;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_HEATPUMPAIRTOWATER_HPP
