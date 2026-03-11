/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOACTUATOR_IMPL_HPP
#define EPMODEL_EXTERNALINTERFACEFUNCTIONALMOCKUPUNITEXPORTTOACTUATOR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ExternalInterfaceFunctionalMockupUnitExportToActuator_Impl() override = default;

  std::string actuatedComponentType() const;
  bool setActuatedComponentType(const std::string& actuatedComponentType);

  std::string actuatedComponentControlType() const;
  bool setActuatedComponentControlType(const std::string& actuatedComponentControlType);

  std::string fMUVariableName() const;
  bool setFMUVariableName(const std::string& fMUVariableName);

  boost::optional<double> initialValue() const;
  bool setInitialValue(double initialValue);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
