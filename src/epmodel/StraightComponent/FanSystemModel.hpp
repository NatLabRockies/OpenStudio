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
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class FanSystemModel_Impl;
}

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
  // - Status: Partial Parity. The core scalar fan-sizing surface is aligned, but the canonical schedule, curve, thermal-zone, and extensible-speed APIs are still absent.
  // - Canonical Counterpart: openstudio::model::FanSystemModel.
  // - Implemented Parity: The scalar flow, sizing, pressure-rise, efficiency, and end-use-subcategory accessors preserve the canonical `openstudio::model` field behavior, including autosize semantics where exposed.
  // - Documented Delta: Epmodel does not yet expose the canonical availability-schedule, curve, thermal-zone, airflow-network, or speed-collection APIs from `openstudio::model::FanSystemModel`.
  // - Field/Storage Mapping: Scalar fields map directly to `Fan:SystemModel` storage in EnergyPlus, while multi-speed data remains a relationship/extensible concern in the canonical model.
  // - Evidence: `src/model/FanSystemModel.hpp`, `src/model/FanSystemModel.cpp`, `src/model/test/FanSystemModel_GTest.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateFanSystemModel.cpp` anchor the canonical API and translation behavior.
  // - Remaining Parity Work: Add the schedule, curve, thermal-zone, and speed-extensible APIs once epmodel relationship and extensible-field support is in place.
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

  boost::optional<double> nightVentilationModePressureRise() const;
  bool setNightVentilationModePressureRise(double nightVentilationModePressureRise);
  void resetNightVentilationModePressureRise();

  boost::optional<double> nightVentilationModeFlowFraction() const;
  bool setNightVentilationModeFlowFraction(double nightVentilationModeFlowFraction);
  void resetNightVentilationModeFlowFraction();

  double motorLossRadiativeFraction() const;
  bool setMotorLossRadiativeFraction(double motorLossRadiativeFraction);

  std::string endUseSubcategory() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);

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
