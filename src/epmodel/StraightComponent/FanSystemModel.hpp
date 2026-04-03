/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANSYSTEMMODEL_HPP
#define EPMODEL_FANSYSTEMMODEL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Node;
class Schedule;
class Curve;
class ThermalZone;

namespace detail {
class FanSystemModel_Impl;
}

class EPMODEL_API FanSystemModelSpeed
{
 public:
  explicit FanSystemModelSpeed(double flowFraction);
  FanSystemModelSpeed(double flowFraction, double electricPowerFraction);

  double flowFraction() const;
  boost::optional<double> electricPowerFraction() const;

  bool operator<(const FanSystemModelSpeed& other) const;

 private:
  double m_flowFraction;
  boost::optional<double> m_electricPowerFraction;
};

EPMODEL_API std::ostream& operator<<(std::ostream& out, const FanSystemModelSpeed& speed);

class EPMODEL_API FanSystemModel : public StraightComponent
{
 public:
  explicit FanSystemModel(const Model& model);

  virtual ~FanSystemModel() override = default;
  FanSystemModel(const FanSystemModel& other) = default;
  FanSystemModel(FanSystemModel&& other) = default;
  FanSystemModel& operator=(const FanSystemModel&) = default;
  FanSystemModel& operator=(FanSystemModel&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> speedControlMethodValues();
  static std::vector<std::string> designPowerSizingMethodValues();

  // Schema Alignment Notes:
  // - Status: Near Parity. The canonical curve, thermal-zone, and extensible-speed APIs are aligned, while the airflow-network helper surface remains absent.
  // - Canonical Counterpart: openstudio::model::FanSystemModel.
  // - Implemented Parity: The constructor defaults, availability-schedule wiring, scalar sizing surface, electric-power curve relationship, motor-loss-zone relationship, and extensible speed APIs preserve the main `openstudio::model::FanSystemModel` behavior.
  // - Documented Delta: Epmodel still omits the airflow-network helper surface from `openstudio::model::FanSystemModel`.
  // - Field/Storage Mapping: The availability schedule, electric-power curve, and motor-loss zone are typed object relationships, while multi-speed data maps directly to `Fan:SystemModel` extensible groups in EnergyPlus.
  // - Evidence: `src/model/FanSystemModel.hpp`, `src/model/FanSystemModel.cpp`, `src/model/test/FanSystemModel_GTest.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateFanSystemModel.cpp` anchor the canonical API and translation behavior.
  // - Remaining Parity Work: Add airflow-network relationship support once epmodel grows the corresponding fan helper surface.
  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  boost::optional<double> designMaximumAirFlowRate() const;
  bool isDesignMaximumAirFlowRateAutosized() const;
  bool setDesignMaximumAirFlowRate(double designMaximumAirFlowRate);
  void autosizeDesignMaximumAirFlowRate();

  std::string speedControlMethod() const;
  bool setSpeedControlMethod(const std::string& speedControlMethod);

  double electricPowerMinimumFlowRateFraction() const;
  bool setElectricPowerMinimumFlowRateFraction(double electricPowerMinimumFlowRateFraction);

  double designPressureRise() const;
  bool setDesignPressureRise(double designPressureRise);

  double motorEfficiency() const;
  bool setMotorEfficiency(double motorEfficiency);

  double motorInAirStreamFraction() const;
  bool setMotorInAirStreamFraction(double motorInAirStreamFraction);

  boost::optional<double> designElectricPowerConsumption() const;
  bool isDesignElectricPowerConsumptionAutosized() const;
  bool setDesignElectricPowerConsumption(double designElectricPowerConsumption);
  void autosizeDesignElectricPowerConsumption();

  std::string designPowerSizingMethod() const;
  bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

  double electricPowerPerUnitFlowRate() const;
  bool setElectricPowerPerUnitFlowRate(double electricPowerPerUnitFlowRate);

  double electricPowerPerUnitFlowRatePerUnitPressure() const;
  bool setElectricPowerPerUnitFlowRatePerUnitPressure(double electricPowerPerUnitFlowRatePerUnitPressure);

  double fanTotalEfficiency() const;
  bool setFanTotalEfficiency(double fanTotalEfficiency);

  boost::optional<Curve> electricPowerFunctionofFlowFractionCurve() const;
  bool setElectricPowerFunctionofFlowFractionCurve(const Curve& curve);
  void resetElectricPowerFunctionofFlowFractionCurve();

  boost::optional<double> nightVentilationModePressureRise() const;
  bool setNightVentilationModePressureRise(double nightVentilationModePressureRise);
  void resetNightVentilationModePressureRise();

  boost::optional<double> nightVentilationModeFlowFraction() const;
  bool setNightVentilationModeFlowFraction(double nightVentilationModeFlowFraction);
  void resetNightVentilationModeFlowFraction();

  boost::optional<ThermalZone> motorLossZone() const;
  bool setMotorLossZone(const ThermalZone& thermalZone);
  void resetMotorLossZone();

  double motorLossRadiativeFraction() const;
  bool setMotorLossRadiativeFraction(double motorLossRadiativeFraction);

  std::string endUseSubcategory() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);

  unsigned numberofSpeeds() const;
  std::vector<FanSystemModelSpeed> speeds() const;
  boost::optional<unsigned> speedIndex(const FanSystemModelSpeed& speed) const;
  boost::optional<FanSystemModelSpeed> getSpeed(unsigned speedIndex) const;

  bool addSpeed(const FanSystemModelSpeed& speed);
  bool addSpeed(double flowFraction);
  bool addSpeed(double flowFraction, double electricPowerFraction);
  bool removeSpeed(unsigned speedIndex);
  void removeAllSpeeds();
  bool setSpeeds(const std::vector<FanSystemModelSpeed>& speeds);

  bool addToNode(Node& node);

 protected:
  using ImplType = detail::FanSystemModel_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FanSystemModel(std::shared_ptr<detail::FanSystemModel_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
