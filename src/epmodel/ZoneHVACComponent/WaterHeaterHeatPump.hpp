/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERHEATERHEATPUMP_HPP
#define EPMODEL_WATERHEATERHEATPUMP_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class WaterHeaterHeatPump_Impl;
  }

  class EPMODEL_API WaterHeaterHeatPump : public ZoneHVACComponent
  {
   public:
    explicit WaterHeaterHeatPump(const Model& model);

    virtual ~WaterHeaterHeatPump() override = default;
    WaterHeaterHeatPump(const WaterHeaterHeatPump& other) = default;
    WaterHeaterHeatPump(WaterHeaterHeatPump&& other) = default;
    WaterHeaterHeatPump& operator=(const WaterHeaterHeatPump&) = default;
    WaterHeaterHeatPump& operator=(WaterHeaterHeatPump&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> inletAirConfigurationValues();
    static std::vector<std::string> compressorLocationValues();
    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> parasiticHeatRejectionLocationValues();
    static std::vector<std::string> tankElementControlLogicValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The water-heater heat-pump scalar fields are aligned, but the attached tank/DX-coil/fan topology remains relationship-driven.
    // - Canonical Counterpart: openstudio::model::WaterHeaterHeatPump.
    // - Implemented Parity: Dead-band, condenser-water, evaporator-air, inlet-air configuration, compressor/fan placement, parasitic load, and tank-control scalars map directly to the EnergyPlus object.
    // - Documented Delta: The attached tank, coil, fan, and schedule/node relationships are not surfaced as scalar fields.
    // - Field/Storage Mapping: Scalar data lives directly on the EnergyPlus object while child equipment and tank topology are represented through explicit attachment state.
    // - Evidence: `src/model/WaterHeaterHeatPump.hpp`, `src/model/WaterHeaterHeatPump.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateWaterHeaterHeatPump.cpp`, and `src/epmodel/test/WaterHeaterHeatPump_GTest.cpp`.
    // - Remaining Parity Work: Add relationship helpers only if the canonical wrapper still exposes them directly.
    double deadBandTemperatureDifference() const;
    bool isDeadBandTemperatureDifferenceDefaulted() const;
    bool setDeadBandTemperatureDifference(double deadBandTemperatureDifference);
    void resetDeadBandTemperatureDifference();

    boost::optional<double> condenserWaterFlowRate() const;
    bool isCondenserWaterFlowRateAutosized() const;
    bool setCondenserWaterFlowRate(double condenserWaterFlowRate);
    void resetCondenserWaterFlowRate();
    void autosizeCondenserWaterFlowRate();

    boost::optional<double> evaporatorAirFlowRate() const;
    bool isEvaporatorAirFlowRateAutosized() const;
    bool setEvaporatorAirFlowRate(double evaporatorAirFlowRate);
    void resetEvaporatorAirFlowRate();
    void autosizeEvaporatorAirFlowRate();

    std::string inletAirConfiguration() const;
    bool setInletAirConfiguration(const std::string& inletAirConfiguration);

    double minimumInletAirTemperatureforCompressorOperation() const;
    bool isMinimumInletAirTemperatureforCompressorOperationDefaulted() const;
    bool setMinimumInletAirTemperatureforCompressorOperation(double minimumInletAirTemperatureforCompressorOperation);
    void resetMinimumInletAirTemperatureforCompressorOperation();

    double maximumInletAirTemperatureforCompressorOperation() const;
    bool isMaximumInletAirTemperatureforCompressorOperationDefaulted() const;
    bool setMaximumInletAirTemperatureforCompressorOperation(double maximumInletAirTemperatureforCompressorOperation);
    void resetMaximumInletAirTemperatureforCompressorOperation();

    std::string compressorLocation() const;
    bool setCompressorLocation(const std::string& compressorLocation);

    std::string fanPlacement() const;
    bool isFanPlacementDefaulted() const;
    bool setFanPlacement(const std::string& fanPlacement);
    void resetFanPlacement();

    double onCycleParasiticElectricLoad() const;
    bool isOnCycleParasiticElectricLoadDefaulted() const;
    bool setOnCycleParasiticElectricLoad(double onCycleParasiticElectricLoad);
    void resetOnCycleParasiticElectricLoad();

    double offCycleParasiticElectricLoad() const;
    bool isOffCycleParasiticElectricLoadDefaulted() const;
    bool setOffCycleParasiticElectricLoad(double offCycleParasiticElectricLoad);
    void resetOffCycleParasiticElectricLoad();

    std::string parasiticHeatRejectionLocation() const;
    bool isParasiticHeatRejectionLocationDefaulted() const;
    bool setParasiticHeatRejectionLocation(const std::string& parasiticHeatRejectionLocation);
    void resetParasiticHeatRejectionLocation();

    std::string tankElementControlLogic() const;
    bool isTankElementControlLogicDefaulted() const;
    bool setTankElementControlLogic(const std::string& tankElementControlLogic);
    void resetTankElementControlLogic();

    boost::optional<double> controlSensor1HeightInStratifiedTank() const;
    bool setControlSensor1HeightInStratifiedTank(double controlSensor1HeightInStratifiedTank);
    void resetControlSensor1HeightInStratifiedTank();

    double controlSensor1Weight() const;
    bool isControlSensor1WeightDefaulted() const;
    bool setControlSensor1Weight(double controlSensor1Weight);
    void resetControlSensor1Weight();

    boost::optional<double> controlSensor2HeightInStratifiedTank() const;
    bool setControlSensor2HeightInStratifiedTank(double controlSensor2HeightInStratifiedTank);
    void resetControlSensor2HeightInStratifiedTank();

   protected:
    using ImplType = detail::WaterHeaterHeatPump_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WaterHeaterHeatPump(std::shared_ptr<detail::WaterHeaterHeatPump_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
