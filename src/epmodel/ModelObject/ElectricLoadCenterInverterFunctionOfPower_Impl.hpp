/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERINVERTERFUNCTIONOFPOWER_IMPL_HPP
#define EPMODEL_ELECTRICLOADCENTERINVERTERFUNCTIONOFPOWER_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ElectricLoadCenterInverterFunctionOfPower_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ElectricLoadCenterInverterFunctionOfPower_Impl() override = default;

  boost::optional<double> radiativeFraction() const;
  bool setRadiativeFraction(double radiativeFraction);
  void resetRadiativeFraction();

  boost::optional<double> ratedMaximumContinuousInputPower() const;
  bool setRatedMaximumContinuousInputPower(double ratedMaximumContinuousInputPower);
  void resetRatedMaximumContinuousInputPower();

  boost::optional<double> minimumEfficiency() const;
  bool setMinimumEfficiency(double minimumEfficiency);
  void resetMinimumEfficiency();

  boost::optional<double> maximumEfficiency() const;
  bool setMaximumEfficiency(double maximumEfficiency);
  void resetMaximumEfficiency();

  boost::optional<double> minimumPowerOutput() const;
  bool setMinimumPowerOutput(double minimumPowerOutput);
  void resetMinimumPowerOutput();

  boost::optional<double> maximumPowerOutput() const;
  bool setMaximumPowerOutput(double maximumPowerOutput);
  void resetMaximumPowerOutput();

  boost::optional<double> ancillaryPowerConsumedInStandby() const;
  bool setAncillaryPowerConsumedInStandby(double ancillaryPowerConsumedInStandby);
  void resetAncillaryPowerConsumedInStandby();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
