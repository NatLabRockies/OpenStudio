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

/** \brief Defines how generators, storage, and purchased electricity are distributed and controlled.
 *
 * \par EnergyPlus object
 * \epobject{group-electric-load-center-generator.html#electricloadcenterdistribution,ElectricLoadCenter:Distribution}
 *
 * \par Important behavior
 * Generator-operation, electrical-bus, storage-operation, demand-limit, metering, and storage-control fields are persisted directly.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::ElectricLoadCenterDistribution</code>.
 * <b>Not yet available:</b> Generator, inverter, storage, converter, transformer, schedule, and child-management relationships from Model are not exposed.
 *
 * \par Known limitations
 * Generator, inverter, storage, and load-center child objects are separate relationships and are not owned by this scalar wrapper.
 */
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
