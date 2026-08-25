/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERAIRTOAIRSENSIBLEANDLATENT_HPP
#define EPMODEL_HEATEXCHANGERAIRTOAIRSENSIBLEANDLATENT_HPP

#include "EPModelAPI.hpp"
#include "AirToAirComponent/AirToAirComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class Curve;

  namespace detail {
    class HeatExchangerAirToAirSensibleAndLatent_Impl;
  }

  /** \brief Represents the EnergyPlus HeatExchanger:AirToAir:SensibleAndLatent object.
   *
   * \par EnergyPlus object
   * \epobject{group-heat-recovery.html#heatexchangerairtoairsensibleandlatent,HeatExchanger:AirToAir:SensibleAndLatent}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::HeatExchangerAirToAirSensibleAndLatent</code>. <b>Not yet available:</b> historical 75% effectiveness compatibility helpers, airflow-network equivalent-duct helpers, and arbitrary multi-exchanger ordering conveniences.
   *
   * \par Known limitations
   * The four-air-port placement is coordinated as one component; specialized outdoor-air-system workflows are the supported topology.
   */
  class EPMODEL_API HeatExchangerAirToAirSensibleAndLatent : public AirToAirComponent
  {
   public:
    explicit HeatExchangerAirToAirSensibleAndLatent(const Model& model);

    virtual ~HeatExchangerAirToAirSensibleAndLatent() override = default;
    HeatExchangerAirToAirSensibleAndLatent(const HeatExchangerAirToAirSensibleAndLatent& other) = default;
    HeatExchangerAirToAirSensibleAndLatent(HeatExchangerAirToAirSensibleAndLatent&& other) = default;
    HeatExchangerAirToAirSensibleAndLatent& operator=(const HeatExchangerAirToAirSensibleAndLatent&) = default;
    HeatExchangerAirToAirSensibleAndLatent& operator=(HeatExchangerAirToAirSensibleAndLatent&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatExchangerTypeValues();
    static std::vector<std::string> frostControlTypeValues();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<Curve> sensibleEffectivenessofHeatingAirFlowCurve() const;
    bool setSensibleEffectivenessofHeatingAirFlowCurve(const Curve& curve);
    void resetSensibleEffectivenessofHeatingAirFlowCurve();

    boost::optional<Curve> latentEffectivenessofHeatingAirFlowCurve() const;
    bool setLatentEffectivenessofHeatingAirFlowCurve(const Curve& curve);
    void resetLatentEffectivenessofHeatingAirFlowCurve();

    boost::optional<Curve> sensibleEffectivenessofCoolingAirFlowCurve() const;
    bool setSensibleEffectivenessofCoolingAirFlowCurve(const Curve& curve);
    void resetSensibleEffectivenessofCoolingAirFlowCurve();

    boost::optional<Curve> latentEffectivenessofCoolingAirFlowCurve() const;
    bool setLatentEffectivenessofCoolingAirFlowCurve(const Curve& curve);
    void resetLatentEffectivenessofCoolingAirFlowCurve();

    /** @name Field Accessors */
    //@{

    boost::optional<double> nominalSupplyAirFlowRate() const;
    bool setNominalSupplyAirFlowRate(double nominalSupplyAirFlowRate);
    bool isNominalSupplyAirFlowRateAutosized() const;
    void autosizeNominalSupplyAirFlowRate();

    double sensibleEffectivenessat100HeatingAirFlow() const;
    bool setSensibleEffectivenessat100HeatingAirFlow(double sensibleEffectivenessat100HeatingAirFlow);

    double latentEffectivenessat100HeatingAirFlow() const;
    bool setLatentEffectivenessat100HeatingAirFlow(double latentEffectivenessat100HeatingAirFlow);

    double sensibleEffectivenessat100CoolingAirFlow() const;
    bool setSensibleEffectivenessat100CoolingAirFlow(double sensibleEffectivenessat100CoolingAirFlow);

    double latentEffectivenessat100CoolingAirFlow() const;
    bool setLatentEffectivenessat100CoolingAirFlow(double latentEffectivenessat100CoolingAirFlow);

    double nominalElectricPower() const;
    bool setNominalElectricPower(double nominalElectricPower);

    bool supplyAirOutletTemperatureControl() const;
    bool setSupplyAirOutletTemperatureControl(bool supplyAirOutletTemperatureControl);

    std::string heatExchangerType() const;
    bool setHeatExchangerType(const std::string& heatExchangerType);

    std::string frostControlType() const;
    bool setFrostControlType(const std::string& frostControlType);

    double thresholdTemperature() const;
    bool setThresholdTemperature(double thresholdTemperature);
    bool isThresholdTemperatureDefaulted() const;
    void resetThresholdTemperature();

    boost::optional<double> initialDefrostTimeFraction() const;
    bool setInitialDefrostTimeFraction(double initialDefrostTimeFraction);
    void resetInitialDefrostTimeFraction();

    boost::optional<double> rateofDefrostTimeFractionIncrease() const;
    bool setRateofDefrostTimeFractionIncrease(double rateofDefrostTimeFractionIncrease);
    void resetRateofDefrostTimeFractionIncrease();

    bool economizerLockout() const;
    bool setEconomizerLockout(bool economizerLockout);

    //@}

   protected:
    using ImplType = detail::HeatExchangerAirToAirSensibleAndLatent_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HeatExchangerAirToAirSensibleAndLatent(std::shared_ptr<detail::HeatExchangerAirToAirSensibleAndLatent_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
