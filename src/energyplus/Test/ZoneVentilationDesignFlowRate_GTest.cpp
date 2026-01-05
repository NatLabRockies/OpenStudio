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

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"

#include "../../model/ZoneVentilationDesignFlowRate.hpp"
#include "../../model/ZoneVentilationDesignFlowRate_Impl.hpp"
#include "../../model/ThermalZone.hpp"
#include "../../model/ThermalZone_Impl.hpp"
#include "../../model/Space.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/ScheduleConstant.hpp"

#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
// E+ FieldEnums
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneVentilation_DesignFlowRate_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_ZoneVentilationDesignFlowRate) {

  ForwardTranslator ft;

  Model m;

  ZoneVentilationDesignFlowRate zoneVentilationDesignFlowRate(m);

  // No zone, not translated
  {
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idf_zones(w.getObjectsByType(IddObjectType::ZoneVentilation_DesignFlowRate));
    EXPECT_EQ(0u, idf_zones.size());
  }

  ThermalZone z(m);
  Space s(m);
  s.setThermalZone(z);
  EXPECT_TRUE(zoneVentilationDesignFlowRate.addToThermalZone(z));
  zoneVentilationDesignFlowRate.setName("My ZoneVentilationDesignFlowRate");
  Schedule schedule = m.alwaysOnDiscreteSchedule();
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setSchedule(schedule));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setDesignFlowRate(0.5));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setVentilationType("Natural"));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setFanPressureRise(1.0));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setFanTotalEfficiency(1.1));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setConstantTermCoefficient(1.2));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setTemperatureTermCoefficient(1.3));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setVelocityTermCoefficient(1.4));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setVelocitySquaredTermCoefficient(1.5));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMinimumIndoorTemperature(88.235));
  ScheduleConstant minimumIndoorTemperatureSchedule(m);
  minimumIndoorTemperatureSchedule.setValue(10.0);
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMinimumIndoorTemperatureSchedule(minimumIndoorTemperatureSchedule));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMaximumIndoorTemperature(89.474));
  ScheduleConstant maximumIndoorTemperatureSchedule(m);
  maximumIndoorTemperatureSchedule.setValue(30.0);
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMaximumIndoorTemperatureSchedule(maximumIndoorTemperatureSchedule));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setDeltaTemperature(-98.0));
  ScheduleConstant deltaTemperatureSchedule(m);
  deltaTemperatureSchedule.setValue(3.0);
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setDeltaTemperatureSchedule(deltaTemperatureSchedule));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMinimumOutdoorTemperature(91.304));
  ScheduleConstant minimumOutdoorTemperatureSchedule(m);
  minimumOutdoorTemperatureSchedule.setValue(-10.0);
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMinimumOutdoorTemperatureSchedule(minimumOutdoorTemperatureSchedule));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMaximumOutdoorTemperature(92.0));
  ScheduleConstant maximumOutdoorTemperatureSchedule(m);
  maximumOutdoorTemperatureSchedule.setValue(20.0);
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMaximumOutdoorTemperatureSchedule(maximumOutdoorTemperatureSchedule));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setMaximumWindSpeed(38.519));
  EXPECT_TRUE(zoneVentilationDesignFlowRate.setDensityBasis("Outdoor"));

  const Workspace w = ft.translateModel(m);
  const auto idfObjs = w.getObjectsByType(IddObjectType::ZoneVentilation_DesignFlowRate);
  ASSERT_EQ(1u, idfObjs.size());
  const auto& idfObject = idfObjs.front();

  EXPECT_EQ(zoneVentilationDesignFlowRate.nameString(), idfObject.getString(ZoneVentilation_DesignFlowRateFields::Name).get());
  EXPECT_EQ(z.nameString(), idfObject.getString(ZoneVentilation_DesignFlowRateFields::ZoneorZoneListorSpaceorSpaceListName).get());
  EXPECT_EQ(schedule.nameString(), idfObject.getString(ZoneVentilation_DesignFlowRateFields::ScheduleName).get());
  EXPECT_EQ("Flow/Zone", idfObject.getString(ZoneVentilation_DesignFlowRateFields::DesignFlowRateCalculationMethod).get());
  EXPECT_EQ(0.5, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::DesignFlowRate).get());
  EXPECT_EQ(0.0, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::FlowRateperFloorArea).get());
  EXPECT_EQ(0.0, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::FlowRateperPerson).get());
  EXPECT_EQ(0.0, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::AirChangesperHour).get());
  EXPECT_EQ("Natural", idfObject.getString(ZoneVentilation_DesignFlowRateFields::VentilationType).get());
  EXPECT_EQ(1.0, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::FanPressureRise).get());
  EXPECT_EQ(1.1, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::FanTotalEfficiency).get());
  EXPECT_EQ(1.2, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::ConstantTermCoefficient).get());
  EXPECT_EQ(1.3, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::TemperatureTermCoefficient).get());
  EXPECT_EQ(1.4, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::VelocityTermCoefficient).get());
  EXPECT_EQ(1.5, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::VelocitySquaredTermCoefficient).get());
  EXPECT_EQ(88.235, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::MinimumIndoorTemperature).get());
  EXPECT_EQ(minimumIndoorTemperatureSchedule.nameString(),
            idfObject.getString(ZoneVentilation_DesignFlowRateFields::MinimumIndoorTemperatureScheduleName).get());
  EXPECT_EQ(89.474, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::MaximumIndoorTemperature).get());
  EXPECT_EQ(maximumIndoorTemperatureSchedule.nameString(),
            idfObject.getString(ZoneVentilation_DesignFlowRateFields::MaximumIndoorTemperatureScheduleName).get());
  EXPECT_EQ(-98.0, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::DeltaTemperature).get());
  EXPECT_EQ(deltaTemperatureSchedule.nameString(), idfObject.getString(ZoneVentilation_DesignFlowRateFields::DeltaTemperatureScheduleName).get());
  EXPECT_EQ(91.304, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::MinimumOutdoorTemperature).get());
  EXPECT_EQ(minimumOutdoorTemperatureSchedule.nameString(),
            idfObject.getString(ZoneVentilation_DesignFlowRateFields::MinimumOutdoorTemperatureScheduleName).get());
  EXPECT_EQ(92.0, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::MaximumOutdoorTemperature).get());
  EXPECT_EQ(maximumOutdoorTemperatureSchedule.nameString(),
            idfObject.getString(ZoneVentilation_DesignFlowRateFields::MaximumOutdoorTemperatureScheduleName).get());
  EXPECT_EQ(38.519, idfObject.getDouble(ZoneVentilation_DesignFlowRateFields::MaximumWindSpeed).get());
  EXPECT_EQ("Outdoor", idfObject.getString(ZoneVentilation_DesignFlowRateFields::DensityBasis).get());
}
