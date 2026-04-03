/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlantEquipmentOperationScheme/PlantEquipmentOperationThermalEnergyStorage.hpp"
#include "PlantEquipmentOperationScheme/PlantEquipmentOperationThermalEnergyStorage_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/PlantEquipmentOperation_ThermalEnergyStorage_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  PlantEquipmentOperationThermalEnergyStorage::PlantEquipmentOperationThermalEnergyStorage(const Model& model)
    : PlantEquipmentOperationScheme(PlantEquipmentOperationThermalEnergyStorage::iddObjectType(), model) {}

  PlantEquipmentOperationThermalEnergyStorage::PlantEquipmentOperationThermalEnergyStorage(
    std::shared_ptr<detail::PlantEquipmentOperationThermalEnergyStorage_Impl> impl)
    : PlantEquipmentOperationScheme(std::move(impl)) {}

  IddObjectType PlantEquipmentOperationThermalEnergyStorage::iddObjectType() {
    return IddObjectType::PlantEquipmentOperation_ThermalEnergyStorage;
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component1ObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component1ObjectType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component1OperationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component1OperationType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component2ObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component2ObjectType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component2OperationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component2OperationType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component3ObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component3ObjectType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component3OperationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component3OperationType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component4ObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component4ObjectType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component4OperationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component4OperationType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component5ObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component5ObjectType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component5OperationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component5OperationType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component6ObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component6ObjectType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component6OperationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component6OperationType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component7ObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component7ObjectType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component7OperationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component7OperationType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component8ObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component8ObjectType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component8OperationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component8OperationType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component9ObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component9ObjectType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component9OperationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component9OperationType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component10ObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component10ObjectType);
  }

  std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage::component10OperationTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component10OperationType);
  }

  double PlantEquipmentOperationThermalEnergyStorage::nonChargingChilledWaterTemperature() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->nonChargingChilledWaterTemperature();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setNonChargingChilledWaterTemperature(double nonChargingChilledWaterTemperature) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setNonChargingChilledWaterTemperature(
      nonChargingChilledWaterTemperature);
  }

  double PlantEquipmentOperationThermalEnergyStorage::chargingChilledWaterTemperature() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->chargingChilledWaterTemperature();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setChargingChilledWaterTemperature(double chargingChilledWaterTemperature) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setChargingChilledWaterTemperature(chargingChilledWaterTemperature);
  }

  boost::optional<double> PlantEquipmentOperationThermalEnergyStorage::component1FlowRate() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component1FlowRate();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::isComponent1FlowRateAutosized() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->isComponent1FlowRateAutosized();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent1FlowRate(double component1FlowRate) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent1FlowRate(component1FlowRate);
  }

  void PlantEquipmentOperationThermalEnergyStorage::autosizeComponent1FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->autosizeComponent1FlowRate();
  }

  std::string PlantEquipmentOperationThermalEnergyStorage::component1ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component1ObjectType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent1ObjectType(const std::string& component1ObjectType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent1ObjectType(component1ObjectType);
  }

  std::string PlantEquipmentOperationThermalEnergyStorage::component1OperationType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component1OperationType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent1OperationType(const std::string& component1OperationType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent1OperationType(component1OperationType);
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component2ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component2ObjectType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent2ObjectType(const std::string& component2ObjectType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent2ObjectType(component2ObjectType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent2ObjectType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent2ObjectType();
  }

  boost::optional<double> PlantEquipmentOperationThermalEnergyStorage::component2FlowRate() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component2FlowRate();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::isComponent2FlowRateAutosized() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->isComponent2FlowRateAutosized();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent2FlowRate(double component2FlowRate) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent2FlowRate(component2FlowRate);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent2FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent2FlowRate();
  }

  void PlantEquipmentOperationThermalEnergyStorage::autosizeComponent2FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->autosizeComponent2FlowRate();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component2OperationType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component2OperationType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent2OperationType(const std::string& component2OperationType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent2OperationType(component2OperationType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent2OperationType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent2OperationType();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component3ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component3ObjectType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent3ObjectType(const std::string& component3ObjectType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent3ObjectType(component3ObjectType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent3ObjectType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent3ObjectType();
  }

  boost::optional<double> PlantEquipmentOperationThermalEnergyStorage::component3FlowRate() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component3FlowRate();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::isComponent3FlowRateAutosized() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->isComponent3FlowRateAutosized();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent3FlowRate(double component3FlowRate) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent3FlowRate(component3FlowRate);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent3FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent3FlowRate();
  }

  void PlantEquipmentOperationThermalEnergyStorage::autosizeComponent3FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->autosizeComponent3FlowRate();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component3OperationType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component3OperationType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent3OperationType(const std::string& component3OperationType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent3OperationType(component3OperationType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent3OperationType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent3OperationType();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component4ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component4ObjectType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent4ObjectType(const std::string& component4ObjectType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent4ObjectType(component4ObjectType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent4ObjectType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent4ObjectType();
  }

  boost::optional<double> PlantEquipmentOperationThermalEnergyStorage::component4FlowRate() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component4FlowRate();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::isComponent4FlowRateAutosized() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->isComponent4FlowRateAutosized();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent4FlowRate(double component4FlowRate) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent4FlowRate(component4FlowRate);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent4FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent4FlowRate();
  }

  void PlantEquipmentOperationThermalEnergyStorage::autosizeComponent4FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->autosizeComponent4FlowRate();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component4OperationType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component4OperationType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent4OperationType(const std::string& component4OperationType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent4OperationType(component4OperationType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent4OperationType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent4OperationType();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component5ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component5ObjectType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent5ObjectType(const std::string& component5ObjectType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent5ObjectType(component5ObjectType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent5ObjectType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent5ObjectType();
  }

  boost::optional<double> PlantEquipmentOperationThermalEnergyStorage::component5FlowRate() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component5FlowRate();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::isComponent5FlowRateAutosized() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->isComponent5FlowRateAutosized();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent5FlowRate(double component5FlowRate) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent5FlowRate(component5FlowRate);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent5FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent5FlowRate();
  }

  void PlantEquipmentOperationThermalEnergyStorage::autosizeComponent5FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->autosizeComponent5FlowRate();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component5OperationType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component5OperationType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent5OperationType(const std::string& component5OperationType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent5OperationType(component5OperationType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent5OperationType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent5OperationType();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component6ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component6ObjectType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent6ObjectType(const std::string& component6ObjectType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent6ObjectType(component6ObjectType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent6ObjectType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent6ObjectType();
  }

  boost::optional<double> PlantEquipmentOperationThermalEnergyStorage::component6FlowRate() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component6FlowRate();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::isComponent6FlowRateAutosized() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->isComponent6FlowRateAutosized();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent6FlowRate(double component6FlowRate) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent6FlowRate(component6FlowRate);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent6FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent6FlowRate();
  }

  void PlantEquipmentOperationThermalEnergyStorage::autosizeComponent6FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->autosizeComponent6FlowRate();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component6OperationType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component6OperationType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent6OperationType(const std::string& component6OperationType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent6OperationType(component6OperationType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent6OperationType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent6OperationType();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component7ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component7ObjectType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent7ObjectType(const std::string& component7ObjectType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent7ObjectType(component7ObjectType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent7ObjectType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent7ObjectType();
  }

  boost::optional<double> PlantEquipmentOperationThermalEnergyStorage::component7FlowRate() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component7FlowRate();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::isComponent7FlowRateAutosized() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->isComponent7FlowRateAutosized();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent7FlowRate(double component7FlowRate) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent7FlowRate(component7FlowRate);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent7FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent7FlowRate();
  }

  void PlantEquipmentOperationThermalEnergyStorage::autosizeComponent7FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->autosizeComponent7FlowRate();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component7OperationType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component7OperationType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent7OperationType(const std::string& component7OperationType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent7OperationType(component7OperationType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent7OperationType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent7OperationType();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component8ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component8ObjectType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent8ObjectType(const std::string& component8ObjectType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent8ObjectType(component8ObjectType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent8ObjectType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent8ObjectType();
  }

  boost::optional<double> PlantEquipmentOperationThermalEnergyStorage::component8FlowRate() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component8FlowRate();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::isComponent8FlowRateAutosized() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->isComponent8FlowRateAutosized();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent8FlowRate(double component8FlowRate) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent8FlowRate(component8FlowRate);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent8FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent8FlowRate();
  }

  void PlantEquipmentOperationThermalEnergyStorage::autosizeComponent8FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->autosizeComponent8FlowRate();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component8OperationType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component8OperationType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent8OperationType(const std::string& component8OperationType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent8OperationType(component8OperationType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent8OperationType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent8OperationType();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component9ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component9ObjectType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent9ObjectType(const std::string& component9ObjectType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent9ObjectType(component9ObjectType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent9ObjectType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent9ObjectType();
  }

  boost::optional<double> PlantEquipmentOperationThermalEnergyStorage::component9FlowRate() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component9FlowRate();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::isComponent9FlowRateAutosized() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->isComponent9FlowRateAutosized();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent9FlowRate(double component9FlowRate) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent9FlowRate(component9FlowRate);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent9FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent9FlowRate();
  }

  void PlantEquipmentOperationThermalEnergyStorage::autosizeComponent9FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->autosizeComponent9FlowRate();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component9OperationType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component9OperationType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent9OperationType(const std::string& component9OperationType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent9OperationType(component9OperationType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent9OperationType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent9OperationType();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component10ObjectType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component10ObjectType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent10ObjectType(const std::string& component10ObjectType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent10ObjectType(component10ObjectType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent10ObjectType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent10ObjectType();
  }

  boost::optional<double> PlantEquipmentOperationThermalEnergyStorage::component10FlowRate() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component10FlowRate();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::isComponent10FlowRateAutosized() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->isComponent10FlowRateAutosized();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent10FlowRate(double component10FlowRate) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent10FlowRate(component10FlowRate);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent10FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent10FlowRate();
  }

  void PlantEquipmentOperationThermalEnergyStorage::autosizeComponent10FlowRate() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->autosizeComponent10FlowRate();
  }

  boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage::component10OperationType() const {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->component10OperationType();
  }

  bool PlantEquipmentOperationThermalEnergyStorage::setComponent10OperationType(const std::string& component10OperationType) {
    return getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->setComponent10OperationType(component10OperationType);
  }

  void PlantEquipmentOperationThermalEnergyStorage::resetComponent10OperationType() {
    getImpl<detail::PlantEquipmentOperationThermalEnergyStorage_Impl>()->resetComponent10OperationType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double PlantEquipmentOperationThermalEnergyStorage_Impl::nonChargingChilledWaterTemperature() const {
      auto value = getDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::NonChargingChilledWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setNonChargingChilledWaterTemperature(double nonChargingChilledWaterTemperature) {
      const bool result = setDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::NonChargingChilledWaterTemperature,
                                    nonChargingChilledWaterTemperature);
      OS_ASSERT(result);
      return result;
    }

    double PlantEquipmentOperationThermalEnergyStorage_Impl::chargingChilledWaterTemperature() const {
      auto value = getDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::ChargingChilledWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setChargingChilledWaterTemperature(double chargingChilledWaterTemperature) {
      const bool result =
        setDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::ChargingChilledWaterTemperature, chargingChilledWaterTemperature);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> PlantEquipmentOperationThermalEnergyStorage_Impl::component1FlowRate() const {
      return getDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component1FlowRate, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::isComponent1FlowRateAutosized() const {
      if (auto value = getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component1FlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent1FlowRate(double component1FlowRate) {
      const bool result = setDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component1FlowRate, component1FlowRate);
      OS_ASSERT(result);
      return result;
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::autosizeComponent1FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component1FlowRate, "autosize"));
    }

    std::string PlantEquipmentOperationThermalEnergyStorage_Impl::component1ObjectType() const {
      const auto value = getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component1ObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent1ObjectType(const std::string& component1ObjectType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component1ObjectType, component1ObjectType);
    }

    std::string PlantEquipmentOperationThermalEnergyStorage_Impl::component1OperationType() const {
      const auto value = getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component1OperationType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent1OperationType(const std::string& component1OperationType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component1OperationType, component1OperationType);
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component2ObjectType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component2ObjectType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent2ObjectType(const std::string& component2ObjectType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component2ObjectType, component2ObjectType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent2ObjectType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component2ObjectType, ""));
    }

    boost::optional<double> PlantEquipmentOperationThermalEnergyStorage_Impl::component2FlowRate() const {
      return getDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component2FlowRate, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::isComponent2FlowRateAutosized() const {
      if (auto value = getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component2FlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent2FlowRate(double component2FlowRate) {
      const bool result = setDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component2FlowRate, component2FlowRate);
      OS_ASSERT(result);
      return result;
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent2FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component2FlowRate, ""));
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::autosizeComponent2FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component2FlowRate, "autosize"));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component2OperationType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component2OperationType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent2OperationType(const std::string& component2OperationType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component2OperationType, component2OperationType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent2OperationType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component2OperationType, ""));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component3ObjectType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component3ObjectType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent3ObjectType(const std::string& component3ObjectType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component3ObjectType, component3ObjectType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent3ObjectType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component3ObjectType, ""));
    }

    boost::optional<double> PlantEquipmentOperationThermalEnergyStorage_Impl::component3FlowRate() const {
      return getDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component3FlowRate, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::isComponent3FlowRateAutosized() const {
      if (auto value = getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component3FlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent3FlowRate(double component3FlowRate) {
      const bool result = setDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component3FlowRate, component3FlowRate);
      OS_ASSERT(result);
      return result;
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent3FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component3FlowRate, ""));
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::autosizeComponent3FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component3FlowRate, "autosize"));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component3OperationType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component3OperationType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent3OperationType(const std::string& component3OperationType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component3OperationType, component3OperationType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent3OperationType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component3OperationType, ""));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component4ObjectType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component4ObjectType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent4ObjectType(const std::string& component4ObjectType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component4ObjectType, component4ObjectType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent4ObjectType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component4ObjectType, ""));
    }

    boost::optional<double> PlantEquipmentOperationThermalEnergyStorage_Impl::component4FlowRate() const {
      return getDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component4FlowRate, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::isComponent4FlowRateAutosized() const {
      if (auto value = getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component4FlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent4FlowRate(double component4FlowRate) {
      const bool result = setDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component4FlowRate, component4FlowRate);
      OS_ASSERT(result);
      return result;
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent4FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component4FlowRate, ""));
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::autosizeComponent4FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component4FlowRate, "autosize"));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component4OperationType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component4OperationType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent4OperationType(const std::string& component4OperationType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component4OperationType, component4OperationType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent4OperationType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component4OperationType, ""));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component5ObjectType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component5ObjectType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent5ObjectType(const std::string& component5ObjectType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component5ObjectType, component5ObjectType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent5ObjectType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component5ObjectType, ""));
    }

    boost::optional<double> PlantEquipmentOperationThermalEnergyStorage_Impl::component5FlowRate() const {
      return getDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component5FlowRate, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::isComponent5FlowRateAutosized() const {
      if (auto value = getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component5FlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent5FlowRate(double component5FlowRate) {
      const bool result = setDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component5FlowRate, component5FlowRate);
      OS_ASSERT(result);
      return result;
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent5FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component5FlowRate, ""));
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::autosizeComponent5FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component5FlowRate, "autosize"));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component5OperationType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component5OperationType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent5OperationType(const std::string& component5OperationType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component5OperationType, component5OperationType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent5OperationType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component5OperationType, ""));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component6ObjectType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component6ObjectType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent6ObjectType(const std::string& component6ObjectType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component6ObjectType, component6ObjectType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent6ObjectType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component6ObjectType, ""));
    }

    boost::optional<double> PlantEquipmentOperationThermalEnergyStorage_Impl::component6FlowRate() const {
      return getDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component6FlowRate, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::isComponent6FlowRateAutosized() const {
      if (auto value = getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component6FlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent6FlowRate(double component6FlowRate) {
      const bool result = setDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component6FlowRate, component6FlowRate);
      OS_ASSERT(result);
      return result;
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent6FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component6FlowRate, ""));
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::autosizeComponent6FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component6FlowRate, "autosize"));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component6OperationType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component6OperationType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent6OperationType(const std::string& component6OperationType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component6OperationType, component6OperationType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent6OperationType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component6OperationType, ""));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component7ObjectType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component7ObjectType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent7ObjectType(const std::string& component7ObjectType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component7ObjectType, component7ObjectType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent7ObjectType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component7ObjectType, ""));
    }

    boost::optional<double> PlantEquipmentOperationThermalEnergyStorage_Impl::component7FlowRate() const {
      return getDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component7FlowRate, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::isComponent7FlowRateAutosized() const {
      if (auto value = getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component7FlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent7FlowRate(double component7FlowRate) {
      const bool result = setDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component7FlowRate, component7FlowRate);
      OS_ASSERT(result);
      return result;
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent7FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component7FlowRate, ""));
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::autosizeComponent7FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component7FlowRate, "autosize"));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component7OperationType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component7OperationType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent7OperationType(const std::string& component7OperationType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component7OperationType, component7OperationType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent7OperationType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component7OperationType, ""));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component8ObjectType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component8ObjectType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent8ObjectType(const std::string& component8ObjectType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component8ObjectType, component8ObjectType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent8ObjectType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component8ObjectType, ""));
    }

    boost::optional<double> PlantEquipmentOperationThermalEnergyStorage_Impl::component8FlowRate() const {
      return getDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component8FlowRate, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::isComponent8FlowRateAutosized() const {
      if (auto value = getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component8FlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent8FlowRate(double component8FlowRate) {
      const bool result = setDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component8FlowRate, component8FlowRate);
      OS_ASSERT(result);
      return result;
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent8FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component8FlowRate, ""));
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::autosizeComponent8FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component8FlowRate, "autosize"));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component8OperationType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component8OperationType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent8OperationType(const std::string& component8OperationType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component8OperationType, component8OperationType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent8OperationType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component8OperationType, ""));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component9ObjectType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component9ObjectType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent9ObjectType(const std::string& component9ObjectType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component9ObjectType, component9ObjectType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent9ObjectType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component9ObjectType, ""));
    }

    boost::optional<double> PlantEquipmentOperationThermalEnergyStorage_Impl::component9FlowRate() const {
      return getDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component9FlowRate, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::isComponent9FlowRateAutosized() const {
      if (auto value = getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component9FlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent9FlowRate(double component9FlowRate) {
      const bool result = setDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component9FlowRate, component9FlowRate);
      OS_ASSERT(result);
      return result;
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent9FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component9FlowRate, ""));
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::autosizeComponent9FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component9FlowRate, "autosize"));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component9OperationType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component9OperationType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent9OperationType(const std::string& component9OperationType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component9OperationType, component9OperationType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent9OperationType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component9OperationType, ""));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component10ObjectType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component10ObjectType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent10ObjectType(const std::string& component10ObjectType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component10ObjectType, component10ObjectType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent10ObjectType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component10ObjectType, ""));
    }

    boost::optional<double> PlantEquipmentOperationThermalEnergyStorage_Impl::component10FlowRate() const {
      return getDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component10FlowRate, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::isComponent10FlowRateAutosized() const {
      if (auto value = getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component10FlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent10FlowRate(double component10FlowRate) {
      const bool result = setDouble(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component10FlowRate, component10FlowRate);
      OS_ASSERT(result);
      return result;
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent10FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component10FlowRate, ""));
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::autosizeComponent10FlowRate() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component10FlowRate, "autosize"));
    }

    boost::optional<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component10OperationType() const {
      return getString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component10OperationType, true);
    }

    bool PlantEquipmentOperationThermalEnergyStorage_Impl::setComponent10OperationType(const std::string& component10OperationType) {
      return setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component10OperationType, component10OperationType);
    }

    void PlantEquipmentOperationThermalEnergyStorage_Impl::resetComponent10OperationType() {
      OS_ASSERT(setString(openstudio::PlantEquipmentOperation_ThermalEnergyStorageFields::Component10OperationType, ""));
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component1ObjectTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component1ObjectTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component1OperationTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component1OperationTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component2ObjectTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component2ObjectTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component2OperationTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component2OperationTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component3ObjectTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component3ObjectTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component3OperationTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component3OperationTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component4ObjectTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component4ObjectTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component4OperationTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component4OperationTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component5ObjectTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component5ObjectTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component5OperationTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component5OperationTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component6ObjectTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component6ObjectTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component6OperationTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component6OperationTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component7ObjectTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component7ObjectTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component7OperationTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component7OperationTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component8ObjectTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component8ObjectTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component8OperationTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component8OperationTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component9ObjectTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component9ObjectTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component9OperationTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component9OperationTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component10ObjectTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component10ObjectTypeValues();
    }

    std::vector<std::string> PlantEquipmentOperationThermalEnergyStorage_Impl::component10OperationTypeValues() const {
      return openstudio::epmodel::PlantEquipmentOperationThermalEnergyStorage::component10OperationTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
