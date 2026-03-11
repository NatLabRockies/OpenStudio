/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_UTILITYCOSTCHARGESIMPLE_IMPL_HPP
#define EPMODEL_UTILITYCOSTCHARGESIMPLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API UtilityCostChargeSimple_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~UtilityCostChargeSimple_Impl() override = default;

      std::string sourceVariable() const;
      bool setSourceVariable(const std::string& sourceVariable);

      boost::optional<std::string> season() const;
      bool setSeason(const std::string& season);
      void resetSeason();

      std::string categoryVariableName() const;
      bool setCategoryVariableName(const std::string& categoryVariableName);

      std::string costPerUnitValueorVariableName() const;
      bool setCostPerUnitValueorVariableName(const std::string& costPerUnitValueorVariableName);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
