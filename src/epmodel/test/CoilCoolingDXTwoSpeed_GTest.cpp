/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXTwoSpeed.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_DefaultConstructor) {
  Model model;
  CoilCoolingDXTwoSpeed coil(model);

  EXPECT_EQ(CoilCoolingDXTwoSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());

  ASSERT_TRUE(coil.totalCoolingCapacityFunctionOfTemperatureCurve().optionalCast<CurveBiquadratic>());
  ASSERT_TRUE(coil.totalCoolingCapacityFunctionOfFlowFractionCurve().optionalCast<CurveQuadratic>());
  ASSERT_TRUE(coil.energyInputRatioFunctionOfTemperatureCurve().optionalCast<CurveBiquadratic>());
  ASSERT_TRUE(coil.energyInputRatioFunctionOfFlowFractionCurve().optionalCast<CurveQuadratic>());
  ASSERT_TRUE(coil.partLoadFractionCorrelationCurve().optionalCast<CurveQuadratic>());
  ASSERT_TRUE(coil.lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve().optionalCast<CurveBiquadratic>());
  ASSERT_TRUE(coil.lowSpeedEnergyInputRatioFunctionOfTemperatureCurve().optionalCast<CurveBiquadratic>());

  EXPECT_FALSE(coil.basinHeaterOperatingSchedule());

  const auto children = coil.children();
  ASSERT_EQ(7u, children.size());
  EXPECT_EQ(coil.totalCoolingCapacityFunctionOfTemperatureCurve().handle(), children[0].handle());
  EXPECT_EQ(coil.totalCoolingCapacityFunctionOfFlowFractionCurve().handle(), children[1].handle());
  EXPECT_EQ(coil.energyInputRatioFunctionOfTemperatureCurve().handle(), children[2].handle());
  EXPECT_EQ(coil.energyInputRatioFunctionOfFlowFractionCurve().handle(), children[3].handle());
  EXPECT_EQ(coil.partLoadFractionCorrelationCurve().handle(), children[4].handle());
  EXPECT_EQ(coil.lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve().handle(), children[5].handle());
  EXPECT_EQ(coil.lowSpeedEnergyInputRatioFunctionOfTemperatureCurve().handle(), children[6].handle());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXTwoSpeed coil(model);

  ASSERT_FALSE(CoilCoolingDXTwoSpeed::condenserTypeValues().empty());

  EXPECT_TRUE(coil.setRatedHighSpeedTotalCoolingCapacity(10000.0));
  ASSERT_TRUE(coil.ratedHighSpeedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(10000.0, coil.ratedHighSpeedTotalCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedHighSpeedTotalCoolingCapacityAutosized());
  coil.autosizeRatedHighSpeedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedHighSpeedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedHighSpeedSensibleHeatRatio(0.72));
  ASSERT_TRUE(coil.ratedHighSpeedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.72, coil.ratedHighSpeedSensibleHeatRatio().get());
  EXPECT_FALSE(coil.isRatedHighSpeedSensibleHeatRatioAutosized());
  coil.autosizeRatedHighSpeedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedHighSpeedSensibleHeatRatioAutosized());

  EXPECT_TRUE(coil.setRatedHighSpeedCOP(3.6));
  EXPECT_DOUBLE_EQ(3.6, coil.ratedHighSpeedCOP());

  EXPECT_TRUE(coil.setRatedHighSpeedAirFlowRate(1.25));
  ASSERT_TRUE(coil.ratedHighSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, coil.ratedHighSpeedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedHighSpeedAirFlowRateAutosized());
  coil.autosizeRatedHighSpeedAirFlowRate();
  EXPECT_TRUE(coil.isRatedHighSpeedAirFlowRateAutosized());

  EXPECT_TRUE(coil.setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017(700.0));
  EXPECT_DOUBLE_EQ(700.0, coil.ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017());
  EXPECT_TRUE(coil.setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023(900.0));
  EXPECT_DOUBLE_EQ(900.0, coil.ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023());

  EXPECT_TRUE(coil.setRatedLowSpeedTotalCoolingCapacity(4200.0));
  ASSERT_TRUE(coil.ratedLowSpeedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(4200.0, coil.ratedLowSpeedTotalCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedLowSpeedTotalCoolingCapacityAutosized());
  coil.autosizeRatedLowSpeedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedLowSpeedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedLowSpeedSensibleHeatRatio(0.66));
  ASSERT_TRUE(coil.ratedLowSpeedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.66, coil.ratedLowSpeedSensibleHeatRatio().get());
  EXPECT_FALSE(coil.isRatedLowSpeedSensibleHeatRatioAutosized());
  coil.autosizeRatedLowSpeedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedLowSpeedSensibleHeatRatioAutosized());

  EXPECT_TRUE(coil.setRatedLowSpeedCOP(2.9));
  EXPECT_DOUBLE_EQ(2.9, coil.ratedLowSpeedCOP());

  EXPECT_TRUE(coil.setRatedLowSpeedAirFlowRate(0.85));
  ASSERT_TRUE(coil.ratedLowSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(0.85, coil.ratedLowSpeedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedLowSpeedAirFlowRateAutosized());
  coil.autosizeRatedLowSpeedAirFlowRate();
  EXPECT_TRUE(coil.isRatedLowSpeedAirFlowRateAutosized());

  EXPECT_TRUE(coil.setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017(650.0));
  EXPECT_DOUBLE_EQ(650.0, coil.ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017());
  EXPECT_TRUE(coil.setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023(850.0));
  EXPECT_DOUBLE_EQ(850.0, coil.ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023());

  EXPECT_TRUE(coil.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("EvaporativelyCooled", coil.condenserType());

  EXPECT_TRUE(coil.setHighSpeedEvaporativeCondenserEffectiveness(0.82));
  EXPECT_DOUBLE_EQ(0.82, coil.highSpeedEvaporativeCondenserEffectiveness());
  EXPECT_TRUE(coil.setHighSpeedEvaporativeCondenserAirFlowRate(0.40));
  ASSERT_TRUE(coil.highSpeedEvaporativeCondenserAirFlowRate());
  EXPECT_DOUBLE_EQ(0.40, coil.highSpeedEvaporativeCondenserAirFlowRate().get());
  EXPECT_FALSE(coil.isHighSpeedEvaporativeCondenserAirFlowRateAutosized());
  coil.autosizeHighSpeedEvaporativeCondenserAirFlowRate();
  EXPECT_TRUE(coil.isHighSpeedEvaporativeCondenserAirFlowRateAutosized());
  EXPECT_TRUE(coil.setHighSpeedEvaporativeCondenserPumpRatedPowerConsumption(125.0));
  ASSERT_TRUE(coil.highSpeedEvaporativeCondenserPumpRatedPowerConsumption());
  EXPECT_DOUBLE_EQ(125.0, coil.highSpeedEvaporativeCondenserPumpRatedPowerConsumption().get());
  EXPECT_FALSE(coil.isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());
  coil.autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption();
  EXPECT_TRUE(coil.isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());

  EXPECT_TRUE(coil.setLowSpeedEvaporativeCondenserEffectiveness(0.79));
  EXPECT_DOUBLE_EQ(0.79, coil.lowSpeedEvaporativeCondenserEffectiveness());
  EXPECT_TRUE(coil.setLowSpeedEvaporativeCondenserAirFlowRate(0.30));
  ASSERT_TRUE(coil.lowSpeedEvaporativeCondenserAirFlowRate());
  EXPECT_DOUBLE_EQ(0.30, coil.lowSpeedEvaporativeCondenserAirFlowRate().get());
  EXPECT_FALSE(coil.isLowSpeedEvaporativeCondenserAirFlowRateAutosized());
  coil.autosizeLowSpeedEvaporativeCondenserAirFlowRate();
  EXPECT_TRUE(coil.isLowSpeedEvaporativeCondenserAirFlowRateAutosized());
  EXPECT_TRUE(coil.setLowSpeedEvaporativeCondenserPumpRatedPowerConsumption(95.0));
  ASSERT_TRUE(coil.lowSpeedEvaporativeCondenserPumpRatedPowerConsumption());
  EXPECT_DOUBLE_EQ(95.0, coil.lowSpeedEvaporativeCondenserPumpRatedPowerConsumption().get());
  EXPECT_FALSE(coil.isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());
  coil.autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption();
  EXPECT_TRUE(coil.isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());

  EXPECT_TRUE(coil.setBasinHeaterCapacity(25.0));
  EXPECT_DOUBLE_EQ(25.0, coil.basinHeaterCapacity());
  EXPECT_TRUE(coil.setBasinHeaterSetpointTemperature(3.5));
  EXPECT_DOUBLE_EQ(3.5, coil.basinHeaterSetpointTemperature());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-10.0));
  EXPECT_DOUBLE_EQ(-10.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());

  EXPECT_TRUE(coil.setUnitInternalStaticAirPressure(710.0));
  EXPECT_DOUBLE_EQ(710.0, coil.unitInternalStaticAirPressure());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_RelationshipSetters_RoundTrip) {
  Model model;
  CoilCoolingDXTwoSpeed coil(model);

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.25));
  ScheduleConstant basinSchedule(model);
  ASSERT_TRUE(basinSchedule.setValue(0.75));

  CurveBiquadratic totalCoolingTemp(model);
  CurveQuadratic totalCoolingFlow(model);
  CurveBiquadratic eirTemp(model);
  CurveQuadratic eirFlow(model);
  CurveQuadratic plf(model);
  CurveBiquadratic lowSpeedTemp(model);
  CurveBiquadratic lowSpeedEirTemp(model);

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setTotalCoolingCapacityFunctionOfTemperatureCurve(totalCoolingTemp));
  EXPECT_EQ(totalCoolingTemp.handle(), coil.totalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_TRUE(coil.setTotalCoolingCapacityFunctionOfFlowFractionCurve(totalCoolingFlow));
  EXPECT_EQ(totalCoolingFlow.handle(), coil.totalCoolingCapacityFunctionOfFlowFractionCurve().handle());
  EXPECT_TRUE(coil.setEnergyInputRatioFunctionOfTemperatureCurve(eirTemp));
  EXPECT_EQ(eirTemp.handle(), coil.energyInputRatioFunctionOfTemperatureCurve().handle());
  EXPECT_TRUE(coil.setEnergyInputRatioFunctionOfFlowFractionCurve(eirFlow));
  EXPECT_EQ(eirFlow.handle(), coil.energyInputRatioFunctionOfFlowFractionCurve().handle());
  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(plf));
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve().handle());
  EXPECT_TRUE(coil.setLowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve(lowSpeedTemp));
  EXPECT_EQ(lowSpeedTemp.handle(), coil.lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_TRUE(coil.setLowSpeedEnergyInputRatioFunctionOfTemperatureCurve(lowSpeedEirTemp));
  EXPECT_EQ(lowSpeedEirTemp.handle(), coil.lowSpeedEnergyInputRatioFunctionOfTemperatureCurve().handle());

  EXPECT_TRUE(coil.setBasinHeaterOperatingSchedule(basinSchedule));
  ASSERT_TRUE(coil.basinHeaterOperatingSchedule());
  EXPECT_EQ(basinSchedule.handle(), coil.basinHeaterOperatingSchedule()->handle());

  const auto children = coil.children();
  ASSERT_EQ(7u, children.size());
  EXPECT_EQ(totalCoolingTemp.handle(), children[0].handle());
  EXPECT_EQ(totalCoolingFlow.handle(), children[1].handle());
  EXPECT_EQ(eirTemp.handle(), children[2].handle());
  EXPECT_EQ(eirFlow.handle(), children[3].handle());
  EXPECT_EQ(plf.handle(), children[4].handle());
  EXPECT_EQ(lowSpeedTemp.handle(), children[5].handle());
  EXPECT_EQ(lowSpeedEirTemp.handle(), children[6].handle());

  coil.resetBasinHeaterOperatingSchedule();
  EXPECT_FALSE(coil.basinHeaterOperatingSchedule());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_RelationshipConstructor) {
  Model model;
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.6));

  CurveBiquadratic totalCoolingTemp(model);
  CurveQuadratic totalCoolingFlow(model);
  CurveBiquadratic eirTemp(model);
  CurveQuadratic eirFlow(model);
  CurveQuadratic plf(model);
  CurveBiquadratic lowSpeedTemp(model);
  CurveBiquadratic lowSpeedEirTemp(model);

  CoilCoolingDXTwoSpeed coil(model, availability, totalCoolingTemp, totalCoolingFlow, eirTemp, eirFlow, plf, lowSpeedTemp, lowSpeedEirTemp);

  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  EXPECT_EQ(totalCoolingTemp.handle(), coil.totalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_EQ(totalCoolingFlow.handle(), coil.totalCoolingCapacityFunctionOfFlowFractionCurve().handle());
  EXPECT_EQ(eirTemp.handle(), coil.energyInputRatioFunctionOfTemperatureCurve().handle());
  EXPECT_EQ(eirFlow.handle(), coil.energyInputRatioFunctionOfFlowFractionCurve().handle());
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve().handle());
  EXPECT_EQ(lowSpeedTemp.handle(), coil.lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_EQ(lowSpeedEirTemp.handle(), coil.lowSpeedEnergyInputRatioFunctionOfTemperatureCurve().handle());
  EXPECT_TRUE(coil.isRatedHighSpeedTotalCoolingCapacityAutosized());
  EXPECT_TRUE(coil.isRatedHighSpeedSensibleHeatRatioAutosized());
  EXPECT_TRUE(coil.isRatedHighSpeedAirFlowRateAutosized());
  EXPECT_TRUE(coil.isRatedLowSpeedTotalCoolingCapacityAutosized());
  ASSERT_TRUE(coil.ratedLowSpeedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.69, *coil.ratedLowSpeedSensibleHeatRatio());
  EXPECT_TRUE(coil.isRatedLowSpeedAirFlowRateAutosized());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  CoilCoolingDXTwoSpeed supplyCoil(model);
  CoilCoolingDXTwoSpeed demandCoil(model);
  CoilCoolingDXTwoSpeed oaCoil(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyCoil.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyCoil.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyCoil.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyCoil.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoil.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoil.airLoopHVAC());

  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  EXPECT_FALSE(oaCoil.addToNode(*outboardOANode));
  EXPECT_FALSE(oaCoil.airLoopHVAC());
}
