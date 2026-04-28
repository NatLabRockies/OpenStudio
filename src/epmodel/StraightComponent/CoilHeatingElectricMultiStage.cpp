/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingElectricMultiStage.hpp"
#include "StraightComponent/CoilHeatingElectricMultiStage_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Heating_Electric_MultiStage_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilHeatingElectricMultiStage::CoilHeatingElectricMultiStage(const Model& model)
  : StraightComponent(CoilHeatingElectricMultiStage::iddObjectType(), model) {
  // Keep required scalar field populated for strict non-optional getter behavior.
  auto availabilitySchedule = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(getImpl<detail::CoilHeatingElectricMultiStage_Impl>()->setAvailabilitySchedule(availabilitySchedule));
  OS_ASSERT(getImpl<detail::CoilHeatingElectricMultiStage_Impl>()->setNumberOfStages(1u));
}

CoilHeatingElectricMultiStage::CoilHeatingElectricMultiStage(std::shared_ptr<detail::CoilHeatingElectricMultiStage_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilHeatingElectricMultiStage::iddObjectType() {
  return IddObjectType::Coil_Heating_Electric_MultiStage;
}

bool CoilHeatingElectricMultiStage::addToNode(Node& node) {
  return getImpl<detail::CoilHeatingElectricMultiStage_Impl>()->addToNode(node);
}

Schedule CoilHeatingElectricMultiStage::availabilitySchedule() const {
  return getImpl<detail::CoilHeatingElectricMultiStage_Impl>()->availabilitySchedule();
}

bool CoilHeatingElectricMultiStage::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::CoilHeatingElectricMultiStage_Impl>()->setAvailabilitySchedule(schedule);
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

bool CoilHeatingElectricMultiStage_Impl::addToNode(Node& node) {
  return false;
}

Schedule CoilHeatingElectricMultiStage_Impl::availabilitySchedule() const {
  auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(
    openstudio::Coil_Heating_Electric_MultiStageFields::AvailabilityScheduleName);
  if (!value) {
    value = this->model().alwaysOnDiscreteSchedule();
    OS_ASSERT(value);
    const_cast<CoilHeatingElectricMultiStage_Impl*>(this)->setAvailabilitySchedule(*value);
    value = getObject<ModelObject>().getModelObjectTarget<Schedule>(
      openstudio::Coil_Heating_Electric_MultiStageFields::AvailabilityScheduleName);
  }
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingElectricMultiStage_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return setPointer(openstudio::Coil_Heating_Electric_MultiStageFields::AvailabilityScheduleName, schedule.handle(), false);
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
