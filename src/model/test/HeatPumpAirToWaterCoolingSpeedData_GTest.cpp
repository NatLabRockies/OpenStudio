/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelFixture.hpp"

#include "../HeatPumpAirToWaterCoolingSpeedData.hpp"
#include "../HeatPumpAirToWaterCoolingSpeedData_Impl.hpp"

#include "../HeatPumpAirToWaterCooling.hpp"

#include "../Model.hpp"
#include "../Curve.hpp"
#include "../Curve_Impl.hpp"
#include "../CurveBiquadratic.hpp"
#include "../CurveBiquadratic_Impl.hpp"
#include "../CurveQuadratic.hpp"
#include "../CurveQuadratic_Impl.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, HeatPumpAirToWaterCoolingSpeedData_GettersSetters) {
  Model m;
  HeatPumpAirToWaterCoolingSpeedData heatPumpAirToWaterCoolingSpeedData(m);

  heatPumpAirToWaterCoolingSpeedData.setName("My HeatPumpAirToWaterCoolingSpeedData");

  // Rated Cooling Capacity: Required Double, ctor defaults to autosize
  EXPECT_TRUE(heatPumpAirToWaterCoolingSpeedData.isRatedCoolingCapacityAutosized());
  // Set
  EXPECT_TRUE(heatPumpAirToWaterCoolingSpeedData.setRatedCoolingCapacity(40000.0));
  ASSERT_TRUE(heatPumpAirToWaterCoolingSpeedData.ratedCoolingCapacity());
  EXPECT_EQ(40000.0, heatPumpAirToWaterCoolingSpeedData.ratedCoolingCapacity().get());
  EXPECT_FALSE(heatPumpAirToWaterCoolingSpeedData.isRatedCoolingCapacityAutosized());
  // Bad Value
  EXPECT_FALSE(heatPumpAirToWaterCoolingSpeedData.setRatedCoolingCapacity(-10.0));
  ASSERT_TRUE(heatPumpAirToWaterCoolingSpeedData.ratedCoolingCapacity());
  EXPECT_EQ(40000.0, heatPumpAirToWaterCoolingSpeedData.ratedCoolingCapacity().get());
  EXPECT_FALSE(heatPumpAirToWaterCoolingSpeedData.isRatedCoolingCapacityAutosized());
  // Autosize
  heatPumpAirToWaterCoolingSpeedData.autosizeRatedCoolingCapacity();
  EXPECT_TRUE(heatPumpAirToWaterCoolingSpeedData.isRatedCoolingCapacityAutosized());

  // Rated COP for Cooling: Required Double, defaults to 3.0
  EXPECT_EQ(3.0, heatPumpAirToWaterCoolingSpeedData.ratedCOPforCooling());
  // Set
  EXPECT_TRUE(heatPumpAirToWaterCoolingSpeedData.setRatedCOPforCooling(4.0));
  EXPECT_EQ(4.0, heatPumpAirToWaterCoolingSpeedData.ratedCOPforCooling());
  // Bad Value
  EXPECT_FALSE(heatPumpAirToWaterCoolingSpeedData.setRatedCOPforCooling(-10.0));
  EXPECT_EQ(4.0, heatPumpAirToWaterCoolingSpeedData.ratedCOPforCooling());

  // Normalized Cooling Capacity Function of Temperature Curve Name: Required Object
  auto oriCapFT = heatPumpAirToWaterCoolingSpeedData.normalizedCoolingCapacityFunctionofTemperatureCurve();
  CurveBiquadratic capFT(m);
  EXPECT_TRUE(heatPumpAirToWaterCoolingSpeedData.setNormalizedCoolingCapacityFunctionofTemperatureCurve(capFT));
  EXPECT_EQ(capFT, heatPumpAirToWaterCoolingSpeedData.normalizedCoolingCapacityFunctionofTemperatureCurve());
  EXPECT_NE(capFT, oriCapFT);

  // Cooling Energy Input Ratio Function of Temperature Curve Name: Required Object
  auto oriEIRFT = heatPumpAirToWaterCoolingSpeedData.coolingEnergyInputRatioFunctionofTemperatureCurve();
  CurveBiquadratic eirFT(m);
  EXPECT_TRUE(heatPumpAirToWaterCoolingSpeedData.setCoolingEnergyInputRatioFunctionofTemperatureCurve(eirFT));
  EXPECT_EQ(eirFT, heatPumpAirToWaterCoolingSpeedData.coolingEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_NE(eirFT, oriEIRFT);

  // Cooling Energy Input Ratio Function of PLR Curve Name: Required Object
  auto oriEIRFPLR = heatPumpAirToWaterCoolingSpeedData.coolingEnergyInputRatioFunctionofPLRCurve();
  CurveQuadratic eirFPLR(m);
  EXPECT_TRUE(heatPumpAirToWaterCoolingSpeedData.setCoolingEnergyInputRatioFunctionofPLRCurve(eirFPLR));
  EXPECT_EQ(eirFPLR, heatPumpAirToWaterCoolingSpeedData.coolingEnergyInputRatioFunctionofPLRCurve());
  EXPECT_NE(eirFPLR, oriEIRFPLR);
}

