/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DISTRICTHEATINGSTEAM_IMPL_HPP
#define EPMODEL_DISTRICTHEATINGSTEAM_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API DistrictHeatingSteam_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~DistrictHeatingSteam_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  boost::optional<double> nominalCapacity() const;
  bool isNominalCapacityAutosized() const;

  bool setNominalCapacity(double nominalCapacity);
  void autosizeNominalCapacity();

  boost::optional<double> autosizedNominalCapacity() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
