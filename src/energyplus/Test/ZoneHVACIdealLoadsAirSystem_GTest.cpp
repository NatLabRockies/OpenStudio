/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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
*  written permission from Alliance for Sustainable Energy, LLC.
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

#include "../../model/ZoneHVACIdealLoadsAirSystem.hpp"
#include "../../model/ZoneHVACIdealLoadsAirSystem_Impl.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"
#include "../../model/Node.hpp"
#include "../../model/PortList.hpp"
#include "../../model/ThermalZone.hpp"
#include "../../model/Space.hpp"
#include "../../model/ScheduleCompact.hpp"
#include "../../model/DesignSpecificationOutdoorAir.hpp"

#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
// E+ FieldEnums
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_IdealLoadsAirSystem_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_ZoneHVACIdealLoadsAirSystem) {

  ForwardTranslator ft;

  Model m;

  ZoneHVACIdealLoadsAirSystem zoneHVACIdealLoadsAirSystem(m);

  zoneHVACIdealLoadsAirSystem.setName("My ZoneHVACIdealLoadsAirSystem");
  Schedule availabilitySchedule = m.alwaysOnDiscreteSchedule();
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setAvailabilitySchedule(availabilitySchedule));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMaximumHeatingSupplyAirTemperature(1.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMinimumCoolingSupplyAirTemperature(2.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMaximumHeatingSupplyAirHumidityRatio(3.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMinimumCoolingSupplyAirHumidityRatio(4.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setHeatingLimit("LimitFlowRate"));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMaximumHeatingAirFlowRate(5.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMaximumSensibleHeatingCapacity(6.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setCoolingLimit("LimitFlowRate"));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMaximumCoolingAirFlowRate(7.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMaximumTotalCoolingCapacity(8.0));
  ScheduleCompact heatingAvailabilitySchedule(m);
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setHeatingAvailabilitySchedule(heatingAvailabilitySchedule));
  ScheduleCompact coolingAvailabilitySchedule(m);
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setCoolingAvailabilitySchedule(coolingAvailabilitySchedule));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setDehumidificationControlType("Humidistat"));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setCoolingSensibleHeatRatio(0.1));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setHumidificationControlType("Humidistat"));

  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setDemandControlledVentilationType("OccupancySchedule"));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setOutdoorAirEconomizerType("DifferentialDryBulb"));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setHeatRecoveryType("Sensible"));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setSensibleHeatRecoveryEffectiveness(0.2));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setLatentHeatRecoveryEffectiveness(0.3));
  ScheduleCompact heatingFuelEfficiencySchedule(m);
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setHeatingFuelEfficiencySchedule(heatingFuelEfficiencySchedule));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setHeatingFuelType("DistrictHeatingWater"));
  ScheduleCompact coolingFuelEfficiencySchedule(m);
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setCoolingFuelEfficiencySchedule(coolingFuelEfficiencySchedule));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setCoolingFuelType("DistrictCooling"));

  // Need to be in a thermal zone to be translated, with at least one space
  ThermalZone z(m);
  zoneHVACIdealLoadsAirSystem.addToThermalZone(z);
  Space s(m);
  s.setThermalZone(z);
  DesignSpecificationOutdoorAir dsoa(m);
  EXPECT_TRUE(s.setDesignSpecificationOutdoorAir(dsoa));

  z.inletPortList().modelObjects()[0].setName("Zone Air Inlet Node");
  z.exhaustPortList().modelObjects()[0].setName("Zone Air Exhaust Node");

  const Workspace w = ft.translateModel(m);
  const auto idfObjs = w.getObjectsByType(IddObjectType::ZoneHVAC_IdealLoadsAirSystem);
  ASSERT_EQ(1u, idfObjs.size());
  const auto& idfObject = idfObjs.front();

  EXPECT_EQ(zoneHVACIdealLoadsAirSystem.nameString(), idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::Name).get());
  EXPECT_EQ(availabilitySchedule.nameString(), idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::AvailabilityScheduleName).get());
  EXPECT_EQ("Zone Air Inlet Node", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::ZoneSupplyAirNodeName).get());
  EXPECT_EQ("Zone Air Exhaust Node", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::ZoneExhaustAirNodeName).get());
  EXPECT_EQ("", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::SystemInletAirNodeName).get());
  EXPECT_EQ(1.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirTemperature).get());
  EXPECT_EQ(2.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirTemperature).get());
  EXPECT_EQ(3.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirHumidityRatio).get());
  EXPECT_EQ(4.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirHumidityRatio).get());
  EXPECT_EQ("LimitFlowRate", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::HeatingLimit).get());
  EXPECT_EQ(5.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingAirFlowRate).get());
  EXPECT_EQ(6.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumSensibleHeatingCapacity).get());
  EXPECT_EQ("LimitFlowRate", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingLimit).get());
  EXPECT_EQ(7.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumCoolingAirFlowRate).get());
  EXPECT_EQ(8.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumTotalCoolingCapacity).get());
  EXPECT_EQ(heatingAvailabilitySchedule.nameString(), idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::HeatingAvailabilityScheduleName).get());
  EXPECT_EQ(coolingAvailabilitySchedule.nameString(), idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingAvailabilityScheduleName).get());
  EXPECT_EQ("Humidistat", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::DehumidificationControlType).get());
  EXPECT_EQ(0.1, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::CoolingSensibleHeatRatio).get());
  EXPECT_EQ("Humidistat", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::HumidificationControlType).get());
  EXPECT_EQ(dsoa.nameString(), idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::DesignSpecificationOutdoorAirObjectName).get());
  EXPECT_EQ("OccupancySchedule", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::DemandControlledVentilationType).get());
  EXPECT_EQ("DifferentialDryBulb", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::OutdoorAirEconomizerType).get());
  EXPECT_EQ("Sensible", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::HeatRecoveryType).get());
  EXPECT_EQ(0.2, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::SensibleHeatRecoveryEffectiveness).get());
  EXPECT_EQ(0.3, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::LatentHeatRecoveryEffectiveness).get());
  EXPECT_EQ("", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::DesignSpecificationZoneHVACSizingObjectName).get());
  EXPECT_EQ(heatingFuelEfficiencySchedule.nameString(),
            idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::HeatingFuelEfficiencyScheduleName).get());
  EXPECT_EQ("DistrictHeatingWater", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::HeatingFuelType).get());
  EXPECT_EQ(coolingFuelEfficiencySchedule.nameString(),
            idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingFuelEfficiencyScheduleName).get());
  EXPECT_EQ("DistrictCooling", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingFuelType).get());
}

