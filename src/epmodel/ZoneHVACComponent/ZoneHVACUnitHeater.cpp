/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACUnitHeater.hpp"
#include "ZoneHVACComponent/ZoneHVACUnitHeater_Impl.hpp"

#include "Model.hpp"

#include <boost/none.hpp>

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_UnitHeater_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACUnitHeater::ZoneHVACUnitHeater(const Model& model) : ModelObject(ZoneHVACUnitHeater::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACUnitHeater_Impl>());

    autosizeMaximumSupplyAirFlowRate();
    OS_ASSERT(setFanControlType("No"));
    autosizeMaximumHotWaterFlowRate();
    OS_ASSERT(setMinimumHotWaterFlowRate(0.0));
    OS_ASSERT(setHeatingConvergenceTolerance(0.001));
  }

  ZoneHVACUnitHeater::ZoneHVACUnitHeater(std::shared_ptr<detail::ZoneHVACUnitHeater_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACUnitHeater::iddObjectType() {
    return IddObjectType::ZoneHVAC_UnitHeater;
  }

  std::vector<std::string> ZoneHVACUnitHeater::fanControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_UnitHeaterFields::SupplyAirFanOperationDuringNoHeating);
  }

  boost::optional<double> ZoneHVACUnitHeater::maximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->maximumSupplyAirFlowRate();
  }

  bool ZoneHVACUnitHeater::isMaximumSupplyAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->isMaximumSupplyAirFlowRateAutosized();
  }

  std::string ZoneHVACUnitHeater::fanControlType() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->fanControlType();
  }

  boost::optional<double> ZoneHVACUnitHeater::maximumHotWaterFlowRate() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->maximumHotWaterFlowRate();
  }

  bool ZoneHVACUnitHeater::isMaximumHotWaterFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->isMaximumHotWaterFlowRateAutosized();
  }

  double ZoneHVACUnitHeater::minimumHotWaterFlowRate() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->minimumHotWaterFlowRate();
  }

  bool ZoneHVACUnitHeater::isMinimumHotWaterFlowRateDefaulted() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->isMinimumHotWaterFlowRateDefaulted();
  }

  double ZoneHVACUnitHeater::heatingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->heatingConvergenceTolerance();
  }

  bool ZoneHVACUnitHeater::isHeatingConvergenceToleranceDefaulted() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->isHeatingConvergenceToleranceDefaulted();
  }

  bool ZoneHVACUnitHeater::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->setMaximumSupplyAirFlowRate(maximumSupplyAirFlowRate);
  }

  void ZoneHVACUnitHeater::autosizeMaximumSupplyAirFlowRate() {
    getImpl<detail::ZoneHVACUnitHeater_Impl>()->autosizeMaximumSupplyAirFlowRate();
  }

  bool ZoneHVACUnitHeater::setFanControlType(const std::string& fanControlType) {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->setFanControlType(fanControlType);
  }

  bool ZoneHVACUnitHeater::setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate) {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->setMaximumHotWaterFlowRate(maximumHotWaterFlowRate);
  }

  void ZoneHVACUnitHeater::resetMaximumHotWaterFlowRate() {
    getImpl<detail::ZoneHVACUnitHeater_Impl>()->resetMaximumHotWaterFlowRate();
  }

  void ZoneHVACUnitHeater::autosizeMaximumHotWaterFlowRate() {
    getImpl<detail::ZoneHVACUnitHeater_Impl>()->autosizeMaximumHotWaterFlowRate();
  }

  bool ZoneHVACUnitHeater::setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate) {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->setMinimumHotWaterFlowRate(minimumHotWaterFlowRate);
  }

  void ZoneHVACUnitHeater::resetMinimumHotWaterFlowRate() {
    getImpl<detail::ZoneHVACUnitHeater_Impl>()->resetMinimumHotWaterFlowRate();
  }

  bool ZoneHVACUnitHeater::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->setHeatingConvergenceTolerance(heatingConvergenceTolerance);
  }

  void ZoneHVACUnitHeater::resetHeatingConvergenceTolerance() {
    getImpl<detail::ZoneHVACUnitHeater_Impl>()->resetHeatingConvergenceTolerance();
  }

  boost::optional<double> ZoneHVACUnitHeater::autosizedMaximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->autosizedMaximumSupplyAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitHeater::autosizedMaximumHotWaterFlowRate() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->autosizedMaximumHotWaterFlowRate();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ZoneHVACUnitHeater_Impl::maximumSupplyAirFlowRate() const {
      return getDouble(ZoneHVAC_UnitHeaterFields::MaximumSupplyAirFlowRate, true);
    }

    bool ZoneHVACUnitHeater_Impl::isMaximumSupplyAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_UnitHeaterFields::MaximumSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACUnitHeater_Impl::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitHeaterFields::MaximumSupplyAirFlowRate, maximumSupplyAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitHeater_Impl::autosizeMaximumSupplyAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitHeaterFields::MaximumSupplyAirFlowRate, "autosize"));
    }

    std::string ZoneHVACUnitHeater_Impl::fanControlType() const {
      auto value = getString(ZoneHVAC_UnitHeaterFields::SupplyAirFanOperationDuringNoHeating, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitHeater_Impl::setFanControlType(const std::string& fanControlType) {
      const bool result = setString(ZoneHVAC_UnitHeaterFields::SupplyAirFanOperationDuringNoHeating, fanControlType);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACUnitHeater_Impl::maximumHotWaterFlowRate() const {
      return getDouble(ZoneHVAC_UnitHeaterFields::MaximumHotWaterorSteamFlowRate, true);
    }

    bool ZoneHVACUnitHeater_Impl::isMaximumHotWaterFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_UnitHeaterFields::MaximumHotWaterorSteamFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACUnitHeater_Impl::setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitHeaterFields::MaximumHotWaterorSteamFlowRate, maximumHotWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitHeater_Impl::resetMaximumHotWaterFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitHeaterFields::MaximumHotWaterorSteamFlowRate, ""));
    }

    void ZoneHVACUnitHeater_Impl::autosizeMaximumHotWaterFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitHeaterFields::MaximumHotWaterorSteamFlowRate, "autosize"));
    }

    double ZoneHVACUnitHeater_Impl::minimumHotWaterFlowRate() const {
      auto value = getDouble(ZoneHVAC_UnitHeaterFields::MinimumHotWaterorSteamFlowRate, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitHeater_Impl::isMinimumHotWaterFlowRateDefaulted() const {
      return isEmpty(ZoneHVAC_UnitHeaterFields::MinimumHotWaterorSteamFlowRate);
    }

    bool ZoneHVACUnitHeater_Impl::setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitHeaterFields::MinimumHotWaterorSteamFlowRate, minimumHotWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitHeater_Impl::resetMinimumHotWaterFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitHeaterFields::MinimumHotWaterorSteamFlowRate, ""));
    }

    double ZoneHVACUnitHeater_Impl::heatingConvergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_UnitHeaterFields::HeatingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitHeater_Impl::isHeatingConvergenceToleranceDefaulted() const {
      return isEmpty(ZoneHVAC_UnitHeaterFields::HeatingConvergenceTolerance);
    }

    bool ZoneHVACUnitHeater_Impl::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
      const bool result = setDouble(ZoneHVAC_UnitHeaterFields::HeatingConvergenceTolerance, heatingConvergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitHeater_Impl::resetHeatingConvergenceTolerance() {
      OS_ASSERT(setString(ZoneHVAC_UnitHeaterFields::HeatingConvergenceTolerance, ""));
    }

    boost::optional<double> ZoneHVACUnitHeater_Impl::autosizedMaximumSupplyAirFlowRate() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACUnitHeater_Impl::autosizedMaximumHotWaterFlowRate() const {
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
