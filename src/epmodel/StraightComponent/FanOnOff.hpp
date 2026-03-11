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

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::FanOnOff scalar accessor names/signatures.
  // - Field Mapping: fanTotalEfficiency/fanEfficiency, pressureRise, maximumFlowRate, motor* and endUseSubcategory map directly to E+ Fan:OnOff fields.
  // - Field Mapping: maximumFlowRate preserves autosize/reset token semantics via the "autosize" value.
  // - ForwardTranslator evidence: ForwardTranslateFanOnOff.cpp writes these scalar fields directly to Fan:OnOff.
  // - TODO(parity): Relationship fields (availability schedule, curves, node links) remain excluded in this scalar scaffold.
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
