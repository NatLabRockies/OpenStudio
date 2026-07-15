/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDPROPERTIESSUPERHEATED_IMPL_HPP
#define EPMODEL_FLUIDPROPERTIESSUPERHEATED_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API FluidPropertiesSuperheated_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FluidPropertiesSuperheated_Impl() override = default;

      boost::optional<std::string> fluidPropertyType() const;
      bool setFluidPropertyType(const std::string& fluidPropertyType);
      void resetFluidPropertyType();

      boost::optional<double> pressure() const;
      bool setPressure(double pressure);
      void resetPressure();

      std::vector<std::string> fluidPropertyTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
