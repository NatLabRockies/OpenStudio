/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/PlantEquipmentOperationSchemes.hpp"
#include "../ModelObject/PlantEquipmentOperationSchemes_Impl.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationUncontrolled.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationCoolingLoad.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationHeatingLoad.hpp"
#include "../PlantEquipmentOperationScheme/PlantEquipmentOperationOutdoorDryBulb.hpp"
#include "../Schedule/ScheduleConstant.hpp"

#include <utilities/idd/PlantEquipmentOperationSchemes_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PlantEquipmentOperationSchemes_DefaultConstructor) {
  Model model;
  PlantEquipmentOperationSchemes schemes(model);

  EXPECT_EQ(PlantEquipmentOperationSchemes::iddObjectType(), schemes.iddObject().type());
  EXPECT_FALSE(schemes.plantEquipmentOperationHeatingLoad());
  EXPECT_FALSE(schemes.plantEquipmentOperationHeatingLoadSchedule());
  EXPECT_FALSE(schemes.plantEquipmentOperationCoolingLoad());
  EXPECT_FALSE(schemes.primaryPlantEquipmentOperationScheme());
  EXPECT_FALSE(schemes.componentSetpointOperationSchemeSchedule());

  auto values = PlantEquipmentOperationSchemes::controlSchemeObjectTypeValues();
  EXPECT_FALSE(values.empty());
}

TEST_F(EPModelFixture, PlantEquipmentOperationSchemes_ReadOnlyTypedAccessorsReflectImplMutation) {
  Model model;
  PlantEquipmentOperationSchemes schemes(model);
  auto impl = schemes.getImpl<detail::PlantEquipmentOperationSchemes_Impl>();

  PlantEquipmentOperationHeatingLoad heating(model);
  PlantEquipmentOperationCoolingLoad cooling(model);
  PlantEquipmentOperationOutdoorDryBulb primary(model);
  ScheduleConstant heatingSchedule(model);
  ScheduleConstant coolingSchedule(model);
  ScheduleConstant primarySchedule(model);
  ScheduleConstant componentSchedule(model);

  ASSERT_TRUE(impl->setPlantEquipmentOperationHeatingLoad(heating));
  ASSERT_TRUE(impl->setPlantEquipmentOperationHeatingLoadSchedule(heatingSchedule));
  ASSERT_TRUE(impl->setPlantEquipmentOperationCoolingLoad(cooling));
  ASSERT_TRUE(impl->setPlantEquipmentOperationCoolingLoadSchedule(coolingSchedule));
  ASSERT_TRUE(impl->setPrimaryPlantEquipmentOperationScheme(primary));
  ASSERT_TRUE(impl->setPrimaryPlantEquipmentOperationSchemeSchedule(primarySchedule));
  ASSERT_TRUE(impl->setComponentSetpointOperationSchemeSchedule(componentSchedule));

  auto heatingResult = schemes.plantEquipmentOperationHeatingLoad();
  ASSERT_TRUE(heatingResult);
  EXPECT_EQ(heating.handle(), heatingResult->handle());

  auto coolingResult = schemes.plantEquipmentOperationCoolingLoad();
  ASSERT_TRUE(coolingResult);
  EXPECT_EQ(cooling.handle(), coolingResult->handle());

  auto primaryResult = schemes.primaryPlantEquipmentOperationScheme();
  ASSERT_TRUE(primaryResult);
  EXPECT_EQ(primary.handle(), primaryResult->handle());

  auto heatingScheduleResult = schemes.plantEquipmentOperationHeatingLoadSchedule();
  ASSERT_TRUE(heatingScheduleResult);
  EXPECT_EQ(heatingSchedule.handle(), heatingScheduleResult->handle());

  auto coolingScheduleResult = schemes.plantEquipmentOperationCoolingLoadSchedule();
  ASSERT_TRUE(coolingScheduleResult);
  EXPECT_EQ(coolingSchedule.handle(), coolingScheduleResult->handle());

  auto primaryScheduleResult = schemes.primaryPlantEquipmentOperationSchemeSchedule();
  ASSERT_TRUE(primaryScheduleResult);
  EXPECT_EQ(primarySchedule.handle(), primaryScheduleResult->handle());

  auto componentScheduleResult = schemes.componentSetpointOperationSchemeSchedule();
  ASSERT_TRUE(componentScheduleResult);
  EXPECT_EQ(componentSchedule.handle(), componentScheduleResult->handle());
}

TEST_F(EPModelFixture, PlantEquipmentOperationSchemes_HeatingAndCoolingSchedulesCanExistWithoutSchemes) {
  Model model;
  PlantEquipmentOperationSchemes schemes(model);
  auto impl = schemes.getImpl<detail::PlantEquipmentOperationSchemes_Impl>();
  ScheduleConstant heatingSchedule(model);
  ScheduleConstant coolingSchedule(model);

  ASSERT_TRUE(impl->setPlantEquipmentOperationHeatingLoadSchedule(heatingSchedule));
  ASSERT_TRUE(impl->setPlantEquipmentOperationCoolingLoadSchedule(coolingSchedule));

  EXPECT_FALSE(schemes.plantEquipmentOperationHeatingLoad());
  EXPECT_FALSE(schemes.plantEquipmentOperationCoolingLoad());

  auto heatingScheduleResult = schemes.plantEquipmentOperationHeatingLoadSchedule();
  ASSERT_TRUE(heatingScheduleResult);
  EXPECT_EQ(heatingSchedule.handle(), heatingScheduleResult->handle());

  auto coolingScheduleResult = schemes.plantEquipmentOperationCoolingLoadSchedule();
  ASSERT_TRUE(coolingScheduleResult);
  EXPECT_EQ(coolingSchedule.handle(), coolingScheduleResult->handle());
}

