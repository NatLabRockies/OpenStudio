/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelThermostatOffset.hpp"
#include "FaultModelThermostatOffset_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_ThermostatOffset_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

FaultModelThermostatOffset::FaultModelThermostatOffset(const Model& model)
  : ModelObject(FaultModelThermostatOffset::iddObjectType(), model) {}

FaultModelThermostatOffset::FaultModelThermostatOffset(std::shared_ptr<detail::FaultModelThermostatOffset_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType FaultModelThermostatOffset::iddObjectType() {
  return IddObjectType::FaultModel_ThermostatOffset;
}

double FaultModelThermostatOffset::referenceThermostatOffset() const {
  return getImpl<detail::FaultModelThermostatOffset_Impl>()->referenceThermostatOffset();
}

bool FaultModelThermostatOffset::isReferenceThermostatOffsetDefaulted() const {
  return getImpl<detail::FaultModelThermostatOffset_Impl>()->isReferenceThermostatOffsetDefaulted();
}

bool FaultModelThermostatOffset::setReferenceThermostatOffset(double referenceThermostatOffset) {
  return getImpl<detail::FaultModelThermostatOffset_Impl>()->setReferenceThermostatOffset(referenceThermostatOffset);
}

void FaultModelThermostatOffset::resetReferenceThermostatOffset() {
  getImpl<detail::FaultModelThermostatOffset_Impl>()->resetReferenceThermostatOffset();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double FaultModelThermostatOffset_Impl::referenceThermostatOffset() const {
  const auto value = getDouble(openstudio::FaultModel_ThermostatOffsetFields::ReferenceThermostatOffset, true);
  OS_ASSERT(value);
  return *value;
}

bool FaultModelThermostatOffset_Impl::isReferenceThermostatOffsetDefaulted() const {
  return isEmpty(openstudio::FaultModel_ThermostatOffsetFields::ReferenceThermostatOffset);
}

bool FaultModelThermostatOffset_Impl::setReferenceThermostatOffset(double referenceThermostatOffset) {
  return setDouble(openstudio::FaultModel_ThermostatOffsetFields::ReferenceThermostatOffset, referenceThermostatOffset);
}

void FaultModelThermostatOffset_Impl::resetReferenceThermostatOffset() {
  OS_ASSERT(setString(openstudio::FaultModel_ThermostatOffsetFields::ReferenceThermostatOffset, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
