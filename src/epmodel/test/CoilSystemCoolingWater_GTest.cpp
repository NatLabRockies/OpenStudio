/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ControllerWaterCoil.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilSystemCoolingWater.hpp"
#include <utilities/idd/CoilSystem_Cooling_Water_FieldEnums.hxx>
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilSystemCoolingWater_DefaultConstructor) {
  Model model;
  CoilSystemCoolingWater coilSystem(model);
  EXPECT_EQ(CoilSystemCoolingWater::iddObjectType(), coilSystem.iddObject().type());
  EXPECT_FALSE(coilSystem.nameString().empty());

  EXPECT_EQ("None", coilSystem.dehumidificationControlType());
  EXPECT_TRUE(coilSystem.runonSensibleLoad());
  EXPECT_FALSE(coilSystem.runonLatentLoad());
  EXPECT_DOUBLE_EQ(0.0, coilSystem.minimumAirToWaterTemperatureOffset());
  EXPECT_TRUE(coilSystem.economizerLockout());
  EXPECT_DOUBLE_EQ(0.0, coilSystem.minimumWaterLoopTemperatureForHeatRecovery());
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_ScalarAccessors_RoundTrip) {
  Model model;
  CoilSystemCoolingWater coilSystem(model);

  const auto dehumidificationControlTypes = CoilSystemCoolingWater::dehumidificationControlTypeValues();
  EXPECT_FALSE(dehumidificationControlTypes.empty());
  EXPECT_TRUE(std::find(dehumidificationControlTypes.begin(), dehumidificationControlTypes.end(), "CoolReheat")
              != dehumidificationControlTypes.end());

  EXPECT_TRUE(coilSystem.setDehumidificationControlType("CoolReheat"));
  EXPECT_EQ("CoolReheat", coilSystem.dehumidificationControlType());
  EXPECT_FALSE(coilSystem.setDehumidificationControlType("Invalid Dehumidification Control Type"));

  EXPECT_TRUE(coilSystem.setRunonSensibleLoad(false));
  EXPECT_FALSE(coilSystem.runonSensibleLoad());

  EXPECT_TRUE(coilSystem.setRunonLatentLoad(true));
  EXPECT_TRUE(coilSystem.runonLatentLoad());

  EXPECT_TRUE(coilSystem.setMinimumAirToWaterTemperatureOffset(1.0));
  EXPECT_DOUBLE_EQ(1.0, coilSystem.minimumAirToWaterTemperatureOffset());

  EXPECT_TRUE(coilSystem.setEconomizerLockout(false));
  EXPECT_FALSE(coilSystem.economizerLockout());

  EXPECT_TRUE(coilSystem.setMinimumWaterLoopTemperatureForHeatRecovery(1.2));
  EXPECT_DOUBLE_EQ(1.2, coilSystem.minimumWaterLoopTemperatureForHeatRecovery());
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilSystemCoolingWater supplyCoilSystem(model);
  CoilSystemCoolingWater demandCoilSystem(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyCoilSystem.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyCoilSystem.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyCoilSystem.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyCoilSystem.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoilSystem.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoilSystem.airLoopHVAC());
}

TEST_F(EPModelFixture, CoilSystemCoolingWater_ContainedCoolingCoilDoesNotCreateStandaloneController) {
  Model model;
  CoilSystemCoolingWater system(model);
  CoilCoolingWater coil(model);
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);

  ASSERT_TRUE(system.setPointer(openstudio::CoilSystem_Cooling_WaterFields::CoolingCoilName, coil.handle()));

  auto supplyOutletNode = airLoop.supplyOutletNode();
  ASSERT_TRUE(coil.addToNode(supplyOutletNode));
  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(coil));

  EXPECT_FALSE(coil.controllerWaterCoil());
}
