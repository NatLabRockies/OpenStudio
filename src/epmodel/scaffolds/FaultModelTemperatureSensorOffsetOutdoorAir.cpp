/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelTemperatureSensorOffsetOutdoorAir.hpp"
#include "FaultModelTemperatureSensorOffsetOutdoorAir_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_TemperatureSensorOffset_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

FaultModelTemperatureSensorOffsetOutdoorAir::FaultModelTemperatureSensorOffsetOutdoorAir(const Model& model)
  : ModelObject(FaultModelTemperatureSensorOffsetOutdoorAir::iddObjectType(), model) {}

FaultModelTemperatureSensorOffsetOutdoorAir::FaultModelTemperatureSensorOffsetOutdoorAir(
  std::shared_ptr<detail::FaultModelTemperatureSensorOffsetOutdoorAir_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType FaultModelTemperatureSensorOffsetOutdoorAir::iddObjectType() {
  return IddObjectType::FaultModel_TemperatureSensorOffset_OutdoorAir;
}

double FaultModelTemperatureSensorOffsetOutdoorAir::temperatureSensorOffset() const {
  return getImpl<detail::FaultModelTemperatureSensorOffsetOutdoorAir_Impl>()->temperatureSensorOffset();
}

bool FaultModelTemperatureSensorOffsetOutdoorAir::isTemperatureSensorOffsetDefaulted() const {
  return getImpl<detail::FaultModelTemperatureSensorOffsetOutdoorAir_Impl>()->isTemperatureSensorOffsetDefaulted();
}

bool FaultModelTemperatureSensorOffsetOutdoorAir::setTemperatureSensorOffset(double temperatureSensorOffset) {
  return getImpl<detail::FaultModelTemperatureSensorOffsetOutdoorAir_Impl>()->setTemperatureSensorOffset(temperatureSensorOffset);
}

void FaultModelTemperatureSensorOffsetOutdoorAir::resetTemperatureSensorOffset() {
  getImpl<detail::FaultModelTemperatureSensorOffsetOutdoorAir_Impl>()->resetTemperatureSensorOffset();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double FaultModelTemperatureSensorOffsetOutdoorAir_Impl::temperatureSensorOffset() const {
  const auto value = getDouble(openstudio::FaultModel_TemperatureSensorOffset_OutdoorAirFields::TemperatureSensorOffset, true);
  OS_ASSERT(value);
  return *value;
}

bool FaultModelTemperatureSensorOffsetOutdoorAir_Impl::isTemperatureSensorOffsetDefaulted() const {
  return isEmpty(openstudio::FaultModel_TemperatureSensorOffset_OutdoorAirFields::TemperatureSensorOffset);
}

bool FaultModelTemperatureSensorOffsetOutdoorAir_Impl::setTemperatureSensorOffset(double temperatureSensorOffset) {
  return setDouble(openstudio::FaultModel_TemperatureSensorOffset_OutdoorAirFields::TemperatureSensorOffset, temperatureSensorOffset);
}

void FaultModelTemperatureSensorOffsetOutdoorAir_Impl::resetTemperatureSensorOffset() {
  OS_ASSERT(setString(openstudio::FaultModel_TemperatureSensorOffset_OutdoorAirFields::TemperatureSensorOffset, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
