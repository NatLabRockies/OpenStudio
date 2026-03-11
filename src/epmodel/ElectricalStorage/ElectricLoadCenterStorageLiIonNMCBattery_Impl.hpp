/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERSTORAGELIIONNMCBATTERY_IMPL_HPP
#define EPMODEL_ELECTRICLOADCENTERSTORAGELIIONNMCBATTERY_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ElectricLoadCenterStorageLiIonNMCBattery_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ElectricLoadCenterStorageLiIonNMCBattery_Impl() override = default;

  double radiativeFraction() const;

  std::string lifetimeModel() const;

  int numberofCellsinSeries() const;

  int numberofStringsinParallel() const;

  double initialFractionalStateofCharge() const;

  double dctoDCChargingEfficiency() const;

  double batteryMass() const;

  double batterySurfaceArea() const;

  double batterySpecificHeatCapacity() const;

  double heatTransferCoefficientBetweenBatteryandAmbient() const;

  double fullyChargedCellVoltage() const;

  double cellVoltageatEndofExponentialZone() const;

  double cellVoltageatEndofNominalZone() const;

  double defaultNominalCellVoltage() const;

  double fullyChargedCellCapacity() const;

  double fractionofCellCapacityRemovedattheEndofExponentialZone() const;

  double fractionofCellCapacityRemovedattheEndofNominalZone() const;

  double chargeRateatWhichVoltagevsCapacityCurveWasGenerated() const;

  double batteryCellInternalElectricalResistance() const;

  bool setRadiativeFraction(double radiativeFraction);

  bool setLifetimeModel(const std::string& lifetimeModel);

  bool setNumberofCellsinSeries(int numberofCellsinSeries);

  bool setNumberofStringsinParallel(int numberofStringsinParallel);

  bool setInitialFractionalStateofCharge(double initialFractionalStateofCharge);

  bool setDCtoDCChargingEfficiency(double dctoDCChargingEfficiency);

  bool setBatteryMass(double batteryMass);

  bool setBatterySurfaceArea(double batterySurfaceArea);

  bool setBatterySpecificHeatCapacity(double batterySpecificHeatCapacity);

  bool setHeatTransferCoefficientBetweenBatteryandAmbient(double heatTransferCoefficientBetweenBatteryandAmbient);

  bool setFullyChargedCellVoltage(double fullyChargedCellCapacity);

  bool setCellVoltageatEndofExponentialZone(double cellVoltageatEndofExponentialZone);

  bool setCellVoltageatEndofNominalZone(double cellVoltageatEndofNominalZone);

  bool setDefaultNominalCellVoltage(double defaultNominalCellVoltage);

  bool setFullyChargedCellCapacity(double fullyChargedCellCapacity);

  bool setFractionofCellCapacityRemovedattheEndofExponentialZone(double fractionofCellCapacityRemovedattheEndofExponentialZone);

  bool setFractionofCellCapacityRemovedattheEndofNominalZone(double fractionofCellCapacityRemovedattheEndofNominalZone);

  bool setChargeRateatWhichVoltagevsCapacityCurveWasGenerated(double chargeRateatWhichVoltagevsCapacityCurveWasGenerated);

  bool setBatteryCellInternalElectricalResistance(double batteryCellInternalElectricalResistance);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
