/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACDehumidifierDX.hpp"

#include <utilities/idd/ZoneHVAC_Dehumidifier_DX_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACDehumidifierDX_DefaultConstructor) {
  Model model;
  ZoneHVACDehumidifierDX dehumidifier(model);
  EXPECT_EQ(ZoneHVACDehumidifierDX::iddObjectType(), dehumidifier.iddObject().type());
  EXPECT_EQ(openstudio::ZoneHVAC_Dehumidifier_DXFields::AirInletNodeName, dehumidifier.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_Dehumidifier_DXFields::AirOutletNodeName, dehumidifier.outletPort());
  EXPECT_FALSE(dehumidifier.inletNode());
  EXPECT_FALSE(dehumidifier.outletNode());
  EXPECT_DOUBLE_EQ(50.16, dehumidifier.ratedWaterRemoval());
  EXPECT_DOUBLE_EQ(3.412, dehumidifier.ratedEnergyFactor());
  EXPECT_DOUBLE_EQ(0.12036, dehumidifier.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(10.0, dehumidifier.minimumDryBulbTemperatureforDehumidifierOperation());
  EXPECT_DOUBLE_EQ(32.0, dehumidifier.maximumDryBulbTemperatureforDehumidifierOperation());
  EXPECT_DOUBLE_EQ(0.0, dehumidifier.offCycleParasiticElectricLoad());
}

TEST_F(EPModelFixture, ZoneHVACDehumidifierDX_ThermalZoneAttachDetach) {
  Model model;
  ZoneHVACDehumidifierDX dehumidifier(model);
  ThermalZone zone(model);

  EXPECT_TRUE(dehumidifier.addToThermalZone(zone));
  EXPECT_TRUE(dehumidifier.thermalZone());
  EXPECT_EQ(zone, dehumidifier.thermalZone().get());
  EXPECT_TRUE(dehumidifier.inletNode());
  EXPECT_TRUE(dehumidifier.outletNode());

  dehumidifier.removeFromThermalZone();
  EXPECT_FALSE(dehumidifier.thermalZone());
  EXPECT_FALSE(dehumidifier.inletNode());
  EXPECT_FALSE(dehumidifier.outletNode());
}

TEST_F(EPModelFixture, ZoneHVACDehumidifierDX_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACDehumidifierDX dehumidifier(model);

  EXPECT_TRUE(dehumidifier.setRatedWaterRemoval(60.5));
  EXPECT_TRUE(dehumidifier.setRatedEnergyFactor(4.001));
  EXPECT_TRUE(dehumidifier.setRatedAirFlowRate(0.150));
  EXPECT_TRUE(dehumidifier.setMinimumDryBulbTemperatureforDehumidifierOperation(12.0));
  EXPECT_TRUE(dehumidifier.setMaximumDryBulbTemperatureforDehumidifierOperation(34.0));
  EXPECT_TRUE(dehumidifier.setOffCycleParasiticElectricLoad(2.5));

  EXPECT_DOUBLE_EQ(60.5, dehumidifier.ratedWaterRemoval());
  EXPECT_DOUBLE_EQ(4.001, dehumidifier.ratedEnergyFactor());
  EXPECT_DOUBLE_EQ(0.150, dehumidifier.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(12.0, dehumidifier.minimumDryBulbTemperatureforDehumidifierOperation());
  EXPECT_DOUBLE_EQ(34.0, dehumidifier.maximumDryBulbTemperatureforDehumidifierOperation());
  EXPECT_DOUBLE_EQ(2.5, dehumidifier.offCycleParasiticElectricLoad());
}

TEST_F(EPModelFixture, ZoneHVACDehumidifierDX_ChildrenOrderAndContent) {
  Model model;
  ZoneHVACDehumidifierDX dehumidifier(model);

  CurveBiquadratic waterRemovalCurve(model);
  CurveBiquadratic energyFactorCurve(model);
  CurveQuadratic partLoadCurve(model);

  EXPECT_TRUE(dehumidifier.setPointer(openstudio::ZoneHVAC_Dehumidifier_DXFields::WaterRemovalCurveName, waterRemovalCurve.handle()));
  EXPECT_TRUE(dehumidifier.setPointer(openstudio::ZoneHVAC_Dehumidifier_DXFields::EnergyFactorCurveName, energyFactorCurve.handle()));
  EXPECT_TRUE(dehumidifier.setPointer(openstudio::ZoneHVAC_Dehumidifier_DXFields::PartLoadFractionCorrelationCurveName, partLoadCurve.handle()));

  const auto children = dehumidifier.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(waterRemovalCurve.handle(), children[0].handle());
  EXPECT_EQ(energyFactorCurve.handle(), children[1].handle());
  EXPECT_EQ(partLoadCurve.handle(), children[2].handle());
  EXPECT_EQ(openstudio::IddObjectType::Curve_Biquadratic, children[0].iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::Curve_Biquadratic, children[1].iddObject().type().value());
  EXPECT_EQ(openstudio::IddObjectType::Curve_Quadratic, children[2].iddObject().type().value());
}
