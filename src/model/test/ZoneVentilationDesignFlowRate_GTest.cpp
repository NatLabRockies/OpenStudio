/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Energy Innovation, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Energy Innovation, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#include "ModelFixture.hpp"

#include "../ZoneVentilationDesignFlowRate.hpp"
#include "../ZoneVentilationDesignFlowRate_Impl.hpp"
#include "../ScheduleConstant.hpp"
#include "../Schedule.hpp"
#include "../ThermalZone.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, ZoneVentilationDesignFlowRate) {
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  ASSERT_EXIT(
    {
      Model m;
      ZoneVentilationDesignFlowRate zv(m);

      exit(0);
    },
    ::testing::ExitedWithCode(0), "");
}

TEST_F(ModelFixture, ZoneVentilationDesignFlowRate_GettersSetters) {
  Model m;

  ZoneVentilationDesignFlowRate zoneVentilationDesignFlowRate(m);

  zoneVentilationDesignFlowRate.setName("My ZoneVentilationDesignFlowRate");

  // Schedule Name: Required Object
  Schedule schedule = m.alwaysOnDiscreteSchedule();
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setSchedule(schedule));
  EXPECT_EQ(schedule, zoneVentilationDesignFlowRate.schedule());

  // Design Flow Rate: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setDesignFlowRate(0.5));
  EXPECT_EQ(0.5, zoneVentilationDesignFlowRate.designFlowRate());
  ASSERT_EQ("Flow/Zone", zoneVentilationDesignFlowRate.designFlowRateCalculationMethod());
  ASSERT_FALSE(zoneVentilationDesignFlowRate.flowRateperZoneFloorArea());
  ASSERT_FALSE(zoneVentilationDesignFlowRate.flowRateperPerson());
  ASSERT_FALSE(zoneVentilationDesignFlowRate.airChangesperHour());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setDesignFlowRate(-10.0));
  EXPECT_EQ(0.5, zoneVentilationDesignFlowRate.designFlowRate());

  // Flow Rate per Zone Floor Area: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setFlowRateperZoneFloorArea(0.6));
  EXPECT_EQ(0.6, zoneVentilationDesignFlowRate.flowRateperZoneFloorArea());
  ASSERT_EQ("Flow/Area", zoneVentilationDesignFlowRate.designFlowRateCalculationMethod());
  ASSERT_FALSE(zoneVentilationDesignFlowRate.designFlowRate());
  ASSERT_FALSE(zoneVentilationDesignFlowRate.flowRateperPerson());
  ASSERT_FALSE(zoneVentilationDesignFlowRate.airChangesperHour());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setFlowRateperZoneFloorArea(-10.0));
  EXPECT_EQ(0.6, zoneVentilationDesignFlowRate.flowRateperZoneFloorArea());

  // Flow Rate per Person: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setFlowRateperPerson(0.7));
  EXPECT_EQ(0.7, zoneVentilationDesignFlowRate.flowRateperPerson());
  ASSERT_EQ("Flow/Person", zoneVentilationDesignFlowRate.designFlowRateCalculationMethod());
  ASSERT_FALSE(zoneVentilationDesignFlowRate.designFlowRate());
  ASSERT_FALSE(zoneVentilationDesignFlowRate.flowRateperZoneFloorArea());
  ASSERT_FALSE(zoneVentilationDesignFlowRate.airChangesperHour());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setFlowRateperPerson(-10.0));
  EXPECT_EQ(0.7, zoneVentilationDesignFlowRate.flowRateperPerson());

  // Air Changes per Hour: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setAirChangesperHour(0.8));
  EXPECT_EQ(0.8, zoneVentilationDesignFlowRate.airChangesperHour());
  ASSERT_EQ("AirChanges/Hour", zoneVentilationDesignFlowRate.designFlowRateCalculationMethod());
  ASSERT_FALSE(zoneVentilationDesignFlowRate.designFlowRate());
  ASSERT_FALSE(zoneVentilationDesignFlowRate.flowRateperZoneFloorArea());
  ASSERT_FALSE(zoneVentilationDesignFlowRate.flowRateperPerson());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setAirChangesperHour(-10.0));
  EXPECT_EQ(0.8, zoneVentilationDesignFlowRate.airChangesperHour());

  // Ventilation Type: Required String
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setVentilationType("Natural"));
  EXPECT_EQ("Natural", zoneVentilationDesignFlowRate.ventilationType());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setVentilationType("BADENUM"));
  EXPECT_EQ("Natural", zoneVentilationDesignFlowRate.ventilationType());

  // Fan Pressure Rise: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setFanPressureRise(1.0));
  EXPECT_EQ(1.0, zoneVentilationDesignFlowRate.fanPressureRise());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setFanPressureRise(-10.0));
  EXPECT_EQ(1.0, zoneVentilationDesignFlowRate.fanPressureRise());

  // Fan Total Efficiency: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setFanTotalEfficiency(1.1));
  EXPECT_EQ(1.1, zoneVentilationDesignFlowRate.fanTotalEfficiency());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setFanTotalEfficiency(-10.0));
  EXPECT_EQ(1.1, zoneVentilationDesignFlowRate.fanTotalEfficiency());

  // Constant Term Coefficient: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setConstantTermCoefficient(1.2));
  EXPECT_EQ(1.2, zoneVentilationDesignFlowRate.constantTermCoefficient());

  // Temperature Term Coefficient: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setTemperatureTermCoefficient(1.3));
  EXPECT_EQ(1.3, zoneVentilationDesignFlowRate.temperatureTermCoefficient());

  // Velocity Term Coefficient: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setVelocityTermCoefficient(1.4));
  EXPECT_EQ(1.4, zoneVentilationDesignFlowRate.velocityTermCoefficient());

  // Velocity Squared Term Coefficient: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setVelocitySquaredTermCoefficient(1.5));
  EXPECT_EQ(1.5, zoneVentilationDesignFlowRate.velocitySquaredTermCoefficient());

  // Minimum Indoor Temperature: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMinimumIndoorTemperature(88.235));
  EXPECT_EQ(88.235, zoneVentilationDesignFlowRate.minimumIndoorTemperature());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setMinimumIndoorTemperature(-110.0));
  EXPECT_EQ(88.235, zoneVentilationDesignFlowRate.minimumIndoorTemperature());

  // Minimum Indoor Temperature Schedule Name: Optional Object
  ScheduleConstant minimumIndoorTemperatureSchedule(m);
  minimumIndoorTemperatureSchedule.setValue(10.0);
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMinimumIndoorTemperatureSchedule(minimumIndoorTemperatureSchedule));
  ASSERT_TRUE(zoneVentilationDesignFlowRate.minimumIndoorTemperatureSchedule());
  EXPECT_EQ(minimumIndoorTemperatureSchedule, zoneVentilationDesignFlowRate.minimumIndoorTemperatureSchedule().get());

  // Maximum Indoor Temperature: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMaximumIndoorTemperature(89.474));
  EXPECT_EQ(89.474, zoneVentilationDesignFlowRate.maximumIndoorTemperature());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setMaximumIndoorTemperature(-110.0));
  EXPECT_EQ(89.474, zoneVentilationDesignFlowRate.maximumIndoorTemperature());

  // Maximum Indoor Temperature Schedule Name: Optional Object
  ScheduleConstant maximumIndoorTemperatureSchedule(m);
  maximumIndoorTemperatureSchedule.setValue(30.0);
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMaximumIndoorTemperatureSchedule(maximumIndoorTemperatureSchedule));
  ASSERT_TRUE(zoneVentilationDesignFlowRate.maximumIndoorTemperatureSchedule());
  EXPECT_EQ(maximumIndoorTemperatureSchedule, zoneVentilationDesignFlowRate.maximumIndoorTemperatureSchedule().get());

  // Delta Temperature: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setDeltaTemperature(-98.0));
  EXPECT_EQ(-98.0, zoneVentilationDesignFlowRate.deltaTemperature());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setDeltaTemperature(-110.0));
  EXPECT_EQ(-98.0, zoneVentilationDesignFlowRate.deltaTemperature());

  // Delta Temperature Schedule Name: Optional Object
  ScheduleConstant deltaTemperatureSchedule(m);
  deltaTemperatureSchedule.setValue(3.0);
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setDeltaTemperatureSchedule(deltaTemperatureSchedule));
  ASSERT_TRUE(zoneVentilationDesignFlowRate.deltaTemperatureSchedule());
  EXPECT_EQ(deltaTemperatureSchedule, zoneVentilationDesignFlowRate.deltaTemperatureSchedule().get());

  // Minimum Outdoor Temperature: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMinimumOutdoorTemperature(91.304));
  EXPECT_EQ(91.304, zoneVentilationDesignFlowRate.minimumOutdoorTemperature());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setMinimumOutdoorTemperature(-110.0));
  EXPECT_EQ(91.304, zoneVentilationDesignFlowRate.minimumOutdoorTemperature());

  // Minimum Outdoor Temperature Schedule Name: Optional Object
  ScheduleConstant minimumOutdoorTemperatureSchedule(m);
  minimumOutdoorTemperatureSchedule.setValue(-10.0);
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMinimumOutdoorTemperatureSchedule(minimumOutdoorTemperatureSchedule));
  ASSERT_TRUE(zoneVentilationDesignFlowRate.minimumOutdoorTemperatureSchedule());
  EXPECT_EQ(minimumOutdoorTemperatureSchedule, zoneVentilationDesignFlowRate.minimumOutdoorTemperatureSchedule().get());

  // Maximum Outdoor Temperature: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMaximumOutdoorTemperature(92.0));
  EXPECT_EQ(92.0, zoneVentilationDesignFlowRate.maximumOutdoorTemperature());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setMaximumOutdoorTemperature(-110.0));
  EXPECT_EQ(92.0, zoneVentilationDesignFlowRate.maximumOutdoorTemperature());

  // Maximum Outdoor Temperature Schedule Name: Optional Object
  ScheduleConstant maximumOutdoorTemperatureSchedule(m);
  maximumOutdoorTemperatureSchedule.setValue(20.0);
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMaximumOutdoorTemperatureSchedule(maximumOutdoorTemperatureSchedule));
  ASSERT_TRUE(zoneVentilationDesignFlowRate.maximumOutdoorTemperatureSchedule());
  EXPECT_EQ(maximumOutdoorTemperatureSchedule, zoneVentilationDesignFlowRate.maximumOutdoorTemperatureSchedule().get());

  // Maximum Wind Speed: Required Double
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMaximumWindSpeed(38.519));
  EXPECT_EQ(38.519, zoneVentilationDesignFlowRate.maximumWindSpeed());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setMaximumWindSpeed(-10.0));
  EXPECT_EQ(38.519, zoneVentilationDesignFlowRate.maximumWindSpeed());

  // Density Basis: Required String
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setDensityBasis("Outdoor"));
  EXPECT_EQ("Outdoor", zoneVentilationDesignFlowRate.densityBasis());
  // Bad Value
  EXPECT_FALSE(zoneVentilationDesignFlowRate.setDensityBasis("BADENUM"));
  EXPECT_EQ("Outdoor", zoneVentilationDesignFlowRate.densityBasis());
}

TEST_F(ModelFixture, ZoneVentilationDesignFlowRate_AddToThermalZone) {

  Model m;
  ThermalZone z(m);
  ZoneVentilationDesignFlowRate zv(m);
  EXPECT_TRUE(zv.addToThermalZone(z));
  ASSERT_TRUE(zv.thermalZone());
  EXPECT_EQ(z, zv.thermalZone().get());

  zv.removeFromThermalZone();
  EXPECT_FALSE(zv.thermalZone());
}
