/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedKusudaAchenbach.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedKusudaAchenbach_Impl.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedFiniteDifference.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedFiniteDifference_Impl.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedXing.hpp"
#include "../ModelObject/SiteGroundTemperatureUndisturbedXing_Impl.hpp"

#include <utilities/idd/GroundHeatExchanger_HorizontalTrench_FieldEnums.hxx>
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/GroundHeatExchangerHorizontalTrench.hpp"
#include "../StraightComponent/GroundHeatExchangerHorizontalTrench_Impl.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatExchangerHorizontalTrench_DefaultConstructor) {
  Model model;
  GroundHeatExchangerHorizontalTrench ghx(model);
  EXPECT_EQ(GroundHeatExchangerHorizontalTrench::iddObjectType(), ghx.iddObject().type());
  EXPECT_FALSE(ghx.nameString().empty());

  EXPECT_DOUBLE_EQ(0.004, ghx.designFlowRate());
  EXPECT_DOUBLE_EQ(75.0, ghx.trenchLengthinPipeAxialDirection());
  EXPECT_EQ(2, ghx.numberofTrenches());
  EXPECT_DOUBLE_EQ(2.0, ghx.horizontalSpacingBetweenPipes());
  EXPECT_DOUBLE_EQ(0.016, ghx.pipeInnerDiameter());
  EXPECT_DOUBLE_EQ(0.02667, ghx.pipeOuterDiameter());
  EXPECT_DOUBLE_EQ(1.25, ghx.burialDepth());
  EXPECT_DOUBLE_EQ(1.08, ghx.soilThermalConductivity());
  EXPECT_DOUBLE_EQ(962.0, ghx.soilDensity());
  EXPECT_DOUBLE_EQ(2576.0, ghx.soilSpecificHeat());
  EXPECT_DOUBLE_EQ(0.3895, ghx.pipeThermalConductivity());
  EXPECT_DOUBLE_EQ(641.0, ghx.pipeDensity());
  EXPECT_DOUBLE_EQ(2405.0, ghx.pipeSpecificHeat());
  EXPECT_DOUBLE_EQ(30.0, ghx.soilMoistureContentPercent());
  EXPECT_DOUBLE_EQ(50.0, ghx.soilMoistureContentPercentatSaturation());
  EXPECT_DOUBLE_EQ(0.408, ghx.evapotranspirationGroundCoverParameter());

  auto undisturbed = ghx.undisturbedGroundTemperatureModel();
  auto kusuda = undisturbed.optionalCast<SiteGroundTemperatureUndisturbedKusudaAchenbach>();
  ASSERT_TRUE(kusuda);
  EXPECT_EQ("KusudaAchenbach", ghx.groundTemperatureModel());
  EXPECT_FALSE(ghx.isGroundTemperatureModelDefaulted());
  EXPECT_DOUBLE_EQ(15.5, ghx.kusudaAchenbachAverageSurfaceTemperature());
  EXPECT_DOUBLE_EQ(12.8, ghx.kusudaAchenbachAverageAmplitudeofSurfaceTemperature());
  EXPECT_DOUBLE_EQ(17.3, ghx.kusudaAchenbachPhaseShiftofMinimumSurfaceTemperature());
}

