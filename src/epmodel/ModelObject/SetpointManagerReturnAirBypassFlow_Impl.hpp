/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERRETURNAIRBYPASSFLOW_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERRETURNAIRBYPASSFLOW_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API SetpointManagerReturnAirBypassFlow_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~SetpointManagerReturnAirBypassFlow_Impl() override = default;

  std::string controlVariable() const;
  bool isControlVariableDefaulted() const;
  bool setControlVariable(const std::string& controlVariable);
  void resetControlVariable();

  std::vector<std::string> controlVariableValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
