/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelTemperatureSensorOffsetCondenserSupplyWater.hpp"
#include "FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_TemperatureSensorOffset_CondenserSupplyWater_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

FaultModelTemperatureSensorOffsetCondenserSupplyWater::FaultModelTemperatureSensorOffsetCondenserSupplyWater(const Model& model)
  : ModelObject(FaultModelTemperatureSensorOffsetCondenserSupplyWater::iddObjectType(), model) {}

FaultModelTemperatureSensorOffsetCondenserSupplyWater::FaultModelTemperatureSensorOffsetCondenserSupplyWater(
  std::shared_ptr<detail::FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType FaultModelTemperatureSensorOffsetCondenserSupplyWater::iddObjectType() {
  return IddObjectType::FaultModel_TemperatureSensorOffset_CondenserSupplyWater;
}

double FaultModelTemperatureSensorOffsetCondenserSupplyWater::referenceSensorOffset() const {
  return getImpl<detail::FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl>()->referenceSensorOffset();
}

bool FaultModelTemperatureSensorOffsetCondenserSupplyWater::isReferenceSensorOffsetDefaulted() const {
  return getImpl<detail::FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl>()->isReferenceSensorOffsetDefaulted();
}

bool FaultModelTemperatureSensorOffsetCondenserSupplyWater::setReferenceSensorOffset(double referenceSensorOffset) {
  return getImpl<detail::FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl>()->setReferenceSensorOffset(referenceSensorOffset);
}

void FaultModelTemperatureSensorOffsetCondenserSupplyWater::resetReferenceSensorOffset() {
  getImpl<detail::FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl>()->resetReferenceSensorOffset();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl::referenceSensorOffset() const {
  const auto value = getDouble(openstudio::FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields::ReferenceSensorOffset, true);
  OS_ASSERT(value);
  return *value;
}

bool FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl::isReferenceSensorOffsetDefaulted() const {
  return isEmpty(openstudio::FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields::ReferenceSensorOffset);
}

bool FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl::setReferenceSensorOffset(double referenceSensorOffset) {
  return setDouble(openstudio::FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields::ReferenceSensorOffset, referenceSensorOffset);
}

void FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl::resetReferenceSensorOffset() {
  OS_ASSERT(setString(openstudio::FaultModel_TemperatureSensorOffset_CondenserSupplyWaterFields::ReferenceSensorOffset, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
