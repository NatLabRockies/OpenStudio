/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DEMANDMANAGERTHERMOSTATS_IMPL_HPP
#define EPMODEL_DEMANDMANAGERTHERMOSTATS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API DemandManagerThermostats_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~DemandManagerThermostats_Impl() override = default;

  std::string resetControl() const;
  bool setResetControl(const std::string& resetControl);

  boost::optional<int> minimumResetDuration() const;
  bool setMinimumResetDuration(int minimumResetDuration);
  void resetMinimumResetDuration();

  double maximumHeatingSetpointReset() const;
  bool setMaximumHeatingSetpointReset(double maximumHeatingSetpointReset);

  double maximumCoolingSetpointReset() const;
  bool setMaximumCoolingSetpointReset(double maximumCoolingSetpointReset);

  boost::optional<double> resetStepChange() const;
  bool setResetStepChange(double resetStepChange);
  void resetResetStepChange();

  std::string selectionControl() const;
  bool setSelectionControl(const std::string& selectionControl);

  boost::optional<int> rotationDuration() const;
  bool setRotationDuration(int rotationDuration);
  void resetRotationDuration();

  std::vector<std::string> resetControlValues() const;
  std::vector<std::string> selectionControlValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
