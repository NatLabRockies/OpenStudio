/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/HVACTemplateSystemVRF.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HVACTemplateSystemVRF_DefaultConstructor) {
  Model model;
  HVACTemplateSystemVRF object(model);
  EXPECT_EQ(HVACTemplateSystemVRF::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, HVACTemplateSystemVRF_ScalarAccessors_RoundTrip) {
  Model model;
  HVACTemplateSystemVRF object(model);

  EXPECT_TRUE(object.setMasterThermostatPriorityControlType("Scheduled"));
  EXPECT_EQ("Scheduled", object.masterThermostatPriorityControlType());

  EXPECT_TRUE(object.setHeatPumpWasteHeatRecovery(true));
  EXPECT_TRUE(object.heatPumpWasteHeatRecovery());

  EXPECT_TRUE(object.setNumberofCompressors(3));
  EXPECT_EQ(3, object.numberofCompressors());

  EXPECT_TRUE(object.setGrossRatedTotalCoolingCapacity(12000.0));
  ASSERT_TRUE(object.grossRatedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12000.0, object.grossRatedTotalCoolingCapacity().get());
  EXPECT_FALSE(object.isGrossRatedTotalCoolingCapacityAutosized());
  object.autosizeGrossRatedTotalCoolingCapacity();
  EXPECT_TRUE(object.isGrossRatedTotalCoolingCapacityAutosized());
  object.resetGrossRatedTotalCoolingCapacity();
  EXPECT_TRUE(object.isGrossRatedTotalCoolingCapacityDefaulted());

  EXPECT_TRUE(object.setEvaporativeCondenserPumpRatedPowerConsumption(350.0));
  ASSERT_TRUE(object.evaporativeCondenserPumpRatedPowerConsumption());
  EXPECT_DOUBLE_EQ(350.0, object.evaporativeCondenserPumpRatedPowerConsumption().get());
  object.autosizeEvaporativeCondenserPumpRatedPowerConsumption();
  EXPECT_TRUE(object.isEvaporativeCondenserPumpRatedPowerConsumptionAutosized());

  EXPECT_FALSE(object.setDefrostControl("InvalidChoice"));
  EXPECT_FALSE(object.setGrossRatedCoolingCOP(0.0));

  EXPECT_GE(HVACTemplateSystemVRF::masterThermostatPriorityControlTypeValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemVRF::defrostStrategyValues().size(), 1u);
  EXPECT_GE(HVACTemplateSystemVRF::condenserTypeValues().size(), 1u);
}
