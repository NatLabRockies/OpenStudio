/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERREDISTRIBUTION_IMPL_HPP
#define EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERREDISTRIBUTION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API MaterialPropertyHeatAndMoistureTransferRedistribution_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~MaterialPropertyHeatAndMoistureTransferRedistribution_Impl() override = default;

  /** @name Number of Redistribution points */
  //@{
  int numberofRedistributionpoints() const;
  bool setNumberofRedistributionpoints(int numberofRedistributionpoints);
  //@}
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
