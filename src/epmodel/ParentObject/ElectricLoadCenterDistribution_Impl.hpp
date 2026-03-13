/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERDISTRIBUTION_IMPL_HPP
#define EPMODEL_ELECTRICLOADCENTERDISTRIBUTION_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ElectricLoadCenterDistribution_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~ElectricLoadCenterDistribution_Impl() override = default;

      // Schema Alignment Notes:
      // - ElectricLoadCenter:Generators is represented through ElectricLoadCenterDistribution + Generator objects.
      // - Extensible generator-list fields are relationship-like and intentionally out of scalar scaffold scope.

      std::vector<std::string> generatorOperationSchemeTypeValues() const;
      std::vector<std::string> electricalBussTypeValues() const;
      std::vector<std::string> storageOperationSchemeValues() const;

      std::string generatorOperationSchemeType() const;
      bool setGeneratorOperationSchemeType(const std::string& generatorOperationSchemeType);
      bool isGeneratorOperationSchemeTypeDefaulted() const;
      void resetGeneratorOperationSchemeType();

      boost::optional<double> demandLimitSchemePurchasedElectricDemandLimit() const;
      bool setDemandLimitSchemePurchasedElectricDemandLimit(double demandLimitSchemePurchasedElectricDemandLimit);
      void resetDemandLimitSchemePurchasedElectricDemandLimit();

      boost::optional<std::string> trackMeterSchemeMeterName() const;
      bool setTrackMeterSchemeMeterName(const std::string& trackMeterSchemeMeterName);
      void resetTrackMeterSchemeMeterName();

      std::string electricalBussType() const;
      bool setElectricalBussType(const std::string& electricalBussType);
      bool isElectricalBussTypeDefaulted() const;
      void resetElectricalBussType();

      std::string storageOperationScheme() const;
      bool setStorageOperationScheme(const std::string& operationScheme);
      bool isStorageOperationSchemeDefaulted() const;
      void resetStorageOperationScheme();

      boost::optional<std::string> storageControlTrackMeterName() const;
      bool setStorageControlTrackMeterName(const std::string& meterName);
      void resetStorageControlTrackMeterName();

      double maximumStorageStateofChargeFraction() const;
      bool setMaximumStorageStateofChargeFraction(double maxStateofCharge);
      bool isMaximumStorageStateofChargeFractionDefaulted() const;
      void resetMaximumStorageStateofChargeFraction();

      double minimumStorageStateofChargeFraction() const;
      bool setMinimumStorageStateofChargeFraction(double minStateofCharge);
      bool isMinimumStorageStateofChargeFractionDefaulted() const;
      void resetMinimumStorageStateofChargeFraction();

      boost::optional<double> designStorageControlChargePower() const;
      bool setDesignStorageControlChargePower(double designStorageControlChargePower);
      void resetDesignStorageControlChargePower();

      boost::optional<double> designStorageControlDischargePower() const;
      bool setDesignStorageControlDischargePower(double designStorageControlDischargePower);
      void resetDesignStorageControlDischargePower();

      boost::optional<double> storageControlUtilityDemandTarget() const;
      bool setStorageControlUtilityDemandTarget(double storageControlUtilityDemandTarget);
      void resetStorageControlUtilityDemandTarget();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
