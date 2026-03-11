/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATBALANCESETTINGSCONDUCTIONFINITEDIFFERENCE_IMPL_HPP
#define EPMODEL_HEATBALANCESETTINGSCONDUCTIONFINITEDIFFERENCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HeatBalanceSettingsConductionFiniteDifference_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HeatBalanceSettingsConductionFiniteDifference_Impl() override = default;

  std::string differenceScheme() const;
  bool isDifferenceSchemeDefaulted() const;
  double spaceDiscretizationConstant() const;
  bool isSpaceDiscretizationConstantDefaulted() const;
  double relaxationFactor() const;
  bool isRelaxationFactorDefaulted() const;
  double insideFaceSurfaceTemperatureConvergenceCriteria() const;
  bool isInsideFaceSurfaceTemperatureConvergenceCriteriaDefaulted() const;

  bool setDifferenceScheme(const std::string& differenceScheme);
  void resetDifferenceScheme();
  bool setSpaceDiscretizationConstant(double spaceDiscretizationConstant);
  void resetSpaceDiscretizationConstant();
  bool setRelaxationFactor(double relaxationFactor);
  void resetRelaxationFactor();
  bool setInsideFaceSurfaceTemperatureConvergenceCriteria(double insideFaceSurfaceTemperatureConvergenceCriteria);
  void resetInsideFaceSurfaceTemperatureConvergenceCriteria();

 private:
  std::vector<std::string> differenceSchemeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
