/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingGasMultiStage.hpp"
#include "StraightComponent/CoilHeatingGasMultiStage_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Heating_Gas_MultiStage_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  CoilHeatingGasMultiStage::CoilHeatingGasMultiStage(const Model& model) : StraightComponent(CoilHeatingGasMultiStage::iddObjectType(), model) {
    auto availabilitySchedule = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setAvailabilitySchedule(availabilitySchedule));
    OS_ASSERT(getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setNumberOfStages(1u));
  }

  CoilHeatingGasMultiStage::CoilHeatingGasMultiStage(std::shared_ptr<detail::CoilHeatingGasMultiStage_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingGasMultiStage::iddObjectType() {
    return IddObjectType::Coil_Heating_Gas_MultiStage;
  }

  bool CoilHeatingGasMultiStage::addToNode(Node& node) {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->addToNode(node);
  }

  Schedule CoilHeatingGasMultiStage::availabilitySchedule() const {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->availabilitySchedule();
  }

  bool CoilHeatingGasMultiStage::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<Curve> CoilHeatingGasMultiStage::partLoadFractionCorrelationCurve() const {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->partLoadFractionCorrelationCurve();
  }

  bool CoilHeatingGasMultiStage::setPartLoadFractionCorrelationCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setPartLoadFractionCorrelationCurve(curve);
  }

  void CoilHeatingGasMultiStage::resetPartLoadFractionCorrelationCurve() {
    getImpl<detail::CoilHeatingGasMultiStage_Impl>()->resetPartLoadFractionCorrelationCurve();
  }

  boost::optional<double> CoilHeatingGasMultiStage::parasiticGasLoad() const {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->offCycleParasiticGasLoad();
  }

  bool CoilHeatingGasMultiStage::setParasiticGasLoad(double parasiticGasLoad) {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setOffCycleParasiticGasLoad(parasiticGasLoad);
  }

  void CoilHeatingGasMultiStage::resetParasiticGasLoad() {
    getImpl<detail::CoilHeatingGasMultiStage_Impl>()->resetOffCycleParasiticGasLoad();
  }

  boost::optional<double> CoilHeatingGasMultiStage::offCycleParasiticGasLoad() const {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->offCycleParasiticGasLoad();
  }

  bool CoilHeatingGasMultiStage::setOffCycleParasiticGasLoad(double offCycleParasiticGasLoad) {
    return getImpl<detail::CoilHeatingGasMultiStage_Impl>()->setOffCycleParasiticGasLoad(offCycleParasiticGasLoad);
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

    std::vector<ModelObject> CoilHeatingGasMultiStage_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto curve = partLoadFractionCorrelationCurve()) {
        result.push_back(*curve);
      }
      return result;
    }

    bool CoilHeatingGasMultiStage_Impl::addToNode(Node& node) {
      return false;
    }

    Schedule CoilHeatingGasMultiStage_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Heating_Gas_MultiStageFields::AvailabilityScheduleName);
      if (!value) {
        value = this->model().alwaysOnDiscreteSchedule();
        OS_ASSERT(value);
        const_cast<CoilHeatingGasMultiStage_Impl*>(this)->setAvailabilitySchedule(*value);
        value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Heating_Gas_MultiStageFields::AvailabilityScheduleName);
      }
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingGasMultiStage_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Heating_Gas_MultiStageFields::AvailabilityScheduleName, schedule.handle(), false);
    }

    boost::optional<Curve> CoilHeatingGasMultiStage_Impl::partLoadFractionCorrelationCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_Gas_MultiStageFields::PartLoadFractionCorrelationCurveName);
    }

    bool CoilHeatingGasMultiStage_Impl::setPartLoadFractionCorrelationCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_Gas_MultiStageFields::PartLoadFractionCorrelationCurveName, curve.handle(), false);
    }

    void CoilHeatingGasMultiStage_Impl::resetPartLoadFractionCorrelationCurve() {
      OS_ASSERT(setPointer(openstudio::Coil_Heating_Gas_MultiStageFields::PartLoadFractionCorrelationCurveName, openstudio::Handle(), false));
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
