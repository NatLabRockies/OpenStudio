/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDPROPERTIESCONCENTRATION_IMPL_HPP
#define EPMODEL_FLUIDPROPERTIESCONCENTRATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API FluidPropertiesConcentration_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FluidPropertiesConcentration_Impl() override = default;

      boost::optional<std::string> fluidPropertyType() const;
      bool setFluidPropertyType(const std::string& fluidPropertyType);
      void resetFluidPropertyType();

      boost::optional<double> concentration() const;
      bool setConcentration(double concentration);
      void resetConcentration();

      std::vector<std::string> fluidPropertyTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
