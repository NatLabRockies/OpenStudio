/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTLOOP_HPP
#define EPMODEL_PLANTLOOP_HPP

#include "EPModelAPI.hpp"
#include "Loop/Loop.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class Model;
  class Mixer;
  class ModelObject;
  class Node;
  class SizingPlant;
  class AvailabilityManager;
  class Splitter;

  namespace detail {
    class PlantLoop_Impl;
  }

  class EPMODEL_API PlantLoop : public Loop
  {
   public:
    explicit PlantLoop(const Model& model);

    virtual ~PlantLoop() override = default;
    PlantLoop(const PlantLoop& other) = default;
    PlantLoop(PlantLoop&& other) = default;
    PlantLoop& operator=(const PlantLoop&) = default;
    PlantLoop& operator=(PlantLoop&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. Core loop operating scalars, supply/demand topology accessors, branch add/remove APIs, setpoint-node helpers, sizing ownership, and availability-manager ownership are present, but the canonical PlantLoop surface is still incomplete.
    // - Canonical Counterpart: openstudio::model::PlantLoop.
    // - Implemented Parity: `loadDistributionScheme`, `fluidType`, glycol concentration, loop temperature/flow/volume scalars, `commonPipeSimulation`, setpoint-node helpers, sizing ownership, supply/demand node accessors, supply/demand mixers and splitters, supply/demand traversal, availability-manager ownership, and branch add/remove APIs preserve the main canonical plant-loop topology contract.
    // - Documented Delta: Plant operation-scheme and operation-schedule APIs remain deferred because epmodel `PlantLoop` wraps the EnergyPlus-backed `PlantLoop`/`PlantEquipmentOperationSchemes` storage shape rather than the canonical `OS:PlantLoop` split fields; clone/remove specializations and autosized-result helpers also remain omitted.
    // - Field/Storage Mapping: Branch-name and connector linkage remain expressed through topology APIs over EnergyPlus-backed loop structure instead of exposing new scalar string accessors for mixer/splitter branch fields.
    // - Evidence: `src/model/PlantLoop.hpp` and `src/energyplus/ForwardTranslator/ForwardTranslatePlantLoop.cpp` define the canonical public surface and direct scalar mappings that this epmodel wrapper currently preserves in part.
    // - Remaining Parity Work: Add plant operation-scheme and operation-schedule parity through the EnergyPlus-backed `PlantEquipmentOperationSchemes` owner object, then follow with clone/remove specializations and autosized-result helpers.

    std::string loadDistributionScheme() const;
    bool setLoadDistributionScheme(const std::string& scheme);

    std::string fluidType() const;
    bool setFluidType(const std::string& value);

    int glycolConcentration() const;
    bool setGlycolConcentration(int glycolConcentration);

    double maximumLoopTemperature() const;
    bool setMaximumLoopTemperature(double value);

    double minimumLoopTemperature() const;
    bool setMinimumLoopTemperature(double value);

    boost::optional<double> maximumLoopFlowRate() const;
    bool setMaximumLoopFlowRate(double value);
    bool isMaximumLoopFlowRateAutosized() const;
    void autosizeMaximumLoopFlowRate();

    boost::optional<double> minimumLoopFlowRate() const;
    bool setMinimumLoopFlowRate(double value);
    bool isMinimumLoopFlowRateAutosized() const;
    void autosizeMinimumLoopFlowRate();

    boost::optional<double> plantLoopVolume() const;
    bool setPlantLoopVolume(double value);
    bool isPlantLoopVolumeAutocalculated() const;
    void autocalculatePlantLoopVolume();

    std::string commonPipeSimulation() const;
    bool setCommonPipeSimulation(const std::string& value);
    bool isCommonPipeSimulationDefaulted() const;
    void resetCommonPipeSimulation();

    Node loopTemperatureSetpointNode();
    bool setLoopTemperatureSetpointNode(Node& node);

    Node supplyInletNode() const override;
    Node supplyOutletNode() const override;
    std::vector<Node> supplyOutletNodes() const override;

    Node demandInletNode() const override;
    std::vector<Node> demandInletNodes() const override;
    Node demandOutletNode() const override;

    Mixer supplyMixer() const;
    Splitter supplySplitter() const;
    Mixer demandMixer();
    Splitter demandSplitter();

    std::vector<ModelObject> supplyComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                              openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const override;
    std::vector<ModelObject> supplyComponents(openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const override;
    std::vector<ModelObject> demandComponents(const HVACComponent& inletComp, const HVACComponent& outletComp,
                                              openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const override;
    std::vector<ModelObject> demandComponents(openstudio::IddObjectType type = openstudio::IddObjectType::Catchall) const override;

    bool addSupplyBranchForComponent(HVACComponent hvacComponent);
    bool removeSupplyBranchWithComponent(HVACComponent hvacComponent);
    bool addDemandBranchForComponent(HVACComponent hvacComponent, bool tertiary = false);
    bool removeDemandBranchWithComponent(HVACComponent hvacComponent);
    SizingPlant sizingPlant() const;
    std::vector<AvailabilityManager> availabilityManagers() const;
    bool addAvailabilityManager(const AvailabilityManager& availabilityManager);
    bool addAvailabilityManager(const AvailabilityManager& availabilityManager, unsigned priority);
    bool setAvailabilityManagers(const std::vector<AvailabilityManager>& availabilityManagers);
    void resetAvailabilityManagers();
    bool removeAvailabilityManager(const AvailabilityManager& availabilityManager);
    bool removeAvailabilityManager(unsigned priority);
    bool setAvailabilityManagerPriority(const AvailabilityManager& availabilityManager, unsigned priority);
    unsigned availabilityManagerPriority(const AvailabilityManager& availabilityManager) const;

   protected:
    using ImplType = detail::PlantLoop_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit PlantLoop(std::shared_ptr<detail::PlantLoop_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
