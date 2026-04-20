/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTVARIABLEDICTIONARY_IMPL_HPP
#define EPMODEL_OUTPUTVARIABLEDICTIONARY_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputVariableDictionary_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputVariableDictionary_Impl() override = default;

      std::string keyField() const;
      bool isKeyFieldDefaulted() const;
      bool setKeyField(const std::string& keyField);
      void resetKeyField();

      boost::optional<std::string> sortOption() const;
      bool setSortOption(const std::string& sortOption);
      void resetSortOption();

      std::vector<std::string> keyFieldValues() const;
      std::vector<std::string> sortOptionValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
