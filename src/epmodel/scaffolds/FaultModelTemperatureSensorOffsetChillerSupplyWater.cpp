/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelTemperatureSensorOffsetChillerSupplyWater.hpp"
#include "FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_TemperatureSensorOffset_ChillerSupplyWater_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

FaultModelTemperatureSensorOffsetChillerSupplyWater::FaultModelTemperatureSensorOffsetChillerSupplyWater(const Model& model)
  : ModelObject(FaultModelTemperatureSensorOffsetChillerSupplyWater::iddObjectType(), model) {}

FaultModelTemperatureSensorOffsetChillerSupplyWater::FaultModelTemperatureSensorOffsetChillerSupplyWater(
  std::shared_ptr<detail::FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType FaultModelTemperatureSensorOffsetChillerSupplyWater::iddObjectType() {
  return IddObjectType::FaultModel_TemperatureSensorOffset_ChillerSupplyWater;
}

double FaultModelTemperatureSensorOffsetChillerSupplyWater::referenceSensorOffset() const {
  return getImpl<detail::FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl>()->referenceSensorOffset();
}

bool FaultModelTemperatureSensorOffsetChillerSupplyWater::isReferenceSensorOffsetDefaulted() const {
  return getImpl<detail::FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl>()->isReferenceSensorOffsetDefaulted();
}

bool FaultModelTemperatureSensorOffsetChillerSupplyWater::setReferenceSensorOffset(double referenceSensorOffset) {
  return getImpl<detail::FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl>()->setReferenceSensorOffset(referenceSensorOffset);
}

void FaultModelTemperatureSensorOffsetChillerSupplyWater::resetReferenceSensorOffset() {
  getImpl<detail::FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl>()->resetReferenceSensorOffset();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl::referenceSensorOffset() const {
  const auto value = getDouble(openstudio::FaultModel_TemperatureSensorOffset_ChillerSupplyWaterFields::ReferenceSensorOffset, true);
  OS_ASSERT(value);
  return *value;
}

bool FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl::isReferenceSensorOffsetDefaulted() const {
  return isEmpty(openstudio::FaultModel_TemperatureSensorOffset_ChillerSupplyWaterFields::ReferenceSensorOffset);
}

bool FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl::setReferenceSensorOffset(double referenceSensorOffset) {
  return setDouble(openstudio::FaultModel_TemperatureSensorOffset_ChillerSupplyWaterFields::ReferenceSensorOffset, referenceSensorOffset);
}

void FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl::resetReferenceSensorOffset() {
  OS_ASSERT(setString(openstudio::FaultModel_TemperatureSensorOffset_ChillerSupplyWaterFields::ReferenceSensorOffset, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
