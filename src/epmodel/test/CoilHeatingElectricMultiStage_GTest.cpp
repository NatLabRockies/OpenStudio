/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilHeatingElectricMultiStage.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/Coil_Heating_Electric_MultiStage_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingElectricMultiStage_DefaultConstructor) {
  Model model;
  CoilHeatingElectricMultiStage coil(model);
  EXPECT_EQ(CoilHeatingElectricMultiStage::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  EXPECT_EQ(1u, coil.numberOfStages());
}

TEST_F(EPModelFixture, CoilHeatingElectricMultiStage_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingElectricMultiStage coil(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.3));

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  ASSERT_TRUE(coil.setPointer(openstudio::Coil_Heating_Electric_MultiStageFields::AvailabilityScheduleName, openstudio::Handle()));
  const auto repairedAvailability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(repairedAvailability);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), repairedAvailability->handle());
  EXPECT_DOUBLE_EQ(1.0, repairedAvailability->value());

  EXPECT_TRUE(coil.setUnsigned(openstudio::Coil_Heating_Electric_MultiStageFields::NumberofStages, 3u));
  EXPECT_EQ(3u, coil.numberOfStages());

  EXPECT_TRUE(coil.setName("HP Electric MultiStage Coil"));
  EXPECT_EQ("HP Electric MultiStage Coil", coil.nameString());
}

TEST_F(EPModelFixture, CoilHeatingElectricMultiStage_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  CoilHeatingElectricMultiStage supplyCoil(model);
  CoilHeatingElectricMultiStage demandCoil(model);
  CoilHeatingElectricMultiStage standaloneCoil(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_FALSE(supplyCoil.addToNode(supplyInletNode));
  EXPECT_FALSE(supplyCoil.inletModelObject());
  EXPECT_FALSE(supplyCoil.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoil.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoil.airLoopHVAC());

  ASSERT_TRUE(oaSystem.outboardOANode());
  auto oaNode = oaSystem.outboardOANode();
  ASSERT_TRUE(oaNode);
  EXPECT_FALSE(standaloneCoil.addToNode(*oaNode));
  Node orphanNode(model);
  EXPECT_FALSE(standaloneCoil.addToNode(orphanNode));
  EXPECT_FALSE(standaloneCoil.airLoopHVAC());
}
