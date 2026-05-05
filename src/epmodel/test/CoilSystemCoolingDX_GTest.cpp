/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed_Impl.hpp"
#include "../ModelObject/CoilSystemCoolingDX.hpp"
#include "../ModelObject/CoilSystemCoolingDX_Impl.hpp"

#include <utilities/idd/CoilSystem_Cooling_DX_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilSystemCoolingDX_DefaultConstructor) {
  Model model;
  CoilSystemCoolingDX coilSystem(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::CoilSystem_Cooling_DX), coilSystem.iddObject().type());
  EXPECT_FALSE(coilSystem.nameString().empty());
}

TEST_F(EPModelFixture, CoilSystemCoolingDX_ScalarAccessors_RoundTrip) {
  Model model;
  CoilSystemCoolingDX system(model);

  const auto coolingCoilObjectTypeChoices = CoilSystemCoolingDX::coolingCoilObjectTypeValues();
  EXPECT_FALSE(coolingCoilObjectTypeChoices.empty());
  EXPECT_TRUE(std::find(coolingCoilObjectTypeChoices.begin(), coolingCoilObjectTypeChoices.end(), "Coil:Cooling:DX:SingleSpeed")
              != coolingCoilObjectTypeChoices.end());
  ASSERT_GE(coolingCoilObjectTypeChoices.size(), 2u);

  const auto dehumidificationChoices = CoilSystemCoolingDX::dehumidificationControlTypeValues();
  EXPECT_FALSE(dehumidificationChoices.empty());
  EXPECT_TRUE(std::find(dehumidificationChoices.begin(), dehumidificationChoices.end(), "None") != dehumidificationChoices.end());

  EXPECT_TRUE(system.setCoolingCoilObjectType("Coil:Cooling:DX:SingleSpeed"));
  EXPECT_EQ("Coil:Cooling:DX:SingleSpeed", system.coolingCoilObjectType());

  EXPECT_TRUE(system.isDehumidificationControlTypeDefaulted());
  EXPECT_EQ("None", system.dehumidificationControlType());
  EXPECT_TRUE(system.setDehumidificationControlType("Multimode"));
  EXPECT_EQ("Multimode", system.dehumidificationControlType());
  EXPECT_FALSE(system.isDehumidificationControlTypeDefaulted());
  system.resetDehumidificationControlType();
  EXPECT_TRUE(system.isDehumidificationControlTypeDefaulted());
  EXPECT_EQ("None", system.dehumidificationControlType());

  EXPECT_TRUE(system.isRunonSensibleLoadDefaulted());
  EXPECT_TRUE(system.runonSensibleLoad());
  EXPECT_TRUE(system.setRunonSensibleLoad(false));
  EXPECT_FALSE(system.runonSensibleLoad());
  EXPECT_FALSE(system.isRunonSensibleLoadDefaulted());
  system.resetRunonSensibleLoad();
  EXPECT_TRUE(system.isRunonSensibleLoadDefaulted());
  EXPECT_TRUE(system.runonSensibleLoad());

  EXPECT_TRUE(system.isRunonLatentLoadDefaulted());
  EXPECT_FALSE(system.runonLatentLoad());
  EXPECT_TRUE(system.setRunonLatentLoad(true));
  EXPECT_TRUE(system.runonLatentLoad());
  EXPECT_FALSE(system.isRunonLatentLoadDefaulted());
  system.resetRunonLatentLoad();
  EXPECT_TRUE(system.isRunonLatentLoadDefaulted());
  EXPECT_FALSE(system.runonLatentLoad());

  EXPECT_TRUE(system.isUseOutdoorAirDXCoolingCoilDefaulted());
  EXPECT_FALSE(system.useOutdoorAirDXCoolingCoil());
  EXPECT_TRUE(system.setUseOutdoorAirDXCoolingCoil(true));
  EXPECT_TRUE(system.useOutdoorAirDXCoolingCoil());
  EXPECT_FALSE(system.isUseOutdoorAirDXCoolingCoilDefaulted());
  system.resetUseOutdoorAirDXCoolingCoil();
  EXPECT_TRUE(system.isUseOutdoorAirDXCoolingCoilDefaulted());
  EXPECT_FALSE(system.useOutdoorAirDXCoolingCoil());

  EXPECT_TRUE(system.isOutdoorAirDXCoolingCoilLeavingMinimumAirTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(2.0, system.outdoorAirDXCoolingCoilLeavingMinimumAirTemperature());
  EXPECT_TRUE(system.setOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature(4.2));
  EXPECT_DOUBLE_EQ(4.2, system.outdoorAirDXCoolingCoilLeavingMinimumAirTemperature());
  EXPECT_FALSE(system.isOutdoorAirDXCoolingCoilLeavingMinimumAirTemperatureDefaulted());
  EXPECT_FALSE(system.setOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature(8.0));
  system.resetOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature();
  EXPECT_TRUE(system.isOutdoorAirDXCoolingCoilLeavingMinimumAirTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(2.0, system.outdoorAirDXCoolingCoilLeavingMinimumAirTemperature());
}

TEST_F(EPModelFixture, CoilSystemCoolingDX_ImplOnlyNavigation) {
  Model model;
  CoilCoolingDXSingleSpeed coil(model);
  CoilSystemCoolingDX system(model);

  ASSERT_TRUE(system.setCoolingCoilObjectType("Coil:Cooling:DX:SingleSpeed"));
  ASSERT_TRUE(system.setPointer(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilName, coil.handle()));

  auto systemImpl = system.getImpl<openstudio::epmodel::detail::CoilSystemCoolingDX_Impl>();
  ASSERT_TRUE(systemImpl);
  auto coilFromSystem = systemImpl->coolingCoil();
  ASSERT_TRUE(coilFromSystem);
  EXPECT_EQ(coil.cast<ModelObject>(), *coilFromSystem);

  auto coilImpl = coil.getImpl<openstudio::epmodel::detail::CoilCoolingDXSingleSpeed_Impl>();
  ASSERT_TRUE(coilImpl);
  auto systemFromCoil = coilImpl->coilSystemCoolingDX();
  ASSERT_TRUE(systemFromCoil);
  EXPECT_EQ(system, *systemFromCoil);
}
