/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FaultModelEnthalpySensorOffsetReturnAir.hpp"
#include "FaultModelEnthalpySensorOffsetReturnAir_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FaultModel_EnthalpySensorOffset_ReturnAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

FaultModelEnthalpySensorOffsetReturnAir::FaultModelEnthalpySensorOffsetReturnAir(const Model& model)
  : ModelObject(FaultModelEnthalpySensorOffsetReturnAir::iddObjectType(), model) {}

FaultModelEnthalpySensorOffsetReturnAir::FaultModelEnthalpySensorOffsetReturnAir(
  std::shared_ptr<detail::FaultModelEnthalpySensorOffsetReturnAir_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType FaultModelEnthalpySensorOffsetReturnAir::iddObjectType() {
  return IddObjectType::FaultModel_EnthalpySensorOffset_ReturnAir;
}

double FaultModelEnthalpySensorOffsetReturnAir::enthalpySensorOffset() const {
  return getImpl<detail::FaultModelEnthalpySensorOffsetReturnAir_Impl>()->enthalpySensorOffset();
}

bool FaultModelEnthalpySensorOffsetReturnAir::isEnthalpySensorOffsetDefaulted() const {
  return getImpl<detail::FaultModelEnthalpySensorOffsetReturnAir_Impl>()->isEnthalpySensorOffsetDefaulted();
}

bool FaultModelEnthalpySensorOffsetReturnAir::setEnthalpySensorOffset(double enthalpySensorOffset) {
  return getImpl<detail::FaultModelEnthalpySensorOffsetReturnAir_Impl>()->setEnthalpySensorOffset(enthalpySensorOffset);
}

void FaultModelEnthalpySensorOffsetReturnAir::resetEnthalpySensorOffset() {
  getImpl<detail::FaultModelEnthalpySensorOffsetReturnAir_Impl>()->resetEnthalpySensorOffset();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double FaultModelEnthalpySensorOffsetReturnAir_Impl::enthalpySensorOffset() const {
  const auto value = getDouble(openstudio::FaultModel_EnthalpySensorOffset_ReturnAirFields::EnthalpySensorOffset, true);
  OS_ASSERT(value);
  return *value;
}

bool FaultModelEnthalpySensorOffsetReturnAir_Impl::isEnthalpySensorOffsetDefaulted() const {
  return isEmpty(openstudio::FaultModel_EnthalpySensorOffset_ReturnAirFields::EnthalpySensorOffset);
}

bool FaultModelEnthalpySensorOffsetReturnAir_Impl::setEnthalpySensorOffset(double enthalpySensorOffset) {
  return setDouble(openstudio::FaultModel_EnthalpySensorOffset_ReturnAirFields::EnthalpySensorOffset, enthalpySensorOffset);
}

void FaultModelEnthalpySensorOffsetReturnAir_Impl::resetEnthalpySensorOffset() {
  OS_ASSERT(setString(openstudio::FaultModel_EnthalpySensorOffset_ReturnAirFields::EnthalpySensorOffset, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
