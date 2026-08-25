/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGDESUPERHEATER_HPP
#define EPMODEL_COILWATERHEATINGDESUPERHEATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class CurveBiquadratic;
  class ModelObject;

  namespace detail {
    class CoilWaterHeatingDesuperheater_Impl;
  }

  /** \brief Represents a water-heating desuperheater coil.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#coilwaterheatingdesuperheater,Coil:WaterHeating:Desuperheater}.
   *
   * \par Important behavior
   * The required setpoint schedule and availability schedule map to the EnergyPlus object; the direct one-argument constructor remains IDF-compatible.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilWaterHeatingDesuperheater</code>. <b>Added:</b> EPModel exposes <code>addToNode()</code>. <b>Not yet available:</b> <code>addToHeatRejectionTarget()</code> and <code>removeFromHeatRejectionTarget()</code>, plus broader tank-link conveniences.
   * \par Known limitations
   * The one-argument constructor does not synthesize the required setpoint schedule.
   */
  class EPMODEL_API CoilWaterHeatingDesuperheater : public StraightComponent
  {
   public:
    /** EnergyPlus-compatible construction. The object remains structurally incomplete until a setpoint temperature schedule is supplied. */
    explicit CoilWaterHeatingDesuperheater(const Model& model);
    explicit CoilWaterHeatingDesuperheater(const Model& model, Schedule& setpointTemperatureSchedule);

    virtual ~CoilWaterHeatingDesuperheater() override = default;
    CoilWaterHeatingDesuperheater(const CoilWaterHeatingDesuperheater& other) = default;
    CoilWaterHeatingDesuperheater(CoilWaterHeatingDesuperheater&& other) = default;
    CoilWaterHeatingDesuperheater& operator=(const CoilWaterHeatingDesuperheater&) = default;
    CoilWaterHeatingDesuperheater& operator=(CoilWaterHeatingDesuperheater&&) = default;

    static IddObjectType iddObjectType();

    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    Schedule setpointTemperatureSchedule() const;
    bool setSetpointTemperatureSchedule(Schedule& schedule);

    boost::optional<CurveBiquadratic> heatReclaimEfficiencyFunctionofTemperatureCurve() const;
    bool setHeatReclaimEfficiencyFunctionofTemperatureCurve(const CurveBiquadratic& curveBiquadratic);
    void resetHeatReclaimEfficiencyFunctionofTemperatureCurve();

    boost::optional<ModelObject> heatingSource() const;
    bool setHeatingSource(const ModelObject& heatingSource);
    void resetHeatingSource();

    bool addToNode(Node& node);

    double deadBandTemperatureDifference() const;
    bool isDeadBandTemperatureDifferenceDefaulted() const;
    bool setDeadBandTemperatureDifference(double deadBandTemperatureDifference);
    void resetDeadBandTemperatureDifference();

    boost::optional<double> ratedHeatReclaimRecoveryEfficiency() const;
    bool setRatedHeatReclaimRecoveryEfficiency(double ratedHeatReclaimRecoveryEfficiency);
    void resetRatedHeatReclaimRecoveryEfficiency();

    double ratedInletWaterTemperature() const;
    bool setRatedInletWaterTemperature(double ratedInletWaterTemperature);

    double ratedOutdoorAirTemperature() const;
    bool setRatedOutdoorAirTemperature(double ratedOutdoorAirTemperature);

    double maximumInletWaterTemperatureforHeatReclaim() const;
    bool setMaximumInletWaterTemperatureforHeatReclaim(double maximumInletWaterTemperatureforHeatReclaim);

    double waterFlowRate() const;
    bool setWaterFlowRate(double waterFlowRate);

    double waterPumpPower() const;
    bool isWaterPumpPowerDefaulted() const;
    bool setWaterPumpPower(double waterPumpPower);
    void resetWaterPumpPower();

    double fractionofPumpHeattoWater() const;
    bool isFractionofPumpHeattoWaterDefaulted() const;
    bool setFractionofPumpHeattoWater(double fractionofPumpHeattoWater);
    void resetFractionofPumpHeattoWater();

    double onCycleParasiticElectricLoad() const;
    bool isOnCycleParasiticElectricLoadDefaulted() const;
    bool setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad);
    void resetOnCycleParasiticElectricLoad();

    double offCycleParasiticElectricLoad() const;
    bool isOffCycleParasiticElectricLoadDefaulted() const;
    bool setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad);
    void resetOffCycleParasiticElectricLoad();

   protected:
    using ImplType = detail::CoilWaterHeatingDesuperheater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilWaterHeatingDesuperheater(std::shared_ptr<detail::CoilWaterHeatingDesuperheater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
