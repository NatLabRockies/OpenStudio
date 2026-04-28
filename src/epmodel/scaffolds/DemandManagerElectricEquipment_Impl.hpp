/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DEMANDMANAGERELECTRICEQUIPMENT_IMPL_HPP
#define EPMODEL_DEMANDMANAGERELECTRICEQUIPMENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API DemandManagerElectricEquipment_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~DemandManagerElectricEquipment_Impl() override = default;

  std::string limitControl() const;
  bool setLimitControl(const std::string& limitControl);

  boost::optional<int> minimumLimitDuration() const;
  bool setMinimumLimitDuration(int minimumLimitDuration);
  void resetMinimumLimitDuration();

  boost::optional<double> maximumLimitFraction() const;
  bool setMaximumLimitFraction(double maximumLimitFraction);
  void resetMaximumLimitFraction();

  boost::optional<double> limitStepChange() const;
  bool setLimitStepChange(double limitStepChange);
  void resetLimitStepChange();

  std::string selectionControl() const;
  bool setSelectionControl(const std::string& selectionControl);

  boost::optional<int> rotationDuration() const;
  bool setRotationDuration(int rotationDuration);
  void resetRotationDuration();

  std::vector<std::string> limitControlValues() const;
  std::vector<std::string> selectionControlValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
