/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_UTILITYCOSTTARIFF_HPP
#define EPMODEL_UTILITYCOSTTARIFF_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class UtilityCostTariff_Impl;
  }

  class EPMODEL_API UtilityCostTariff : public ModelObject
  {
   public:
    explicit UtilityCostTariff(const Model& model);

    virtual ~UtilityCostTariff() override = default;
    UtilityCostTariff(const UtilityCostTariff& other) = default;
    UtilityCostTariff(UtilityCostTariff&& other) = default;
    UtilityCostTariff& operator=(const UtilityCostTariff&) = default;
    UtilityCostTariff& operator=(UtilityCostTariff&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> conversionFactorChoiceValues();
    static std::vector<std::string> demandWindowLengthValues();
    static std::vector<std::string> buyOrSellValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists (UtilityCost:Tariff is OS-only), so scalar accessors mirror the EnergyPlus IDD naming.
    // - Field Mapping: Conversion Factor Choice, Energy Conversion Factor, Demand Conversion Factor, Demand Window Length,
    //   Monthly Charge or Variable Name, Minimum Monthly Charge or Variable Name, Group Name, and Buy Or Sell map directly to UtilityCost:Tariff.
    // - Field Mapping: Relationship fields (Output Meter Name, time-of-use/season/month schedules, and the real-time pricing/baseline
    //   schedule references) are deferred to a later parity pass.
    boost::optional<std::string> conversionFactorChoice() const;
    bool setConversionFactorChoice(const std::string& conversionFactorChoice);
    void resetConversionFactorChoice();

    boost::optional<double> energyConversionFactor() const;
    bool setEnergyConversionFactor(double energyConversionFactor);
    void resetEnergyConversionFactor();

    boost::optional<double> demandConversionFactor() const;
    bool setDemandConversionFactor(double demandConversionFactor);
    void resetDemandConversionFactor();

    boost::optional<std::string> demandWindowLength() const;
    bool setDemandWindowLength(const std::string& demandWindowLength);
    void resetDemandWindowLength();

    boost::optional<std::string> monthlyChargeorVariableName() const;
    bool setMonthlyChargeorVariableName(const std::string& monthlyChargeorVariableName);
    void resetMonthlyChargeorVariableName();

    boost::optional<std::string> minimumMonthlyChargeorVariableName() const;
    bool setMinimumMonthlyChargeorVariableName(const std::string& minimumMonthlyChargeorVariableName);
    void resetMinimumMonthlyChargeorVariableName();

    boost::optional<std::string> groupName() const;
    bool setGroupName(const std::string& groupName);
    void resetGroupName();

    std::string buyOrSell() const;
    bool setBuyOrSell(const std::string& buyOrSell);
    void resetBuyOrSell();

   protected:
    using ImplType = detail::UtilityCostTariff_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit UtilityCostTariff(std::shared_ptr<detail::UtilityCostTariff_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
