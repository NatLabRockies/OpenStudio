/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMINTEGRATEDHEATPUMPAIRSOURCE_HPP
#define EPMODEL_COILSYSTEMINTEGRATEDHEATPUMPAIRSOURCE_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class StraightComponent;
  class HVACComponent;
  class CoilCoolingDXVariableSpeed;
  class CoilHeatingDXVariableSpeed;
  class CoilWaterHeatingAirToWaterHeatPumpVariableSpeed;

  namespace detail {
    class CoilSystemIntegratedHeatPumpAirSource_Impl;
  }

  class EPMODEL_API CoilSystemIntegratedHeatPumpAirSource : public StraightComponent
  {
   public:
    explicit CoilSystemIntegratedHeatPumpAirSource(const Model& model);
    explicit CoilSystemIntegratedHeatPumpAirSource(const Model& model, const StraightComponent& spaceCoolingCoil,
                                                   const StraightComponent& spaceHeatingCoil, const HVACComponent& dedicatedWaterHeatingCoil,
                                                   const HVACComponent& scwhCoil, const StraightComponent& scdwhCoolingCoil,
                                                   const HVACComponent& scdwhWaterHeatingCoil, const StraightComponent& shdwhHeatingCoil,
                                                   const HVACComponent& shdwhWaterHeatingCoil);

    virtual ~CoilSystemIntegratedHeatPumpAirSource() override = default;
    CoilSystemIntegratedHeatPumpAirSource(const CoilSystemIntegratedHeatPumpAirSource& other) = default;
    CoilSystemIntegratedHeatPumpAirSource(CoilSystemIntegratedHeatPumpAirSource&& other) = default;
    CoilSystemIntegratedHeatPumpAirSource& operator=(const CoilSystemIntegratedHeatPumpAirSource&) = default;
    CoilSystemIntegratedHeatPumpAirSource& operator=(CoilSystemIntegratedHeatPumpAirSource&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The scalar control surface and referenced-coil relationships are aligned, while standalone node-link behavior
    //   remains intentionally rejected.
    // - Canonical Counterpart: openstudio::model::CoilSystemIntegratedHeatPumpAirSource.
    // - Implemented Parity: The canonical temperature-limit, load-control, speed-level, and water-flow control scalars are preserved alongside
    //   the eight coil-reference relationships (`spaceCoolingCoil`, `spaceHeatingCoil`, `dedicatedWaterHeatingCoil`, `scwhCoil`,
    //   `scdwhCoolingCoil`, `scdwhWaterHeatingCoil`, `shdwhHeatingCoil`, and `shdwhWaterHeatingCoil`).
    // - Documented Delta: epmodel keeps this as a serial `StraightComponent` for compound ownership, but `addToNode(...)` remains rejected
    //   intentionally and no extra loop-placement surface is introduced.
    // - Field/Storage Mapping: The preserved scalars and referenced-coil relationships map directly to EnergyPlus
    //   `CoilSystem:IntegratedHeatPump:AirSource` storage.
    // - Default Seeding: The no-arg constructor seeds canonical default subcomponents using existing epmodel wrappers, along with the scalar
    //   defaults already carried by the integrated system.
    // - Evidence: `src/model/CoilSystemIntegratedHeatPumpAirSource.hpp`, `src/model/CoilSystemIntegratedHeatPumpAirSource.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemIntegratedHeatPumpAirSource.cpp`, and
    //   `src/epmodel/test/CoilSystemIntegratedHeatPumpAirSource_GTest.cpp`.
    // - Remaining Parity Work: Higher-level loop-link helpers remain outside this bounded slice.
    StraightComponent spaceCoolingCoil() const;
    StraightComponent spaceHeatingCoil() const;
    HVACComponent dedicatedWaterHeatingCoil() const;
    HVACComponent scwhCoil() const;
    StraightComponent scdwhCoolingCoil() const;
    HVACComponent scdwhWaterHeatingCoil() const;
    StraightComponent shdwhHeatingCoil() const;
    HVACComponent shdwhWaterHeatingCoil() const;

    bool setSpaceCoolingCoil(const StraightComponent& spaceCoolingCoil);
    bool setSpaceHeatingCoil(const StraightComponent& spaceHeatingCoil);
    bool setDedicatedWaterHeatingCoil(const HVACComponent& dedicatedWaterHeatingCoil);
    bool setSCWHCoil(const HVACComponent& scwhCoil);
    bool setSCDWHCoolingCoil(const StraightComponent& scdwhCoolingCoil);
    bool setSCDWHWaterHeatingCoil(const HVACComponent& scdwhWaterHeatingCoil);
    bool setSHDWHHeatingCoil(const StraightComponent& shdwhHeatingCoil);
    bool setSHDWHWaterHeatingCoil(const HVACComponent& shdwhWaterHeatingCoil);

    double indoorTemperatureLimitForSCWHMode() const;
    bool setIndoorTemperatureLimitForSCWHMode(double indoorTemperatureLimitForSCWHMode);

    double ambientTemperatureLimitForSCWHMode() const;
    bool setAmbientTemperatureLimitForSCWHMode(double ambientTemperatureLimitForSCWHMode);

    double indoorTemperatureAboveWhichWHHasHigherPriority() const;
    bool setIndoorTemperatureAboveWhichWHHasHigherPriority(double indoorTemperatureAboveWhichWHHasHigherPriority);

    double ambientTemperatureAboveWhichWHHasHigherPriority() const;
    bool setAmbientTemperatureAboveWhichWHHasHigherPriority(double ambientTemperatureAboveWhichWHHasHigherPriority);

    int flagtoIndicateLoadControlInSCWHMode() const;
    bool setFlagtoIndicateLoadControlInSCWHMode(int flagtoIndicateLoadControlInSCWHMode);

    int minimumSpeedLevelForSCWHMode() const;
    bool setMinimumSpeedLevelForSCWHMode(int minimumSpeedLevelForSCWHMode);

    double maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode() const;
    bool setMaximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode(double maximumWaterFlowVolumeBeforeSwitchingfromSCDWHtoSCWHMode);

    int minimumSpeedLevelForSCDWHMode() const;
    bool setMinimumSpeedLevelForSCDWHMode(int minimumSpeedLevelForSCDWHMode);

    double maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode() const;
    bool setMaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode(
      double maximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode);

    int minimumSpeedLevelForSHDWHMode() const;
    bool setMinimumSpeedLevelForSHDWHMode(int minimumSpeedLevelForSHDWHMode);

   protected:
    using ImplType = detail::CoilSystemIntegratedHeatPumpAirSource_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilSystemIntegratedHeatPumpAirSource(std::shared_ptr<detail::CoilSystemIntegratedHeatPumpAirSource_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
