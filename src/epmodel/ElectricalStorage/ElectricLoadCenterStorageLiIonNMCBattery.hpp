/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICLOADCENTERSTORAGELIIONNMCBATTERY_HPP
#define EPMODEL_ELECTRICLOADCENTERSTORAGELIIONNMCBATTERY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ElectricLoadCenterStorageLiIonNMCBattery_Impl;
}

class EPMODEL_API ElectricLoadCenterStorageLiIonNMCBattery : public ModelObject
{
 public:
  explicit ElectricLoadCenterStorageLiIonNMCBattery(const Model& model);

  explicit ElectricLoadCenterStorageLiIonNMCBattery(const Model& model, int numberofCellsinSeries, int numberofStringsinParallel,
                                                    double batteryMass, double batterySurfaceArea);

  virtual ~ElectricLoadCenterStorageLiIonNMCBattery() override = default;
  ElectricLoadCenterStorageLiIonNMCBattery(const ElectricLoadCenterStorageLiIonNMCBattery& other) = default;
  ElectricLoadCenterStorageLiIonNMCBattery(ElectricLoadCenterStorageLiIonNMCBattery&& other) = default;
  ElectricLoadCenterStorageLiIonNMCBattery& operator=(const ElectricLoadCenterStorageLiIonNMCBattery&) = default;
  ElectricLoadCenterStorageLiIonNMCBattery& operator=(ElectricLoadCenterStorageLiIonNMCBattery&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> lifetimeModelValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::ElectricLoadCenterStorageLiIonNMCBattery scalar accessor names/signatures.
  // - Field Mapping: scalar APIs map directly to ElectricLoadCenter:Storage:LiIonNMCBattery scalar fields.
  // - Field Mapping: Availability Schedule Name and Zone Name are relationship-like fields and intentionally excluded.
  // - ForwardTranslator evidence: ForwardTranslateElectricLoadCenterStorageLiIonNMCBattery maps these scalar APIs directly.
  // - Naming Drift: Getter `dctoDCChargingEfficiency` and setter `setDCtoDCChargingEfficiency` both map to
  //   `DCtoDCChargingEfficiency` to preserve existing model API.
  // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.
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

 protected:
  using ImplType = detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ElectricLoadCenterStorageLiIonNMCBattery(std::shared_ptr<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
