/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTSCHEDULES_IMPL_HPP
#define EPMODEL_OUTPUTSCHEDULES_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputSchedules_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputSchedules_Impl() override = default;

      std::string keyField() const;

      bool setKeyField(const std::string& keyField);

      std::vector<std::string> keyFieldValues() const;
      std::vector<std::string> validKeyFieldValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
