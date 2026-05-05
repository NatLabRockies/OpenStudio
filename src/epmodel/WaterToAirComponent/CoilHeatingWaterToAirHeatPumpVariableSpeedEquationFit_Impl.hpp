/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_IMPL_HPP
#define EPMODEL_COILHEATINGWATERTOAIRHEATPUMPVARIABLESPEEDEQUATIONFIT_IMPL_HPP

#include "WaterToAirComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Curve;
  class Schedule;
  class CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit;
  class CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData;
  class AirflowNetworkDistributionComponentCoil;

  namespace detail {

    std::string transientSpeedDataName(const openstudio::epmodel::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit& parent, unsigned speedIndex);

    class EPMODEL_API CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl : public WaterToAirComponent_Impl
    {
     public:
      using WaterToAirComponent_Impl::WaterToAirComponent_Impl;
      virtual ~CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl() override = default;

      unsigned airInletPort() const override;
      unsigned airOutletPort() const override;
      unsigned waterInletPort() const override;
      unsigned waterOutletPort() const override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      int nominalSpeedLevel() const;
      bool setNominalSpeedLevel(int nominalSpeedLevel);

      boost::optional<double> ratedHeatingCapacityAtSelectedNominalSpeedLevel() const;
      bool setRatedHeatingCapacityAtSelectedNominalSpeedLevel(double ratedHeatingCapacityAtSelectedNominalSpeedLevel);
      bool isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized() const;
      void autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();
      boost::optional<double> autosizedRatedHeatingCapacityAtSelectedNominalSpeedLevel() const;

      boost::optional<double> ratedAirFlowRateAtSelectedNominalSpeedLevel() const;
      bool setRatedAirFlowRateAtSelectedNominalSpeedLevel(double ratedAirFlowRateAtSelectedNominalSpeedLevel);
      bool isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() const;
      void autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
      boost::optional<double> autosizedRatedAirFlowRateAtSelectedNominalSpeedLevel() const;

      boost::optional<double> ratedWaterFlowRateAtSelectedNominalSpeedLevel() const;
      bool setRatedWaterFlowRateAtSelectedNominalSpeedLevel(double ratedWaterFlowRateAtSelectedNominalSpeedLevel);
      bool isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized() const;
      void autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();

      boost::optional<double> autosizedRatedWaterFlowRateAtSelectedNominalSpeedLevel() const;

      Curve energyPartLoadFractionCurve() const;
      bool setEnergyPartLoadFractionCurve(const Curve& curve);

      std::vector<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData> speeds() const;
      bool addSpeed(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed);
      void removeSpeed(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData& speed);
      void removeAllSpeeds();

      AirflowNetworkDistributionComponentCoil getAirflowNetworkEquivalentDuct(double length, double diameter);
      boost::optional<AirflowNetworkDistributionComponentCoil> airflowNetworkEquivalentDuct() const;

      std::vector<ModelObject> children() const override;
      std::vector<IdfObject> remove() override;

      void setConstructorFieldDefaults();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
