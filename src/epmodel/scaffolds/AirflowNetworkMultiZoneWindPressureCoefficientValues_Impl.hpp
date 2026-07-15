/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONEWINDPRESSURECOEFFICIENTVALUES_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONEWINDPRESSURECOEFFICIENTVALUES_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl() override = default;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
