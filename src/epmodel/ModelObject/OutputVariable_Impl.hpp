/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OUTPUTVARIABLE_IMPL_HPP
#define EPMODEL_OUTPUTVARIABLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API OutputVariable_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~OutputVariable_Impl() override = default;

      // Scalar-only scaffold: relationship-like fields (ScheduleName) and OS-only fields
      // (ExportToBCVTB) are intentionally excluded from this class.
      std::string keyValue() const;
      bool isKeyValueDefaulted() const;
      bool setKeyValue(const std::string& keyValue);
      void resetKeyValue();

      std::string variableName() const;
      bool setVariableName(const std::string& variableName);

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
