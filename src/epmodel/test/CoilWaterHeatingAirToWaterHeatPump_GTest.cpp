/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../Curve/Curve.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Splitter/Splitter.hpp"
#include "../WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPump.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/Coil_WaterHeating_AirToWaterHeatPump_Pumped_FieldEnums.hxx>
#include <utilities/idf/Handle.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPump_DefaultConstructor) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPump coil(model);
  EXPECT_EQ(CoilWaterHeatingAirToWaterHeatPump::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coil.availabilitySchedule().handle());
  EXPECT_DOUBLE_EQ(4000.0, coil.ratedHeatingCapacity());
  EXPECT_DOUBLE_EQ(3.2, coil.ratedCOP());
  EXPECT_DOUBLE_EQ(0.6956, coil.ratedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(29.44, coil.ratedEvaporatorInletAirDryBulbTemperature());
  EXPECT_DOUBLE_EQ(22.22, coil.ratedEvaporatorInletAirWetBulbTemperature());
  EXPECT_DOUBLE_EQ(55.72, coil.ratedCondenserInletWaterTemperature());
  EXPECT_TRUE(coil.isRatedEvaporatorAirFlowRateAutosized());
  EXPECT_TRUE(coil.isRatedCondenserWaterFlowRateAutosized());
  EXPECT_FALSE(coil.evaporatorFanPowerIncludedinRatedCOP());
  EXPECT_FALSE(coil.condenserPumpPowerIncludedinRatedCOP());
  EXPECT_FALSE(coil.condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP());
  EXPECT_DOUBLE_EQ(150.0, coil.condenserWaterPumpPower());
  EXPECT_DOUBLE_EQ(0.1, coil.fractionofCondenserPumpHeattoWater());
  EXPECT_DOUBLE_EQ(100.0, coil.crankcaseHeaterCapacity());
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_DOUBLE_EQ(5.0, coil.maximumAmbientTemperatureforCrankcaseHeaterOperation());
  EXPECT_EQ("WetBulbTemperature", coil.evaporatorAirTemperatureTypeforCurveObjects());

  auto heatingCapacityTemperatureCurve = coil.heatingCapacityFunctionofTemperatureCurve().cast<CurveBiquadratic>();
  EXPECT_DOUBLE_EQ(0.369827, heatingCapacityTemperatureCurve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.043341, heatingCapacityTemperatureCurve.coefficient2x());
  EXPECT_DOUBLE_EQ(-0.00023, heatingCapacityTemperatureCurve.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.000466, heatingCapacityTemperatureCurve.coefficient4y());
  EXPECT_DOUBLE_EQ(0.000026, heatingCapacityTemperatureCurve.coefficient5yPOW2());
  EXPECT_DOUBLE_EQ(-0.00027, heatingCapacityTemperatureCurve.coefficient6xTIMESY());
  EXPECT_DOUBLE_EQ(0.0, heatingCapacityTemperatureCurve.minimumValueofx());
  EXPECT_DOUBLE_EQ(40.0, heatingCapacityTemperatureCurve.maximumValueofx());
  EXPECT_DOUBLE_EQ(20.0, heatingCapacityTemperatureCurve.minimumValueofy());
  EXPECT_DOUBLE_EQ(90.0, heatingCapacityTemperatureCurve.maximumValueofy());
  EXPECT_EQ("Temperature", heatingCapacityTemperatureCurve.inputUnitTypeforX());
  EXPECT_EQ("Temperature", heatingCapacityTemperatureCurve.inputUnitTypeforY());
  EXPECT_EQ("Dimensionless", heatingCapacityTemperatureCurve.outputUnitType());

  auto heatingCapacityAirFlowCurve = coil.heatingCapacityFunctionofAirFlowFractionCurve().cast<CurveQuadratic>();
  EXPECT_DOUBLE_EQ(1.0, heatingCapacityAirFlowCurve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.0, heatingCapacityAirFlowCurve.coefficient2x());
  EXPECT_DOUBLE_EQ(0.0, heatingCapacityAirFlowCurve.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, heatingCapacityAirFlowCurve.minimumValueofx());
  EXPECT_DOUBLE_EQ(1.0, heatingCapacityAirFlowCurve.maximumValueofx());

  auto heatingCapacityWaterFlowCurve = coil.heatingCapacityFunctionofWaterFlowFractionCurve().cast<CurveQuadratic>();
  EXPECT_DOUBLE_EQ(1.0, heatingCapacityWaterFlowCurve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.0, heatingCapacityWaterFlowCurve.coefficient2x());
  EXPECT_DOUBLE_EQ(0.0, heatingCapacityWaterFlowCurve.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, heatingCapacityWaterFlowCurve.minimumValueofx());
  EXPECT_DOUBLE_EQ(1.0, heatingCapacityWaterFlowCurve.maximumValueofx());

  auto heatingCOPTemperatureCurve = coil.heatingCOPFunctionofTemperatureCurve().cast<CurveBiquadratic>();
  EXPECT_DOUBLE_EQ(1.19713, heatingCOPTemperatureCurve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.077849, heatingCOPTemperatureCurve.coefficient2x());
  EXPECT_DOUBLE_EQ(-0.0000016, heatingCOPTemperatureCurve.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(-0.02675, heatingCOPTemperatureCurve.coefficient4y());
  EXPECT_DOUBLE_EQ(0.000296, heatingCOPTemperatureCurve.coefficient5yPOW2());
  EXPECT_DOUBLE_EQ(-0.00112, heatingCOPTemperatureCurve.coefficient6xTIMESY());
  EXPECT_DOUBLE_EQ(0.0, heatingCOPTemperatureCurve.minimumValueofx());
  EXPECT_DOUBLE_EQ(40.0, heatingCOPTemperatureCurve.maximumValueofx());
  EXPECT_DOUBLE_EQ(20.0, heatingCOPTemperatureCurve.minimumValueofy());
  EXPECT_DOUBLE_EQ(90.0, heatingCOPTemperatureCurve.maximumValueofy());
  EXPECT_EQ("Temperature", heatingCOPTemperatureCurve.inputUnitTypeforX());
  EXPECT_EQ("Temperature", heatingCOPTemperatureCurve.inputUnitTypeforY());
  EXPECT_EQ("Dimensionless", heatingCOPTemperatureCurve.outputUnitType());

  auto heatingCOPAirFlowCurve = coil.heatingCOPFunctionofAirFlowFractionCurve().cast<CurveQuadratic>();
  EXPECT_DOUBLE_EQ(1.0, heatingCOPAirFlowCurve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.0, heatingCOPAirFlowCurve.coefficient2x());
  EXPECT_DOUBLE_EQ(0.0, heatingCOPAirFlowCurve.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, heatingCOPAirFlowCurve.minimumValueofx());
  EXPECT_DOUBLE_EQ(1.0, heatingCOPAirFlowCurve.maximumValueofx());

  auto heatingCOPWaterFlowCurve = coil.heatingCOPFunctionofWaterFlowFractionCurve().cast<CurveQuadratic>();
  EXPECT_DOUBLE_EQ(1.0, heatingCOPWaterFlowCurve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.0, heatingCOPWaterFlowCurve.coefficient2x());
  EXPECT_DOUBLE_EQ(0.0, heatingCOPWaterFlowCurve.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, heatingCOPWaterFlowCurve.minimumValueofx());
  EXPECT_DOUBLE_EQ(1.0, heatingCOPWaterFlowCurve.maximumValueofx());

  auto partLoadFractionCurve = coil.partLoadFractionCorrelationCurve().cast<CurveQuadratic>();
  EXPECT_DOUBLE_EQ(0.75, partLoadFractionCurve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.25, partLoadFractionCurve.coefficient2x());
  EXPECT_DOUBLE_EQ(0.0, partLoadFractionCurve.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, partLoadFractionCurve.minimumValueofx());
  EXPECT_DOUBLE_EQ(1.0, partLoadFractionCurve.maximumValueofx());

  auto children = coil.children();
  ASSERT_EQ(7u, children.size());
  EXPECT_EQ(heatingCapacityTemperatureCurve.handle(), children[0].handle());
  EXPECT_EQ(heatingCapacityAirFlowCurve.handle(), children[1].handle());
  EXPECT_EQ(heatingCapacityWaterFlowCurve.handle(), children[2].handle());
  EXPECT_EQ(heatingCOPTemperatureCurve.handle(), children[3].handle());
  EXPECT_EQ(heatingCOPAirFlowCurve.handle(), children[4].handle());
  EXPECT_EQ(heatingCOPWaterFlowCurve.handle(), children[5].handle());
  EXPECT_EQ(partLoadFractionCurve.handle(), children[6].handle());

  CurveQuadratic crankcaseCurve(model);
  ASSERT_TRUE(crankcaseCurve.setCoefficient1Constant(1.0));
  ASSERT_TRUE(crankcaseCurve.setCoefficient2x(0.1));
  ASSERT_TRUE(crankcaseCurve.setCoefficient3xPOW2(0.01));
  ASSERT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseCurve));

  children = coil.children();
  ASSERT_EQ(8u, children.size());
  EXPECT_EQ(crankcaseCurve.handle(), children.back().handle());

  coil.resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  EXPECT_EQ(7u, coil.children().size());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPump_WaterToAirPortsWithoutLoopPlacement) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPump coil(model);
  Node node(model);
  Splitter splitter(model);

  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirInletNodeName, coil.airInletPort());
  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirOutletNodeName, coil.airOutletPort());
  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterInletNodeName, coil.waterInletPort());
  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterOutletNodeName, coil.waterOutletPort());
  EXPECT_FALSE(coil.addToNode(node));
  EXPECT_FALSE(coil.addToSplitter(splitter));
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
  EXPECT_FALSE(coil.isRatedEvaporatorAirFlowRateAutosized());
  ASSERT_TRUE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.52, coil.ratedEvaporatorAirFlowRate().get());
  coil.autosizeRatedEvaporatorAirFlowRate();
  EXPECT_TRUE(coil.isRatedEvaporatorAirFlowRateAutosized());
  EXPECT_EQ(boost::none, coil.autosizedRatedEvaporatorAirFlowRate());
  EXPECT_TRUE(coil.setRatedEvaporatorAirFlowRate(0.53));
  EXPECT_FALSE(coil.isRatedEvaporatorAirFlowRateAutosized());
  ASSERT_TRUE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.53, coil.ratedEvaporatorAirFlowRate().get());

  EXPECT_TRUE(coil.setRatedCondenserWaterFlowRate(0.12));
  EXPECT_FALSE(coil.isRatedCondenserWaterFlowRateAutosized());
  ASSERT_TRUE(coil.ratedCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.12, coil.ratedCondenserWaterFlowRate().get());
  coil.autosizeRatedCondenserWaterFlowRate();
  EXPECT_TRUE(coil.isRatedCondenserWaterFlowRateAutosized());
  EXPECT_EQ(boost::none, coil.autosizedRatedCondenserWaterFlowRate());
  EXPECT_TRUE(coil.setRatedCondenserWaterFlowRate(0.13));
  EXPECT_FALSE(coil.isRatedCondenserWaterFlowRateAutosized());
  ASSERT_TRUE(coil.ratedCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.13, coil.ratedCondenserWaterFlowRate().get());

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

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPump_AvailabilityScheduleGetterRepairsMissingRequiredReference) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPump coil(model);

  ASSERT_TRUE(
    coil.setPointer(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(
    coil.getModelObjectTarget<Schedule>(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::AvailabilityScheduleName));

  const auto schedule = coil.availabilitySchedule();
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), schedule);
  const auto repairedSchedule =
    coil.getModelObjectTarget<Schedule>(openstudio::Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::AvailabilityScheduleName);
  ASSERT_TRUE(repairedSchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *repairedSchedule);
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPump_Remove_RemovesOwnedCurvesAndPreservesSchedule) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPump coil(model);

  const auto initialCoils = model.getObjectsByType(CoilWaterHeatingAirToWaterHeatPump::iddObjectType()).size();
  const auto initialQuadratics = model.getObjectsByType(openstudio::IddObjectType::Curve_Quadratic).size();
  const auto initialBiquadratics = model.getObjectsByType(openstudio::IddObjectType::Curve_Biquadratic).size();
  const auto alwaysOnHandle = model.alwaysOnDiscreteSchedule().handle();

  const auto heatingCapacityTemperatureCurveHandle = coil.heatingCapacityFunctionofTemperatureCurve().handle();
  const auto heatingCapacityAirFlowCurveHandle = coil.heatingCapacityFunctionofAirFlowFractionCurve().handle();
  const auto heatingCapacityWaterFlowCurveHandle = coil.heatingCapacityFunctionofWaterFlowFractionCurve().handle();
  const auto heatingCOPTemperatureCurveHandle = coil.heatingCOPFunctionofTemperatureCurve().handle();
  const auto heatingCOPAirFlowCurveHandle = coil.heatingCOPFunctionofAirFlowFractionCurve().handle();
  const auto heatingCOPWaterFlowCurveHandle = coil.heatingCOPFunctionofWaterFlowFractionCurve().handle();
  const auto partLoadFractionCurveHandle = coil.partLoadFractionCorrelationCurve().handle();

  CurveQuadratic crankcaseCurve(model);
  ASSERT_TRUE(crankcaseCurve.setCoefficient1Constant(1.0));
  ASSERT_TRUE(crankcaseCurve.setCoefficient2x(0.1));
  ASSERT_TRUE(crankcaseCurve.setCoefficient3xPOW2(0.01));
  ASSERT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseCurve));

  EXPECT_FALSE(coil.remove().empty());
  EXPECT_EQ(initialCoils - 1u, model.getObjectsByType(CoilWaterHeatingAirToWaterHeatPump::iddObjectType()).size());
  EXPECT_EQ(initialQuadratics - 5u, model.getObjectsByType(openstudio::IddObjectType::Curve_Quadratic).size());
  EXPECT_EQ(initialBiquadratics - 2u, model.getObjectsByType(openstudio::IddObjectType::Curve_Biquadratic).size());
  EXPECT_TRUE(model.getObject(alwaysOnHandle));
  EXPECT_FALSE(model.getObject(heatingCapacityTemperatureCurveHandle));
  EXPECT_FALSE(model.getObject(heatingCapacityAirFlowCurveHandle));
  EXPECT_FALSE(model.getObject(heatingCapacityWaterFlowCurveHandle));
  EXPECT_FALSE(model.getObject(heatingCOPTemperatureCurveHandle));
  EXPECT_FALSE(model.getObject(heatingCOPAirFlowCurveHandle));
  EXPECT_FALSE(model.getObject(heatingCOPWaterFlowCurveHandle));
  EXPECT_FALSE(model.getObject(partLoadFractionCurveHandle));
  EXPECT_FALSE(model.getObject(crankcaseCurve.handle()));
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
