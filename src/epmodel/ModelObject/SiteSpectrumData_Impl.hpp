/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITESPECTRUMDATA_IMPL_HPP
#define EPMODEL_SITESPECTRUMDATA_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SiteSpectrumData_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SiteSpectrumData_Impl() override = default;

      std::vector<std::string> spectrumDataTypeValues() const;

      std::string spectrumDataType() const;
      bool setSpectrumDataType(const std::string& spectrumDataType);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
