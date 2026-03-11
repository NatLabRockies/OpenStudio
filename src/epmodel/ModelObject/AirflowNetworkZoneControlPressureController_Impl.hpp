/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKZONECONTROLPRESSURECONTROLLER_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKZONECONTROLPRESSURECONTROLLER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkZoneControlPressureController_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkZoneControlPressureController_Impl() override = default;

  std::string controlObjectType() const;
  bool setControlObjectType(const std::string& controlObjectType);

  std::vector<std::string> controlObjectTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
