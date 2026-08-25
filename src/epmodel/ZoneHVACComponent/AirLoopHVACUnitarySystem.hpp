/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACUNITARYSYSTEM_HPP
#define EPMODEL_AIRLOOPHVACUNITARYSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class HVACComponent;
  class Node;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class AirLoopHVACUnitarySystem_Impl;
  }

/** \brief A unitary heating and cooling system used as zone equipment or on an air loop.
 *
 * \par EnergyPlus object
 * \epobject{group-unitary-equipment.html#airloophvacunitarysystem,AirLoopHVAC:UnitarySystem}
 *
 * \par Important behavior
 * Its fan and coil children share a parent-owned serial air path when moved between zone equipment and an air loop. EPModel adds fanOutletNode(), coolingCoilOutletNode(), and heatingCoilOutletNode().
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::AirLoopHVACUnitarySystem</code>.
 * EPModel adds explicit fan and coil outlet node accessors and additional
 * supply-air method setters. Model additionally provides design-specification,
 * outdoor-temperature-sensor, and autosized supply-flow helpers.
 *
 * \par Known limitations
 * Broader node-level conveniences, SQL-backed autosized values, and validation for every child family are not yet exposed.
 */
  class EPMODEL_API AirLoopHVACUnitarySystem : public ZoneHVACComponent
  {
   public:
    explicit AirLoopHVACUnitarySystem(const Model& model);

    virtual ~AirLoopHVACUnitarySystem() override = default;
    AirLoopHVACUnitarySystem(const AirLoopHVACUnitarySystem& other) = default;
    AirLoopHVACUnitarySystem(AirLoopHVACUnitarySystem&& other) = default;
    AirLoopHVACUnitarySystem& operator=(const AirLoopHVACUnitarySystem&) = default;
    AirLoopHVACUnitarySystem& operator=(AirLoopHVACUnitarySystem&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlTypeValues();
    static std::vector<std::string> dehumidificationControlTypeValues();
    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> latentLoadControlValues();
    static std::vector<std::string> supplyAirFlowRateMethodDuringCoolingOperationValues();
    static std::vector<std::string> supplyAirFlowRateMethodDuringHeatingOperationValues();
    static std::vector<std::string> supplyAirFlowRateMethodWhenNoCoolingorHeatingisRequiredValues();

    std::string controlType() const;
    bool isControlTypeDefaulted() const;
    bool setControlType(const std::string& controlType);
    void resetControlType();

    boost::optional<ThermalZone> controllingZoneorThermostatLocation() const;
    bool setControllingZoneorThermostatLocation(const ThermalZone& thermalZone);
    void resetControllingZoneorThermostatLocation();

    std::string dehumidificationControlType() const;
    bool isDehumidificationControlTypeDefaulted() const;
    bool setDehumidificationControlType(const std::string& dehumidificationControlType);
    void resetDehumidificationControlType();

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    boost::optional<HVACComponent> supplyFan() const;
    bool setSupplyFan(const HVACComponent& supplyFan);
    void resetSupplyFan();

    boost::optional<std::string> fanPlacement() const;
    bool setFanPlacement(const std::string& fanPlacement);
    void resetFanPlacement();

    boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;
    bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);
    void resetSupplyAirFanOperatingModeSchedule();

    bool hasHeatingCoil() const;
    boost::optional<HVACComponent> heatingCoil() const;
    bool setHeatingCoil(const HVACComponent& heatingCoil);
    void resetHeatingCoil();

    double dXHeatingCoilSizingRatio() const;
    bool isDXHeatingCoilSizingRatioDefaulted() const;
    bool setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio);
    void resetDXHeatingCoilSizingRatio();

    bool hasCoolingCoil() const;
    boost::optional<HVACComponent> coolingCoil() const;
    bool setCoolingCoil(const HVACComponent& coolingCoil);
    void resetCoolingCoil();

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

    boost::optional<HVACComponent> supplementalHeatingCoil() const;
    bool setSupplementalHeatingCoil(const HVACComponent& supplementalHeatingCoil);
    void resetSupplementalHeatingCoil();

    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> coolingCoilOutletNode() const;
    boost::optional<Node> heatingCoilOutletNode() const;

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

   protected:
    using ImplType = detail::AirLoopHVACUnitarySystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirLoopHVACUnitarySystem(std::shared_ptr<detail::AirLoopHVACUnitarySystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
