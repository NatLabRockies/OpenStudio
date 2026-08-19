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

/** \brief A wrapped-condenser heat-pump water heater used as zone equipment.
 *
 * \par EnergyPlus object
 * \epobject{group-water-heaters.html#waterheaterheatpumpwrappedcondenser,WaterHeater:HeatPump:WrappedCondenser}
 *
 * \par Important behavior
 * The WaterHeater:Stratified tank, wrapped water-heating coil, and fan are typed children connected to the parent-owned air path; EPModel adds fanOutletNode(), mixedAirNode(), outdoorAirNode(), and reliefAirNode().
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::WaterHeaterHeatPumpWrappedCondenser</code>.
 *
 * \par Known limitations
 * Higher-level OpenStudio conveniences are not recreated where the EnergyPlus object stores only resulting wrapped-condenser fields.
 */
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
