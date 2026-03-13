/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLTABLESTYLE_IMPL_HPP
#define EPMODEL_OUTPUTCONTROLTABLESTYLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputControlTableStyle_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputControlTableStyle_Impl() override = default;

      std::string columnSeparator() const;
      bool setColumnSeparator(const std::string& columnSeparator);
      std::vector<std::string> columnSeparatorValues() const;

      std::string unitConversion() const;
      bool setUnitConversion(const std::string& unitConversion);
      std::vector<std::string> unitConversionValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
