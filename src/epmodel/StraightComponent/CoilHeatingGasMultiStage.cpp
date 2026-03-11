/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingGasMultiStage.hpp"
#include "StraightComponent/CoilHeatingGasMultiStage_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Heating_Gas_MultiStage_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilHeatingGasMultiStage::CoilHeatingGasMultiStage(const Model& model)
  : StraightComponent(CoilHeatingGasMultiStage::iddObjectType(), model) {
  // Keep required scalar field populated for strict non-optional getter behavior.
  OS_ASSERT(getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setNumberOfStages(1u));
}

CoilHeatingGasMultiStage::CoilHeatingGasMultiStage(std::shared_ptr<detail::CoilHeatingGasMultiStage_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilHeatingGasMultiStage::iddObjectType() {
  return IddObjectType::Coil_Heating_Gas_MultiStage;
}

boost::optional<double> CoilHeatingGasMultiStage::parasiticGasLoad() const {
  return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->offCycleParasiticGasLoad();
}

boost::optional<double> CoilHeatingGasMultiStage::offCycleParasiticGasLoad() const {
  return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->offCycleParasiticGasLoad();
}

bool CoilHeatingGasMultiStage::setParasiticGasLoad(double parasiticGasLoad) {
  return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setOffCycleParasiticGasLoad(parasiticGasLoad);
}

bool CoilHeatingGasMultiStage::setOffCycleParasiticGasLoad(double offCycleParasiticGasLoad) {
  return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setOffCycleParasiticGasLoad(offCycleParasiticGasLoad);
}

void CoilHeatingGasMultiStage::resetParasiticGasLoad() {
  getImpl<detail::CoilHeatingGasMultiStage_Impl>()->resetOffCycleParasiticGasLoad();
}

void CoilHeatingGasMultiStage::resetOffCycleParasiticGasLoad() {
  getImpl<detail::CoilHeatingGasMultiStage_Impl>()->resetOffCycleParasiticGasLoad();
}

unsigned CoilHeatingGasMultiStage::numberOfStages() const {
  return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->numberOfStages();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilHeatingGasMultiStage_Impl::inletPort() const {
  return openstudio::Coil_Heating_Gas_MultiStageFields::AirInletNodeName;
}

unsigned CoilHeatingGasMultiStage_Impl::outletPort() const {
  return openstudio::Coil_Heating_Gas_MultiStageFields::AirOutletNodeName;
}

boost::optional<double> CoilHeatingGasMultiStage_Impl::offCycleParasiticGasLoad() const {
  return getDouble(openstudio::Coil_Heating_Gas_MultiStageFields::OffCycleParasiticGasLoad, true);
}

bool CoilHeatingGasMultiStage_Impl::setOffCycleParasiticGasLoad(double offCycleParasiticGasLoad) {
  return setDouble(openstudio::Coil_Heating_Gas_MultiStageFields::OffCycleParasiticGasLoad, offCycleParasiticGasLoad);
}

void CoilHeatingGasMultiStage_Impl::resetOffCycleParasiticGasLoad() {
  const bool result = setString(openstudio::Coil_Heating_Gas_MultiStageFields::OffCycleParasiticGasLoad, "");
  OS_ASSERT(result);
}

unsigned CoilHeatingGasMultiStage_Impl::numberOfStages() const {
  const auto value = getUnsigned(openstudio::Coil_Heating_Gas_MultiStageFields::NumberofStages, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingGasMultiStage_Impl::setNumberOfStages(unsigned numberOfStages) {
  return setUnsigned(openstudio::Coil_Heating_Gas_MultiStageFields::NumberofStages, numberOfStages);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
