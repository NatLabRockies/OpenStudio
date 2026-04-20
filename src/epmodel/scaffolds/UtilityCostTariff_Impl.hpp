/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_UTILITYCOSTTARIFF_IMPL_HPP
#define EPMODEL_UTILITYCOSTTARIFF_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API UtilityCostTariff_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~UtilityCostTariff_Impl() override = default;

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
