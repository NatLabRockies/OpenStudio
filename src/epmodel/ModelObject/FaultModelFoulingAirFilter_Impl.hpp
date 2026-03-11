/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELFOULINGAIRFILTER_IMPL_HPP
#define EPMODEL_FAULTMODELFOULINGAIRFILTER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API FaultModelFoulingAirFilter_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~FaultModelFoulingAirFilter_Impl() override = default;

  std::string fanObjectType() const;
  bool setFanObjectType(const std::string& fanObjectType);

  std::vector<std::string> fanObjectTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
