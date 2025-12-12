/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelFixture.hpp"

#include "../HeatPumpAirToWaterHeatingSpeedData.hpp"
#include "../HeatPumpAirToWaterHeatingSpeedData_Impl.hpp"

#include "../HeatPumpAirToWaterHeating.hpp"

#include "../Model.hpp"
#include "../Curve.hpp"
#include "../Curve_Impl.hpp"
#include "../CurveBiquadratic.hpp"
#include "../CurveBiquadratic_Impl.hpp"
#include "../CurveQuadratic.hpp"
#include "../CurveQuadratic_Impl.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, HeatPumpAirToWaterHeatingSpeedData_GettersSetters) {
  Model m;
  HeatPumpAirToWaterHeatingSpeedData heatPumpAirToWaterHeatingSpeedData(m);

  heatPumpAirToWaterHeatingSpeedData.setName("My HeatPumpAirToWaterHeatingSpeedData");

  // Rated Heating Capacity: Required Double, ctor defaults to autosize
  EXPECT_TRUE(heatPumpAirToWaterHeatingSpeedData.isRatedHeatingCapacityAutosized());
  // Set
  EXPECT_TRUE(heatPumpAirToWaterHeatingSpeedData.setRatedHeatingCapacity(40000.0));
  ASSERT_TRUE(heatPumpAirToWaterHeatingSpeedData.ratedHeatingCapacity());
  EXPECT_EQ(40000.0, heatPumpAirToWaterHeatingSpeedData.ratedHeatingCapacity().get());
  EXPECT_FALSE(heatPumpAirToWaterHeatingSpeedData.isRatedHeatingCapacityAutosized());
  // Bad Value
  EXPECT_FALSE(heatPumpAirToWaterHeatingSpeedData.setRatedHeatingCapacity(-10.0));
  ASSERT_TRUE(heatPumpAirToWaterHeatingSpeedData.ratedHeatingCapacity());
  EXPECT_EQ(40000.0, heatPumpAirToWaterHeatingSpeedData.ratedHeatingCapacity().get());
  EXPECT_FALSE(heatPumpAirToWaterHeatingSpeedData.isRatedHeatingCapacityAutosized());
  // Autosize
  heatPumpAirToWaterHeatingSpeedData.autosizeRatedHeatingCapacity();
  EXPECT_TRUE(heatPumpAirToWaterHeatingSpeedData.isRatedHeatingCapacityAutosized());

  // Rated COP for Heating: Required Double, defaults to 3.0
  EXPECT_EQ(3.0, heatPumpAirToWaterHeatingSpeedData.ratedCOPforHeating());
  // Set
  EXPECT_TRUE(heatPumpAirToWaterHeatingSpeedData.setRatedCOPforHeating(4.0));
  EXPECT_EQ(4.0, heatPumpAirToWaterHeatingSpeedData.ratedCOPforHeating());
  // Bad Value
  EXPECT_FALSE(heatPumpAirToWaterHeatingSpeedData.setRatedCOPforHeating(-10.0));
  EXPECT_EQ(4.0, heatPumpAirToWaterHeatingSpeedData.ratedCOPforHeating());

  // Normalized Heating Capacity Function of Temperature Curve Name: Required Object
  auto oriCapFT = heatPumpAirToWaterHeatingSpeedData.normalizedHeatingCapacityFunctionofTemperatureCurve();
  CurveBiquadratic capFT(m);
  EXPECT_TRUE(heatPumpAirToWaterHeatingSpeedData.setNormalizedHeatingCapacityFunctionofTemperatureCurve(capFT));
  EXPECT_EQ(capFT, heatPumpAirToWaterHeatingSpeedData.normalizedHeatingCapacityFunctionofTemperatureCurve());
  EXPECT_NE(capFT, oriCapFT);

  // Heating Energy Input Ratio Function of Temperature Curve Name: Required Object
  auto oriEIRFT = heatPumpAirToWaterHeatingSpeedData.heatingEnergyInputRatioFunctionofTemperatureCurve();
  CurveBiquadratic eirFT(m);
  EXPECT_TRUE(heatPumpAirToWaterHeatingSpeedData.setHeatingEnergyInputRatioFunctionofTemperatureCurve(eirFT));
  EXPECT_EQ(eirFT, heatPumpAirToWaterHeatingSpeedData.heatingEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_NE(eirFT, oriEIRFT);

  // Heating Energy Input Ratio Function of PLR Curve Name: Required Object
  auto oriEIRFPLR = heatPumpAirToWaterHeatingSpeedData.heatingEnergyInputRatioFunctionofPLRCurve();
  CurveQuadratic eirFPLR(m);
  EXPECT_TRUE(heatPumpAirToWaterHeatingSpeedData.setHeatingEnergyInputRatioFunctionofPLRCurve(eirFPLR));
  EXPECT_EQ(eirFPLR, heatPumpAirToWaterHeatingSpeedData.heatingEnergyInputRatioFunctionofPLRCurve());
  EXPECT_NE(eirFPLR, oriEIRFPLR);
}

