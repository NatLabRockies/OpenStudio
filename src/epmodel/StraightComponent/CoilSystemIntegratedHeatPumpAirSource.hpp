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

  /** \brief Represents a air-source integrated heat-pump coil system.
   *
   * \par EnergyPlus object
   * \epobject{group-heating-and-cooling-coils.html#ASIHPIO,CoilSystem:IntegratedHeatPump:AirSource}.
   *
   * \par Important behavior
   * Referenced child coils and the supported contained air path are stored through the EnergyPlus object-list fields.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::CoilSystemIntegratedHeatPumpAirSource</code>.
   * Not yet available: broader containing-component, clone/remove, and higher-level air-node convenience methods.
   *
   * \par Known limitations
   * Use the supported compound-parent workflows for loop placement.
   */
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
