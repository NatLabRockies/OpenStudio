/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplatePlantTower.hpp"
#include "HVACTemplatePlantTower_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Plant_Tower_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplatePlantTower::HVACTemplatePlantTower(const Model& model) : ModelObject(HVACTemplatePlantTower::iddObjectType(), model) {}

  HVACTemplatePlantTower::HVACTemplatePlantTower(std::shared_ptr<detail::HVACTemplatePlantTower_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplatePlantTower::iddObjectType() {
    return IddObjectType::HVACTemplate_Plant_Tower;
  }

  std::vector<std::string> HVACTemplatePlantTower::towerTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Plant_TowerFields::TowerType);
  }

  std::vector<std::string> HVACTemplatePlantTower::templatePlantLoopTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Plant_TowerFields::TemplatePlantLoopType);
  }

  std::string HVACTemplatePlantTower::towerType() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->towerType();
  }

  bool HVACTemplatePlantTower::setTowerType(const std::string& towerType) {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->setTowerType(towerType);
  }

  boost::optional<double> HVACTemplatePlantTower::highSpeedNominalCapacity() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->highSpeedNominalCapacity();
  }

  bool HVACTemplatePlantTower::isHighSpeedNominalCapacityDefaulted() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->isHighSpeedNominalCapacityDefaulted();
  }

  bool HVACTemplatePlantTower::isHighSpeedNominalCapacityAutosized() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->isHighSpeedNominalCapacityAutosized();
  }

  bool HVACTemplatePlantTower::setHighSpeedNominalCapacity(double highSpeedNominalCapacity) {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->setHighSpeedNominalCapacity(highSpeedNominalCapacity);
  }

  void HVACTemplatePlantTower::resetHighSpeedNominalCapacity() {
    getImpl<detail::HVACTemplatePlantTower_Impl>()->resetHighSpeedNominalCapacity();
  }

  void HVACTemplatePlantTower::autosizeHighSpeedNominalCapacity() {
    getImpl<detail::HVACTemplatePlantTower_Impl>()->autosizeHighSpeedNominalCapacity();
  }

  boost::optional<double> HVACTemplatePlantTower::highSpeedFanPower() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->highSpeedFanPower();
  }

  bool HVACTemplatePlantTower::isHighSpeedFanPowerDefaulted() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->isHighSpeedFanPowerDefaulted();
  }

  bool HVACTemplatePlantTower::isHighSpeedFanPowerAutosized() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->isHighSpeedFanPowerAutosized();
  }

  bool HVACTemplatePlantTower::setHighSpeedFanPower(double highSpeedFanPower) {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->setHighSpeedFanPower(highSpeedFanPower);
  }

  void HVACTemplatePlantTower::resetHighSpeedFanPower() {
    getImpl<detail::HVACTemplatePlantTower_Impl>()->resetHighSpeedFanPower();
  }

  void HVACTemplatePlantTower::autosizeHighSpeedFanPower() {
    getImpl<detail::HVACTemplatePlantTower_Impl>()->autosizeHighSpeedFanPower();
  }

  boost::optional<double> HVACTemplatePlantTower::lowSpeedNominalCapacity() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->lowSpeedNominalCapacity();
  }

  bool HVACTemplatePlantTower::isLowSpeedNominalCapacityDefaulted() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->isLowSpeedNominalCapacityDefaulted();
  }

  bool HVACTemplatePlantTower::isLowSpeedNominalCapacityAutosized() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->isLowSpeedNominalCapacityAutosized();
  }

  bool HVACTemplatePlantTower::setLowSpeedNominalCapacity(double lowSpeedNominalCapacity) {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->setLowSpeedNominalCapacity(lowSpeedNominalCapacity);
  }

  void HVACTemplatePlantTower::resetLowSpeedNominalCapacity() {
    getImpl<detail::HVACTemplatePlantTower_Impl>()->resetLowSpeedNominalCapacity();
  }

  void HVACTemplatePlantTower::autosizeLowSpeedNominalCapacity() {
    getImpl<detail::HVACTemplatePlantTower_Impl>()->autosizeLowSpeedNominalCapacity();
  }

  boost::optional<double> HVACTemplatePlantTower::lowSpeedFanPower() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->lowSpeedFanPower();
  }

  bool HVACTemplatePlantTower::isLowSpeedFanPowerDefaulted() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->isLowSpeedFanPowerDefaulted();
  }

  bool HVACTemplatePlantTower::isLowSpeedFanPowerAutosized() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->isLowSpeedFanPowerAutosized();
  }

  bool HVACTemplatePlantTower::setLowSpeedFanPower(double lowSpeedFanPower) {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->setLowSpeedFanPower(lowSpeedFanPower);
  }

  void HVACTemplatePlantTower::resetLowSpeedFanPower() {
    getImpl<detail::HVACTemplatePlantTower_Impl>()->resetLowSpeedFanPower();
  }

  void HVACTemplatePlantTower::autosizeLowSpeedFanPower() {
    getImpl<detail::HVACTemplatePlantTower_Impl>()->autosizeLowSpeedFanPower();
  }

  boost::optional<double> HVACTemplatePlantTower::freeConvectionCapacity() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->freeConvectionCapacity();
  }

  bool HVACTemplatePlantTower::isFreeConvectionCapacityDefaulted() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->isFreeConvectionCapacityDefaulted();
  }

  bool HVACTemplatePlantTower::isFreeConvectionCapacityAutosized() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->isFreeConvectionCapacityAutosized();
  }

  bool HVACTemplatePlantTower::setFreeConvectionCapacity(double freeConvectionCapacity) {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->setFreeConvectionCapacity(freeConvectionCapacity);
  }

  void HVACTemplatePlantTower::resetFreeConvectionCapacity() {
    getImpl<detail::HVACTemplatePlantTower_Impl>()->resetFreeConvectionCapacity();
  }

  void HVACTemplatePlantTower::autosizeFreeConvectionCapacity() {
    getImpl<detail::HVACTemplatePlantTower_Impl>()->autosizeFreeConvectionCapacity();
  }

  boost::optional<std::string> HVACTemplatePlantTower::priority() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->priority();
  }

  bool HVACTemplatePlantTower::setPriority(const std::string& priority) {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->setPriority(priority);
  }

  void HVACTemplatePlantTower::resetPriority() {
    getImpl<detail::HVACTemplatePlantTower_Impl>()->resetPriority();
  }

  double HVACTemplatePlantTower::sizingFactor() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->sizingFactor();
  }

  bool HVACTemplatePlantTower::isSizingFactorDefaulted() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->isSizingFactorDefaulted();
  }

  bool HVACTemplatePlantTower::setSizingFactor(double sizingFactor) {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->setSizingFactor(sizingFactor);
  }

  void HVACTemplatePlantTower::resetSizingFactor() {
    getImpl<detail::HVACTemplatePlantTower_Impl>()->resetSizingFactor();
  }

  boost::optional<std::string> HVACTemplatePlantTower::templatePlantLoopType() const {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->templatePlantLoopType();
  }

  bool HVACTemplatePlantTower::setTemplatePlantLoopType(const std::string& templatePlantLoopType) {
    return getImpl<detail::HVACTemplatePlantTower_Impl>()->setTemplatePlantLoopType(templatePlantLoopType);
  }

  void HVACTemplatePlantTower::resetTemplatePlantLoopType() {
    getImpl<detail::HVACTemplatePlantTower_Impl>()->resetTemplatePlantLoopType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string HVACTemplatePlantTower_Impl::towerType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_TowerFields::TowerType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantTower_Impl::setTowerType(const std::string& towerType) {
      return setString(openstudio::HVACTemplate_Plant_TowerFields::TowerType, towerType);
    }

    boost::optional<double> HVACTemplatePlantTower_Impl::highSpeedNominalCapacity() const {
      return getDouble(openstudio::HVACTemplate_Plant_TowerFields::HighSpeedNominalCapacity, true);
    }

    bool HVACTemplatePlantTower_Impl::isHighSpeedNominalCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_TowerFields::HighSpeedNominalCapacity);
    }

    bool HVACTemplatePlantTower_Impl::isHighSpeedNominalCapacityAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Plant_TowerFields::HighSpeedNominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplatePlantTower_Impl::setHighSpeedNominalCapacity(double highSpeedNominalCapacity) {
      return setDouble(openstudio::HVACTemplate_Plant_TowerFields::HighSpeedNominalCapacity, highSpeedNominalCapacity);
    }

    void HVACTemplatePlantTower_Impl::resetHighSpeedNominalCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_TowerFields::HighSpeedNominalCapacity, ""));
    }

    void HVACTemplatePlantTower_Impl::autosizeHighSpeedNominalCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_TowerFields::HighSpeedNominalCapacity, "autosize"));
    }

    boost::optional<double> HVACTemplatePlantTower_Impl::highSpeedFanPower() const {
      return getDouble(openstudio::HVACTemplate_Plant_TowerFields::HighSpeedFanPower, true);
    }

    bool HVACTemplatePlantTower_Impl::isHighSpeedFanPowerDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_TowerFields::HighSpeedFanPower);
    }

    bool HVACTemplatePlantTower_Impl::isHighSpeedFanPowerAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Plant_TowerFields::HighSpeedFanPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplatePlantTower_Impl::setHighSpeedFanPower(double highSpeedFanPower) {
      return setDouble(openstudio::HVACTemplate_Plant_TowerFields::HighSpeedFanPower, highSpeedFanPower);
    }

    void HVACTemplatePlantTower_Impl::resetHighSpeedFanPower() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_TowerFields::HighSpeedFanPower, ""));
    }

    void HVACTemplatePlantTower_Impl::autosizeHighSpeedFanPower() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_TowerFields::HighSpeedFanPower, "autosize"));
    }

    boost::optional<double> HVACTemplatePlantTower_Impl::lowSpeedNominalCapacity() const {
      return getDouble(openstudio::HVACTemplate_Plant_TowerFields::LowSpeedNominalCapacity, true);
    }

    bool HVACTemplatePlantTower_Impl::isLowSpeedNominalCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_TowerFields::LowSpeedNominalCapacity);
    }

    bool HVACTemplatePlantTower_Impl::isLowSpeedNominalCapacityAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Plant_TowerFields::LowSpeedNominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplatePlantTower_Impl::setLowSpeedNominalCapacity(double lowSpeedNominalCapacity) {
      return setDouble(openstudio::HVACTemplate_Plant_TowerFields::LowSpeedNominalCapacity, lowSpeedNominalCapacity);
    }

    void HVACTemplatePlantTower_Impl::resetLowSpeedNominalCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_TowerFields::LowSpeedNominalCapacity, ""));
    }

    void HVACTemplatePlantTower_Impl::autosizeLowSpeedNominalCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_TowerFields::LowSpeedNominalCapacity, "autosize"));
    }

    boost::optional<double> HVACTemplatePlantTower_Impl::lowSpeedFanPower() const {
      return getDouble(openstudio::HVACTemplate_Plant_TowerFields::LowSpeedFanPower, true);
    }

    bool HVACTemplatePlantTower_Impl::isLowSpeedFanPowerDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_TowerFields::LowSpeedFanPower);
    }

    bool HVACTemplatePlantTower_Impl::isLowSpeedFanPowerAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Plant_TowerFields::LowSpeedFanPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplatePlantTower_Impl::setLowSpeedFanPower(double lowSpeedFanPower) {
      return setDouble(openstudio::HVACTemplate_Plant_TowerFields::LowSpeedFanPower, lowSpeedFanPower);
    }

    void HVACTemplatePlantTower_Impl::resetLowSpeedFanPower() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_TowerFields::LowSpeedFanPower, ""));
    }

    void HVACTemplatePlantTower_Impl::autosizeLowSpeedFanPower() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_TowerFields::LowSpeedFanPower, "autosize"));
    }

    boost::optional<double> HVACTemplatePlantTower_Impl::freeConvectionCapacity() const {
      return getDouble(openstudio::HVACTemplate_Plant_TowerFields::FreeConvectionCapacity, true);
    }

    bool HVACTemplatePlantTower_Impl::isFreeConvectionCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_TowerFields::FreeConvectionCapacity);
    }

    bool HVACTemplatePlantTower_Impl::isFreeConvectionCapacityAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Plant_TowerFields::FreeConvectionCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplatePlantTower_Impl::setFreeConvectionCapacity(double freeConvectionCapacity) {
      return setDouble(openstudio::HVACTemplate_Plant_TowerFields::FreeConvectionCapacity, freeConvectionCapacity);
    }

    void HVACTemplatePlantTower_Impl::resetFreeConvectionCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_TowerFields::FreeConvectionCapacity, ""));
    }

    void HVACTemplatePlantTower_Impl::autosizeFreeConvectionCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_TowerFields::FreeConvectionCapacity, "autosize"));
    }

    boost::optional<std::string> HVACTemplatePlantTower_Impl::priority() const {
      return getString(openstudio::HVACTemplate_Plant_TowerFields::Priority, true);
    }

    bool HVACTemplatePlantTower_Impl::setPriority(const std::string& priority) {
      const bool result = setString(openstudio::HVACTemplate_Plant_TowerFields::Priority, priority);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplatePlantTower_Impl::resetPriority() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_TowerFields::Priority, ""));
    }

    double HVACTemplatePlantTower_Impl::sizingFactor() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_TowerFields::SizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantTower_Impl::isSizingFactorDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_TowerFields::SizingFactor);
    }

    bool HVACTemplatePlantTower_Impl::setSizingFactor(double sizingFactor) {
      return setDouble(openstudio::HVACTemplate_Plant_TowerFields::SizingFactor, sizingFactor);
    }

    void HVACTemplatePlantTower_Impl::resetSizingFactor() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_TowerFields::SizingFactor, ""));
    }

    boost::optional<std::string> HVACTemplatePlantTower_Impl::templatePlantLoopType() const {
      return getString(openstudio::HVACTemplate_Plant_TowerFields::TemplatePlantLoopType, true);
    }

    bool HVACTemplatePlantTower_Impl::setTemplatePlantLoopType(const std::string& templatePlantLoopType) {
      return setString(openstudio::HVACTemplate_Plant_TowerFields::TemplatePlantLoopType, templatePlantLoopType);
    }

    void HVACTemplatePlantTower_Impl::resetTemplatePlantLoopType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_TowerFields::TemplatePlantLoopType, ""));
    }

    std::vector<std::string> HVACTemplatePlantTower_Impl::towerTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantTower::towerTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantTower_Impl::templatePlantLoopTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantTower::templatePlantLoopTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
