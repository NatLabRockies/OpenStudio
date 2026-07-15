/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/CoilWaterHeatingAirToWaterHeatPumpWrapped.hpp"
#include "../StraightComponent/StraightComponent.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/Coil_WaterHeating_AirToWaterHeatPump_Wrapped_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpWrapped_DefaultConstructor) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpWrapped coil(model);
  EXPECT_EQ(CoilWaterHeatingAirToWaterHeatPumpWrapped::iddObjectType(), coil.iddObject().type());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coil.availabilitySchedule().handle());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpWrapped_StraightComponentPortsWithoutLoopPlacement) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpWrapped coil(model);
  Node node(model);

  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirInletNodeName, coil.inletPort());
  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirOutletNodeName, coil.outletPort());
  EXPECT_FALSE(coil.addToNode(node));
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpWrapped_ScalarAccessors_RoundTrip) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpWrapped coil(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(1.0));

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  ASSERT_TRUE(coil.getTarget(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::AvailabilityScheduleName));
  EXPECT_EQ(availability.handle(),
            coil.getTarget(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::AvailabilityScheduleName)->handle());

  EXPECT_TRUE(coil.setRatedHeatingCapacity(4000.0));
  EXPECT_DOUBLE_EQ(4000.0, coil.ratedHeatingCapacity());

  EXPECT_TRUE(coil.isRatedCOPDefaulted());
  EXPECT_DOUBLE_EQ(3.2, coil.ratedCOP());
  EXPECT_TRUE(coil.setRatedCOP(3.6));
  EXPECT_DOUBLE_EQ(3.6, coil.ratedCOP());
  EXPECT_FALSE(coil.isRatedCOPDefaulted());
  coil.resetRatedCOP();
  EXPECT_TRUE(coil.isRatedCOPDefaulted());

  EXPECT_TRUE(coil.isRatedSensibleHeatRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.85, coil.ratedSensibleHeatRatio());
  EXPECT_TRUE(coil.setRatedSensibleHeatRatio(0.9));
  EXPECT_DOUBLE_EQ(0.9, coil.ratedSensibleHeatRatio());
  coil.resetRatedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedSensibleHeatRatioDefaulted());

  EXPECT_TRUE(coil.isRatedEvaporatorInletAirDryBulbTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(19.7, coil.ratedEvaporatorInletAirDryBulbTemperature());
  EXPECT_TRUE(coil.setRatedEvaporatorInletAirDryBulbTemperature(21.1));
  EXPECT_DOUBLE_EQ(21.1, coil.ratedEvaporatorInletAirDryBulbTemperature());
  coil.resetRatedEvaporatorInletAirDryBulbTemperature();
  EXPECT_TRUE(coil.isRatedEvaporatorInletAirDryBulbTemperatureDefaulted());

  EXPECT_TRUE(coil.isRatedEvaporatorInletAirWetBulbTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(13.5, coil.ratedEvaporatorInletAirWetBulbTemperature());
  EXPECT_TRUE(coil.setRatedEvaporatorInletAirWetBulbTemperature(14.2));
  EXPECT_DOUBLE_EQ(14.2, coil.ratedEvaporatorInletAirWetBulbTemperature());
  coil.resetRatedEvaporatorInletAirWetBulbTemperature();
  EXPECT_TRUE(coil.isRatedEvaporatorInletAirWetBulbTemperatureDefaulted());

  EXPECT_TRUE(coil.isRatedCondenserWaterTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(57.5, coil.ratedCondenserWaterTemperature());
  EXPECT_TRUE(coil.setRatedCondenserWaterTemperature(52.0));
  EXPECT_DOUBLE_EQ(52.0, coil.ratedCondenserWaterTemperature());
  coil.resetRatedCondenserWaterTemperature();
  EXPECT_TRUE(coil.isRatedCondenserWaterTemperatureDefaulted());

  EXPECT_FALSE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_FALSE(coil.isRatedEvaporatorAirFlowRateAutocalculated());
  EXPECT_TRUE(coil.setRatedEvaporatorAirFlowRate(1.0));
  ASSERT_TRUE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(1.0, coil.ratedEvaporatorAirFlowRate().get());
  coil.autocalculateRatedEvaporatorAirFlowRate();
  EXPECT_TRUE(coil.isRatedEvaporatorAirFlowRateAutocalculated());
  coil.resetRatedEvaporatorAirFlowRate();
  EXPECT_FALSE(coil.ratedEvaporatorAirFlowRate());

  EXPECT_TRUE(coil.isEvaporatorFanPowerIncludedinRatedCOPDefaulted());
  EXPECT_TRUE(coil.evaporatorFanPowerIncludedinRatedCOP());
  EXPECT_TRUE(coil.setEvaporatorFanPowerIncludedinRatedCOP(false));
  EXPECT_FALSE(coil.evaporatorFanPowerIncludedinRatedCOP());
  coil.resetEvaporatorFanPowerIncludedinRatedCOP();
  EXPECT_TRUE(coil.isEvaporatorFanPowerIncludedinRatedCOPDefaulted());

  EXPECT_TRUE(coil.isCrankcaseHeaterCapacityDefaulted());
  EXPECT_DOUBLE_EQ(0.0, coil.crankcaseHeaterCapacity());
  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(105.0));
  EXPECT_DOUBLE_EQ(105.0, coil.crankcaseHeaterCapacity());
  coil.resetCrankcaseHeaterCapacity();
  EXPECT_TRUE(coil.isCrankcaseHeaterCapacityDefaulted());

  EXPECT_TRUE(coil.isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted());
  EXPECT_DOUBLE_EQ(10.0, coil.maximumAmbientTemperatureforCrankcaseHeaterOperation());
  EXPECT_TRUE(coil.setMaximumAmbientTemperatureforCrankcaseHeaterOperation(9.0));
  EXPECT_DOUBLE_EQ(9.0, coil.maximumAmbientTemperatureforCrankcaseHeaterOperation());
  coil.resetMaximumAmbientTemperatureforCrankcaseHeaterOperation();
  EXPECT_TRUE(coil.isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted());

  const auto temperatureTypeChoices = CoilWaterHeatingAirToWaterHeatPumpWrapped::evaporatorAirTemperatureTypeforCurveObjectsValues();
  EXPECT_FALSE(temperatureTypeChoices.empty());
  EXPECT_TRUE(std::find(temperatureTypeChoices.begin(), temperatureTypeChoices.end(), "WetBulbTemperature") != temperatureTypeChoices.end());

  EXPECT_TRUE(coil.isEvaporatorAirTemperatureTypeforCurveObjectsDefaulted());
  EXPECT_EQ("WetBulbTemperature", coil.evaporatorAirTemperatureTypeforCurveObjects());
  EXPECT_TRUE(coil.setEvaporatorAirTemperatureTypeforCurveObjects("DryBulbTemperature"));
  EXPECT_EQ("DryBulbTemperature", coil.evaporatorAirTemperatureTypeforCurveObjects());
  coil.resetEvaporatorAirTemperatureTypeforCurveObjects();
  EXPECT_TRUE(coil.isEvaporatorAirTemperatureTypeforCurveObjectsDefaulted());
}
