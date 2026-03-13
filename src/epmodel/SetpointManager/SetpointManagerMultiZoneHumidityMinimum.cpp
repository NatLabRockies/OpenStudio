/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SetpointManager/SetpointManagerMultiZoneHumidityMinimum.hpp"
#include "SetpointManager/SetpointManagerMultiZoneHumidityMinimum_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SetpointManager_MultiZone_Humidity_Minimum_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SetpointManagerMultiZoneHumidityMinimum::SetpointManagerMultiZoneHumidityMinimum(const Model& model)
    : SetpointManager(SetpointManagerMultiZoneHumidityMinimum::iddObjectType(), model) {
    auto impl = getImpl<detail::SetpointManagerMultiZoneHumidityMinimum_Impl>();
    OS_ASSERT(impl);
  }

  SetpointManagerMultiZoneHumidityMinimum::SetpointManagerMultiZoneHumidityMinimum(
    std::shared_ptr<detail::SetpointManagerMultiZoneHumidityMinimum_Impl> impl)
    : SetpointManager(std::move(impl)) {}

  IddObjectType SetpointManagerMultiZoneHumidityMinimum::iddObjectType() {
    return IddObjectType::SetpointManager_MultiZone_Humidity_Minimum;
  }

  std::vector<std::string> SetpointManagerMultiZoneHumidityMinimum::controlVariableValues() {
    return {"MinimumHumidityRatio"};
  }

  std::string SetpointManagerMultiZoneHumidityMinimum::controlVariable() const {
    return "MinimumHumidityRatio";
  }

  bool SetpointManagerMultiZoneHumidityMinimum::setControlVariable(const std::string& controlVariable) {
    return openstudio::istringEqual(controlVariable, "MinimumHumidityRatio");
  }

  double SetpointManagerMultiZoneHumidityMinimum::minimumSetpointHumidityRatio() const {
    return getImpl<detail::SetpointManagerMultiZoneHumidityMinimum_Impl>()->minimumSetpointHumidityRatio();
  }

  bool SetpointManagerMultiZoneHumidityMinimum::isMinimumSetpointHumidityRatioDefaulted() const {
    return getImpl<detail::SetpointManagerMultiZoneHumidityMinimum_Impl>()->isMinimumSetpointHumidityRatioDefaulted();
  }

  bool SetpointManagerMultiZoneHumidityMinimum::setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio) {
    const bool result =
      getImpl<detail::SetpointManagerMultiZoneHumidityMinimum_Impl>()->setMinimumSetpointHumidityRatio(minimumSetpointHumidityRatio);
    OS_ASSERT(result);
    return result;
  }

  void SetpointManagerMultiZoneHumidityMinimum::resetMinimumSetpointHumidityRatio() {
    getImpl<detail::SetpointManagerMultiZoneHumidityMinimum_Impl>()->resetMinimumSetpointHumidityRatio();
  }

  double SetpointManagerMultiZoneHumidityMinimum::maximumSetpointHumidityRatio() const {
    return getImpl<detail::SetpointManagerMultiZoneHumidityMinimum_Impl>()->maximumSetpointHumidityRatio();
  }

  bool SetpointManagerMultiZoneHumidityMinimum::isMaximumSetpointHumidityRatioDefaulted() const {
    return getImpl<detail::SetpointManagerMultiZoneHumidityMinimum_Impl>()->isMaximumSetpointHumidityRatioDefaulted();
  }

  bool SetpointManagerMultiZoneHumidityMinimum::setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio) {
    const bool result =
      getImpl<detail::SetpointManagerMultiZoneHumidityMinimum_Impl>()->setMaximumSetpointHumidityRatio(maximumSetpointHumidityRatio);
    OS_ASSERT(result);
    return result;
  }

  void SetpointManagerMultiZoneHumidityMinimum::resetMaximumSetpointHumidityRatio() {
    getImpl<detail::SetpointManagerMultiZoneHumidityMinimum_Impl>()->resetMaximumSetpointHumidityRatio();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SetpointManagerMultiZoneHumidityMinimum_Impl::minimumSetpointHumidityRatio() const {
      const auto value = getDouble(openstudio::SetpointManager_MultiZone_Humidity_MinimumFields::MinimumSetpointHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerMultiZoneHumidityMinimum_Impl::isMinimumSetpointHumidityRatioDefaulted() const {
      return isEmpty(openstudio::SetpointManager_MultiZone_Humidity_MinimumFields::MinimumSetpointHumidityRatio);
    }

    bool SetpointManagerMultiZoneHumidityMinimum_Impl::setMinimumSetpointHumidityRatio(double minimumSetpointHumidityRatio) {
      const bool result =
        setDouble(openstudio::SetpointManager_MultiZone_Humidity_MinimumFields::MinimumSetpointHumidityRatio, minimumSetpointHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerMultiZoneHumidityMinimum_Impl::resetMinimumSetpointHumidityRatio() {
      const bool result = setString(openstudio::SetpointManager_MultiZone_Humidity_MinimumFields::MinimumSetpointHumidityRatio, "");
      OS_ASSERT(result);
    }

    double SetpointManagerMultiZoneHumidityMinimum_Impl::maximumSetpointHumidityRatio() const {
      const auto value = getDouble(openstudio::SetpointManager_MultiZone_Humidity_MinimumFields::MaximumSetpointHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SetpointManagerMultiZoneHumidityMinimum_Impl::isMaximumSetpointHumidityRatioDefaulted() const {
      return isEmpty(openstudio::SetpointManager_MultiZone_Humidity_MinimumFields::MaximumSetpointHumidityRatio);
    }

    bool SetpointManagerMultiZoneHumidityMinimum_Impl::setMaximumSetpointHumidityRatio(double maximumSetpointHumidityRatio) {
      const bool result =
        setDouble(openstudio::SetpointManager_MultiZone_Humidity_MinimumFields::MaximumSetpointHumidityRatio, maximumSetpointHumidityRatio);
      OS_ASSERT(result);
      return result;
    }

    void SetpointManagerMultiZoneHumidityMinimum_Impl::resetMaximumSetpointHumidityRatio() {
      const bool result = setString(openstudio::SetpointManager_MultiZone_Humidity_MinimumFields::MaximumSetpointHumidityRatio, "");
      OS_ASSERT(result);
    }

    unsigned SetpointManagerMultiZoneHumidityMinimum_Impl::setpointNodeFieldIndex() const {
      return openstudio::SetpointManager_MultiZone_Humidity_MinimumFields::SetpointNodeorNodeListName;
    }

    unsigned SetpointManagerMultiZoneHumidityMinimum_Impl::controlVariableFieldIndex() const {
      // E+ SetpointManager:MultiZone:Humidity:Minimum has no explicit control variable field;
      // this placeholder index satisfies the abstract SetpointManager_Impl contract.
      return openstudio::SetpointManager_MultiZone_Humidity_MinimumFields::HVACAirLoopName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
