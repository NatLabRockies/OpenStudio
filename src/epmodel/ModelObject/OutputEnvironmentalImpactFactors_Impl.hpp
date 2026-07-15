/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTENVIRONMENTALIMPACTFACTORS_IMPL_HPP
#define EPMODEL_OUTPUTENVIRONMENTALIMPACTFACTORS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputEnvironmentalImpactFactors_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputEnvironmentalImpactFactors_Impl() override = default;

      std::string reportingFrequency() const;

      bool setReportingFrequency(const std::string& reportingFrequency);

      std::vector<std::string> reportingFrequencyValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
