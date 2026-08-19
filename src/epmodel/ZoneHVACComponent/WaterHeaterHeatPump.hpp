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
  class HVACComponent;
  class ModelObject;
  class Node;
  class Schedule;

  namespace detail {
    class WaterHeaterHeatPump_Impl;
  }

/** \brief A pumped-condenser heat-pump water heater used as zone equipment.
 *
 * \par EnergyPlus object
 * \epobject{group-water-heaters.html#waterheaterheatpumppumpedcondenser,WaterHeater:HeatPump:PumpedCondenser}
 *
 * \par Important behavior
 * The tank (WaterHeater:Mixed or WaterHeater:Stratified), water-heating coil, and fan are typed children connected to parent-owned air and condenser-water paths. EPModel adds fanOutletNode(), mixedAirNode(), outdoorAirNode(), reliefAirNode(), condenserWaterInletNode(), and condenserWaterOutletNode().
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::WaterHeaterHeatPump</code>.
 * EPModel exposes raw control-sensor height/weight fields and additional node
 * roles; Model instead exposes <code>controlSensorLocationInStratifiedTank()</code>
 * and autosized flow-result queries.
 *
 * \par Known limitations
 * <code>controlSensorLocationInStratifiedTank()</code> is not available because
 * EnergyPlus stores the resulting control-sensor heights; autosized flow-result
 * queries and other higher-level tank conveniences remain limited.
 */
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

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    Schedule compressorSetpointTemperatureSchedule() const;
    bool setCompressorSetpointTemperatureSchedule(Schedule& schedule);

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

    boost::optional<Schedule> inletAirTemperatureSchedule() const;
    bool setInletAirTemperatureSchedule(Schedule& schedule);
    void resetInletAirTemperatureSchedule();

    boost::optional<Schedule> inletAirHumiditySchedule() const;
    bool setInletAirHumiditySchedule(Schedule& schedule);
    void resetInletAirHumiditySchedule();

    HVACComponent tank() const;
    bool setTank(const HVACComponent& waterHeater);

    ModelObject dXCoil() const;
    bool setDXCoil(const ModelObject& heatPumpWaterHeaterDXCoil);

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

    Schedule inletAirMixerSchedule() const;
    bool setInletAirMixerSchedule(Schedule& schedule);

    std::string tankElementControlLogic() const;
    bool isTankElementControlLogicDefaulted() const;
    bool setTankElementControlLogic(const std::string& tankElementControlLogic);
    void resetTankElementControlLogic();

    boost::optional<Node> fanOutletNode() const;
    boost::optional<Node> mixedAirNode() const;
    boost::optional<Node> outdoorAirNode() const;
    boost::optional<Node> reliefAirNode() const;
    boost::optional<Node> condenserWaterInletNode() const;
    boost::optional<Node> condenserWaterOutletNode() const;

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
    using ImplType = detail::WaterHeaterHeatPump_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit WaterHeaterHeatPump(std::shared_ptr<detail::WaterHeaterHeatPump_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
