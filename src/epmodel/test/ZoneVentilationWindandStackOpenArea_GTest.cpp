/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneVentilationWindandStackOpenArea.hpp"
#include "../ZoneHVACComponent/ZoneVentilationWindandStackOpenArea_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/ZoneVentilation_WindandStackOpenArea_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedZoneVentilationFileRemoval
{
 public:
  explicit ScopedZoneVentilationFileRemoval(openstudio::path path) : m_path(std::move(path)) {}
  ~ScopedZoneVentilationFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueZoneVentilationPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, ZoneVentilationWindandStackOpenArea_DefaultConstructor) {
  Model model;
  ZoneVentilationWindandStackOpenArea ventilation(model);

  EXPECT_EQ(ZoneVentilationWindandStackOpenArea::iddObjectType(), ventilation.iddObject().type());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), ventilation.openingAreaFractionSchedule().handle());
  EXPECT_DOUBLE_EQ(0.0, ventilation.openingArea());
  EXPECT_FALSE(ventilation.openingEffectiveness());
  EXPECT_TRUE(ventilation.isOpeningEffectivenessAutocalculated());
  EXPECT_DOUBLE_EQ(0.0, ventilation.effectiveAngle());
  EXPECT_DOUBLE_EQ(0.0, ventilation.heightDifference());
  EXPECT_FALSE(ventilation.dischargeCoefficientforOpening());
  EXPECT_TRUE(ventilation.isDischargeCoefficientforOpeningAutocalculated());
  EXPECT_DOUBLE_EQ(-100.0, ventilation.minimumIndoorTemperature());
  EXPECT_DOUBLE_EQ(100.0, ventilation.maximumIndoorTemperature());
  EXPECT_DOUBLE_EQ(-100.0, ventilation.deltaTemperature());
  EXPECT_DOUBLE_EQ(-100.0, ventilation.minimumOutdoorTemperature());
  EXPECT_DOUBLE_EQ(100.0, ventilation.maximumOutdoorTemperature());
  EXPECT_DOUBLE_EQ(40.0, ventilation.maximumWindSpeed());
}

