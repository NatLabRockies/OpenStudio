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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
