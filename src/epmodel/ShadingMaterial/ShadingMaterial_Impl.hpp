/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SHADINGMATERIAL_IMPL_HPP
#define EPMODEL_SHADINGMATERIAL_IMPL_HPP

#include "FenestrationMaterial/FenestrationMaterial_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ShadingMaterial_Impl : public FenestrationMaterial_Impl
    {
     public:
      using FenestrationMaterial_Impl::FenestrationMaterial_Impl;
      virtual ~ShadingMaterial_Impl() override = default;

     private:
      REGISTER_LOGGER("openstudio.epmodel.ShadingMaterial");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
