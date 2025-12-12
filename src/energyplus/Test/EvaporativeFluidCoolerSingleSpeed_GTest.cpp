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

#include "../../model/EvaporativeFluidCoolerSingleSpeed.hpp"
#include "../../model/EvaporativeFluidCoolerSingleSpeed_Impl.hpp"
#include "../../model/ScheduleCompact.hpp"
#include "../../model/PlantLoop.hpp"
#include "../../model/Node.hpp"

#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
// E+ FieldEnums
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/EvaporativeFluidCooler_SingleSpeed_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_EvaporativeFluidCoolerSingleSpeed) {

  ForwardTranslator ft;

  Model m;

  EvaporativeFluidCoolerSingleSpeed evaporativeFluidCoolerSingleSpeed(m);
  PlantLoop plantLoop(m);
  Node supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.addToNode(supplyOutletNode));

  evaporativeFluidCoolerSingleSpeed.setName("My EvaporativeFluidCoolerSingleSpeed");
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setDesignAirFlowRate(1.0));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setFanPoweratDesignAirFlowRate(2.0));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setDesignSprayWaterFlowRate(3.0));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setPerformanceInputMethod("StandardDesignCapacity"));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setHeatRejectionCapacityandNominalCapacitySizingRatio(4.0));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setStandardDesignCapacity(5.0));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setUfactorTimesAreaValueatDesignAirFlowRate(6.0));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setDesignWaterFlowRate(7.0));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setUserSpecifiedDesignCapacity(8.0));
  evaporativeFluidCoolerSingleSpeed.autosizeDesignEnteringWaterTemperature();
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setDesignEnteringAirTemperature(9.0));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setDesignEnteringAirWetbulbTemperature(10.0));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setCapacityControl("FluidBypass"));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setSizingFactor(11.0));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setEvaporationLossMode("LossFactor"));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setEvaporationLossFactor(12.0));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setDriftLossPercent(13.0));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setBlowdownCalculationMode("ScheduledRate"));
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setBlowdownConcentrationRatio(14.0));
  ScheduleCompact blowdownMakeupWaterUsageSchedule(m);
  EXPECT_TRUE(evaporativeFluidCoolerSingleSpeed.setBlowdownMakeupWaterUsageSchedule(blowdownMakeupWaterUsageSchedule));

  const Workspace w = ft.translateModel(m);
  const auto idfObjs = w.getObjectsByType(IddObjectType::EvaporativeFluidCooler_SingleSpeed);
  ASSERT_EQ(1u, idfObjs.size());
  const auto& idfObject = idfObjs.front();

  EXPECT_EQ(evaporativeFluidCoolerSingleSpeed.nameString(), idfObject.getString(EvaporativeFluidCooler_SingleSpeedFields::Name).get());
  EXPECT_EQ(evaporativeFluidCoolerSingleSpeed.inletModelObject().get().nameString(),
            idfObject.getString(EvaporativeFluidCooler_SingleSpeedFields::WaterInletNodeName).get());
  EXPECT_EQ(evaporativeFluidCoolerSingleSpeed.outletModelObject().get().nameString(),
            idfObject.getString(EvaporativeFluidCooler_SingleSpeedFields::WaterOutletNodeName).get());
  EXPECT_EQ(1.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRate).get());
  EXPECT_EQ(2.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower).get());
  EXPECT_EQ(3.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::DesignSprayWaterFlowRate).get());
  EXPECT_EQ("StandardDesignCapacity", idfObject.getString(EvaporativeFluidCooler_SingleSpeedFields::PerformanceInputMethod).get());
  EXPECT_TRUE(idfObject.isEmpty(EvaporativeFluidCooler_SingleSpeedFields::OutdoorAirInletNodeName));
  EXPECT_EQ(4.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio).get());
  EXPECT_EQ(5.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::StandardDesignCapacity).get());
  EXPECT_EQ(6.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue).get());
  EXPECT_EQ(7.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::DesignWaterFlowRate).get());
  EXPECT_EQ(8.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::UserSpecifiedDesignCapacity).get());
  EXPECT_EQ("Autosize", idfObject.getString(EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringWaterTemperature).get());
  EXPECT_EQ(9.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringAirTemperature).get());
  EXPECT_EQ(10.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::DesignEnteringAirWetbulbTemperature).get());
  EXPECT_EQ("FluidBypass", idfObject.getString(EvaporativeFluidCooler_SingleSpeedFields::CapacityControl).get());
  EXPECT_EQ(11.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::SizingFactor).get());
  EXPECT_EQ("LossFactor", idfObject.getString(EvaporativeFluidCooler_SingleSpeedFields::EvaporationLossMode).get());
  EXPECT_EQ(12.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::EvaporationLossFactor).get());
  EXPECT_EQ(13.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::DriftLossPercent).get());
  EXPECT_EQ("ScheduledRate", idfObject.getString(EvaporativeFluidCooler_SingleSpeedFields::BlowdownCalculationMode).get());
  EXPECT_EQ(14.0, idfObject.getDouble(EvaporativeFluidCooler_SingleSpeedFields::BlowdownConcentrationRatio).get());
  EXPECT_EQ(blowdownMakeupWaterUsageSchedule.nameString(),
            idfObject.getString(EvaporativeFluidCooler_SingleSpeedFields::BlowdownMakeupWaterUsageScheduleName).get());
  EXPECT_TRUE(idfObject.isEmpty(EvaporativeFluidCooler_SingleSpeedFields::SupplyWaterStorageTankName));
}
