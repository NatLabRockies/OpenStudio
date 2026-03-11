/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERDISTRIBUTION_HPP
#define EPMODEL_ELECTRICLOADCENTERDISTRIBUTION_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ElectricLoadCenterDistribution_Impl;
}

class EPMODEL_API ElectricLoadCenterDistribution : public ParentObject
{
 public:
  explicit ElectricLoadCenterDistribution(const Model& model);

  virtual ~ElectricLoadCenterDistribution() override = default;
  ElectricLoadCenterDistribution(const ElectricLoadCenterDistribution& other) = default;
  ElectricLoadCenterDistribution(ElectricLoadCenterDistribution&& other) = default;
  ElectricLoadCenterDistribution& operator=(const ElectricLoadCenterDistribution&) = default;
  ElectricLoadCenterDistribution& operator=(ElectricLoadCenterDistribution&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> generatorOperationSchemeTypeValues();
  static std::vector<std::string> electricalBussTypeValues();
  static std::vector<std::string> storageOperationSchemeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ElectricLoadCenterDistribution scalar accessor names/signatures.
  // - API: EnergyPlus ElectricLoadCenter:Generators maps to this class; no separate epmodel class is introduced.
  // - Field Mapping: demandLimitSchemePurchasedElectricDemandLimit maps to EnergyPlus
  //   GeneratorDemandLimitSchemePurchasedElectricDemandLimit.
  // - Field Mapping: trackMeterSchemeMeterName maps to EnergyPlus GeneratorTrackMeterSchemeMeterName.
  // - Field Mapping: ElectricLoadCenter:Generators extensible group fields are relationship-like and intentionally excluded from scalar accessors.
  // - Field Mapping: Generator extensible scalar values (rated power, availability schedule, thermal/electric ratio) are carried by Generator APIs.
  // - Field Mapping: Relationship fields (generator list, schedules, inverter/storage/transformer references) are intentionally excluded.
  // - ForwardTranslator evidence: ForwardTranslateElectricLoadCenterDistribution.cpp writes these scalar fields directly.
  // - TODO(parity): Add non-scalar parity incrementally without changing preserved scalar signatures.
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

 protected:
  using ImplType = detail::ElectricLoadCenterDistribution_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ElectricLoadCenterDistribution(std::shared_ptr<detail::ElectricLoadCenterDistribution_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
