/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FLUIDPROPERTIESGLYCOLCONCENTRATION_IMPL_HPP
#define EPMODEL_FLUIDPROPERTIESGLYCOLCONCENTRATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API FluidPropertiesGlycolConcentration_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FluidPropertiesGlycolConcentration_Impl() override = default;

      std::string glycolType() const;
      bool setGlycolType(const std::string& glycolType);
      std::vector<std::string> glycolTypeValues() const;

      boost::optional<double> glycolConcentration() const;
      bool setGlycolConcentration(double glycolConcentration);
      void resetGlycolConcentration();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
