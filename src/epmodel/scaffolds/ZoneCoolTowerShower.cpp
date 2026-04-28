/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZoneCoolTowerShower.hpp"
#include "ZoneCoolTowerShower_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneCoolTower_Shower_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneCoolTowerShower::ZoneCoolTowerShower(const Model& model) : ModelObject(ZoneCoolTowerShower::iddObjectType(), model) {
    OS_ASSERT(setMaximumWaterFlowRate(0.01));
    OS_ASSERT(setEffectiveTowerHeight(10.0));
    OS_ASSERT(setAirflowOutletArea(1.0));
    OS_ASSERT(setMaximumAirFlowRate(0.5));
    OS_ASSERT(setMinimumIndoorTemperature(20.0));
    OS_ASSERT(setFlowControlType("WindDrivenFlow"));
    OS_ASSERT(setRatedPowerConsumption(1200.0));
  }

  ZoneCoolTowerShower::ZoneCoolTowerShower(std::shared_ptr<detail::ZoneCoolTowerShower_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneCoolTowerShower::iddObjectType() {
    return IddObjectType::ZoneCoolTower_Shower;
  }

  std::vector<std::string> ZoneCoolTowerShower::flowControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneCoolTower_ShowerFields::FlowControlType);
  }

  std::string ZoneCoolTowerShower::flowControlType() const {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->flowControlType();
  }

  bool ZoneCoolTowerShower::setFlowControlType(const std::string& flowControlType) {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->setFlowControlType(flowControlType);
  }

  bool ZoneCoolTowerShower::isFlowControlTypeDefaulted() const {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->isFlowControlTypeDefaulted();
  }

  void ZoneCoolTowerShower::resetFlowControlType() {
    getImpl<detail::ZoneCoolTowerShower_Impl>()->resetFlowControlType();
  }

  double ZoneCoolTowerShower::maximumWaterFlowRate() const {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->maximumWaterFlowRate();
  }

  bool ZoneCoolTowerShower::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->setMaximumWaterFlowRate(maximumWaterFlowRate);
  }

  double ZoneCoolTowerShower::effectiveTowerHeight() const {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->effectiveTowerHeight();
  }

  bool ZoneCoolTowerShower::setEffectiveTowerHeight(double effectiveTowerHeight) {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->setEffectiveTowerHeight(effectiveTowerHeight);
  }

  double ZoneCoolTowerShower::airflowOutletArea() const {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->airflowOutletArea();
  }

  bool ZoneCoolTowerShower::setAirflowOutletArea(double airflowOutletArea) {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->setAirflowOutletArea(airflowOutletArea);
  }

  double ZoneCoolTowerShower::maximumAirFlowRate() const {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->maximumAirFlowRate();
  }

  bool ZoneCoolTowerShower::setMaximumAirFlowRate(double maximumAirFlowRate) {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
  }

  double ZoneCoolTowerShower::minimumIndoorTemperature() const {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->minimumIndoorTemperature();
  }

  bool ZoneCoolTowerShower::setMinimumIndoorTemperature(double minimumIndoorTemperature) {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->setMinimumIndoorTemperature(minimumIndoorTemperature);
  }

  boost::optional<double> ZoneCoolTowerShower::fractionofWaterLoss() const {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->fractionofWaterLoss();
  }

  bool ZoneCoolTowerShower::setFractionofWaterLoss(double fractionofWaterLoss) {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->setFractionofWaterLoss(fractionofWaterLoss);
  }

  bool ZoneCoolTowerShower::isFractionofWaterLossDefaulted() const {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->isFractionofWaterLossDefaulted();
  }

  void ZoneCoolTowerShower::resetFractionofWaterLoss() {
    getImpl<detail::ZoneCoolTowerShower_Impl>()->resetFractionofWaterLoss();
  }

  boost::optional<double> ZoneCoolTowerShower::fractionofFlowSchedule() const {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->fractionofFlowSchedule();
  }

  bool ZoneCoolTowerShower::setFractionofFlowSchedule(double fractionofFlowSchedule) {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->setFractionofFlowSchedule(fractionofFlowSchedule);
  }

  bool ZoneCoolTowerShower::isFractionofFlowScheduleDefaulted() const {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->isFractionofFlowScheduleDefaulted();
  }

  void ZoneCoolTowerShower::resetFractionofFlowSchedule() {
    getImpl<detail::ZoneCoolTowerShower_Impl>()->resetFractionofFlowSchedule();
  }

  double ZoneCoolTowerShower::ratedPowerConsumption() const {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->ratedPowerConsumption();
  }

  bool ZoneCoolTowerShower::setRatedPowerConsumption(double ratedPowerConsumption) {
    return getImpl<detail::ZoneCoolTowerShower_Impl>()->setRatedPowerConsumption(ratedPowerConsumption);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string ZoneCoolTowerShower_Impl::flowControlType() const {
      const auto value = getString(openstudio::ZoneCoolTower_ShowerFields::FlowControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneCoolTowerShower_Impl::isFlowControlTypeDefaulted() const {
      return isEmpty(openstudio::ZoneCoolTower_ShowerFields::FlowControlType);
    }

    bool ZoneCoolTowerShower_Impl::setFlowControlType(const std::string& flowControlType) {
      return setString(openstudio::ZoneCoolTower_ShowerFields::FlowControlType, flowControlType);
    }

    void ZoneCoolTowerShower_Impl::resetFlowControlType() {
      OS_ASSERT(setString(openstudio::ZoneCoolTower_ShowerFields::FlowControlType, ""));
    }

    double ZoneCoolTowerShower_Impl::maximumWaterFlowRate() const {
      const auto value = getDouble(openstudio::ZoneCoolTower_ShowerFields::MaximumWaterFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneCoolTowerShower_Impl::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
      const bool result = setDouble(openstudio::ZoneCoolTower_ShowerFields::MaximumWaterFlowRate, maximumWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    double ZoneCoolTowerShower_Impl::effectiveTowerHeight() const {
      const auto value = getDouble(openstudio::ZoneCoolTower_ShowerFields::EffectiveTowerHeight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneCoolTowerShower_Impl::setEffectiveTowerHeight(double effectiveTowerHeight) {
      const bool result = setDouble(openstudio::ZoneCoolTower_ShowerFields::EffectiveTowerHeight, effectiveTowerHeight);
      OS_ASSERT(result);
      return result;
    }

    double ZoneCoolTowerShower_Impl::airflowOutletArea() const {
      const auto value = getDouble(openstudio::ZoneCoolTower_ShowerFields::AirflowOutletArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneCoolTowerShower_Impl::setAirflowOutletArea(double airflowOutletArea) {
      const bool result = setDouble(openstudio::ZoneCoolTower_ShowerFields::AirflowOutletArea, airflowOutletArea);
      OS_ASSERT(result);
      return result;
    }

    double ZoneCoolTowerShower_Impl::maximumAirFlowRate() const {
      const auto value = getDouble(openstudio::ZoneCoolTower_ShowerFields::MaximumAirFlowRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneCoolTowerShower_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
      return setDouble(openstudio::ZoneCoolTower_ShowerFields::MaximumAirFlowRate, maximumAirFlowRate);
    }

    double ZoneCoolTowerShower_Impl::minimumIndoorTemperature() const {
      const auto value = getDouble(openstudio::ZoneCoolTower_ShowerFields::MinimumIndoorTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneCoolTowerShower_Impl::setMinimumIndoorTemperature(double minimumIndoorTemperature) {
      return setDouble(openstudio::ZoneCoolTower_ShowerFields::MinimumIndoorTemperature, minimumIndoorTemperature);
    }

    boost::optional<double> ZoneCoolTowerShower_Impl::fractionofWaterLoss() const {
      return getDouble(openstudio::ZoneCoolTower_ShowerFields::FractionofWaterLoss, true);
    }

    bool ZoneCoolTowerShower_Impl::setFractionofWaterLoss(double fractionofWaterLoss) {
      return setDouble(openstudio::ZoneCoolTower_ShowerFields::FractionofWaterLoss, fractionofWaterLoss);
    }

    bool ZoneCoolTowerShower_Impl::isFractionofWaterLossDefaulted() const {
      return isEmpty(openstudio::ZoneCoolTower_ShowerFields::FractionofWaterLoss);
    }

    void ZoneCoolTowerShower_Impl::resetFractionofWaterLoss() {
      OS_ASSERT(setString(openstudio::ZoneCoolTower_ShowerFields::FractionofWaterLoss, ""));
    }

    boost::optional<double> ZoneCoolTowerShower_Impl::fractionofFlowSchedule() const {
      return getDouble(openstudio::ZoneCoolTower_ShowerFields::FractionofFlowSchedule, true);
    }

    bool ZoneCoolTowerShower_Impl::setFractionofFlowSchedule(double fractionofFlowSchedule) {
      return setDouble(openstudio::ZoneCoolTower_ShowerFields::FractionofFlowSchedule, fractionofFlowSchedule);
    }

    bool ZoneCoolTowerShower_Impl::isFractionofFlowScheduleDefaulted() const {
      return isEmpty(openstudio::ZoneCoolTower_ShowerFields::FractionofFlowSchedule);
    }

    void ZoneCoolTowerShower_Impl::resetFractionofFlowSchedule() {
      OS_ASSERT(setString(openstudio::ZoneCoolTower_ShowerFields::FractionofFlowSchedule, ""));
    }

    double ZoneCoolTowerShower_Impl::ratedPowerConsumption() const {
      const auto value = getDouble(openstudio::ZoneCoolTower_ShowerFields::RatedPowerConsumption, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneCoolTowerShower_Impl::setRatedPowerConsumption(double ratedPowerConsumption) {
      const bool result = setDouble(openstudio::ZoneCoolTower_ShowerFields::RatedPowerConsumption, ratedPowerConsumption);
      OS_ASSERT(result);
      return result;
    }

    std::vector<std::string> ZoneCoolTowerShower_Impl::flowControlTypeValues() const {
      return openstudio::epmodel::ZoneCoolTowerShower::flowControlTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
