/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERSTORAGECONVERTER_IMPL_HPP
#define EPMODEL_ELECTRICLOADCENTERSTORAGECONVERTER_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ElectricLoadCenterStorageConverter_Impl : public ParentObject_Impl
{
 public:
  using ParentObject_Impl::ParentObject_Impl;
  virtual ~ElectricLoadCenterStorageConverter_Impl() override = default;

  std::string powerConversionEfficiencyMethod() const;

  boost::optional<double> simpleFixedEfficiency() const;
  bool setSimpleFixedEfficiency(double simpleFixedEfficiency);

  boost::optional<double> designMaximumContinuousInputPower() const;
  bool setDesignMaximumContinuousInputPower(double designMaximumContinuousInputPower);

  double ancillaryPowerConsumedInStandby() const;
  bool isAncillaryPowerConsumedInStandbyDefaulted() const;
  bool setAncillaryPowerConsumedInStandby(double ancillaryPowerConsumedInStandby);
  void resetAncillaryPowerConsumedInStandby();

  double radiativeFraction() const;
  bool isRadiativeFractionDefaulted() const;
  bool setRadiativeFraction(double radiativeFraction);
  void resetRadiativeFraction();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
