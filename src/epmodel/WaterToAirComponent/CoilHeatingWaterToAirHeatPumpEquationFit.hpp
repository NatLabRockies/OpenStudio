/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP
#define EPMODEL_COILHEATINGWATERTOAIRHEATPUMPEQUATIONFIT_HPP

#include "EPModelAPI.hpp"
#include "WaterToAirComponent.hpp"

#include <utilities/core/Deprecated.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class Schedule;
class Curve;
class AirflowNetworkDistributionComponentCoil;

namespace detail {
class CoilHeatingWaterToAirHeatPumpEquationFit_Impl;
}

class EPMODEL_API CoilHeatingWaterToAirHeatPumpEquationFit : public WaterToAirComponent
{
 public:
  CoilHeatingWaterToAirHeatPumpEquationFit(const Model& model, const Curve& heatingCapacityCurve, const Curve& heatingPowerConsumptionCurve);
  explicit CoilHeatingWaterToAirHeatPumpEquationFit(const Model& model);

  virtual ~CoilHeatingWaterToAirHeatPumpEquationFit() override = default;
  CoilHeatingWaterToAirHeatPumpEquationFit(const CoilHeatingWaterToAirHeatPumpEquationFit& other) = default;
  CoilHeatingWaterToAirHeatPumpEquationFit(CoilHeatingWaterToAirHeatPumpEquationFit&& other) = default;
  CoilHeatingWaterToAirHeatPumpEquationFit& operator=(const CoilHeatingWaterToAirHeatPumpEquationFit&) = default;
  CoilHeatingWaterToAirHeatPumpEquationFit& operator=(CoilHeatingWaterToAirHeatPumpEquationFit&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Parity with documented deltas. The canonical schedule, curve, constructor, autosized-query, and
  //   deprecated coefficient alias surface is preserved here.
  // - Canonical Counterpart: openstudio::model::CoilHeatingWaterToAirHeatPumpEquationFit.
  // - Implemented Parity: `availabilitySchedule`, the two required curve relationships,
  //   `partLoadFractionCorrelationCurve`, the canonical constructors, the deprecated coefficient aliases that delegate
  //   through the stored curves, the scalar fit fields, and the autosized-value query helpers preserve the canonical
  //   public contract.
  // - Implemented Parity: the canonical equivalent-duct helper surface lands on epmodel's
  //   `AirflowNetworkDistributionComponentCoil`, which is the EnergyPlus object written by the
  //   model-side `AirflowNetworkEquivalentDuct` translator path for coils.
  // - Documented Delta: Autosized-value query helpers currently return `none`, which is the same documented
  //   limitation already used by the nearby equation-fit cooling coil until epmodel grows canonical SQL-backed
  //   autosized results.
  // - Field/Storage Mapping: Availability schedule and curve relationships are stored directly on the EnergyPlus
  //   `Coil:Heating:WaterToAirHeatPump:EquationFit` object, and scalar fit fields map directly to the corresponding
  //   EnergyPlus fields.
  // - Evidence: `src/model/CoilHeatingWaterToAirHeatPumpEquationFit.hpp`,
  //   `src/model/CoilHeatingWaterToAirHeatPumpEquationFit.cpp`,
  //   `src/energyplus/ForwardTranslator/ForwardTranslateCoilHeatingWaterToAirHeatPumpEquationFit.cpp`, and
  //   `src/epmodel/test/CoilHeatingWaterToAirHeatPumpEquationFit_GTest.cpp`.
  // - Remaining Parity Work: Extend the same AFN mapping surface to the remaining water-to-air heat pump coil family
  //   wrappers when that campaign reaches them.
  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  boost::optional<double> ratedAirFlowRate() const;
  bool isRatedAirFlowRateDefaulted() const;
  bool isRatedAirFlowRateAutosized() const;
  bool setRatedAirFlowRate(boost::optional<double> ratedAirFlowRate);
  bool setRatedAirFlowRate(double ratedAirFlowRate);
  void resetRatedAirFlowRate();
  void autosizeRatedAirFlowRate();
  boost::optional<double> autosizedRatedAirFlowRate() const;

  boost::optional<double> ratedWaterFlowRate() const;
  bool isRatedWaterFlowRateDefaulted() const;
  bool isRatedWaterFlowRateAutosized() const;
  bool setRatedWaterFlowRate(boost::optional<double> ratedWaterFlowRate);
  bool setRatedWaterFlowRate(double ratedWaterFlowRate);
  void resetRatedWaterFlowRate();
  void autosizeRatedWaterFlowRate();
  boost::optional<double> autosizedRatedWaterFlowRate() const;

  boost::optional<double> ratedHeatingCapacity() const;
  bool isRatedHeatingCapacityDefaulted() const;
  bool isRatedHeatingCapacityAutosized() const;
  bool setRatedHeatingCapacity(boost::optional<double> ratedHeatingCapacity);
  bool setRatedHeatingCapacity(double ratedHeatingCapacity);
  void resetRatedHeatingCapacity();
  void autosizeRatedHeatingCapacity();
  boost::optional<double> autosizedRatedHeatingCapacity() const;

  double ratedHeatingCoefficientofPerformance() const;
  bool isRatedHeatingCoefficientofPerformanceDefaulted() const;
  bool setRatedHeatingCoefficientofPerformance(double ratedHeatingCoefficientofPerformance);
  void resetRatedHeatingCoefficientofPerformance();

  double ratedEnteringWaterTemperature() const;
  bool setRatedEnteringWaterTemperature(double ratedEnteringWaterTemperature);

  double ratedEnteringAirDryBulbTemperature() const;
  bool setRatedEnteringAirDryBulbTemperature(double ratedEnteringAirDryBulbTemperature);

  Curve heatingCapacityCurve() const;
  bool setHeatingCapacityCurve(const Curve& heatingCapacityCurve);
  OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient1() const;
  OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient1(double heatingCapacityCoefficient1);
  OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient2() const;
  OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient2(double heatingCapacityCoefficient2);
  OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient3() const;
  OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient3(double heatingCapacityCoefficient3);
  OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient4() const;
  OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient4(double heatingCapacityCoefficient4);
  OS_DEPRECATED(3, 2, 0) double heatingCapacityCoefficient5() const;
  OS_DEPRECATED(3, 2, 0) bool setHeatingCapacityCoefficient5(double heatingCapacityCoefficient5);

  Curve heatingPowerConsumptionCurve() const;
  bool setHeatingPowerConsumptionCurve(const Curve& heatingPowerConsumptionCurve);
  OS_DEPRECATED(3, 2, 0) double heatingPowerConsumptionCoefficient1() const;
  OS_DEPRECATED(3, 2, 0) bool setHeatingPowerConsumptionCoefficient1(double heatingPowerConsumptionCoefficient1);
  OS_DEPRECATED(3, 2, 0) double heatingPowerConsumptionCoefficient2() const;
  OS_DEPRECATED(3, 2, 0) bool setHeatingPowerConsumptionCoefficient2(double heatingPowerConsumptionCoefficient2);
  OS_DEPRECATED(3, 2, 0) double heatingPowerConsumptionCoefficient3() const;
  OS_DEPRECATED(3, 2, 0) bool setHeatingPowerConsumptionCoefficient3(double heatingPowerConsumptionCoefficient3);
  OS_DEPRECATED(3, 2, 0) double heatingPowerConsumptionCoefficient4() const;
  OS_DEPRECATED(3, 2, 0) bool setHeatingPowerConsumptionCoefficient4(double heatingPowerConsumptionCoefficient4);
  OS_DEPRECATED(3, 2, 0) double heatingPowerConsumptionCoefficient5() const;
  OS_DEPRECATED(3, 2, 0) bool setHeatingPowerConsumptionCoefficient5(double heatingPowerConsumptionCoefficient5);

  Curve partLoadFractionCorrelationCurve() const;
  bool setPartLoadFractionCorrelationCurve(const Curve& partLoadFractionCorrelationCurve);

  double ratioofRatedHeatingCapacitytoRatedCoolingCapacity() const;
  bool setRatioofRatedHeatingCapacitytoRatedCoolingCapacity(double ratioofRatedHeatingCapacitytoRatedCoolingCapacity);

  AirflowNetworkDistributionComponentCoil getAirflowNetworkEquivalentDuct(double length, double diameter);
  boost::optional<AirflowNetworkDistributionComponentCoil> airflowNetworkEquivalentDuct() const;

 protected:
  using ImplType = detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilHeatingWaterToAirHeatPumpEquationFit(std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpEquationFit_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
