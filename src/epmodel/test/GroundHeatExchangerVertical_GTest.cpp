/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedFiniteDifference.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedFiniteDifference_Impl.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedKusudaAchenbach.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedXing.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedXing_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/GroundHeatExchangerVertical.hpp"
#include "../StraightComponent/GroundHeatExchangerVertical_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/GroundHeatExchanger_ResponseFactors_FieldEnums.hxx>
#include <utilities/idd/GroundHeatExchanger_System_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatExchangerVertical_DefaultConstructor) {
  Model model;
  GroundHeatExchangerVertical ghx(model);
  EXPECT_EQ(GroundHeatExchangerVertical::iddObjectType(), ghx.iddObject().type());
  EXPECT_FALSE(ghx.nameString().empty());

  const auto designFlowRate = ghx.designFlowRate();
  ASSERT_TRUE(designFlowRate);
  EXPECT_DOUBLE_EQ(0.0033, *designFlowRate);

  const auto numberofBoreHoles = ghx.numberofBoreHoles();
  ASSERT_TRUE(numberofBoreHoles);
  EXPECT_EQ(120, *numberofBoreHoles);
  EXPECT_DOUBLE_EQ(0.0005, ghx.gFunctionReferenceRatio());
  EXPECT_DOUBLE_EQ(1.0, ghx.boreHoleTopDepth());

  const auto boreHoleLength = ghx.boreHoleLength();
  ASSERT_TRUE(boreHoleLength);
  EXPECT_DOUBLE_EQ(76.2, *boreHoleLength);

  const auto boreHoleRadius = ghx.boreHoleRadius();
  ASSERT_TRUE(boreHoleRadius);
  EXPECT_DOUBLE_EQ(0.635080E-01, *boreHoleRadius);

  const auto gFunctions = ghx.gFunctions();
  ASSERT_EQ(35u, gFunctions.size());
  EXPECT_DOUBLE_EQ(-15.2996, gFunctions.front().lnValue());
  EXPECT_DOUBLE_EQ(-0.348322, gFunctions.front().gValue());
  EXPECT_DOUBLE_EQ(3.003, gFunctions.back().lnValue());
  EXPECT_DOUBLE_EQ(72.511, gFunctions.back().gValue());

  auto undisturbed = ghx.undisturbedGroundTemperatureModel();
  auto kusuda = undisturbed.optionalCast<SiteGroundTemperatureUndisturbedKusudaAchenbach>();
  ASSERT_TRUE(kusuda);
  EXPECT_DOUBLE_EQ(0.692626, kusuda->soilThermalConductivity());
  EXPECT_DOUBLE_EQ(920.0, kusuda->soilDensity());
  EXPECT_DOUBLE_EQ(0.234700E+07 / 920.0, kusuda->soilSpecificHeat());
  ASSERT_TRUE(kusuda->averageSoilSurfaceTemperature());
  EXPECT_DOUBLE_EQ(13.375, *kusuda->averageSoilSurfaceTemperature());
  ASSERT_TRUE(kusuda->averageAmplitudeofSurfaceTemperature());
  EXPECT_DOUBLE_EQ(3.2, *kusuda->averageAmplitudeofSurfaceTemperature());
  ASSERT_TRUE(kusuda->phaseShiftofMinimumSurfaceTemperature());
  EXPECT_DOUBLE_EQ(8.0, *kusuda->phaseShiftofMinimumSurfaceTemperature());

  auto propertiesTarget = ghx.getTarget(openstudio::GroundHeatExchanger_ResponseFactorsFields::GHE_Vertical_PropertiesObjectName);
  ASSERT_TRUE(propertiesTarget);
  auto systems = model.getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_System);
  ASSERT_EQ(1u, systems.size());
  EXPECT_EQ(ghx.handle(), systems[0].getTarget(openstudio::GroundHeatExchanger_SystemFields::GHE_Vertical_ResponseFactorsObjectName)->handle());
  EXPECT_EQ(kusuda->handle(), systems[0].getTarget(openstudio::GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelName)->handle());
  ASSERT_TRUE(systems[0].getString(openstudio::GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelType, true));
  EXPECT_EQ(kusuda->iddObject().name(),
            systems[0].getString(openstudio::GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelType, true).get());
}

