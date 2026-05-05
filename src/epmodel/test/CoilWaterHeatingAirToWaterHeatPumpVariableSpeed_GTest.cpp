/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../ParentObject/CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData.hpp"
#include "../ParentObject/CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../StraightComponent/CoilSystemIntegratedHeatPumpAirSource.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.hpp"
#include "../ZoneHVACComponent/WaterHeaterHeatPump.hpp"

#include <utilities/idd/Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/Handle.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_DefaultConstructor) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed coil(model);

  EXPECT_EQ(CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorAirInletNodeName, coil.airInletPort());
  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorAirOutletNodeName, coil.airOutletPort());
  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserWaterInletNodeName, coil.waterInletPort());
  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserWaterOutletNodeName, coil.waterOutletPort());

  Node node(model);
  EXPECT_FALSE(coil.addToNode(node));

  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), coil.availabilitySchedule());
  EXPECT_EQ(1, coil.nominalSpeedLevel());
  EXPECT_DOUBLE_EQ(4000.0, coil.ratedWaterHeatingCapacity());
  EXPECT_DOUBLE_EQ(29.44, coil.ratedEvaporatorInletAirDryBulbTemperature());
  EXPECT_DOUBLE_EQ(22.22, coil.ratedEvaporatorInletAirWetBulbTemperature());
  EXPECT_DOUBLE_EQ(55.72, coil.ratedCondenserInletWaterTemperature());
  EXPECT_FALSE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_TRUE(coil.isRatedEvaporatorAirFlowRateAutocalculated());
  EXPECT_FALSE(coil.autocalculatedRatedEvaporatorAirFlowRate());
  EXPECT_FALSE(coil.ratedCondenserWaterFlowRate());
  EXPECT_TRUE(coil.isRatedCondenserWaterFlowRateAutocalculated());
  EXPECT_FALSE(coil.autocalculatedRatedCondenserWaterFlowRate());
  EXPECT_EQ("Yes", coil.evaporatorFanPowerIncludedinRatedCOP());
  EXPECT_EQ("No", coil.condenserPumpPowerIncludedinRatedCOP());
  EXPECT_EQ("No", coil.condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP());
  EXPECT_DOUBLE_EQ(0.2, coil.fractionofCondenserPumpHeattoWater());
  EXPECT_DOUBLE_EQ(0.0, coil.crankcaseHeaterCapacity());
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_DOUBLE_EQ(10.0, coil.maximumAmbientTemperatureforCrankcaseHeaterOperation());
  EXPECT_EQ("WetBulbTemperature", coil.evaporatorAirTemperatureTypeforCurveObjects());

  auto partLoadFractionCurve = coil.partLoadFractionCorrelationCurve();
  EXPECT_EQ(openstudio::IddObjectType::Curve_Quadratic, partLoadFractionCurve.iddObject().type().value());

  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(partLoadFractionCurve.handle(), children.front().handle());
  EXPECT_TRUE(coil.speeds().empty());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed coil(model);

  EXPECT_TRUE(coil.setNominalSpeedLevel(2));
  EXPECT_EQ(2, coil.nominalSpeedLevel());

  EXPECT_TRUE(coil.setRatedWaterHeatingCapacity(4200.0));
  EXPECT_DOUBLE_EQ(4200.0, coil.ratedWaterHeatingCapacity());

  EXPECT_TRUE(coil.setRatedEvaporatorInletAirDryBulbTemperature(29.44));
  EXPECT_DOUBLE_EQ(29.44, coil.ratedEvaporatorInletAirDryBulbTemperature());

  EXPECT_TRUE(coil.setRatedEvaporatorInletAirWetBulbTemperature(22.22));
  EXPECT_DOUBLE_EQ(22.22, coil.ratedEvaporatorInletAirWetBulbTemperature());

  EXPECT_TRUE(coil.setRatedCondenserInletWaterTemperature(55.72));
  EXPECT_DOUBLE_EQ(55.72, coil.ratedCondenserInletWaterTemperature());

  EXPECT_TRUE(coil.setRatedEvaporatorAirFlowRate(0.52));
  ASSERT_TRUE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.52, coil.ratedEvaporatorAirFlowRate().get());
  coil.autocalculateRatedEvaporatorAirFlowRate();
  EXPECT_TRUE(coil.isRatedEvaporatorAirFlowRateAutocalculated());
  EXPECT_FALSE(coil.autocalculatedRatedEvaporatorAirFlowRate());
  EXPECT_TRUE(coil.setRatedEvaporatorAirFlowRate(0.53));
  ASSERT_TRUE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.53, coil.ratedEvaporatorAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedEvaporatorAirFlowRateAutocalculated());

  EXPECT_TRUE(coil.setRatedCondenserWaterFlowRate(0.12));
  ASSERT_TRUE(coil.ratedCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.12, coil.ratedCondenserWaterFlowRate().get());
  coil.autocalculateRatedCondenserWaterFlowRate();
  EXPECT_TRUE(coil.isRatedCondenserWaterFlowRateAutocalculated());
  EXPECT_FALSE(coil.autocalculatedRatedCondenserWaterFlowRate());
  EXPECT_TRUE(coil.setRatedCondenserWaterFlowRate(0.13));
  ASSERT_TRUE(coil.ratedCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.13, coil.ratedCondenserWaterFlowRate().get());
  EXPECT_FALSE(coil.isRatedCondenserWaterFlowRateAutocalculated());

  EXPECT_TRUE(coil.setEvaporatorFanPowerIncludedinRatedCOP("Yes"));
  EXPECT_EQ("Yes", coil.evaporatorFanPowerIncludedinRatedCOP());

  EXPECT_TRUE(coil.setCondenserPumpPowerIncludedinRatedCOP("No"));
  EXPECT_EQ("No", coil.condenserPumpPowerIncludedinRatedCOP());

  EXPECT_TRUE(coil.setCondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP("No"));
  EXPECT_EQ("No", coil.condenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP());

  EXPECT_TRUE(coil.setFractionofCondenserPumpHeattoWater(0.2));
  EXPECT_DOUBLE_EQ(0.2, coil.fractionofCondenserPumpHeattoWater());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(100.0));
  EXPECT_DOUBLE_EQ(100.0, coil.crankcaseHeaterCapacity());

  CurveQuadratic crankcaseCurve(model);
  EXPECT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseCurve));
  ASSERT_TRUE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(crankcaseCurve, coil.crankcaseHeaterCapacityFunctionofTemperatureCurve().get());
  coil.resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());

  EXPECT_TRUE(coil.setMaximumAmbientTemperatureforCrankcaseHeaterOperation(10.0));
  EXPECT_DOUBLE_EQ(10.0, coil.maximumAmbientTemperatureforCrankcaseHeaterOperation());

  const auto temperatureTypeChoices = CoilWaterHeatingAirToWaterHeatPumpVariableSpeed::evaporatorAirTemperatureTypeforCurveObjectsValues();
  EXPECT_FALSE(temperatureTypeChoices.empty());
  EXPECT_TRUE(std::find(temperatureTypeChoices.begin(), temperatureTypeChoices.end(), "WetBulbTemperature") != temperatureTypeChoices.end());

  EXPECT_TRUE(coil.setEvaporatorAirTemperatureTypeforCurveObjects("WetBulbTemperature"));
  EXPECT_EQ("WetBulbTemperature", coil.evaporatorAirTemperatureTypeforCurveObjects());

  CurveQuadratic replacementPLF(model);
  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(replacementPLF));
  EXPECT_EQ(replacementPLF, coil.partLoadFractionCorrelationCurve());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_SpeedChildrenRoundTrip) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed coil(model);
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData speed(model);
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData speed2(model);

  ASSERT_TRUE(speed2.setRatedWaterHeatingCOP(5.2));

  EXPECT_TRUE(coil.addSpeed(speed));
  EXPECT_TRUE(coil.addSpeed(speed2));
  EXPECT_TRUE(coil.setNominalSpeedLevel(2));
  ASSERT_EQ(2u, coil.speeds().size());
  EXPECT_EQ(speed.handle(), coil.speeds()[0].handle());
  EXPECT_EQ(speed2.handle(), coil.speeds()[1].handle());
  EXPECT_EQ(3u, coil.children().size());
  EXPECT_EQ(2, coil.getInt(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::NumberofSpeeds).get());

  EXPECT_TRUE(speed2.setRatedWaterHeatingCOP(5.6));
  EXPECT_DOUBLE_EQ(5.6, coil.speeds()[1].ratedWaterHeatingCOP());
  EXPECT_EQ(coil.speeds()[1].copFunctionofAirFlowFractionCurve().handle(), coil.speeds()[1].cOPFunctionofAirFlowFractionCurve().handle());

  auto attachedSpeed = coil.speeds()[0];
  EXPECT_DOUBLE_EQ(400.0, attachedSpeed.ratedWaterHeatingCapacity());
  EXPECT_EQ(openstudio::IddObjectType::Curve_Biquadratic,
            attachedSpeed.totalWaterHeatingCapacityFunctionofTemperatureCurve().iddObject().type().value());
  EXPECT_EQ(6u, attachedSpeed.children().size());

  EXPECT_TRUE(attachedSpeed.setRatedWaterHeatingCOP(4.5));
  EXPECT_DOUBLE_EQ(4.5, coil.speeds().front().ratedWaterHeatingCOP());

  coil.removeSpeed(attachedSpeed);
  ASSERT_EQ(1u, coil.speeds().size());
  EXPECT_EQ(speed2.handle(), coil.speeds().front().handle());
  EXPECT_DOUBLE_EQ(5.6, coil.speeds().front().ratedWaterHeatingCOP());
  EXPECT_EQ(1, coil.getInt(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::NumberofSpeeds).get());
  EXPECT_EQ(2, coil.nominalSpeedLevel());
  EXPECT_DOUBLE_EQ(4.5, attachedSpeed.ratedWaterHeatingCOP());

  coil.removeAllSpeeds();
  EXPECT_TRUE(coil.speeds().empty());
  EXPECT_EQ(1u, coil.children().size());
  EXPECT_FALSE(coil.getInt(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::NumberofSpeeds));
  EXPECT_DOUBLE_EQ(4.5, attachedSpeed.ratedWaterHeatingCOP());
  EXPECT_DOUBLE_EQ(5.6, speed2.ratedWaterHeatingCOP());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_RemoveCleansUpAttachedTransientSpeeds) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed coil(model);
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData speed1(model);
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData speed2(model);

  ASSERT_TRUE(coil.addSpeed(speed1));
  ASSERT_TRUE(coil.addSpeed(speed2));
  ASSERT_EQ(2u, coil.speeds().size());
  EXPECT_EQ(2u, model.getConcreteModelObjects<CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData>(true).size());

  coil.remove();

  EXPECT_TRUE(model.getConcreteModelObjects<CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData>(true).empty());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_ContainingHVACComponentTracksCompoundOwners) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed coil(model);

  EXPECT_FALSE(coil.containingHVACComponent());

  WaterHeaterHeatPump heatPump(model);
  EXPECT_TRUE(heatPump.setDXCoil(coil));
  auto owner = coil.containingHVACComponent();
  ASSERT_TRUE(owner);
  EXPECT_EQ(heatPump.handle(), owner->handle());
  EXPECT_TRUE(coil.remove().empty());

  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed systemCoil(model);
  CoilSystemIntegratedHeatPumpAirSource system(model);
  EXPECT_TRUE(system.setDedicatedWaterHeatingCoil(systemCoil));
  owner = systemCoil.containingHVACComponent();
  ASSERT_TRUE(owner);
  EXPECT_EQ(system.handle(), owner->handle());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_AvailabilityScheduleGetterRepairsMissingRequiredReference) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed coil(model);

  ASSERT_TRUE(coil.setPointer(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(coil.getModelObjectTarget<Schedule>(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::AvailabilityScheduleName));

  const auto schedule = coil.availabilitySchedule();
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), schedule);
  const auto repairedSchedule =
    coil.getModelObjectTarget<Schedule>(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::AvailabilityScheduleName);
  ASSERT_TRUE(repairedSchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *repairedSchedule);
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_AttachedSpeedRemoveRemovesParentRowAndTransientWrapper) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeed coil(model);
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData speed1(model);
  CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData speed2(model);

  ASSERT_TRUE(coil.addSpeed(speed1));
  ASSERT_TRUE(coil.addSpeed(speed2));
  auto attachedSpeed = coil.speeds().front();
  const auto attachedHandle = attachedSpeed.handle();

  EXPECT_EQ(2u, model.getConcreteModelObjects<CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData>(true).size());

  attachedSpeed.remove();

  ASSERT_EQ(1u, coil.speeds().size());
  EXPECT_EQ(speed2.handle(), coil.speeds().front().handle());
  EXPECT_EQ(1, coil.getInt(openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::NumberofSpeeds).get());
  const auto remainingSpeeds = model.getConcreteModelObjects<CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData>(true);
  EXPECT_EQ(1u, remainingSpeeds.size());
  EXPECT_TRUE(std::none_of(remainingSpeeds.begin(), remainingSpeeds.end(), [&](const auto& speed) { return speed.handle() == attachedHandle; }));
}