TEST_F(EPModelFixture, PlantEquipmentOperationSchemes_PrimaryRejectsHeatingLoadType) {
  Model model;
  PlantEquipmentOperationSchemes schemes(model);
  auto impl = schemes.getImpl<detail::PlantEquipmentOperationSchemes_Impl>();
  PlantEquipmentOperationHeatingLoad heating(model);

  EXPECT_FALSE(impl->setPrimaryPlantEquipmentOperationScheme(heating));
  EXPECT_FALSE(schemes.primaryPlantEquipmentOperationScheme());
}

TEST_F(EPModelFixture, PlantEquipmentOperationSchemes_PrimaryScheduleCanExistWithoutPrimaryScheme) {
  Model model;
  PlantEquipmentOperationSchemes schemes(model);
  auto impl = schemes.getImpl<detail::PlantEquipmentOperationSchemes_Impl>();
  ScheduleConstant primarySchedule(model);

  ASSERT_TRUE(impl->setPrimaryPlantEquipmentOperationSchemeSchedule(primarySchedule));
  EXPECT_FALSE(schemes.primaryPlantEquipmentOperationScheme());

  auto primaryScheduleResult = schemes.primaryPlantEquipmentOperationSchemeSchedule();
  ASSERT_TRUE(primaryScheduleResult);
  EXPECT_EQ(primarySchedule.handle(), primaryScheduleResult->handle());
}

TEST_F(EPModelFixture, PlantEquipmentOperationSchemes_SetPrimaryUsesCanonicalPrimarySlot) {
  Model model;
  PlantEquipmentOperationSchemes schemes(model);
  auto impl = schemes.getImpl<detail::PlantEquipmentOperationSchemes_Impl>();
  PlantEquipmentOperationOutdoorDryBulb originalPrimary(model);
  PlantEquipmentOperationUncontrolled newPrimary(model);

  auto firstGroup = schemes.pushExtensibleGroup();
  ASSERT_FALSE(firstGroup.empty());
  ASSERT_TRUE(firstGroup.setString(openstudio::PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType,
                                   originalPrimary.iddObject().name()));
  ASSERT_TRUE(firstGroup.setString(openstudio::PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeName, originalPrimary.nameString()));

  auto secondGroup = schemes.pushExtensibleGroup();
  ASSERT_FALSE(secondGroup.empty());
  ASSERT_TRUE(secondGroup.setString(openstudio::PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType,
                                    newPrimary.iddObject().name()));
  ASSERT_TRUE(secondGroup.setString(openstudio::PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeName, newPrimary.nameString()));

  ASSERT_TRUE(impl->setPrimaryPlantEquipmentOperationScheme(newPrimary));

  auto primaryResult = schemes.primaryPlantEquipmentOperationScheme();
  ASSERT_TRUE(primaryResult);
  EXPECT_EQ(newPrimary.handle(), primaryResult->handle());
}

TEST_F(EPModelFixture, PlantEquipmentOperationSchemes_CanonicalizeMergesPrimaryScheduleOnlyAndSchemeRows) {
  Model model;
  PlantEquipmentOperationSchemes schemes(model);
  ScheduleConstant primarySchedule(model);
  PlantEquipmentOperationOutdoorDryBulb primary(model);

  auto scheduleOnlyGroup = schemes.pushExtensibleGroup();
  ASSERT_FALSE(scheduleOnlyGroup.empty());
  ASSERT_TRUE(scheduleOnlyGroup.setString(openstudio::PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType,
                                          "PlantEquipmentOperation:Uncontrolled"));
  ASSERT_TRUE(scheduleOnlyGroup.setString(openstudio::PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeScheduleName,
                                          primarySchedule.nameString()));

  auto schemeOnlyGroup = schemes.pushExtensibleGroup();
  ASSERT_FALSE(schemeOnlyGroup.empty());
  ASSERT_TRUE(schemeOnlyGroup.setString(openstudio::PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeObjectType,
                                        primary.iddObject().name()));
  ASSERT_TRUE(schemeOnlyGroup.setString(openstudio::PlantEquipmentOperationSchemesExtensibleFields::ControlSchemeName, primary.nameString()));

  auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);

  auto primaryResult = schemes.primaryPlantEquipmentOperationScheme();
  ASSERT_TRUE(primaryResult);
  EXPECT_EQ(primary.handle(), primaryResult->handle());

  auto primaryScheduleResult = schemes.primaryPlantEquipmentOperationSchemeSchedule();
  ASSERT_TRUE(primaryScheduleResult);
  EXPECT_EQ(primarySchedule.handle(), primaryScheduleResult->handle());
}
