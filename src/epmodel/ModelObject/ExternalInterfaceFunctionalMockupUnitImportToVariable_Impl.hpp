/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOVARIABLE_IMPL_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITIMPORTTOVARIABLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ExternalInterfaceFunctionalMockupUnitImportToVariable_Impl() override = default;

  std::string fMUInstanceName() const;
  bool setFMUInstanceName(const std::string& fMUInstanceName);

  std::string fMUVariableName() const;
  bool setFMUVariableName(const std::string& fMUVariableName);

  double initialValue() const;
  bool setInitialValue(double initialValue);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
