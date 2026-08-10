/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AvailabilityManager/AvailabilityManagerLowTemperatureTurnOn.hpp"
#include "../AvailabilityManager/AvailabilityManagerLowTemperatureTurnOn_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AvailabilityManagerLowTemperatureTurnOn_DefaultConstructor) {
  Model model;
  AvailabilityManagerLowTemperatureTurnOn availabilityManager(model);

  EXPECT_EQ(AvailabilityManagerLowTemperatureTurnOn::iddObjectType(), availabilityManager.iddObject().type());
  EXPECT_FALSE(availabilityManager.nameString().empty());
}

TEST_F(EPModelFixture, AvailabilityManagerLowTemperatureTurnOn_ScalarAccessors_RoundTrip) {
  Model model;
  AvailabilityManagerLowTemperatureTurnOn availabilityManager(model);

  EXPECT_DOUBLE_EQ(30.0, availabilityManager.temperature());
  EXPECT_TRUE(availabilityManager.setTemperature(41.75));
  EXPECT_DOUBLE_EQ(41.75, availabilityManager.temperature());
}

TEST_F(EPModelFixture, AvailabilityManagerLowTemperatureTurnOn_PlantLoopSensorLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-low-temperature-availability-sensor.idf");

  Model model;
  PlantLoop plantLoop(model);
  AvailabilityManagerLowTemperatureTurnOn availabilityManager(model);
  ASSERT_TRUE(plantLoop.setName("Sensor Availability Plant Loop"));
  ASSERT_TRUE(availabilityManager.setName("Low Temperature Sensor Manager"));
  ASSERT_TRUE(availabilityManager.setSensorNode(plantLoop.supplyOutletNode()));
  ASSERT_TRUE(availabilityManager.setTemperature(12.5));
  ASSERT_TRUE(plantLoop.addAvailabilityManager(availabilityManager));
  ASSERT_TRUE(availabilityManager.loop());
  EXPECT_EQ(plantLoop, *availabilityManager.loop());
  ASSERT_TRUE(availabilityManager.sensorNode());
  EXPECT_EQ(plantLoop.supplyOutletNode(), *availabilityManager.sensorNode());
  ASSERT_EQ(1u, plantLoop.availabilityManagers().size());
  EXPECT_EQ(availabilityManager, plantLoop.availabilityManagers().front());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Sensor Availability Plant Loop");
  auto loadedAvailabilityManager =
    loadedModel->getConcreteModelObjectByName<AvailabilityManagerLowTemperatureTurnOn>("Low Temperature Sensor Manager");
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedAvailabilityManager);
  ASSERT_TRUE(loadedAvailabilityManager->loop());
  EXPECT_EQ(*loadedPlantLoop, *loadedAvailabilityManager->loop());
  ASSERT_EQ(1u, loadedPlantLoop->availabilityManagers().size());
  EXPECT_EQ(*loadedAvailabilityManager, loadedPlantLoop->availabilityManagers().front());
  ASSERT_TRUE(loadedAvailabilityManager->sensorNode());
  EXPECT_EQ(loadedPlantLoop->supplyOutletNode(), *loadedAvailabilityManager->sensorNode());
  EXPECT_DOUBLE_EQ(12.5, loadedAvailabilityManager->temperature());

  loadedAvailabilityManager->resetSensorNode();
  EXPECT_FALSE(loadedAvailabilityManager->sensorNode());
  ASSERT_TRUE(loadedAvailabilityManager->loop());
  EXPECT_EQ(*loadedPlantLoop, *loadedAvailabilityManager->loop());
  ASSERT_EQ(1u, loadedPlantLoop->availabilityManagers().size());
  EXPECT_EQ(*loadedAvailabilityManager, loadedPlantLoop->availabilityManagers().front());
  ASSERT_TRUE(loadedAvailabilityManager->setSensorNode(loadedPlantLoop->supplyInletNode()));
  ASSERT_TRUE(loadedAvailabilityManager->sensorNode());
  EXPECT_EQ(loadedPlantLoop->supplyInletNode(), *loadedAvailabilityManager->sensorNode());

  const auto managerHandle = loadedAvailabilityManager->handle();
  const auto supplyInletHandle = loadedPlantLoop->supplyInletNode().handle();
  const auto supplyOutletHandle = loadedPlantLoop->supplyOutletNode().handle();
  ASSERT_TRUE(loadedPlantLoop->removeAvailabilityManager(*loadedAvailabilityManager));
  EXPECT_TRUE(loadedPlantLoop->availabilityManagers().empty());
  EXPECT_FALSE(loadedAvailabilityManager->loop());
  ASSERT_TRUE(loadedAvailabilityManager->sensorNode());
  EXPECT_EQ(supplyInletHandle, loadedAvailabilityManager->sensorNode()->handle());
  EXPECT_TRUE(loadedModel->getObject(managerHandle));
  EXPECT_FALSE(loadedAvailabilityManager->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(managerHandle));
  EXPECT_TRUE(loadedModel->getObject(supplyInletHandle));
  EXPECT_TRUE(loadedModel->getObject(supplyOutletHandle));
  EXPECT_TRUE(loadedModel->getObject(loadedPlantLoop->handle()));
  EXPECT_TRUE(std::ranges::none_of(loadedPlantLoop->supplyInletNode().sources(),
                                   [&managerHandle](const auto& source) { return source.handle() == managerHandle; }));

  openstudio::filesystem::remove(idfPath);
}
