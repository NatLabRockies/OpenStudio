/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirToAirComponent/HeatExchangerDesiccantBalancedFlow.hpp"
#include "AirToAirComponent/HeatExchangerDesiccantBalancedFlow_Impl.hpp"

#include "Model.hpp"
#include "ResourceObject/HeatExchangerDesiccantBalancedFlowPerformanceDataType1.hpp"
#include "ResourceObject/HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HeatExchanger_Desiccant_BalancedFlow_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

  HeatExchangerDesiccantBalancedFlow::HeatExchangerDesiccantBalancedFlow(const Model& model)
    : AirToAirComponent(HeatExchangerDesiccantBalancedFlow::iddObjectType(), model) {
    auto schedule = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(schedule));
    HeatExchangerDesiccantBalancedFlowPerformanceDataType1 performance(model);
    OS_ASSERT(setHeatExchangerPerformance(performance));
    OS_ASSERT(setEconomizerLockout(true));
  }

  HeatExchangerDesiccantBalancedFlow::HeatExchangerDesiccantBalancedFlow(
    const Model& model, const HeatExchangerDesiccantBalancedFlowPerformanceDataType1& heatExchangerPerformance)
    : AirToAirComponent(HeatExchangerDesiccantBalancedFlow::iddObjectType(), model) {
    auto schedule = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(schedule));
    if (!setHeatExchangerPerformance(heatExchangerPerformance)) {
      remove();
      throw std::invalid_argument("The desiccant heat-exchanger performance object must belong to the same model.");
    }
    OS_ASSERT(setEconomizerLockout(true));
  }

  HeatExchangerDesiccantBalancedFlow::HeatExchangerDesiccantBalancedFlow(std::shared_ptr<detail::HeatExchangerDesiccantBalancedFlow_Impl> impl)
    : AirToAirComponent(std::move(impl)) {}

  IddObjectType HeatExchangerDesiccantBalancedFlow::iddObjectType() {
    return IddObjectType::HeatExchanger_Desiccant_BalancedFlow;
  }

  Schedule HeatExchangerDesiccantBalancedFlow::availabilitySchedule() const {
    return getImpl<detail::HeatExchangerDesiccantBalancedFlow_Impl>()->availabilitySchedule();
  }

  bool HeatExchangerDesiccantBalancedFlow::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::HeatExchangerDesiccantBalancedFlow_Impl>()->setAvailabilitySchedule(schedule);
  }

  HeatExchangerDesiccantBalancedFlowPerformanceDataType1 HeatExchangerDesiccantBalancedFlow::heatExchangerPerformance() const {
    return getImpl<detail::HeatExchangerDesiccantBalancedFlow_Impl>()->heatExchangerPerformance();
  }

  bool HeatExchangerDesiccantBalancedFlow::setHeatExchangerPerformance(
    const HeatExchangerDesiccantBalancedFlowPerformanceDataType1& heatExchangerPerformance) {
    return getImpl<detail::HeatExchangerDesiccantBalancedFlow_Impl>()->setHeatExchangerPerformance(heatExchangerPerformance);
  }

  // Scalar accessors for Economizer Lockout
  //@{
  bool HeatExchangerDesiccantBalancedFlow::economizerLockout() const {
    return getImpl<detail::HeatExchangerDesiccantBalancedFlow_Impl>()->economizerLockout();
  }

  bool HeatExchangerDesiccantBalancedFlow::setEconomizerLockout(bool economizerLockout) {
    return getImpl<detail::HeatExchangerDesiccantBalancedFlow_Impl>()->setEconomizerLockout(economizerLockout);
  }
  //@}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    HeatExchangerDesiccantBalancedFlow_Impl::HeatExchangerDesiccantBalancedFlow_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : AirToAirComponent_Impl(idfObject, model, keepHandle) {}

    HeatExchangerDesiccantBalancedFlow_Impl::HeatExchangerDesiccantBalancedFlow_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : AirToAirComponent_Impl(other, model, keepHandle) {}

    HeatExchangerDesiccantBalancedFlow_Impl::HeatExchangerDesiccantBalancedFlow_Impl(const HeatExchangerDesiccantBalancedFlow_Impl& other,
                                                                                     Model_Impl* model, bool keepHandle)
      : AirToAirComponent_Impl(other, model, keepHandle) {}

    std::vector<ModelObject> HeatExchangerDesiccantBalancedFlow_Impl::children() const {
      return {heatExchangerPerformance()};
    }

    std::vector<IdfObject> HeatExchangerDesiccantBalancedFlow_Impl::remove() {
      if (!isRemovable()) {
        return {};
      }

      auto performance = getObject<ModelObject>().getModelObjectTarget<HeatExchangerDesiccantBalancedFlowPerformanceDataType1>(
        openstudio::HeatExchanger_Desiccant_BalancedFlowFields::HeatExchangerPerformanceName);
      auto result = AirToAirComponent_Impl::remove();
      if (!result.empty() && performance && performance->getModelObjectSources<HeatExchangerDesiccantBalancedFlow>().empty()) {
        auto removedPerformance = performance->remove();
        result.insert(result.end(), removedPerformance.begin(), removedPerformance.end());
      }
      return result;
    }

    Schedule HeatExchangerDesiccantBalancedFlow_Impl::availabilitySchedule() const {
      auto schedule =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::AvailabilityScheduleName);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool HeatExchangerDesiccantBalancedFlow_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::AvailabilityScheduleName,
                                           "HeatExchangerDesiccantBalancedFlow", "Availability", schedule);
    }

    HeatExchangerDesiccantBalancedFlowPerformanceDataType1 HeatExchangerDesiccantBalancedFlow_Impl::heatExchangerPerformance() const {
      auto performance = getObject<ModelObject>().getModelObjectTarget<HeatExchangerDesiccantBalancedFlowPerformanceDataType1>(
        openstudio::HeatExchanger_Desiccant_BalancedFlowFields::HeatExchangerPerformanceName);
      OS_ASSERT(performance);
      return *performance;
    }

    bool HeatExchangerDesiccantBalancedFlow_Impl::setHeatExchangerPerformance(
      const HeatExchangerDesiccantBalancedFlowPerformanceDataType1& heatExchangerPerformance) {
      if (heatExchangerPerformance.model() != model()) {
        return false;
      }

      const auto typeField = openstudio::HeatExchanger_Desiccant_BalancedFlowFields::HeatExchangerPerformanceObjectType;
      const auto nameField = openstudio::HeatExchanger_Desiccant_BalancedFlowFields::HeatExchangerPerformanceName;
      const auto oldType = getString(typeField).value_or("");
      const auto oldPerformance = getObject<ModelObject>().getModelObjectTarget<HeatExchangerDesiccantBalancedFlowPerformanceDataType1>(nameField);
      const auto performanceType = heatExchangerPerformance.iddObject().name();

      if (!setString(typeField, performanceType) || !setPointer(nameField, heatExchangerPerformance.handle(), false)) {
        OS_ASSERT(setString(typeField, oldType));
        OS_ASSERT(setPointer(nameField, oldPerformance ? oldPerformance->handle() : Handle(), false));
        return false;
      }
      return true;
    }

    // Scalar accessors for Economizer Lockout
    //@{
    bool HeatExchangerDesiccantBalancedFlow_Impl::economizerLockout() const {
      const auto value = getString(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::EconomizerLockout, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool HeatExchangerDesiccantBalancedFlow_Impl::setEconomizerLockout(bool economizerLockout) {
      const bool result = setString(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::EconomizerLockout, economizerLockout ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    unsigned HeatExchangerDesiccantBalancedFlow_Impl::primaryAirInletPort() const {
      return openstudio::HeatExchanger_Desiccant_BalancedFlowFields::RegenerationAirInletNodeName;
    }

    unsigned HeatExchangerDesiccantBalancedFlow_Impl::primaryAirOutletPort() const {
      return openstudio::HeatExchanger_Desiccant_BalancedFlowFields::RegenerationAirOutletNodeName;
    }

    unsigned HeatExchangerDesiccantBalancedFlow_Impl::secondaryAirInletPort() const {
      return openstudio::HeatExchanger_Desiccant_BalancedFlowFields::ProcessAirInletNodeName;
    }

    unsigned HeatExchangerDesiccantBalancedFlow_Impl::secondaryAirOutletPort() const {
      return openstudio::HeatExchanger_Desiccant_BalancedFlowFields::ProcessAirOutletNodeName;
    }

    void HeatExchangerDesiccantBalancedFlow_Impl::doCanonicalize(LoadContext& context) {
      AirToAirComponent_Impl::doCanonicalize(context);

      auto schedule =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::AvailabilityScheduleName);
      if (!schedule) {
        auto alwaysOn = model().alwaysOnDiscreteSchedule();
        OS_ASSERT(setAvailabilitySchedule(alwaysOn));
        detail::addLoadInfo(context, "Attached the always-on schedule to desiccant heat exchanger '" + getObject<ModelObject>().nameString() + "'.");
      }

      auto performance = getObject<ModelObject>().getModelObjectTarget<HeatExchangerDesiccantBalancedFlowPerformanceDataType1>(
        openstudio::HeatExchanger_Desiccant_BalancedFlowFields::HeatExchangerPerformanceName);
      if (!performance) {
        performance = HeatExchangerDesiccantBalancedFlowPerformanceDataType1(model());
        detail::addLoadInfo(context,
                            "Created missing performance data for desiccant heat exchanger '" + getObject<ModelObject>().nameString() + "'.");
      }

      const auto storedType = getString(openstudio::HeatExchanger_Desiccant_BalancedFlowFields::HeatExchangerPerformanceObjectType);
      if (!(storedType && openstudio::istringEqual(*storedType, performance->iddObject().name()))) {
        detail::addLoadInfo(context,
                            "Aligned the performance object type for desiccant heat exchanger '" + getObject<ModelObject>().nameString() + "'.");
      }
      OS_ASSERT(setHeatExchangerPerformance(*performance));
    }
    //@}

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
