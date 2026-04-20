/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DUCTLOSSCONDUCTION_IMPL_HPP
#define EPMODEL_DUCTLOSSCONDUCTION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API DuctLossConduction_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~DuctLossConduction_Impl() override = default;

      std::vector<std::string> environmentTypeValues() const;

      std::string environmentType() const;
      bool setEnvironmentType(const std::string& environmentType);
      bool isEnvironmentTypeDefaulted() const;
      void resetEnvironmentType();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
