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
    bool setRadiativeFraction(double radiativeFraction);

    std::string lifetimeModel() const;
    bool setLifetimeModel(const std::string& lifetimeModel);

    int numberofCellsinSeries() const;
    bool setNumberofCellsinSeries(int numberofCellsinSeries);

    int numberofStringsinParallel() const;
    bool setNumberofStringsinParallel(int numberofStringsinParallel);

    double initialFractionalStateofCharge() const;
    bool setInitialFractionalStateofCharge(double initialFractionalStateofCharge);

    double dctoDCChargingEfficiency() const;
    bool setDCtoDCChargingEfficiency(double dctoDCChargingEfficiency);

    double batteryMass() const;
    bool setBatteryMass(double batteryMass);

    double batterySurfaceArea() const;
    bool setBatterySurfaceArea(double batterySurfaceArea);

    double batterySpecificHeatCapacity() const;
    bool setBatterySpecificHeatCapacity(double batterySpecificHeatCapacity);

    double heatTransferCoefficientBetweenBatteryandAmbient() const;
    bool setHeatTransferCoefficientBetweenBatteryandAmbient(double heatTransferCoefficientBetweenBatteryandAmbient);

    double fullyChargedCellVoltage() const;
    bool setFullyChargedCellVoltage(double fullyChargedCellCapacity);

    double cellVoltageatEndofExponentialZone() const;
    bool setCellVoltageatEndofExponentialZone(double cellVoltageatEndofExponentialZone);

    double cellVoltageatEndofNominalZone() const;
    bool setCellVoltageatEndofNominalZone(double cellVoltageatEndofNominalZone);

    double defaultNominalCellVoltage() const;
    bool setDefaultNominalCellVoltage(double defaultNominalCellVoltage);

    double fullyChargedCellCapacity() const;
    bool setFullyChargedCellCapacity(double fullyChargedCellCapacity);

    double fractionofCellCapacityRemovedattheEndofExponentialZone() const;
    bool setFractionofCellCapacityRemovedattheEndofExponentialZone(double fractionofCellCapacityRemovedattheEndofExponentialZone);

    double fractionofCellCapacityRemovedattheEndofNominalZone() const;
    bool setFractionofCellCapacityRemovedattheEndofNominalZone(double fractionofCellCapacityRemovedattheEndofNominalZone);

    double chargeRateatWhichVoltagevsCapacityCurveWasGenerated() const;
    bool setChargeRateatWhichVoltagevsCapacityCurveWasGenerated(double chargeRateatWhichVoltagevsCapacityCurveWasGenerated);

    double batteryCellInternalElectricalResistance() const;
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