TEST_F(ModelFixture, HeatPumpAirToWaterHeatingSpeedData_CreateInvalid) {
  {
    Model m;
    CurveQuadratic univariate(m);
    CurveBiquadratic bivariate(m);

    EXPECT_EQ(1, univariate.numVariables());
    EXPECT_EQ(2, bivariate.numVariables());

    // Valid
    {
      HeatPumpAirToWaterHeatingSpeedData awhpHCSpeed(m, bivariate, bivariate, univariate);
      EXPECT_EQ(1, m.getConcreteModelObjects<HeatPumpAirToWaterHeatingSpeedData>().size());
      EXPECT_EQ(1, m.getConcreteModelObjects<CurveBiquadratic>().size());
      EXPECT_EQ(1, m.getConcreteModelObjects<CurveQuadratic>().size());
    }

    // Invalid: wrong curve type
    EXPECT_THROW({ HeatPumpAirToWaterHeatingSpeedData(m, bivariate, univariate, univariate); }, openstudio::Exception);
    EXPECT_THROW({ HeatPumpAirToWaterHeatingSpeedData(m, univariate, bivariate, univariate); }, openstudio::Exception);
    EXPECT_THROW({ HeatPumpAirToWaterHeatingSpeedData(m, bivariate, bivariate, bivariate); }, openstudio::Exception);
    EXPECT_EQ(1, m.getConcreteModelObjects<HeatPumpAirToWaterHeatingSpeedData>().size());
    EXPECT_EQ(1, m.getConcreteModelObjects<CurveBiquadratic>().size());
    EXPECT_EQ(1, m.getConcreteModelObjects<CurveQuadratic>().size());
  }

  // There is a nasty side effect that curves may be removed if ctor failed and they are not used anywhere else, so we'll want to call
  // ModelObject::remove() and not HeatPumpAirToWaterHeatingSpeedData::remove() (=ParentObject::remove) in the ctor
  {
    Model m;
    CurveQuadratic univariate(m);
    CurveBiquadratic bivariate(m);
    EXPECT_EQ(0, univariate.directUseCount());
    EXPECT_EQ(0, bivariate.directUseCount());

    EXPECT_THROW({ HeatPumpAirToWaterHeatingSpeedData(m, bivariate, univariate, univariate); }, openstudio::Exception);
    EXPECT_EQ(0, m.getConcreteModelObjects<HeatPumpAirToWaterHeatingSpeedData>().size());
    // Curves should not be removed in case the expliclit ctor with curves failed
    EXPECT_EQ(1, m.getConcreteModelObjects<CurveBiquadratic>().size());
    EXPECT_EQ(1, m.getConcreteModelObjects<CurveQuadratic>().size());
  }
}

