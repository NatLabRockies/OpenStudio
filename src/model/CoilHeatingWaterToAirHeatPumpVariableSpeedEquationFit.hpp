/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_HPP
#define MODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_HPP

#include "ModelAPI.hpp"
#include "WaterToAirComponent.hpp"

namespace openstudio {

namespace model {

  class Curve;
  class CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData;
  class AirflowNetworkEquivalentDuct;

  namespace detail {

    class CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl;

  }  // namespace detail

  /** CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit is a WaterToAirComponent that wraps the OpenStudio IDD object 'OS:Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit'. */
  class MODEL_API CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit : public WaterToAirComponent
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    explicit CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(const Model& model);

    explicit CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(const Model& model, const Curve& partLoadFraction);

    virtual ~CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit() override = default;
    // Default the copy and move operators because the virtual dtor is explicit
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit& other) = default;
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit&& other) = default;
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit& operator=(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit&) = default;
    CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit& operator=(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit&&) = default;

    //@}

    static IddObjectType iddObjectType();

    /** @name Getters */
    //@{

    Schedule availabilitySchedule() const;

    int nominalSpeedLevel() const;

    boost::optional<double> ratedHeatingCapacityAtSelectedNominalSpeedLevel() const;

    bool isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const;

    boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;

    bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;

    boost::optional<double> ratedWaterFlowRateAtSelectedNominalSpeedLevel() const;

    bool isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const;

    Curve energyPartLoadFractionCurve() const;

    //@}
    /** @name Setters */
    //@{

    bool setAvailabilitySchedule(Schedule& schedule);

    bool setNominalSpeedLevel(int nominalSpeedLevel);

    bool setRatedHeatingCapacityAtSelectedNominalSpeedLevel(double ratedHeatingCapacityAtSelectedNominalSpeedLevel);

    void autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();

    bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);

    void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();

    bool setRatedWaterFlowRateAtSelectedNominalSpeedLevel(double ratedWaterFlowRateAtSelectedNominalSpeedLevel);

    void autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();

    bool setEnergyPartLoadFractionCurve(const Curve& curve);

    //@}
    /** @name Other */
    //@{

    std::vector<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData> speeds() const;

    bool addSpeed(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed);

    void removeSpeed(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed);

    void removeAllSpeeds();

    /** Returns an equivalent duct object, creating a new one if an object is not already attached. */
    AirflowNetworkEquivalentDuct getAirflowNetworkEquivalentDuct(double length, double diameter);

    /** Returns the attached equivalent duct object if there is one. */
    boost::optional<AirflowNetworkEquivalentDuct> airflowNetworkEquivalentDuct() const;

    boost::optional<double> autosizedRatedHeatingCapacityAtSelectedNominalSpeedLevel() const;

    boost::optional<double> autosizedRatedAirFlowRateAtSelectedNominalSpeedLevel() const;

    boost::optional<double> autosizedRatedWaterFlowRateAtSelectedNominalSpeedLevel() const;

    //@}
   protected:
    /// @cond
    using ImplType = detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl;

    explicit CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit(
      std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl> impl);

    friend class detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    /// @endcond
   private:
    REGISTER_LOGGER("openstudio.model.CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit");
  };

  /** \relates CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit*/
  using OptionalCoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit = boost::optional<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit>;

  /** \relates CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit*/
  using CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitVector = std::vector<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit>;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_HPP