TEST_F(ModelFixture, HeatPumpAirToWaterCoolingSpeedData_CreateInvalid) {
  {
    Model m;
    CurveQuadratic univariate(m);
    CurveBiquadratic bivariate(m);

    EXPECT_EQ(1, univariate.numVariables());
    EXPECT_EQ(2, bivariate.numVariables());

    // Valid
    {
      HeatPumpAirToWaterCoolingSpeedData awhpHCSpeed(m, bivariate, bivariate, univariate);
      EXPECT_EQ(1, m.getConcreteModelObjects<HeatPumpAirToWaterCoolingSpeedData>().size());
      EXPECT_EQ(1, m.getConcreteModelObjects<CurveBiquadratic>().size());
      EXPECT_EQ(1, m.getConcreteModelObjects<CurveQuadratic>().size());
    }

    // Invalid: wrong curve type
    EXPECT_THROW({ HeatPumpAirToWaterCoolingSpeedData(m, bivariate, univariate, univariate); }, openstudio::Exception);
    EXPECT_THROW({ HeatPumpAirToWaterCoolingSpeedData(m, univariate, bivariate, univariate); }, openstudio::Exception);
    EXPECT_THROW({ HeatPumpAirToWaterCoolingSpeedData(m, bivariate, bivariate, bivariate); }, openstudio::Exception);
    EXPECT_EQ(1, m.getConcreteModelObjects<HeatPumpAirToWaterCoolingSpeedData>().size());
    EXPECT_EQ(1, m.getConcreteModelObjects<CurveBiquadratic>().size());
    EXPECT_EQ(1, m.getConcreteModelObjects<CurveQuadratic>().size());
  }

  // There is a nasty side effect that curves may be removed if ctor failed and they are not used anywhere else, so we'll want to call
  // ModelObject::remove() and not HeatPumpAirToWaterCoolingSpeedData::remove() (=ParentObject::remove) in the ctor
  {
    Model m;
    CurveQuadratic univariate(m);
    CurveBiquadratic bivariate(m);
    EXPECT_EQ(0, univariate.directUseCount());
    EXPECT_EQ(0, bivariate.directUseCount());

    EXPECT_THROW({ HeatPumpAirToWaterCoolingSpeedData(m, bivariate, univariate, univariate); }, openstudio::Exception);
    EXPECT_EQ(0, m.getConcreteModelObjects<HeatPumpAirToWaterCoolingSpeedData>().size());
    // Curves should not be removed in case the expliclit ctor with curves failed
    EXPECT_EQ(1, m.getConcreteModelObjects<CurveBiquadratic>().size());
    EXPECT_EQ(1, m.getConcreteModelObjects<CurveQuadratic>().size());
  }
}

