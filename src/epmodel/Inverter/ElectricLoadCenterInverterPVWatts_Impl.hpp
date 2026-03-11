/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERINVERTERPVWATTS_IMPL_HPP
#define EPMODEL_ELECTRICLOADCENTERINVERTERPVWATTS_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ElectricLoadCenterInverterPVWatts_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ElectricLoadCenterInverterPVWatts_Impl() override = default;

  double dcToACSizeRatio() const;
  bool isDCToACSizeRatioDefaulted() const;
  bool setDCToACSizeRatio(double dcToACSizeRatio);
  void resetDCToACSizeRatio();

  double inverterEfficiency() const;
  bool isInverterEfficiencyDefaulted() const;
  bool setInverterEfficiency(double inverterEfficiency);
  void resetInverterEfficiency();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
