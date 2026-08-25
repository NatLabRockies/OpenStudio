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
  class PlantEquipmentOperationCoolingLoad;
  class PlantEquipmentOperationHeatingLoad;
  class PlantEquipmentOperationScheme;
  class SizingPlant;
  class AvailabilityManager;
  class Schedule;
  class Splitter;

  namespace detail {
    class PlantLoop_Impl;
  }

  /** \brief Represents a plant-side HVAC loop and its equipment branches.
   *
   * \par EnergyPlus object
   * \epobject{group-plant-condenser-loops.html#plantloop,PlantLoop}.
   *
   * \par Important behavior
   * Relationships are projected from EnergyPlus branch and node topology and mutators maintain that topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::PlantLoop</code>.
   * <b>Not yet available: <code>clone()</code>, SQL autosized-result helpers, and Model value-list methods such as <code>validFluidTypeValues()</code>, <code>validLoadDistributionSchemeValues()</code>, and <code>validCommonPipeSimulationValues()</code>.</b>
   *
   * \par Known limitations
   * Plant operation-scheme ownership is represented by the loop's operation-scheme lists; individual scheme wrappers do not provide a loop back-link.
   */
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

    boost::optional<PlantEquipmentOperationHeatingLoad> plantEquipmentOperationHeatingLoad() const;
    bool setPlantEquipmentOperationHeatingLoad(const PlantEquipmentOperationHeatingLoad& plantOperation);
    void resetPlantEquipmentOperationHeatingLoad();

    bool setPlantEquipmentOperationHeatingLoadSchedule(Schedule& schedule);
    void resetPlantEquipmentOperationHeatingLoadSchedule();
    boost::optional<Schedule> plantEquipmentOperationHeatingLoadSchedule() const;

    boost::optional<PlantEquipmentOperationCoolingLoad> plantEquipmentOperationCoolingLoad() const;
    bool setPlantEquipmentOperationCoolingLoad(const PlantEquipmentOperationCoolingLoad& plantOperation);
    void resetPlantEquipmentOperationCoolingLoad();

    bool setPlantEquipmentOperationCoolingLoadSchedule(Schedule& schedule);
    boost::optional<Schedule> plantEquipmentOperationCoolingLoadSchedule() const;
    void resetPlantEquipmentOperationCoolingLoadSchedule();

    boost::optional<PlantEquipmentOperationScheme> primaryPlantEquipmentOperationScheme() const;
    bool setPrimaryPlantEquipmentOperationScheme(const PlantEquipmentOperationScheme& plantOperation);
    void resetPrimaryPlantEquipmentOperationScheme();

    bool setPrimaryPlantEquipmentOperationSchemeSchedule(Schedule& schedule);
    void resetPrimaryPlantEquipmentOperationSchemeSchedule();
    boost::optional<Schedule> primaryPlantEquipmentOperationSchemeSchedule() const;

    bool setComponentSetpointOperationSchemeSchedule(Schedule& schedule);
    void resetComponentSetpointOperationSchemeSchedule();
    boost::optional<Schedule> componentSetpointOperationSchemeSchedule() const;

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
