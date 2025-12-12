/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HeatPumpAirToWaterHeating.hpp"
#include "HeatPumpAirToWaterHeating_Impl.hpp"

#include "HeatPumpAirToWater.hpp"
#include "HeatPumpAirToWater_Impl.hpp"
#include "HeatPumpAirToWaterHeatingSpeedData.hpp"
#include "HeatPumpAirToWaterHeatingSpeedData_Impl.hpp"

#include "Schedule.hpp"
#include "Schedule_Impl.hpp"
#include "Curve.hpp"
#include "Curve_Impl.hpp"
#include "ModelObjectList.hpp"
#include "ModelObjectList_Impl.hpp"

#include "ScheduleTypeLimits.hpp"
#include "ScheduleTypeRegistry.hpp"

#include "PlantLoop.hpp"
#include "PlantLoop_Impl.hpp"
#include "Node.hpp"

// Need for clone override
#include "Model.hpp"
#include "Model_Impl.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/ContainersMove.hpp"
#include "../utilities/data/DataEnums.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_HeatPump_AirToWater_Heating_FieldEnums.hxx>

namespace openstudio {
namespace model {

  namespace detail {

    HeatPumpAirToWaterHeating_Impl::HeatPumpAirToWaterHeating_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : StraightComponent_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == HeatPumpAirToWaterHeating::iddObjectType());
    }

