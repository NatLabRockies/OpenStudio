/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTCONTROLSIZINGSTYLE_IMPL_HPP
#define EPMODEL_OUTPUTCONTROLSIZINGSTYLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputControlSizingStyle_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputControlSizingStyle_Impl() override = default;

      std::vector<std::string> columnSeparatorValues() const;

      std::string columnSeparator() const;
      bool setColumnSeparator(const std::string& columnSeparator);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
