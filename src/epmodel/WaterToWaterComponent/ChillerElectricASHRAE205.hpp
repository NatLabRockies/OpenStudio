/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERELECTRICASHRAE205_HPP
#define EPMODEL_CHILLERELECTRICASHRAE205_HPP

#include "EPModelAPI.hpp"
#include "WaterToWaterComponent/WaterToWaterComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class PlantLoop;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class ChillerElectricASHRAE205_Impl;
  }

  class EPMODEL_API ChillerElectricASHRAE205 : public WaterToWaterComponent
  {
   public:
    explicit ChillerElectricASHRAE205(const Model& model);

    virtual ~ChillerElectricASHRAE205() override = default;
    ChillerElectricASHRAE205(const ChillerElectricASHRAE205& other) = default;
    ChillerElectricASHRAE205(ChillerElectricASHRAE205&& other) = default;
    ChillerElectricASHRAE205& operator=(const ChillerElectricASHRAE205&) = default;
    ChillerElectricASHRAE205& operator=(ChillerElectricASHRAE205&&) = default;

    static constexpr bool isHeatRecoverySupportedByEnergyplus = false;

    static IddObjectType iddObjectType();

    static std::vector<std::string> performanceInterpolationMethodValues();
    static std::vector<std::string> ambientTemperatureIndicatorValues();
    static std::vector<std::string> chillerFlowModeValues();

    // Schema Alignment Notes:
    // - Status: Parity with documented deltas. Canonical scalar, ambient, autosized-helper, HVAC-classification, and loop convenience behavior is aligned
    //   inside epmodel's supported wrapper surface.
    // - Canonical Counterpart: openstudio::model::ChillerElectricASHRAE205.
    // - Implemented Parity: Scalar accessors, ambient schedule/zone relationships, SQL-backed autosized helpers, HVAC classification and fuel reporting,
    //   and chilled/condenser/oil-cooler/auxiliary loop conveniences preserve the canonical model API shape wherever epmodel has the necessary wrapper types;
    //   heat-recovery attachment remains disabled in line with current unsupported EnergyPlus behavior.
    // - Documented Delta: Representation-file linkage still remains excluded because epmodel does not yet wrap `ExternalFile`.
    // - Field/Storage Mapping: Public behavior targets EnergyPlus `Chiller:Electric:ASHRAE205` fields and plant topology; external-file linkage remains blocked
    //   on missing epmodel storage wrappers, while autosized helper queries resolve against the shared epmodel SQL-backed component-sizing lookup.
    // - Evidence: `src/model/ChillerElectricASHRAE205.hpp`, `src/model/ChillerElectricASHRAE205.cpp`, and
    //   `src/energyplus/ForwardTranslator/ForwardTranslateChillerElectricASHRAE205.cpp`.
    // - Remaining Parity Work: Add canonical representation-file support once epmodel gains an `ExternalFile` wrapper.
    std::string performanceInterpolationMethod() const;
    bool setPerformanceInterpolationMethod(const std::string& performanceInterpolationMethod);

    boost::optional<double> ratedCapacity() const;
    bool isRatedCapacityAutosized() const;
    bool setRatedCapacity(double ratedCapacity);
    void autosizeRatedCapacity();

    double sizingFactor() const;
    bool setSizingFactor(double sizingFactor);

    std::string ambientTemperatureIndicator() const;
    boost::optional<Schedule> ambientTemperatureSchedule() const;
    bool setAmbientTemperatureSchedule(Schedule& schedule);
    void resetAmbientTemperatureSchedule();
    boost::optional<ThermalZone> ambientTemperatureZone() const;
    bool setAmbientTemperatureZone(const ThermalZone& thermalZone);
    void resetAmbientTemperatureZone();

    boost::optional<std::string> ambientTemperatureOutdoorAirNodeName() const;
    bool setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName);
    void resetAmbientTemperatureOutdoorAirNodeName();

    boost::optional<double> chilledWaterMaximumRequestedFlowRate() const;
    bool isChilledWaterMaximumRequestedFlowRateAutosized() const;
    bool setChilledWaterMaximumRequestedFlowRate(double chilledWaterMaximumRequestedFlowRate);
    void autosizeChilledWaterMaximumRequestedFlowRate();

    boost::optional<double> condenserMaximumRequestedFlowRate() const;
    bool isCondenserMaximumRequestedFlowRateAutosized() const;
    bool setCondenserMaximumRequestedFlowRate(double condenserMaximumRequestedFlowRate);
    void autosizeCondenserMaximumRequestedFlowRate();

    std::string chillerFlowMode() const;
    bool setChillerFlowMode(const std::string& chillerFlowMode);

    boost::optional<double> oilCoolerDesignFlowRate() const;
    bool setOilCoolerDesignFlowRate(double oilCoolerDesignFlowRate);
    void resetOilCoolerDesignFlowRate();

    boost::optional<double> auxiliaryCoolingDesignFlowRate() const;
    bool setAuxiliaryCoolingDesignFlowRate(double auxiliaryCoolingDesignFlowRate);
    void resetAuxiliaryCoolingDesignFlowRate();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    boost::optional<double> autosizedRatedCapacity() const;
    boost::optional<double> autosizedChilledWaterMaximumRequestedFlowRate() const;
    boost::optional<double> autosizedCondenserMaximumRequestedFlowRate() const;

    boost::optional<PlantLoop> chilledWaterLoop() const;
    boost::optional<Node> chilledWaterInletNode() const;
    boost::optional<Node> chilledWaterOutletNode() const;

    boost::optional<PlantLoop> condenserWaterLoop() const;
    boost::optional<Node> condenserInletNode() const;
    boost::optional<Node> condenserOutletNode() const;

    boost::optional<PlantLoop> heatRecoveryLoop() const;
    boost::optional<Node> heatRecoveryInletNode() const;
    boost::optional<Node> heatRecoveryOutletNode() const;

    unsigned oilCoolerInletPort() const;
    boost::optional<ModelObject> oilCoolerInletModelObject() const;
    boost::optional<Node> oilCoolerInletNode() const;
    unsigned oilCoolerOutletPort() const;
    boost::optional<ModelObject> oilCoolerOutletModelObject() const;
    boost::optional<Node> oilCoolerOutletNode() const;
    boost::optional<PlantLoop> oilCoolerLoop() const;
    bool addDemandBranchOnOilCoolerLoop(PlantLoop& plantLoop);
    bool addToOilCoolerLoopNode(Node& node);
    bool removeFromOilCoolerLoop();

    unsigned auxiliaryInletPort() const;
    boost::optional<ModelObject> auxiliaryInletModelObject() const;
    boost::optional<Node> auxiliaryInletNode() const;
    unsigned auxiliaryOutletPort() const;
    boost::optional<ModelObject> auxiliaryOutletModelObject() const;
    boost::optional<Node> auxiliaryOutletNode() const;
    boost::optional<PlantLoop> auxiliaryLoop() const;
    bool addDemandBranchOnAuxiliaryLoop(PlantLoop& plantLoop);
    bool addToAuxiliaryLoopNode(Node& node);
    bool removeFromAuxiliaryLoop();

   protected:
    using ImplType = detail::ChillerElectricASHRAE205_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ChillerElectricASHRAE205(std::shared_ptr<detail::ChillerElectricASHRAE205_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
