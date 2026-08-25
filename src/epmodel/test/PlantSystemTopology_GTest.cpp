/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad_Impl.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/Splitter.hpp"
#include "../StraightComponent/BoilerHotWater.hpp"
#include "../StraightComponent/BoilerHotWater_Impl.hpp"
#include "../StraightComponent/CoolingTowerSingleSpeed.hpp"
#include "../StraightComponent/CoolingTowerSingleSpeed_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/PumpVariableSpeed.hpp"
#include "../StraightComponent/PumpVariableSpeed_Impl.hpp"
#include "../StraightComponent/StraightComponent.hpp"
#include "../WaterToWaterComponent/ChillerElectricEIR.hpp"
#include "../WaterToWaterComponent/ChillerElectricEIR_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>

#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

using namespace openstudio::epmodel;

namespace {

class ScopedFileRemoval
{
 public:
  explicit ScopedFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

struct EndpointHandles
{
  openstudio::Handle inlet;
  openstudio::Handle outlet;

  bool operator==(const EndpointHandles&) const = default;
};

boost::optional<EndpointHandles> endpointHandles(const StraightComponent& component) {
  const auto inlet = component.inletModelObject();
  const auto outlet = component.outletModelObject();
  if (!inlet || !outlet) {
    return boost::none;
  }
  return EndpointHandles{inlet->handle(), outlet->handle()};
}

boost::optional<EndpointHandles> endpointHandles(const boost::optional<Node>& inlet, const boost::optional<Node>& outlet) {
  if (!inlet || !outlet) {
    return boost::none;
  }
  return EndpointHandles{inlet->handle(), outlet->handle()};
}

::testing::AssertionResult hasStraightSupplyTopology(const PlantLoop& loop, const StraightComponent& component, bool isInletBranchPump = false) {
  const auto owner = component.plantLoop();
  if (!owner || (*owner != loop)) {
    return ::testing::AssertionFailure() << component.nameString() << " does not report " << loop.nameString() << " as its plant owner";
  }

  const auto inletObject = component.inletModelObject();
  const auto outletObject = component.outletModelObject();
  if (!inletObject || !outletObject) {
    return ::testing::AssertionFailure() << component.nameString() << " is missing an inlet or outlet object";
  }
  const auto inletNode = inletObject->optionalCast<Node>();
  const auto outletNode = outletObject->optionalCast<Node>();
  if (!inletNode || !outletNode) {
    return ::testing::AssertionFailure() << component.nameString() << " does not resolve both endpoints as live Nodes";
  }
  const auto inletOwner = inletNode->plantLoop();
  const auto outletOwner = outletNode->plantLoop();
  if (!inletOwner || (*inletOwner != loop) || !outletOwner || (*outletOwner != loop)) {
    return ::testing::AssertionFailure() << component.nameString() << " endpoint Nodes do not both resolve to " << loop.nameString();
  }

  const auto supplyPath = loop.supplyComponents();
  const auto componentIt =
    std::find_if(supplyPath.begin(), supplyPath.end(), [&component](const auto& object) { return object.handle() == component.handle(); });
  if ((componentIt == supplyPath.end()) || (componentIt == supplyPath.begin()) || (std::next(componentIt) == supplyPath.end())) {
    return ::testing::AssertionFailure() << component.nameString() << " is not bracketed by endpoints in supply traversal";
  }
  if ((std::prev(componentIt)->handle() != inletNode->handle()) || (std::next(componentIt)->handle() != outletNode->handle())) {
    return ::testing::AssertionFailure() << component.nameString() << " traversal neighbors do not match its inlet and outlet Nodes";
  }

  if (isInletBranchPump) {
    if (*inletNode != loop.supplyInletNode()) {
      return ::testing::AssertionFailure() << component.nameString() << " inlet is not the loop supply inlet";
    }
    const auto splitterInlet = loop.supplySplitter().inletModelObject();
    if (!splitterInlet || (splitterInlet->handle() != outletNode->handle())) {
      return ::testing::AssertionFailure() << component.nameString() << " outlet does not continue to the supply splitter inlet";
    }
  }

  return ::testing::AssertionSuccess();
}

::testing::AssertionResult hasChilledWaterTopology(const PlantLoop& loop, const ChillerElectricEIR& chiller) {
  const auto owner = chiller.chilledWaterLoop();
  const auto inletNode = chiller.chilledWaterInletNode();
  const auto outletNode = chiller.chilledWaterOutletNode();
  if (!owner || (*owner != loop)) {
    return ::testing::AssertionFailure() << chiller.nameString() << " does not report " << loop.nameString() << " as chilled-water owner";
  }
  if (!inletNode || !outletNode) {
    return ::testing::AssertionFailure() << chiller.nameString() << " is missing a chilled-water endpoint";
  }
  const auto inletOwner = inletNode->plantLoop();
  const auto outletOwner = outletNode->plantLoop();
  if (!inletOwner || (*inletOwner != loop) || !outletOwner || (*outletOwner != loop)) {
    return ::testing::AssertionFailure() << chiller.nameString() << " chilled-water endpoints do not both resolve to " << loop.nameString();
  }

  const auto supplyPath = loop.supplyComponents();
  const auto componentIt =
    std::find_if(supplyPath.begin(), supplyPath.end(), [&chiller](const auto& object) { return object.handle() == chiller.handle(); });
  if ((componentIt == supplyPath.end()) || (componentIt == supplyPath.begin()) || (std::next(componentIt) == supplyPath.end())) {
    return ::testing::AssertionFailure() << chiller.nameString() << " is not bracketed by chilled-water endpoints in supply traversal";
  }
  if ((std::prev(componentIt)->handle() != inletNode->handle()) || (std::next(componentIt)->handle() != outletNode->handle())) {
    return ::testing::AssertionFailure() << chiller.nameString() << " chilled-water traversal neighbors do not match its endpoints";
  }
  return ::testing::AssertionSuccess();
}

::testing::AssertionResult hasCondenserWaterTopology(const PlantLoop& loop, const ChillerElectricEIR& chiller) {
  const auto owner = chiller.condenserWaterLoop();
  const auto inletNode = chiller.condenserInletNode();
  const auto outletNode = chiller.condenserOutletNode();
  if (!owner || (*owner != loop)) {
    return ::testing::AssertionFailure() << chiller.nameString() << " does not report " << loop.nameString() << " as condenser owner";
  }
  if (!inletNode || !outletNode) {
    return ::testing::AssertionFailure() << chiller.nameString() << " is missing a condenser endpoint";
  }
  const auto inletOwner = inletNode->plantLoop();
  const auto outletOwner = outletNode->plantLoop();
  if (!inletOwner || (*inletOwner != loop) || !outletOwner || (*outletOwner != loop)) {
    return ::testing::AssertionFailure() << chiller.nameString() << " condenser endpoints do not both resolve to " << loop.nameString();
  }

  const auto demandPath = loop.demandComponents();
  const auto componentIt =
    std::find_if(demandPath.begin(), demandPath.end(), [&chiller](const auto& object) { return object.handle() == chiller.handle(); });
  if ((componentIt == demandPath.end()) || (componentIt == demandPath.begin()) || (std::next(componentIt) == demandPath.end())) {
    return ::testing::AssertionFailure() << chiller.nameString() << " is not bracketed by condenser endpoints in demand traversal";
  }
  if ((std::prev(componentIt)->handle() != inletNode->handle()) || (std::next(componentIt)->handle() != outletNode->handle())) {
    return ::testing::AssertionFailure() << chiller.nameString() << " condenser traversal neighbors do not match its endpoints";
  }
  return ::testing::AssertionSuccess();
}

}  // namespace

TEST_F(EPModelFixture, PlantSystemTopology_HotWaterChilledWaterAndCondenserVerticalSlice) {
  const auto idfPath =
    openstudio::tempDir()
    / openstudio::toPath("epmodel-plant-system-topology-vertical-slice-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;

  PlantLoop hotWaterLoop(model);
  PumpVariableSpeed hotWaterPump(model);
  BoilerHotWater boiler(model);
  PlantEquipmentOperationHeatingLoad heatingOperation(model);
  ScheduleConstant heatingOperationSchedule(model);
  ASSERT_TRUE(hotWaterLoop.setName("Vertical Slice Hot Water Loop"));
  ASSERT_TRUE(hotWaterPump.setName("Vertical Slice Hot Water Pump"));
  ASSERT_TRUE(boiler.setName("Vertical Slice Boiler"));
  ASSERT_TRUE(heatingOperation.setName("Vertical Slice Heating Operation"));
  ASSERT_TRUE(heatingOperationSchedule.setName("Vertical Slice Heating Operation Schedule"));
  ASSERT_TRUE(heatingOperationSchedule.setValue(1.0));
  ASSERT_TRUE(hotWaterLoop.sizingPlant().setLoopType("Heating"));
  auto hotWaterSupplyInletNode = hotWaterLoop.supplyInletNode();
  ASSERT_TRUE(hotWaterPump.addToNode(hotWaterSupplyInletNode));
  ASSERT_TRUE(hotWaterLoop.addSupplyBranchForComponent(boiler));
  ASSERT_TRUE(heatingOperation.addEquipment(boiler));
  ASSERT_TRUE(hotWaterLoop.setPlantEquipmentOperationHeatingLoad(heatingOperation));
  ASSERT_TRUE(hotWaterLoop.setPlantEquipmentOperationHeatingLoadSchedule(heatingOperationSchedule));

  PlantLoop chilledWaterLoop(model);
  PumpVariableSpeed chilledWaterPump(model);
  ChillerElectricEIR chiller(model);
  PlantEquipmentOperationCoolingLoad chilledWaterOperation(model);
  ScheduleConstant chilledWaterOperationSchedule(model);
  ASSERT_TRUE(chilledWaterLoop.setName("Vertical Slice Chilled Water Loop"));
  ASSERT_TRUE(chilledWaterPump.setName("Vertical Slice Chilled Water Pump"));
  ASSERT_TRUE(chiller.setName("Vertical Slice Chiller"));
  ASSERT_TRUE(chilledWaterOperation.setName("Vertical Slice Chilled Water Operation"));
  ASSERT_TRUE(chilledWaterOperationSchedule.setName("Vertical Slice Chilled Water Operation Schedule"));
  ASSERT_TRUE(chilledWaterOperationSchedule.setValue(1.0));
  ASSERT_TRUE(chilledWaterLoop.sizingPlant().setLoopType("Cooling"));
  auto chilledWaterSupplyInletNode = chilledWaterLoop.supplyInletNode();
  ASSERT_TRUE(chilledWaterPump.addToNode(chilledWaterSupplyInletNode));
  ASSERT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(chilledWaterOperation.addEquipment(chiller));
  ASSERT_TRUE(chilledWaterLoop.setPlantEquipmentOperationCoolingLoad(chilledWaterOperation));
  ASSERT_TRUE(chilledWaterLoop.setPlantEquipmentOperationCoolingLoadSchedule(chilledWaterOperationSchedule));

  PlantLoop condenserLoop(model);
  PumpVariableSpeed condenserPump(model);
  CoolingTowerSingleSpeed coolingTower(model);
  PlantEquipmentOperationCoolingLoad condenserOperation(model);
  ScheduleConstant condenserOperationSchedule(model);
  ASSERT_TRUE(condenserLoop.setName("Vertical Slice Condenser Loop"));
  ASSERT_TRUE(condenserPump.setName("Vertical Slice Condenser Pump"));
  ASSERT_TRUE(coolingTower.setName("Vertical Slice Cooling Tower"));
  ASSERT_TRUE(condenserOperation.setName("Vertical Slice Condenser Operation"));
  ASSERT_TRUE(condenserOperationSchedule.setName("Vertical Slice Condenser Operation Schedule"));
  ASSERT_TRUE(condenserOperationSchedule.setValue(1.0));
  ASSERT_TRUE(condenserLoop.sizingPlant().setLoopType("Condenser"));
  auto condenserSupplyInletNode = condenserLoop.supplyInletNode();
  ASSERT_TRUE(condenserPump.addToNode(condenserSupplyInletNode));
  ASSERT_TRUE(condenserLoop.addSupplyBranchForComponent(coolingTower));
  ASSERT_TRUE(condenserLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(condenserOperation.addEquipment(coolingTower));
  ASSERT_TRUE(condenserLoop.setPlantEquipmentOperationCoolingLoad(condenserOperation));
  ASSERT_TRUE(condenserLoop.setPlantEquipmentOperationCoolingLoadSchedule(condenserOperationSchedule));

  EXPECT_EQ("Heating", hotWaterLoop.sizingPlant().loopType());
  EXPECT_EQ("Cooling", chilledWaterLoop.sizingPlant().loopType());
  EXPECT_EQ("Condenser", condenserLoop.sizingPlant().loopType());
  EXPECT_TRUE(hasStraightSupplyTopology(hotWaterLoop, hotWaterPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(hotWaterLoop, boiler));
  EXPECT_TRUE(hasStraightSupplyTopology(chilledWaterLoop, chilledWaterPump, true));
  EXPECT_TRUE(hasChilledWaterTopology(chilledWaterLoop, chiller));
  EXPECT_TRUE(hasStraightSupplyTopology(condenserLoop, condenserPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(condenserLoop, coolingTower));
  EXPECT_TRUE(hasCondenserWaterTopology(condenserLoop, chiller));
  EXPECT_EQ("WaterCooled", chiller.condenserType());

  ASSERT_TRUE(hotWaterLoop.plantEquipmentOperationHeatingLoad());
  ASSERT_TRUE(chilledWaterLoop.plantEquipmentOperationCoolingLoad());
  ASSERT_TRUE(condenserLoop.plantEquipmentOperationCoolingLoad());
  EXPECT_EQ(heatingOperation, *hotWaterLoop.plantEquipmentOperationHeatingLoad());
  EXPECT_EQ(chilledWaterOperation, *chilledWaterLoop.plantEquipmentOperationCoolingLoad());
  EXPECT_EQ(condenserOperation, *condenserLoop.plantEquipmentOperationCoolingLoad());
  ASSERT_EQ(1u, heatingOperation.equipment(heatingOperation.maximumUpperLimit()).size());
  ASSERT_EQ(1u, chilledWaterOperation.equipment(chilledWaterOperation.maximumUpperLimit()).size());
  ASSERT_EQ(1u, condenserOperation.equipment(condenserOperation.maximumUpperLimit()).size());
  EXPECT_EQ(boiler.handle(), heatingOperation.equipment(heatingOperation.maximumUpperLimit()).front().handle());
  EXPECT_EQ(chiller.handle(), chilledWaterOperation.equipment(chilledWaterOperation.maximumUpperLimit()).front().handle());
  EXPECT_EQ(coolingTower.handle(), condenserOperation.equipment(condenserOperation.maximumUpperLimit()).front().handle());

  const std::vector<boost::optional<EndpointHandles>> endpointsBeforeRejection{
    endpointHandles(hotWaterPump),
    endpointHandles(boiler),
    endpointHandles(chilledWaterPump),
    endpointHandles(chiller.chilledWaterInletNode(), chiller.chilledWaterOutletNode()),
    endpointHandles(condenserPump),
    endpointHandles(coolingTower),
    endpointHandles(chiller.condenserInletNode(), chiller.condenserOutletNode()),
  };
  ASSERT_TRUE(std::all_of(endpointsBeforeRejection.begin(), endpointsBeforeRejection.end(), [](const auto& value) { return value.has_value(); }));
  const auto hotWaterSupplyBeforeRejection = hotWaterLoop.supplyComponents();
  const auto condenserDemandBeforeRejection = condenserLoop.demandComponents();

  // A boiler is supply-only. Its rejected condenser-demand placement must preserve both existing loop graphs and every live endpoint.
  EXPECT_FALSE(condenserLoop.addDemandBranchForComponent(boiler));
  const std::vector<boost::optional<EndpointHandles>> endpointsAfterRejection{
    endpointHandles(hotWaterPump),
    endpointHandles(boiler),
    endpointHandles(chilledWaterPump),
    endpointHandles(chiller.chilledWaterInletNode(), chiller.chilledWaterOutletNode()),
    endpointHandles(condenserPump),
    endpointHandles(coolingTower),
    endpointHandles(chiller.condenserInletNode(), chiller.condenserOutletNode()),
  };
  EXPECT_TRUE(endpointsBeforeRejection == endpointsAfterRejection);
  EXPECT_TRUE(hotWaterSupplyBeforeRejection == hotWaterLoop.supplyComponents());
  EXPECT_TRUE(condenserDemandBeforeRejection == condenserLoop.demandComponents());
  EXPECT_TRUE(condenserLoop.demandComponents(BoilerHotWater::iddObjectType()).empty());
  EXPECT_TRUE(hasStraightSupplyTopology(hotWaterLoop, hotWaterPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(hotWaterLoop, boiler));
  EXPECT_TRUE(hasStraightSupplyTopology(chilledWaterLoop, chilledWaterPump, true));
  EXPECT_TRUE(hasChilledWaterTopology(chilledWaterLoop, chiller));
  EXPECT_TRUE(hasStraightSupplyTopology(condenserLoop, condenserPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(condenserLoop, coolingTower));
  EXPECT_TRUE(hasCondenserWaterTopology(condenserLoop, chiller));
  EXPECT_EQ("WaterCooled", chiller.condenserType());

  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedHotWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Vertical Slice Hot Water Loop");
  auto loadedChilledWaterLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Vertical Slice Chilled Water Loop");
  auto loadedCondenserLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Vertical Slice Condenser Loop");
  auto loadedHotWaterPump = loadedModel->getConcreteModelObjectByName<PumpVariableSpeed>("Vertical Slice Hot Water Pump");
  auto loadedBoiler = loadedModel->getConcreteModelObjectByName<BoilerHotWater>("Vertical Slice Boiler");
  auto loadedChilledWaterPump = loadedModel->getConcreteModelObjectByName<PumpVariableSpeed>("Vertical Slice Chilled Water Pump");
  auto loadedChiller = loadedModel->getConcreteModelObjectByName<ChillerElectricEIR>("Vertical Slice Chiller");
  auto loadedCondenserPump = loadedModel->getConcreteModelObjectByName<PumpVariableSpeed>("Vertical Slice Condenser Pump");
  auto loadedCoolingTower = loadedModel->getConcreteModelObjectByName<CoolingTowerSingleSpeed>("Vertical Slice Cooling Tower");
  auto loadedHeatingOperation = loadedModel->getConcreteModelObjectByName<PlantEquipmentOperationHeatingLoad>("Vertical Slice Heating Operation");
  auto loadedChilledWaterOperation =
    loadedModel->getConcreteModelObjectByName<PlantEquipmentOperationCoolingLoad>("Vertical Slice Chilled Water Operation");
  auto loadedCondenserOperation = loadedModel->getConcreteModelObjectByName<PlantEquipmentOperationCoolingLoad>("Vertical Slice Condenser Operation");
  auto loadedHeatingOperationSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Vertical Slice Heating Operation Schedule");
  auto loadedChilledWaterOperationSchedule =
    loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Vertical Slice Chilled Water Operation Schedule");
  auto loadedCondenserOperationSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Vertical Slice Condenser Operation Schedule");
  ASSERT_TRUE(loadedHotWaterLoop);
  ASSERT_TRUE(loadedChilledWaterLoop);
  ASSERT_TRUE(loadedCondenserLoop);
  ASSERT_TRUE(loadedHotWaterPump);
  ASSERT_TRUE(loadedBoiler);
  ASSERT_TRUE(loadedChilledWaterPump);
  ASSERT_TRUE(loadedChiller);
  ASSERT_TRUE(loadedCondenserPump);
  ASSERT_TRUE(loadedCoolingTower);
  ASSERT_TRUE(loadedHeatingOperation);
  ASSERT_TRUE(loadedChilledWaterOperation);
  ASSERT_TRUE(loadedCondenserOperation);
  ASSERT_TRUE(loadedHeatingOperationSchedule);
  ASSERT_TRUE(loadedChilledWaterOperationSchedule);
  ASSERT_TRUE(loadedCondenserOperationSchedule);

  EXPECT_EQ("Heating", loadedHotWaterLoop->sizingPlant().loopType());
  EXPECT_EQ("Cooling", loadedChilledWaterLoop->sizingPlant().loopType());
  EXPECT_EQ("Condenser", loadedCondenserLoop->sizingPlant().loopType());
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedHotWaterLoop, *loadedHotWaterPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedHotWaterLoop, *loadedBoiler));
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedChilledWaterLoop, *loadedChilledWaterPump, true));
  EXPECT_TRUE(hasChilledWaterTopology(*loadedChilledWaterLoop, *loadedChiller));
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedCondenserLoop, *loadedCondenserPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedCondenserLoop, *loadedCoolingTower));
  EXPECT_TRUE(hasCondenserWaterTopology(*loadedCondenserLoop, *loadedChiller));
  EXPECT_EQ("WaterCooled", loadedChiller->condenserType());

  ASSERT_TRUE(loadedHotWaterLoop->plantEquipmentOperationHeatingLoad());
  ASSERT_TRUE(loadedChilledWaterLoop->plantEquipmentOperationCoolingLoad());
  ASSERT_TRUE(loadedCondenserLoop->plantEquipmentOperationCoolingLoad());
  ASSERT_TRUE(loadedHotWaterLoop->plantEquipmentOperationHeatingLoadSchedule());
  ASSERT_TRUE(loadedChilledWaterLoop->plantEquipmentOperationCoolingLoadSchedule());
  ASSERT_TRUE(loadedCondenserLoop->plantEquipmentOperationCoolingLoadSchedule());
  EXPECT_EQ(*loadedHeatingOperation, *loadedHotWaterLoop->plantEquipmentOperationHeatingLoad());
  EXPECT_EQ(*loadedChilledWaterOperation, *loadedChilledWaterLoop->plantEquipmentOperationCoolingLoad());
  EXPECT_EQ(*loadedCondenserOperation, *loadedCondenserLoop->plantEquipmentOperationCoolingLoad());
  EXPECT_EQ(*loadedHeatingOperationSchedule, *loadedHotWaterLoop->plantEquipmentOperationHeatingLoadSchedule());
  EXPECT_EQ(*loadedChilledWaterOperationSchedule, *loadedChilledWaterLoop->plantEquipmentOperationCoolingLoadSchedule());
  EXPECT_EQ(*loadedCondenserOperationSchedule, *loadedCondenserLoop->plantEquipmentOperationCoolingLoadSchedule());
  ASSERT_EQ(1u, loadedHeatingOperation->equipment(loadedHeatingOperation->maximumUpperLimit()).size());
  ASSERT_EQ(1u, loadedChilledWaterOperation->equipment(loadedChilledWaterOperation->maximumUpperLimit()).size());
  ASSERT_EQ(1u, loadedCondenserOperation->equipment(loadedCondenserOperation->maximumUpperLimit()).size());
  EXPECT_EQ(loadedBoiler->handle(), loadedHeatingOperation->equipment(loadedHeatingOperation->maximumUpperLimit()).front().handle());
  EXPECT_EQ(loadedChiller->handle(), loadedChilledWaterOperation->equipment(loadedChilledWaterOperation->maximumUpperLimit()).front().handle());
  EXPECT_EQ(loadedCoolingTower->handle(), loadedCondenserOperation->equipment(loadedCondenserOperation->maximumUpperLimit()).front().handle());

  const auto chillerHandle = loadedChiller->handle();
  ASSERT_TRUE(loadedChiller->removeFromSecondaryPlantLoop());
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedHotWaterLoop, *loadedHotWaterPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedHotWaterLoop, *loadedBoiler));
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedChilledWaterLoop, *loadedChilledWaterPump, true));
  EXPECT_TRUE(hasChilledWaterTopology(*loadedChilledWaterLoop, *loadedChiller));
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedCondenserLoop, *loadedCondenserPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedCondenserLoop, *loadedCoolingTower));
  EXPECT_TRUE(loadedCondenserLoop->demandComponents(ChillerElectricEIR::iddObjectType()).empty());
  ASSERT_TRUE(loadedCondenserLoop->plantEquipmentOperationCoolingLoad());
  ASSERT_TRUE(loadedCondenserLoop->plantEquipmentOperationCoolingLoadSchedule());
  EXPECT_EQ(*loadedCondenserOperation, *loadedCondenserLoop->plantEquipmentOperationCoolingLoad());
  EXPECT_EQ(*loadedCondenserOperationSchedule, *loadedCondenserLoop->plantEquipmentOperationCoolingLoadSchedule());
  ASSERT_EQ(1u, loadedCondenserOperation->equipment(loadedCondenserOperation->maximumUpperLimit()).size());
  EXPECT_EQ(loadedCoolingTower->handle(), loadedCondenserOperation->equipment(loadedCondenserOperation->maximumUpperLimit()).front().handle());
  EXPECT_FALSE(loadedChiller->condenserWaterLoop());
  EXPECT_FALSE(loadedChiller->condenserInletNode());
  EXPECT_FALSE(loadedChiller->condenserOutletNode());
  EXPECT_EQ("AirCooled", loadedChiller->condenserType());
  EXPECT_EQ(1u, loadedChilledWaterLoop->supplyComponents(ChillerElectricEIR::iddObjectType()).size());
  EXPECT_EQ(chillerHandle, loadedChilledWaterLoop->supplyComponents(ChillerElectricEIR::iddObjectType()).front().handle());
  ASSERT_EQ(1u, loadedChilledWaterOperation->equipment(loadedChilledWaterOperation->maximumUpperLimit()).size());
  EXPECT_EQ(chillerHandle, loadedChilledWaterOperation->equipment(loadedChilledWaterOperation->maximumUpperLimit()).front().handle());

  PlantLoop replacementCondenserLoop(*loadedModel);
  PumpVariableSpeed replacementCondenserPump(*loadedModel);
  CoolingTowerSingleSpeed replacementCoolingTower(*loadedModel);
  PlantEquipmentOperationCoolingLoad replacementCondenserOperation(*loadedModel);
  ScheduleConstant replacementCondenserOperationSchedule(*loadedModel);
  ASSERT_TRUE(replacementCondenserLoop.setName("Vertical Slice Replacement Condenser Loop"));
  ASSERT_TRUE(replacementCondenserPump.setName("Vertical Slice Replacement Condenser Pump"));
  ASSERT_TRUE(replacementCoolingTower.setName("Vertical Slice Replacement Cooling Tower"));
  ASSERT_TRUE(replacementCondenserOperation.setName("Vertical Slice Replacement Condenser Operation"));
  ASSERT_TRUE(replacementCondenserOperationSchedule.setName("Vertical Slice Replacement Condenser Operation Schedule"));
  ASSERT_TRUE(replacementCondenserOperationSchedule.setValue(1.0));
  ASSERT_TRUE(replacementCondenserLoop.sizingPlant().setLoopType("Condenser"));
  auto replacementCondenserSupplyInletNode = replacementCondenserLoop.supplyInletNode();
  ASSERT_TRUE(replacementCondenserPump.addToNode(replacementCondenserSupplyInletNode));
  ASSERT_TRUE(replacementCondenserLoop.addSupplyBranchForComponent(replacementCoolingTower));
  ASSERT_TRUE(replacementCondenserLoop.addDemandBranchForComponent(*loadedChiller));
  ASSERT_TRUE(replacementCondenserOperation.addEquipment(replacementCoolingTower));
  ASSERT_TRUE(replacementCondenserLoop.setPlantEquipmentOperationCoolingLoad(replacementCondenserOperation));
  ASSERT_TRUE(replacementCondenserLoop.setPlantEquipmentOperationCoolingLoadSchedule(replacementCondenserOperationSchedule));
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedHotWaterLoop, *loadedHotWaterPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedHotWaterLoop, *loadedBoiler));
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedChilledWaterLoop, *loadedChilledWaterPump, true));
  EXPECT_TRUE(hasChilledWaterTopology(*loadedChilledWaterLoop, *loadedChiller));
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedCondenserLoop, *loadedCondenserPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(*loadedCondenserLoop, *loadedCoolingTower));
  EXPECT_TRUE(hasStraightSupplyTopology(replacementCondenserLoop, replacementCondenserPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(replacementCondenserLoop, replacementCoolingTower));
  EXPECT_TRUE(hasCondenserWaterTopology(replacementCondenserLoop, *loadedChiller));
  EXPECT_EQ("WaterCooled", loadedChiller->condenserType());

  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto finalModel = Model::load(idfPath);
  ASSERT_TRUE(finalModel);
  auto finalHotWaterLoop = finalModel->getConcreteModelObjectByName<PlantLoop>("Vertical Slice Hot Water Loop");
  auto finalChilledWaterLoop = finalModel->getConcreteModelObjectByName<PlantLoop>("Vertical Slice Chilled Water Loop");
  auto finalOriginalCondenserLoop = finalModel->getConcreteModelObjectByName<PlantLoop>("Vertical Slice Condenser Loop");
  auto finalCondenserLoop = finalModel->getConcreteModelObjectByName<PlantLoop>("Vertical Slice Replacement Condenser Loop");
  auto finalHotWaterPump = finalModel->getConcreteModelObjectByName<PumpVariableSpeed>("Vertical Slice Hot Water Pump");
  auto finalBoiler = finalModel->getConcreteModelObjectByName<BoilerHotWater>("Vertical Slice Boiler");
  auto finalChilledWaterPump = finalModel->getConcreteModelObjectByName<PumpVariableSpeed>("Vertical Slice Chilled Water Pump");
  auto finalChiller = finalModel->getConcreteModelObjectByName<ChillerElectricEIR>("Vertical Slice Chiller");
  auto finalOriginalCondenserPump = finalModel->getConcreteModelObjectByName<PumpVariableSpeed>("Vertical Slice Condenser Pump");
  auto finalOriginalCoolingTower = finalModel->getConcreteModelObjectByName<CoolingTowerSingleSpeed>("Vertical Slice Cooling Tower");
  auto finalCondenserPump = finalModel->getConcreteModelObjectByName<PumpVariableSpeed>("Vertical Slice Replacement Condenser Pump");
  auto finalCoolingTower = finalModel->getConcreteModelObjectByName<CoolingTowerSingleSpeed>("Vertical Slice Replacement Cooling Tower");
  auto finalHeatingOperation = finalModel->getConcreteModelObjectByName<PlantEquipmentOperationHeatingLoad>("Vertical Slice Heating Operation");
  auto finalHeatingOperationSchedule = finalModel->getConcreteModelObjectByName<ScheduleConstant>("Vertical Slice Heating Operation Schedule");
  auto finalChilledWaterOperation =
    finalModel->getConcreteModelObjectByName<PlantEquipmentOperationCoolingLoad>("Vertical Slice Chilled Water Operation");
  auto finalChilledWaterOperationSchedule =
    finalModel->getConcreteModelObjectByName<ScheduleConstant>("Vertical Slice Chilled Water Operation Schedule");
  auto finalOriginalCondenserOperation =
    finalModel->getConcreteModelObjectByName<PlantEquipmentOperationCoolingLoad>("Vertical Slice Condenser Operation");
  auto finalOriginalCondenserOperationSchedule =
    finalModel->getConcreteModelObjectByName<ScheduleConstant>("Vertical Slice Condenser Operation Schedule");
  auto finalCondenserOperation =
    finalModel->getConcreteModelObjectByName<PlantEquipmentOperationCoolingLoad>("Vertical Slice Replacement Condenser Operation");
  auto finalCondenserOperationSchedule =
    finalModel->getConcreteModelObjectByName<ScheduleConstant>("Vertical Slice Replacement Condenser Operation Schedule");
  ASSERT_TRUE(finalHotWaterLoop);
  ASSERT_TRUE(finalChilledWaterLoop);
  ASSERT_TRUE(finalOriginalCondenserLoop);
  ASSERT_TRUE(finalCondenserLoop);
  ASSERT_TRUE(finalHotWaterPump);
  ASSERT_TRUE(finalBoiler);
  ASSERT_TRUE(finalChilledWaterPump);
  ASSERT_TRUE(finalChiller);
  ASSERT_TRUE(finalOriginalCondenserPump);
  ASSERT_TRUE(finalOriginalCoolingTower);
  ASSERT_TRUE(finalCondenserPump);
  ASSERT_TRUE(finalCoolingTower);
  ASSERT_TRUE(finalHeatingOperation);
  ASSERT_TRUE(finalHeatingOperationSchedule);
  ASSERT_TRUE(finalChilledWaterOperation);
  ASSERT_TRUE(finalChilledWaterOperationSchedule);
  ASSERT_TRUE(finalOriginalCondenserOperation);
  ASSERT_TRUE(finalOriginalCondenserOperationSchedule);
  ASSERT_TRUE(finalCondenserOperation);
  ASSERT_TRUE(finalCondenserOperationSchedule);

  EXPECT_EQ(4u, finalModel->getConcreteModelObjects<PlantLoop>().size());
  EXPECT_EQ("Heating", finalHotWaterLoop->sizingPlant().loopType());
  EXPECT_EQ("Cooling", finalChilledWaterLoop->sizingPlant().loopType());
  EXPECT_EQ("Condenser", finalOriginalCondenserLoop->sizingPlant().loopType());
  EXPECT_EQ("Condenser", finalCondenserLoop->sizingPlant().loopType());
  EXPECT_TRUE(hasStraightSupplyTopology(*finalHotWaterLoop, *finalHotWaterPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(*finalHotWaterLoop, *finalBoiler));
  EXPECT_TRUE(hasStraightSupplyTopology(*finalChilledWaterLoop, *finalChilledWaterPump, true));
  EXPECT_TRUE(hasChilledWaterTopology(*finalChilledWaterLoop, *finalChiller));
  EXPECT_TRUE(hasStraightSupplyTopology(*finalOriginalCondenserLoop, *finalOriginalCondenserPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(*finalOriginalCondenserLoop, *finalOriginalCoolingTower));
  EXPECT_TRUE(finalOriginalCondenserLoop->demandComponents(ChillerElectricEIR::iddObjectType()).empty());
  EXPECT_TRUE(hasStraightSupplyTopology(*finalCondenserLoop, *finalCondenserPump, true));
  EXPECT_TRUE(hasStraightSupplyTopology(*finalCondenserLoop, *finalCoolingTower));
  EXPECT_TRUE(hasCondenserWaterTopology(*finalCondenserLoop, *finalChiller));
  EXPECT_EQ("WaterCooled", finalChiller->condenserType());
  ASSERT_TRUE(finalHotWaterLoop->plantEquipmentOperationHeatingLoad());
  ASSERT_TRUE(finalHotWaterLoop->plantEquipmentOperationHeatingLoadSchedule());
  EXPECT_EQ(*finalHeatingOperation, *finalHotWaterLoop->plantEquipmentOperationHeatingLoad());
  EXPECT_EQ(*finalHeatingOperationSchedule, *finalHotWaterLoop->plantEquipmentOperationHeatingLoadSchedule());
  ASSERT_EQ(1u, finalHeatingOperation->equipment(finalHeatingOperation->maximumUpperLimit()).size());
  EXPECT_EQ(finalBoiler->handle(), finalHeatingOperation->equipment(finalHeatingOperation->maximumUpperLimit()).front().handle());
  ASSERT_TRUE(finalChilledWaterLoop->plantEquipmentOperationCoolingLoad());
  ASSERT_TRUE(finalChilledWaterLoop->plantEquipmentOperationCoolingLoadSchedule());
  EXPECT_EQ(*finalChilledWaterOperation, *finalChilledWaterLoop->plantEquipmentOperationCoolingLoad());
  EXPECT_EQ(*finalChilledWaterOperationSchedule, *finalChilledWaterLoop->plantEquipmentOperationCoolingLoadSchedule());
  ASSERT_EQ(1u, finalChilledWaterOperation->equipment(finalChilledWaterOperation->maximumUpperLimit()).size());
  EXPECT_EQ(finalChiller->handle(), finalChilledWaterOperation->equipment(finalChilledWaterOperation->maximumUpperLimit()).front().handle());
  ASSERT_TRUE(finalOriginalCondenserLoop->plantEquipmentOperationCoolingLoad());
  ASSERT_TRUE(finalOriginalCondenserLoop->plantEquipmentOperationCoolingLoadSchedule());
  EXPECT_EQ(*finalOriginalCondenserOperation, *finalOriginalCondenserLoop->plantEquipmentOperationCoolingLoad());
  EXPECT_EQ(*finalOriginalCondenserOperationSchedule, *finalOriginalCondenserLoop->plantEquipmentOperationCoolingLoadSchedule());
  ASSERT_EQ(1u, finalOriginalCondenserOperation->equipment(finalOriginalCondenserOperation->maximumUpperLimit()).size());
  EXPECT_EQ(finalOriginalCoolingTower->handle(),
            finalOriginalCondenserOperation->equipment(finalOriginalCondenserOperation->maximumUpperLimit()).front().handle());
  ASSERT_TRUE(finalCondenserLoop->plantEquipmentOperationCoolingLoad());
  ASSERT_TRUE(finalCondenserLoop->plantEquipmentOperationCoolingLoadSchedule());
  EXPECT_EQ(*finalCondenserOperation, *finalCondenserLoop->plantEquipmentOperationCoolingLoad());
  EXPECT_EQ(*finalCondenserOperationSchedule, *finalCondenserLoop->plantEquipmentOperationCoolingLoadSchedule());
  ASSERT_EQ(1u, finalCondenserOperation->equipment(finalCondenserOperation->maximumUpperLimit()).size());
  EXPECT_EQ(finalCoolingTower->handle(), finalCondenserOperation->equipment(finalCondenserOperation->maximumUpperLimit()).front().handle());
}
