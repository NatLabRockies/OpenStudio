/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorFuelCellElectricalStorage.hpp"
#include "GeneratorFuelCellElectricalStorage_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_FuelCell_ElectricalStorage_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  GeneratorFuelCellElectricalStorage::GeneratorFuelCellElectricalStorage(const Model& model)
    : ModelObject(GeneratorFuelCellElectricalStorage::iddObjectType(), model) {}

  GeneratorFuelCellElectricalStorage::GeneratorFuelCellElectricalStorage(std::shared_ptr<detail::GeneratorFuelCellElectricalStorage_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GeneratorFuelCellElectricalStorage::iddObjectType() {
    return IddObjectType::Generator_FuelCell_ElectricalStorage;
  }

  std::vector<std::string> GeneratorFuelCellElectricalStorage::choiceofModelValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Generator_FuelCell_ElectricalStorageFields::ChoiceofModel);
  }

  std::string GeneratorFuelCellElectricalStorage::choiceofModel() const {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->choiceofModel();
  }

  bool GeneratorFuelCellElectricalStorage::setChoiceofModel(const std::string& choiceofModel) {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->setChoiceofModel(choiceofModel);
  }

  void GeneratorFuelCellElectricalStorage::resetChoiceofModel() {
    getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->resetChoiceofModel();
  }

  double GeneratorFuelCellElectricalStorage::nominalChargingEnergeticEfficiency() const {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->nominalChargingEnergeticEfficiency();
  }

  bool GeneratorFuelCellElectricalStorage::setNominalChargingEnergeticEfficiency(double nominalChargingEnergeticEfficiency) {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->setNominalChargingEnergeticEfficiency(nominalChargingEnergeticEfficiency);
  }

  void GeneratorFuelCellElectricalStorage::resetNominalChargingEnergeticEfficiency() {
    getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->resetNominalChargingEnergeticEfficiency();
  }

  double GeneratorFuelCellElectricalStorage::nominalDischargingEnergeticEfficiency() const {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->nominalDischargingEnergeticEfficiency();
  }

  bool GeneratorFuelCellElectricalStorage::setNominalDischargingEnergeticEfficiency(double nominalDischargingEnergeticEfficiency) {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->setNominalDischargingEnergeticEfficiency(
      nominalDischargingEnergeticEfficiency);
  }

  void GeneratorFuelCellElectricalStorage::resetNominalDischargingEnergeticEfficiency() {
    getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->resetNominalDischargingEnergeticEfficiency();
  }

  double GeneratorFuelCellElectricalStorage::simpleMaximumCapacity() const {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->simpleMaximumCapacity();
  }

  bool GeneratorFuelCellElectricalStorage::setSimpleMaximumCapacity(double simpleMaximumCapacity) {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->setSimpleMaximumCapacity(simpleMaximumCapacity);
  }

  void GeneratorFuelCellElectricalStorage::resetSimpleMaximumCapacity() {
    getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->resetSimpleMaximumCapacity();
  }

  double GeneratorFuelCellElectricalStorage::simpleMaximumPowerDraw() const {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->simpleMaximumPowerDraw();
  }

  bool GeneratorFuelCellElectricalStorage::setSimpleMaximumPowerDraw(double simpleMaximumPowerDraw) {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->setSimpleMaximumPowerDraw(simpleMaximumPowerDraw);
  }

  void GeneratorFuelCellElectricalStorage::resetSimpleMaximumPowerDraw() {
    getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->resetSimpleMaximumPowerDraw();
  }

  double GeneratorFuelCellElectricalStorage::simpleMaximumPowerStore() const {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->simpleMaximumPowerStore();
  }

  bool GeneratorFuelCellElectricalStorage::setSimpleMaximumPowerStore(double simpleMaximumPowerStore) {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->setSimpleMaximumPowerStore(simpleMaximumPowerStore);
  }

  void GeneratorFuelCellElectricalStorage::resetSimpleMaximumPowerStore() {
    getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->resetSimpleMaximumPowerStore();
  }

  double GeneratorFuelCellElectricalStorage::initialChargeState() const {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->initialChargeState();
  }

  bool GeneratorFuelCellElectricalStorage::setInitialChargeState(double initialChargeState) {
    return getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->setInitialChargeState(initialChargeState);
  }

  void GeneratorFuelCellElectricalStorage::resetInitialChargeState() {
    getImpl<detail::GeneratorFuelCellElectricalStorage_Impl>()->resetInitialChargeState();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string GeneratorFuelCellElectricalStorage_Impl::choiceofModel() const {
      const auto value = getString(openstudio::Generator_FuelCell_ElectricalStorageFields::ChoiceofModel, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellElectricalStorage_Impl::setChoiceofModel(const std::string& choiceofModel) {
      return setString(openstudio::Generator_FuelCell_ElectricalStorageFields::ChoiceofModel, choiceofModel);
    }

    void GeneratorFuelCellElectricalStorage_Impl::resetChoiceofModel() {
      OS_ASSERT(setString(openstudio::Generator_FuelCell_ElectricalStorageFields::ChoiceofModel, "SimpleEfficiencyWithConstraints"));
    }

    double GeneratorFuelCellElectricalStorage_Impl::nominalChargingEnergeticEfficiency() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::NominalChargingEnergeticEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellElectricalStorage_Impl::setNominalChargingEnergeticEfficiency(double nominalChargingEnergeticEfficiency) {
      return setDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::NominalChargingEnergeticEfficiency,
                       nominalChargingEnergeticEfficiency);
    }

    void GeneratorFuelCellElectricalStorage_Impl::resetNominalChargingEnergeticEfficiency() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::NominalChargingEnergeticEfficiency, 1.0));
    }

    double GeneratorFuelCellElectricalStorage_Impl::nominalDischargingEnergeticEfficiency() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::NominalDischargingEnergeticEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellElectricalStorage_Impl::setNominalDischargingEnergeticEfficiency(double nominalDischargingEnergeticEfficiency) {
      return setDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::NominalDischargingEnergeticEfficiency,
                       nominalDischargingEnergeticEfficiency);
    }

    void GeneratorFuelCellElectricalStorage_Impl::resetNominalDischargingEnergeticEfficiency() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::NominalDischargingEnergeticEfficiency, 1.0));
    }

    double GeneratorFuelCellElectricalStorage_Impl::simpleMaximumCapacity() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::SimpleMaximumCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellElectricalStorage_Impl::setSimpleMaximumCapacity(double simpleMaximumCapacity) {
      const bool result = setDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::SimpleMaximumCapacity, simpleMaximumCapacity);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellElectricalStorage_Impl::resetSimpleMaximumCapacity() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::SimpleMaximumCapacity, 0.0));
    }

    double GeneratorFuelCellElectricalStorage_Impl::simpleMaximumPowerDraw() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::SimpleMaximumPowerDraw, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellElectricalStorage_Impl::setSimpleMaximumPowerDraw(double simpleMaximumPowerDraw) {
      const bool result = setDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::SimpleMaximumPowerDraw, simpleMaximumPowerDraw);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellElectricalStorage_Impl::resetSimpleMaximumPowerDraw() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::SimpleMaximumPowerDraw, 0.0));
    }

    double GeneratorFuelCellElectricalStorage_Impl::simpleMaximumPowerStore() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::SimpleMaximumPowerStore, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellElectricalStorage_Impl::setSimpleMaximumPowerStore(double simpleMaximumPowerStore) {
      const bool result = setDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::SimpleMaximumPowerStore, simpleMaximumPowerStore);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellElectricalStorage_Impl::resetSimpleMaximumPowerStore() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::SimpleMaximumPowerStore, 0.0));
    }

    double GeneratorFuelCellElectricalStorage_Impl::initialChargeState() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::InitialChargeState, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellElectricalStorage_Impl::setInitialChargeState(double initialChargeState) {
      const bool result = setDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::InitialChargeState, initialChargeState);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellElectricalStorage_Impl::resetInitialChargeState() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_ElectricalStorageFields::InitialChargeState, 0.0));
    }

    std::vector<std::string> GeneratorFuelCellElectricalStorage_Impl::choiceofModelValues() const {
      return openstudio::epmodel::GeneratorFuelCellElectricalStorage::choiceofModelValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