TEST_F(EPModelFixture, GroundHeatExchangerHorizontalTrench_ScalarAndRelationshipAccessors_RoundTrip) {
  Model model;
  GroundHeatExchangerHorizontalTrench ghx(model);

  SiteGroundTemperatureUndisturbedXing initialXing(model);
  GroundHeatExchangerHorizontalTrench ghxWithExplicitModel(model, initialXing);
  EXPECT_DOUBLE_EQ(0.004, ghxWithExplicitModel.designFlowRate());
  EXPECT_DOUBLE_EQ(0.408, ghxWithExplicitModel.evapotranspirationGroundCoverParameter());
  EXPECT_EQ(initialXing.handle(), ghxWithExplicitModel.undisturbedGroundTemperatureModel().handle());
  ASSERT_TRUE(ghxWithExplicitModel.getTarget(openstudio::GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelName));
  EXPECT_EQ(initialXing.handle(),
            ghxWithExplicitModel.getTarget(openstudio::GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelName)->handle());
  ASSERT_TRUE(ghxWithExplicitModel.getString(openstudio::GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelType, true));
  EXPECT_EQ(
    initialXing.iddObject().name(),
    ghxWithExplicitModel.getString(openstudio::GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelType, true).get());
  EXPECT_EQ("SiteGroundTemperature", ghxWithExplicitModel.groundTemperatureModel());
  auto xingCloneObject = model.addObject(ghxWithExplicitModel.idfObject());
  ASSERT_TRUE(xingCloneObject);
  auto xingClone = xingCloneObject->cast<GroundHeatExchangerHorizontalTrench>();
  EXPECT_EQ(initialXing.handle(), xingClone.undisturbedGroundTemperatureModel().handle());

  EXPECT_TRUE(ghx.setDesignFlowRate(0.006));
  EXPECT_DOUBLE_EQ(0.006, ghx.designFlowRate());

  EXPECT_TRUE(ghx.setTrenchLengthinPipeAxialDirection(90.0));
  EXPECT_DOUBLE_EQ(90.0, ghx.trenchLengthinPipeAxialDirection());

  EXPECT_TRUE(ghx.setNumberofTrenches(3));
  EXPECT_EQ(3, ghx.numberofTrenches());

  EXPECT_TRUE(ghx.setHorizontalSpacingBetweenPipes(2.5));
  EXPECT_DOUBLE_EQ(2.5, ghx.horizontalSpacingBetweenPipes());

  EXPECT_TRUE(ghx.setPipeInnerDiameter(0.02));
  EXPECT_DOUBLE_EQ(0.02, ghx.pipeInnerDiameter());

  EXPECT_TRUE(ghx.setPipeOuterDiameter(0.03));
  EXPECT_DOUBLE_EQ(0.03, ghx.pipeOuterDiameter());

  EXPECT_TRUE(ghx.setBurialDepth(1.75));
  EXPECT_DOUBLE_EQ(1.75, ghx.burialDepth());

  EXPECT_TRUE(ghx.setSoilThermalConductivity(1.5));
  EXPECT_DOUBLE_EQ(1.5, ghx.soilThermalConductivity());

  EXPECT_TRUE(ghx.setSoilDensity(1000.0));
  EXPECT_DOUBLE_EQ(1000.0, ghx.soilDensity());

  EXPECT_TRUE(ghx.setSoilSpecificHeat(2600.0));
  EXPECT_DOUBLE_EQ(2600.0, ghx.soilSpecificHeat());

  EXPECT_TRUE(ghx.setPipeThermalConductivity(0.42));
  EXPECT_DOUBLE_EQ(0.42, ghx.pipeThermalConductivity());

  EXPECT_TRUE(ghx.setPipeDensity(700.0));
  EXPECT_DOUBLE_EQ(700.0, ghx.pipeDensity());

  EXPECT_TRUE(ghx.setPipeSpecificHeat(2500.0));
  EXPECT_DOUBLE_EQ(2500.0, ghx.pipeSpecificHeat());

  EXPECT_TRUE(ghx.setSoilMoistureContentPercent(35.0));
  EXPECT_DOUBLE_EQ(35.0, ghx.soilMoistureContentPercent());

  EXPECT_TRUE(ghx.setSoilMoistureContentPercentatSaturation(55.0));
  EXPECT_DOUBLE_EQ(55.0, ghx.soilMoistureContentPercentatSaturation());

  EXPECT_TRUE(ghx.setEvapotranspirationGroundCoverParameter(0.5));
  EXPECT_DOUBLE_EQ(0.5, ghx.evapotranspirationGroundCoverParameter());

  SiteGroundTemperatureUndisturbedKusudaAchenbach kusuda(model);
  EXPECT_TRUE(ghx.setUndisturbedGroundTemperatureModel(kusuda));
  EXPECT_EQ(kusuda.handle(), ghx.undisturbedGroundTemperatureModel().handle());
  EXPECT_TRUE(ghx.setKusudaAchenbachAverageSurfaceTemperature(16.0));
  EXPECT_TRUE(ghx.setKusudaAchenbachAverageAmplitudeofSurfaceTemperature(13.0));
  EXPECT_TRUE(ghx.setKusudaAchenbachPhaseShiftofMinimumSurfaceTemperature(18.0));
  EXPECT_DOUBLE_EQ(16.0, ghx.kusudaAchenbachAverageSurfaceTemperature());
  EXPECT_DOUBLE_EQ(13.0, ghx.kusudaAchenbachAverageAmplitudeofSurfaceTemperature());
  EXPECT_DOUBLE_EQ(18.0, ghx.kusudaAchenbachPhaseShiftofMinimumSurfaceTemperature());
  ASSERT_TRUE(ghx.getTarget(openstudio::GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelName));
  EXPECT_EQ(kusuda.handle(), ghx.getTarget(openstudio::GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelName)->handle());
  ASSERT_TRUE(ghx.getString(openstudio::GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelType, true));
  EXPECT_EQ(kusuda.iddObject().name(),
            ghx.getString(openstudio::GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelType, true).get());
  EXPECT_FALSE(ghx.setGroundTemperatureModel("SiteGroundTemperature"));
  ghx.resetGroundTemperatureModel();
  EXPECT_EQ(kusuda.handle(), ghx.undisturbedGroundTemperatureModel().handle());
  EXPECT_EQ("KusudaAchenbach", ghx.groundTemperatureModel());

  SiteGroundTemperatureUndisturbedFiniteDifference finiteDifference(model);
  EXPECT_TRUE(ghx.setUndisturbedGroundTemperatureModel(finiteDifference));
  EXPECT_EQ(finiteDifference.handle(), ghx.undisturbedGroundTemperatureModel().handle());
  ASSERT_TRUE(ghx.getTarget(openstudio::GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelName));
  EXPECT_EQ(finiteDifference.handle(),
            ghx.getTarget(openstudio::GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelName)->handle());
  ASSERT_TRUE(ghx.getString(openstudio::GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelType, true));
  EXPECT_EQ(finiteDifference.iddObject().name(),
            ghx.getString(openstudio::GroundHeatExchanger_HorizontalTrenchFields::UndisturbedGroundTemperatureModelType, true).get());
  EXPECT_EQ("SiteGroundTemperature", ghx.groundTemperatureModel());
  EXPECT_THROW(ghx.kusudaAchenbachAverageSurfaceTemperature(), openstudio::Exception);
  EXPECT_THROW(ghx.kusudaAchenbachAverageAmplitudeofSurfaceTemperature(), openstudio::Exception);
  EXPECT_THROW(ghx.kusudaAchenbachPhaseShiftofMinimumSurfaceTemperature(), openstudio::Exception);
  auto finiteDifferenceCloneObject = model.addObject(ghx.idfObject());
  ASSERT_TRUE(finiteDifferenceCloneObject);
  auto finiteDifferenceClone = finiteDifferenceCloneObject->cast<GroundHeatExchangerHorizontalTrench>();
  EXPECT_EQ(finiteDifference.handle(), finiteDifferenceClone.undisturbedGroundTemperatureModel().handle());
}

