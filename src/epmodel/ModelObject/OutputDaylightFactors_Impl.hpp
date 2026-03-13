/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTDAYLIGHTFACTORS_IMPL_HPP
#define EPMODEL_OUTPUTDAYLIGHTFACTORS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputDaylightFactors_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputDaylightFactors_Impl() override = default;

      std::vector<std::string> reportingDaysValues() const;

      std::string reportingDays() const;
      bool setReportingDays(const std::string& reportingDays);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
