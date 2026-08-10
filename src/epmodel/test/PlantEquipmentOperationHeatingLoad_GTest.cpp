/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/HVACComponent.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../Model.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/BoilerHotWater.hpp"
#include "../StraightComponent/BoilerHotWater_Impl.hpp"

#include <utilities/core/Filesystem.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationHeatingLoad_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationHeatingLoad heatingLoad(model);
  EXPECT_EQ(PlantEquipmentOperationHeatingLoad::iddObjectType(), heatingLoad.iddObject().type());
  EXPECT_FALSE(heatingLoad.nameString().empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationHeatingLoad_RangeEquipmentApi) {
  Model model;
  PlantEquipmentOperationHeatingLoad heatingLoad(model);
  BoilerHotWater boiler(model);
  BoilerHotWater boiler2(model);

  EXPECT_DOUBLE_EQ(1e9, heatingLoad.maximumUpperLimit());
  EXPECT_DOUBLE_EQ(0.0, heatingLoad.minimumLowerLimit());
  ASSERT_EQ(1u, heatingLoad.loadRangeUpperLimits().size());
  EXPECT_TRUE(heatingLoad.equipment(heatingLoad.maximumUpperLimit()).empty());

  EXPECT_TRUE(heatingLoad.addEquipment(boiler));
  EXPECT_FALSE(heatingLoad.addEquipment(boiler));
  ASSERT_EQ(1u, heatingLoad.equipment(heatingLoad.maximumUpperLimit()).size());
  EXPECT_EQ(boiler.cast<HVACComponent>(), heatingLoad.equipment(heatingLoad.maximumUpperLimit()).front());

  EXPECT_TRUE(heatingLoad.addLoadRange(1000.0, {boiler2}));
  auto upperLimits = heatingLoad.loadRangeUpperLimits();
  ASSERT_EQ(2u, upperLimits.size());
  EXPECT_DOUBLE_EQ(1000.0, upperLimits.front());
  ASSERT_EQ(1u, heatingLoad.equipment(1000.0).size());
  EXPECT_EQ(boiler2.cast<HVACComponent>(), heatingLoad.equipment(1000.0).front());

  auto removed = heatingLoad.removeLoadRange(1000.0);
  ASSERT_EQ(1u, removed.size());
  EXPECT_EQ(boiler2.cast<HVACComponent>(), removed.front());
  EXPECT_EQ(1u, heatingLoad.loadRangeUpperLimits().size());
}

