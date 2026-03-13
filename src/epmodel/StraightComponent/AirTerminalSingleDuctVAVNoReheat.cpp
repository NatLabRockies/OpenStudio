/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctVAVNoReheat.hpp"
#include "StraightComponent/AirTerminalSingleDuctVAVNoReheat_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_VAV_NoReheat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  AirTerminalSingleDuctVAVNoReheat::AirTerminalSingleDuctVAVNoReheat(const Model& model)
    : ModelObject(AirTerminalSingleDuctVAVNoReheat::iddObjectType(), model) {
    autosizeMaximumAirFlowRate();
    OS_ASSERT(setZoneMinimumAirFlowInputMethod("Constant"));
    OS_ASSERT(setConstantMinimumAirFlowFraction(0.3));
  }

  AirTerminalSingleDuctVAVNoReheat::AirTerminalSingleDuctVAVNoReheat(std::shared_ptr<detail::AirTerminalSingleDuctVAVNoReheat_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctVAVNoReheat::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_VAV_NoReheat;
  }

  std::vector<std::string> AirTerminalSingleDuctVAVNoReheat::zoneMinimumAirFlowInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ZoneMinimumAirFlowInputMethod);
  }

  boost::optional<double> AirTerminalSingleDuctVAVNoReheat::maximumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->maximumAirFlowRate();
  }

  bool AirTerminalSingleDuctVAVNoReheat::isMaximumAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->isMaximumAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVNoReheat::setMaximumAirFlowRate(double maximumAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->setMaximumAirFlowRate(maximumAirFlowRate);
  }

  void AirTerminalSingleDuctVAVNoReheat::resetMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->resetMaximumAirFlowRate();
  }

  void AirTerminalSingleDuctVAVNoReheat::autosizeMaximumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->autosizeMaximumAirFlowRate();
  }

  boost::optional<std::string> AirTerminalSingleDuctVAVNoReheat::zoneMinimumAirFlowInputMethod() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->zoneMinimumAirFlowInputMethod();
  }

  bool AirTerminalSingleDuctVAVNoReheat::setZoneMinimumAirFlowInputMethod(const std::string& zoneMinimumAirFlowInputMethod) {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->setZoneMinimumAirFlowInputMethod(zoneMinimumAirFlowInputMethod);
  }

  void AirTerminalSingleDuctVAVNoReheat::resetZoneMinimumAirFlowInputMethod() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->resetZoneMinimumAirFlowInputMethod();
  }

  boost::optional<double> AirTerminalSingleDuctVAVNoReheat::constantMinimumAirFlowFraction() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->constantMinimumAirFlowFraction();
  }

  bool AirTerminalSingleDuctVAVNoReheat::isConstantMinimumAirFlowFractionAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->isConstantMinimumAirFlowFractionAutosized();
  }

  bool AirTerminalSingleDuctVAVNoReheat::isConstantMinimumAirFlowFractionDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->isConstantMinimumAirFlowFractionDefaulted();
  }

  bool AirTerminalSingleDuctVAVNoReheat::setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction) {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->setConstantMinimumAirFlowFraction(constantMinimumAirFlowFraction);
  }

  void AirTerminalSingleDuctVAVNoReheat::resetConstantMinimumAirFlowFraction() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->resetConstantMinimumAirFlowFraction();
  }

  void AirTerminalSingleDuctVAVNoReheat::autosizeConstantMinimumAirFlowFraction() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->autosizeConstantMinimumAirFlowFraction();
  }

  boost::optional<double> AirTerminalSingleDuctVAVNoReheat::fixedMinimumAirFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->fixedMinimumAirFlowRate();
  }

  bool AirTerminalSingleDuctVAVNoReheat::isFixedMinimumAirFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->isFixedMinimumAirFlowRateAutosized();
  }

  bool AirTerminalSingleDuctVAVNoReheat::isFixedMinimumAirFlowRateDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->isFixedMinimumAirFlowRateDefaulted();
  }

  bool AirTerminalSingleDuctVAVNoReheat::setFixedMinimumAirFlowRate(double fixedMinimumAirFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->setFixedMinimumAirFlowRate(fixedMinimumAirFlowRate);
  }

  void AirTerminalSingleDuctVAVNoReheat::resetFixedMinimumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->resetFixedMinimumAirFlowRate();
  }

  void AirTerminalSingleDuctVAVNoReheat::autosizeFixedMinimumAirFlowRate() {
    getImpl<detail::AirTerminalSingleDuctVAVNoReheat_Impl>()->autosizeFixedMinimumAirFlowRate();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> AirTerminalSingleDuctVAVNoReheat_Impl::maximumAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MaximumAirFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::isMaximumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MaximumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::setMaximumAirFlowRate(double maximumAirFlowRate) {
      const bool result = setDouble(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MaximumAirFlowRate, maximumAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::resetMaximumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MaximumAirFlowRate, "");
      OS_ASSERT(result);
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::autosizeMaximumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::MaximumAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<std::string> AirTerminalSingleDuctVAVNoReheat_Impl::zoneMinimumAirFlowInputMethod() const {
      return getString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ZoneMinimumAirFlowInputMethod, true);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::setZoneMinimumAirFlowInputMethod(const std::string& zoneMinimumAirFlowInputMethod) {
      const bool result =
        setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ZoneMinimumAirFlowInputMethod, zoneMinimumAirFlowInputMethod);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::resetZoneMinimumAirFlowInputMethod() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ZoneMinimumAirFlowInputMethod, "");
      OS_ASSERT(result);
    }

    std::vector<std::string> AirTerminalSingleDuctVAVNoReheat_Impl::zoneMinimumAirFlowInputMethodValues() const {
      return AirTerminalSingleDuctVAVNoReheat::zoneMinimumAirFlowInputMethodValues();
    }

    boost::optional<double> AirTerminalSingleDuctVAVNoReheat_Impl::constantMinimumAirFlowFraction() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ConstantMinimumAirFlowFraction, true);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::isConstantMinimumAirFlowFractionAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ConstantMinimumAirFlowFraction, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::isConstantMinimumAirFlowFractionDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ConstantMinimumAirFlowFraction);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::setConstantMinimumAirFlowFraction(double constantMinimumAirFlowFraction) {
      const bool result =
        setDouble(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ConstantMinimumAirFlowFraction, constantMinimumAirFlowFraction);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::resetConstantMinimumAirFlowFraction() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ConstantMinimumAirFlowFraction, "");
      OS_ASSERT(result);
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::autosizeConstantMinimumAirFlowFraction() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::ConstantMinimumAirFlowFraction, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> AirTerminalSingleDuctVAVNoReheat_Impl::fixedMinimumAirFlowRate() const {
      return getDouble(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::FixedMinimumAirFlowRate, true);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::isFixedMinimumAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::FixedMinimumAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::isFixedMinimumAirFlowRateDefaulted() const {
      return isEmpty(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::FixedMinimumAirFlowRate);
    }

    bool AirTerminalSingleDuctVAVNoReheat_Impl::setFixedMinimumAirFlowRate(double fixedMinimumAirFlowRate) {
      const bool result = setDouble(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::FixedMinimumAirFlowRate, fixedMinimumAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::resetFixedMinimumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::FixedMinimumAirFlowRate, "");
      OS_ASSERT(result);
    }

    void AirTerminalSingleDuctVAVNoReheat_Impl::autosizeFixedMinimumAirFlowRate() {
      const bool result = setString(openstudio::AirTerminal_SingleDuct_VAV_NoReheatFields::FixedMinimumAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
