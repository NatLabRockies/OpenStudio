/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../CoilCoolingDXSingleSpeed.hpp"
#include "../CoilCoolingDXSingleSpeed_Impl.hpp"
#include "../CoilSystemCoolingDX.hpp"
#include "../CoilSystemCoolingDX_Impl.hpp"

#include <utilities/idd/CoilSystem_Cooling_DX_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilSystemCoolingDX_DefaultConstructor) {
  Model model;
  CoilSystemCoolingDX coilSystem(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::CoilSystem_Cooling_DX), coilSystem.iddObject().type());
  EXPECT_FALSE(coilSystem.nameString().empty());
}

TEST_F(EPModelFixture, CoilSystemCoolingDX_ImplOnlyNavigation) {
  Model model;
  CoilCoolingDXSingleSpeed coil(model);
  CoilSystemCoolingDX system(model);

  ASSERT_TRUE(system.setString(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilObjectType, "Coil:Cooling:DX:SingleSpeed"));
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
