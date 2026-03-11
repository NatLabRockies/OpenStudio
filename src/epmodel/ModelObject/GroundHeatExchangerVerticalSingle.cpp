/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatExchangerVerticalSingle.hpp"
#include "GroundHeatExchangerVerticalSingle_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatExchanger_Vertical_Single_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

GroundHeatExchangerVerticalSingle::GroundHeatExchangerVerticalSingle(const Model& model)
  : ModelObject(GroundHeatExchangerVerticalSingle::iddObjectType(), model) {
  bool ok = true;
  ok = setXLocation(0.0);
  OS_ASSERT(ok);
  ok = setYLocation(0.0);
  OS_ASSERT(ok);
}

GroundHeatExchangerVerticalSingle::GroundHeatExchangerVerticalSingle(std::shared_ptr<detail::GroundHeatExchangerVerticalSingle_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType GroundHeatExchangerVerticalSingle::iddObjectType() {
  return IddObjectType::GroundHeatExchanger_Vertical_Single;
}

double GroundHeatExchangerVerticalSingle::xLocation() const {
  return getImpl<detail::GroundHeatExchangerVerticalSingle_Impl>()->xLocation();
}

double GroundHeatExchangerVerticalSingle::yLocation() const {
  return getImpl<detail::GroundHeatExchangerVerticalSingle_Impl>()->yLocation();
}

bool GroundHeatExchangerVerticalSingle::setXLocation(double xLocation) {
  return getImpl<detail::GroundHeatExchangerVerticalSingle_Impl>()->setXLocation(xLocation);
}

bool GroundHeatExchangerVerticalSingle::setYLocation(double yLocation) {
  return getImpl<detail::GroundHeatExchangerVerticalSingle_Impl>()->setYLocation(yLocation);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double GroundHeatExchangerVerticalSingle_Impl::xLocation() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_Vertical_SingleFields::XLocation, true);
  OS_ASSERT(value);
  return *value;
}

double GroundHeatExchangerVerticalSingle_Impl::yLocation() const {
  const auto value = getDouble(openstudio::GroundHeatExchanger_Vertical_SingleFields::YLocation, true);
  OS_ASSERT(value);
  return *value;
}

bool GroundHeatExchangerVerticalSingle_Impl::setXLocation(double xLocation) {
  const bool result = setDouble(openstudio::GroundHeatExchanger_Vertical_SingleFields::XLocation, xLocation);
  OS_ASSERT(result);
  return result;
}

bool GroundHeatExchangerVerticalSingle_Impl::setYLocation(double yLocation) {
  const bool result = setDouble(openstudio::GroundHeatExchanger_Vertical_SingleFields::YLocation, yLocation);
  OS_ASSERT(result);
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
