/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKINTRAZONENODE_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKINTRAZONENODE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkIntraZoneNode_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkIntraZoneNode_Impl() override = default;

  double nodeHeight() const;
  bool isNodeHeightDefaulted() const;
  bool setNodeHeight(double nodeHeight);
  void resetNodeHeight();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
