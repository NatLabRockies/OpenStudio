/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Schedule/Schedule.hpp"
#include "../WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPump.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/Coil_WaterHeating_AirToWaterHeatPump_Pumped_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPump_DefaultConstructor) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPump coil(model);
  EXPECT_EQ(CoilWaterHeatingAirToWaterHeatPump::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coil.availabilitySchedule().handle());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Curve_Biquadratic),
            coil.heatingCapacityFunctionofTemperatureCurve().iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Curve_Quadratic),
            coil.heatingCapacityFunctionofAirFlowFractionCurve().iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Curve_Quadratic),
            coil.heatingCapacityFunctionofWaterFlowFractionCurve().iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Curve_Biquadratic),
            coil.heatingCOPFunctionofTemperatureCurve().iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Curve_Quadratic),
            coil.heatingCOPFunctionofAirFlowFractionCurve().iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Curve_Quadratic),
            coil.heatingCOPFunctionofWaterFlowFractionCurve().iddObject().type());
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Curve_Quadratic), coil.partLoadFractionCorrelationCurve().iddObject().type());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPump_WaterToAirPortsWithoutLoopPlacement) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPump coil(model);
  Node node(model);

  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirInletNodeName, coil.airInletPort());
  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirOutletNodeName, coil.airOutletPort());
  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterInletNodeName, coil.waterInletPort());
  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterOutletNodeName, coil.waterOutletPort());
  EXPECT_FALSE(coil.addToNode(node));
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPump_ScalarAccessors_RoundTrip) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPump coil(model);
  Schedule schedule = model.alwaysOnDiscreteSchedule();

  EXPECT_TRUE(coil.setAvailabilitySchedule(schedule));
  EXPECT_EQ(schedule.handle(), coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setRatedHeatingCapacity(4200.0));
  EXPECT_DOUBLE_EQ(4200.0, coil.ratedHeatingCapacity());

  EXPECT_TRUE(coil.setRatedCOP(3.4));
  EXPECT_DOUBLE_EQ(3.4, coil.ratedCOP());

  EXPECT_TRUE(coil.setRatedSensibleHeatRatio(0.88));
  EXPECT_DOUBLE_EQ(0.88, coil.ratedSensibleHeatRatio());

  EXPECT_TRUE(coil.setRatedEvaporatorInletAirDryBulbTemperature(29.44));
  EXPECT_DOUBLE_EQ(29.44, coil.ratedEvaporatorInletAirDryBulbTemperature());

  EXPECT_TRUE(coil.setRatedEvaporatorInletAirWetBulbTemperature(22.22));
  EXPECT_DOUBLE_EQ(22.22, coil.ratedEvaporatorInletAirWetBulbTemperature());

  EXPECT_TRUE(coil.setRatedCondenserInletWaterTemperature(55.72));
  EXPECT_DOUBLE_EQ(55.72, coil.ratedCondenserInletWaterTemperature());

  EXPECT_TRUE(coil.setRatedEvaporatorAirFlowRate(0.52));
  ASSERT_TRUE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.52, coil.ratedEvaporatorAirFlowRate().get());
  coil.autosizeRatedEvaporatorAirFlowRate();
  EXPECT_TRUE(coil.isRatedEvaporatorAirFlowRateAutosized());
  EXPECT_FALSE(coil.autosizedRatedEvaporatorAirFlowRate());

  EXPECT_TRUE(coil.setRatedCondenserWaterFlowRate(0.12));
  ASSERT_TRUE(coil.ratedCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.12, coil.ratedCondenserWaterFlowRate().get());
  coil.autosizeRatedCondenserWaterFlowRate();
  EXPECT_TRUE(coil.isRatedCondenserWaterFlowRateAutosized());
  EXPECT_FALSE(coil.autosizedRatedCondenserWaterFlowRate());

  EXPECT_TRUE(coil.setEvaporatorFanPowerIncludedinRatedCOP(true));
  EXPECT_TRUE(coil.evaporatorFanPowerIncludedinRatedCOP());

  EXPECT_TRUE(coil.setCondenserPumpPowerIncludedinRatedCOP(false));
  EXPECT_FALSE(coil.condenserPumpPowerIncludedinRatedCOP());

  EXPECT_TRUE(coil.setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP(false));
  EXPECT_FALSE(coil.condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP());

  EXPECT_TRUE(coil.setCondenserWaterPumpPower(300.0));
  EXPECT_DOUBLE_EQ(300.0, coil.condenserWaterPumpPower());

  EXPECT_TRUE(coil.setFractionofCondenserPumpHeattoWater(0.2));
  EXPECT_DOUBLE_EQ(0.2, coil.fractionofCondenserPumpHeattoWater());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(100.0));
  EXPECT_DOUBLE_EQ(100.0, coil.crankcaseHeaterCapacity());

  CurveQuadratic crankcaseCurve(model);
  EXPECT_TRUE(crankcaseCurve.setCoefficient1Constant(1.0));
  EXPECT_TRUE(crankcaseCurve.setCoefficient2x(0.1));
  EXPECT_TRUE(crankcaseCurve.setCoefficient3xPOW2(0.01));
  EXPECT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseCurve));
  ASSERT_TRUE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(crankcaseCurve.handle(), coil.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());
  coil.resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());

  EXPECT_TRUE(coil.setMaximumAmbientTemperatureforCrankcaseHeaterOperation(10.0));
  EXPECT_DOUBLE_EQ(10.0, coil.maximumAmbientTemperatureforCrankcaseHeaterOperation());

  const auto temperatureTypeChoices = CoilWaterHeatingAirToWaterHeatPump::evaporatorAirTemperatureTypeforCurveObjectsValues();
  EXPECT_FALSE(temperatureTypeChoices.empty());
  EXPECT_TRUE(std::find(temperatureTypeChoices.begin(), temperatureTypeChoices.end(), "WetBulbTemperature") != temperatureTypeChoices.end());

  EXPECT_TRUE(coil.setEvaporatorAirTemperatureTypeforCurveObjects("WetBulbTemperature"));
  EXPECT_EQ("WetBulbTemperature", coil.evaporatorAirTemperatureTypeforCurveObjects());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPump_CurveConstructorAndRelationships) {
  Model model;

  CurveBiquadratic heatingCapacityTemperatureCurve(model);
  CurveQuadratic heatingCapacityAirFlowCurve(model);
  CurveQuadratic heatingCapacityWaterFlowCurve(model);
  CurveBiquadratic heatingCOPTemperatureCurve(model);
  CurveQuadratic heatingCOPAirFlowCurve(model);
  CurveQuadratic heatingCOPWaterFlowCurve(model);
  CurveQuadratic partLoadFractionCurve(model);

  CoilWaterHeatingAirToWaterHeatPump coil(model, heatingCapacityTemperatureCurve, heatingCapacityAirFlowCurve, heatingCapacityWaterFlowCurve,
                                          heatingCOPTemperatureCurve, heatingCOPAirFlowCurve, heatingCOPWaterFlowCurve, partLoadFractionCurve);

  EXPECT_EQ(heatingCapacityTemperatureCurve.handle(), coil.heatingCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(heatingCapacityAirFlowCurve.handle(), coil.heatingCapacityFunctionofAirFlowFractionCurve().handle());
  EXPECT_EQ(heatingCapacityWaterFlowCurve.handle(), coil.heatingCapacityFunctionofWaterFlowFractionCurve().handle());
  EXPECT_EQ(heatingCOPTemperatureCurve.handle(), coil.heatingCOPFunctionofTemperatureCurve().handle());
  EXPECT_EQ(heatingCOPAirFlowCurve.handle(), coil.heatingCOPFunctionofAirFlowFractionCurve().handle());
  EXPECT_EQ(heatingCOPWaterFlowCurve.handle(), coil.heatingCOPFunctionofWaterFlowFractionCurve().handle());
  EXPECT_EQ(partLoadFractionCurve.handle(), coil.partLoadFractionCorrelationCurve().handle());
}
