/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANVARIABLEVOLUME_HPP
#define EPMODEL_FANVARIABLEVOLUME_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Node;
class Schedule;

namespace detail {
class FanVariableVolume_Impl;
}

class EPMODEL_API FanVariableVolume : public StraightComponent
{
 public:
  explicit FanVariableVolume(const Model& model);

  virtual ~FanVariableVolume() override = default;
  FanVariableVolume(const FanVariableVolume& other) = default;
  FanVariableVolume(FanVariableVolume&& other) = default;
  FanVariableVolume& operator=(const FanVariableVolume&) = default;
  FanVariableVolume& operator=(FanVariableVolume&&) = default;

  static IddObjectType iddObjectType();

  bool addToNode(Node& node);

  static std::vector<std::string> fanPowerMinimumFlowRateInputMethodValues();

  /** \deprecated */
  static std::vector<std::string> validFanPowerMinimumFlowRateInputMethodValues();

  // Schema Alignment Notes:
  // - Status: Partial Parity. Scalar fan properties, availability-schedule wiring, and the fan-power input-method helpers are aligned, but the canonical airflow-network surface is still absent.
  // - Canonical Counterpart: openstudio::model::FanVariableVolume.
  // - Implemented Parity: The availability-schedule, fan total-efficiency, fan-efficiency, pressure-rise, maximum-flow-rate, fan-power input-method, motor, coefficient, and end-use-subcategory accessors preserve the canonical scalar field behavior, including autosize/reset semantics for flow rate.
  // - Documented Delta: Epmodel still omits the airflow-network fan helper surface from `openstudio::model::FanVariableVolume`.
  // - Field/Storage Mapping: The availability schedule is represented as a typed `Schedule` relationship, while the scalar fields map directly to `Fan:VariableVolume` storage in EnergyPlus.
  // - Evidence: `src/model/FanVariableVolume.hpp`, `src/model/FanVariableVolume.cpp`, `src/model/test/FanVariableVolume_GTest.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateFanVariableVolume.cpp` establish the canonical API and translation behavior.
  // - Remaining Parity Work: Add airflow-network relationship support once the epmodel relationship layer is ready for it.
  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

  double fanTotalEfficiency() const;
  bool isFanTotalEfficiencyDefaulted() const;
  bool setFanTotalEfficiency(double fanTotalEfficiency);
  void resetFanTotalEfficiency();

  double fanEfficiency() const;
  bool isFanEfficiencyDefaulted() const;
  bool setFanEfficiency(double fanTotalEfficiency);
  void resetFanEfficiency();

  double pressureRise() const;
  bool setPressureRise(double pressureRise);

  boost::optional<double> maximumFlowRate() const;
  bool isMaximumFlowRateAutosized() const;
  bool setMaximumFlowRate(double maximumFlowRate);
  void resetMaximumFlowRate();
  void autosizeMaximumFlowRate();

  std::string fanPowerMinimumFlowRateInputMethod() const;
  bool isFanPowerMinimumFlowRateInputMethodDefaulted() const;
  bool setFanPowerMinimumFlowRateInputMethod(const std::string& fanPowerMinimumFlowRateInputMethod);
  void resetFanPowerMinimumFlowRateInputMethod();

  double fanPowerMinimumFlowFraction() const;
  bool isFanPowerMinimumFlowFractionDefaulted() const;
  bool setFanPowerMinimumFlowFraction(double fanPowerMinimumFlowFraction);
  void resetFanPowerMinimumFlowFraction();

  boost::optional<double> fanPowerMinimumAirFlowRate() const;
  bool setFanPowerMinimumAirFlowRate(double fanPowerMinimumAirFlowRate);
  void resetFanPowerMinimumAirFlowRate();

  double motorEfficiency() const;
  bool isMotorEfficiencyDefaulted() const;
  bool setMotorEfficiency(double motorEfficiency);
  void resetMotorEfficiency();

  double motorInAirstreamFraction() const;
  bool isMotorInAirstreamFractionDefaulted() const;
  bool setMotorInAirstreamFraction(double motorInAirstreamFraction);
  void resetMotorInAirstreamFraction();

  boost::optional<double> fanPowerCoefficient1() const;
  bool setFanPowerCoefficient1(double fanPowerCoefficient1);
  void resetFanPowerCoefficient1();

  boost::optional<double> fanPowerCoefficient2() const;
  bool setFanPowerCoefficient2(double fanPowerCoefficient2);
  void resetFanPowerCoefficient2();

  boost::optional<double> fanPowerCoefficient3() const;
  bool setFanPowerCoefficient3(double fanPowerCoefficient3);
  void resetFanPowerCoefficient3();

  boost::optional<double> fanPowerCoefficient4() const;
  bool setFanPowerCoefficient4(double fanPowerCoefficient4);
  void resetFanPowerCoefficient4();

  boost::optional<double> fanPowerCoefficient5() const;
  bool setFanPowerCoefficient5(double fanPowerCoefficient5);
  void resetFanPowerCoefficient5();

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

 protected:
  using ImplType = detail::FanVariableVolume_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FanVariableVolume(std::shared_ptr<detail::FanVariableVolume_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
