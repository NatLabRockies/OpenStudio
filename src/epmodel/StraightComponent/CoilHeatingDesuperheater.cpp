/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingDesuperheater.hpp"
#include "StraightComponent/CoilHeatingDesuperheater_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Heating_Desuperheater_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  CoilHeatingDesuperheater::CoilHeatingDesuperheater(const Model& model) : StraightComponent(CoilHeatingDesuperheater::iddObjectType(), model) {
    bool ok = true;
    ok = setHeatReclaimRecoveryEfficiency(0.8);
    OS_ASSERT(ok);
    ok = setOnCycleParasiticElectricLoad(0.0);
    OS_ASSERT(ok);
  }

  CoilHeatingDesuperheater::CoilHeatingDesuperheater(std::shared_ptr<detail::CoilHeatingDesuperheater_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingDesuperheater::iddObjectType() {
    return IddObjectType::Coil_Heating_Desuperheater;
  }

  double CoilHeatingDesuperheater::heatReclaimRecoveryEfficiency() const {
    return getImpl<detail::CoilHeatingDesuperheater_Impl>()->heatReclaimRecoveryEfficiency();
  }

  bool CoilHeatingDesuperheater::isHeatReclaimRecoveryEfficiencyDefaulted() const {
    return getImpl<detail::CoilHeatingDesuperheater_Impl>()->isHeatReclaimRecoveryEfficiencyDefaulted();
  }

  bool CoilHeatingDesuperheater::setHeatReclaimRecoveryEfficiency(double heatReclaimRecoveryEfficiency) {
    return getImpl<detail::CoilHeatingDesuperheater_Impl>()->setHeatReclaimRecoveryEfficiency(heatReclaimRecoveryEfficiency);
  }

  void CoilHeatingDesuperheater::resetHeatReclaimRecoveryEfficiency() {
    getImpl<detail::CoilHeatingDesuperheater_Impl>()->resetHeatReclaimRecoveryEfficiency();
  }

  double CoilHeatingDesuperheater::parasiticElectricLoad() const {
    return getImpl<detail::CoilHeatingDesuperheater_Impl>()->parasiticElectricLoad();
  }

  double CoilHeatingDesuperheater::onCycleParasiticElectricLoad() const {
    return getImpl<detail::CoilHeatingDesuperheater_Impl>()->onCycleParasiticElectricLoad();
  }

  bool CoilHeatingDesuperheater::isParasiticElectricLoadDefaulted() const {
    return getImpl<detail::CoilHeatingDesuperheater_Impl>()->isParasiticElectricLoadDefaulted();
  }

  bool CoilHeatingDesuperheater::isOnCycleParasiticElectricLoadDefaulted() const {
    return getImpl<detail::CoilHeatingDesuperheater_Impl>()->isOnCycleParasiticElectricLoadDefaulted();
  }

  bool CoilHeatingDesuperheater::setParasiticElectricLoad(double parasiticElectricLoad) {
    return getImpl<detail::CoilHeatingDesuperheater_Impl>()->setParasiticElectricLoad(parasiticElectricLoad);
  }

  bool CoilHeatingDesuperheater::setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad) {
    return getImpl<detail::CoilHeatingDesuperheater_Impl>()->setOnCycleParasiticElectricLoad(onCycleParasiticElectricLoad);
  }

  void CoilHeatingDesuperheater::resetParasiticElectricLoad() {
    getImpl<detail::CoilHeatingDesuperheater_Impl>()->resetParasiticElectricLoad();
  }

  void CoilHeatingDesuperheater::resetOnCycleParasiticElectricLoad() {
    getImpl<detail::CoilHeatingDesuperheater_Impl>()->resetOnCycleParasiticElectricLoad();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool CoilHeatingDesuperheater_Impl::addToNode(Node& node) {
      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
    }

    unsigned CoilHeatingDesuperheater_Impl::inletPort() const {
      return openstudio::Coil_Heating_DesuperheaterFields::AirInletNodeName;
    }

    unsigned CoilHeatingDesuperheater_Impl::outletPort() const {
      return openstudio::Coil_Heating_DesuperheaterFields::AirOutletNodeName;
    }

    double CoilHeatingDesuperheater_Impl::heatReclaimRecoveryEfficiency() const {
      const auto value = getDouble(openstudio::Coil_Heating_DesuperheaterFields::HeatReclaimRecoveryEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDesuperheater_Impl::isHeatReclaimRecoveryEfficiencyDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DesuperheaterFields::HeatReclaimRecoveryEfficiency);
    }

    bool CoilHeatingDesuperheater_Impl::setHeatReclaimRecoveryEfficiency(double heatReclaimRecoveryEfficiency) {
      return setDouble(openstudio::Coil_Heating_DesuperheaterFields::HeatReclaimRecoveryEfficiency, heatReclaimRecoveryEfficiency);
    }

    void CoilHeatingDesuperheater_Impl::resetHeatReclaimRecoveryEfficiency() {
      // Retained for API compatibility: this field is required in the current EnergyPlus schema.
    }

    double CoilHeatingDesuperheater_Impl::parasiticElectricLoad() const {
      return onCycleParasiticElectricLoad();
    }

    double CoilHeatingDesuperheater_Impl::onCycleParasiticElectricLoad() const {
      const auto value = getDouble(openstudio::Coil_Heating_DesuperheaterFields::OnCycleParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDesuperheater_Impl::isParasiticElectricLoadDefaulted() const {
      return isOnCycleParasiticElectricLoadDefaulted();
    }

    bool CoilHeatingDesuperheater_Impl::isOnCycleParasiticElectricLoadDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DesuperheaterFields::OnCycleParasiticElectricLoad);
    }

    bool CoilHeatingDesuperheater_Impl::setParasiticElectricLoad(double parasiticElectricLoad) {
      return setOnCycleParasiticElectricLoad(parasiticElectricLoad);
    }

    bool CoilHeatingDesuperheater_Impl::setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad) {
      return setDouble(openstudio::Coil_Heating_DesuperheaterFields::OnCycleParasiticElectricLoad, onCycleParasiticElectricLoad);
    }

    void CoilHeatingDesuperheater_Impl::resetParasiticElectricLoad() {
      resetOnCycleParasiticElectricLoad();
    }

    void CoilHeatingDesuperheater_Impl::resetOnCycleParasiticElectricLoad() {
      // Retained for API compatibility: this field is required in the current EnergyPlus schema.
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