TEST_F(EnergyPlusFixture, ForwardTranslator_ZoneHVACIdealLoadsAirSystem_HardcodedDSOA) {

  ForwardTranslator ft;

  Model m;

  ZoneHVACIdealLoadsAirSystem zoneHVACIdealLoadsAirSystem(m);

  zoneHVACIdealLoadsAirSystem.setName("My ZoneHVACIdealLoadsAirSystem");
  Schedule availabilitySchedule = m.alwaysOnDiscreteSchedule();
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setAvailabilitySchedule(availabilitySchedule));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMaximumHeatingSupplyAirTemperature(1.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMinimumCoolingSupplyAirTemperature(2.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMaximumHeatingSupplyAirHumidityRatio(3.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMinimumCoolingSupplyAirHumidityRatio(4.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setHeatingLimit("LimitFlowRate"));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMaximumHeatingAirFlowRate(5.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMaximumSensibleHeatingCapacity(6.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setCoolingLimit("LimitFlowRate"));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMaximumCoolingAirFlowRate(7.0));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setMaximumTotalCoolingCapacity(8.0));
  ScheduleCompact heatingAvailabilitySchedule(m);
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setHeatingAvailabilitySchedule(heatingAvailabilitySchedule));
  ScheduleCompact coolingAvailabilitySchedule(m);
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setCoolingAvailabilitySchedule(coolingAvailabilitySchedule));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setDehumidificationControlType("Humidistat"));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setCoolingSensibleHeatRatio(0.1));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setHumidificationControlType("Humidistat"));
  DesignSpecificationOutdoorAir dsoa(m);
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setDesignSpecificationOutdoorAirObject(dsoa));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setDemandControlledVentilationType("OccupancySchedule"));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setOutdoorAirEconomizerType("DifferentialDryBulb"));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setHeatRecoveryType("Sensible"));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setSensibleHeatRecoveryEffectiveness(0.2));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setLatentHeatRecoveryEffectiveness(0.3));
  ScheduleCompact heatingFuelEfficiencySchedule(m);
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setHeatingFuelEfficiencySchedule(heatingFuelEfficiencySchedule));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setHeatingFuelType("DistrictHeatingWater"));
  ScheduleCompact coolingFuelEfficiencySchedule(m);
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setCoolingFuelEfficiencySchedule(coolingFuelEfficiencySchedule));
  EXPECT_TRUE(zoneHVACIdealLoadsAirSystem.setCoolingFuelType("DistrictCooling"));

  // Need to be in a thermal zone to be translated, with at least one space
  ThermalZone z(m);
  zoneHVACIdealLoadsAirSystem.addToThermalZone(z);
  Space s(m);
  s.setThermalZone(z);

  z.inletPortList().modelObjects()[0].setName("Zone Air Inlet Node");
  z.exhaustPortList().modelObjects()[0].setName("Zone Air Exhaust Node");

  const Workspace w = ft.translateModel(m);
  const auto idfObjs = w.getObjectsByType(IddObjectType::ZoneHVAC_IdealLoadsAirSystem);
  ASSERT_EQ(1u, idfObjs.size());
  const auto& idfObject = idfObjs.front();

  EXPECT_EQ(zoneHVACIdealLoadsAirSystem.nameString(), idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::Name).get());
  EXPECT_EQ(availabilitySchedule.nameString(), idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::AvailabilityScheduleName).get());
  EXPECT_EQ("Zone Air Inlet Node", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::ZoneSupplyAirNodeName).get());
  EXPECT_EQ("Zone Air Exhaust Node", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::ZoneExhaustAirNodeName).get());
  EXPECT_EQ("", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::SystemInletAirNodeName).get());
  EXPECT_EQ(1.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirTemperature).get());
  EXPECT_EQ(2.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirTemperature).get());
  EXPECT_EQ(3.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirHumidityRatio).get());
  EXPECT_EQ(4.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirHumidityRatio).get());
  EXPECT_EQ("LimitFlowRate", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::HeatingLimit).get());
  EXPECT_EQ(5.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingAirFlowRate).get());
  EXPECT_EQ(6.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumSensibleHeatingCapacity).get());
  EXPECT_EQ("LimitFlowRate", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingLimit).get());
  EXPECT_EQ(7.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumCoolingAirFlowRate).get());
  EXPECT_EQ(8.0, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::MaximumTotalCoolingCapacity).get());
  EXPECT_EQ(heatingAvailabilitySchedule.nameString(), idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::HeatingAvailabilityScheduleName).get());
  EXPECT_EQ(coolingAvailabilitySchedule.nameString(), idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingAvailabilityScheduleName).get());
  EXPECT_EQ("Humidistat", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::DehumidificationControlType).get());
  EXPECT_EQ(0.1, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::CoolingSensibleHeatRatio).get());
  EXPECT_EQ("Humidistat", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::HumidificationControlType).get());
  EXPECT_EQ(dsoa.nameString(), idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::DesignSpecificationOutdoorAirObjectName).get());
  EXPECT_EQ("OccupancySchedule", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::DemandControlledVentilationType).get());
  EXPECT_EQ("DifferentialDryBulb", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::OutdoorAirEconomizerType).get());
  EXPECT_EQ("Sensible", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::HeatRecoveryType).get());
  EXPECT_EQ(0.2, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::SensibleHeatRecoveryEffectiveness).get());
  EXPECT_EQ(0.3, idfObject.getDouble(ZoneHVAC_IdealLoadsAirSystemFields::LatentHeatRecoveryEffectiveness).get());
  EXPECT_EQ("", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::DesignSpecificationZoneHVACSizingObjectName).get());
  EXPECT_EQ(heatingFuelEfficiencySchedule.nameString(),
            idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::HeatingFuelEfficiencyScheduleName).get());
  EXPECT_EQ("DistrictHeatingWater", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::HeatingFuelType).get());
  EXPECT_EQ(coolingFuelEfficiencySchedule.nameString(),
            idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingFuelEfficiencyScheduleName).get());
  EXPECT_EQ("DistrictCooling", idfObject.getString(ZoneHVAC_IdealLoadsAirSystemFields::CoolingFuelType).get());
}
