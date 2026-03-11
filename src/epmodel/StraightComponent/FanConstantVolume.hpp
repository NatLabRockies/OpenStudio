/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANCONSTANTVOLUME_HPP
#define EPMODEL_FANCONSTANTVOLUME_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
  class FanConstantVolume_Impl;
}

class EPMODEL_API FanConstantVolume : public StraightComponent
{
 public:
  explicit FanConstantVolume(const Model& model);

  virtual ~FanConstantVolume() override = default;
  FanConstantVolume(const FanConstantVolume& other) = default;
  FanConstantVolume(FanConstantVolume&& other) = default;
  FanConstantVolume& operator=(const FanConstantVolume&) = default;
  FanConstantVolume& operator=(FanConstantVolume&&) = default;

  static IddObjectType iddObjectType();

  bool addToNode(Node& node);

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: fan* efficiency, pressure rise, motor fields, and end-use subcategory map directly to E+ Fan:ConstantVolume fields.
  // - Field Mapping: maximumFlowRate API preserves autosize/reset semantics by storing numeric values or the "autosize" token.
  // - TODO(parity): Keep relationship fields (availability schedule and node targets) out of scalar scaffold coverage.
  double fanTotalEfficiency() const;
  double fanEfficiency() const;
  bool setFanTotalEfficiency(double fanTotalEfficiency);
  bool setFanEfficiency(double fanEfficiency);

  double pressureRise() const;
  bool setPressureRise(double pressureRise);

  boost::optional<double> maximumFlowRate() const;
  bool isMaximumFlowRateAutosized() const;
  bool setMaximumFlowRate(double maximumFlowRate);
  void resetMaximumFlowRate();
  void autosizeMaximumFlowRate();

  double motorEfficiency() const;
  bool setMotorEfficiency(double motorEfficiency);

  double motorInAirstreamFraction() const;
  bool setMotorInAirstreamFraction(double motorInAirstreamFraction);

  std::string endUseSubcategory() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);

 protected:
  using ImplType = detail::FanConstantVolume_Impl;

  friend class openstudio::epmodel::Model;

  explicit FanConstantVolume(std::shared_ptr<detail::FanConstantVolume_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
