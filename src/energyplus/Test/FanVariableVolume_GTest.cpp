/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"
#include "../ReverseTranslator.hpp"

#include "../../model/FanVariableVolume.hpp"
#include "../../model/FanVariableVolume_Impl.hpp"

#include "../../model/Model.hpp"

#include "../../model/AirLoopHVAC.hpp"
#include "../../model/Node.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/ScheduleConstant.hpp"
#include "../../model/ScheduleConstant_Impl.hpp"

#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"

// E+ FieldEnums
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Fan_VariableVolume_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_FanVariableVolume_EndUseSubCategory) {

  Model m;

  FanVariableVolume fan(m);

  std::string endUse("Special Fan");
  fan.setEndUseSubcategory(endUse);

  // Assign it to a loop
  AirLoopHVAC a(m);
  Node supplyOutletNode = a.supplyOutletNode();
  fan.addToNode(supplyOutletNode);

  // ForwardTranslate
  ForwardTranslator ft;
  Workspace w = ft.translateModel(m);

  WorkspaceObjectVector idfObjs(w.getObjectsByType(IddObjectType::Fan_VariableVolume));
  ASSERT_EQ(1u, idfObjs.size());
  WorkspaceObject idf_fan(idfObjs[0]);

  // End Use Subcategory
  boost::optional<std::string> _idfEndUse = idf_fan.getString(Fan_VariableVolumeFields::EndUseSubcategory);
  ASSERT_TRUE(_idfEndUse);
  EXPECT_EQ(endUse, _idfEndUse.get());
}

// The Forward Translator should not translate fan if not used (by an AirLoopHVAC, or a ZoneHVACComponent )
TEST_F(EnergyPlusFixture, ForwardTranslator_FanVariableVolume_NotUsed) {

  Model m;

  FanVariableVolume fan(m);

  // ForwardTranslate
  ForwardTranslator ft;
  Workspace w = ft.translateModel(m);

  WorkspaceObjectVector idfObjs(w.getObjectsByType(IddObjectType::Fan_VariableVolume));
  EXPECT_EQ(0u, idfObjs.size());
}

TEST_F(EnergyPlusFixture, ReverseTranslator_FanVariableVolume) {

  ReverseTranslator rt;

  Workspace w(StrictnessLevel::Minimal, IddFileType::EnergyPlus);

  auto woFVV = w.addObject(IdfObject(IddObjectType::Fan_VariableVolume)).get();

  woFVV.setName("My FanVariableVolume");
  auto woavailabilitySchedule = w.addObject(IdfObject(IddObjectType::Schedule_Constant)).get();
  woavailabilitySchedule.setName("My availabilitySchedule");
  EXPECT_TRUE(woFVV.setPointer(Fan_VariableVolumeFields::AvailabilityScheduleName, woavailabilitySchedule.handle()));
  EXPECT_TRUE(woFVV.setDouble(Fan_VariableVolumeFields::FanTotalEfficiency, 0.75));
  EXPECT_TRUE(woFVV.setDouble(Fan_VariableVolumeFields::PressureRise, 0.4));
  // Autosize
  // EXPECT_TRUE(woFVV.setString(Fan_VariableVolumeFields::MaximumFlowRate, "Autosized"));
  EXPECT_TRUE(woFVV.setDouble(Fan_VariableVolumeFields::MaximumFlowRate, 0.5));
  EXPECT_TRUE(woFVV.setString(Fan_VariableVolumeFields::FanPowerMinimumFlowRateInputMethod, "Fraction"));
  EXPECT_TRUE(woFVV.setDouble(Fan_VariableVolumeFields::FanPowerMinimumFlowFraction, 0.875));
  EXPECT_TRUE(woFVV.setDouble(Fan_VariableVolumeFields::FanPowerMinimumAirFlowRate, 0.8));
  EXPECT_TRUE(woFVV.setDouble(Fan_VariableVolumeFields::MotorEfficiency, 0.9));
  EXPECT_TRUE(woFVV.setDouble(Fan_VariableVolumeFields::MotorInAirstreamFraction, 0.909));
  EXPECT_TRUE(woFVV.setDouble(Fan_VariableVolumeFields::FanPowerCoefficient1, 1.1));
  EXPECT_TRUE(woFVV.setDouble(Fan_VariableVolumeFields::FanPowerCoefficient2, 1.2));
  EXPECT_TRUE(woFVV.setDouble(Fan_VariableVolumeFields::FanPowerCoefficient3, 1.3));
  EXPECT_TRUE(woFVV.setDouble(Fan_VariableVolumeFields::FanPowerCoefficient4, 1.4));
  EXPECT_TRUE(woFVV.setDouble(Fan_VariableVolumeFields::FanPowerCoefficient5, 1.5));
  EXPECT_TRUE(woFVV.setString(Fan_VariableVolumeFields::AirInletNodeName, "FanVV Inlet Node Name"));
  EXPECT_TRUE(woFVV.setString(Fan_VariableVolumeFields::AirInletNodeName, "Fan VV Outlet Node Name"));
  EXPECT_TRUE(woFVV.setString(Fan_VariableVolumeFields::EndUseSubcategory, "Fan End Use Subcategory"));


  const Model m = rt.translateWorkspace(w);
  const auto modelObjects = m.getConcreteModelObjects<FanVariableVolume>();
  ASSERT_EQ(1u, modelObjects.size());

  const auto& modelObject = modelObjects.front();
  ASSERT_TRUE(modelObject.availabilitySchedule().optionalCast<ScheduleConstant>());
  EXPECT_EQ(woavailabilitySchedule.nameString(), modelObject.availabilitySchedule().nameString());
  EXPECT_EQ(0.75, modelObject.fanTotalEfficiency());
  EXPECT_EQ(0.4, modelObject.pressureRise());

  EXPECT_FALSE(modelObject.isMaximumFlowRateAutosized());
  ASSERT_TRUE(modelObject.maximumFlowRate());
  EXPECT_EQ(0.5, modelObject.maximumFlowRate().get());

  EXPECT_EQ("Fraction", modelObject.fanPowerMinimumFlowRateInputMethod());
  EXPECT_EQ(0.875, modelObject.fanPowerMinimumFlowFraction());

  ASSERT_TRUE(modelObject.fanPowerMinimumAirFlowRate());
  EXPECT_EQ(0.8, modelObject.fanPowerMinimumAirFlowRate().get());

  EXPECT_EQ(0.9, modelObject.motorEfficiency());
  EXPECT_EQ(0.909, modelObject.motorInAirstreamFraction());
  EXPECT_EQ(1.1, modelObject.fanPowerCoefficient1().get());
  EXPECT_EQ(1.2, modelObject.fanPowerCoefficient2().get());
  EXPECT_EQ(1.3, modelObject.fanPowerCoefficient3().get());
  EXPECT_EQ(1.4, modelObject.fanPowerCoefficient4().get());
  EXPECT_EQ(1.5, modelObject.fanPowerCoefficient5().get());
  EXPECT_EQ("Fan End Use Subcategory", modelObject.endUseSubcategory());
}
