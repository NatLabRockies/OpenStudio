/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitOperatingMode.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitPerformance.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitPerformance_Impl.hpp"
#include "../Schedule/Schedule.hpp"

#include <utilities/idd/Coil_Cooling_DX_CurveFit_Performance_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXCurveFitPerformance_DefaultConstructor) {
  Model model;
  CoilCoolingDXCurveFitPerformance performance(model);
  EXPECT_EQ(CoilCoolingDXCurveFitPerformance::iddObjectType(), performance.iddObject().type());
  EXPECT_FALSE(performance.nameString().empty());
}

TEST_F(EPModelFixture, CoilCoolingDXCurveFitPerformance_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXCurveFitPerformance performance(model);

  EXPECT_TRUE(performance.setCrankcaseHeaterCapacity(500.0));
  EXPECT_DOUBLE_EQ(500.0, performance.crankcaseHeaterCapacity());

  EXPECT_TRUE(performance.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-12.0));
  EXPECT_DOUBLE_EQ(-12.0, performance.minimumOutdoorDryBulbTemperatureforCompressorOperation());

  EXPECT_TRUE(performance.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(9.0));
  EXPECT_DOUBLE_EQ(9.0, performance.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());

  EXPECT_TRUE(performance.setUnitInternalStaticAirPressure(780.0));
  EXPECT_DOUBLE_EQ(780.0, performance.unitInternalStaticAirPressure());

  EXPECT_TRUE(performance.setCapacityControlMethod("Continuous"));
  EXPECT_EQ("Continuous", performance.capacityControlMethod());

  EXPECT_TRUE(performance.setEvaporativeCondenserBasinHeaterCapacity(42.0));
  EXPECT_DOUBLE_EQ(42.0, performance.evaporativeCondenserBasinHeaterCapacity());

  EXPECT_TRUE(performance.setEvaporativeCondenserBasinHeaterSetpointTemperature(3.0));
  EXPECT_DOUBLE_EQ(3.0, performance.evaporativeCondenserBasinHeaterSetpointTemperature());

  EXPECT_TRUE(performance.setCompressorFuelType("Electricity"));
  EXPECT_EQ("Electricity", performance.compressorFuelType());

  const auto capacityControlMethodValues = CoilCoolingDXCurveFitPerformance::capacityControlMethodValues();
  EXPECT_NE(std::find(capacityControlMethodValues.begin(), capacityControlMethodValues.end(), "Discrete"), capacityControlMethodValues.end());

  const auto compressorFuelTypeValues = CoilCoolingDXCurveFitPerformance::compressorFuelTypeValues();
  EXPECT_NE(std::find(compressorFuelTypeValues.begin(), compressorFuelTypeValues.end(), "Electricity"), compressorFuelTypeValues.end());
}

TEST_F(EPModelFixture, CoilCoolingDXCurveFitPerformance_BaseOperatingModeRelationship) {
  Model model;
  CoilCoolingDXCurveFitOperatingMode baseOperatingMode(model);
  CoilCoolingDXCurveFitPerformance performance(model, baseOperatingMode);

  EXPECT_EQ(baseOperatingMode.handle(), performance.baseOperatingMode().handle());
  EXPECT_DOUBLE_EQ(0.0, performance.crankcaseHeaterCapacity());
  EXPECT_DOUBLE_EQ(-25.0, performance.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  EXPECT_DOUBLE_EQ(10.0, performance.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_DOUBLE_EQ(773.3, performance.unitInternalStaticAirPressure());
  EXPECT_EQ("Discrete", performance.capacityControlMethod());
  EXPECT_DOUBLE_EQ(0.0, performance.evaporativeCondenserBasinHeaterCapacity());
  EXPECT_DOUBLE_EQ(2.0, performance.evaporativeCondenserBasinHeaterSetpointTemperature());
  EXPECT_EQ("Electricity", performance.compressorFuelType());
  const auto basinHeaterSchedule =
    performance.getTarget(openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterOperatingScheduleName);
  ASSERT_TRUE(basinHeaterSchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), basinHeaterSchedule->handle());

  CoilCoolingDXCurveFitOperatingMode replacementOperatingMode(model);
  ASSERT_TRUE(performance.setBaseOperatingMode(replacementOperatingMode));
  EXPECT_EQ(replacementOperatingMode.handle(), performance.baseOperatingMode().handle());

  Model otherModel;
  CoilCoolingDXCurveFitOperatingMode foreignOperatingMode(otherModel);
  EXPECT_FALSE(performance.setBaseOperatingMode(foreignOperatingMode));
  EXPECT_EQ(replacementOperatingMode.handle(), performance.baseOperatingMode().handle());

  const auto objectCount = otherModel.getConcreteModelObjects<CoilCoolingDXCurveFitPerformance>().size();
  EXPECT_THROW((CoilCoolingDXCurveFitPerformance{otherModel, replacementOperatingMode}), std::invalid_argument);
  EXPECT_EQ(objectCount, otherModel.getConcreteModelObjects<CoilCoolingDXCurveFitPerformance>().size());
}
