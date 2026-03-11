/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_METERCUSTOMDECREMENT_IMPL_HPP
#define EPMODEL_METERCUSTOMDECREMENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API MeterCustomDecrement_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~MeterCustomDecrement_Impl() override = default;

  boost::optional<std::string> fuelType() const;
  bool setFuelType(const std::string& fuelType);
  void resetFuelType();

  std::string sourceMeterName() const;
  bool setSourceMeterName(const std::string& sourceMeterName);

  std::vector<std::string> fuelTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
