/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingElectricMultiStage.hpp"
#include "StraightComponent/CoilHeatingElectricMultiStage_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Heating_Electric_MultiStage_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilHeatingElectricMultiStage::CoilHeatingElectricMultiStage(const Model& model)
  : StraightComponent(CoilHeatingElectricMultiStage::iddObjectType(), model) {
  // Keep required scalar field populated for strict non-optional getter behavior.
  OS_ASSERT(getImpl<detail::CoilHeatingElectricMultiStage_Impl>()->setNumberOfStages(1u));
}

CoilHeatingElectricMultiStage::CoilHeatingElectricMultiStage(std::shared_ptr<detail::CoilHeatingElectricMultiStage_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilHeatingElectricMultiStage::iddObjectType() {
  return IddObjectType::Coil_Heating_Electric_MultiStage;
}

unsigned CoilHeatingElectricMultiStage::numberOfStages() const {
  return getImpl<detail::CoilHeatingElectricMultiStage_Impl>()->numberOfStages();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilHeatingElectricMultiStage_Impl::inletPort() const {
  return openstudio::Coil_Heating_Electric_MultiStageFields::AirInletNodeName;
}

unsigned CoilHeatingElectricMultiStage_Impl::outletPort() const {
  return openstudio::Coil_Heating_Electric_MultiStageFields::AirOutletNodeName;
}

unsigned CoilHeatingElectricMultiStage_Impl::numberOfStages() const {
  const auto value = getUnsigned(openstudio::Coil_Heating_Electric_MultiStageFields::NumberofStages, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingElectricMultiStage_Impl::setNumberOfStages(unsigned numberOfStages) {
  return setUnsigned(openstudio::Coil_Heating_Electric_MultiStageFields::NumberofStages, numberOfStages);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
