/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HUMIDIFIERSTEAMELECTRIC_IMPL_HPP
#define EPMODEL_HUMIDIFIERSTEAMELECTRIC_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API HumidifierSteamElectric_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~HumidifierSteamElectric_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  boost::optional<double> ratedCapacity() const;
  bool isRatedCapacityAutosized() const;

  boost::optional<double> ratedPower() const;
  bool isRatedPowerAutosized() const;

  boost::optional<double> ratedFanPower() const;

  boost::optional<double> standbyPower() const;

  bool setRatedCapacity(double ratedCapacity);
  void autosizeRatedCapacity();

  bool setRatedPower(double ratedPower);
  void resetRatedPower();
  void autosizeRatedPower();

  bool setRatedFanPower(double ratedFanPower);
  void resetRatedFanPower();

  bool setStandbyPower(double standbyPower);
  void resetStandbyPower();

  boost::optional<double> autosizedRatedCapacity() const;
  boost::optional<double> autosizedRatedPower() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