TEST_F(EPModelFixture, GroundHeatExchangerVertical_RelationshipAndGFunctionAccessors_RoundTrip) {
  Model model;
  SiteGroundTemperatureUndisturbedXing initialXing(model);
  GroundHeatExchangerVertical ghx(model, initialXing);

  EXPECT_EQ(initialXing.handle(), ghx.undisturbedGroundTemperatureModel().handle());
  auto systems = model.getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_System);
  ASSERT_EQ(1u, systems.size());
  EXPECT_EQ(initialXing.handle(), systems[0].getTarget(openstudio::GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelName)->handle());
  ASSERT_TRUE(systems[0].getString(openstudio::GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelType, true));
  EXPECT_EQ(initialXing.iddObject().name(),
            systems[0].getString(openstudio::GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelType, true).get());

  EXPECT_TRUE(ghx.setDesignFlowRate(0.004));
  EXPECT_TRUE(ghx.setNumberofBoreHoles(156));
  EXPECT_TRUE(ghx.setBoreHoleTopDepth(1.25));
  EXPECT_TRUE(ghx.setBoreHoleLength(80.2));
  EXPECT_TRUE(ghx.setBoreHoleRadius(0.07));
  EXPECT_TRUE(ghx.setGroundThermalConductivity(0.7));
  EXPECT_TRUE(ghx.setGroundThermalHeatCapacity(0.3E+07));
  EXPECT_TRUE(ghx.setGroutThermalConductivity(0.72));
  EXPECT_TRUE(ghx.setPipeThermalConductivity(0.45));
  EXPECT_TRUE(ghx.setPipeOutDiameter(0.03));
  EXPECT_TRUE(ghx.setUTubeDistance(0.028));
  EXPECT_TRUE(ghx.setPipeThickness(0.003));
  EXPECT_TRUE(ghx.setGFunctionReferenceRatio(0.0012));

  EXPECT_TRUE(ghx.designFlowRate());
  EXPECT_DOUBLE_EQ(0.004, *ghx.designFlowRate());
  ASSERT_TRUE(ghx.numberofBoreHoles());
  EXPECT_EQ(156, *ghx.numberofBoreHoles());
  EXPECT_DOUBLE_EQ(1.25, ghx.boreHoleTopDepth());
  ASSERT_TRUE(ghx.boreHoleLength());
  EXPECT_DOUBLE_EQ(80.2, *ghx.boreHoleLength());
  ASSERT_TRUE(ghx.boreHoleRadius());
  EXPECT_DOUBLE_EQ(0.07, *ghx.boreHoleRadius());
  ASSERT_TRUE(ghx.groundThermalConductivity());
  EXPECT_DOUBLE_EQ(0.7, *ghx.groundThermalConductivity());
  ASSERT_TRUE(ghx.groundThermalHeatCapacity());
  EXPECT_DOUBLE_EQ(0.3E+07, *ghx.groundThermalHeatCapacity());
  ASSERT_TRUE(ghx.groutThermalConductivity());
  EXPECT_DOUBLE_EQ(0.72, *ghx.groutThermalConductivity());
  ASSERT_TRUE(ghx.pipeThermalConductivity());
  EXPECT_DOUBLE_EQ(0.45, *ghx.pipeThermalConductivity());
  ASSERT_TRUE(ghx.pipeOutDiameter());
  EXPECT_DOUBLE_EQ(0.03, *ghx.pipeOutDiameter());
  ASSERT_TRUE(ghx.uTubeDistance());
  EXPECT_DOUBLE_EQ(0.028, *ghx.uTubeDistance());
  ASSERT_TRUE(ghx.pipeThickness());
  EXPECT_DOUBLE_EQ(0.003, *ghx.pipeThickness());
  EXPECT_DOUBLE_EQ(0.0012, ghx.gFunctionReferenceRatio());
  EXPECT_FALSE(ghx.isGFunctionReferenceRatioDefaulted());

  ghx.resetBoreHoleLength();
  ghx.resetBoreHoleRadius();
  ghx.resetGroundThermalConductivity();
  ghx.resetGroundThermalHeatCapacity();
  ghx.resetGroutThermalConductivity();
  ghx.resetPipeThermalConductivity();
  ghx.resetPipeOutDiameter();
  ghx.resetUTubeDistance();
  ghx.resetPipeThickness();
  ghx.resetNumberofBoreHoles();
  ghx.resetGFunctionReferenceRatio();
  EXPECT_FALSE(ghx.boreHoleLength());
  EXPECT_FALSE(ghx.boreHoleRadius());
  EXPECT_FALSE(ghx.groundThermalConductivity());
  EXPECT_FALSE(ghx.groundThermalHeatCapacity());
  EXPECT_FALSE(ghx.groutThermalConductivity());
  EXPECT_FALSE(ghx.pipeThermalConductivity());
  EXPECT_FALSE(ghx.pipeOutDiameter());
  EXPECT_FALSE(ghx.uTubeDistance());
  EXPECT_FALSE(ghx.pipeThickness());
  EXPECT_FALSE(ghx.numberofBoreHoles());
  EXPECT_TRUE(ghx.isGFunctionReferenceRatioDefaulted());

  ghx.removeAllGFunctions();
  EXPECT_TRUE(ghx.gFunctions().empty());
  EXPECT_TRUE(ghx.addGFunction(-1.0, 2.0));
  EXPECT_TRUE(ghx.addGFunction(GFunction(0.5, 3.0)));
  auto gFunctions = ghx.gFunctions();
  ASSERT_EQ(2u, gFunctions.size());
  EXPECT_DOUBLE_EQ(-1.0, gFunctions[0].lnValue());
  EXPECT_DOUBLE_EQ(2.0, gFunctions[0].gValue());
  EXPECT_DOUBLE_EQ(0.5, gFunctions[1].lnValue());
  EXPECT_DOUBLE_EQ(3.0, gFunctions[1].gValue());
  ghx.removeGFunction(0);
  gFunctions = ghx.gFunctions();
  ASSERT_EQ(1u, gFunctions.size());
  EXPECT_DOUBLE_EQ(0.5, gFunctions[0].lnValue());
  EXPECT_DOUBLE_EQ(3.0, gFunctions[0].gValue());

  SiteGroundTemperatureUndisturbedFiniteDifference finiteDifference(model);
  EXPECT_TRUE(ghx.setUndisturbedGroundTemperatureModel(finiteDifference));
  EXPECT_EQ(finiteDifference.handle(), ghx.undisturbedGroundTemperatureModel().handle());
  EXPECT_EQ(finiteDifference.handle(), systems[0].getTarget(openstudio::GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelName)->handle());
  ASSERT_TRUE(systems[0].getString(openstudio::GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelType, true));
  EXPECT_EQ(finiteDifference.iddObject().name(),
            systems[0].getString(openstudio::GroundHeatExchanger_SystemFields::UndisturbedGroundTemperatureModelType, true).get());
}

