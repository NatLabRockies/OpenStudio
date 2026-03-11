/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/MaterialPropertyHeatAndMoistureTransferSettings.hpp"
#include "ModelObject/MaterialPropertyHeatAndMoistureTransferSettings_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/MaterialProperty_HeatAndMoistureTransfer_Settings_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

MaterialPropertyHeatAndMoistureTransferSettings::MaterialPropertyHeatAndMoistureTransferSettings(const Model& model)
  : ModelObject(MaterialPropertyHeatAndMoistureTransferSettings::iddObjectType(), model) {}

MaterialPropertyHeatAndMoistureTransferSettings::MaterialPropertyHeatAndMoistureTransferSettings(
  std::shared_ptr<detail::MaterialPropertyHeatAndMoistureTransferSettings_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType MaterialPropertyHeatAndMoistureTransferSettings::iddObjectType() {
  return IddObjectType::MaterialProperty_HeatAndMoistureTransfer_Settings;
}

double MaterialPropertyHeatAndMoistureTransferSettings::porosity() const {
  return getImpl<detail::MaterialPropertyHeatAndMoistureTransferSettings_Impl>()->porosity();
}

bool MaterialPropertyHeatAndMoistureTransferSettings::setPorosity(double porosity) {
  return getImpl<detail::MaterialPropertyHeatAndMoistureTransferSettings_Impl>()->setPorosity(porosity);
}

double MaterialPropertyHeatAndMoistureTransferSettings::initialWaterContentRatio() const {
  return getImpl<detail::MaterialPropertyHeatAndMoistureTransferSettings_Impl>()->initialWaterContentRatio();
}

bool MaterialPropertyHeatAndMoistureTransferSettings::isInitialWaterContentRatioDefaulted() const {
  return getImpl<detail::MaterialPropertyHeatAndMoistureTransferSettings_Impl>()->isInitialWaterContentRatioDefaulted();
}

bool MaterialPropertyHeatAndMoistureTransferSettings::setInitialWaterContentRatio(double initialWaterContentRatio) {
  return getImpl<detail::MaterialPropertyHeatAndMoistureTransferSettings_Impl>()->setInitialWaterContentRatio(initialWaterContentRatio);
}

void MaterialPropertyHeatAndMoistureTransferSettings::resetInitialWaterContentRatio() {
  getImpl<detail::MaterialPropertyHeatAndMoistureTransferSettings_Impl>()->resetInitialWaterContentRatio();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double MaterialPropertyHeatAndMoistureTransferSettings_Impl::porosity() const {
  const auto value = getDouble(openstudio::MaterialProperty_HeatAndMoistureTransfer_SettingsFields::Porosity, true);
  OS_ASSERT(value);
  return *value;
}

bool MaterialPropertyHeatAndMoistureTransferSettings_Impl::setPorosity(double porosity) {
  return setDouble(openstudio::MaterialProperty_HeatAndMoistureTransfer_SettingsFields::Porosity, porosity);
}

double MaterialPropertyHeatAndMoistureTransferSettings_Impl::initialWaterContentRatio() const {
  const auto value = getDouble(openstudio::MaterialProperty_HeatAndMoistureTransfer_SettingsFields::InitialWaterContentRatio, true);
  OS_ASSERT(value);
  return *value;
}

bool MaterialPropertyHeatAndMoistureTransferSettings_Impl::isInitialWaterContentRatioDefaulted() const {
  return isEmpty(openstudio::MaterialProperty_HeatAndMoistureTransfer_SettingsFields::InitialWaterContentRatio);
}

bool MaterialPropertyHeatAndMoistureTransferSettings_Impl::setInitialWaterContentRatio(double initialWaterContentRatio) {
  return setDouble(openstudio::MaterialProperty_HeatAndMoistureTransfer_SettingsFields::InitialWaterContentRatio,
                   initialWaterContentRatio);
}

void MaterialPropertyHeatAndMoistureTransferSettings_Impl::resetInitialWaterContentRatio() {
  OS_ASSERT(setString(openstudio::MaterialProperty_HeatAndMoistureTransfer_SettingsFields::InitialWaterContentRatio, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
