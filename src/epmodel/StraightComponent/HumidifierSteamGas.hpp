/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HUMIDIFIERSTEAMGAS_HPP
#define EPMODEL_HUMIDIFIERSTEAMGAS_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class Curve;
  class Schedule;

  namespace detail {
    class HumidifierSteamGas_Impl;
  }

/** \brief A gas-fired steam humidifier.
 *
 * \par EnergyPlus object
 * \epobject{group-humidifiers-and-dehumidifiers.html#humidifiersteamgas,Humidifier:Steam:Gas}
 *
 * \par Important behavior
 * Availability, node, capacity, efficiency, and fuel-use fields map directly to Humidifier:Steam:Gas.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::HumidifierSteamGas</code>.
 *
 * \par Known limitations
 * No additional type-specific limitation is known beyond shared straight-component topology.
 */
  class EPMODEL_API HumidifierSteamGas : public StraightComponent
  {
   public:
    explicit HumidifierSteamGas(const Model& model);

    virtual ~HumidifierSteamGas() override = default;
    HumidifierSteamGas(const HumidifierSteamGas& other) = default;
    HumidifierSteamGas(HumidifierSteamGas&& other) = default;
    HumidifierSteamGas& operator=(const HumidifierSteamGas&) = default;
    HumidifierSteamGas& operator=(HumidifierSteamGas&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    static std::vector<std::string> inletWaterTemperatureOptionValues();


    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    // Rated Capacity
    boost::optional<double> ratedCapacity() const;
    bool isRatedCapacityAutosized() const;
    bool setRatedCapacity(double ratedCapacity);
    void autosizeRatedCapacity();
    boost::optional<double> autosizedRatedCapacity() const;

    // Rated Gas Use Rate
    boost::optional<double> ratedGasUseRate() const;
    bool isRatedGasUseRateAutosized() const;
    bool setRatedGasUseRate(double ratedGasUseRate);
    void resetRatedGasUseRate();
    void autosizeRatedGasUseRate();
    boost::optional<double> autosizedRatedGasUseRate() const;

    // Thermal Efficiency
    double thermalEfficiency() const;
    bool isThermalEfficiencyDefaulted() const;
    bool setThermalEfficiency(double thermalEfficiency);
    void resetThermalEfficiency();

    // Rated Fan Power
    boost::optional<double> ratedFanPower() const;
    bool setRatedFanPower(double ratedFanPower);
    void resetRatedFanPower();

    // Auxiliary Electric Power
    double auxiliaryElectricPower() const;
    bool isAuxiliaryElectricPowerDefaulted() const;
    bool setAuxiliaryElectricPower(double auxiliaryElectricPower);
    void resetAuxiliaryElectricPower();

    // Inlet Water Temperature Option
    std::string inletWaterTemperatureOption() const;
    bool isInletWaterTemperatureOptionDefaulted() const;
    bool setInletWaterTemperatureOption(const std::string& inletWaterTemperatureOption);
    void resetInletWaterTemperatureOption();

    // Thermal Efficiency Modifier Curve
    boost::optional<Curve> thermalEfficiencyModifierCurve() const;
    bool setThermalEfficiencyModifierCurve(const Curve& curve);
    void resetThermalEfficiencyModifierCurve();

   protected:
    using ImplType = detail::HumidifierSteamGas_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HumidifierSteamGas(std::shared_ptr<detail::HumidifierSteamGas_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