TEST_F(EPModelFixture, GroundHeatExchangerVertical_RejectsUnsupportedUndisturbedGroundModelTarget) {
  Model model;
  GroundHeatExchangerVertical ghx(model);
  PlantLoop unsupportedModelObject(model);

  EXPECT_FALSE(ghx.setUndisturbedGroundTemperatureModel(unsupportedModelObject));
  EXPECT_THROW(GroundHeatExchangerVertical(model, unsupportedModelObject), openstudio::Exception);
  EXPECT_EQ(1u, model.getConcreteModelObjects<GroundHeatExchangerVertical>().size());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_System).size());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_Vertical_Properties).size());
}

TEST_F(EPModelFixture, GroundHeatExchangerVertical_Remove_CleansCompanionObjects) {
  Model model;
  GroundHeatExchangerVertical ghx(model);

  EXPECT_EQ(1u, model.getConcreteModelObjects<GroundHeatExchangerVertical>().size());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_System).size());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_Vertical_Properties).size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<SiteGroundTemperatureUndisturbedKusudaAchenbach>().size());

  ghx.remove();

  EXPECT_EQ(0u, model.getConcreteModelObjects<GroundHeatExchangerVertical>().size());
  EXPECT_EQ(0u, model.getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_System).size());
  EXPECT_EQ(0u, model.getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_Vertical_Properties).size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<SiteGroundTemperatureUndisturbedKusudaAchenbach>().size());
}

