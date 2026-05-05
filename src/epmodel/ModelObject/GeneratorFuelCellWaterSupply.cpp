/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorFuelCellWaterSupply.hpp"
#include "GeneratorFuelCellWaterSupply_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_FuelCell_WaterSupply_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  GeneratorFuelCellWaterSupply::GeneratorFuelCellWaterSupply(const Model& model) : ModelObject(GeneratorFuelCellWaterSupply::iddObjectType(), model) {
    // Keep existing model API non-optional getters strict by populating scalar defaults.
    OS_ASSERT(setPumpHeatLossFactor(0.0));
    OS_ASSERT(setWaterTemperatureModelingMode("TemperatureFromSchedule"));
  }

  GeneratorFuelCellWaterSupply::GeneratorFuelCellWaterSupply(std::shared_ptr<detail::GeneratorFuelCellWaterSupply_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GeneratorFuelCellWaterSupply::iddObjectType() {
    return IddObjectType::Generator_FuelCell_WaterSupply;
  }

  std::vector<std::string> GeneratorFuelCellWaterSupply::waterTemperatureModelingModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Generator_FuelCell_WaterSupplyFields::WaterTemperatureModelingMode);
  }

  double GeneratorFuelCellWaterSupply::pumpHeatLossFactor() const {
    return getImpl<detail::GeneratorFuelCellWaterSupply_Impl>()->pumpHeatLossFactor();
  }

  bool GeneratorFuelCellWaterSupply::setPumpHeatLossFactor(double pumpHeatLossFactor) {
    return getImpl<detail::GeneratorFuelCellWaterSupply_Impl>()->setPumpHeatLossFactor(pumpHeatLossFactor);
  }

  void GeneratorFuelCellWaterSupply::resetPumpHeatLossFactor() {
    getImpl<detail::GeneratorFuelCellWaterSupply_Impl>()->resetPumpHeatLossFactor();
  }

  std::string GeneratorFuelCellWaterSupply::waterTemperatureModelingMode() const {
    return getImpl<detail::GeneratorFuelCellWaterSupply_Impl>()->waterTemperatureModelingMode();
  }

  bool GeneratorFuelCellWaterSupply::setWaterTemperatureModelingMode(const std::string& waterTemperatureModelingMode) {
    return getImpl<detail::GeneratorFuelCellWaterSupply_Impl>()->setWaterTemperatureModelingMode(waterTemperatureModelingMode);
  }

  void GeneratorFuelCellWaterSupply::resetWaterTemperatureModelingMode() {
    getImpl<detail::GeneratorFuelCellWaterSupply_Impl>()->resetWaterTemperatureModelingMode();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double GeneratorFuelCellWaterSupply_Impl::pumpHeatLossFactor() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_WaterSupplyFields::PumpHeatLossFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellWaterSupply_Impl::setPumpHeatLossFactor(double pumpHeatLossFactor) {
      const bool result = setDouble(openstudio::Generator_FuelCell_WaterSupplyFields::PumpHeatLossFactor, pumpHeatLossFactor);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellWaterSupply_Impl::resetPumpHeatLossFactor() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_WaterSupplyFields::PumpHeatLossFactor, 0.0));
    }

    std::string GeneratorFuelCellWaterSupply_Impl::waterTemperatureModelingMode() const {
      const auto value = getString(openstudio::Generator_FuelCell_WaterSupplyFields::WaterTemperatureModelingMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellWaterSupply_Impl::setWaterTemperatureModelingMode(const std::string& waterTemperatureModelingMode) {
      return setString(openstudio::Generator_FuelCell_WaterSupplyFields::WaterTemperatureModelingMode, waterTemperatureModelingMode);
    }

    void GeneratorFuelCellWaterSupply_Impl::resetWaterTemperatureModelingMode() {
      OS_ASSERT(setString(openstudio::Generator_FuelCell_WaterSupplyFields::WaterTemperatureModelingMode, "TemperatureFromSchedule"));
    }

    std::vector<std::string> GeneratorFuelCellWaterSupply_Impl::waterTemperatureModelingModeValues() const {
      return openstudio::epmodel::GeneratorFuelCellWaterSupply::waterTemperatureModelingModeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
