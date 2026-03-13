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

  namespace detail {
    class CoilWaterHeatingDesuperheater_Impl;
  }

  class EPMODEL_API CoilWaterHeatingDesuperheater : public StraightComponent
  {
   public:
    explicit CoilWaterHeatingDesuperheater(const Model& model);

    virtual ~CoilWaterHeatingDesuperheater() override = default;
    CoilWaterHeatingDesuperheater(const CoilWaterHeatingDesuperheater& other) = default;
    CoilWaterHeatingDesuperheater(CoilWaterHeatingDesuperheater&& other) = default;
    CoilWaterHeatingDesuperheater& operator=(const CoilWaterHeatingDesuperheater&) = default;
    CoilWaterHeatingDesuperheater& operator=(CoilWaterHeatingDesuperheater&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::CoilWaterHeatingDesuperheater scalar accessor names/signatures.
    // - Field Mapping: Preserved scalar APIs map directly to E+ Coil:WaterHeating:Desuperheater scalar fields.
    // - Field Mapping: Relationship-like fields (schedules, tank/heating source, curve, and node links) are excluded in this pass.
    // - ForwardTranslator evidence: ForwardTranslateCoilWaterHeatingDesuperheater.cpp writes these scalar fields directly.
    // - TODO(parity): Add excluded relationship APIs incrementally without changing preserved scalar signatures.

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
