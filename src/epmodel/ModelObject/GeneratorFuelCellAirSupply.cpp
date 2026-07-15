/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GeneratorFuelCellAirSupply.hpp"
#include "GeneratorFuelCellAirSupply_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Generator_FuelCell_AirSupply_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  GeneratorFuelCellAirSupply::GeneratorFuelCellAirSupply(const Model& model) : ModelObject(GeneratorFuelCellAirSupply::iddObjectType(), model) {}

  GeneratorFuelCellAirSupply::GeneratorFuelCellAirSupply(std::shared_ptr<detail::GeneratorFuelCellAirSupply_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GeneratorFuelCellAirSupply::iddObjectType() {
    return IddObjectType::Generator_FuelCell_AirSupply;
  }

  std::vector<std::string> GeneratorFuelCellAirSupply::airSupplyRateCalculationModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Generator_FuelCell_AirSupplyFields::AirSupplyRateCalculationMode);
  }

  std::vector<std::string> GeneratorFuelCellAirSupply::airIntakeHeatRecoveryModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Generator_FuelCell_AirSupplyFields::AirIntakeHeatRecoveryMode);
  }

  std::vector<std::string> GeneratorFuelCellAirSupply::airSupplyConstituentModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Generator_FuelCell_AirSupplyFields::AirSupplyConstituentMode);
  }

  double GeneratorFuelCellAirSupply::blowerHeatLossFactor() const {
    return getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->blowerHeatLossFactor();
  }

  bool GeneratorFuelCellAirSupply::setBlowerHeatLossFactor(double blowerHeatLossFactor) {
    return getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->setBlowerHeatLossFactor(blowerHeatLossFactor);
  }

  void GeneratorFuelCellAirSupply::resetBlowerHeatLossFactor() {
    getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->resetBlowerHeatLossFactor();
  }

  std::string GeneratorFuelCellAirSupply::airSupplyRateCalculationMode() const {
    return getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->airSupplyRateCalculationMode();
  }

  bool GeneratorFuelCellAirSupply::setAirSupplyRateCalculationMode(const std::string& airSupplyRateCalculationMode) {
    return getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->setAirSupplyRateCalculationMode(airSupplyRateCalculationMode);
  }

  boost::optional<double> GeneratorFuelCellAirSupply::stoichiometricRatio() const {
    return getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->stoichiometricRatio();
  }

  bool GeneratorFuelCellAirSupply::setStoichiometricRatio(double stoichiometricRatio) {
    return getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->setStoichiometricRatio(stoichiometricRatio);
  }

  void GeneratorFuelCellAirSupply::resetStoichiometricRatio() {
    getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->resetStoichiometricRatio();
  }

  boost::optional<double> GeneratorFuelCellAirSupply::airRateAirTemperatureCoefficient() const {
    return getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->airRateAirTemperatureCoefficient();
  }

  bool GeneratorFuelCellAirSupply::setAirRateAirTemperatureCoefficient(double airRateAirTemperatureCoefficient) {
    return getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->setAirRateAirTemperatureCoefficient(airRateAirTemperatureCoefficient);
  }

  void GeneratorFuelCellAirSupply::resetAirRateAirTemperatureCoefficient() {
    getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->resetAirRateAirTemperatureCoefficient();
  }

  std::string GeneratorFuelCellAirSupply::airIntakeHeatRecoveryMode() const {
    return getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->airIntakeHeatRecoveryMode();
  }

  bool GeneratorFuelCellAirSupply::setAirIntakeHeatRecoveryMode(const std::string& airIntakeHeatRecoveryMode) {
    return getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->setAirIntakeHeatRecoveryMode(airIntakeHeatRecoveryMode);
  }

  std::string GeneratorFuelCellAirSupply::airSupplyConstituentMode() const {
    return getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->airSupplyConstituentMode();
  }

  bool GeneratorFuelCellAirSupply::setAirSupplyConstituentMode(const std::string& airSupplyConstituentMode) {
    return getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->setAirSupplyConstituentMode(airSupplyConstituentMode);
  }

  boost::optional<unsigned int> GeneratorFuelCellAirSupply::numberofUserDefinedConstituents() const {
    return getImpl<detail::GeneratorFuelCellAirSupply_Impl>()->numberofUserDefinedConstituents();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double GeneratorFuelCellAirSupply_Impl::blowerHeatLossFactor() const {
      const auto value = getDouble(openstudio::Generator_FuelCell_AirSupplyFields::BlowerHeatLossFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAirSupply_Impl::setBlowerHeatLossFactor(double blowerHeatLossFactor) {
      return setDouble(openstudio::Generator_FuelCell_AirSupplyFields::BlowerHeatLossFactor, blowerHeatLossFactor);
    }

    void GeneratorFuelCellAirSupply_Impl::resetBlowerHeatLossFactor() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_AirSupplyFields::BlowerHeatLossFactor, 0.0));
    }

    std::string GeneratorFuelCellAirSupply_Impl::airSupplyRateCalculationMode() const {
      const auto value = getString(openstudio::Generator_FuelCell_AirSupplyFields::AirSupplyRateCalculationMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAirSupply_Impl::setAirSupplyRateCalculationMode(const std::string& airSupplyRateCalculationMode) {
      return setString(openstudio::Generator_FuelCell_AirSupplyFields::AirSupplyRateCalculationMode, airSupplyRateCalculationMode);
    }

    boost::optional<double> GeneratorFuelCellAirSupply_Impl::stoichiometricRatio() const {
      return getDouble(openstudio::Generator_FuelCell_AirSupplyFields::StoichiometricRatio, true);
    }

    bool GeneratorFuelCellAirSupply_Impl::setStoichiometricRatio(double stoichiometricRatio) {
      const bool result = setDouble(openstudio::Generator_FuelCell_AirSupplyFields::StoichiometricRatio, stoichiometricRatio);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellAirSupply_Impl::resetStoichiometricRatio() {
      OS_ASSERT(setString(openstudio::Generator_FuelCell_AirSupplyFields::StoichiometricRatio, ""));
    }

    boost::optional<double> GeneratorFuelCellAirSupply_Impl::airRateAirTemperatureCoefficient() const {
      return getDouble(openstudio::Generator_FuelCell_AirSupplyFields::AirRateAirTemperatureCoefficient, true);
    }

    bool GeneratorFuelCellAirSupply_Impl::setAirRateAirTemperatureCoefficient(double airRateAirTemperatureCoefficient) {
      const bool result =
        setDouble(openstudio::Generator_FuelCell_AirSupplyFields::AirRateAirTemperatureCoefficient, airRateAirTemperatureCoefficient);
      OS_ASSERT(result);
      return result;
    }

    void GeneratorFuelCellAirSupply_Impl::resetAirRateAirTemperatureCoefficient() {
      OS_ASSERT(setDouble(openstudio::Generator_FuelCell_AirSupplyFields::AirRateAirTemperatureCoefficient, 0.0));
    }

    std::string GeneratorFuelCellAirSupply_Impl::airIntakeHeatRecoveryMode() const {
      const auto value = getString(openstudio::Generator_FuelCell_AirSupplyFields::AirIntakeHeatRecoveryMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAirSupply_Impl::setAirIntakeHeatRecoveryMode(const std::string& airIntakeHeatRecoveryMode) {
      return setString(openstudio::Generator_FuelCell_AirSupplyFields::AirIntakeHeatRecoveryMode, airIntakeHeatRecoveryMode);
    }

    std::string GeneratorFuelCellAirSupply_Impl::airSupplyConstituentMode() const {
      const auto value = getString(openstudio::Generator_FuelCell_AirSupplyFields::AirSupplyConstituentMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GeneratorFuelCellAirSupply_Impl::setAirSupplyConstituentMode(const std::string& airSupplyConstituentMode) {
      return setString(openstudio::Generator_FuelCell_AirSupplyFields::AirSupplyConstituentMode, airSupplyConstituentMode);
    }

    boost::optional<unsigned int> GeneratorFuelCellAirSupply_Impl::numberofUserDefinedConstituents() const {
      return numExtensibleGroups();
    }

    std::vector<std::string> GeneratorFuelCellAirSupply_Impl::airSupplyRateCalculationModeValues() const {
      return openstudio::epmodel::GeneratorFuelCellAirSupply::airSupplyRateCalculationModeValues();
    }

    std::vector<std::string> GeneratorFuelCellAirSupply_Impl::airIntakeHeatRecoveryModeValues() const {
      return openstudio::epmodel::GeneratorFuelCellAirSupply::airIntakeHeatRecoveryModeValues();
    }

    std::vector<std::string> GeneratorFuelCellAirSupply_Impl::airSupplyConstituentModeValues() const {
      return openstudio::epmodel::GeneratorFuelCellAirSupply::airSupplyConstituentModeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
