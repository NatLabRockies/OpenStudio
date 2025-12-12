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

#include "../../model/EvaporativeFluidCoolerTwoSpeed.hpp"
#include "../../model/EvaporativeFluidCoolerTwoSpeed_Impl.hpp"
#include "../../model/ScheduleCompact.hpp"
#include "../../model/PlantLoop.hpp"
#include "../../model/Node.hpp"

#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
// E+ FieldEnums
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/EvaporativeFluidCooler_TwoSpeed_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_EvaporativeFluidCoolerTwoSpeed) {

  ForwardTranslator ft;

  Model m;

  EvaporativeFluidCoolerTwoSpeed evaporativeFluidCoolerTwoSpeed(m);
  PlantLoop plantLoop(m);
  Node supplyOutletNode = plantLoop.supplyOutletNode();
  evaporativeFluidCoolerTwoSpeed.addToNode(supplyOutletNode);

  evaporativeFluidCoolerTwoSpeed.setName("My EvaporativeFluidCoolerTwoSpeed");

  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setHighFanSpeedAirFlowRate(1.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setHighFanSpeedFanPower(2.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setLowFanSpeedAirFlowRate(3.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setLowFanSpeedAirFlowRateSizingFactor(4.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setLowFanSpeedFanPower(5.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setLowFanSpeedFanPowerSizingFactor(6.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setDesignSprayWaterFlowRate(7.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setPerformanceInputMethod("StandardDesignCapacity"));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setOutdoorAirInletNodeName(
    "Outdoor Air Inlet Node Name"));  // FIXME: this gets translated as "" even though there's a setter?
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setHeatRejectionCapacityandNominalCapacitySizingRatio(8.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setHighSpeedStandardDesignCapacity(9.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setLowSpeedStandardDesignCapacity(10.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setLowSpeedStandardCapacitySizingFactor(11.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setHighFanSpeedUfactorTimesAreaValue(12.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setLowFanSpeedUfactorTimesAreaValue(13.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setLowFanSpeedUFactorTimesAreaSizingFactor(14.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setDesignWaterFlowRate(15.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setHighSpeedUserSpecifiedDesignCapacity(16.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setLowSpeedUserSpecifiedDesignCapacity(17.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setLowSpeedUserSpecifiedDesignCapacitySizingFactor(18.0));
  evaporativeFluidCoolerTwoSpeed.autosizeDesignEnteringWaterTemperature();
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setDesignEnteringAirTemperature(19.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setDesignEnteringAirWetbulbTemperature(20.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setHighSpeedSizingFactor(21.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setEvaporationLossMode("LossFactor"));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setEvaporationLossFactor(22.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setDriftLossPercent(23.0));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setBlowdownCalculationMode("ScheduledRate"));
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setBlowdownConcentrationRatio(24.0));
  ScheduleCompact blowdownMakeupWaterUsageSchedule(m);
  EXPECT_TRUE(evaporativeFluidCoolerTwoSpeed.setBlowdownMakeupWaterUsageSchedule(blowdownMakeupWaterUsageSchedule));

  const Workspace w = ft.translateModel(m);
  const auto idfObjs = w.getObjectsByType(IddObjectType::EvaporativeFluidCooler_TwoSpeed);
  ASSERT_EQ(1u, idfObjs.size());
  const auto& idfObject = idfObjs.front();

  EXPECT_EQ(evaporativeFluidCoolerTwoSpeed.nameString(), idfObject.getString(EvaporativeFluidCooler_TwoSpeedFields::Name).get());
  EXPECT_EQ(evaporativeFluidCoolerTwoSpeed.inletModelObject().get().nameString(),
            idfObject.getString(EvaporativeFluidCooler_TwoSpeedFields::WaterInletNodeName).get());
  EXPECT_EQ(evaporativeFluidCoolerTwoSpeed.outletModelObject().get().nameString(),
            idfObject.getString(EvaporativeFluidCooler_TwoSpeedFields::WaterOutletNodeName).get());
  EXPECT_EQ(1.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate).get());
  EXPECT_EQ(2.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedFanPower).get());
  EXPECT_EQ(3.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate).get());
  EXPECT_EQ(4.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor).get());
  EXPECT_EQ(5.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedFanPower).get());
  EXPECT_EQ(6.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor).get());
  EXPECT_EQ(7.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::DesignSprayWaterFlowRate).get());
  EXPECT_EQ("StandardDesignCapacity", idfObject.getString(EvaporativeFluidCooler_TwoSpeedFields::PerformanceInputMethod).get());
  EXPECT_TRUE(idfObject.isEmpty(EvaporativeFluidCooler_TwoSpeedFields::OutdoorAirInletNodeName));
  EXPECT_EQ(8.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::HeatRejectionCapacityandNominalCapacitySizingRatio).get());
  EXPECT_EQ(9.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::HighSpeedStandardDesignCapacity).get());
  EXPECT_EQ(10.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::LowSpeedStandardDesignCapacity).get());
  EXPECT_EQ(11.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::LowSpeedStandardCapacitySizingFactor).get());
  EXPECT_EQ(12.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue).get());
  EXPECT_EQ(13.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue).get());
  EXPECT_EQ(14.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor).get());
  EXPECT_EQ(15.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::DesignWaterFlowRate).get());
  EXPECT_EQ(16.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::HighSpeedUserSpecifiedDesignCapacity).get());
  EXPECT_EQ(17.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::LowSpeedUserSpecifiedDesignCapacity).get());
  EXPECT_EQ(18.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::LowSpeedUserSpecifiedDesignCapacitySizingFactor).get());
  EXPECT_EQ("Autosize", idfObject.getString(EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringWaterTemperature).get());
  EXPECT_EQ(19.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringAirTemperature).get());
  EXPECT_EQ(20.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::DesignEnteringAirWetbulbTemperature).get());
  EXPECT_EQ(21.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::HighSpeedSizingFactor).get());
  EXPECT_EQ("LossFactor", idfObject.getString(EvaporativeFluidCooler_TwoSpeedFields::EvaporationLossMode).get());
  EXPECT_EQ(22.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::EvaporationLossFactor).get());
  EXPECT_EQ(23.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::DriftLossPercent).get());
  EXPECT_EQ("ScheduledRate", idfObject.getString(EvaporativeFluidCooler_TwoSpeedFields::BlowdownCalculationMode).get());
  EXPECT_EQ(24.0, idfObject.getDouble(EvaporativeFluidCooler_TwoSpeedFields::BlowdownConcentrationRatio).get());
  EXPECT_EQ(blowdownMakeupWaterUsageSchedule.nameString(),
            idfObject.getString(EvaporativeFluidCooler_TwoSpeedFields::BlowdownMakeupWaterUsageScheduleName).get());
  EXPECT_TRUE(idfObject.isEmpty(EvaporativeFluidCooler_TwoSpeedFields::SupplyWaterStorageTankName));
}
