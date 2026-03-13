/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FanConstantVolume.hpp"
#include "FanConstantVolume_Impl.hpp"

#include "Loop/AirLoopHVAC_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Fan_ConstantVolume_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  FanConstantVolume::FanConstantVolume(const Model& model) : StraightComponent(FanConstantVolume::iddObjectType(), model) {
    auto impl = getImpl<detail::FanConstantVolume_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  FanConstantVolume::FanConstantVolume(std::shared_ptr<detail::FanConstantVolume_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType FanConstantVolume::iddObjectType() {
    return IddObjectType::Fan_ConstantVolume;
  }

  bool FanConstantVolume::addToNode(Node& node) {
    return getImpl<detail::FanConstantVolume_Impl>()->addToNode(node);
  }

  double FanConstantVolume::fanTotalEfficiency() const {
    return getImpl<detail::FanConstantVolume_Impl>()->fanTotalEfficiency();
  }

  bool FanConstantVolume::setFanTotalEfficiency(double fanTotalEfficiency) {
    return getImpl<detail::FanConstantVolume_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
  }

  double FanConstantVolume::fanEfficiency() const {
    return getImpl<detail::FanConstantVolume_Impl>()->fanTotalEfficiency();
  }

  bool FanConstantVolume::setFanEfficiency(double fanEfficiency) {
    return getImpl<detail::FanConstantVolume_Impl>()->setFanTotalEfficiency(fanEfficiency);
  }

  double FanConstantVolume::pressureRise() const {
    return getImpl<detail::FanConstantVolume_Impl>()->pressureRise();
  }

  bool FanConstantVolume::setPressureRise(double pressureRise) {
    return getImpl<detail::FanConstantVolume_Impl>()->setPressureRise(pressureRise);
  }

  boost::optional<double> FanConstantVolume::maximumFlowRate() const {
    return getImpl<detail::FanConstantVolume_Impl>()->maximumFlowRate();
  }

  bool FanConstantVolume::isMaximumFlowRateAutosized() const {
    return getImpl<detail::FanConstantVolume_Impl>()->isMaximumFlowRateAutosized();
  }

  bool FanConstantVolume::setMaximumFlowRate(double maximumFlowRate) {
    return getImpl<detail::FanConstantVolume_Impl>()->setMaximumFlowRate(maximumFlowRate);
  }

  void FanConstantVolume::resetMaximumFlowRate() {
    getImpl<detail::FanConstantVolume_Impl>()->resetMaximumFlowRate();
  }

  void FanConstantVolume::autosizeMaximumFlowRate() {
    getImpl<detail::FanConstantVolume_Impl>()->autosizeMaximumFlowRate();
  }

  double FanConstantVolume::motorEfficiency() const {
    return getImpl<detail::FanConstantVolume_Impl>()->motorEfficiency();
  }

  bool FanConstantVolume::setMotorEfficiency(double motorEfficiency) {
    return getImpl<detail::FanConstantVolume_Impl>()->setMotorEfficiency(motorEfficiency);
  }

  double FanConstantVolume::motorInAirstreamFraction() const {
    return getImpl<detail::FanConstantVolume_Impl>()->motorInAirstreamFraction();
  }

  bool FanConstantVolume::setMotorInAirstreamFraction(double motorInAirstreamFraction) {
    return getImpl<detail::FanConstantVolume_Impl>()->setMotorInAirstreamFraction(motorInAirstreamFraction);
  }

  std::string FanConstantVolume::endUseSubcategory() const {
    return getImpl<detail::FanConstantVolume_Impl>()->endUseSubcategory();
  }

  bool FanConstantVolume::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::FanConstantVolume_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned FanConstantVolume_Impl::inletPort() const {
      return Fan_ConstantVolumeFields::AirInletNodeName;
    }

    unsigned FanConstantVolume_Impl::outletPort() const {
      return Fan_ConstantVolumeFields::AirOutletNodeName;
    }

    bool FanConstantVolume_Impl::addToNode(Node& node) {
      auto airLoop = node.airLoopHVAC();
      auto oaSystem = node.airLoopHVACOutdoorAirSystem();

      // Parity with openstudio::model: allow insertion on AirLoop supply path and
      // OA-system-connected nodes (for contexts currently represented in epmodel).
      if ((airLoop && airLoop->supplyComponent(node.handle())) || oaSystem) {
        if (!StraightComponent_Impl::addToNode(node)) {
          return false;
        }

        // MixedAir SPM fan-node fields are derived from supply topology and must be
        // refreshed whenever a fan insertion mutates that topology.
        if (!airLoop && oaSystem) {
          airLoop = oaSystem->airLoopHVAC();
        }
        if (airLoop) {
          auto airLoopImpl = airLoop->getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>();
          OS_ASSERT(airLoopImpl);
          airLoopImpl->syncSetpointManagerMixedAirFanNodes();
        }
        return true;
      }

      return false;
    }

    double FanConstantVolume_Impl::fanTotalEfficiency() const {
      const auto value = getDouble(openstudio::Fan_ConstantVolumeFields::FanTotalEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanConstantVolume_Impl::setFanTotalEfficiency(double fanTotalEfficiency) {
      return setDouble(openstudio::Fan_ConstantVolumeFields::FanTotalEfficiency, fanTotalEfficiency);
    }

    double FanConstantVolume_Impl::pressureRise() const {
      const auto value = getDouble(openstudio::Fan_ConstantVolumeFields::PressureRise, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanConstantVolume_Impl::setPressureRise(double pressureRise) {
      return setDouble(openstudio::Fan_ConstantVolumeFields::PressureRise, pressureRise);
    }

    boost::optional<double> FanConstantVolume_Impl::maximumFlowRate() const {
      return getDouble(openstudio::Fan_ConstantVolumeFields::MaximumFlowRate, true);
    }

    bool FanConstantVolume_Impl::isMaximumFlowRateAutosized() const {
      if (const auto value = getString(openstudio::Fan_ConstantVolumeFields::MaximumFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FanConstantVolume_Impl::setMaximumFlowRate(double maximumFlowRate) {
      return setDouble(openstudio::Fan_ConstantVolumeFields::MaximumFlowRate, maximumFlowRate);
    }

    void FanConstantVolume_Impl::resetMaximumFlowRate() {
      OS_ASSERT(setString(openstudio::Fan_ConstantVolumeFields::MaximumFlowRate, ""));
    }

    void FanConstantVolume_Impl::autosizeMaximumFlowRate() {
      OS_ASSERT(setString(openstudio::Fan_ConstantVolumeFields::MaximumFlowRate, "autosize"));
    }

    double FanConstantVolume_Impl::motorEfficiency() const {
      const auto value = getDouble(openstudio::Fan_ConstantVolumeFields::MotorEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanConstantVolume_Impl::setMotorEfficiency(double motorEfficiency) {
      return setDouble(openstudio::Fan_ConstantVolumeFields::MotorEfficiency, motorEfficiency);
    }

    double FanConstantVolume_Impl::motorInAirstreamFraction() const {
      const auto value = getDouble(openstudio::Fan_ConstantVolumeFields::MotorInAirstreamFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanConstantVolume_Impl::setMotorInAirstreamFraction(double motorInAirstreamFraction) {
      return setDouble(openstudio::Fan_ConstantVolumeFields::MotorInAirstreamFraction, motorInAirstreamFraction);
    }

    std::string FanConstantVolume_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::Fan_ConstantVolumeFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanConstantVolume_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      return setString(openstudio::Fan_ConstantVolumeFields::EndUseSubcategory, endUseSubcategory);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
