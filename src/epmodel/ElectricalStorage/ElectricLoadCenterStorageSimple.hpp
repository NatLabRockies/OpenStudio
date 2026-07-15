/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERSTORAGESIMPLE_HPP
#define EPMODEL_ELECTRICLOADCENTERSTORAGESIMPLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ElectricLoadCenterStorageSimple_Impl;
  }

  class EPMODEL_API ElectricLoadCenterStorageSimple : public ModelObject
  {
   public:
    explicit ElectricLoadCenterStorageSimple(const Model& model);

    virtual ~ElectricLoadCenterStorageSimple() override = default;
    ElectricLoadCenterStorageSimple(const ElectricLoadCenterStorageSimple& other) = default;
    ElectricLoadCenterStorageSimple(ElectricLoadCenterStorageSimple&& other) = default;
    ElectricLoadCenterStorageSimple& operator=(const ElectricLoadCenterStorageSimple&) = default;
    ElectricLoadCenterStorageSimple& operator=(ElectricLoadCenterStorageSimple&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::ElectricLoadCenterStorageSimple scalar accessor names/signatures.
    // - Field Mapping: scalar APIs map directly to ElectricLoadCenter:Storage:Simple scalar fields.
    // - Field Mapping: Availability Schedule Name and Zone Name are relationship-like fields and are intentionally excluded.
    // - ForwardTranslator evidence: ForwardTranslateElectricLoadCenterStorageSimple maps these preserved scalar APIs directly.
    // - TODO(parity): Add relationship APIs incrementally without breaking preserved scalar signatures.
    double radiativeFractionforZoneHeatGains() const;
    bool isRadiativeFractionforZoneHeatGainsDefaulted() const;
    bool setRadiativeFractionforZoneHeatGains(double radiativeFractionforZoneHeatGains);
    void resetRadiativeFractionforZoneHeatGains();

    double nominalEnergeticEfficiencyforCharging() const;
    bool isNominalEnergeticEfficiencyforChargingDefaulted() const;
    bool setNominalEnergeticEfficiencyforCharging(double nominalEnergeticEfficiencyforCharging);
    void resetNominalEnergeticEfficiencyforCharging();

    double nominalDischargingEnergeticEfficiency() const;
    bool isNominalDischargingEnergeticEfficiencyDefaulted() const;
    bool setNominalDischargingEnergeticEfficiency(double nominalDischargingEnergeticEfficiency);
    void resetNominalDischargingEnergeticEfficiency();

    double maximumStorageCapacity() const;
    bool setMaximumStorageCapacity(double maximumStorageCapacity);

    double maximumPowerforDischarging() const;
    bool setMaximumPowerforDischarging(double maximumPowerforDischarging);

    double maximumPowerforCharging() const;
    bool setMaximumPowerforCharging(double maximumPowerforCharging);

    double initialStateofCharge() const;
    bool isInitialStateofChargeDefaulted() const;
    bool setInitialStateofCharge(double initialStateofCharge);
    void resetInitialStateofCharge();

   protected:
    using ImplType = detail::ElectricLoadCenterStorageSimple_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ElectricLoadCenterStorageSimple(std::shared_ptr<detail::ElectricLoadCenterStorageSimple_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
