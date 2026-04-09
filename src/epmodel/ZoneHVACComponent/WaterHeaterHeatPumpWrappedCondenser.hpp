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
  class HVACComponent;
  class ModelObject;
  class Node;
  class Schedule;

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
    // - Status: Partial Parity. The attached tank, DX coil, fan, schedules, and owned internal topology are now surfaced directly on the
    //   parent, but a few higher-level canonical conveniences remain outside the EnergyPlus-backed epmodel surface.
    // - Canonical Counterpart: openstudio::model::WaterHeaterHeatPumpWrappedCondenser.
    // - Implemented Parity: Dead-band, condenser location, evaporator-air flow, inlet-air configuration, compressor/fan placement, parasitic
    //   load, and tank-control scalars map directly to the EnergyPlus object. The attached tank, wrapped DX coil, fan, schedules, and
    //   meaningful internal node roles are now exposed through ordinary parent methods instead of raw relationship state.
    // - Documented Delta: epmodel still follows the EnergyPlus-backed wrapped-condenser object closely, so any canonical convenience that
    //   only exists as an OpenStudio-side abstraction remains documented instead of being recreated implicitly. Epmodel also adds
    //   parent-level internal node helpers such as `fanOutletNode()`, `mixedAirNode()`, `outdoorAirNode()`, and `reliefAirNode()` so the
    //   owned compound topology is inspectable from the parent.
    // - Field/Storage Mapping: Scalar values live directly on the EnergyPlus object while child equipment and the owned air topology are
    //   maintained through explicit attachment state and parent-owned node fields.
    // - Evidence: `src/model/WaterHeaterHeatPumpWrappedCondenser.hpp`, `src/model/WaterHeaterHeatPumpWrappedCondenser.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateWaterHeaterHeatPumpWrappedCondenser.cpp`, and `src/epmodel/test/WaterHeaterHeatPumpWrappedCondenser_GTest.cpp`.
    // - Remaining Parity Work: Resolve the `Tank Element Control Logic` default mismatch only if the canonical model continues to diverge from the EnergyPlus default.
    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    Schedule compressorSetpointTemperatureSchedule() const;
    bool setCompressorSetpointTemperatureSchedule(Schedule& schedule);

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

    boost::optional<Schedule> inletAirTemperatureSchedule() const;
    bool setInletAirTemperatureSchedule(Schedule& schedule);
    void resetInletAirTemperatureSchedule();

    boost::optional<Schedule> inletAirHumiditySchedule() const;
    bool setInletAirHumiditySchedule(Schedule& schedule);
    void resetInletAirHumiditySchedule();

    HVACComponent tank() const;
    bool setTank(const HVACComponent& waterHeaterStratified);

    ModelObject dXCoil() const;
    bool setDXCoil(const ModelObject& heatPumpWaterHeaterDXCoilWrapped);

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

    boost::optional<Schedule> compressorAmbientTemperatureSchedule() const;
    bool setCompressorAmbientTemperatureSchedule(Schedule& schedule);
    void resetCompressorAmbientTemperatureSchedule();

    HVACComponent fan() const;
    bool setFan(const HVACComponent& fan);

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

    boost::optional<Schedule> inletAirMixerSchedule() const;
    bool setInletAirMixerSchedule(Schedule& schedule);
    void resetInletAirMixerSchedule();

    std::string tankElementControlLogic() const;
    bool isTankElementControlLogicDefaulted() const;
    bool setTankElementControlLogic(const std::string& tankElementControlLogic);
    void resetTankElementControlLogic();

    std::string airInletNodeName() const;
    std::string airOutletNodeName() const;
    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> mixedAirNode() const;
    boost::optional<Node> outdoorAirNode() const;
    boost::optional<Node> reliefAirNode() const;

    std::vector<ModelObject> children() const;

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
