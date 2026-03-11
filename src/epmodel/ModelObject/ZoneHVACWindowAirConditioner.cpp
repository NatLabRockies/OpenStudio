/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACWindowAirConditioner.hpp"
#include "ZoneHVACWindowAirConditioner_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/ZoneHVAC_WindowAirConditioner_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACWindowAirConditioner::ZoneHVACWindowAirConditioner(const Model& model)
    : ModelObject(ZoneHVACWindowAirConditioner::iddObjectType(), model) {}

  ZoneHVACWindowAirConditioner::ZoneHVACWindowAirConditioner(std::shared_ptr<detail::ZoneHVACWindowAirConditioner_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACWindowAirConditioner::iddObjectType() {
    return IddObjectType::ZoneHVAC_WindowAirConditioner;
  }

  std::vector<std::string> ZoneHVACWindowAirConditioner::outdoorAirMixerObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneHVAC_WindowAirConditionerFields::OutdoorAirMixerObjectType);
  }

  std::vector<std::string> ZoneHVACWindowAirConditioner::supplyAirFanObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneHVAC_WindowAirConditionerFields::SupplyAirFanObjectType);
  }

  std::vector<std::string> ZoneHVACWindowAirConditioner::coolingCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneHVAC_WindowAirConditionerFields::CoolingCoilObjectType);
  }

  std::vector<std::string> ZoneHVACWindowAirConditioner::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_WindowAirConditionerFields::FanPlacement);
  }

  boost::optional<double> ZoneHVACWindowAirConditioner::maximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->maximumSupplyAirFlowRate();
  }

  bool ZoneHVACWindowAirConditioner::isMaximumSupplyAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->isMaximumSupplyAirFlowRateAutosized();
  }

  bool ZoneHVACWindowAirConditioner::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->setMaximumSupplyAirFlowRate(maximumSupplyAirFlowRate);
  }

  void ZoneHVACWindowAirConditioner::autosizeMaximumSupplyAirFlowRate() {
    getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->autosizeMaximumSupplyAirFlowRate();
  }

  boost::optional<double> ZoneHVACWindowAirConditioner::autosizedMaximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->autosizedMaximumSupplyAirFlowRate();
  }

  boost::optional<double> ZoneHVACWindowAirConditioner::maximumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->maximumOutdoorAirFlowRate();
  }

  bool ZoneHVACWindowAirConditioner::isMaximumOutdoorAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->isMaximumOutdoorAirFlowRateAutosized();
  }

  bool ZoneHVACWindowAirConditioner::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->setMaximumOutdoorAirFlowRate(maximumOutdoorAirFlowRate);
  }

  void ZoneHVACWindowAirConditioner::autosizeMaximumOutdoorAirFlowRate() {
    getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->autosizeMaximumOutdoorAirFlowRate();
  }

  boost::optional<double> ZoneHVACWindowAirConditioner::autosizedMaximumOutdoorAirFlowRate() const {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->autosizedMaximumOutdoorAirFlowRate();
  }

  std::string ZoneHVACWindowAirConditioner::outdoorAirMixerObjectType() const {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->outdoorAirMixerObjectType();
  }

  bool ZoneHVACWindowAirConditioner::setOutdoorAirMixerObjectType(const std::string& outdoorAirMixerObjectType) {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->setOutdoorAirMixerObjectType(outdoorAirMixerObjectType);
  }

  std::string ZoneHVACWindowAirConditioner::supplyAirFanObjectType() const {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->supplyAirFanObjectType();
  }

  bool ZoneHVACWindowAirConditioner::setSupplyAirFanObjectType(const std::string& supplyAirFanObjectType) {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->setSupplyAirFanObjectType(supplyAirFanObjectType);
  }

  std::string ZoneHVACWindowAirConditioner::coolingCoilObjectType() const {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->coolingCoilObjectType();
  }

  bool ZoneHVACWindowAirConditioner::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->setCoolingCoilObjectType(coolingCoilObjectType);
  }

  std::string ZoneHVACWindowAirConditioner::fanPlacement() const {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->fanPlacement();
  }

  bool ZoneHVACWindowAirConditioner::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::ZoneHVACWindowAirConditioner_Impl>()->setFanPlacement(fanPlacement);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ZoneHVACWindowAirConditioner_Impl::maximumSupplyAirFlowRate() const {
      return getDouble(openstudio::ZoneHVAC_WindowAirConditionerFields::MaximumSupplyAirFlowRate, true);
    }

    bool ZoneHVACWindowAirConditioner_Impl::isMaximumSupplyAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::ZoneHVAC_WindowAirConditionerFields::MaximumSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ZoneHVACWindowAirConditioner_Impl::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
      const bool result = setDouble(openstudio::ZoneHVAC_WindowAirConditionerFields::MaximumSupplyAirFlowRate, maximumSupplyAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWindowAirConditioner_Impl::autosizeMaximumSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_WindowAirConditionerFields::MaximumSupplyAirFlowRate, "autosize"));
    }

    boost::optional<double> ZoneHVACWindowAirConditioner_Impl::autosizedMaximumSupplyAirFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::optional<double>();
    }

    boost::optional<double> ZoneHVACWindowAirConditioner_Impl::maximumOutdoorAirFlowRate() const {
      return getDouble(openstudio::ZoneHVAC_WindowAirConditionerFields::MaximumOutdoorAirFlowRate, true);
    }

    bool ZoneHVACWindowAirConditioner_Impl::isMaximumOutdoorAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::ZoneHVAC_WindowAirConditionerFields::MaximumOutdoorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool ZoneHVACWindowAirConditioner_Impl::setMaximumOutdoorAirFlowRate(double maximumOutdoorAirFlowRate) {
      const bool result = setDouble(openstudio::ZoneHVAC_WindowAirConditionerFields::MaximumOutdoorAirFlowRate, maximumOutdoorAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWindowAirConditioner_Impl::autosizeMaximumOutdoorAirFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_WindowAirConditionerFields::MaximumOutdoorAirFlowRate, "autosize"));
    }

    boost::optional<double> ZoneHVACWindowAirConditioner_Impl::autosizedMaximumOutdoorAirFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::optional<double>();
    }

    std::string ZoneHVACWindowAirConditioner_Impl::outdoorAirMixerObjectType() const {
      const auto value = getString(openstudio::ZoneHVAC_WindowAirConditionerFields::OutdoorAirMixerObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACWindowAirConditioner_Impl::setOutdoorAirMixerObjectType(const std::string& outdoorAirMixerObjectType) {
      return setString(openstudio::ZoneHVAC_WindowAirConditionerFields::OutdoorAirMixerObjectType, outdoorAirMixerObjectType);
    }

    std::string ZoneHVACWindowAirConditioner_Impl::supplyAirFanObjectType() const {
      const auto value = getString(openstudio::ZoneHVAC_WindowAirConditionerFields::SupplyAirFanObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACWindowAirConditioner_Impl::setSupplyAirFanObjectType(const std::string& supplyAirFanObjectType) {
      return setString(openstudio::ZoneHVAC_WindowAirConditionerFields::SupplyAirFanObjectType, supplyAirFanObjectType);
    }

    std::string ZoneHVACWindowAirConditioner_Impl::coolingCoilObjectType() const {
      const auto value = getString(openstudio::ZoneHVAC_WindowAirConditionerFields::CoolingCoilObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACWindowAirConditioner_Impl::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
      return setString(openstudio::ZoneHVAC_WindowAirConditionerFields::CoolingCoilObjectType, coolingCoilObjectType);
    }

    std::string ZoneHVACWindowAirConditioner_Impl::fanPlacement() const {
      const auto value = getString(openstudio::ZoneHVAC_WindowAirConditionerFields::FanPlacement, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACWindowAirConditioner_Impl::setFanPlacement(const std::string& fanPlacement) {
      return setString(openstudio::ZoneHVAC_WindowAirConditionerFields::FanPlacement, fanPlacement);
    }

    std::vector<std::string> ZoneHVACWindowAirConditioner_Impl::outdoorAirMixerObjectTypeValues() const {
      return openstudio::epmodel::ZoneHVACWindowAirConditioner::outdoorAirMixerObjectTypeValues();
    }

    std::vector<std::string> ZoneHVACWindowAirConditioner_Impl::supplyAirFanObjectTypeValues() const {
      return openstudio::epmodel::ZoneHVACWindowAirConditioner::supplyAirFanObjectTypeValues();
    }

    std::vector<std::string> ZoneHVACWindowAirConditioner_Impl::coolingCoilObjectTypeValues() const {
      return openstudio::epmodel::ZoneHVACWindowAirConditioner::coolingCoilObjectTypeValues();
    }

    std::vector<std::string> ZoneHVACWindowAirConditioner_Impl::fanPlacementValues() const {
      return openstudio::epmodel::ZoneHVACWindowAirConditioner::fanPlacementValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
