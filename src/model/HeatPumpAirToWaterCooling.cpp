/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HeatPumpAirToWaterCooling.hpp"
#include "HeatPumpAirToWaterCooling_Impl.hpp"

#include "HeatPumpAirToWater.hpp"
#include "HeatPumpAirToWater_Impl.hpp"
#include "HeatPumpAirToWaterCoolingSpeedData.hpp"
#include "HeatPumpAirToWaterCoolingSpeedData_Impl.hpp"

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
#include <utilities/idd/OS_HeatPump_AirToWater_Cooling_FieldEnums.hxx>

namespace openstudio {
namespace model {

  namespace detail {

    HeatPumpAirToWaterCooling_Impl::HeatPumpAirToWaterCooling_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : StraightComponent_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == HeatPumpAirToWaterCooling::iddObjectType());
    }

    HeatPumpAirToWaterCooling_Impl::HeatPumpAirToWaterCooling_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model,
                                                                   bool keepHandle)
      : StraightComponent_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == HeatPumpAirToWaterCooling::iddObjectType());
    }

    HeatPumpAirToWaterCooling_Impl::HeatPumpAirToWaterCooling_Impl(const HeatPumpAirToWaterCooling_Impl& other, Model_Impl* model, bool keepHandle)
      : StraightComponent_Impl(other, model, keepHandle) {}

    const std::vector<std::string>& HeatPumpAirToWaterCooling_Impl::outputVariableNames() const {
      static std::vector<std::string> result;
      if (result.empty()) {
      }
      return result;
    }

    std::vector<ScheduleTypeKey> HeatPumpAirToWaterCooling_Impl::getScheduleTypeKeys(const Schedule& schedule) const {
      std::vector<ScheduleTypeKey> result;
      const UnsignedVector fieldIndices = getSourceIndices(schedule.handle());
      if (std::find(fieldIndices.cbegin(), fieldIndices.cend(), OS_HeatPump_AirToWater_CoolingFields::AvailabilityScheduleName)
          != fieldIndices.cend()) {
        result.emplace_back("HeatPumpAirToWaterCooling", "Availability");
      }
      return result;
    }

    IddObjectType HeatPumpAirToWaterCooling_Impl::iddObjectType() const {
      return HeatPumpAirToWaterCooling::iddObjectType();
    }

    unsigned HeatPumpAirToWaterCooling_Impl::inletPort() const {
      return OS_HeatPump_AirToWater_CoolingFields::ChilledWaterInletNodeName;
    }

    unsigned HeatPumpAirToWaterCooling_Impl::outletPort() const {
      return OS_HeatPump_AirToWater_CoolingFields::ChilledWaterOutletNodeName;
    }

    bool HeatPumpAirToWaterCooling_Impl::addToNode(Node& node) {
      if (boost::optional<PlantLoop> plant = node.plantLoop()) {
        if (plant->supplyComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }

      return false;
    }

    boost::optional<HVACComponent> HeatPumpAirToWaterCooling_Impl::containingHVACComponent() const {
      auto awhp_ = heatPumpAirToWater();
      if (awhp_) {
        return std::move(*awhp_);
      }
      return boost::none;
    }

    boost::optional<HeatPumpAirToWater> HeatPumpAirToWaterCooling_Impl::heatPumpAirToWater() const {
      auto awhps = getObject<ModelObject>().getModelObjectSources<HeatPumpAirToWater>(HeatPumpAirToWater::iddObjectType());
      if (awhps.empty()) {
        return boost::none;
      }
      if (awhps.size() > 1) {
        LOG(Error, briefDescription() << " is referenced by more than one HeatPumpAirToWater, returning the first");
      }
      return awhps[0];
    }

    ModelObject HeatPumpAirToWaterCooling_Impl::clone(Model model) const {
      const bool same_model = this->model() == model;
      // This handles resetting the ports, and bypassing ParentObject::clone so it doesn't clone children
      auto t_clone = StraightComponent_Impl::clone(model).cast<HeatPumpAirToWaterCooling>();

      // Make a clean list and repopulate it, without cloning the SpeedData objects
      auto newSpeedList = ModelObjectList(model);
      newSpeedList.setName(t_clone.nameString() + " Speed Data List");
      bool ok = t_clone.getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setSpeedDataList(newSpeedList);
      OS_ASSERT(ok);

      for (const auto& speed : speeds()) {
        if (same_model) {
          ok = t_clone.addSpeed(speed);
        } else {
          auto speedClone = speed.clone(model).cast<HeatPumpAirToWaterCoolingSpeedData>();
          ok = t_clone.addSpeed(speedClone);
        }
        OS_ASSERT(ok);
      }

      return std::move(t_clone);
    }

    std::vector<ModelObject> HeatPumpAirToWaterCooling_Impl::children() const {
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

    std::vector<IdfObject> HeatPumpAirToWaterCooling_Impl::remove() {
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

    Schedule HeatPumpAirToWaterCooling_Impl::availabilitySchedule() const {
      boost::optional<Schedule> value = optionalAvailabilitySchedule();
      if (!value) {
        LOG_AND_THROW(briefDescription() << " does not have an Availability Schedule attached.");
      }
      return value.get();
    }

    double HeatPumpAirToWaterCooling_Impl::ratedInletAirTemperature() const {
      boost::optional<double> value = getDouble(OS_HeatPump_AirToWater_CoolingFields::RatedInletAirTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<double> HeatPumpAirToWaterCooling_Impl::ratedAirFlowRate() const {
      return getDouble(OS_HeatPump_AirToWater_CoolingFields::RatedAirFlowRate, true);
    }

    bool HeatPumpAirToWaterCooling_Impl::isRatedAirFlowRateAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(OS_HeatPump_AirToWater_CoolingFields::RatedAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "autosize");
      }
      return result;
    }

    double HeatPumpAirToWaterCooling_Impl::ratedLeavingWaterTemperature() const {
      boost::optional<double> value = getDouble(OS_HeatPump_AirToWater_CoolingFields::RatedLeavingWaterTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<double> HeatPumpAirToWaterCooling_Impl::ratedWaterFlowRate() const {
      return getDouble(OS_HeatPump_AirToWater_CoolingFields::RatedWaterFlowRate, true);
    }

    bool HeatPumpAirToWaterCooling_Impl::isRatedWaterFlowRateAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(OS_HeatPump_AirToWater_CoolingFields::RatedWaterFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "autosize");
      }
      return result;
    }

    double HeatPumpAirToWaterCooling_Impl::minimumOutdoorAirTemperature() const {
      boost::optional<double> value = getDouble(OS_HeatPump_AirToWater_CoolingFields::MinimumOutdoorAirTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    double HeatPumpAirToWaterCooling_Impl::maximumOutdoorAirTemperature() const {
      boost::optional<double> value = getDouble(OS_HeatPump_AirToWater_CoolingFields::MaximumOutdoorAirTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<Curve> HeatPumpAirToWaterCooling_Impl::minimumLeavingWaterTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(OS_HeatPump_AirToWater_CoolingFields::MinimumLeavingWaterTemperatureCurveName);
    }

    boost::optional<Curve> HeatPumpAirToWaterCooling_Impl::maximumLeavingWaterTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(OS_HeatPump_AirToWater_CoolingFields::MaximumLeavingWaterTemperatureCurveName);
    }

    double HeatPumpAirToWaterCooling_Impl::sizingFactor() const {
      boost::optional<double> value = getDouble(OS_HeatPump_AirToWater_CoolingFields::SizingFactor, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<HeatPumpAirToWaterCoolingSpeedData> HeatPumpAirToWaterCooling_Impl::boosterModeOnSpeed() const {
      return getObject<ModelObject>().getModelObjectTarget<HeatPumpAirToWaterCoolingSpeedData>(
        OS_HeatPump_AirToWater_CoolingFields::BoosterModeOnSpeed);
    }

    bool HeatPumpAirToWaterCooling_Impl::setAvailabilitySchedule(Schedule& availabilitySchedule) {
      const bool result = setSchedule(OS_HeatPump_AirToWater_CoolingFields::AvailabilityScheduleName, "HeatPumpAirToWaterCooling", "Availability",
                                      availabilitySchedule);
      return result;
    }

    bool HeatPumpAirToWaterCooling_Impl::setRatedInletAirTemperature(double ratedInletAirTemperature) {
      const bool result = setDouble(OS_HeatPump_AirToWater_CoolingFields::RatedInletAirTemperature, ratedInletAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HeatPumpAirToWaterCooling_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
      const bool result = setDouble(OS_HeatPump_AirToWater_CoolingFields::RatedAirFlowRate, ratedAirFlowRate);
      return result;
    }

    void HeatPumpAirToWaterCooling_Impl::autosizeRatedAirFlowRate() {
      const bool result = setString(OS_HeatPump_AirToWater_CoolingFields::RatedAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    bool HeatPumpAirToWaterCooling_Impl::setRatedLeavingWaterTemperature(double ratedLeavingWaterTemperature) {
      const bool result = setDouble(OS_HeatPump_AirToWater_CoolingFields::RatedLeavingWaterTemperature, ratedLeavingWaterTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HeatPumpAirToWaterCooling_Impl::setRatedWaterFlowRate(double ratedWaterFlowRate) {
      const bool result = setDouble(OS_HeatPump_AirToWater_CoolingFields::RatedWaterFlowRate, ratedWaterFlowRate);
      return result;
    }

    void HeatPumpAirToWaterCooling_Impl::autosizeRatedWaterFlowRate() {
      const bool result = setString(OS_HeatPump_AirToWater_CoolingFields::RatedWaterFlowRate, "autosize");
      OS_ASSERT(result);
    }

    bool HeatPumpAirToWaterCooling_Impl::setMinimumOutdoorAirTemperature(double minimumOutdoorAirTemperature) {
      const bool result = setDouble(OS_HeatPump_AirToWater_CoolingFields::MinimumOutdoorAirTemperature, minimumOutdoorAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HeatPumpAirToWaterCooling_Impl::setMaximumOutdoorAirTemperature(double maximumOutdoorAirTemperature) {
      const bool result = setDouble(OS_HeatPump_AirToWater_CoolingFields::MaximumOutdoorAirTemperature, maximumOutdoorAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    bool HeatPumpAirToWaterCooling_Impl::setMinimumLeavingWaterTemperatureCurve(const Curve& minimumLeavingWaterTemperatureCurve) {
      const bool result =
        setPointer(OS_HeatPump_AirToWater_CoolingFields::MinimumLeavingWaterTemperatureCurveName, minimumLeavingWaterTemperatureCurve.handle());
      return result;
    }

    void HeatPumpAirToWaterCooling_Impl::resetMinimumLeavingWaterTemperatureCurve() {
      const bool result = setString(OS_HeatPump_AirToWater_CoolingFields::MinimumLeavingWaterTemperatureCurveName, "");
      OS_ASSERT(result);
    }

    bool HeatPumpAirToWaterCooling_Impl::setMaximumLeavingWaterTemperatureCurve(const Curve& maximumLeavingWaterTemperatureCurve) {
      const bool result =
        setPointer(OS_HeatPump_AirToWater_CoolingFields::MaximumLeavingWaterTemperatureCurveName, maximumLeavingWaterTemperatureCurve.handle());
      return result;
    }

    void HeatPumpAirToWaterCooling_Impl::resetMaximumLeavingWaterTemperatureCurve() {
      const bool result = setString(OS_HeatPump_AirToWater_CoolingFields::MaximumLeavingWaterTemperatureCurveName, "");
      OS_ASSERT(result);
    }

    bool HeatPumpAirToWaterCooling_Impl::setSizingFactor(double sizingFactor) {
      const bool result = setDouble(OS_HeatPump_AirToWater_CoolingFields::SizingFactor, sizingFactor);
      return result;
    }

    bool HeatPumpAirToWaterCooling_Impl::setBoosterModeOnSpeed(const HeatPumpAirToWaterCoolingSpeedData& boosterModeOnSpeed) {
      const bool result = setPointer(OS_HeatPump_AirToWater_CoolingFields::BoosterModeOnSpeed, boosterModeOnSpeed.handle());
      return result;
    }

    void HeatPumpAirToWaterCooling_Impl::resetBoosterModeOnSpeed() {
      const bool result = setString(OS_HeatPump_AirToWater_CoolingFields::BoosterModeOnSpeed, "");
      OS_ASSERT(result);
    }

    boost::optional<double> HeatPumpAirToWaterCooling_Impl::autosizedRatedAirFlowRate() const {
      boost::optional<double> result;
      if (auto awhp_ = heatPumpAirToWater()) {
        result = awhp_->autosizedRatedAirFlowRateinCoolingMode();
      }
      return result;
    }

    boost::optional<double> HeatPumpAirToWaterCooling_Impl::autosizedRatedWaterFlowRate() const {
      boost::optional<double> result;
      if (auto awhp_ = heatPumpAirToWater()) {
        result = awhp_->autosizedRatedWaterFlowRateinCoolingMode();
      }
      return result;
    }

    boost::optional<double> HeatPumpAirToWaterCooling_Impl::autosizedRatedCoolingCapacity() const {
      boost::optional<double> result;
      if (auto awhp_ = heatPumpAirToWater()) {
        result = awhp_->autosizedRatedCoolingCapacity();
      }
      return result;
    }

    void HeatPumpAirToWaterCooling_Impl::autosize() {
      autosizeRatedAirFlowRate();
      autosizeRatedWaterFlowRate();
      auto speeds = this->speeds();
      if (!speeds.empty()) {
        speeds.back().autosize();  // Only need/can autosize the last (highest) speed
      }
    }

    void HeatPumpAirToWaterCooling_Impl::applySizingValues() {
      if (boost::optional<double> val_ = autosizedRatedAirFlowRate()) {
        setRatedAirFlowRate(*val_);
      }

      if (boost::optional<double> val_ = autosizedRatedWaterFlowRate()) {
        setRatedWaterFlowRate(*val_);
      }

      if (boost::optional<double> val_ = autosizedRatedCoolingCapacity()) {
        auto speeds = this->speeds();
        if (!speeds.empty()) {
          speeds.back().setRatedCoolingCapacity(*val_);  // Only need/can autosize the last (highest) speed
        }
      }
    }

    ComponentType HeatPumpAirToWaterCooling_Impl::componentType() const {
      return ComponentType::Cooling;
    }

    std::vector<FuelType> HeatPumpAirToWaterCooling_Impl::coolingFuelTypes() const {
      return {FuelType::Electricity};
    }

    std::vector<FuelType> HeatPumpAirToWaterCooling_Impl::heatingFuelTypes() const {
      return {};
    }

    std::vector<AppGFuelType> HeatPumpAirToWaterCooling_Impl::appGHeatingFuelTypes() const {
      return {};
    }

    boost::optional<Schedule> HeatPumpAirToWaterCooling_Impl::optionalAvailabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_HeatPump_AirToWater_CoolingFields::AvailabilityScheduleName);
    }

    // Speed API
    boost::optional<ModelObjectList> HeatPumpAirToWaterCooling_Impl::optionalSpeedDataList() const {
      return getObject<ModelObject>().getModelObjectTarget<ModelObjectList>(OS_HeatPump_AirToWater_CoolingFields::SpeedDataList);
    }

    ModelObjectList HeatPumpAirToWaterCooling_Impl::speedDataList() const {
      boost::optional<ModelObjectList> value = optionalSpeedDataList();
      if (!value) {
        LOG_AND_THROW(briefDescription() << " does not have a Speed Data List attached.");
      }
      return value.get();
    }

    bool HeatPumpAirToWaterCooling_Impl::setSpeedDataList(const ModelObjectList& speedDataList) {
      const bool result = setPointer(OS_HeatPump_AirToWater_CoolingFields::SpeedDataList, speedDataList.handle());
      return result;
    }

    void HeatPumpAirToWaterCooling_Impl::resetSpeedDataList() {
      bool result = setString(OS_HeatPump_AirToWater_CoolingFields::SpeedDataList, "");
      OS_ASSERT(result);
    }

    std::vector<HeatPumpAirToWaterCoolingSpeedData> HeatPumpAirToWaterCooling_Impl::speeds() const {
      std::vector<HeatPumpAirToWaterCoolingSpeedData> result;
      auto const modelObjects = speedDataList().modelObjects();

      for (auto&& elem : modelObjects) {
        auto modelObject = elem.optionalCast<HeatPumpAirToWaterCoolingSpeedData>();
        if (modelObject) {
          result.push_back(std::move(*modelObject));
        }
      }
      return result;
    }

    unsigned HeatPumpAirToWaterCooling_Impl::numberOfSpeeds() const {
      return speeds().size();  // This is right in all cases, but this is slow
      // return speedDataList().size(); // This is fast, but could be wrong if the user put non-SpeedData objects in the list or if there are blanks
    }

    boost::optional<unsigned> HeatPumpAirToWaterCooling_Impl::speedIndex(const HeatPumpAirToWaterCoolingSpeedData& speed) const {
      const auto speedVector = speeds();
      auto it = std::find_if(speedVector.cbegin(), speedVector.cend(), [&](const HeatPumpAirToWaterCoolingSpeedData& s) { return s == speed; });
      if (it != speedVector.cend()) {
        return static_cast<unsigned>(std::distance(speedVector.cbegin(), it)) + 1;  // 1-indexed
      }
      return boost::none;
    }

    bool HeatPumpAirToWaterCooling_Impl::addSpeed(const HeatPumpAirToWaterCoolingSpeedData& speed) {
      if (numberOfSpeeds() >= HeatPumpAirToWaterCooling::maximum_number_of_speeds) {
        LOG(Error, "You have reached the maximum number of speeds (=" << HeatPumpAirToWaterCooling::maximum_number_of_speeds << "), occurred for "
                                                                      << briefDescription() << ".");
        return false;  // too many speeds
      }
      if (speedIndex(speed)) {
        return false;  // already in the list
      }

      return speedDataList().addModelObject(speed);
    }

    bool HeatPumpAirToWaterCooling_Impl::setSpeedIndex(const HeatPumpAirToWaterCoolingSpeedData& speed, unsigned index) {
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

    bool HeatPumpAirToWaterCooling_Impl::addSpeed(const HeatPumpAirToWaterCoolingSpeedData& speed, unsigned index) {
      bool ok = addSpeed(speed);
      if (!ok) {
        return false;
      }
      ok = setSpeedIndex(speed, index);
      return ok;
    }

    bool HeatPumpAirToWaterCooling_Impl::setSpeeds(const std::vector<HeatPumpAirToWaterCoolingSpeedData>& speeds) {
      // Clear the extensible groups, and redo them
      bool ok = true;
      removeAllSpeeds();
      for (const auto& s : speeds) {
        ok &= addSpeed(s);
      }
      return ok;
    }

    bool HeatPumpAirToWaterCooling_Impl::removeSpeed(const HeatPumpAirToWaterCoolingSpeedData& speed) {  // NOLINT(readability-*)
      auto speedList = speedDataList();
      if (!speedList.hasModelObject(speed)) {
        LOG(Warn, "For " << briefDescription() << " cannot remove speed " << speed.briefDescription() << " since it is not part of it.");
        return false;
      }
      speedList.removeModelObject(speed);
      return true;
    }

    bool HeatPumpAirToWaterCooling_Impl::removeSpeed(unsigned index) {
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

    void HeatPumpAirToWaterCooling_Impl::removeAllSpeeds() {  // NOLINT(readability-make-member-function-const)
      speedDataList().removeAllModelObjects();                // This just clears the list, does not delete the underlying objects
    }

  }  // namespace detail

  HeatPumpAirToWaterCooling::HeatPumpAirToWaterCooling(const Model& model) : StraightComponent(HeatPumpAirToWaterCooling::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::HeatPumpAirToWaterCooling_Impl>());

    bool ok = true;

    auto speedList = ModelObjectList(model);
    speedList.setName(this->nameString() + " Speed Data List");
    ok = getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setSpeedDataList(speedList);
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

  IddObjectType HeatPumpAirToWaterCooling::iddObjectType() {
    return {IddObjectType::OS_HeatPump_AirToWater_Cooling};
  }

  Schedule HeatPumpAirToWaterCooling::availabilitySchedule() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->availabilitySchedule();
  }

  double HeatPumpAirToWaterCooling::ratedInletAirTemperature() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->ratedInletAirTemperature();
  }

  boost::optional<double> HeatPumpAirToWaterCooling::ratedAirFlowRate() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->ratedAirFlowRate();
  }

  bool HeatPumpAirToWaterCooling::isRatedAirFlowRateAutosized() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->isRatedAirFlowRateAutosized();
  }

  boost::optional<double> HeatPumpAirToWaterCooling::autosizedRatedAirFlowRate() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->autosizedRatedAirFlowRate();
  }

  double HeatPumpAirToWaterCooling::ratedLeavingWaterTemperature() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->ratedLeavingWaterTemperature();
  }

  boost::optional<double> HeatPumpAirToWaterCooling::ratedWaterFlowRate() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->ratedWaterFlowRate();
  }

  bool HeatPumpAirToWaterCooling::isRatedWaterFlowRateAutosized() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->isRatedWaterFlowRateAutosized();
  }

  boost::optional<double> HeatPumpAirToWaterCooling::autosizedRatedWaterFlowRate() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->autosizedRatedWaterFlowRate();
  }

  double HeatPumpAirToWaterCooling::minimumOutdoorAirTemperature() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->minimumOutdoorAirTemperature();
  }

  double HeatPumpAirToWaterCooling::maximumOutdoorAirTemperature() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->maximumOutdoorAirTemperature();
  }

  boost::optional<Curve> HeatPumpAirToWaterCooling::minimumLeavingWaterTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->minimumLeavingWaterTemperatureCurve();
  }

  boost::optional<Curve> HeatPumpAirToWaterCooling::maximumLeavingWaterTemperatureCurve() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->maximumLeavingWaterTemperatureCurve();
  }

  double HeatPumpAirToWaterCooling::sizingFactor() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->sizingFactor();
  }

  boost::optional<HeatPumpAirToWaterCoolingSpeedData> HeatPumpAirToWaterCooling::boosterModeOnSpeed() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->boosterModeOnSpeed();
  }

  bool HeatPumpAirToWaterCooling::setAvailabilitySchedule(Schedule& availabilitySchedule) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setAvailabilitySchedule(availabilitySchedule);
  }

  bool HeatPumpAirToWaterCooling::setRatedInletAirTemperature(double ratedInletAirTemperature) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setRatedInletAirTemperature(ratedInletAirTemperature);
  }

  bool HeatPumpAirToWaterCooling::setRatedAirFlowRate(double ratedAirFlowRate) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
  }

  void HeatPumpAirToWaterCooling::autosizeRatedAirFlowRate() {
    getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->autosizeRatedAirFlowRate();
  }

  bool HeatPumpAirToWaterCooling::setRatedLeavingWaterTemperature(double ratedLeavingWaterTemperature) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setRatedLeavingWaterTemperature(ratedLeavingWaterTemperature);
  }

  bool HeatPumpAirToWaterCooling::setRatedWaterFlowRate(double ratedWaterFlowRate) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setRatedWaterFlowRate(ratedWaterFlowRate);
  }

  void HeatPumpAirToWaterCooling::autosizeRatedWaterFlowRate() {
    getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->autosizeRatedWaterFlowRate();
  }

  bool HeatPumpAirToWaterCooling::setMinimumOutdoorAirTemperature(double minimumOutdoorAirTemperature) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setMinimumOutdoorAirTemperature(minimumOutdoorAirTemperature);
  }

  bool HeatPumpAirToWaterCooling::setMaximumOutdoorAirTemperature(double maximumOutdoorAirTemperature) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setMaximumOutdoorAirTemperature(maximumOutdoorAirTemperature);
  }

  bool HeatPumpAirToWaterCooling::setMinimumLeavingWaterTemperatureCurve(const Curve& minimumLeavingWaterTemperatureCurve) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setMinimumLeavingWaterTemperatureCurve(minimumLeavingWaterTemperatureCurve);
  }

  void HeatPumpAirToWaterCooling::resetMinimumLeavingWaterTemperatureCurve() {
    getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->resetMinimumLeavingWaterTemperatureCurve();
  }

  bool HeatPumpAirToWaterCooling::setMaximumLeavingWaterTemperatureCurve(const Curve& maximumLeavingWaterTemperatureCurve) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setMaximumLeavingWaterTemperatureCurve(maximumLeavingWaterTemperatureCurve);
  }

  void HeatPumpAirToWaterCooling::resetMaximumLeavingWaterTemperatureCurve() {
    getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->resetMaximumLeavingWaterTemperatureCurve();
  }

  bool HeatPumpAirToWaterCooling::setSizingFactor(double sizingFactor) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setSizingFactor(sizingFactor);
  }

  bool HeatPumpAirToWaterCooling::setBoosterModeOnSpeed(const HeatPumpAirToWaterCoolingSpeedData& boosterModeOnSpeed) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setBoosterModeOnSpeed(boosterModeOnSpeed);
  }

  void HeatPumpAirToWaterCooling::resetBoosterModeOnSpeed() {
    getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->resetBoosterModeOnSpeed();
  }

  // Speed Data API
  unsigned HeatPumpAirToWaterCooling::numberOfSpeeds() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->numberOfSpeeds();
  }

  boost::optional<unsigned> HeatPumpAirToWaterCooling::speedIndex(const HeatPumpAirToWaterCoolingSpeedData& speed) const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->speedIndex(speed);
  }

  std::vector<HeatPumpAirToWaterCoolingSpeedData> HeatPumpAirToWaterCooling::speeds() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->speeds();
  }

  bool HeatPumpAirToWaterCooling::addSpeed(const HeatPumpAirToWaterCoolingSpeedData& speed) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->addSpeed(speed);
  }

  bool HeatPumpAirToWaterCooling::addSpeed(const HeatPumpAirToWaterCoolingSpeedData& speed, unsigned index) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->addSpeed(speed, index);
  }

  bool HeatPumpAirToWaterCooling::setSpeedIndex(const HeatPumpAirToWaterCoolingSpeedData& speed, unsigned index) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setSpeedIndex(speed, index);
  }

  bool HeatPumpAirToWaterCooling::setSpeeds(const std::vector<HeatPumpAirToWaterCoolingSpeedData>& speeds) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->setSpeeds(speeds);
  }

  void HeatPumpAirToWaterCooling::removeAllSpeeds() {
    getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->removeAllSpeeds();
  }

  bool HeatPumpAirToWaterCooling::removeSpeed(const HeatPumpAirToWaterCoolingSpeedData& speed) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->removeSpeed(speed);
  }

  bool HeatPumpAirToWaterCooling::removeSpeed(unsigned index) {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->removeSpeed(index);
  }

  boost::optional<HeatPumpAirToWater> HeatPumpAirToWaterCooling::heatPumpAirToWater() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->heatPumpAirToWater();
  }

  boost::optional<double> HeatPumpAirToWaterCooling::autosizedRatedCoolingCapacity() const {
    return getImpl<detail::HeatPumpAirToWaterCooling_Impl>()->autosizedRatedCoolingCapacity();
  }

  /// @cond
  HeatPumpAirToWaterCooling::HeatPumpAirToWaterCooling(std::shared_ptr<detail::HeatPumpAirToWaterCooling_Impl> impl)
    : StraightComponent(std::move(impl)) {}
  /// @endcond

}  // namespace model
}  // namespace openstudio
