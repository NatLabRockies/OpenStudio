/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTCONSTANTPRESSUREDROP_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTCONSTANTPRESSUREDROP_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirflowNetworkDistributionComponentConstantPressureDrop_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirflowNetworkDistributionComponentConstantPressureDrop_Impl() override = default;

      double pressureDifferenceAcrosstheComponent() const;
      bool setPressureDifferenceAcrosstheComponent(double pressureDifferenceAcrosstheComponent);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
