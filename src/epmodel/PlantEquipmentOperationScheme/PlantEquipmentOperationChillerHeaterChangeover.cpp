/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlantEquipmentOperationScheme/PlantEquipmentOperationChillerHeaterChangeover.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationChillerHeaterChangeover_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/PlantEquipmentOperation_ChillerHeaterChangeover_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PlantEquipmentOperationChillerHeaterChangeover::PlantEquipmentOperationChillerHeaterChangeover(const Model& model)
    : PlantEquipmentOperationScheme(PlantEquipmentOperationChillerHeaterChangeover::iddObjectType(), model) {
    OS_ASSERT(setPrimaryCoolingPlantSetpointTemperature(7.0));
    OS_ASSERT(setPrimaryHeatingPlantSetpointatOutdoorHighTemperature(55.0));
    OS_ASSERT(setOutdoorHighTemperature(30.0));
    OS_ASSERT(setPrimaryHeatingPlantSetpointatOutdoorLowTemperature(35.0));
    OS_ASSERT(setOutdoorLowTemperature(0.0));
  }

  PlantEquipmentOperationChillerHeaterChangeover::PlantEquipmentOperationChillerHeaterChangeover(
    std::shared_ptr<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl> impl)
    : PlantEquipmentOperationScheme(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationChillerHeaterChangeover::iddObjectType() {
    return IddObjectType("PlantEquipmentOperation_ChillerHeaterChangeover");
  }

  double PlantEquipmentOperationChillerHeaterChangeover::primaryCoolingPlantSetpointTemperature() const {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->primaryCoolingPlantSetpointTemperature();
  }

  bool PlantEquipmentOperationChillerHeaterChangeover::setPrimaryCoolingPlantSetpointTemperature(double primaryCoolingPlantSetpointTemperature) {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->setPrimaryCoolingPlantSetpointTemperature(
      primaryCoolingPlantSetpointTemperature);
  }

  boost::optional<double> PlantEquipmentOperationChillerHeaterChangeover::secondaryDistributionCoolingPlantSetpointTemperature() const {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->secondaryDistributionCoolingPlantSetpointTemperature();
  }

  bool PlantEquipmentOperationChillerHeaterChangeover::setSecondaryDistributionCoolingPlantSetpointTemperature(
    double secondaryDistributionCoolingPlantSetpointTemperature) {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->setSecondaryDistributionCoolingPlantSetpointTemperature(
      secondaryDistributionCoolingPlantSetpointTemperature);
  }

  void PlantEquipmentOperationChillerHeaterChangeover::resetSecondaryDistributionCoolingPlantSetpointTemperature() {
    getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->resetSecondaryDistributionCoolingPlantSetpointTemperature();
  }

  double PlantEquipmentOperationChillerHeaterChangeover::primaryHeatingPlantSetpointatOutdoorHighTemperature() const {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->primaryHeatingPlantSetpointatOutdoorHighTemperature();
  }

  bool PlantEquipmentOperationChillerHeaterChangeover::setPrimaryHeatingPlantSetpointatOutdoorHighTemperature(
    double primaryHeatingPlantSetpointatOutdoorHighTemperature) {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->setPrimaryHeatingPlantSetpointatOutdoorHighTemperature(
      primaryHeatingPlantSetpointatOutdoorHighTemperature);
  }

  double PlantEquipmentOperationChillerHeaterChangeover::outdoorHighTemperature() const {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->outdoorHighTemperature();
  }

  bool PlantEquipmentOperationChillerHeaterChangeover::setOutdoorHighTemperature(double outdoorHighTemperature) {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->setOutdoorHighTemperature(outdoorHighTemperature);
  }

  double PlantEquipmentOperationChillerHeaterChangeover::primaryHeatingPlantSetpointatOutdoorLowTemperature() const {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->primaryHeatingPlantSetpointatOutdoorLowTemperature();
  }

  bool PlantEquipmentOperationChillerHeaterChangeover::setPrimaryHeatingPlantSetpointatOutdoorLowTemperature(
    double primaryHeatingPlantSetpointatOutdoorLowTemperature) {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->setPrimaryHeatingPlantSetpointatOutdoorLowTemperature(
      primaryHeatingPlantSetpointatOutdoorLowTemperature);
  }

  double PlantEquipmentOperationChillerHeaterChangeover::outdoorLowTemperature() const {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->outdoorLowTemperature();
  }

  bool PlantEquipmentOperationChillerHeaterChangeover::setOutdoorLowTemperature(double outdoorLowTemperature) {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->setOutdoorLowTemperature(outdoorLowTemperature);
  }

  boost::optional<double> PlantEquipmentOperationChillerHeaterChangeover::secondaryDistributionHeatingPlantSetpointTemperature() const {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->secondaryDistributionHeatingPlantSetpointTemperature();
  }

  bool PlantEquipmentOperationChillerHeaterChangeover::setSecondaryDistributionHeatingPlantSetpointTemperature(
    double secondaryDistributionHeatingPlantSetpointTemperature) {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->setSecondaryDistributionHeatingPlantSetpointTemperature(
      secondaryDistributionHeatingPlantSetpointTemperature);
  }

  void PlantEquipmentOperationChillerHeaterChangeover::resetSecondaryDistributionHeatingPlantSetpointTemperature() {
    getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->resetSecondaryDistributionHeatingPlantSetpointTemperature();
  }

  double PlantEquipmentOperationChillerHeaterChangeover::boilerSetpointTemperatureOffset() const {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->boilerSetpointTemperatureOffset();
  }

  bool PlantEquipmentOperationChillerHeaterChangeover::setBoilerSetpointTemperatureOffset(double boilerSetpointTemperatureOffset) {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->setBoilerSetpointTemperatureOffset(
      boilerSetpointTemperatureOffset);
  }

  void PlantEquipmentOperationChillerHeaterChangeover::resetBoilerSetpointTemperatureOffset() {
    getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->resetBoilerSetpointTemperatureOffset();
  }

  bool PlantEquipmentOperationChillerHeaterChangeover::isBoilerSetpointTemperatureOffsetDefaulted() const {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->isBoilerSetpointTemperatureOffsetDefaulted();
  }

  boost::optional<double> PlantEquipmentOperationChillerHeaterChangeover::primaryHeatingPlantSetpointatBackupOutdoorLowTemperature() const {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->primaryHeatingPlantSetpointatBackupOutdoorLowTemperature();
  }

  bool PlantEquipmentOperationChillerHeaterChangeover::setPrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature(
    double primaryHeatingPlantSetpointatBackupOutdoorLowTemperature) {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->setPrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature(
      primaryHeatingPlantSetpointatBackupOutdoorLowTemperature);
  }

  void PlantEquipmentOperationChillerHeaterChangeover::resetPrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature() {
    getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->resetPrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature();
  }

  boost::optional<double> PlantEquipmentOperationChillerHeaterChangeover::backupOutdoorLowTemperature() const {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->backupOutdoorLowTemperature();
  }

  bool PlantEquipmentOperationChillerHeaterChangeover::setBackupOutdoorLowTemperature(double backupOutdoorLowTemperature) {
    return getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->setBackupOutdoorLowTemperature(backupOutdoorLowTemperature);
  }

  void PlantEquipmentOperationChillerHeaterChangeover::resetBackupOutdoorLowTemperature() {
    getImpl<detail::PlantEquipmentOperationChillerHeaterChangeover_Impl>()->resetBackupOutdoorLowTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double PlantEquipmentOperationChillerHeaterChangeover_Impl::primaryCoolingPlantSetpointTemperature() const {
      const auto value = getDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::PrimaryCoolingPlantSetpointTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool
      PlantEquipmentOperationChillerHeaterChangeover_Impl::setPrimaryCoolingPlantSetpointTemperature(double primaryCoolingPlantSetpointTemperature) {
      return setDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::PrimaryCoolingPlantSetpointTemperature,
                       primaryCoolingPlantSetpointTemperature);
    }

    boost::optional<double> PlantEquipmentOperationChillerHeaterChangeover_Impl::secondaryDistributionCoolingPlantSetpointTemperature() const {
      return getDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::SecondaryDistributionCoolingPlantSetpointTemperature);
    }

    bool PlantEquipmentOperationChillerHeaterChangeover_Impl::setSecondaryDistributionCoolingPlantSetpointTemperature(
      double secondaryDistributionCoolingPlantSetpointTemperature) {
      return setDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::SecondaryDistributionCoolingPlantSetpointTemperature,
                       secondaryDistributionCoolingPlantSetpointTemperature);
    }

    void PlantEquipmentOperationChillerHeaterChangeover_Impl::resetSecondaryDistributionCoolingPlantSetpointTemperature() {
      const bool result =
        setString(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::SecondaryDistributionCoolingPlantSetpointTemperature, "");
      OS_ASSERT(result);
    }

    double PlantEquipmentOperationChillerHeaterChangeover_Impl::primaryHeatingPlantSetpointatOutdoorHighTemperature() const {
      const auto value =
        getDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::PrimaryHeatingPlantSetpointatOutdoorHighTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantEquipmentOperationChillerHeaterChangeover_Impl::setPrimaryHeatingPlantSetpointatOutdoorHighTemperature(
      double primaryHeatingPlantSetpointatOutdoorHighTemperature) {
      return setDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::PrimaryHeatingPlantSetpointatOutdoorHighTemperature,
                       primaryHeatingPlantSetpointatOutdoorHighTemperature);
    }

    double PlantEquipmentOperationChillerHeaterChangeover_Impl::outdoorHighTemperature() const {
      const auto value = getDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::OutdoorHighTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantEquipmentOperationChillerHeaterChangeover_Impl::setOutdoorHighTemperature(double outdoorHighTemperature) {
      return setDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::OutdoorHighTemperature, outdoorHighTemperature);
    }

    double PlantEquipmentOperationChillerHeaterChangeover_Impl::primaryHeatingPlantSetpointatOutdoorLowTemperature() const {
      const auto value =
        getDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::PrimaryHeatingPlantSetpointatOutdoorLowTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantEquipmentOperationChillerHeaterChangeover_Impl::setPrimaryHeatingPlantSetpointatOutdoorLowTemperature(
      double primaryHeatingPlantSetpointatOutdoorLowTemperature) {
      return setDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::PrimaryHeatingPlantSetpointatOutdoorLowTemperature,
                       primaryHeatingPlantSetpointatOutdoorLowTemperature);
    }

    double PlantEquipmentOperationChillerHeaterChangeover_Impl::outdoorLowTemperature() const {
      const auto value = getDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::OutdoorLowTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantEquipmentOperationChillerHeaterChangeover_Impl::setOutdoorLowTemperature(double outdoorLowTemperature) {
      return setDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::OutdoorLowTemperature, outdoorLowTemperature);
    }

    boost::optional<double> PlantEquipmentOperationChillerHeaterChangeover_Impl::secondaryDistributionHeatingPlantSetpointTemperature() const {
      return getDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::SecondaryDistributionHeatingPlantSetpointTemperature);
    }

    bool PlantEquipmentOperationChillerHeaterChangeover_Impl::setSecondaryDistributionHeatingPlantSetpointTemperature(
      double secondaryDistributionHeatingPlantSetpointTemperature) {
      return setDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::SecondaryDistributionHeatingPlantSetpointTemperature,
                       secondaryDistributionHeatingPlantSetpointTemperature);
    }

    void PlantEquipmentOperationChillerHeaterChangeover_Impl::resetSecondaryDistributionHeatingPlantSetpointTemperature() {
      const bool result =
        setString(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::SecondaryDistributionHeatingPlantSetpointTemperature, "");
      OS_ASSERT(result);
    }

    double PlantEquipmentOperationChillerHeaterChangeover_Impl::boilerSetpointTemperatureOffset() const {
      const auto value = getDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::BoilerSetpointTemperatureOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantEquipmentOperationChillerHeaterChangeover_Impl::setBoilerSetpointTemperatureOffset(double boilerSetpointTemperatureOffset) {
      return setDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::BoilerSetpointTemperatureOffset,
                       boilerSetpointTemperatureOffset);
    }

    void PlantEquipmentOperationChillerHeaterChangeover_Impl::resetBoilerSetpointTemperatureOffset() {
      const bool result = setString(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::BoilerSetpointTemperatureOffset, "");
      OS_ASSERT(result);
    }

    bool PlantEquipmentOperationChillerHeaterChangeover_Impl::isBoilerSetpointTemperatureOffsetDefaulted() const {
      return isEmpty(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::BoilerSetpointTemperatureOffset);
    }

    boost::optional<double> PlantEquipmentOperationChillerHeaterChangeover_Impl::primaryHeatingPlantSetpointatBackupOutdoorLowTemperature() const {
      return getDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::PrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature);
    }

    bool PlantEquipmentOperationChillerHeaterChangeover_Impl::setPrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature(
      double primaryHeatingPlantSetpointatBackupOutdoorLowTemperature) {
      return setDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::PrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature,
                       primaryHeatingPlantSetpointatBackupOutdoorLowTemperature);
    }

    void PlantEquipmentOperationChillerHeaterChangeover_Impl::resetPrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature() {
      const bool result =
        setString(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::PrimaryHeatingPlantSetpointatBackupOutdoorLowTemperature, "");
      OS_ASSERT(result);
    }

    boost::optional<double> PlantEquipmentOperationChillerHeaterChangeover_Impl::backupOutdoorLowTemperature() const {
      return getDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::BackupOutdoorLowTemperature);
    }

    bool PlantEquipmentOperationChillerHeaterChangeover_Impl::setBackupOutdoorLowTemperature(double backupOutdoorLowTemperature) {
      return setDouble(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::BackupOutdoorLowTemperature, backupOutdoorLowTemperature);
    }

    void PlantEquipmentOperationChillerHeaterChangeover_Impl::resetBackupOutdoorLowTemperature() {
      const bool result = setString(openstudio::PlantEquipmentOperation_ChillerHeaterChangeoverFields::BackupOutdoorLowTemperature, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
