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

namespace detail {
class FanOnOff_Impl;
}

class EPMODEL_API FanOnOff : public StraightComponent
{
 public:
  explicit FanOnOff(const Model& model);

  virtual ~FanOnOff() override = default;
  FanOnOff(const FanOnOff& other) = default;
  FanOnOff(FanOnOff&& other) = default;
  FanOnOff& operator=(const FanOnOff&) = default;
  FanOnOff& operator=(FanOnOff&&) = default;

  static IddObjectType iddObjectType();

  bool addToNode(Node& node);

  // Schema Alignment Notes:
  // - Status: Partial Parity. Scalar fan properties and node insertion are aligned, but the canonical schedule, curve, and airflow-network surface is still absent.
  // - Canonical Counterpart: openstudio::model::FanOnOff.
  // - Implemented Parity: The fan total-efficiency, fan-efficiency, pressure-rise, maximum-flow-rate, motor, and end-use-subcategory accessors preserve the canonical scalar field behavior, including autosize/reset semantics for flow rate.
  // - Documented Delta: Epmodel does not yet expose the canonical availability-schedule constructors/accessors, curve linkage APIs, or airflow-network fan helper surface from `openstudio::model::FanOnOff`.
  // - Field/Storage Mapping: Scalar fields map directly to `Fan:OnOff` storage in EnergyPlus.
  // - Evidence: `src/model/FanOnOff.hpp`, `src/model/FanOnOff.cpp`, `src/model/test/FanOnOff_GTest.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateFanOnOff.cpp` establish the canonical API and translation behavior.
  // - Remaining Parity Work: Add the schedule, curve, and airflow-network relationship APIs once epmodel relationship coverage can support them cleanly.
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

 protected:
  using ImplType = detail::FanOnOff_Impl;

  friend class Model;

  explicit FanOnOff(std::shared_ptr<detail::FanOnOff_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