TEST_F(EPModelFixture, GroundHeatExchangerHorizontalTrench_RejectsIncompatibleUndisturbedGroundModel) {
  Model model;
  GroundHeatExchangerHorizontalTrench ghx(model);
  PlantLoop invalidModel(model);

  EXPECT_FALSE(ghx.setUndisturbedGroundTemperatureModel(invalidModel));
  EXPECT_THROW(GroundHeatExchangerHorizontalTrench(model, invalidModel), openstudio::Exception);
  EXPECT_EQ(1u, model.getConcreteModelObjects<GroundHeatExchangerHorizontalTrench>().size());
}

TEST_F(EPModelFixture, GroundHeatExchangerHorizontalTrench_AddToNodeCloneAndRemove_PlantNonDemandOnly) {
  Model model;
  GroundHeatExchangerHorizontalTrench ghx(model);

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

  PlantLoop secondPlantLoop(model);
  GroundHeatExchangerHorizontalTrench supplyInletComponent(model);
  auto plantSupplyInletNode = secondPlantLoop.supplyInletNode();
  EXPECT_TRUE(supplyInletComponent.addToNode(plantSupplyInletNode));
  ASSERT_TRUE(supplyInletComponent.loop());
  EXPECT_EQ(secondPlantLoop.handle(), supplyInletComponent.loop()->handle());
  EXPECT_TRUE(secondPlantLoop.supplyComponent(supplyInletComponent.handle()));
  EXPECT_FALSE(secondPlantLoop.demandComponent(supplyInletComponent.handle()));

  GroundHeatExchangerHorizontalTrench second(model);
  auto plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(second.addToNode(plantDemandOutletNode));
  EXPECT_FALSE(second.loop());
  EXPECT_FALSE(second.inletModelObject());
  EXPECT_FALSE(second.outletModelObject());

  auto linkedGroundModel = ghx.undisturbedGroundTemperatureModel();
  auto cloneObject = model.addObject(ghx.idfObject());
  ASSERT_TRUE(cloneObject);
  auto clone = cloneObject->cast<GroundHeatExchangerHorizontalTrench>();
  EXPECT_EQ(linkedGroundModel.handle(), clone.undisturbedGroundTemperatureModel().handle());

  ghx.remove();
  EXPECT_EQ(3u, model.getConcreteModelObjects<GroundHeatExchangerHorizontalTrench>().size());
  EXPECT_EQ(5u, plantLoop.supplyComponents().size());
  EXPECT_EQ(linkedGroundModel.handle(), clone.undisturbedGroundTemperatureModel().handle());
}
