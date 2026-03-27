/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACUnitVentilator.hpp"
#include "ZoneHVACComponent/ZoneHVACUnitVentilator_Impl.hpp"

#include "Model.hpp"

#include <boost/none.hpp>

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_UnitVentilator_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACUnitVentilator::ZoneHVACUnitVentilator(const Model& model) : ZoneHVACComponent(ZoneHVACUnitVentilator::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACUnitVentilator_Impl>());

    OS_ASSERT(setOutdoorAirControlType("VariablePercent"));
    autosizeMaximumSupplyAirFlowRate();
    autosizeMinimumOutdoorAirFlowRate();
    autosizeMaximumOutdoorAirFlowRate();
    OS_ASSERT(setHeatingConvergenceTolerance(0.001));
    OS_ASSERT(setCoolingConvergenceTolerance(0.001));
  }

  ZoneHVACUnitVentilator::ZoneHVACUnitVentilator(std::shared_ptr<detail::ZoneHVACUnitVentilator_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACUnitVentilator::iddObjectType() {
    return IddObjectType::ZoneHVAC_UnitVentilator;
  }

  std::vector<std::string> ZoneHVACUnitVentilator::outdoorAirControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_UnitVentilatorFields::OutdoorAirControlType);
  }

  boost::optional<double> ZoneHVACUnitVentilator::maximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->maximumSupplyAirFlowRate();
  }

  bool ZoneHVACUnitVentilator::isMaximumSupplyAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->isMaximumSupplyAirFlowRateAutosized();
  }

  bool ZoneHVACUnitVentilator::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setMaximumSupplyAirFlowRate(maximumSupplyAirFlowRate);
  }

  void ZoneHVACUnitVentilator::autosizeMaximumSupplyAirFlowRate() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizeMaximumSupplyAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitVentilator::autosizedMaximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizedMaximumSupplyAirFlowRate();
  }

  std::string ZoneHVACUnitVentilator::outdoorAirControlType() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->outdoorAirControlType();
  }

  bool ZoneHVACUnitVentilator::setOutdoorAirControlType(const std::string& outdoorAirControlType) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setOutdoorAirControlType(outdoorAirControlType);
  }

  boost::optional<double> ZoneHVACUnitVentilator::minimumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->minimumOutdoorAirFlowRate();
  }

  bool ZoneHVACUnitVentilator::isMinimumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->isMinimumOutdoorAirFlowRateAutosized();
  }

  bool ZoneHVACUnitVentilator::setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setMinimumOutdoorAirFlowRate(minimumOutdoorAirFlowRate);
  }

  void ZoneHVACUnitVentilator::autosizeMinimumOutdoorAirFlowRate() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizeMinimumOutdoorAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitVentilator::autosizedMinimumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizedMinimumOutdoorAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitVentilator::maximumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->maximumOutdoorAirFlowRate();
  }

  bool ZoneHVACUnitVentilator::isMaximumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->isMaximumOutdoorAirFlowRateAutosized();
  }

  bool ZoneHVACUnitVentilator::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setMaximumOutdoorAirFlowRate(maximumOutdoorAirFlowRate);
  }

  void ZoneHVACUnitVentilator::autosizeMaximumOutdoorAirFlowRate() {
    getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizeMaximumOutdoorAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitVentilator::autosizedMaximumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->autosizedMaximumOutdoorAirFlowRate();
  }

  double ZoneHVACUnitVentilator::heatingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->heatingConvergenceTolerance();
  }

  bool ZoneHVACUnitVentilator::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setHeatingConvergenceTolerance(heatingConvergenceTolerance);
  }

  double ZoneHVACUnitVentilator::coolingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->coolingConvergenceTolerance();
  }

  bool ZoneHVACUnitVentilator::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACUnitVentilator_Impl>()->setCoolingConvergenceTolerance(coolingConvergenceTolerance);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ZoneHVACUnitVentilator_Impl::maximumSupplyAirFlowRate() const {
      return getDouble(ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, true);
    }

    bool ZoneHVACUnitVentilator_Impl::isMaximumSupplyAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACUnitVentilator_Impl::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, maximumSupplyAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitVentilator_Impl::autosizeMaximumSupplyAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, "autosize"));
    }

    std::string ZoneHVACUnitVentilator_Impl::outdoorAirControlType() const {
      auto value = getString(ZoneHVAC_UnitVentilatorFields::OutdoorAirControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitVentilator_Impl::setOutdoorAirControlType(const std::string& outdoorAirControlType) {
      const bool result = setString(ZoneHVAC_UnitVentilatorFields::OutdoorAirControlType, outdoorAirControlType);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::minimumOutdoorAirFlowRate() const {
      return getDouble(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, true);
    }

    bool ZoneHVACUnitVentilator_Impl::isMinimumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACUnitVentilator_Impl::setMinimumOutdoorAirFlowRate(double minimumOutdoorAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, minimumOutdoorAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitVentilator_Impl::autosizeMinimumOutdoorAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, "autosize"));
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::maximumOutdoorAirFlowRate() const {
      return getDouble(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, true);
    }

    bool ZoneHVACUnitVentilator_Impl::isMaximumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACUnitVentilator_Impl::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, maximumOutdoorAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitVentilator_Impl::autosizeMaximumOutdoorAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, "autosize"));
    }

    double ZoneHVACUnitVentilator_Impl::heatingConvergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_UnitVentilatorFields::HeatingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitVentilator_Impl::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::HeatingConvergenceTolerance, heatingConvergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACUnitVentilator_Impl::coolingConvergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_UnitVentilatorFields::CoolingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitVentilator_Impl::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
      const bool result = setDouble(ZoneHVAC_UnitVentilatorFields::CoolingConvergenceTolerance, coolingConvergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::autosizedMaximumSupplyAirFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::autosizedMinimumOutdoorAirFlowRate() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACUnitVentilator_Impl::autosizedMaximumOutdoorAirFlowRate() const {
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
