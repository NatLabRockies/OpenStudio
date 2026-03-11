/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelFoulingAirFilter.hpp"
#include "FaultModelFoulingAirFilter_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_Fouling_AirFilter_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

FaultModelFoulingAirFilter::FaultModelFoulingAirFilter(const Model& model) : ModelObject(FaultModelFoulingAirFilter::iddObjectType(), model) {}

FaultModelFoulingAirFilter::FaultModelFoulingAirFilter(std::shared_ptr<detail::FaultModelFoulingAirFilter_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType FaultModelFoulingAirFilter::iddObjectType() {
  return IddObjectType::FaultModel_Fouling_AirFilter;
}

std::vector<std::string> FaultModelFoulingAirFilter::fanObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::FaultModel_Fouling_AirFilterFields::FanObjectType);
}

std::string FaultModelFoulingAirFilter::fanObjectType() const {
  return getImpl<detail::FaultModelFoulingAirFilter_Impl>()->fanObjectType();
}

bool FaultModelFoulingAirFilter::setFanObjectType(const std::string& fanObjectType) {
  return getImpl<detail::FaultModelFoulingAirFilter_Impl>()->setFanObjectType(fanObjectType);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string FaultModelFoulingAirFilter_Impl::fanObjectType() const {
  const auto value = getString(openstudio::FaultModel_Fouling_AirFilterFields::FanObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool FaultModelFoulingAirFilter_Impl::setFanObjectType(const std::string& fanObjectType) {
  return setString(openstudio::FaultModel_Fouling_AirFilterFields::FanObjectType, fanObjectType);
}

std::vector<std::string> FaultModelFoulingAirFilter_Impl::fanObjectTypeValues() const {
  return openstudio::epmodel::FaultModelFoulingAirFilter::fanObjectTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