    HeatPumpAirToWaterHeating_Impl::HeatPumpAirToWaterHeating_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model,
                                                                   bool keepHandle)
      : StraightComponent_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == HeatPumpAirToWaterHeating::iddObjectType());
    }

    HeatPumpAirToWaterHeating_Impl::HeatPumpAirToWaterHeating_Impl(const HeatPumpAirToWaterHeating_Impl& other, Model_Impl* model, bool keepHandle)
      : StraightComponent_Impl(other, model, keepHandle) {}

    const std::vector<std::string>& HeatPumpAirToWaterHeating_Impl::outputVariableNames() const {
      static std::vector<std::string> result;
      if (result.empty()) {
      }
      return result;
    }

    std::vector<ScheduleTypeKey> HeatPumpAirToWaterHeating_Impl::getScheduleTypeKeys(const Schedule& schedule) const {
      std::vector<ScheduleTypeKey> result;
      const UnsignedVector fieldIndices = getSourceIndices(schedule.handle());
      if (std::find(fieldIndices.cbegin(), fieldIndices.cend(), OS_HeatPump_AirToWater_HeatingFields::AvailabilityScheduleName)
          != fieldIndices.cend()) {
        result.emplace_back("HeatPumpAirToWaterHeating", "Availability");
      }
      return result;
    }

    IddObjectType HeatPumpAirToWaterHeating_Impl::iddObjectType() const {
      return HeatPumpAirToWaterHeating::iddObjectType();
    }

    unsigned HeatPumpAirToWaterHeating_Impl::inletPort() const {
      return OS_HeatPump_AirToWater_HeatingFields::HotWaterInletNodeName;
    }

    unsigned HeatPumpAirToWaterHeating_Impl::outletPort() const {
      return OS_HeatPump_AirToWater_HeatingFields::HotWaterOutletNodeName;
    }

    bool HeatPumpAirToWaterHeating_Impl::addToNode(Node& node) {
      if (boost::optional<PlantLoop> plant = node.plantLoop()) {
        if (plant->supplyComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }

      return false;
    }

    boost::optional<HVACComponent> HeatPumpAirToWaterHeating_Impl::containingHVACComponent() const {
      auto awhp_ = heatPumpAirToWater();
      if (awhp_) {
        return std::move(*awhp_);
      }
      return boost::none;
    }

    boost::optional<HeatPumpAirToWater> HeatPumpAirToWaterHeating_Impl::heatPumpAirToWater() const {
      auto awhps = getObject<ModelObject>().getModelObjectSources<HeatPumpAirToWater>(HeatPumpAirToWater::iddObjectType());
      if (awhps.empty()) {
        return boost::none;
      }
      if (awhps.size() > 1) {
        LOG(Error, briefDescription() << " is referenced by more than one HeatPumpAirToWater, returning the first");
      }
      return awhps[0];
    }

    ModelObject HeatPumpAirToWaterHeating_Impl::clone(Model model) const {
      const bool same_model = this->model() == model;
      // This handles resetting the ports, and bypassing ParentObject::clone so it doesn't clone children
      auto t_clone = StraightComponent_Impl::clone(model).cast<HeatPumpAirToWaterHeating>();

      // Make a clean list and repopulate it, without cloning the SpeedData objects
      auto newSpeedList = ModelObjectList(model);
      newSpeedList.setName(t_clone.nameString() + " Speed Data List");
      bool ok = t_clone.getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setSpeedDataList(newSpeedList);
      OS_ASSERT(ok);

      for (const auto& speed : speeds()) {
        if (same_model) {
          ok = t_clone.addSpeed(speed);
        } else {
          auto speedClone = speed.clone(model).cast<HeatPumpAirToWaterHeatingSpeedData>();
          ok = t_clone.addSpeed(speedClone);
        }
        OS_ASSERT(ok);
      }

      return std::move(t_clone);
    }

    std::vector<ModelObject> HeatPumpAirToWaterHeating_Impl::children() const {
      std::vector<ModelObject> children;
      if (auto c_ = minimumLeavingWaterTemperatureCurve()) {
        children.emplace_back(std::move(*c_));
      }
      if (auto c_ = maximumLeavingWaterTemperatureCurve()) {
        children.emplace_back(std::move(*c_));
      }
      if (auto const speedDataList_ = optionalSpeedDataList()) {
        for (const auto& mo : speedDataList_->modelObjects()) {
          children.push_back(mo);
        }
      }
      return children;
    }

    // std::vector<IddObjectType> allowableChildTypes() const override;

    std::vector<IdfObject> HeatPumpAirToWaterHeating_Impl::remove() {
      // ModelObjectList is kinda dumb, it removes all the modelObjects it has, which we don't want
      // We listed the SpeedData (ResourceObjects) in children, so it should be handled by ParentObject::remove
      auto speedList_ = optionalSpeedDataList();
      std::vector<IdfObject> result = StraightComponent_Impl::remove();
      if (!result.empty() && speedList_) {
        speedList_->clearExtensibleGroups();  // Clearer than removeAllModelObjects (which does the same thing, but could mean delete all objects)
        openstudio::detail::concat_helper(result, speedList_->remove());
      }

      return result;
    }

    Schedule HeatPumpAirToWaterHeating_Impl::availabilitySchedule() const {
      boost::optional<Schedule> value = optionalAvailabilitySchedule();
      if (!value) {
        LOG_AND_THROW(briefDescription() << " does not have an Availability Schedule attached.");
      }
      return value.get();
    }

    double HeatPumpAirToWaterHeating_Impl::ratedInletAirTemperature() const {
      boost::optional<double> value = getDouble(OS_HeatPump_AirToWater_HeatingFields::RatedInletAirTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<double> HeatPumpAirToWaterHeating_Impl::ratedAirFlowRate() const {
      return getDouble(OS_HeatPump_AirToWater_HeatingFields::RatedAirFlowRate, true);
    }

    bool HeatPumpAirToWaterHeating_Impl::isRatedAirFlowRateAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(OS_HeatPump_AirToWater_HeatingFields::RatedAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "autosize");
      }
      return result;
    }

    double HeatPumpAirToWaterHeating_Impl::ratedLeavingWaterTemperature() const {
      boost::optional<double> value = getDouble(OS_HeatPump_AirToWater_HeatingFields::RatedLeavingWaterTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<double> HeatPumpAirToWaterHeating_Impl::ratedWaterFlowRate() const {
      return getDouble(OS_HeatPump_AirToWater_HeatingFields::RatedWaterFlowRate, true);
    }

    bool HeatPumpAirToWaterHeating_Impl::isRatedWaterFlowRateAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(OS_HeatPump_AirToWater_HeatingFields::RatedWaterFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "autosize");
      }
      return result;
    }

    double HeatPumpAirToWaterHeating_Impl::minimumOutdoorAirTemperature() const {
      boost::optional<double> value = getDouble(OS_HeatPump_AirToWater_HeatingFields::MinimumOutdoorAirTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    double HeatPumpAirToWaterHeating_Impl::maximumOutdoorAirTemperature() const {
      boost::optional<double> value = getDouble(OS_HeatPump_AirToWater_HeatingFields::MaximumOutdoorAirTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<Curve> HeatPumpAirToWaterHeating_Impl::minimumLeavingWaterTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(OS_HeatPump_AirToWater_HeatingFields::MinimumLeavingWaterTemperatureCurveName);
    }

    boost::optional<Curve> HeatPumpAirToWaterHeating_Impl::maximumLeavingWaterTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(OS_HeatPump_AirToWater_HeatingFields::MaximumLeavingWaterTemperatureCurveName);
    }

    double HeatPumpAirToWaterHeating_Impl::sizingFactor() const {
      boost::optional<double> value = getDouble(OS_HeatPump_AirToWater_HeatingFields::SizingFactor, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<HeatPumpAirToWaterHeatingSpeedData> HeatPumpAirToWaterHeating_Impl::boosterModeOnSpeed() const {
      return getObject<ModelObject>().getModelObjectTarget<HeatPumpAirToWaterHeatingSpeedData>(
        OS_HeatPump_AirToWater_HeatingFields::BoosterModeOnSpeed);
    }

    bool HeatPumpAirToWaterHeating_Impl::setAvailabilitySchedule(Schedule& availabilitySchedule) {
      const bool result = setSchedule(OS_HeatPump_AirToWater_HeatingFields::AvailabilityScheduleName, "HeatPumpAirToWaterHeating", "Availability",
                                      availabilitySchedule);
      return result;
    }

    bool HeatPumpAirToWaterHeating_Impl::setRatedInletAirTemperature(double ratedInletAirTemperature) {
      const bool result = setDouble(OS_HeatPump_AirToWater_HeatingFields::RatedInletAirTemperature, ratedInletAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HeatPumpAirToWaterHeating_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
      const bool result = setDouble(OS_HeatPump_AirToWater_HeatingFields::RatedAirFlowRate, ratedAirFlowRate);
      return result;
    }

    void HeatPumpAirToWaterHeating_Impl::autosizeRatedAirFlowRate() {
      const bool result = setString(OS_HeatPump_AirToWater_HeatingFields::RatedAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    bool HeatPumpAirToWaterHeating_Impl::setRatedLeavingWaterTemperature(double ratedLeavingWaterTemperature) {
      const bool result = setDouble(OS_HeatPump_AirToWater_HeatingFields::RatedLeavingWaterTemperature, ratedLeavingWaterTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HeatPumpAirToWaterHeating_Impl::setRatedWaterFlowRate(double ratedWaterFlowRate) {
      const bool result = setDouble(OS_HeatPump_AirToWater_HeatingFields::RatedWaterFlowRate, ratedWaterFlowRate);
      return result;
    }

    void HeatPumpAirToWaterHeating_Impl::autosizeRatedWaterFlowRate() {
      const bool result = setString(OS_HeatPump_AirToWater_HeatingFields::RatedWaterFlowRate, "autosize");
      OS_ASSERT(result);
    }

    bool HeatPumpAirToWaterHeating_Impl::setMinimumOutdoorAirTemperature(double minimumOutdoorAirTemperature) {
      const bool result = setDouble(OS_HeatPump_AirToWater_HeatingFields::MinimumOutdoorAirTemperature, minimumOutdoorAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HeatPumpAirToWaterHeating_Impl::setMaximumOutdoorAirTemperature(double maximumOutdoorAirTemperature) {
      const bool result = setDouble(OS_HeatPump_AirToWater_HeatingFields::MaximumOutdoorAirTemperature, maximumOutdoorAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HeatPumpAirToWaterHeating_Impl::setMinimumLeavingWaterTemperatureCurve(const Curve& minimumLeavingWaterTemperatureCurve) {
      const bool result =
        setPointer(OS_HeatPump_AirToWater_HeatingFields::MinimumLeavingWaterTemperatureCurveName, minimumLeavingWaterTemperatureCurve.handle());
      return result;
    }

    void HeatPumpAirToWaterHeating_Impl::resetMinimumLeavingWaterTemperatureCurve() {
      const bool result = setString(OS_HeatPump_AirToWater_HeatingFields::MinimumLeavingWaterTemperatureCurveName, "");
      OS_ASSERT(result);
    }

    bool HeatPumpAirToWaterHeating_Impl::setMaximumLeavingWaterTemperatureCurve(const Curve& maximumLeavingWaterTemperatureCurve) {
      const bool result =
        setPointer(OS_HeatPump_AirToWater_HeatingFields::MaximumLeavingWaterTemperatureCurveName, maximumLeavingWaterTemperatureCurve.handle());
      return result;
    }

    void HeatPumpAirToWaterHeating_Impl::resetMaximumLeavingWaterTemperatureCurve() {
      const bool result = setString(OS_HeatPump_AirToWater_HeatingFields::MaximumLeavingWaterTemperatureCurveName, "");
      OS_ASSERT(result);
    }

    bool HeatPumpAirToWaterHeating_Impl::setSizingFactor(double sizingFactor) {
      const bool result = setDouble(OS_HeatPump_AirToWater_HeatingFields::SizingFactor, sizingFactor);
      return result;
    }

    bool HeatPumpAirToWaterHeating_Impl::setBoosterModeOnSpeed(const HeatPumpAirToWaterHeatingSpeedData& boosterModeOnSpeed) {
      const bool result = setPointer(OS_HeatPump_AirToWater_HeatingFields::BoosterModeOnSpeed, boosterModeOnSpeed.handle());
      return result;
    }

    void HeatPumpAirToWaterHeating_Impl::resetBoosterModeOnSpeed() {
      const bool result = setString(OS_HeatPump_AirToWater_HeatingFields::BoosterModeOnSpeed, "");
      OS_ASSERT(result);
    }

    boost::optional<double> HeatPumpAirToWaterHeating_Impl::autosizedRatedAirFlowRate() const {
      boost::optional<double> result;
      if (auto awhp_ = heatPumpAirToWater()) {
        result = awhp_->autosizedRatedAirFlowRateinHeatingMode();
      }
      return result;
    }

    boost::optional<double> HeatPumpAirToWaterHeating_Impl::autosizedRatedWaterFlowRate() const {
      boost::optional<double> result;
      if (auto awhp_ = heatPumpAirToWater()) {
        result = awhp_->autosizedRatedWaterFlowRateinHeatingMode();
      }
      return result;
    }

    boost::optional<double> HeatPumpAirToWaterHeating_Impl::autosizedRatedHeatingCapacity() const {
      boost::optional<double> result;
      if (auto awhp_ = heatPumpAirToWater()) {
        result = awhp_->autosizedRatedHeatingCapacity();
      }
      return result;
    }

    void HeatPumpAirToWaterHeating_Impl::autosize() {
      autosizeRatedAirFlowRate();
      autosizeRatedWaterFlowRate();
      auto speeds = this->speeds();
      if (!speeds.empty()) {
        speeds.back().autosize();  // Only need/can autosize the last (highest) speed
      }
    }

    void HeatPumpAirToWaterHeating_Impl::applySizingValues() {
      if (boost::optional<double> val_ = autosizedRatedAirFlowRate()) {
        setRatedAirFlowRate(*val_);
      }

      if (boost::optional<double> val_ = autosizedRatedWaterFlowRate()) {
        setRatedWaterFlowRate(*val_);
      }

      if (boost::optional<double> val_ = autosizedRatedHeatingCapacity()) {
        auto speeds = this->speeds();
        if (!speeds.empty()) {
          speeds.back().setRatedHeatingCapacity(*val_);  // Only need/can autosize the last (highest) speed
        }
      }
    }

    ComponentType HeatPumpAirToWaterHeating_Impl::componentType() const {
      return ComponentType::Heating;
    }

    std::vector<FuelType> HeatPumpAirToWaterHeating_Impl::coolingFuelTypes() const {
      return {};
    }

    std::vector<FuelType> HeatPumpAirToWaterHeating_Impl::heatingFuelTypes() const {
      return {FuelType::Electricity};
    }

    std::vector<AppGFuelType> HeatPumpAirToWaterHeating_Impl::appGHeatingFuelTypes() const {
      return {AppGFuelType::HeatPump};
    }

    boost::optional<Schedule> HeatPumpAirToWaterHeating_Impl::optionalAvailabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_HeatPump_AirToWater_HeatingFields::AvailabilityScheduleName);
    }

    // Speed API
    boost::optional<ModelObjectList> HeatPumpAirToWaterHeating_Impl::optionalSpeedDataList() const {
      return getObject<ModelObject>().getModelObjectTarget<ModelObjectList>(OS_HeatPump_AirToWater_HeatingFields::SpeedDataList);
    }

    ModelObjectList HeatPumpAirToWaterHeating_Impl::speedDataList() const {
      boost::optional<ModelObjectList> value = optionalSpeedDataList();
      if (!value) {
        LOG_AND_THROW(briefDescription() << " does not have a Speed Data List attached.");
      }
      return value.get();
    }

    bool HeatPumpAirToWaterHeating_Impl::setSpeedDataList(const ModelObjectList& speedDataList) {
      const bool result = setPointer(OS_HeatPump_AirToWater_HeatingFields::SpeedDataList, speedDataList.handle());
      return result;
    }

    void HeatPumpAirToWaterHeating_Impl::resetSpeedDataList() {
      bool result = setString(OS_HeatPump_AirToWater_HeatingFields::SpeedDataList, "");
      OS_ASSERT(result);
    }

    std::vector<HeatPumpAirToWaterHeatingSpeedData> HeatPumpAirToWaterHeating_Impl::speeds() const {
      std::vector<HeatPumpAirToWaterHeatingSpeedData> result;
      auto const modelObjects = speedDataList().modelObjects();

      for (auto&& elem : modelObjects) {
        auto modelObject = elem.optionalCast<HeatPumpAirToWaterHeatingSpeedData>();
        if (modelObject) {
          result.push_back(std::move(*modelObject));
        }
      }
      return result;
    }

    unsigned HeatPumpAirToWaterHeating_Impl::numberOfSpeeds() const {
      return speeds().size();  // This is right in all cases, but this is slow
      // return speedDataList().size(); // This is fast, but could be wrong if the user put non-SpeedData objects in the list or if there are blanks
    }

    boost::optional<unsigned> HeatPumpAirToWaterHeating_Impl::speedIndex(const HeatPumpAirToWaterHeatingSpeedData& speed) const {
      const auto speedVector = speeds();
      auto it = std::find_if(speedVector.cbegin(), speedVector.cend(), [&](const HeatPumpAirToWaterHeatingSpeedData& s) { return s == speed; });
      if (it != speedVector.cend()) {
        return static_cast<unsigned>(std::distance(speedVector.cbegin(), it)) + 1;  // 1-indexed
      }
      return boost::none;
    }

    bool HeatPumpAirToWaterHeating_Impl::addSpeed(const HeatPumpAirToWaterHeatingSpeedData& speed) {
      if (numberOfSpeeds() >= HeatPumpAirToWaterHeating::maximum_number_of_speeds) {
        LOG(Error, "You have reached the maximum number of speeds (=" << HeatPumpAirToWaterHeating::maximum_number_of_speeds << "), occurred for "
                                                                      << briefDescription() << ".");
        return false;  // too many speeds
      }
      if (speedIndex(speed)) {
        return false;  // already in the list
      }

      return speedDataList().addModelObject(speed);
    }

    bool HeatPumpAirToWaterHeating_Impl::setSpeedIndex(const HeatPumpAirToWaterHeatingSpeedData& speed, unsigned index) {
      auto cur_idx_ = speedIndex(speed);
      if (!cur_idx_) {
        LOG(Warn, "For " << briefDescription() << " cannot set the index of speed " << speed.briefDescription() << " since it is not part of it.");
        return false;
      }

      auto speedVector = speeds();

      if (index < 1) {
        LOG(Debug, "Requested a speed index of " << index << " < 1 to be assigned to " << speed.briefDescription() << ", resetting to 1");
        index = 1;
      } else if (index > speedVector.size()) {
        LOG(Debug, "Requested a speed index of " << index << " > number of speeds (" << speedVector.size() << ") to be assigned to "
                                                 << speed.briefDescription() << ", resetting to " << speedVector.size());
        index = speedVector.size();
      }

      speedVector.erase(speedVector.begin() + (*cur_idx_ - 1));      // stageIndex is 1-indexed, and vector is 0-indexed
      speedVector.insert(speedVector.begin() + (index - 1), speed);  // index is 1-indexed, and vector is 0-indexed

      return setSpeeds(speedVector);
    }

    bool HeatPumpAirToWaterHeating_Impl::addSpeed(const HeatPumpAirToWaterHeatingSpeedData& speed, unsigned index) {
      bool ok = addSpeed(speed);
      if (!ok) {
        return false;
      }
      ok = setSpeedIndex(speed, index);
      return ok;
    }

    bool HeatPumpAirToWaterHeating_Impl::setSpeeds(const std::vector<HeatPumpAirToWaterHeatingSpeedData>& speeds) {
      // Clear the extensible groups, and redo them
      bool ok = true;
      removeAllSpeeds();
      for (const auto& s : speeds) {
        ok &= addSpeed(s);
      }
      return ok;
    }

    bool HeatPumpAirToWaterHeating_Impl::removeSpeed(const HeatPumpAirToWaterHeatingSpeedData& speed) {  // NOLINT(readability-*)
      auto speedList = speedDataList();
      if (!speedList.hasModelObject(speed)) {
        LOG(Warn, "For " << briefDescription() << " cannot remove speed " << speed.briefDescription() << " since it is not part of it.");
        return false;
      }
      speedList.removeModelObject(speed);
      return true;
    }

    bool HeatPumpAirToWaterHeating_Impl::removeSpeed(unsigned index) {
      bool result = false;
      if (index < 1) {
        return false;
      }
      auto speedVector = speeds();
      if (index <= speedVector.size()) {
        result = removeSpeed(speedVector[index - 1]);  // index is 1-indexed
      }
      return result;
    }

    void HeatPumpAirToWaterHeating_Impl::removeAllSpeeds() {  // NOLINT(readability-make-member-function-const)
      // TODO: same question, do we want to remove the underlying objects too?
      speedDataList().removeAllModelObjects();  // This just clears the list, does not delete the underlying objects
    }

  }  // namespace detail

  HeatPumpAirToWaterHeating::HeatPumpAirToWaterHeating(const Model& model) : StraightComponent(HeatPumpAirToWaterHeating::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::HeatPumpAirToWaterHeating_Impl>());

    bool ok = true;

    auto speedList = ModelObjectList(model);
    speedList.setName(this->nameString() + " Speed Data List");
    ok = getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setSpeedDataList(speedList);
    OS_ASSERT(ok);

    auto availabilitySchedule = model.alwaysOnDiscreteSchedule();
    ok = setAvailabilitySchedule(availabilitySchedule);
    OS_ASSERT(ok);

    // IDD Defaults
    setRatedInletAirTemperature(8.0);
    autosizeRatedAirFlowRate();
    setRatedLeavingWaterTemperature(40.0);
    autosizeRatedWaterFlowRate();
    setMinimumOutdoorAirTemperature(-30.0);
    setMaximumOutdoorAirTemperature(100.0);
    setSizingFactor(1.0);
  }

  IddObjectType HeatPumpAirToWaterHeating::iddObjectType() {
    return {IddObjectType::OS_HeatPump_AirToWater_Heating};
  }

  Schedule HeatPumpAirToWaterHeating::availabilitySchedule() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->availabilitySchedule();
  }

  double HeatPumpAirToWaterHeating::ratedInletAirTemperature() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->ratedInletAirTemperature();
  }

  boost::optional<double> HeatPumpAirToWaterHeating::ratedAirFlowRate() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->ratedAirFlowRate();
  }

  bool HeatPumpAirToWaterHeating::isRatedAirFlowRateAutosized() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->isRatedAirFlowRateAutosized();
  }

  boost::optional<double> HeatPumpAirToWaterHeating::autosizedRatedAirFlowRate() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->autosizedRatedAirFlowRate();
  }

  double HeatPumpAirToWaterHeating::ratedLeavingWaterTemperature() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->ratedLeavingWaterTemperature();
  }

  boost::optional<double> HeatPumpAirToWaterHeating::ratedWaterFlowRate() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->ratedWaterFlowRate();
  }

  bool HeatPumpAirToWaterHeating::isRatedWaterFlowRateAutosized() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->isRatedWaterFlowRateAutosized();
  }

  boost::optional<double> HeatPumpAirToWaterHeating::autosizedRatedWaterFlowRate() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->autosizedRatedWaterFlowRate();
  }

  double HeatPumpAirToWaterHeating::minimumOutdoorAirTemperature() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->minimumOutdoorAirTemperature();
  }

  double HeatPumpAirToWaterHeating::maximumOutdoorAirTemperature() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->maximumOutdoorAirTemperature();
  }

  boost::optional<Curve> HeatPumpAirToWaterHeating::minimumLeavingWaterTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->minimumLeavingWaterTemperatureCurve();
  }

  boost::optional<Curve> HeatPumpAirToWaterHeating::maximumLeavingWaterTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->maximumLeavingWaterTemperatureCurve();
  }

  double HeatPumpAirToWaterHeating::sizingFactor() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->sizingFactor();
  }

  boost::optional<HeatPumpAirToWaterHeatingSpeedData> HeatPumpAirToWaterHeating::boosterModeOnSpeed() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->boosterModeOnSpeed();
  }

  bool HeatPumpAirToWaterHeating::setAvailabilitySchedule(Schedule& availabilitySchedule) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setAvailabilitySchedule(availabilitySchedule);
  }

  bool HeatPumpAirToWaterHeating::setRatedInletAirTemperature(double ratedInletAirTemperature) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setRatedInletAirTemperature(ratedInletAirTemperature);
  }

  bool HeatPumpAirToWaterHeating::setRatedAirFlowRate(double ratedAirFlowRate) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
  }

  void HeatPumpAirToWaterHeating::autosizeRatedAirFlowRate() {
    getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->autosizeRatedAirFlowRate();
  }

  bool HeatPumpAirToWaterHeating::setRatedLeavingWaterTemperature(double ratedLeavingWaterTemperature) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setRatedLeavingWaterTemperature(ratedLeavingWaterTemperature);
  }

  bool HeatPumpAirToWaterHeating::setRatedWaterFlowRate(double ratedWaterFlowRate) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setRatedWaterFlowRate(ratedWaterFlowRate);
  }

  void HeatPumpAirToWaterHeating::autosizeRatedWaterFlowRate() {
    getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->autosizeRatedWaterFlowRate();
  }

  bool HeatPumpAirToWaterHeating::setMinimumOutdoorAirTemperature(double minimumOutdoorAirTemperature) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setMinimumOutdoorAirTemperature(minimumOutdoorAirTemperature);
  }

  bool HeatPumpAirToWaterHeating::setMaximumOutdoorAirTemperature(double maximumOutdoorAirTemperature) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setMaximumOutdoorAirTemperature(maximumOutdoorAirTemperature);
  }

  bool HeatPumpAirToWaterHeating::setMinimumLeavingWaterTemperatureCurve(const Curve& minimumLeavingWaterTemperatureCurve) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setMinimumLeavingWaterTemperatureCurve(minimumLeavingWaterTemperatureCurve);
  }

  void HeatPumpAirToWaterHeating::resetMinimumLeavingWaterTemperatureCurve() {
    getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->resetMinimumLeavingWaterTemperatureCurve();
  }

  bool HeatPumpAirToWaterHeating::setMaximumLeavingWaterTemperatureCurve(const Curve& maximumLeavingWaterTemperatureCurve) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setMaximumLeavingWaterTemperatureCurve(maximumLeavingWaterTemperatureCurve);
  }

  void HeatPumpAirToWaterHeating::resetMaximumLeavingWaterTemperatureCurve() {
    getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->resetMaximumLeavingWaterTemperatureCurve();
  }

  bool HeatPumpAirToWaterHeating::setSizingFactor(double sizingFactor) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setSizingFactor(sizingFactor);
  }

  bool HeatPumpAirToWaterHeating::setBoosterModeOnSpeed(const HeatPumpAirToWaterHeatingSpeedData& boosterModeOnSpeed) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setBoosterModeOnSpeed(boosterModeOnSpeed);
  }

  void HeatPumpAirToWaterHeating::resetBoosterModeOnSpeed() {
    getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->resetBoosterModeOnSpeed();
  }

  // Speed Data API
  unsigned HeatPumpAirToWaterHeating::numberOfSpeeds() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->numberOfSpeeds();
  }

  boost::optional<unsigned> HeatPumpAirToWaterHeating::speedIndex(const HeatPumpAirToWaterHeatingSpeedData& speed) const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->speedIndex(speed);
  }

  std::vector<HeatPumpAirToWaterHeatingSpeedData> HeatPumpAirToWaterHeating::speeds() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->speeds();
  }

  bool HeatPumpAirToWaterHeating::addSpeed(const HeatPumpAirToWaterHeatingSpeedData& speed) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->addSpeed(speed);
  }

  bool HeatPumpAirToWaterHeating::addSpeed(const HeatPumpAirToWaterHeatingSpeedData& speed, unsigned index) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->addSpeed(speed, index);
  }

  bool HeatPumpAirToWaterHeating::setSpeedIndex(const HeatPumpAirToWaterHeatingSpeedData& speed, unsigned index) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setSpeedIndex(speed, index);
  }

  bool HeatPumpAirToWaterHeating::setSpeeds(const std::vector<HeatPumpAirToWaterHeatingSpeedData>& speeds) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->setSpeeds(speeds);
  }

  void HeatPumpAirToWaterHeating::removeAllSpeeds() {
    getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->removeAllSpeeds();
  }

  bool HeatPumpAirToWaterHeating::removeSpeed(const HeatPumpAirToWaterHeatingSpeedData& speed) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->removeSpeed(speed);
  }

  bool HeatPumpAirToWaterHeating::removeSpeed(unsigned index) {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->removeSpeed(index);
  }

  boost::optional<HeatPumpAirToWater> HeatPumpAirToWaterHeating::heatPumpAirToWater() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->heatPumpAirToWater();
  }

  boost::optional<double> HeatPumpAirToWaterHeating::autosizedRatedHeatingCapacity() const {
    return getImpl<detail::HeatPumpAirToWaterHeating_Impl>()->autosizedRatedHeatingCapacity();
  }

  /// @cond
  HeatPumpAirToWaterHeating::HeatPumpAirToWaterHeating(std::shared_ptr<detail::HeatPumpAirToWaterHeating_Impl> impl)
    : StraightComponent(std::move(impl)) {}
  /// @endcond

}  // namespace model
}  // namespace openstudio