TEST_F(EPModelFixture, ZoneVentilationWindandStackOpenArea_ScheduleRelationshipsValidationAndReset) {
  Model model;
  ZoneVentilationWindandStackOpenArea ventilation(model);
  ScheduleConstant opening(model);
  ScheduleConstant minimumIndoor(model);
  ScheduleConstant maximumIndoor(model);
  ScheduleConstant delta(model);
  ScheduleConstant minimumOutdoor(model);
  ScheduleConstant maximumOutdoor(model);
  ASSERT_TRUE(opening.setValue(0.5));
  ASSERT_TRUE(minimumIndoor.setValue(18.0));
  ASSERT_TRUE(maximumIndoor.setValue(27.0));
  ASSERT_TRUE(delta.setValue(3.0));
  ASSERT_TRUE(minimumOutdoor.setValue(-10.0));
  ASSERT_TRUE(maximumOutdoor.setValue(35.0));

  ASSERT_TRUE(ventilation.setOpeningAreaFractionSchedule(opening));
  ASSERT_TRUE(ventilation.setMinimumIndoorTemperatureSchedule(minimumIndoor));
  ASSERT_TRUE(ventilation.setMaximumIndoorTemperatureSchedule(maximumIndoor));
  ASSERT_TRUE(ventilation.setDeltaTemperatureSchedule(delta));
  ASSERT_TRUE(ventilation.setMinimumOutdoorTemperatureSchedule(minimumOutdoor));
  ASSERT_TRUE(ventilation.setMaximumOutdoorTemperatureSchedule(maximumOutdoor));
  EXPECT_EQ(opening.handle(), ventilation.openingAreaFractionSchedule().handle());
  ASSERT_TRUE(ventilation.minimumIndoorTemperatureSchedule());
  EXPECT_EQ(minimumIndoor.handle(), ventilation.minimumIndoorTemperatureSchedule()->handle());
  ASSERT_TRUE(ventilation.maximumIndoorTemperatureSchedule());
  EXPECT_EQ(maximumIndoor.handle(), ventilation.maximumIndoorTemperatureSchedule()->handle());
  ASSERT_TRUE(ventilation.deltaTemperatureSchedule());
  EXPECT_EQ(delta.handle(), ventilation.deltaTemperatureSchedule()->handle());
  ASSERT_TRUE(ventilation.minimumOutdoorTemperatureSchedule());
  EXPECT_EQ(minimumOutdoor.handle(), ventilation.minimumOutdoorTemperatureSchedule()->handle());
  ASSERT_TRUE(ventilation.maximumOutdoorTemperatureSchedule());
  EXPECT_EQ(maximumOutdoor.handle(), ventilation.maximumOutdoorTemperatureSchedule()->handle());

  ScheduleConstant incompatible(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatible.setScheduleTypeLimits(temperatureLimits));
  Model foreignModel;
  ScheduleConstant foreign(foreignModel);
  EXPECT_FALSE(ventilation.setOpeningAreaFractionSchedule(incompatible));
  EXPECT_FALSE(ventilation.setOpeningAreaFractionSchedule(foreign));
  EXPECT_EQ(opening.handle(), ventilation.openingAreaFractionSchedule().handle());

  ScheduleConstant discreteTemperature(model);
  ScheduleTypeLimits discreteTemperatureLimits(model);
  ASSERT_TRUE(discreteTemperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(discreteTemperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(discreteTemperature.setScheduleTypeLimits(discreteTemperatureLimits));
  EXPECT_FALSE(ventilation.setMinimumIndoorTemperatureSchedule(discreteTemperature));
  ASSERT_TRUE(ventilation.minimumIndoorTemperatureSchedule());
  EXPECT_EQ(minimumIndoor.handle(), ventilation.minimumIndoorTemperatureSchedule()->handle());

  ScheduleConstant discreteDelta(model);
  ScheduleTypeLimits discreteDeltaLimits(model);
  ASSERT_TRUE(discreteDeltaLimits.setNumericType("Discrete"));
  ASSERT_TRUE(discreteDeltaLimits.setUnitType("DeltaTemperature"));
  ASSERT_TRUE(discreteDelta.setScheduleTypeLimits(discreteDeltaLimits));
  EXPECT_FALSE(ventilation.setDeltaTemperatureSchedule(discreteDelta));
  ASSERT_TRUE(ventilation.deltaTemperatureSchedule());
  EXPECT_EQ(delta.handle(), ventilation.deltaTemperatureSchedule()->handle());
  EXPECT_FALSE(ventilation.setMaximumOutdoorTemperatureSchedule(foreign));
  ASSERT_TRUE(ventilation.maximumOutdoorTemperatureSchedule());
  EXPECT_EQ(maximumOutdoor.handle(), ventilation.maximumOutdoorTemperatureSchedule()->handle());

  constexpr auto minimumIndoorField = openstudio::ZoneVentilation_WindandStackOpenAreaFields::MinimumIndoorTemperatureScheduleName;
  auto workspaceImpl = ventilation.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  ASSERT_TRUE(workspaceImpl->setPointer(minimumIndoorField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(minimumIndoorField, "Unresolved Minimum Indoor", false));
  ventilation.resetMinimumIndoorTemperatureSchedule();
  EXPECT_FALSE(ventilation.minimumIndoorTemperatureSchedule());
  EXPECT_EQ("", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(minimumIndoorField, false, true).value_or(""));

  ventilation.resetMaximumIndoorTemperatureSchedule();
  ventilation.resetDeltaTemperatureSchedule();
  ventilation.resetMinimumOutdoorTemperatureSchedule();
  ventilation.resetMaximumOutdoorTemperatureSchedule();
  EXPECT_FALSE(ventilation.maximumIndoorTemperatureSchedule());
  EXPECT_FALSE(ventilation.deltaTemperatureSchedule());
  EXPECT_FALSE(ventilation.minimumOutdoorTemperatureSchedule());
  EXPECT_FALSE(ventilation.maximumOutdoorTemperatureSchedule());
  EXPECT_EQ("", workspaceImpl
                  ->openstudio::detail::IdfObject_Impl::getString(
                    openstudio::ZoneVentilation_WindandStackOpenAreaFields::MaximumIndoorTemperatureScheduleName, false, true)
                  .value_or(""));
  EXPECT_EQ("", workspaceImpl
                  ->openstudio::detail::IdfObject_Impl::getString(
                    openstudio::ZoneVentilation_WindandStackOpenAreaFields::DeltaTemperatureScheduleName, false, true)
                  .value_or(""));
  EXPECT_EQ("", workspaceImpl
                  ->openstudio::detail::IdfObject_Impl::getString(
                    openstudio::ZoneVentilation_WindandStackOpenAreaFields::MinimumOutdoorTemperatureScheduleName, false, true)
                  .value_or(""));
  EXPECT_EQ("", workspaceImpl
                  ->openstudio::detail::IdfObject_Impl::getString(
                    openstudio::ZoneVentilation_WindandStackOpenAreaFields::MaximumOutdoorTemperatureScheduleName, false, true)
                  .value_or(""));
}

TEST_F(EPModelFixture, ZoneVentilationWindandStackOpenArea_CanonicalizationRepairsOnlyBlankOpeningSchedule) {
  constexpr auto field = openstudio::ZoneVentilation_WindandStackOpenAreaFields::OpeningAreaFractionScheduleName;

  Model blankModel;
  ZoneVentilationWindandStackOpenArea blankVentilation(blankModel);
  auto blankWorkspaceImpl = blankVentilation.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankWorkspaceImpl);
  ASSERT_TRUE(blankWorkspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(blankWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  EXPECT_EQ(0u, blankModel.canonicalize().errorCount);
  EXPECT_EQ(blankModel.alwaysOnDiscreteSchedule().handle(), blankVentilation.openingAreaFractionSchedule().handle());

  Model unresolvedModel;
  ZoneVentilationWindandStackOpenArea unresolvedVentilation(unresolvedModel);
  auto unresolvedWorkspaceImpl = unresolvedVentilation.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(unresolvedWorkspaceImpl);
  ASSERT_TRUE(unresolvedWorkspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(unresolvedWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Unresolved Opening Fraction", false));
  EXPECT_EQ(0u, unresolvedModel.canonicalize().errorCount);
  EXPECT_EQ("Unresolved Opening Fraction", unresolvedWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
}

TEST_F(EPModelFixture, ZoneVentilationWindandStackOpenArea_SchedulesSurviveReloadMutationAndRemoval) {
  const auto firstPath = uniqueZoneVentilationPath("epmodel-zone-ventilation-first");
  const auto secondPath = uniqueZoneVentilationPath("epmodel-zone-ventilation-second");
  const ScopedZoneVentilationFileRemoval removeFirst(firstPath);
  const ScopedZoneVentilationFileRemoval removeSecond(secondPath);

  Model model;
  ZoneVentilationWindandStackOpenArea ventilation(model);
  ScheduleConstant opening(model);
  ScheduleConstant minimumIndoor(model);
  ASSERT_TRUE(ventilation.setName("Reloadable Zone Ventilation"));
  ASSERT_TRUE(opening.setName("Zone Ventilation Opening Fraction"));
  ASSERT_TRUE(minimumIndoor.setName("Zone Ventilation Minimum Indoor"));
  ASSERT_TRUE(opening.setValue(0.75));
  ASSERT_TRUE(minimumIndoor.setValue(19.0));
  ASSERT_TRUE(ventilation.setOpeningAreaFractionSchedule(opening));
  ASSERT_TRUE(ventilation.setMinimumIndoorTemperatureSchedule(minimumIndoor));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedVentilation = loadedModel->getConcreteModelObjectByName<ZoneVentilationWindandStackOpenArea>("Reloadable Zone Ventilation");
  auto loadedOpening = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Zone Ventilation Opening Fraction");
  ASSERT_TRUE(loadedVentilation);
  ASSERT_TRUE(loadedOpening);
  EXPECT_EQ(loadedOpening->handle(), loadedVentilation->openingAreaFractionSchedule().handle());

  ScheduleConstant replacement(*loadedModel);
  ASSERT_TRUE(replacement.setName("Zone Ventilation Maximum Outdoor"));
  ASSERT_TRUE(replacement.setValue(32.0));
  ASSERT_TRUE(loadedVentilation->setMaximumOutdoorTemperatureSchedule(replacement));
  loadedVentilation->resetMinimumIndoorTemperatureSchedule();
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedVentilation = reloadedModel->getConcreteModelObjectByName<ZoneVentilationWindandStackOpenArea>("Reloadable Zone Ventilation");
  auto reloadedOpening = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Zone Ventilation Opening Fraction");
  auto reloadedReplacement = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Zone Ventilation Maximum Outdoor");
  ASSERT_TRUE(reloadedVentilation);
  ASSERT_TRUE(reloadedOpening);
  ASSERT_TRUE(reloadedReplacement);
  EXPECT_FALSE(reloadedVentilation->minimumIndoorTemperatureSchedule());
  ASSERT_TRUE(reloadedVentilation->maximumOutdoorTemperatureSchedule());
  EXPECT_EQ(reloadedReplacement->handle(), reloadedVentilation->maximumOutdoorTemperatureSchedule()->handle());
  EXPECT_FALSE(reloadedVentilation->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedOpening->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacement->handle()));
}

TEST_F(EPModelFixture, ZoneVentilationWindandStackOpenArea_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneVentilationWindandStackOpenArea ventilation(model);

  EXPECT_TRUE(ventilation.setOpeningArea(1.5));
  EXPECT_TRUE(ventilation.setOpeningEffectiveness(0.65));
  EXPECT_FALSE(ventilation.isOpeningEffectivenessAutocalculated());
  EXPECT_TRUE(ventilation.setEffectiveAngle(45.0));
  EXPECT_TRUE(ventilation.setHeightDifference(3.25));
  EXPECT_TRUE(ventilation.setDischargeCoefficientforOpening(0.45));
  EXPECT_FALSE(ventilation.isDischargeCoefficientforOpeningAutocalculated());
  EXPECT_TRUE(ventilation.setMinimumIndoorTemperature(-20.0));
  EXPECT_TRUE(ventilation.setMaximumIndoorTemperature(45.0));
  EXPECT_TRUE(ventilation.setDeltaTemperature(12.0));
  EXPECT_TRUE(ventilation.setMinimumOutdoorTemperature(-15.0));
  EXPECT_TRUE(ventilation.setMaximumOutdoorTemperature(35.0));
  EXPECT_TRUE(ventilation.setMaximumWindSpeed(30.0));

  EXPECT_DOUBLE_EQ(1.5, ventilation.openingArea());
  ASSERT_TRUE(ventilation.openingEffectiveness());
  EXPECT_DOUBLE_EQ(0.65, ventilation.openingEffectiveness().value());
  EXPECT_DOUBLE_EQ(45.0, ventilation.effectiveAngle());
  EXPECT_DOUBLE_EQ(3.25, ventilation.heightDifference());
  ASSERT_TRUE(ventilation.dischargeCoefficientforOpening());
  EXPECT_DOUBLE_EQ(0.45, ventilation.dischargeCoefficientforOpening().value());
  EXPECT_DOUBLE_EQ(-20.0, ventilation.minimumIndoorTemperature());
  EXPECT_DOUBLE_EQ(45.0, ventilation.maximumIndoorTemperature());
  EXPECT_DOUBLE_EQ(12.0, ventilation.deltaTemperature());
  EXPECT_DOUBLE_EQ(-15.0, ventilation.minimumOutdoorTemperature());
  EXPECT_DOUBLE_EQ(35.0, ventilation.maximumOutdoorTemperature());
  EXPECT_DOUBLE_EQ(30.0, ventilation.maximumWindSpeed());

  ventilation.autocalculateOpeningEffectiveness();
  EXPECT_TRUE(ventilation.isOpeningEffectivenessAutocalculated());
  EXPECT_FALSE(ventilation.openingEffectiveness());

  ventilation.autocalculateDischargeCoefficientforOpening();
  EXPECT_TRUE(ventilation.isDischargeCoefficientforOpeningAutocalculated());
  EXPECT_FALSE(ventilation.dischargeCoefficientforOpening());
}

TEST_F(EPModelFixture, ZoneVentilationWindandStackOpenArea_ZoneAttachmentRoundTrip) {
  Model model;
  ThermalZone zone(model);
  ZoneVentilationWindandStackOpenArea ventilation(model);

  EXPECT_EQ(0u, ventilation.inletPort());
  EXPECT_EQ(0u, ventilation.outletPort());
  EXPECT_FALSE(ventilation.thermalZone());
  EXPECT_TRUE(ventilation.addToThermalZone(zone));
  ASSERT_TRUE(ventilation.thermalZone());
  EXPECT_EQ(zone, ventilation.thermalZone().get());
  EXPECT_FALSE(ventilation.inletNode());
  EXPECT_FALSE(ventilation.outletNode());

  ventilation.removeFromThermalZone();
  EXPECT_FALSE(ventilation.thermalZone());
  EXPECT_FALSE(ventilation.inletNode());
  EXPECT_FALSE(ventilation.outletNode());
}