TEST_F(EPModelFixture, PlantEquipmentOperationHeatingLoad_MembershipAndBranchLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-plant-operation-membership-lifecycle.idf");

  Model model;
  PlantLoop plantLoop(model);
  BoilerHotWater boiler(model);
  PlantEquipmentOperationHeatingLoad heatingOperation(model);
  ScheduleConstant initialSchedule(model);
  ASSERT_TRUE(plantLoop.setName("Operation Membership Plant Loop"));
  ASSERT_TRUE(boiler.setName("Operation Membership Boiler"));
  ASSERT_TRUE(heatingOperation.setName("Heating Operation Scheme"));
  ASSERT_TRUE(initialSchedule.setName("Initial Heating Operation Schedule"));
  ASSERT_TRUE(initialSchedule.setValue(1.0));

  ASSERT_TRUE(plantLoop.addSupplyBranchForComponent(boiler));
  ASSERT_TRUE(heatingOperation.addEquipment(boiler));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoad(heatingOperation));
  ASSERT_TRUE(plantLoop.setPlantEquipmentOperationHeatingLoadSchedule(initialSchedule));

  ASSERT_TRUE(plantLoop.plantEquipmentOperationHeatingLoad());
  ASSERT_TRUE(plantLoop.plantEquipmentOperationHeatingLoadSchedule());
  EXPECT_EQ(heatingOperation, *plantLoop.plantEquipmentOperationHeatingLoad());
  EXPECT_EQ(initialSchedule, *plantLoop.plantEquipmentOperationHeatingLoadSchedule());
  ASSERT_EQ(1u, heatingOperation.equipment(heatingOperation.maximumUpperLimit()).size());
  EXPECT_EQ(boiler.handle(), heatingOperation.equipment(heatingOperation.maximumUpperLimit()).front().handle());
  ASSERT_TRUE(boiler.plantLoop());
  EXPECT_EQ(plantLoop, *boiler.plantLoop());
  EXPECT_TRUE(plantLoop.supplyComponent(boiler.handle()));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Operation Membership Plant Loop");
  auto loadedBoiler = loadedModel->getConcreteModelObjectByName<BoilerHotWater>("Operation Membership Boiler");
  auto loadedHeatingOperation = loadedModel->getConcreteModelObjectByName<PlantEquipmentOperationHeatingLoad>("Heating Operation Scheme");
  auto loadedInitialSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Initial Heating Operation Schedule");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedBoiler);
  ASSERT_TRUE(loadedHeatingOperation);
  ASSERT_TRUE(loadedInitialSchedule);

  ASSERT_TRUE(loadedPlantLoop->plantEquipmentOperationHeatingLoad());
  ASSERT_TRUE(loadedPlantLoop->plantEquipmentOperationHeatingLoadSchedule());
  EXPECT_EQ(*loadedHeatingOperation, *loadedPlantLoop->plantEquipmentOperationHeatingLoad());
  EXPECT_EQ(*loadedInitialSchedule, *loadedPlantLoop->plantEquipmentOperationHeatingLoadSchedule());
  ASSERT_EQ(1u, loadedHeatingOperation->equipment(loadedHeatingOperation->maximumUpperLimit()).size());
  EXPECT_EQ(loadedBoiler->handle(), loadedHeatingOperation->equipment(loadedHeatingOperation->maximumUpperLimit()).front().handle());
  ASSERT_TRUE(loadedBoiler->plantLoop());
  EXPECT_EQ(*loadedPlantLoop, *loadedBoiler->plantLoop());
  EXPECT_TRUE(loadedPlantLoop->supplyComponent(loadedBoiler->handle()));

  ScheduleConstant postLoadSchedule(*loadedModel);
  ASSERT_TRUE(postLoadSchedule.setName("Post-load Heating Operation Schedule"));
  ASSERT_TRUE(postLoadSchedule.setValue(0.5));
  ASSERT_TRUE(loadedPlantLoop->setPlantEquipmentOperationHeatingLoadSchedule(postLoadSchedule));
  ASSERT_TRUE(loadedPlantLoop->plantEquipmentOperationHeatingLoadSchedule());
  EXPECT_EQ(postLoadSchedule, *loadedPlantLoop->plantEquipmentOperationHeatingLoadSchedule());

  EXPECT_TRUE(loadedHeatingOperation->removeEquipment(*loadedBoiler));
  EXPECT_TRUE(loadedHeatingOperation->equipment(loadedHeatingOperation->maximumUpperLimit()).empty());
  EXPECT_TRUE(loadedPlantLoop->supplyComponent(loadedBoiler->handle()));
  ASSERT_TRUE(loadedBoiler->plantLoop());
  EXPECT_TRUE(loadedHeatingOperation->addEquipment(*loadedBoiler));
  EXPECT_FALSE(loadedHeatingOperation->addEquipment(*loadedBoiler));
  ASSERT_EQ(1u, loadedHeatingOperation->equipment(loadedHeatingOperation->maximumUpperLimit()).size());

  const auto boilerHandle = loadedBoiler->handle();
  const auto plantLoopHandle = loadedPlantLoop->handle();
  EXPECT_FALSE(loadedBoiler->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(boilerHandle));
  EXPECT_TRUE(loadedHeatingOperation->equipment(loadedHeatingOperation->maximumUpperLimit()).empty());
  EXPECT_FALSE(loadedPlantLoop->supplyComponent(boilerHandle));
  EXPECT_TRUE(loadedModel->getObject(plantLoopHandle));

  EXPECT_FALSE(loadedHeatingOperation->remove().empty());
  EXPECT_FALSE(loadedPlantLoop->plantEquipmentOperationHeatingLoad());
  ASSERT_TRUE(loadedPlantLoop->plantEquipmentOperationHeatingLoadSchedule());
  EXPECT_EQ(postLoadSchedule, *loadedPlantLoop->plantEquipmentOperationHeatingLoadSchedule());
  EXPECT_TRUE(loadedModel->getObject(loadedInitialSchedule->handle()));
  EXPECT_TRUE(loadedModel->getObject(postLoadSchedule.handle()));
  EXPECT_TRUE(loadedModel->getObject(plantLoopHandle));

  openstudio::filesystem::remove(idfPath);
}
