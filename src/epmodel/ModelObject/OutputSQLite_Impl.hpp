/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTSQLITE_IMPL_HPP
#define EPMODEL_OUTPUTSQLITE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputSQLite_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputSQLite_Impl() override = default;

      std::string optionType() const;
      bool setOptionType(const std::string& optionType);
      std::vector<std::string> optionTypeValues() const;

      std::string unitConversionforTabularData() const;
      bool setUnitConversionforTabularData(const std::string& unitConversionforTabularData);
      std::vector<std::string> unitConversionforTabularDataValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
