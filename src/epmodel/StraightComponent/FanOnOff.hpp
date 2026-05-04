/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANONOFF_HPP
#define EPMODEL_FANONOFF_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

class Model;
class Node;
class Schedule;
class Curve;

namespace detail {
class FanOnOff_Impl;
}

class EPMODEL_API FanOnOff : public StraightComponent
{
 public:
  explicit FanOnOff(const Model& model);
  explicit FanOnOff(const Model& model, Schedule& availabilitySchedule);
  explicit FanOnOff(const Model& model, Schedule& availabilitySchedule, Curve& fanPowerRatioFunctionofSpeedRatioCurve,
                    Curve& fanEfficiencyRatioFunctionofSpeedRatioCurve);

  virtual ~FanOnOff() override = default;
  FanOnOff(const FanOnOff& other) = default;
  FanOnOff(FanOnOff&& other) = default;
  FanOnOff& operator=(const FanOnOff&) = default;
  FanOnOff& operator=(FanOnOff&&) = default;

  static IddObjectType iddObjectType();

  bool addToNode(Node& node);

  // Schema Alignment Notes:
  // - Status: Near Parity. The canonical curve relationships, constructor defaults, and contained-fan topology rules are aligned, while the airflow-network surface remains absent.
  // - Canonical Counterpart: openstudio::model::FanOnOff.
  // - Implemented Parity: The canonical constructors, curve relationships, contained-fan `addToNode` behavior, and the availability-schedule, fan total-efficiency, fan-efficiency, pressure-rise, maximum-flow-rate, motor, and end-use-subcategory accessors preserve the main `openstudio::model::FanOnOff` behavior, including autosize/reset semantics for flow rate.
  // - Documented Delta: Epmodel still omits the airflow-network fan helper surface from `openstudio::model::FanOnOff`.
  // - Field/Storage Mapping: The availability schedule and both curve references are typed object relationships, while the remaining scalar fields map directly to `Fan:OnOff` storage in EnergyPlus.
  // - Evidence: `src/model/FanOnOff.hpp`, `src/model/FanOnOff.cpp`, `src/model/test/FanOnOff_GTest.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateFanOnOff.cpp` establish the canonical API and translation behavior.
  // - Remaining Parity Work: Add airflow-network relationship support once epmodel grows the corresponding fan helper surface.
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
  bool setMaximumFlowRate(double maximumFlowRate);
  void resetMaximumFlowRate();
  void autosizeMaximumFlowRate();
  bool isMaximumFlowRateAutosized() const;

  double motorEfficiency() const;
  bool isMotorEfficiencyDefaulted() const;
  bool setMotorEfficiency(double motorEfficiency);
  void resetMotorEfficiency();

  boost::optional<double> motorInAirstreamFraction() const;
  bool setMotorInAirstreamFraction(double motorInAirstreamFraction);
  void resetMotorInAirstreamFraction();

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

  Curve fanPowerRatioFunctionofSpeedRatioCurve() const;
  bool setFanPowerRatioFunctionofSpeedRatioCurve(const Curve& curve);

  Curve fanEfficiencyRatioFunctionofSpeedRatioCurve() const;
  bool setFanEfficiencyRatioFunctionofSpeedRatioCurve(const Curve& curve);

 protected:
  using ImplType = detail::FanOnOff_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FanOnOff(std::shared_ptr<detail::FanOnOff_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
