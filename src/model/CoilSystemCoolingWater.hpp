/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef MODEL_COILSYSTEMCOOLINGWATER_HPP
#define MODEL_COILSYSTEMCOOLINGWATER_HPP

#include <model/ModelAPI.hpp>
#include "StraightComponent.hpp"

namespace openstudio {

namespace model {

  class Schedule;
  class HVACComponent;

  namespace detail {

    class CoilSystemCoolingWater_Impl;

  }  // namespace detail

  /** CoilSystemCoolingWater is a StraightComponent that wraps the OpenStudio IDD object 'OS:CoilSystem:Cooling:Water'. */
  class MODEL_API CoilSystemCoolingWater : public StraightComponent
  {
   public:
    /** @name Constructors and Destructors */
    //@{

    explicit CoilSystemCoolingWater(const Model& model);

    explicit CoilSystemCoolingWater(const Model& model, const HVACComponent& coolingCoil);

    virtual ~CoilSystemCoolingWater() = default;
    // Default the copy and move operators because the virtual dtor is explicit
    CoilSystemCoolingWater(const CoilSystemCoolingWater& other) = default;
    CoilSystemCoolingWater(CoilSystemCoolingWater&& other) = default;
    CoilSystemCoolingWater& operator=(const CoilSystemCoolingWater&) = default;
    CoilSystemCoolingWater& operator=(CoilSystemCoolingWater&&) = default;

    //@}

    static IddObjectType iddObjectType();

    static std::vector<std::string> dehumidificationControlTypeValues();

    /** @name Getters */
    //@{

    Schedule availabilitySchedule() const;

    HVACComponent coolingCoil() const;

    std::string dehumidificationControlType() const;

    bool runonSensibleLoad() const;

    bool runonLatentLoad() const;

    double minimumAirToWaterTemperatureOffset() const;

    bool economizerLockout() const;

    double minimumWaterLoopTemperatureForHeatRecovery() const;

    boost::optional<HVACComponent> companionCoilUsedForHeatRecovery() const;

    //@}
    /** @name Setters */
    //@{

    bool setAvailabilitySchedule(Schedule& schedule);

    // CoilCoolingWater or CoilSystemCoolingWaterHeatExchangerAssisted
    bool setCoolingCoil(const HVACComponent& coolingCoil);

    bool setDehumidificationControlType(const std::string& dehumidificationControlType);

    bool setRunonSensibleLoad(bool runonSensibleLoad);

    bool setRunonLatentLoad(bool runonLatentLoad);

    bool setMinimumAirToWaterTemperatureOffset(double minimumAirToWaterTemperatureOffset);

    bool setEconomizerLockout(bool economizerLockout);

    bool setMinimumWaterLoopTemperatureForHeatRecovery(double minimumWaterLoopTemperatureForHeatRecovery);

    // Only CoilCoolingWater is supported by E+ as a companion coil right now
    bool setCompanionCoilUsedForHeatRecovery(const HVACComponent& companionCoilUsedForHeatRecovery);

    void resetCompanionCoilUsedForHeatRecovery();

    //@}
    /** @name Other */
    //@{

    //@}
   protected:
    /// @cond
    using ImplType = detail::CoilSystemCoolingWater_Impl;

    explicit CoilSystemCoolingWater(std::shared_ptr<detail::CoilSystemCoolingWater_Impl> impl);

    friend class detail::CoilSystemCoolingWater_Impl;
    friend class Model;
    friend class IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    /// @endcond
   private:
    REGISTER_LOGGER("openstudio.model.CoilSystemCoolingWater");

    void assignEnergyPlusIDDDefaults();
  };

  /** \relates CoilSystemCoolingWater*/
  using OptionalCoilSystemCoolingWater = boost::optional<CoilSystemCoolingWater>;

  /** \relates CoilSystemCoolingWater*/
  using CoilSystemCoolingWaterVector = std::vector<CoilSystemCoolingWater>;

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_COILSYSTEMCOOLINGWATER_HPP
