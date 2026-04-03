/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTLOOP_IMPL_HPP
#define EPMODEL_PLANTLOOP_IMPL_HPP

#include "Loop/Loop_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  class Branch;
  class BranchList;
  class AvailabilityManager;
  class AvailabilityManagerAssignmentList;
  class ConnectorMixer;
  class ConnectorSplitter;
  class HVACComponent;
  class Mixer;
  class Node;
  class PlantEquipmentOperationCoolingLoad;
  class PlantEquipmentOperationHeatingLoad;
  class PlantEquipmentOperationScheme;
  class PlantEquipmentOperationSchemes;
  class Schedule;
  class SizingPlant;
  class Splitter;

  namespace detail {
    struct LoadContext;

    class EPMODEL_API PlantLoop_Impl : public Loop_Impl
    {
     public:
      using Loop_Impl::Loop_Impl;
      virtual ~PlantLoop_Impl() override = default;

      openstudio::epmodel::Node supplyInletNode() const override;
      openstudio::epmodel::Node supplyOutletNode() const override;
      std::vector<openstudio::epmodel::Node> supplyOutletNodes() const override;
      openstudio::epmodel::Node demandInletNode() const override;
      std::vector<openstudio::epmodel::Node> demandInletNodes() const override;
      openstudio::epmodel::Node demandOutletNode() const override;

      openstudio::epmodel::BranchList supplyBranchList() const;
      openstudio::epmodel::BranchList demandBranchList() const;
      openstudio::epmodel::Branch supplyInletBranch() const;
      openstudio::epmodel::Branch supplyOutletBranch() const;
      openstudio::epmodel::Branch demandInletBranch() const;
      openstudio::epmodel::Branch demandOutletBranch() const;
      std::vector<openstudio::epmodel::Branch> supplyEquipmentBranches() const;
      std::vector<openstudio::epmodel::Branch> demandEquipmentBranches() const;

      openstudio::epmodel::Mixer supplyMixer() const;
      openstudio::epmodel::Splitter supplySplitter() const;
      openstudio::epmodel::Mixer demandMixer() const override;
      openstudio::epmodel::Splitter demandSplitter() const override;

      std::vector<openstudio::epmodel::ModelObject> supplyComponents(const openstudio::epmodel::HVACComponent& inletComp,
                                                                     const openstudio::epmodel::HVACComponent& outletComp,
                                                                     openstudio::IddObjectType type) const override;
      std::vector<openstudio::epmodel::ModelObject> supplyComponents(openstudio::IddObjectType type) const override;
      std::vector<openstudio::epmodel::ModelObject> demandComponents(const openstudio::epmodel::HVACComponent& inletComp,
                                                                     const openstudio::epmodel::HVACComponent& outletComp,
                                                                     openstudio::IddObjectType type) const override;
      std::vector<openstudio::epmodel::ModelObject> demandComponents(openstudio::IddObjectType type) const override;

      bool addSupplyBranchForComponent(openstudio::epmodel::HVACComponent hvacComponent);
      bool removeSupplyBranchWithComponent(openstudio::epmodel::HVACComponent hvacComponent);
      bool addDemandBranchForComponent(openstudio::epmodel::HVACComponent hvacComponent, bool tertiary = false);
      bool removeDemandBranchWithComponent(openstudio::epmodel::HVACComponent hvacComponent);

      boost::optional<openstudio::epmodel::Branch> branchForNode(const openstudio::epmodel::Node& node) const;

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

      openstudio::epmodel::Node loopTemperatureSetpointNode() const;
      bool setLoopTemperatureSetpointNode(openstudio::epmodel::Node& node);
      boost::optional<openstudio::epmodel::PlantEquipmentOperationHeatingLoad> plantEquipmentOperationHeatingLoad() const;
      bool setPlantEquipmentOperationHeatingLoad(const openstudio::epmodel::PlantEquipmentOperationHeatingLoad& plantOperation);
      void resetPlantEquipmentOperationHeatingLoad();
      bool setPlantEquipmentOperationHeatingLoadSchedule(openstudio::epmodel::Schedule& schedule);
      void resetPlantEquipmentOperationHeatingLoadSchedule();
      boost::optional<openstudio::epmodel::Schedule> plantEquipmentOperationHeatingLoadSchedule() const;
      boost::optional<openstudio::epmodel::PlantEquipmentOperationCoolingLoad> plantEquipmentOperationCoolingLoad() const;
      bool setPlantEquipmentOperationCoolingLoad(const openstudio::epmodel::PlantEquipmentOperationCoolingLoad& plantOperation);
      void resetPlantEquipmentOperationCoolingLoad();
      bool setPlantEquipmentOperationCoolingLoadSchedule(openstudio::epmodel::Schedule& schedule);
      boost::optional<openstudio::epmodel::Schedule> plantEquipmentOperationCoolingLoadSchedule() const;
      void resetPlantEquipmentOperationCoolingLoadSchedule();
      boost::optional<openstudio::epmodel::PlantEquipmentOperationScheme> primaryPlantEquipmentOperationScheme() const;
      bool setPrimaryPlantEquipmentOperationScheme(const openstudio::epmodel::PlantEquipmentOperationScheme& plantOperation);
      void resetPrimaryPlantEquipmentOperationScheme();
      bool setPrimaryPlantEquipmentOperationSchemeSchedule(openstudio::epmodel::Schedule& schedule);
      void resetPrimaryPlantEquipmentOperationSchemeSchedule();
      boost::optional<openstudio::epmodel::Schedule> primaryPlantEquipmentOperationSchemeSchedule() const;
      bool setComponentSetpointOperationSchemeSchedule(openstudio::epmodel::Schedule& schedule);
      void resetComponentSetpointOperationSchemeSchedule();
      boost::optional<openstudio::epmodel::Schedule> componentSetpointOperationSchemeSchedule() const;
      openstudio::epmodel::SizingPlant sizingPlant() const;
      openstudio::epmodel::AvailabilityManagerAssignmentList availabilityManagerAssignmentList() const;
      std::vector<openstudio::epmodel::AvailabilityManager> availabilityManagers() const;
      bool addAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager);
      bool addAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager, unsigned priority);
      bool setAvailabilityManagers(const std::vector<openstudio::epmodel::AvailabilityManager>& availabilityManagers);
      void resetAvailabilityManagers();
      bool removeAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager);
      bool removeAvailabilityManager(unsigned priority);
      bool setAvailabilityManagerPriority(const openstudio::epmodel::AvailabilityManager& availabilityManager, unsigned priority);
      unsigned availabilityManagerPriority(const openstudio::epmodel::AvailabilityManager& availabilityManager) const;

      void doCanonicalize(LoadContext& context) override;

    private:
      openstudio::epmodel::PlantEquipmentOperationSchemes plantEquipmentOperationSchemes() const;
      bool syncConnectorPorts(openstudio::epmodel::ConnectorSplitter& splitter, openstudio::epmodel::ConnectorMixer& mixer,
                              const openstudio::epmodel::Branch& inletBranch, const openstudio::epmodel::Branch& outletBranch,
                              const std::vector<openstudio::epmodel::Branch>& equipmentBranches) const;

      boost::optional<openstudio::epmodel::Branch> supplyBranchForNode(const openstudio::epmodel::Node& node) const;
      boost::optional<openstudio::epmodel::Branch> demandBranchForNode(const openstudio::epmodel::Node& node) const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
