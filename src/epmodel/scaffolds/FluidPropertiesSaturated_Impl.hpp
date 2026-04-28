/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDPROPERTIESSATURATED_IMPL_HPP
#define EPMODEL_FLUIDPROPERTIESSATURATED_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API FluidPropertiesSaturated_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FluidPropertiesSaturated_Impl() override = default;

      std::vector<std::string> fluidPropertyTypeValues() const;
      std::vector<std::string> fluidPhaseValues() const;

      boost::optional<std::string> fluidPropertyType() const;
      bool setFluidPropertyType(const std::string& fluidPropertyType);
      void resetFluidPropertyType();

      boost::optional<std::string> fluidPhase() const;
      bool setFluidPhase(const std::string& fluidPhase);
      void resetFluidPhase();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
