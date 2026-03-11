/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_REFRIGERATIONSUBCOOLERMECHANICAL_IMPL_HPP
#define EPMODEL_REFRIGERATIONSUBCOOLERMECHANICAL_IMPL_HPP

#include "RefrigerationSubcooler_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RefrigerationSubcoolerMechanical_Impl : public RefrigerationSubcooler_Impl
    {
     public:
      using RefrigerationSubcooler_Impl::RefrigerationSubcooler_Impl;
      virtual ~RefrigerationSubcoolerMechanical_Impl() override = default;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
