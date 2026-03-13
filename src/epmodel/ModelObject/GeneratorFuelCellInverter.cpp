/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorFuelCellInverter.hpp"
#include "GeneratorFuelCellInverter_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_FuelCell_Inverter_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  GeneratorFuelCellInverter::GeneratorFuelCellInverter(const Model& model) : ModelObject(GeneratorFuelCellInverter::iddObjectType(), model) {}

  GeneratorFuelCellInverter::GeneratorFuelCellInverter(std::shared_ptr<detail::GeneratorFuelCellInverter_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType GeneratorFuelCellInverter::iddObjectType() {
    return IddObjectType::Generator_FuelCell_Inverter;
  }

  std::vector<std::string> GeneratorFuelCellInverter::inverterEfficiencyCalculationModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Generator_FuelCell_InverterFields::InverterEfficiencyCalculationMode);
  }

  std::string GeneratorFuelCellInverter::inverterEfficiencyCalculationMode() const {
    return getImpl<detail::GeneratorFuelCellInverter_Impl>()->inverterEfficiencyCalculationMode();
  }

  bool GeneratorFuelCellInverter::setInverterEfficiencyCalculationMode(const std::string& inverterEfficiencyCalculationMode) {
    return getImpl<detail::GeneratorFuelCellInverter_Impl>()->setInverterEfficiencyCalculationMode(inverterEfficiencyCalculationMode);
  }

  void GeneratorFuelCellInverter::resetInverterEfficiencyCalculationMode() {
    getImpl<detail::GeneratorFuelCellInverter_Impl>()->resetInverterEfficiencyCalculationMode();
  }

  double GeneratorFuelCellInverter::inverterEfficiency() const {
    return getImpl<detail::GeneratorFuelCellInverter_Impl>()->inverterEfficiency();
  }

  bool GeneratorFuelCellInverter::setInverterEfficiency(double inverterEfficiency) {
    return getImpl<detail::GeneratorFuelCellInverter_Impl>()->setInverterEfficiency(inverterEfficiency);
  }

  void GeneratorFuelCellInverter::resetInverterEfficiency() {
    getImpl<detail::GeneratorFuelCellInverter_Impl>()->resetInverterEfficiency();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string GeneratorFuelCellInverter_Impl::inverterEfficiencyCalculationMode() const {
      const auto value = getString(openstudio::Generator_FuelCell_InverterFields::InverterEfficiencyCalculationMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellInverter_Impl::setInverterEfficiencyCalculationMode(const std::string& inverterEfficiencyCalculationMode) {
      return setString(openstudio::Generator_FuelCell_InverterFields::InverterEfficiencyCalculationMode, inverterEfficiencyCalculationMode);
    }

    void GeneratorFuelCellInverter_Impl::resetInverterEfficiencyCalculationMode() {
      OS_ASSERT(setString(openstudio::Generator_FuelCell_InverterFields::InverterEfficiencyCalculationMode, "Constant"));
    }

    std::vector<std::string> GeneratorFuelCellInverter_Impl::inverterEfficiencyCalculationModeValues() const {
      return openstudio::epmodel::GeneratorFuelCellInverter::inverterEfficiencyCalculationModeValues();
    }

    double GeneratorFuelCellInverter_Impl::inverterEfficiency() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_InverterFields::InverterEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellInverter_Impl::setInverterEfficiency(double inverterEfficiency) {
      return setDouble(openstudio::Generator_FuelCell_InverterFields::InverterEfficiency, inverterEfficiency);
    }

    void GeneratorFuelCellInverter_Impl::resetInverterEfficiency() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_InverterFields::InverterEfficiency, 1.0));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
