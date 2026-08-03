/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FENESTRATIONMATERIAL_IMPL_HPP
#define EPMODEL_FENESTRATIONMATERIAL_IMPL_HPP

#include "Material/Material_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API FenestrationMaterial_Impl : public Material_Impl
    {
     public:
      using Material_Impl::Material_Impl;
      virtual ~FenestrationMaterial_Impl() override = default;

     private:
      REGISTER_LOGGER("openstudio.epmodel.FenestrationMaterial");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
