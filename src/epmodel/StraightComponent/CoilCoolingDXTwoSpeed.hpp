/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXTWOSPEED_HPP
#define EPMODEL_COILCOOLINGDXTWOSPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Schedule;
  class Curve;

  namespace detail {
    class CoilCoolingDXTwoSpeed_Impl;
  }

  class EPMODEL_API CoilCoolingDXTwoSpeed : public StraightComponent
  {
   public:
    explicit CoilCoolingDXTwoSpeed(const Model& model);
    explicit CoilCoolingDXTwoSpeed(const Model& model, Schedule& availabilitySchedule, const Curve& coolingCurveFofTemp,
                                   const Curve& coolingCurveFofFlow, const Curve& energyInputRatioFofTemp, const Curve& energyInputRatioFofFlow,
                                   const Curve& partLoadFraction, const Curve& lowSpeedCoolingCurveFofTemp,
                                   const Curve& lowSpeedEnergyInputRatioFofTemp);

    virtual ~CoilCoolingDXTwoSpeed() override = default;
    CoilCoolingDXTwoSpeed(const CoilCoolingDXTwoSpeed& other) = default;
    CoilCoolingDXTwoSpeed(CoilCoolingDXTwoSpeed&& other) = default;
    CoilCoolingDXTwoSpeed& operator=(const CoilCoolingDXTwoSpeed&) = default;
    CoilCoolingDXTwoSpeed& operator=(CoilCoolingDXTwoSpeed&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> condenserTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The core two-speed DX scalar surface, required schedule / curve relationships, and the current epmodel
    //   supply-side air-loop insertion path are present, while AFN, condenser-air-node, tank-link, and broader OA / DOAS topology helpers
    //   remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilCoolingDXTwoSpeed.
    // - Implemented Parity: `availabilitySchedule`, the high/low-speed performance curves, and `basinHeaterOperatingSchedule` preserve the
    //   canonical naming and child-ownership slice; the relationship constructor and the current supply-side air-loop `addToNode` path are
    //   preserved for the bounded epmodel topology slice; and the high- and low-speed capacity, COP, airflow, fan-power, and condenser controls
    //   preserve the canonical scalar naming and autosize behavior.
    // - Documented Delta: AFN equivalent-duct parity, condenser-air-node helpers, and tank-link helpers from canonical
    //   `openstudio::model::CoilCoolingDXTwoSpeed` remain deferred.
    // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `Coil:Cooling:DX:TwoSpeed` fields.
    // - Evidence: `src/model/CoilCoolingDXTwoSpeed.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDXTwoSpeed.cpp`, and `src/epmodel/test/CoilCoolingDXTwoSpeed_GTest.cpp`.
    // - Remaining Parity Work: Add the deferred AFN, condenser-air-node, tank-link, and broader OA / DOAS topology helpers without changing the
    //   preserved scalar signatures.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<double> ratedHighSpeedTotalCoolingCapacity() const;
    bool isRatedHighSpeedTotalCoolingCapacityAutosized() const;
    bool setRatedHighSpeedTotalCoolingCapacity(double ratedHighSpeedTotalCoolingCapacity);
    void autosizeRatedHighSpeedTotalCoolingCapacity();

    boost::optional<double> ratedHighSpeedSensibleHeatRatio() const;
    bool isRatedHighSpeedSensibleHeatRatioAutosized() const;
    bool setRatedHighSpeedSensibleHeatRatio(double ratedHighSpeedSensibleHeatRatio);
    void autosizeRatedHighSpeedSensibleHeatRatio();

    double ratedHighSpeedCOP() const;
    bool setRatedHighSpeedCOP(double ratedHighSpeedCOP);

    boost::optional<double> ratedHighSpeedAirFlowRate() const;
    bool isRatedHighSpeedAirFlowRateAutosized() const;
    bool setRatedHighSpeedAirFlowRate(double ratedHighSpeedAirFlowRate);
    void autosizeRatedHighSpeedAirFlowRate();

    double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017() const;
    bool setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017);

    double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023() const;
    bool setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023);

    Curve totalCoolingCapacityFunctionOfTemperatureCurve() const;
    bool setTotalCoolingCapacityFunctionOfTemperatureCurve(const Curve& curve);

    Curve totalCoolingCapacityFunctionOfFlowFractionCurve() const;
    bool setTotalCoolingCapacityFunctionOfFlowFractionCurve(const Curve& curve);

    Curve energyInputRatioFunctionOfTemperatureCurve() const;
    bool setEnergyInputRatioFunctionOfTemperatureCurve(const Curve& curve);

    Curve energyInputRatioFunctionOfFlowFractionCurve() const;
    bool setEnergyInputRatioFunctionOfFlowFractionCurve(const Curve& curve);

    Curve partLoadFractionCorrelationCurve() const;
    bool setPartLoadFractionCorrelationCurve(const Curve& curve);

    boost::optional<double> ratedLowSpeedTotalCoolingCapacity() const;
    bool isRatedLowSpeedTotalCoolingCapacityAutosized() const;
    bool setRatedLowSpeedTotalCoolingCapacity(double ratedLowSpeedTotalCoolingCapacity);
    void autosizeRatedLowSpeedTotalCoolingCapacity();

    boost::optional<double> ratedLowSpeedSensibleHeatRatio() const;
    bool isRatedLowSpeedSensibleHeatRatioAutosized() const;
    bool setRatedLowSpeedSensibleHeatRatio(double ratedLowSpeedSensibleHeatRatio);
    void autosizeRatedLowSpeedSensibleHeatRatio();

    double ratedLowSpeedCOP() const;
    bool setRatedLowSpeedCOP(double ratedLowSpeedCOP);

    boost::optional<double> ratedLowSpeedAirFlowRate() const;
    bool isRatedLowSpeedAirFlowRateAutosized() const;
    bool setRatedLowSpeedAirFlowRate(double ratedLowSpeedAirFlowRate);
    void autosizeRatedLowSpeedAirFlowRate();

    double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017() const;
    bool setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017(double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017);

    double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023() const;
    bool setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023(double ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023);

    Curve lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve() const;
    bool setLowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve(const Curve& curve);

    Curve lowSpeedEnergyInputRatioFunctionOfTemperatureCurve() const;
    bool setLowSpeedEnergyInputRatioFunctionOfTemperatureCurve(const Curve& curve);

    boost::optional<Schedule> basinHeaterOperatingSchedule() const;
    bool setBasinHeaterOperatingSchedule(Schedule& schedule);
    void resetBasinHeaterOperatingSchedule();

    std::string condenserType() const;
    bool setCondenserType(const std::string& condenserType);

    double highSpeedEvaporativeCondenserEffectiveness() const;
    bool setHighSpeedEvaporativeCondenserEffectiveness(double highSpeedEvaporativeCondenserEffectiveness);

    boost::optional<double> highSpeedEvaporativeCondenserAirFlowRate() const;
    bool isHighSpeedEvaporativeCondenserAirFlowRateAutosized() const;
    bool setHighSpeedEvaporativeCondenserAirFlowRate(double highSpeedEvaporativeCondenserAirFlowRate);
    void autosizeHighSpeedEvaporativeCondenserAirFlowRate();

    boost::optional<double> highSpeedEvaporativeCondenserPumpRatedPowerConsumption() const;
    bool isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
    bool setHighSpeedEvaporativeCondenserPumpRatedPowerConsumption(double highSpeedEvaporativeCondenserPumpRatedPowerConsumption);
    void autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption();

    double lowSpeedEvaporativeCondenserEffectiveness() const;
    bool setLowSpeedEvaporativeCondenserEffectiveness(double lowSpeedEvaporativeCondenserEffectiveness);

    boost::optional<double> lowSpeedEvaporativeCondenserAirFlowRate() const;
    bool isLowSpeedEvaporativeCondenserAirFlowRateAutosized() const;
    bool setLowSpeedEvaporativeCondenserAirFlowRate(double lowSpeedEvaporativeCondenserAirFlowRate);
    void autosizeLowSpeedEvaporativeCondenserAirFlowRate();

    boost::optional<double> lowSpeedEvaporativeCondenserPumpRatedPowerConsumption() const;
    bool isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized() const;
    bool setLowSpeedEvaporativeCondenserPumpRatedPowerConsumption(double lowSpeedEvaporativeCondenserPumpRatedPowerConsumption);
    void autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption();

    double basinHeaterCapacity() const;
    bool setBasinHeaterCapacity(double basinHeaterCapacity);

    double basinHeaterSetpointTemperature() const;
    bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);

    double minimumOutdoorDryBulbTemperatureforCompressorOperation() const;
    bool setMinimumOutdoorDryBulbTemperatureforCompressorOperation(double minimumOutdoorDryBulbTemperatureforCompressorOperation);

    double unitInternalStaticAirPressure() const;
    bool setUnitInternalStaticAirPressure(double unitInternalStaticAirPressure);

    bool addToNode(Node& node);

   protected:
    using ImplType = detail::CoilCoolingDXTwoSpeed_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilCoolingDXTwoSpeed(std::shared_ptr<detail::CoilCoolingDXTwoSpeed_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
