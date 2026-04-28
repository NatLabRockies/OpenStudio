/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILWATERHEATINGDESUPERHEATER_IMPL_HPP
#define EPMODEL_COILWATERHEATINGDESUPERHEATER_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
  class Schedule;
  class CurveBiquadratic;
  class ModelObject;
  namespace detail {

    class EPMODEL_API CoilWaterHeatingDesuperheater_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~CoilWaterHeatingDesuperheater_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      std::vector<ModelObject> children() const override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      boost::optional<CurveBiquadratic> heatReclaimEfficiencyFunctionofTemperatureCurve() const;
      bool setHeatReclaimEfficiencyFunctionofTemperatureCurve(const CurveBiquadratic& curveBiquadratic);
      void resetHeatReclaimEfficiencyFunctionofTemperatureCurve();

      boost::optional<ModelObject> heatingSource() const;
      bool setHeatingSource(const ModelObject& heatingSource);
      void resetHeatingSource();

      bool addToNode(Node& node) override;

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