TEST_F(ModelFixture, HeatPumpAirToWaterCoolingSpeedData_clone_remove) {

  Model m;
  CurveBiquadratic capFT(m);
  CurveBiquadratic eirFT(m);
  CurveQuadratic eirFPLR(m);

  constexpr double cap = 40000.0;
  constexpr double cop = 4.0;

  HeatPumpAirToWaterCoolingSpeedData awhpHCSpeed(m, capFT, eirFT, eirFPLR);
  EXPECT_TRUE(awhpHCSpeed.setRatedCoolingCapacity(cap));
  EXPECT_TRUE(awhpHCSpeed.setRatedCOPforCooling(cop));

  EXPECT_EQ(1, m.getConcreteModelObjects<HeatPumpAirToWaterCoolingSpeedData>().size());
  EXPECT_EQ(2, m.getConcreteModelObjects<CurveBiquadratic>().size());
  EXPECT_EQ(1, m.getConcreteModelObjects<CurveQuadratic>().size());

  auto awhpHCSpeedClone = awhpHCSpeed.clone(m).cast<HeatPumpAirToWaterCoolingSpeedData>();
  EXPECT_EQ(cap, awhpHCSpeedClone.ratedCoolingCapacity().get());
  EXPECT_EQ(cop, awhpHCSpeedClone.ratedCOPforCooling());
  EXPECT_EQ(capFT, awhpHCSpeedClone.normalizedCoolingCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(eirFT, awhpHCSpeedClone.coolingEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(eirFPLR, awhpHCSpeedClone.coolingEnergyInputRatioFunctionofPLRCurve());

  EXPECT_EQ(2, m.getConcreteModelObjects<HeatPumpAirToWaterCoolingSpeedData>().size());
  EXPECT_EQ(2, m.getConcreteModelObjects<CurveBiquadratic>().size());
  EXPECT_EQ(1, m.getConcreteModelObjects<CurveQuadratic>().size());

  {
    Model m2;
    auto awhpHCSpeedClone2 = awhpHCSpeed.clone(m2).cast<HeatPumpAirToWaterCoolingSpeedData>();
    EXPECT_EQ(cap, awhpHCSpeedClone2.ratedCoolingCapacity().get());
    EXPECT_EQ(cop, awhpHCSpeedClone2.ratedCOPforCooling());
    EXPECT_NE(capFT, awhpHCSpeedClone2.normalizedCoolingCapacityFunctionofTemperatureCurve());
    EXPECT_NE(eirFT, awhpHCSpeedClone2.coolingEnergyInputRatioFunctionofTemperatureCurve());
    EXPECT_NE(eirFPLR, awhpHCSpeedClone2.coolingEnergyInputRatioFunctionofPLRCurve());

    EXPECT_EQ(1, m2.getConcreteModelObjects<HeatPumpAirToWaterCoolingSpeedData>().size());
    EXPECT_EQ(2, m2.getConcreteModelObjects<CurveBiquadratic>().size());
    EXPECT_EQ(1, m2.getConcreteModelObjects<CurveQuadratic>().size());
    auto rmed = awhpHCSpeedClone2.remove();
    EXPECT_EQ(4u, rmed.size());
    EXPECT_EQ(0, m2.getConcreteModelObjects<HeatPumpAirToWaterCoolingSpeedData>().size());
    EXPECT_EQ(0, m2.getConcreteModelObjects<CurveBiquadratic>().size());
    EXPECT_EQ(0, m2.getConcreteModelObjects<CurveQuadratic>().size());
  }

  auto rmed = awhpHCSpeed.remove();
  EXPECT_EQ(1u, rmed.size());
  EXPECT_EQ(1, m.getConcreteModelObjects<HeatPumpAirToWaterCoolingSpeedData>().size());
  EXPECT_EQ(2, m.getConcreteModelObjects<CurveBiquadratic>().size());
  EXPECT_EQ(1, m.getConcreteModelObjects<CurveQuadratic>().size());
  EXPECT_EQ(cap, awhpHCSpeedClone.ratedCoolingCapacity().get());
  EXPECT_EQ(cop, awhpHCSpeedClone.ratedCOPforCooling());
  EXPECT_EQ(capFT, awhpHCSpeedClone.normalizedCoolingCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(eirFT, awhpHCSpeedClone.coolingEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(eirFPLR, awhpHCSpeedClone.coolingEnergyInputRatioFunctionofPLRCurve());

  rmed = awhpHCSpeedClone.remove();
  EXPECT_EQ(4u, rmed.size());
  EXPECT_EQ(0, m.getConcreteModelObjects<HeatPumpAirToWaterCoolingSpeedData>().size());
  EXPECT_EQ(0, m.getConcreteModelObjects<CurveBiquadratic>().size());
  EXPECT_EQ(0, m.getConcreteModelObjects<CurveQuadratic>().size());
}

TEST_F(ModelFixture, HeatPumpAirToWaterCoolingSpeedData_RemoveParentModelObjectList) {
  Model m;

  HeatPumpAirToWaterCooling awhp(m);
  HeatPumpAirToWaterCooling awhp2(m);

  HeatPumpAirToWaterCoolingSpeedData speed1(m);
  HeatPumpAirToWaterCoolingSpeedData speed2(m);

  // Test convenience method
  EXPECT_EQ(0, speed1.heatPumpAirToWaterCoolings().size());
  EXPECT_EQ(0, speed2.heatPumpAirToWaterCoolings().size());

  EXPECT_TRUE(awhp.addSpeed(speed1));
  EXPECT_EQ(1, speed1.heatPumpAirToWaterCoolings().size());
  EXPECT_EQ(0, speed2.heatPumpAirToWaterCoolings().size());

  EXPECT_TRUE(awhp2.addSpeed(speed1));
  EXPECT_EQ(2, speed1.heatPumpAirToWaterCoolings().size());
  EXPECT_EQ(0, speed2.heatPumpAirToWaterCoolings().size());

  EXPECT_TRUE(awhp.addSpeed(speed2));
  EXPECT_EQ(2, speed1.heatPumpAirToWaterCoolings().size());
  EXPECT_EQ(1, speed2.heatPumpAirToWaterCoolings().size());

  EXPECT_TRUE(awhp2.addSpeed(speed2));
  EXPECT_EQ(2, speed1.heatPumpAirToWaterCoolings().size());
  EXPECT_EQ(2, speed2.heatPumpAirToWaterCoolings().size());

  {
    const std::vector<HeatPumpAirToWaterCoolingSpeedData> speeds{speed1, speed2};
    EXPECT_EQ(speeds, awhp.speeds());
    EXPECT_EQ(speeds, awhp2.speeds());
  }

  speed1.remove();
  {
    const std::vector<HeatPumpAirToWaterCoolingSpeedData> speeds{speed2};
    EXPECT_EQ(speeds, awhp.speeds());
    EXPECT_EQ(speeds, awhp2.speeds());
  }

  awhp.remove();
  EXPECT_EQ(1, speed2.heatPumpAirToWaterCoolings().size());
}
