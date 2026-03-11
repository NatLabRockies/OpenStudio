/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERSTORAGESIMPLE_IMPL_HPP
#define EPMODEL_ELECTRICLOADCENTERSTORAGESIMPLE_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ElectricLoadCenterStorageSimple_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ElectricLoadCenterStorageSimple_Impl() override = default;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
