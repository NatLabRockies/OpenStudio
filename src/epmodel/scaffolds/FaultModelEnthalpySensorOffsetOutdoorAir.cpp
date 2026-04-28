/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelEnthalpySensorOffsetOutdoorAir.hpp"
#include "FaultModelEnthalpySensorOffsetOutdoorAir_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_EnthalpySensorOffset_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

FaultModelEnthalpySensorOffsetOutdoorAir::FaultModelEnthalpySensorOffsetOutdoorAir(const Model& model)
  : ModelObject(FaultModelEnthalpySensorOffsetOutdoorAir::iddObjectType(), model) {}

FaultModelEnthalpySensorOffsetOutdoorAir::FaultModelEnthalpySensorOffsetOutdoorAir(
  std::shared_ptr<detail::FaultModelEnthalpySensorOffsetOutdoorAir_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType FaultModelEnthalpySensorOffsetOutdoorAir::iddObjectType() {
  return IddObjectType::FaultModel_EnthalpySensorOffset_OutdoorAir;
}

double FaultModelEnthalpySensorOffsetOutdoorAir::enthalpySensorOffset() const {
  return getImpl<detail::FaultModelEnthalpySensorOffsetOutdoorAir_Impl>()->enthalpySensorOffset();
}

bool FaultModelEnthalpySensorOffsetOutdoorAir::isEnthalpySensorOffsetDefaulted() const {
  return getImpl<detail::FaultModelEnthalpySensorOffsetOutdoorAir_Impl>()->isEnthalpySensorOffsetDefaulted();
}

bool FaultModelEnthalpySensorOffsetOutdoorAir::setEnthalpySensorOffset(double enthalpySensorOffset) {
  return getImpl<detail::FaultModelEnthalpySensorOffsetOutdoorAir_Impl>()->setEnthalpySensorOffset(enthalpySensorOffset);
}

void FaultModelEnthalpySensorOffsetOutdoorAir::resetEnthalpySensorOffset() {
  getImpl<detail::FaultModelEnthalpySensorOffsetOutdoorAir_Impl>()->resetEnthalpySensorOffset();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double FaultModelEnthalpySensorOffsetOutdoorAir_Impl::enthalpySensorOffset() const {
  const auto value = getDouble(openstudio::FaultModel_EnthalpySensorOffset_OutdoorAirFields::EnthalpySensorOffset, true);
  OS_ASSERT(value);
  return *value;
}

bool FaultModelEnthalpySensorOffsetOutdoorAir_Impl::isEnthalpySensorOffsetDefaulted() const {
  return isEmpty(openstudio::FaultModel_EnthalpySensorOffset_OutdoorAirFields::EnthalpySensorOffset);
}

bool FaultModelEnthalpySensorOffsetOutdoorAir_Impl::setEnthalpySensorOffset(double enthalpySensorOffset) {
  return setDouble(openstudio::FaultModel_EnthalpySensorOffset_OutdoorAirFields::EnthalpySensorOffset, enthalpySensorOffset);
}

void FaultModelEnthalpySensorOffsetOutdoorAir_Impl::resetEnthalpySensorOffset() {
  OS_ASSERT(setString(openstudio::FaultModel_EnthalpySensorOffset_OutdoorAirFields::EnthalpySensorOffset, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
