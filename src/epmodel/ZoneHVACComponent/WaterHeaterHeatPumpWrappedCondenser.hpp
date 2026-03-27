/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WATERHEATERHEATPUMPWRAPPEDCONDENSER_HPP
#define EPMODEL_WATERHEATERHEATPUMPWRAPPEDCONDENSER_HPP

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
    class WaterHeaterHeatPumpWrappedCondenser_Impl;
  }

  class EPMODEL_API WaterHeaterHeatPumpWrappedCondenser : public ZoneHVACComponent
  {
   public:
    explicit WaterHeaterHeatPumpWrappedCondenser(const Model& model);

    virtual ~WaterHeaterHeatPumpWrappedCondenser() override = default;
    WaterHeaterHeatPumpWrappedCondenser(const WaterHeaterHeatPumpWrappedCondenser& other) = default;
    WaterHeaterHeatPumpWrappedCondenser(WaterHeaterHeatPumpWrappedCondenser&& other) = default;
    WaterHeaterHeatPumpWrappedCondenser& operator=(const WaterHeaterHeatPumpWrappedCondenser&) = default;
    WaterHeaterHeatPumpWrappedCondenser& operator=(WaterHeaterHeatPumpWrappedCondenser&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> inletAirConfigurationValues();
    static std::vector<std::string> compressorLocationValues();
    static std::vector<std::string> fanPlacementValues();
    static std::vector<std::string> parasiticHeatRejectionLocationValues();
    static std::vector<std::string> tankElementControlLogicValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The wrapped-condenser scalar fields are aligned, but the tank/coil/fan/schedule topology remains relationship-driven.
    // - Canonical Counterpart: openstudio::model::WaterHeaterHeatPumpWrappedCondenser.
    // - Implemented Parity: Dead-band, condenser location, evaporator-air flow, inlet-air configuration, compressor/fan placement, parasitic load, and tank-control scalars map directly to the EnergyPlus object.
    // - Documented Delta: Relationship-like fields for schedules, nodes, and tank/coil/fan references stay outside the scalar surface.
    // - Field/Storage Mapping: Scalar values live directly on the EnergyPlus object while the omitted links are represented through explicit attachment and topology state.
    // - Evidence: `src/model/WaterHeaterHeatPumpWrappedCondenser.hpp`, `src/model/WaterHeaterHeatPumpWrappedCondenser.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateWaterHeaterHeatPumpWrappedCondenser.cpp`, and `src/epmodel/test/WaterHeaterHeatPumpWrappedCondenser_GTest.cpp`.
    // - Remaining Parity Work: Resolve the `Tank Element Control Logic` default mismatch only if the canonical model continues to diverge from the EnergyPlus default.
    double deadBandTemperatureDifference() const;
    bool isDeadBandTemperatureDifferenceDefaulted() const;
    bool setDeadBandTemperatureDifference(double deadBandTemperatureDifference);
    void resetDeadBandTemperatureDifference();

    double condenserBottomLocation() const;
    bool isCondenserBottomLocationDefaulted() const;
    bool setCondenserBottomLocation(double condenserBottomLocation);
    void resetCondenserBottomLocation();

    double condenserTopLocation() const;
    bool setCondenserTopLocation(double condenserTopLocation);

    boost::optional<double> evaporatorAirFlowRate() const;
    bool isEvaporatorAirFlowRateAutocalculated() const;
    bool setEvaporatorAirFlowRate(double evaporatorAirFlowRate);
    void resetEvaporatorAirFlowRate();
    void autocalculateEvaporatorAirFlowRate();

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
    using ImplType = detail::WaterHeaterHeatPumpWrappedCondenser_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WaterHeaterHeatPumpWrappedCondenser(std::shared_ptr<detail::WaterHeaterHeatPumpWrappedCondenser_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
