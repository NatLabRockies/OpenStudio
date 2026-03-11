/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/WaterUseStorage.hpp"
#include "ModelObject/WaterUseStorage_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WaterUse_Storage_FieldEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  WaterUseStorage::WaterUseStorage(const Model& model) : ModelObject(WaterUseStorage::iddObjectType(), model) {}

  WaterUseStorage::WaterUseStorage(std::shared_ptr<detail::WaterUseStorage_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType WaterUseStorage::iddObjectType() {
    return IddObjectType::WaterUse_Storage;
  }

  std::vector<std::string> WaterUseStorage::typeOfSupplyControlledByFloatValveValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterUse_StorageFields::TypeofSupplyControlledbyFloatValve);
  }

  std::vector<std::string> WaterUseStorage::waterThermalModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterUse_StorageFields::WaterThermalMode);
  }

  std::vector<std::string> WaterUseStorage::ambientTemperatureIndicatorValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterUse_StorageFields::AmbientTemperatureIndicator);
  }

  boost::optional<std::string> WaterUseStorage::waterQualitySubcategory() const {
    return getImpl<detail::WaterUseStorage_Impl>()->waterQualitySubcategory();
  }

  bool WaterUseStorage::setWaterQualitySubcategory(const std::string& waterQualitySubcategory) {
    return getImpl<detail::WaterUseStorage_Impl>()->setWaterQualitySubcategory(waterQualitySubcategory);
  }

  boost::optional<double> WaterUseStorage::maximumCapacity() const {
    return getImpl<detail::WaterUseStorage_Impl>()->maximumCapacity();
  }

  bool WaterUseStorage::setMaximumCapacity(double maximumCapacity) {
    return getImpl<detail::WaterUseStorage_Impl>()->setMaximumCapacity(maximumCapacity);
  }

  boost::optional<double> WaterUseStorage::initialVolume() const {
    return getImpl<detail::WaterUseStorage_Impl>()->initialVolume();
  }

  bool WaterUseStorage::setInitialVolume(double initialVolume) {
    return getImpl<detail::WaterUseStorage_Impl>()->setInitialVolume(initialVolume);
  }

  boost::optional<double> WaterUseStorage::designInFlowRate() const {
    return getImpl<detail::WaterUseStorage_Impl>()->designInFlowRate();
  }

  bool WaterUseStorage::setDesignInFlowRate(double designInFlowRate) {
    return getImpl<detail::WaterUseStorage_Impl>()->setDesignInFlowRate(designInFlowRate);
  }

  boost::optional<double> WaterUseStorage::designOutFlowRate() const {
    return getImpl<detail::WaterUseStorage_Impl>()->designOutFlowRate();
  }

  bool WaterUseStorage::setDesignOutFlowRate(double designOutFlowRate) {
    return getImpl<detail::WaterUseStorage_Impl>()->setDesignOutFlowRate(designOutFlowRate);
  }

  boost::optional<std::string> WaterUseStorage::typeOfSupplyControlledByFloatValve() const {
    return getImpl<detail::WaterUseStorage_Impl>()->typeOfSupplyControlledByFloatValve();
  }

  bool WaterUseStorage::setTypeOfSupplyControlledByFloatValve(const std::string& typeOfSupplyControlledByFloatValve) {
    return getImpl<detail::WaterUseStorage_Impl>()->setTypeOfSupplyControlledByFloatValve(typeOfSupplyControlledByFloatValve);
  }

  boost::optional<double> WaterUseStorage::floatValveOnCapacity() const {
    return getImpl<detail::WaterUseStorage_Impl>()->floatValveOnCapacity();
  }

  bool WaterUseStorage::setFloatValveOnCapacity(double floatValveOnCapacity) {
    return getImpl<detail::WaterUseStorage_Impl>()->setFloatValveOnCapacity(floatValveOnCapacity);
  }

  boost::optional<double> WaterUseStorage::floatValveOffCapacity() const {
    return getImpl<detail::WaterUseStorage_Impl>()->floatValveOffCapacity();
  }

  bool WaterUseStorage::setFloatValveOffCapacity(double floatValveOffCapacity) {
    return getImpl<detail::WaterUseStorage_Impl>()->setFloatValveOffCapacity(floatValveOffCapacity);
  }

  boost::optional<double> WaterUseStorage::backupMainsCapacity() const {
    return getImpl<detail::WaterUseStorage_Impl>()->backupMainsCapacity();
  }

  bool WaterUseStorage::setBackupMainsCapacity(double backupMainsCapacity) {
    return getImpl<detail::WaterUseStorage_Impl>()->setBackupMainsCapacity(backupMainsCapacity);
  }

  boost::optional<std::string> WaterUseStorage::waterThermalMode() const {
    return getImpl<detail::WaterUseStorage_Impl>()->waterThermalMode();
  }

  bool WaterUseStorage::setWaterThermalMode(const std::string& waterThermalMode) {
    return getImpl<detail::WaterUseStorage_Impl>()->setWaterThermalMode(waterThermalMode);
  }

  boost::optional<std::string> WaterUseStorage::ambientTemperatureIndicator() const {
    return getImpl<detail::WaterUseStorage_Impl>()->ambientTemperatureIndicator();
  }

  bool WaterUseStorage::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
    return getImpl<detail::WaterUseStorage_Impl>()->setAmbientTemperatureIndicator(ambientTemperatureIndicator);
  }

  boost::optional<double> WaterUseStorage::tankSurfaceArea() const {
    return getImpl<detail::WaterUseStorage_Impl>()->tankSurfaceArea();
  }

  bool WaterUseStorage::setTankSurfaceArea(double tankSurfaceArea) {
    return getImpl<detail::WaterUseStorage_Impl>()->setTankSurfaceArea(tankSurfaceArea);
  }

  boost::optional<double> WaterUseStorage::tankUValue() const {
    return getImpl<detail::WaterUseStorage_Impl>()->tankUValue();
  }

  bool WaterUseStorage::setTankUValue(double tankUValue) {
    return getImpl<detail::WaterUseStorage_Impl>()->setTankUValue(tankUValue);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<std::string> WaterUseStorage_Impl::waterQualitySubcategory() const {
      return getString(openstudio::WaterUse_StorageFields::WaterQualitySubcategory, true);
    }

    bool WaterUseStorage_Impl::setWaterQualitySubcategory(const std::string& waterQualitySubcategory) {
      return setString(openstudio::WaterUse_StorageFields::WaterQualitySubcategory, waterQualitySubcategory);
    }

    boost::optional<double> WaterUseStorage_Impl::maximumCapacity() const {
      return getDouble(openstudio::WaterUse_StorageFields::MaximumCapacity, true);
    }

    bool WaterUseStorage_Impl::setMaximumCapacity(double maximumCapacity) {
      return setDouble(openstudio::WaterUse_StorageFields::MaximumCapacity, maximumCapacity);
    }

    boost::optional<double> WaterUseStorage_Impl::initialVolume() const {
      return getDouble(openstudio::WaterUse_StorageFields::InitialVolume, true);
    }

    bool WaterUseStorage_Impl::setInitialVolume(double initialVolume) {
      return setDouble(openstudio::WaterUse_StorageFields::InitialVolume, initialVolume);
    }

    boost::optional<double> WaterUseStorage_Impl::designInFlowRate() const {
      return getDouble(openstudio::WaterUse_StorageFields::DesignInFlowRate, true);
    }

    bool WaterUseStorage_Impl::setDesignInFlowRate(double designInFlowRate) {
      return setDouble(openstudio::WaterUse_StorageFields::DesignInFlowRate, designInFlowRate);
    }

    boost::optional<double> WaterUseStorage_Impl::designOutFlowRate() const {
      return getDouble(openstudio::WaterUse_StorageFields::DesignOutFlowRate, true);
    }

    bool WaterUseStorage_Impl::setDesignOutFlowRate(double designOutFlowRate) {
      return setDouble(openstudio::WaterUse_StorageFields::DesignOutFlowRate, designOutFlowRate);
    }

    boost::optional<std::string> WaterUseStorage_Impl::typeOfSupplyControlledByFloatValve() const {
      return getString(openstudio::WaterUse_StorageFields::TypeofSupplyControlledbyFloatValve, true);
    }

    bool WaterUseStorage_Impl::setTypeOfSupplyControlledByFloatValve(const std::string& typeOfSupplyControlledByFloatValve) {
      return setString(openstudio::WaterUse_StorageFields::TypeofSupplyControlledbyFloatValve, typeOfSupplyControlledByFloatValve);
    }

    std::vector<std::string> WaterUseStorage_Impl::typeOfSupplyControlledByFloatValveValues() const {
      return openstudio::epmodel::WaterUseStorage::typeOfSupplyControlledByFloatValveValues();
    }

    boost::optional<double> WaterUseStorage_Impl::floatValveOnCapacity() const {
      return getDouble(openstudio::WaterUse_StorageFields::FloatValveOnCapacity, true);
    }

    bool WaterUseStorage_Impl::setFloatValveOnCapacity(double floatValveOnCapacity) {
      return setDouble(openstudio::WaterUse_StorageFields::FloatValveOnCapacity, floatValveOnCapacity);
    }

    boost::optional<double> WaterUseStorage_Impl::floatValveOffCapacity() const {
      return getDouble(openstudio::WaterUse_StorageFields::FloatValveOffCapacity, true);
    }

    bool WaterUseStorage_Impl::setFloatValveOffCapacity(double floatValveOffCapacity) {
      return setDouble(openstudio::WaterUse_StorageFields::FloatValveOffCapacity, floatValveOffCapacity);
    }

    boost::optional<double> WaterUseStorage_Impl::backupMainsCapacity() const {
      return getDouble(openstudio::WaterUse_StorageFields::BackupMainsCapacity, true);
    }

    bool WaterUseStorage_Impl::setBackupMainsCapacity(double backupMainsCapacity) {
      return setDouble(openstudio::WaterUse_StorageFields::BackupMainsCapacity, backupMainsCapacity);
    }

    boost::optional<std::string> WaterUseStorage_Impl::waterThermalMode() const {
      return getString(openstudio::WaterUse_StorageFields::WaterThermalMode, true);
    }

    bool WaterUseStorage_Impl::setWaterThermalMode(const std::string& waterThermalMode) {
      return setString(openstudio::WaterUse_StorageFields::WaterThermalMode, waterThermalMode);
    }

    std::vector<std::string> WaterUseStorage_Impl::waterThermalModeValues() const {
      return openstudio::epmodel::WaterUseStorage::waterThermalModeValues();
    }

    boost::optional<std::string> WaterUseStorage_Impl::ambientTemperatureIndicator() const {
      return getString(openstudio::WaterUse_StorageFields::AmbientTemperatureIndicator, true);
    }

    bool WaterUseStorage_Impl::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
      return setString(openstudio::WaterUse_StorageFields::AmbientTemperatureIndicator, ambientTemperatureIndicator);
    }

    std::vector<std::string> WaterUseStorage_Impl::ambientTemperatureIndicatorValues() const {
      return openstudio::epmodel::WaterUseStorage::ambientTemperatureIndicatorValues();
    }

    boost::optional<double> WaterUseStorage_Impl::tankSurfaceArea() const {
      return getDouble(openstudio::WaterUse_StorageFields::TankSurfaceArea, true);
    }

    bool WaterUseStorage_Impl::setTankSurfaceArea(double tankSurfaceArea) {
      return setDouble(openstudio::WaterUse_StorageFields::TankSurfaceArea, tankSurfaceArea);
    }

    boost::optional<double> WaterUseStorage_Impl::tankUValue() const {
      return getDouble(openstudio::WaterUse_StorageFields::TankUValue, true);
    }

    bool WaterUseStorage_Impl::setTankUValue(double tankUValue) {
      return setDouble(openstudio::WaterUse_StorageFields::TankUValue, tankUValue);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
