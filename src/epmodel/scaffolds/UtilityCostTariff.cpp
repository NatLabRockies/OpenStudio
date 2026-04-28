/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "UtilityCostTariff.hpp"
#include "UtilityCostTariff_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/UtilityCost_Tariff_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  UtilityCostTariff::UtilityCostTariff(const Model& model) : ModelObject(UtilityCostTariff::iddObjectType(), model) {}

  UtilityCostTariff::UtilityCostTariff(std::shared_ptr<detail::UtilityCostTariff_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType UtilityCostTariff::iddObjectType() {
    return IddObjectType::UtilityCost_Tariff;
  }

  std::vector<std::string> UtilityCostTariff::conversionFactorChoiceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::UtilityCost_TariffFields::ConversionFactorChoice);
  }

  std::vector<std::string> UtilityCostTariff::demandWindowLengthValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::UtilityCost_TariffFields::DemandWindowLength);
  }

  std::vector<std::string> UtilityCostTariff::buyOrSellValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::UtilityCost_TariffFields::BuyOrSell);
  }

  boost::optional<std::string> UtilityCostTariff::conversionFactorChoice() const {
    return getImpl<detail::UtilityCostTariff_Impl>()->conversionFactorChoice();
  }

  bool UtilityCostTariff::setConversionFactorChoice(const std::string& conversionFactorChoice) {
    return getImpl<detail::UtilityCostTariff_Impl>()->setConversionFactorChoice(conversionFactorChoice);
  }

  void UtilityCostTariff::resetConversionFactorChoice() {
    getImpl<detail::UtilityCostTariff_Impl>()->resetConversionFactorChoice();
  }

  boost::optional<double> UtilityCostTariff::energyConversionFactor() const {
    return getImpl<detail::UtilityCostTariff_Impl>()->energyConversionFactor();
  }

  bool UtilityCostTariff::setEnergyConversionFactor(double energyConversionFactor) {
    return getImpl<detail::UtilityCostTariff_Impl>()->setEnergyConversionFactor(energyConversionFactor);
  }

  void UtilityCostTariff::resetEnergyConversionFactor() {
    getImpl<detail::UtilityCostTariff_Impl>()->resetEnergyConversionFactor();
  }

  boost::optional<double> UtilityCostTariff::demandConversionFactor() const {
    return getImpl<detail::UtilityCostTariff_Impl>()->demandConversionFactor();
  }

  bool UtilityCostTariff::setDemandConversionFactor(double demandConversionFactor) {
    return getImpl<detail::UtilityCostTariff_Impl>()->setDemandConversionFactor(demandConversionFactor);
  }

  void UtilityCostTariff::resetDemandConversionFactor() {
    getImpl<detail::UtilityCostTariff_Impl>()->resetDemandConversionFactor();
  }

  boost::optional<std::string> UtilityCostTariff::demandWindowLength() const {
    return getImpl<detail::UtilityCostTariff_Impl>()->demandWindowLength();
  }

  bool UtilityCostTariff::setDemandWindowLength(const std::string& demandWindowLength) {
    return getImpl<detail::UtilityCostTariff_Impl>()->setDemandWindowLength(demandWindowLength);
  }

  void UtilityCostTariff::resetDemandWindowLength() {
    getImpl<detail::UtilityCostTariff_Impl>()->resetDemandWindowLength();
  }

  boost::optional<std::string> UtilityCostTariff::monthlyChargeorVariableName() const {
    return getImpl<detail::UtilityCostTariff_Impl>()->monthlyChargeorVariableName();
  }

  bool UtilityCostTariff::setMonthlyChargeorVariableName(const std::string& monthlyChargeorVariableName) {
    return getImpl<detail::UtilityCostTariff_Impl>()->setMonthlyChargeorVariableName(monthlyChargeorVariableName);
  }

  void UtilityCostTariff::resetMonthlyChargeorVariableName() {
    getImpl<detail::UtilityCostTariff_Impl>()->resetMonthlyChargeorVariableName();
  }

  boost::optional<std::string> UtilityCostTariff::minimumMonthlyChargeorVariableName() const {
    return getImpl<detail::UtilityCostTariff_Impl>()->minimumMonthlyChargeorVariableName();
  }

  bool UtilityCostTariff::setMinimumMonthlyChargeorVariableName(const std::string& minimumMonthlyChargeorVariableName) {
    return getImpl<detail::UtilityCostTariff_Impl>()->setMinimumMonthlyChargeorVariableName(minimumMonthlyChargeorVariableName);
  }

  void UtilityCostTariff::resetMinimumMonthlyChargeorVariableName() {
    getImpl<detail::UtilityCostTariff_Impl>()->resetMinimumMonthlyChargeorVariableName();
  }

  boost::optional<std::string> UtilityCostTariff::groupName() const {
    return getImpl<detail::UtilityCostTariff_Impl>()->groupName();
  }

  bool UtilityCostTariff::setGroupName(const std::string& groupName) {
    return getImpl<detail::UtilityCostTariff_Impl>()->setGroupName(groupName);
  }

  void UtilityCostTariff::resetGroupName() {
    getImpl<detail::UtilityCostTariff_Impl>()->resetGroupName();
  }

  std::string UtilityCostTariff::buyOrSell() const {
    return getImpl<detail::UtilityCostTariff_Impl>()->buyOrSell();
  }

  bool UtilityCostTariff::setBuyOrSell(const std::string& buyOrSell) {
    return getImpl<detail::UtilityCostTariff_Impl>()->setBuyOrSell(buyOrSell);
  }

  void UtilityCostTariff::resetBuyOrSell() {
    getImpl<detail::UtilityCostTariff_Impl>()->resetBuyOrSell();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {
      bool setAlphaField(UtilityCostTariff_Impl* impl, unsigned fieldIndex, const std::string& value) {
        if (impl->setString(fieldIndex, value)) {
          return true;
        }
        return impl->setString(fieldIndex, value, false);
      }
    }  // namespace

    boost::optional<std::string> UtilityCostTariff_Impl::conversionFactorChoice() const {
      const auto value = getString(openstudio::UtilityCost_TariffFields::ConversionFactorChoice, true);
      if (value && !value->empty()) {
        return *value;
      }
      return boost::none;
    }

    bool UtilityCostTariff_Impl::setConversionFactorChoice(const std::string& conversionFactorChoice) {
      return setAlphaField(this, openstudio::UtilityCost_TariffFields::ConversionFactorChoice, conversionFactorChoice);
    }

    void UtilityCostTariff_Impl::resetConversionFactorChoice() {
      OS_ASSERT(setString(openstudio::UtilityCost_TariffFields::ConversionFactorChoice, ""));
    }

    boost::optional<double> UtilityCostTariff_Impl::energyConversionFactor() const {
      return getDouble(openstudio::UtilityCost_TariffFields::EnergyConversionFactor, true);
    }

    bool UtilityCostTariff_Impl::setEnergyConversionFactor(double energyConversionFactor) {
      const bool result = setDouble(openstudio::UtilityCost_TariffFields::EnergyConversionFactor, energyConversionFactor);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostTariff_Impl::resetEnergyConversionFactor() {
      OS_ASSERT(setString(openstudio::UtilityCost_TariffFields::EnergyConversionFactor, ""));
    }

    boost::optional<double> UtilityCostTariff_Impl::demandConversionFactor() const {
      return getDouble(openstudio::UtilityCost_TariffFields::DemandConversionFactor, true);
    }

    bool UtilityCostTariff_Impl::setDemandConversionFactor(double demandConversionFactor) {
      const bool result = setDouble(openstudio::UtilityCost_TariffFields::DemandConversionFactor, demandConversionFactor);
      OS_ASSERT(result);
      return result;
    }

    void UtilityCostTariff_Impl::resetDemandConversionFactor() {
      OS_ASSERT(setString(openstudio::UtilityCost_TariffFields::DemandConversionFactor, ""));
    }

    boost::optional<std::string> UtilityCostTariff_Impl::demandWindowLength() const {
      const auto value = getString(openstudio::UtilityCost_TariffFields::DemandWindowLength, true);
      if (value && !value->empty()) {
        return *value;
      }
      return boost::none;
    }

    bool UtilityCostTariff_Impl::setDemandWindowLength(const std::string& demandWindowLength) {
      return setAlphaField(this, openstudio::UtilityCost_TariffFields::DemandWindowLength, demandWindowLength);
    }

    void UtilityCostTariff_Impl::resetDemandWindowLength() {
      OS_ASSERT(setString(openstudio::UtilityCost_TariffFields::DemandWindowLength, ""));
    }

    boost::optional<std::string> UtilityCostTariff_Impl::monthlyChargeorVariableName() const {
      const auto value = getString(openstudio::UtilityCost_TariffFields::MonthlyChargeorVariableName, true);
      if (value && !value->empty()) {
        return *value;
      }
      return boost::none;
    }

    bool UtilityCostTariff_Impl::setMonthlyChargeorVariableName(const std::string& monthlyChargeorVariableName) {
      return setAlphaField(this, openstudio::UtilityCost_TariffFields::MonthlyChargeorVariableName, monthlyChargeorVariableName);
    }

    void UtilityCostTariff_Impl::resetMonthlyChargeorVariableName() {
      OS_ASSERT(setString(openstudio::UtilityCost_TariffFields::MonthlyChargeorVariableName, ""));
    }

    boost::optional<std::string> UtilityCostTariff_Impl::minimumMonthlyChargeorVariableName() const {
      const auto value = getString(openstudio::UtilityCost_TariffFields::MinimumMonthlyChargeorVariableName, true);
      if (value && !value->empty()) {
        return *value;
      }
      return boost::none;
    }

    bool UtilityCostTariff_Impl::setMinimumMonthlyChargeorVariableName(const std::string& minimumMonthlyChargeorVariableName) {
      return setAlphaField(this, openstudio::UtilityCost_TariffFields::MinimumMonthlyChargeorVariableName, minimumMonthlyChargeorVariableName);
    }

    void UtilityCostTariff_Impl::resetMinimumMonthlyChargeorVariableName() {
      OS_ASSERT(setString(openstudio::UtilityCost_TariffFields::MinimumMonthlyChargeorVariableName, ""));
    }

    boost::optional<std::string> UtilityCostTariff_Impl::groupName() const {
      const auto value = getString(openstudio::UtilityCost_TariffFields::GroupName, true);
      if (value && !value->empty()) {
        return *value;
      }
      return boost::none;
    }

    bool UtilityCostTariff_Impl::setGroupName(const std::string& groupName) {
      return setAlphaField(this, openstudio::UtilityCost_TariffFields::GroupName, groupName);
    }

    void UtilityCostTariff_Impl::resetGroupName() {
      OS_ASSERT(setString(openstudio::UtilityCost_TariffFields::GroupName, ""));
    }

    std::string UtilityCostTariff_Impl::buyOrSell() const {
      const auto value = getString(openstudio::UtilityCost_TariffFields::BuyOrSell, true);
      OS_ASSERT(value);
      return *value;
    }

    bool UtilityCostTariff_Impl::setBuyOrSell(const std::string& buyOrSell) {
      return setAlphaField(this, openstudio::UtilityCost_TariffFields::BuyOrSell, buyOrSell);
    }

    void UtilityCostTariff_Impl::resetBuyOrSell() {
      OS_ASSERT(setString(openstudio::UtilityCost_TariffFields::BuyOrSell, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
