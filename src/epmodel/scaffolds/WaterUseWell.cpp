/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "scaffolds/WaterUseWell.hpp"
#include "scaffolds/WaterUseWell_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/WaterUse_Well_FieldEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  WaterUseWell::WaterUseWell(const Model& model) : ModelObject(WaterUseWell::iddObjectType(), model) {}

  WaterUseWell::WaterUseWell(std::shared_ptr<detail::WaterUseWell_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WaterUseWell::iddObjectType() {
    return IddObjectType::WaterUse_Well;
  }

  std::vector<std::string> WaterUseWell::waterTableDepthModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterUse_WellFields::WaterTableDepthMode);
  }

  boost::optional<double> WaterUseWell::pumpDepth() const {
    return getImpl<detail::WaterUseWell_Impl>()->pumpDepth();
  }

  bool WaterUseWell::setPumpDepth(double pumpDepth) {
    return getImpl<detail::WaterUseWell_Impl>()->setPumpDepth(pumpDepth);
  }

  boost::optional<double> WaterUseWell::pumpRatedFlowRate() const {
    return getImpl<detail::WaterUseWell_Impl>()->pumpRatedFlowRate();
  }

  bool WaterUseWell::setPumpRatedFlowRate(double pumpRatedFlowRate) {
    return getImpl<detail::WaterUseWell_Impl>()->setPumpRatedFlowRate(pumpRatedFlowRate);
  }

  boost::optional<double> WaterUseWell::pumpRatedHead() const {
    return getImpl<detail::WaterUseWell_Impl>()->pumpRatedHead();
  }

  bool WaterUseWell::setPumpRatedHead(double pumpRatedHead) {
    return getImpl<detail::WaterUseWell_Impl>()->setPumpRatedHead(pumpRatedHead);
  }

  boost::optional<double> WaterUseWell::pumpRatedPowerConsumption() const {
    return getImpl<detail::WaterUseWell_Impl>()->pumpRatedPowerConsumption();
  }

  bool WaterUseWell::setPumpRatedPowerConsumption(double pumpRatedPowerConsumption) {
    return getImpl<detail::WaterUseWell_Impl>()->setPumpRatedPowerConsumption(pumpRatedPowerConsumption);
  }

  boost::optional<double> WaterUseWell::pumpEfficiency() const {
    return getImpl<detail::WaterUseWell_Impl>()->pumpEfficiency();
  }

  bool WaterUseWell::setPumpEfficiency(double pumpEfficiency) {
    return getImpl<detail::WaterUseWell_Impl>()->setPumpEfficiency(pumpEfficiency);
  }

  boost::optional<double> WaterUseWell::wellRecoveryRate() const {
    return getImpl<detail::WaterUseWell_Impl>()->wellRecoveryRate();
  }

  bool WaterUseWell::setWellRecoveryRate(double wellRecoveryRate) {
    return getImpl<detail::WaterUseWell_Impl>()->setWellRecoveryRate(wellRecoveryRate);
  }

  boost::optional<double> WaterUseWell::nominalWellStorageVolume() const {
    return getImpl<detail::WaterUseWell_Impl>()->nominalWellStorageVolume();
  }

  bool WaterUseWell::setNominalWellStorageVolume(double nominalWellStorageVolume) {
    return getImpl<detail::WaterUseWell_Impl>()->setNominalWellStorageVolume(nominalWellStorageVolume);
  }

  boost::optional<std::string> WaterUseWell::waterTableDepthMode() const {
    return getImpl<detail::WaterUseWell_Impl>()->waterTableDepthMode();
  }

  bool WaterUseWell::setWaterTableDepthMode(const std::string& waterTableDepthMode) {
    return getImpl<detail::WaterUseWell_Impl>()->setWaterTableDepthMode(waterTableDepthMode);
  }

  boost::optional<double> WaterUseWell::waterTableDepth() const {
    return getImpl<detail::WaterUseWell_Impl>()->waterTableDepth();
  }

  bool WaterUseWell::setWaterTableDepth(double waterTableDepth) {
    return getImpl<detail::WaterUseWell_Impl>()->setWaterTableDepth(waterTableDepth);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> WaterUseWell_Impl::pumpDepth() const {
      return getDouble(openstudio::WaterUse_WellFields::PumpDepth, true);
    }

    bool WaterUseWell_Impl::setPumpDepth(double pumpDepth) {
      return setDouble(openstudio::WaterUse_WellFields::PumpDepth, pumpDepth);
    }

    boost::optional<double> WaterUseWell_Impl::pumpRatedFlowRate() const {
      return getDouble(openstudio::WaterUse_WellFields::PumpRatedFlowRate, true);
    }

    bool WaterUseWell_Impl::setPumpRatedFlowRate(double pumpRatedFlowRate) {
      return setDouble(openstudio::WaterUse_WellFields::PumpRatedFlowRate, pumpRatedFlowRate);
    }

    boost::optional<double> WaterUseWell_Impl::pumpRatedHead() const {
      return getDouble(openstudio::WaterUse_WellFields::PumpRatedHead, true);
    }

    bool WaterUseWell_Impl::setPumpRatedHead(double pumpRatedHead) {
      return setDouble(openstudio::WaterUse_WellFields::PumpRatedHead, pumpRatedHead);
    }

    boost::optional<double> WaterUseWell_Impl::pumpRatedPowerConsumption() const {
      return getDouble(openstudio::WaterUse_WellFields::PumpRatedPowerConsumption, true);
    }

    bool WaterUseWell_Impl::setPumpRatedPowerConsumption(double pumpRatedPowerConsumption) {
      return setDouble(openstudio::WaterUse_WellFields::PumpRatedPowerConsumption, pumpRatedPowerConsumption);
    }

    boost::optional<double> WaterUseWell_Impl::pumpEfficiency() const {
      return getDouble(openstudio::WaterUse_WellFields::PumpEfficiency, true);
    }

    bool WaterUseWell_Impl::setPumpEfficiency(double pumpEfficiency) {
      return setDouble(openstudio::WaterUse_WellFields::PumpEfficiency, pumpEfficiency);
    }

    boost::optional<double> WaterUseWell_Impl::wellRecoveryRate() const {
      return getDouble(openstudio::WaterUse_WellFields::WellRecoveryRate, true);
    }

    bool WaterUseWell_Impl::setWellRecoveryRate(double wellRecoveryRate) {
      return setDouble(openstudio::WaterUse_WellFields::WellRecoveryRate, wellRecoveryRate);
    }

    boost::optional<double> WaterUseWell_Impl::nominalWellStorageVolume() const {
      return getDouble(openstudio::WaterUse_WellFields::NominalWellStorageVolume, true);
    }

    bool WaterUseWell_Impl::setNominalWellStorageVolume(double nominalWellStorageVolume) {
      return setDouble(openstudio::WaterUse_WellFields::NominalWellStorageVolume, nominalWellStorageVolume);
    }

    boost::optional<std::string> WaterUseWell_Impl::waterTableDepthMode() const {
      return getString(openstudio::WaterUse_WellFields::WaterTableDepthMode, true);
    }

    bool WaterUseWell_Impl::setWaterTableDepthMode(const std::string& waterTableDepthMode) {
      return setString(openstudio::WaterUse_WellFields::WaterTableDepthMode, waterTableDepthMode);
    }

    std::vector<std::string> WaterUseWell_Impl::waterTableDepthModeValues() const {
      return openstudio::epmodel::WaterUseWell::waterTableDepthModeValues();
    }

    boost::optional<double> WaterUseWell_Impl::waterTableDepth() const {
      return getDouble(openstudio::WaterUse_WellFields::WaterTableDepth, true);
    }

    bool WaterUseWell_Impl::setWaterTableDepth(double waterTableDepth) {
      return setDouble(openstudio::WaterUse_WellFields::WaterTableDepth, waterTableDepth);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