TEST_F(ModelFixture, HeatPumpAirToWaterHeatingSpeedData_clone_remove) {

  Model m;
  CurveBiquadratic capFT(m);
  CurveBiquadratic eirFT(m);
  CurveQuadratic eirFPLR(m);

  constexpr double cap = 40000.0;
  constexpr double cop = 4.0;

  HeatPumpAirToWaterHeatingSpeedData awhpHCSpeed(m, capFT, eirFT, eirFPLR);
  EXPECT_TRUE(awhpHCSpeed.setRatedHeatingCapacity(cap));
  EXPECT_TRUE(awhpHCSpeed.setRatedCOPforHeating(cop));

  EXPECT_EQ(1, m.getConcreteModelObjects<HeatPumpAirToWaterHeatingSpeedData>().size());
  EXPECT_EQ(2, m.getConcreteModelObjects<CurveBiquadratic>().size());
  EXPECT_EQ(1, m.getConcreteModelObjects<CurveQuadratic>().size());

  auto awhpHCSpeedClone = awhpHCSpeed.clone(m).cast<HeatPumpAirToWaterHeatingSpeedData>();
  EXPECT_EQ(cap, awhpHCSpeedClone.ratedHeatingCapacity().get());
  EXPECT_EQ(cop, awhpHCSpeedClone.ratedCOPforHeating());
  EXPECT_EQ(capFT, awhpHCSpeedClone.normalizedHeatingCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(eirFT, awhpHCSpeedClone.heatingEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(eirFPLR, awhpHCSpeedClone.heatingEnergyInputRatioFunctionofPLRCurve());

  EXPECT_EQ(2, m.getConcreteModelObjects<HeatPumpAirToWaterHeatingSpeedData>().size());
  EXPECT_EQ(2, m.getConcreteModelObjects<CurveBiquadratic>().size());
  EXPECT_EQ(1, m.getConcreteModelObjects<CurveQuadratic>().size());

  {
    Model m2;
    auto awhpHCSpeedClone2 = awhpHCSpeed.clone(m2).cast<HeatPumpAirToWaterHeatingSpeedData>();
    EXPECT_EQ(cap, awhpHCSpeedClone2.ratedHeatingCapacity().get());
    EXPECT_EQ(cop, awhpHCSpeedClone2.ratedCOPforHeating());
    EXPECT_NE(capFT, awhpHCSpeedClone2.normalizedHeatingCapacityFunctionofTemperatureCurve());
    EXPECT_NE(eirFT, awhpHCSpeedClone2.heatingEnergyInputRatioFunctionofTemperatureCurve());
    EXPECT_NE(eirFPLR, awhpHCSpeedClone2.heatingEnergyInputRatioFunctionofPLRCurve());

    EXPECT_EQ(1, m2.getConcreteModelObjects<HeatPumpAirToWaterHeatingSpeedData>().size());
    EXPECT_EQ(2, m2.getConcreteModelObjects<CurveBiquadratic>().size());
    EXPECT_EQ(1, m2.getConcreteModelObjects<CurveQuadratic>().size());
    auto rmed = awhpHCSpeedClone2.remove();
    EXPECT_EQ(4u, rmed.size());
    EXPECT_EQ(0, m2.getConcreteModelObjects<HeatPumpAirToWaterHeatingSpeedData>().size());
    EXPECT_EQ(0, m2.getConcreteModelObjects<CurveBiquadratic>().size());
    EXPECT_EQ(0, m2.getConcreteModelObjects<CurveQuadratic>().size());
  }

  auto rmed = awhpHCSpeed.remove();
  EXPECT_EQ(1u, rmed.size());
  EXPECT_EQ(1, m.getConcreteModelObjects<HeatPumpAirToWaterHeatingSpeedData>().size());
  EXPECT_EQ(2, m.getConcreteModelObjects<CurveBiquadratic>().size());
  EXPECT_EQ(1, m.getConcreteModelObjects<CurveQuadratic>().size());
  EXPECT_EQ(cap, awhpHCSpeedClone.ratedHeatingCapacity().get());
  EXPECT_EQ(cop, awhpHCSpeedClone.ratedCOPforHeating());
  EXPECT_EQ(capFT, awhpHCSpeedClone.normalizedHeatingCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(eirFT, awhpHCSpeedClone.heatingEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(eirFPLR, awhpHCSpeedClone.heatingEnergyInputRatioFunctionofPLRCurve());

  rmed = awhpHCSpeedClone.remove();
  EXPECT_EQ(4u, rmed.size());
  EXPECT_EQ(0, m.getConcreteModelObjects<HeatPumpAirToWaterHeatingSpeedData>().size());
  EXPECT_EQ(0, m.getConcreteModelObjects<CurveBiquadratic>().size());
  EXPECT_EQ(0, m.getConcreteModelObjects<CurveQuadratic>().size());
}

TEST_F(ModelFixture, HeatPumpAirToWaterHeatingSpeedData_RemoveParentModelObjectList) {
  Model m;

  HeatPumpAirToWaterHeating awhp(m);
  HeatPumpAirToWaterHeating awhp2(m);

  HeatPumpAirToWaterHeatingSpeedData speed1(m);
  HeatPumpAirToWaterHeatingSpeedData speed2(m);

  // Test convenience method
  EXPECT_EQ(0, speed1.heatPumpAirToWaterHeatings().size());
  EXPECT_EQ(0, speed2.heatPumpAirToWaterHeatings().size());

  EXPECT_TRUE(awhp.addSpeed(speed1));
  EXPECT_EQ(1, speed1.heatPumpAirToWaterHeatings().size());
  EXPECT_EQ(0, speed2.heatPumpAirToWaterHeatings().size());

  EXPECT_TRUE(awhp2.addSpeed(speed1));
  EXPECT_EQ(2, speed1.heatPumpAirToWaterHeatings().size());
  EXPECT_EQ(0, speed2.heatPumpAirToWaterHeatings().size());

  EXPECT_TRUE(awhp.addSpeed(speed2));
  EXPECT_EQ(2, speed1.heatPumpAirToWaterHeatings().size());
  EXPECT_EQ(1, speed2.heatPumpAirToWaterHeatings().size());

  EXPECT_TRUE(awhp2.addSpeed(speed2));
  EXPECT_EQ(2, speed1.heatPumpAirToWaterHeatings().size());
  EXPECT_EQ(2, speed2.heatPumpAirToWaterHeatings().size());

  {
    const std::vector<HeatPumpAirToWaterHeatingSpeedData> speeds{speed1, speed2};
    EXPECT_EQ(speeds, awhp.speeds());
    EXPECT_EQ(speeds, awhp2.speeds());
  }

  speed1.remove();
  {
    const std::vector<HeatPumpAirToWaterHeatingSpeedData> speeds{speed2};
    EXPECT_EQ(speeds, awhp.speeds());
    EXPECT_EQ(speeds, awhp2.speeds());
  }

  awhp.remove();
  EXPECT_EQ(1, speed2.heatPumpAirToWaterHeatings().size());
}
