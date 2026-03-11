/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERSUCTION_IMPL_HPP
#define EPMODEL_MATERIALPROPERTYHEATANDMOISTURETRANSFERSUCTION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API MaterialPropertyHeatAndMoistureTransferSuction_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~MaterialPropertyHeatAndMoistureTransferSuction_Impl() override = default;

  int numberofSuctionpoints() const;
  bool setNumberofSuctionpoints(int numberofSuctionpoints);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
