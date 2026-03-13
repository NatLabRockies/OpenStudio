/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerMultiZoneMinimumHumidityAverage.hpp"
#include "SetpointManager/SetpointManagerMultiZoneMinimumHumidityAverage_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_MultiZone_MinimumHumidity_Average_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerMultiZoneMinimumHumidityAverage::SetpointManagerMultiZoneMinimumHumidityAverage(const Model& model)
    : SetpointManager(SetpointManagerMultiZoneMinimumHumidityAverage::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerMultiZoneMinimumHumidityAverage_Impl>();
    OS_ASSERT(impl);
  }

  SetpointManagerMultiZoneMinimumHumidityAverage::SetpointManagerMultiZoneMinimumHumidityAverage(
    std::shared_ptr<detail::SetpointManagerMultiZoneMinimumHumidityAverage_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerMultiZoneMinimumHumidityAverage::iddObjectType() {
    return IddObjectType::SetpointManager_MultiZone_MinimumHumidity_Average;
  }

  std::vector<std::string> SetpointManagerMultiZoneMinimumHumidityAverage::controlVariableValues() {
    return {"MinimumHumidityRatio"};
  }

  std::string SetpointManagerMultiZoneMinimumHumidityAverage::controlVariable() const {
    return "MinimumHumidityRatio";
  }

  bool SetpointManagerMultiZoneMinimumHumidityAverage::setControlVariable(const std::string& controlVariable) {
    return openstudio::istringEqual(controlVariable, "MinimumHumidityRatio");
  }

  double SetpointManagerMultiZoneMinimumHumidityAverage::minimumSetpointHumidityRatio() const {
    return getImpl<detail::SetpointManagerMultiZoneMinimumHumidityAverage_Impl>()->minimumSetpointHumidityRatio();
  }

  bool SetpointManagerMultiZoneMinimumHumidityAverage::isMinimumSetpointHumidityRatioDefaulted() const {
    return getImpl<detail::SetpointManagerMultiZoneMinimumHumidityAverage_Impl>()->isMinimumSetpointHumidityRatioDefaulted();
  }

  bool SetpointManagerMultiZoneMinimumHumidityAverage::setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio) {
    const bool result =
      getImpl<detail::SetpointManagerMultiZoneMinimumHumidityAverage_Impl>()->setMinimumSetpointHumidityRatio(minimumSetpointHumidityRatio);
    OS_ASSERT(result);
    return result;
  }

  void SetpointManagerMultiZoneMinimumHumidityAverage::resetMinimumSetpointHumidityRatio() {
    getImpl<detail::SetpointManagerMultiZoneMinimumHumidityAverage_Impl>()->resetMinimumSetpointHumidityRatio();
  }

  double SetpointManagerMultiZoneMinimumHumidityAverage::maximumSetpointHumidityRatio() const {
    return getImpl<detail::SetpointManagerMultiZoneMinimumHumidityAverage_Impl>()->maximumSetpointHumidityRatio();
  }

  bool SetpointManagerMultiZoneMinimumHumidityAverage::isMaximumSetpointHumidityRatioDefaulted() const {
    return getImpl<detail::SetpointManagerMultiZoneMinimumHumidityAverage_Impl>()->isMaximumSetpointHumidityRatioDefaulted();
  }

  bool SetpointManagerMultiZoneMinimumHumidityAverage::setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio) {
    const bool result =
      getImpl<detail::SetpointManagerMultiZoneMinimumHumidityAverage_Impl>()->setMaximumSetpointHumidityRatio(maximumSetpointHumidityRatio);
    OS_ASSERT(result);
    return result;
  }

  void SetpointManagerMultiZoneMinimumHumidityAverage::resetMaximumSetpointHumidityRatio() {
    getImpl<detail::SetpointManagerMultiZoneMinimumHumidityAverage_Impl>()->resetMaximumSetpointHumidityRatio();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SetpointManagerMultiZoneMinimumHumidityAverage_Impl::minimumSetpointHumidityRatio() const {
      const auto value = getDouble(openstudio::SetpointManager_MultiZone_MinimumHumidity_AverageFields::MinimumSetpointHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerMultiZoneMinimumHumidityAverage_Impl::isMinimumSetpointHumidityRatioDefaulted() const {
      return isEmpty(openstudio::SetpointManager_MultiZone_MinimumHumidity_AverageFields::MinimumSetpointHumidityRatio);
    }

    bool SetpointManagerMultiZoneMinimumHumidityAverage_Impl::setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio) {
      const bool result =
        setDouble(openstudio::SetpointManager_MultiZone_MinimumHumidity_AverageFields::MinimumSetpointHumidityRatio, minimumSetpointHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerMultiZoneMinimumHumidityAverage_Impl::resetMinimumSetpointHumidityRatio() {
      const bool result = setString(openstudio::SetpointManager_MultiZone_MinimumHumidity_AverageFields::MinimumSetpointHumidityRatio, "");
      OS_ASSERT(result);
    }

    double SetpointManagerMultiZoneMinimumHumidityAverage_Impl::maximumSetpointHumidityRatio() const {
      const auto value = getDouble(openstudio::SetpointManager_MultiZone_MinimumHumidity_AverageFields::MaximumSetpointHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerMultiZoneMinimumHumidityAverage_Impl::isMaximumSetpointHumidityRatioDefaulted() const {
      return isEmpty(openstudio::SetpointManager_MultiZone_MinimumHumidity_AverageFields::MaximumSetpointHumidityRatio);
    }

    bool SetpointManagerMultiZoneMinimumHumidityAverage_Impl::setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio) {
      const bool result =
        setDouble(openstudio::SetpointManager_MultiZone_MinimumHumidity_AverageFields::MaximumSetpointHumidityRatio, maximumSetpointHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerMultiZoneMinimumHumidityAverage_Impl::resetMaximumSetpointHumidityRatio() {
      const bool result = setString(openstudio::SetpointManager_MultiZone_MinimumHumidity_AverageFields::MaximumSetpointHumidityRatio, "");
      OS_ASSERT(result);
    }

    unsigned SetpointManagerMultiZoneMinimumHumidityAverage_Impl::setpointNodeFieldIndex() const {
      return openstudio::SetpointManager_MultiZone_MinimumHumidity_AverageFields::SetpointNodeorNodeListName;
    }

    unsigned SetpointManagerMultiZoneMinimumHumidityAverage_Impl::controlVariableFieldIndex() const {
      // E+ SetpointManager:MultiZone:MinimumHumidity:Average has no explicit control variable field;
      // this placeholder index satisfies the abstract SetpointManager_Impl contract.
      return openstudio::SetpointManager_MultiZone_MinimumHumidity_AverageFields::HVACAirLoopName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
