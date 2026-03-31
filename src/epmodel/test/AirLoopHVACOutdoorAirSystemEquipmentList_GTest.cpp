/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList.hpp"
#include "../ModelObject/AirLoopHVACOutdoorAirSystemEquipmentList_Impl.hpp"
#include "../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../WaterToAirComponent/CoilCoolingWaterToAirHeatPumpEquationFit.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirLoopHVACOutdoorAirSystemEquipmentList_DefaultConstructor) {
  Model model;
  AirLoopHVACOutdoorAirSystemEquipmentList equipmentList(model);
  EXPECT_EQ(AirLoopHVACOutdoorAirSystemEquipmentList::iddObjectType(), equipmentList.iddObject().type());
}

TEST_F(EPModelFixture, AirLoopHVACOutdoorAirSystemEquipmentList_ScalarAccessors_RoundTrip) {
  Model model;
  AirLoopHVACOutdoorAirSystemEquipmentList equipmentList(model);

  EXPECT_TRUE(equipmentList.setName("Main OA Equipment List"));
  EXPECT_EQ("Main OA Equipment List", equipmentList.nameString());
}

TEST_F(EPModelFixture, AirLoopHVACOutdoorAirSystemEquipmentList_AddEquipmentUsesProposedEnergyPlusAllowlist) {
  Model model;
  AirLoopHVACOutdoorAirSystemEquipmentList equipmentList(model);
  auto impl = equipmentList.getImpl<detail::AirLoopHVACOutdoorAirSystemEquipmentList_Impl>();
  ASSERT_TRUE(impl);

  CoilCoolingWater allowed(model);
  CoilCoolingWaterToAirHeatPumpEquationFit rejected(model);

  EXPECT_TRUE(impl->addEquipment(allowed));
  EXPECT_FALSE(impl->addEquipment(rejected));

  const auto equipment = equipmentList.equipment();
  ASSERT_EQ(1u, equipment.size());
  EXPECT_EQ(allowed.handle(), equipment.front().handle());
}
