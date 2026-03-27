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

  namespace detail {
    class HumidifierSteamGas_Impl;
  }

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

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical steam-gas humidifier scalar surface is present, while schedule, curve, node, and storage-tank helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::HumidifierSteamGas.
    // - Implemented Parity: The preserved scalar API matches the rated-capacity, gas-use, efficiency, fan-power, auxiliary-power, and inlet-water-temperature accessors with matching autosize/default behavior.
    // - Documented Delta: Availability schedule, curve, inlet/outlet node, and water-storage-tank helpers remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `Humidifier:Steam:Gas` scalar fields used by the forward translator.
    // - Evidence: `src/model/HumidifierSteamGas.hpp`, `src/model/HumidifierSteamGas.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateHumidifierSteamGas.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.

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
