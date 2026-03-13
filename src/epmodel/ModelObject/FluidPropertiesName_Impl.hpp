/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDPROPERTIESNAME_IMPL_HPP
#define EPMODEL_FLUIDPROPERTIESNAME_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API FluidPropertiesName_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FluidPropertiesName_Impl() override = default;

      std::vector<std::string> fluidTypeValues() const;

      std::string fluidName() const;
      bool setFluidName(const std::string& fluidName);

      std::string fluidType() const;
      bool setFluidType(const std::string& fluidType);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