TEST_F(EPModelFixture, GroundHeatExchangerVertical_RemoveWhileAttached_CleansLoopAndCompanionObjects) {
  Model model;
  PlantLoop plantLoop(model);
  GroundHeatExchangerVertical ghx(model);

  auto plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(ghx.addToNode(plantSupplyOutletNode));
  ASSERT_EQ(1u, plantLoop.supplyComponents(GroundHeatExchangerVertical::iddObjectType()).size());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_System).size());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_Vertical_Properties).size());

  ghx.remove();

  EXPECT_TRUE(plantLoop.supplyComponents(GroundHeatExchangerVertical::iddObjectType()).empty());
  EXPECT_TRUE(plantLoop.supplyComponents(openstudio::IddObjectType::GroundHeatExchanger_System).empty());
  EXPECT_EQ(0u, model.getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_System).size());
  EXPECT_EQ(0u, model.getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_Vertical_Properties).size());
}

TEST_F(EPModelFixture, GroundHeatExchangerVertical_AddToNode_PlantNonDemandOnly) {
  Model model;
  GroundHeatExchangerVertical ghx(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(ghx.addToNode(airSupplyOutletNode));
  EXPECT_FALSE(ghx.loop());
  EXPECT_FALSE(ghx.inletModelObject());
  EXPECT_FALSE(ghx.outletModelObject());

  auto splitterBranch = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranch);
  auto airDemandNode = splitterBranch->optionalCast<Node>();
  ASSERT_TRUE(airDemandNode);
  EXPECT_FALSE(ghx.addToNode(*airDemandNode));
  EXPECT_FALSE(ghx.loop());

  PlantLoop plantLoop(model);
  auto plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(ghx.addToNode(plantSupplyOutletNode));
  ASSERT_TRUE(ghx.loop());
  EXPECT_EQ(plantLoop.handle(), ghx.loop()->handle());
  ASSERT_TRUE(ghx.inletModelObject());
  ASSERT_TRUE(ghx.outletModelObject());
  EXPECT_TRUE(plantLoop.supplyComponent(ghx.handle()));
  EXPECT_FALSE(plantLoop.demandComponent(ghx.handle()));
  ASSERT_EQ(1u, plantLoop.supplyComponents(GroundHeatExchangerVertical::iddObjectType()).size());
  EXPECT_EQ(ghx.handle(), plantLoop.supplyComponents(GroundHeatExchangerVertical::iddObjectType())[0].handle());
  EXPECT_TRUE(plantLoop.supplyComponents(openstudio::IddObjectType::GroundHeatExchanger_System).empty());

  auto systems = model.getObjectsByType(openstudio::IddObjectType::GroundHeatExchanger_System);
  ASSERT_GE(systems.size(), 1u);
  EXPECT_EQ(ghx.inletModelObject()->handle(), systems[0].getTarget(openstudio::GroundHeatExchanger_SystemFields::InletNodeName)->handle());
  EXPECT_EQ(ghx.outletModelObject()->handle(), systems[0].getTarget(openstudio::GroundHeatExchanger_SystemFields::OutletNodeName)->handle());

  PlantLoop secondPlantLoop(model);
  GroundHeatExchangerVertical supplyInletComponent(model);
  auto plantSupplyInletNode = secondPlantLoop.supplyInletNode();
  EXPECT_TRUE(supplyInletComponent.addToNode(plantSupplyInletNode));
  ASSERT_TRUE(supplyInletComponent.loop());
  EXPECT_EQ(secondPlantLoop.handle(), supplyInletComponent.loop()->handle());
  EXPECT_TRUE(secondPlantLoop.supplyComponent(supplyInletComponent.handle()));
  EXPECT_FALSE(secondPlantLoop.demandComponent(supplyInletComponent.handle()));

  GroundHeatExchangerVertical second(model);
  auto plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(second.addToNode(plantDemandOutletNode));
  EXPECT_FALSE(second.loop());
  EXPECT_FALSE(second.inletModelObject());
  EXPECT_FALSE(second.outletModelObject());
}

