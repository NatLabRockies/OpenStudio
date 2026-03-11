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

  std::string generatorOperationSchemeType() const;
  bool isGeneratorOperationSchemeTypeDefaulted() const;
  bool setGeneratorOperationSchemeType(const std::string& generatorOperationSchemeType);
  void resetGeneratorOperationSchemeType();

  boost::optional<double> demandLimitSchemePurchasedElectricDemandLimit() const;
  bool setDemandLimitSchemePurchasedElectricDemandLimit(double demandLimitSchemePurchasedElectricDemandLimit);
  void resetDemandLimitSchemePurchasedElectricDemandLimit();

  boost::optional<std::string> trackMeterSchemeMeterName() const;
  bool setTrackMeterSchemeMeterName(const std::string& trackMeterSchemeMeterName);
  void resetTrackMeterSchemeMeterName();

  std::string electricalBussType() const;
  bool isElectricalBussTypeDefaulted() const;
  bool setElectricalBussType(const std::string& electricalBussType);
  void resetElectricalBussType();

  std::string storageOperationScheme() const;
  bool isStorageOperationSchemeDefaulted() const;
  bool setStorageOperationScheme(const std::string& operationScheme);
  void resetStorageOperationScheme();

  boost::optional<std::string> storageControlTrackMeterName() const;
  bool setStorageControlTrackMeterName(const std::string& meterName);
  void resetStorageControlTrackMeterName();

  double maximumStorageStateofChargeFraction() const;
  bool isMaximumStorageStateofChargeFractionDefaulted() const;
  bool setMaximumStorageStateofChargeFraction(double maxStateofCharge);
  void resetMaximumStorageStateofChargeFraction();

  double minimumStorageStateofChargeFraction() const;
  bool isMinimumStorageStateofChargeFractionDefaulted() const;
  bool setMinimumStorageStateofChargeFraction(double minStateofCharge);
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

  std::vector<std::string> generatorOperationSchemeTypeValues() const;
  std::vector<std::string> electricalBussTypeValues() const;
  std::vector<std::string> storageOperationSchemeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
