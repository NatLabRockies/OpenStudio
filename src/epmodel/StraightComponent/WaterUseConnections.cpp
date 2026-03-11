/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/WaterUseConnections.hpp"
#include "StraightComponent/WaterUseConnections_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_WaterUse_Connections_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  WaterUseConnections::WaterUseConnections(const Model& model) : StraightComponent(WaterUseConnections::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::WaterUseConnections_Impl>());

    setDrainWaterHeatExchangerType("None");
    setDrainWaterHeatExchangerDestination("Plant");
  }

  WaterUseConnections::WaterUseConnections(std::shared_ptr<detail::WaterUseConnections_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType WaterUseConnections::iddObjectType() {
    return IddObjectType::OS_WaterUse_Connections;
  }

  std::vector<std::string> WaterUseConnections::drainWaterHeatExchangerTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::OS_WaterUse_ConnectionsFields::DrainWaterHeatExchangerType);
  }

  std::vector<std::string> WaterUseConnections::drainWaterHeatExchangerDestinationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::OS_WaterUse_ConnectionsFields::DrainWaterHeatExchangerDestination);
  }

  std::string WaterUseConnections::drainWaterHeatExchangerType() const {
    return getImpl<detail::WaterUseConnections_Impl>()->drainWaterHeatExchangerType();
  }

  bool WaterUseConnections::setDrainWaterHeatExchangerType(const std::string& drainWaterHeatExchangerType) {
    return getImpl<detail::WaterUseConnections_Impl>()->setDrainWaterHeatExchangerType(drainWaterHeatExchangerType);
  }

  std::string WaterUseConnections::drainWaterHeatExchangerDestination() const {
    return getImpl<detail::WaterUseConnections_Impl>()->drainWaterHeatExchangerDestination();
  }

  bool WaterUseConnections::setDrainWaterHeatExchangerDestination(const std::string& drainWaterHeatExchangerDestination) {
    return getImpl<detail::WaterUseConnections_Impl>()->setDrainWaterHeatExchangerDestination(drainWaterHeatExchangerDestination);
  }

  boost::optional<double> WaterUseConnections::drainWaterHeatExchangerUFactorTimesArea() const {
    return getImpl<detail::WaterUseConnections_Impl>()->drainWaterHeatExchangerUFactorTimesArea();
  }

  bool WaterUseConnections::setDrainWaterHeatExchangerUFactorTimesArea(double drainWaterHeatExchangerUFactorTimesArea) {
    return getImpl<detail::WaterUseConnections_Impl>()->setDrainWaterHeatExchangerUFactorTimesArea(drainWaterHeatExchangerUFactorTimesArea);
  }

  void WaterUseConnections::resetDrainWaterHeatExchangerUFactorTimesArea() {
    getImpl<detail::WaterUseConnections_Impl>()->resetDrainWaterHeatExchangerUFactorTimesArea();
  }

  namespace detail {

    std::string WaterUseConnections_Impl::drainWaterHeatExchangerType() const {
      const auto value = getString(openstudio::OS_WaterUse_ConnectionsFields::DrainWaterHeatExchangerType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterUseConnections_Impl::setDrainWaterHeatExchangerType(const std::string& drainWaterHeatExchangerType) {
      return setString(openstudio::OS_WaterUse_ConnectionsFields::DrainWaterHeatExchangerType, drainWaterHeatExchangerType);
    }

    std::string WaterUseConnections_Impl::drainWaterHeatExchangerDestination() const {
      const auto value = getString(openstudio::OS_WaterUse_ConnectionsFields::DrainWaterHeatExchangerDestination, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterUseConnections_Impl::setDrainWaterHeatExchangerDestination(const std::string& drainWaterHeatExchangerDestination) {
      return setString(openstudio::OS_WaterUse_ConnectionsFields::DrainWaterHeatExchangerDestination, drainWaterHeatExchangerDestination);
    }

    boost::optional<double> WaterUseConnections_Impl::drainWaterHeatExchangerUFactorTimesArea() const {
      return getDouble(openstudio::OS_WaterUse_ConnectionsFields::DrainWaterHeatExchangerUFactorTimesArea, true);
    }

    bool WaterUseConnections_Impl::setDrainWaterHeatExchangerUFactorTimesArea(double drainWaterHeatExchangerUFactorTimesArea) {
      return setDouble(openstudio::OS_WaterUse_ConnectionsFields::DrainWaterHeatExchangerUFactorTimesArea, drainWaterHeatExchangerUFactorTimesArea);
    }

    void WaterUseConnections_Impl::resetDrainWaterHeatExchangerUFactorTimesArea() {
      OS_ASSERT(setString(openstudio::OS_WaterUse_ConnectionsFields::DrainWaterHeatExchangerUFactorTimesArea, ""));
    }

    std::vector<std::string> WaterUseConnections_Impl::drainWaterHeatExchangerTypeValues() const {
      return openstudio::epmodel::WaterUseConnections::drainWaterHeatExchangerTypeValues();
    }

    std::vector<std::string> WaterUseConnections_Impl::drainWaterHeatExchangerDestinationValues() const {
      return openstudio::epmodel::WaterUseConnections::drainWaterHeatExchangerDestinationValues();
    }

    unsigned WaterUseConnections_Impl::inletPort() const {
      return openstudio::OS_WaterUse_ConnectionsFields::InletNodeName;
    }

    unsigned WaterUseConnections_Impl::outletPort() const {
      return openstudio::OS_WaterUse_ConnectionsFields::OutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
