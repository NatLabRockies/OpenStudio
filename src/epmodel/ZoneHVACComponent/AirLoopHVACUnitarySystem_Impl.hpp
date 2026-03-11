/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYSYSTEM_IMPL_HPP
#define EPMODEL_AIRLOOPHVACUNITARYSYSTEM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirLoopHVACUnitarySystem_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirLoopHVACUnitarySystem_Impl() override = default;

  std::string controlType() const;
  bool isControlTypeDefaulted() const;
  bool setControlType(const std::string& controlType);
  void resetControlType();

  std::string dehumidificationControlType() const;
  bool isDehumidificationControlTypeDefaulted() const;
  bool setDehumidificationControlType(const std::string& dehumidificationControlType);
  void resetDehumidificationControlType();

  boost::optional<std::string> fanPlacement() const;
  bool setFanPlacement(const std::string& fanPlacement);
  void resetFanPlacement();

  double dXHeatingCoilSizingRatio() const;
  bool isDXHeatingCoilSizingRatioDefaulted() const;
  bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);
  void resetDXHeatingCoilSizingRatio();

  bool useDOASDXCoolingCoil() const;
  bool isUseDOASDXCoolingCoilDefaulted() const;
  bool setUseDOASDXCoolingCoil(bool useDOASDXCoolingCoil);
  void resetUseDOASDXCoolingCoil();

  double dOASDXCoolingCoilLeavingMinimumAirTemperature() const;
  bool isDOASDXCoolingCoilLeavingMinimumAirTemperatureDefaulted() const;
  bool isDOASDXCoolingCoilLeavingMinimumAirTemperatureAutosized() const;
  bool setDOASDXCoolingCoilLeavingMinimumAirTemperature(double dOASDXCoolingCoilLeavingMinimumAirTemperature);
  void resetDOASDXCoolingCoilLeavingMinimumAirTemperature();
  void autosizeDOASDXCoolingCoilLeavingMinimumAirTemperature();

  std::string latentLoadControl() const;
  bool isLatentLoadControlDefaulted() const;
  bool setLatentLoadControl(const std::string& latentLoadControl);
  void resetLatentLoadControl();

  std::string supplyAirFlowRateMethodDuringCoolingOperation() const;
  bool setSupplyAirFlowRateMethodDuringCoolingOperation(const std::string& supplyAirFlowRateMethodDuringCoolingOperation);
  void resetSupplyAirFlowRateMethodDuringCoolingOperation();

  boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;
  bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;
  bool setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation);
  void resetSupplyAirFlowRateDuringCoolingOperation();
  void autosizeSupplyAirFlowRateDuringCoolingOperation();

  boost::optional<double> supplyAirFlowRatePerFloorAreaDuringCoolingOperation() const;
  bool setSupplyAirFlowRatePerFloorAreaDuringCoolingOperation(double supplyAirFlowRatePerFloorAreaDuringCoolingOperation);
  void resetSupplyAirFlowRatePerFloorAreaDuringCoolingOperation();

  boost::optional<double> fractionofAutosizedDesignCoolingSupplyAirFlowRate() const;
  bool setFractionofAutosizedDesignCoolingSupplyAirFlowRate(double fractionofAutosizedDesignCoolingSupplyAirFlowRate);
  void resetFractionofAutosizedDesignCoolingSupplyAirFlowRate();

  boost::optional<double> designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation() const;
  bool setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation(double designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation);
  void resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation();

  std::string supplyAirFlowRateMethodDuringHeatingOperation() const;
  bool setSupplyAirFlowRateMethodDuringHeatingOperation(const std::string& supplyAirFlowRateMethodDuringHeatingOperation);
  void resetSupplyAirFlowRateMethodDuringHeatingOperation();

  boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;
  bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;
  bool setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation);
  void resetSupplyAirFlowRateDuringHeatingOperation();
  void autosizeSupplyAirFlowRateDuringHeatingOperation();

  boost::optional<double> supplyAirFlowRatePerFloorAreaduringHeatingOperation() const;
  bool setSupplyAirFlowRatePerFloorAreaduringHeatingOperation(double supplyAirFlowRatePerFloorAreaduringHeatingOperation);
  void resetSupplyAirFlowRatePerFloorAreaduringHeatingOperation();

  boost::optional<double> fractionofAutosizedDesignHeatingSupplyAirFlowRate() const;
  bool setFractionofAutosizedDesignHeatingSupplyAirFlowRate(double fractionofAutosizedDesignHeatingSupplyAirFlowRate);
  void resetFractionofAutosizedDesignHeatingSupplyAirFlowRate();

  boost::optional<double> designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation() const;
  bool setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation(double designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation);
  void resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation();

  std::string supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired() const;
  bool setSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired(const std::string& noCoolHeatMethod);
  void resetSupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired();

  boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisRequired() const;
  bool isSupplyAirFlowRateWhenNoCoolingorHeatingisRequiredAutosized() const;
  bool setSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(double supplyAirFlowRateWhenNoCoolingorHeatingisRequired);
  void resetSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();
  void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();

  boost::optional<double> supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired() const;
  bool setSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired(double supplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired);
  void resetSupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired();

  boost::optional<double> fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() const;
  bool setFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
    double fractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired);
  void resetFractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();

  boost::optional<double> fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired() const;
  bool setFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired(
    double fractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired);
  void resetFractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired();

  boost::optional<double> designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired() const;
  bool setDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired(
    double designSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired);
  void resetDesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired();

  boost::optional<double> designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired() const;
  bool setDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired(
    double designSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired);
  void resetDesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired();

  bool noLoadSupplyAirFlowRateControlSetToLowSpeed() const;
  bool setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed);

  boost::optional<double> maximumSupplyAirTemperature() const;
  bool isMaximumSupplyAirTemperatureDefaulted() const;
  bool isMaximumSupplyAirTemperatureAutosized() const;
  bool setMaximumSupplyAirTemperature(double maximumSupplyAirTemperature);
  void resetMaximumSupplyAirTemperature();
  void autosizeMaximumSupplyAirTemperature();

  double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const;
  bool isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const;
  bool setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
  void resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();

  double ancilliaryOnCycleElectricPower() const;
  bool isAncilliaryOnCycleElectricPowerDefaulted() const;
  bool setAncilliaryOnCycleElectricPower(double ancilliaryOnCycleElectricPower);
  void resetAncilliaryOnCycleElectricPower();

  double ancilliaryOffCycleElectricPower() const;
  bool isAncilliaryOffCycleElectricPowerDefaulted() const;
  bool setAncilliaryOffCycleElectricPower(double ancilliaryOffCycleElectricPower);
  void resetAncilliaryOffCycleElectricPower();

  std::vector<std::string> controlTypeValues() const;
  std::vector<std::string> dehumidificationControlTypeValues() const;
  std::vector<std::string> fanPlacementValues() const;
  std::vector<std::string> latentLoadControlValues() const;
  std::vector<std::string> supplyAirFlowRateMethodDuringCoolingOperationValues() const;
  std::vector<std::string> supplyAirFlowRateMethodDuringHeatingOperationValues() const;
  std::vector<std::string> supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequiredValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
