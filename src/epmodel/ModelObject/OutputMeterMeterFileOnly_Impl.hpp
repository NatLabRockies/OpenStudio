/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTMETERMETERFILEONLY_IMPL_HPP
#define EPMODEL_OUTPUTMETERMETERFILEONLY_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputMeterMeterFileOnly_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputMeterMeterFileOnly_Impl() override = default;

      std::string keyName() const;
      bool setKeyName(const std::string& keyName);

      std::string reportingFrequency() const;
      bool isReportingFrequencyDefaulted() const;
      bool setReportingFrequency(const std::string& reportingFrequency);
      void resetReportingFrequency();

      std::vector<std::string> reportingFrequencyValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
