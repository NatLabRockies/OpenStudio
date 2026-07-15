/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ElectricLoadCenterInverterLookUpTable.hpp"
#include "ElectricLoadCenterInverterLookUpTable_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ElectricLoadCenter_Inverter_LookUpTable_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ElectricLoadCenterInverterLookUpTable::ElectricLoadCenterInverterLookUpTable(const Model& model)
    : ModelObject(ElectricLoadCenterInverterLookUpTable::iddObjectType(), model) {}

  ElectricLoadCenterInverterLookUpTable::ElectricLoadCenterInverterLookUpTable(
    std::shared_ptr<detail::ElectricLoadCenterInverterLookUpTable_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ElectricLoadCenterInverterLookUpTable::iddObjectType() {
    return IddObjectType::ElectricLoadCenter_Inverter_LookUpTable;
  }

  boost::optional<double> ElectricLoadCenterInverterLookUpTable::radiativeFraction() const {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->radiativeFraction();
  }

  bool ElectricLoadCenterInverterLookUpTable::setRadiativeFraction(double radiativeFraction) {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->setRadiativeFraction(radiativeFraction);
  }

  void ElectricLoadCenterInverterLookUpTable::resetRadiativeFraction() {
    getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->resetRadiativeFraction();
  }

  boost::optional<double> ElectricLoadCenterInverterLookUpTable::ratedMaximumContinuousOutputPower() const {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->ratedMaximumContinuousOutputPower();
  }

  bool ElectricLoadCenterInverterLookUpTable::setRatedMaximumContinuousOutputPower(double ratedMaximumContinuousOutputPower) {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->setRatedMaximumContinuousOutputPower(ratedMaximumContinuousOutputPower);
  }

  void ElectricLoadCenterInverterLookUpTable::resetRatedMaximumContinuousOutputPower() {
    getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->resetRatedMaximumContinuousOutputPower();
  }

  boost::optional<double> ElectricLoadCenterInverterLookUpTable::nightTareLossPower() const {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->nightTareLossPower();
  }

  bool ElectricLoadCenterInverterLookUpTable::setNightTareLossPower(double nightTareLossPower) {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->setNightTareLossPower(nightTareLossPower);
  }

  void ElectricLoadCenterInverterLookUpTable::resetNightTareLossPower() {
    getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->resetNightTareLossPower();
  }

  boost::optional<double> ElectricLoadCenterInverterLookUpTable::nominalVoltageInput() const {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->nominalVoltageInput();
  }

  bool ElectricLoadCenterInverterLookUpTable::setNominalVoltageInput(double nominalVoltageInput) {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->setNominalVoltageInput(nominalVoltageInput);
  }

  void ElectricLoadCenterInverterLookUpTable::resetNominalVoltageInput() {
    getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->resetNominalVoltageInput();
  }

  boost::optional<double> ElectricLoadCenterInverterLookUpTable::efficiencyAt10PowerAndNominalVoltage() const {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->efficiencyAt10PowerAndNominalVoltage();
  }

  bool ElectricLoadCenterInverterLookUpTable::setEfficiencyAt10PowerAndNominalVoltage(double efficiencyAt10PowerAndNominalVoltage) {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->setEfficiencyAt10PowerAndNominalVoltage(
      efficiencyAt10PowerAndNominalVoltage);
  }

  void ElectricLoadCenterInverterLookUpTable::resetEfficiencyAt10PowerAndNominalVoltage() {
    getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->resetEfficiencyAt10PowerAndNominalVoltage();
  }

  boost::optional<double> ElectricLoadCenterInverterLookUpTable::efficiencyAt20PowerAndNominalVoltage() const {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->efficiencyAt20PowerAndNominalVoltage();
  }

  bool ElectricLoadCenterInverterLookUpTable::setEfficiencyAt20PowerAndNominalVoltage(double efficiencyAt20PowerAndNominalVoltage) {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->setEfficiencyAt20PowerAndNominalVoltage(
      efficiencyAt20PowerAndNominalVoltage);
  }

  void ElectricLoadCenterInverterLookUpTable::resetEfficiencyAt20PowerAndNominalVoltage() {
    getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->resetEfficiencyAt20PowerAndNominalVoltage();
  }

  boost::optional<double> ElectricLoadCenterInverterLookUpTable::efficiencyAt30PowerAndNominalVoltage() const {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->efficiencyAt30PowerAndNominalVoltage();
  }

  bool ElectricLoadCenterInverterLookUpTable::setEfficiencyAt30PowerAndNominalVoltage(double efficiencyAt30PowerAndNominalVoltage) {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->setEfficiencyAt30PowerAndNominalVoltage(
      efficiencyAt30PowerAndNominalVoltage);
  }

  void ElectricLoadCenterInverterLookUpTable::resetEfficiencyAt30PowerAndNominalVoltage() {
    getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->resetEfficiencyAt30PowerAndNominalVoltage();
  }

  boost::optional<double> ElectricLoadCenterInverterLookUpTable::efficiencyAt50PowerAndNominalVoltage() const {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->efficiencyAt50PowerAndNominalVoltage();
  }

  bool ElectricLoadCenterInverterLookUpTable::setEfficiencyAt50PowerAndNominalVoltage(double efficiencyAt50PowerAndNominalVoltage) {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->setEfficiencyAt50PowerAndNominalVoltage(
      efficiencyAt50PowerAndNominalVoltage);
  }

  void ElectricLoadCenterInverterLookUpTable::resetEfficiencyAt50PowerAndNominalVoltage() {
    getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->resetEfficiencyAt50PowerAndNominalVoltage();
  }

  boost::optional<double> ElectricLoadCenterInverterLookUpTable::efficiencyAt75PowerAndNominalVoltage() const {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->efficiencyAt75PowerAndNominalVoltage();
  }

  bool ElectricLoadCenterInverterLookUpTable::setEfficiencyAt75PowerAndNominalVoltage(double efficiencyAt75PowerAndNominalVoltage) {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->setEfficiencyAt75PowerAndNominalVoltage(
      efficiencyAt75PowerAndNominalVoltage);
  }

  void ElectricLoadCenterInverterLookUpTable::resetEfficiencyAt75PowerAndNominalVoltage() {
    getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->resetEfficiencyAt75PowerAndNominalVoltage();
  }

  boost::optional<double> ElectricLoadCenterInverterLookUpTable::efficiencyAt100PowerAndNominalVoltage() const {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->efficiencyAt100PowerAndNominalVoltage();
  }

  bool ElectricLoadCenterInverterLookUpTable::setEfficiencyAt100PowerAndNominalVoltage(double efficiencyAt100PowerAndNominalVoltage) {
    return getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->setEfficiencyAt100PowerAndNominalVoltage(
      efficiencyAt100PowerAndNominalVoltage);
  }

  void ElectricLoadCenterInverterLookUpTable::resetEfficiencyAt100PowerAndNominalVoltage() {
    getImpl<detail::ElectricLoadCenterInverterLookUpTable_Impl>()->resetEfficiencyAt100PowerAndNominalVoltage();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ElectricLoadCenterInverterLookUpTable_Impl::radiativeFraction() const {
      return getDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::RadiativeFraction, true);
    }

    bool ElectricLoadCenterInverterLookUpTable_Impl::setRadiativeFraction(double radiativeFraction) {
      const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::RadiativeFraction, radiativeFraction);
      return result;
    }

    void ElectricLoadCenterInverterLookUpTable_Impl::resetRadiativeFraction() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::RadiativeFraction, ""));
    }

    boost::optional<double> ElectricLoadCenterInverterLookUpTable_Impl::ratedMaximumContinuousOutputPower() const {
      return getDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::RatedMaximumContinuousOutputPower, true);
    }

    bool ElectricLoadCenterInverterLookUpTable_Impl::setRatedMaximumContinuousOutputPower(double ratedMaximumContinuousOutputPower) {
      const bool result =
        setDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::RatedMaximumContinuousOutputPower, ratedMaximumContinuousOutputPower);
      OS_ASSERT(result);
      return result;
    }

    void ElectricLoadCenterInverterLookUpTable_Impl::resetRatedMaximumContinuousOutputPower() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::RatedMaximumContinuousOutputPower, ""));
    }

    boost::optional<double> ElectricLoadCenterInverterLookUpTable_Impl::nightTareLossPower() const {
      return getDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::NightTareLossPower, true);
    }

    bool ElectricLoadCenterInverterLookUpTable_Impl::setNightTareLossPower(double nightTareLossPower) {
      const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::NightTareLossPower, nightTareLossPower);
      OS_ASSERT(result);
      return result;
    }

    void ElectricLoadCenterInverterLookUpTable_Impl::resetNightTareLossPower() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::NightTareLossPower, ""));
    }

    boost::optional<double> ElectricLoadCenterInverterLookUpTable_Impl::nominalVoltageInput() const {
      return getDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::NominalVoltageInput, true);
    }

    bool ElectricLoadCenterInverterLookUpTable_Impl::setNominalVoltageInput(double nominalVoltageInput) {
      const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::NominalVoltageInput, nominalVoltageInput);
      OS_ASSERT(result);
      return result;
    }

    void ElectricLoadCenterInverterLookUpTable_Impl::resetNominalVoltageInput() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::NominalVoltageInput, ""));
    }

    boost::optional<double> ElectricLoadCenterInverterLookUpTable_Impl::efficiencyAt10PowerAndNominalVoltage() const {
      return getDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat10_PowerandNominalVoltage, true);
    }

    bool ElectricLoadCenterInverterLookUpTable_Impl::setEfficiencyAt10PowerAndNominalVoltage(double efficiencyAt10PowerAndNominalVoltage) {
      const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat10_PowerandNominalVoltage,
                                    efficiencyAt10PowerAndNominalVoltage);
      return result;
    }

    void ElectricLoadCenterInverterLookUpTable_Impl::resetEfficiencyAt10PowerAndNominalVoltage() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat10_PowerandNominalVoltage, ""));
    }

    boost::optional<double> ElectricLoadCenterInverterLookUpTable_Impl::efficiencyAt20PowerAndNominalVoltage() const {
      return getDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat20_PowerandNominalVoltage, true);
    }

    bool ElectricLoadCenterInverterLookUpTable_Impl::setEfficiencyAt20PowerAndNominalVoltage(double efficiencyAt20PowerAndNominalVoltage) {
      const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat20_PowerandNominalVoltage,
                                    efficiencyAt20PowerAndNominalVoltage);
      return result;
    }

    void ElectricLoadCenterInverterLookUpTable_Impl::resetEfficiencyAt20PowerAndNominalVoltage() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat20_PowerandNominalVoltage, ""));
    }

    boost::optional<double> ElectricLoadCenterInverterLookUpTable_Impl::efficiencyAt30PowerAndNominalVoltage() const {
      return getDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat30_PowerandNominalVoltage, true);
    }

    bool ElectricLoadCenterInverterLookUpTable_Impl::setEfficiencyAt30PowerAndNominalVoltage(double efficiencyAt30PowerAndNominalVoltage) {
      const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat30_PowerandNominalVoltage,
                                    efficiencyAt30PowerAndNominalVoltage);
      return result;
    }

    void ElectricLoadCenterInverterLookUpTable_Impl::resetEfficiencyAt30PowerAndNominalVoltage() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat30_PowerandNominalVoltage, ""));
    }

    boost::optional<double> ElectricLoadCenterInverterLookUpTable_Impl::efficiencyAt50PowerAndNominalVoltage() const {
      return getDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat50_PowerandNominalVoltage, true);
    }

    bool ElectricLoadCenterInverterLookUpTable_Impl::setEfficiencyAt50PowerAndNominalVoltage(double efficiencyAt50PowerAndNominalVoltage) {
      const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat50_PowerandNominalVoltage,
                                    efficiencyAt50PowerAndNominalVoltage);
      return result;
    }

    void ElectricLoadCenterInverterLookUpTable_Impl::resetEfficiencyAt50PowerAndNominalVoltage() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat50_PowerandNominalVoltage, ""));
    }

    boost::optional<double> ElectricLoadCenterInverterLookUpTable_Impl::efficiencyAt75PowerAndNominalVoltage() const {
      return getDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat75_PowerandNominalVoltage, true);
    }

    bool ElectricLoadCenterInverterLookUpTable_Impl::setEfficiencyAt75PowerAndNominalVoltage(double efficiencyAt75PowerAndNominalVoltage) {
      const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat75_PowerandNominalVoltage,
                                    efficiencyAt75PowerAndNominalVoltage);
      return result;
    }

    void ElectricLoadCenterInverterLookUpTable_Impl::resetEfficiencyAt75PowerAndNominalVoltage() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat75_PowerandNominalVoltage, ""));
    }

    boost::optional<double> ElectricLoadCenterInverterLookUpTable_Impl::efficiencyAt100PowerAndNominalVoltage() const {
      return getDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat100_PowerandNominalVoltage, true);
    }

    bool ElectricLoadCenterInverterLookUpTable_Impl::setEfficiencyAt100PowerAndNominalVoltage(double efficiencyAt100PowerAndNominalVoltage) {
      const bool result = setDouble(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat100_PowerandNominalVoltage,
                                    efficiencyAt100PowerAndNominalVoltage);
      return result;
    }

    void ElectricLoadCenterInverterLookUpTable_Impl::resetEfficiencyAt100PowerAndNominalVoltage() {
      OS_ASSERT(setString(openstudio::ElectricLoadCenter_Inverter_LookUpTableFields::Efficiencyat100_PowerandNominalVoltage, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