TEST_F(EPModelFixture, GroundHeatExchangerVertical_AddToNode_InsertsIntoNonEmptySupplyBranch) {
  Model model;
  PlantLoop plantLoop(model);
  GroundHeatExchangerVertical downstream(model);

  auto plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(downstream.addToNode(plantSupplyOutletNode));
  auto anchorNodeObject = downstream.inletModelObject();
  ASSERT_TRUE(anchorNodeObject);
  auto anchorNode = anchorNodeObject->optionalCast<Node>();
  ASSERT_TRUE(anchorNode);

  GroundHeatExchangerVertical upstream(model);
  EXPECT_TRUE(upstream.addToNode(*anchorNode));

  ASSERT_TRUE(upstream.inletModelObject());
  ASSERT_TRUE(upstream.outletModelObject());
  ASSERT_TRUE(downstream.inletModelObject());
  EXPECT_EQ(anchorNode->handle(), upstream.inletModelObject()->handle());
  EXPECT_EQ(upstream.outletModelObject()->handle(), downstream.inletModelObject()->handle());

  const auto supplyComponents = plantLoop.supplyComponents(GroundHeatExchangerVertical::iddObjectType());
  ASSERT_EQ(2u, supplyComponents.size());
  EXPECT_EQ(upstream.handle(), supplyComponents[0].handle());
  EXPECT_EQ(downstream.handle(), supplyComponents[1].handle());
  EXPECT_TRUE(plantLoop.supplyComponents(openstudio::IddObjectType::GroundHeatExchanger_System).empty());
}

TEST_F(EPModelFixture, GroundHeatExchangerVertical_RemoveFromPlantLoop_UsesProjectedTraversalIdentity) {
  Model model;
  PlantLoop plantLoop(model);
  GroundHeatExchangerVertical ghx(model);

  EXPECT_TRUE(plantLoop.addSupplyBranchForComponent(ghx));
  ASSERT_TRUE(plantLoop.supplyComponent(ghx.handle()));
  ASSERT_EQ(1u, plantLoop.supplyComponents(GroundHeatExchangerVertical::iddObjectType()).size());
  EXPECT_EQ(ghx.handle(), plantLoop.supplyComponents(GroundHeatExchangerVertical::iddObjectType())[0].handle());

  EXPECT_TRUE(plantLoop.removeSupplyBranchWithComponent(ghx));
  EXPECT_FALSE(ghx.loop());
  EXPECT_FALSE(ghx.inletModelObject());
  EXPECT_FALSE(ghx.outletModelObject());
  EXPECT_FALSE(plantLoop.supplyComponent(ghx.handle()));
  EXPECT_TRUE(plantLoop.supplyComponents(GroundHeatExchangerVertical::iddObjectType()).empty());
  EXPECT_TRUE(plantLoop.supplyComponents(openstudio::IddObjectType::GroundHeatExchanger_System).empty());
}
