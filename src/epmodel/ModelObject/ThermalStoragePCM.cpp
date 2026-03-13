/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Model.hpp"
#include "ModelObject/ThermalStoragePCM.hpp"
#include "ModelObject/ThermalStoragePCM_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/ThermalStorage_PCM_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ThermalStoragePCM::ThermalStoragePCM(const Model& model) : ModelObject(ThermalStoragePCM::iddObjectType(), model) {}

  ThermalStoragePCM::ThermalStoragePCM(std::shared_ptr<detail::ThermalStoragePCM_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ThermalStoragePCM::iddObjectType() {
    return IddObjectType::ThermalStorage_PCM;
  }

  boost::optional<double> ThermalStoragePCM::tankCapacity() const {
    return getImpl<detail::ThermalStoragePCM_Impl>()->tankCapacity();
  }

  bool ThermalStoragePCM::setTankCapacity(double tankCapacity) {
    return getImpl<detail::ThermalStoragePCM_Impl>()->setTankCapacity(tankCapacity);
  }

  void ThermalStoragePCM::autosizeTankCapacity() {
    getImpl<detail::ThermalStoragePCM_Impl>()->autosizeTankCapacity();
  }

  bool ThermalStoragePCM::isTankCapacityAutosized() const {
    return getImpl<detail::ThermalStoragePCM_Impl>()->isTankCapacityAutosized();
  }

  boost::optional<double> ThermalStoragePCM::heatLossRate() const {
    return getImpl<detail::ThermalStoragePCM_Impl>()->heatLossRate();
  }

  bool ThermalStoragePCM::setHeatLossRate(double heatLossRate) {
    return getImpl<detail::ThermalStoragePCM_Impl>()->setHeatLossRate(heatLossRate);
  }

  bool ThermalStoragePCM::isHeatLossRateDefaulted() const {
    return getImpl<detail::ThermalStoragePCM_Impl>()->isHeatLossRateDefaulted();
  }

  void ThermalStoragePCM::resetHeatLossRate() {
    getImpl<detail::ThermalStoragePCM_Impl>()->resetHeatLossRate();
  }

  boost::optional<double> ThermalStoragePCM::useSideDesignFlowRate() const {
    return getImpl<detail::ThermalStoragePCM_Impl>()->useSideDesignFlowRate();
  }

  bool ThermalStoragePCM::setUseSideDesignFlowRate(double useSideDesignFlowRate) {
    return getImpl<detail::ThermalStoragePCM_Impl>()->setUseSideDesignFlowRate(useSideDesignFlowRate);
  }

  void ThermalStoragePCM::autosizeUseSideDesignFlowRate() {
    getImpl<detail::ThermalStoragePCM_Impl>()->autosizeUseSideDesignFlowRate();
  }

  bool ThermalStoragePCM::isUseSideDesignFlowRateAutosized() const {
    return getImpl<detail::ThermalStoragePCM_Impl>()->isUseSideDesignFlowRateAutosized();
  }

  boost::optional<double> ThermalStoragePCM::plantSideDesignFlowRate() const {
    return getImpl<detail::ThermalStoragePCM_Impl>()->plantSideDesignFlowRate();
  }

  bool ThermalStoragePCM::setPlantSideDesignFlowRate(double plantSideDesignFlowRate) {
    return getImpl<detail::ThermalStoragePCM_Impl>()->setPlantSideDesignFlowRate(plantSideDesignFlowRate);
  }

  void ThermalStoragePCM::autosizePlantSideDesignFlowRate() {
    getImpl<detail::ThermalStoragePCM_Impl>()->autosizePlantSideDesignFlowRate();
  }

  bool ThermalStoragePCM::isPlantSideDesignFlowRateAutosized() const {
    return getImpl<detail::ThermalStoragePCM_Impl>()->isPlantSideDesignFlowRateAutosized();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ThermalStoragePCM_Impl::tankCapacity() const {
      return getDouble(openstudio::ThermalStorage_PCMFields::TankCapacity, true);
    }

    bool ThermalStoragePCM_Impl::setTankCapacity(double tankCapacity) {
      return setDouble(openstudio::ThermalStorage_PCMFields::TankCapacity, tankCapacity);
    }

    void ThermalStoragePCM_Impl::autosizeTankCapacity() {
      OS_ASSERT(setString(openstudio::ThermalStorage_PCMFields::TankCapacity, "autosize"));
    }

    bool ThermalStoragePCM_Impl::isTankCapacityAutosized() const {
      if (auto value = getString(openstudio::ThermalStorage_PCMFields::TankCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    boost::optional<double> ThermalStoragePCM_Impl::heatLossRate() const {
      return getDouble(openstudio::ThermalStorage_PCMFields::HeatLossRate, true);
    }

    bool ThermalStoragePCM_Impl::setHeatLossRate(double heatLossRate) {
      const bool result = setDouble(openstudio::ThermalStorage_PCMFields::HeatLossRate, heatLossRate);
      OS_ASSERT(result);
      return result;
    }

    bool ThermalStoragePCM_Impl::isHeatLossRateDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_PCMFields::HeatLossRate);
    }

    void ThermalStoragePCM_Impl::resetHeatLossRate() {
      OS_ASSERT(setString(openstudio::ThermalStorage_PCMFields::HeatLossRate, ""));
    }

    boost::optional<double> ThermalStoragePCM_Impl::useSideDesignFlowRate() const {
      return getDouble(openstudio::ThermalStorage_PCMFields::UseSideDesignFlowRate, true);
    }

    bool ThermalStoragePCM_Impl::setUseSideDesignFlowRate(double useSideDesignFlowRate) {
      return setDouble(openstudio::ThermalStorage_PCMFields::UseSideDesignFlowRate, useSideDesignFlowRate);
    }

    void ThermalStoragePCM_Impl::autosizeUseSideDesignFlowRate() {
      OS_ASSERT(setString(openstudio::ThermalStorage_PCMFields::UseSideDesignFlowRate, "autosize"));
    }

    bool ThermalStoragePCM_Impl::isUseSideDesignFlowRateAutosized() const {
      if (auto value = getString(openstudio::ThermalStorage_PCMFields::UseSideDesignFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    boost::optional<double> ThermalStoragePCM_Impl::plantSideDesignFlowRate() const {
      return getDouble(openstudio::ThermalStorage_PCMFields::PlantSideDesignFlowRate, true);
    }

    bool ThermalStoragePCM_Impl::setPlantSideDesignFlowRate(double plantSideDesignFlowRate) {
      return setDouble(openstudio::ThermalStorage_PCMFields::PlantSideDesignFlowRate, plantSideDesignFlowRate);
    }

    void ThermalStoragePCM_Impl::autosizePlantSideDesignFlowRate() {
      OS_ASSERT(setString(openstudio::ThermalStorage_PCMFields::PlantSideDesignFlowRate, "autosize"));
    }

    bool ThermalStoragePCM_Impl::isPlantSideDesignFlowRateAutosized() const {
      if (auto value = getString(openstudio::ThermalStorage_PCMFields::PlantSideDesignFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
