/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_METERCUSTOM_IMPL_HPP
#define EPMODEL_METERCUSTOM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API MeterCustom_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~MeterCustom_Impl() override = default;

      std::vector<std::string> fuelTypeValues() const;

      boost::optional<std::string> fuelType() const;
      bool setFuelType(const std::string& fuelType);
      void resetFuelType();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
