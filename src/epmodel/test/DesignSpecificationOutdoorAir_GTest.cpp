/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/DesignSpecification_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/DesignSpecification_OutdoorAir_SpaceList_FieldEnums.hxx>
#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include "EPModelFixture.hpp"

#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/DesignSpecificationOutdoorAirSpaceList.hpp"
#include "../ModelObject/DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "../ModelObject/SizingZone.hpp"
#include "../ModelObject/SizingZone_Impl.hpp"
#include "../PlanarSurfaceGroup/Space.hpp"
#include "../PlanarSurfaceGroup/Space_Impl.hpp"
#include "../ResourceObject/DesignSpecificationOutdoorAir.hpp"
#include "../ResourceObject/DesignSpecificationOutdoorAir_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedDesignSpecificationOutdoorAirFileRemoval
{
 public:
  explicit ScopedDesignSpecificationOutdoorAirFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedDesignSpecificationOutdoorAirFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueDesignSpecificationOutdoorAirPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAir_DefaultConstructor) {
  Model model;
  DesignSpecificationOutdoorAir dsoa(model);
  EXPECT_EQ(DesignSpecificationOutdoorAir::iddObjectType(), dsoa.iddObject().type());

  EXPECT_EQ("Sum", dsoa.outdoorAirMethod());
  EXPECT_TRUE(dsoa.isOutdoorAirMethodDefaulted());
  EXPECT_DOUBLE_EQ(0.0, dsoa.outdoorAirFlowperPerson());
  EXPECT_TRUE(dsoa.isOutdoorAirFlowperPersonDefaulted());
  EXPECT_DOUBLE_EQ(0.0, dsoa.outdoorAirFlowperFloorArea());
  EXPECT_TRUE(dsoa.isOutdoorAirFlowperFloorAreaDefaulted());
  EXPECT_DOUBLE_EQ(0.0, dsoa.outdoorAirFlowRate());
  EXPECT_TRUE(dsoa.isOutdoorAirFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.0, dsoa.outdoorAirFlowAirChangesperHour());
  EXPECT_TRUE(dsoa.isOutdoorAirFlowAirChangesperHourDefaulted());
  EXPECT_FALSE(dsoa.outdoorAirFlowRateFractionSchedule());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ("Sum", dsoa.outdoorAirMethod());
  EXPECT_TRUE(dsoa.isOutdoorAirMethodDefaulted());
  EXPECT_DOUBLE_EQ(0.0, dsoa.outdoorAirFlowperPerson());
  EXPECT_TRUE(dsoa.isOutdoorAirFlowperPersonDefaulted());
  EXPECT_DOUBLE_EQ(0.0, dsoa.outdoorAirFlowperFloorArea());
  EXPECT_TRUE(dsoa.isOutdoorAirFlowperFloorAreaDefaulted());
  EXPECT_DOUBLE_EQ(0.0, dsoa.outdoorAirFlowRate());
  EXPECT_TRUE(dsoa.isOutdoorAirFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.0, dsoa.outdoorAirFlowAirChangesperHour());
  EXPECT_TRUE(dsoa.isOutdoorAirFlowAirChangesperHourDefaulted());
}

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAir_OutdoorAirMethodValuesUseConfiguredKeys) {
  const std::vector<std::string> expectedValues{"Flow/Person",
                                                "Flow/Area",
                                                "Flow/Zone",
                                                "AirChanges/Hour",
                                                "Sum",
                                                "Maximum",
                                                "IndoorAirQualityProcedure",
                                                "ProportionalControlBasedOnDesignOccupancy",
                                                "ProportionalControlBasedOnOccupancySchedule"};
  EXPECT_EQ(expectedValues, DesignSpecificationOutdoorAir::outdoorAirMethodValues());
  EXPECT_EQ(expectedValues, DesignSpecificationOutdoorAir::validOutdoorAirMethodValues());
}

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAir_ScalarSetInvalidPreservationAndReset) {
  Model model;
  DesignSpecificationOutdoorAir dsoa(model);

  ASSERT_TRUE(dsoa.setOutdoorAirMethod("Maximum"));
  EXPECT_EQ("Maximum", dsoa.outdoorAirMethod());
  EXPECT_FALSE(dsoa.isOutdoorAirMethodDefaulted());
  EXPECT_FALSE(dsoa.setOutdoorAirMethod("Not a configured outdoor air method"));
  EXPECT_EQ("Maximum", dsoa.outdoorAirMethod());
  EXPECT_FALSE(dsoa.isOutdoorAirMethodDefaulted());

  ASSERT_TRUE(dsoa.setOutdoorAirFlowperPerson(0.0075));
  EXPECT_DOUBLE_EQ(0.0075, dsoa.outdoorAirFlowperPerson());
  EXPECT_FALSE(dsoa.isOutdoorAirFlowperPersonDefaulted());
  EXPECT_FALSE(dsoa.setOutdoorAirFlowperPerson(-0.001));
  EXPECT_DOUBLE_EQ(0.0075, dsoa.outdoorAirFlowperPerson());

  ASSERT_TRUE(dsoa.setOutdoorAirFlowperFloorArea(0.0008));
  EXPECT_DOUBLE_EQ(0.0008, dsoa.outdoorAirFlowperFloorArea());
  EXPECT_FALSE(dsoa.isOutdoorAirFlowperFloorAreaDefaulted());
  EXPECT_FALSE(dsoa.setOutdoorAirFlowperFloorArea(-0.001));
  EXPECT_DOUBLE_EQ(0.0008, dsoa.outdoorAirFlowperFloorArea());

  ASSERT_TRUE(dsoa.setOutdoorAirFlowRate(0.12));
  EXPECT_DOUBLE_EQ(0.12, dsoa.outdoorAirFlowRate());
  EXPECT_FALSE(dsoa.isOutdoorAirFlowRateDefaulted());
  EXPECT_FALSE(dsoa.setOutdoorAirFlowRate(-0.01));
  EXPECT_DOUBLE_EQ(0.12, dsoa.outdoorAirFlowRate());

  ASSERT_TRUE(dsoa.setOutdoorAirFlowAirChangesperHour(0.65));
  EXPECT_DOUBLE_EQ(0.65, dsoa.outdoorAirFlowAirChangesperHour());
  EXPECT_FALSE(dsoa.isOutdoorAirFlowAirChangesperHourDefaulted());
  EXPECT_FALSE(dsoa.setOutdoorAirFlowAirChangesperHour(-0.1));
  EXPECT_DOUBLE_EQ(0.65, dsoa.outdoorAirFlowAirChangesperHour());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ("Maximum", dsoa.outdoorAirMethod());
  EXPECT_DOUBLE_EQ(0.0075, dsoa.outdoorAirFlowperPerson());
  EXPECT_DOUBLE_EQ(0.0008, dsoa.outdoorAirFlowperFloorArea());
  EXPECT_DOUBLE_EQ(0.12, dsoa.outdoorAirFlowRate());
  EXPECT_DOUBLE_EQ(0.65, dsoa.outdoorAirFlowAirChangesperHour());

  dsoa.resetOutdoorAirMethod();
  dsoa.resetOutdoorAirFlowperPerson();
  dsoa.resetOutdoorAirFlowperFloorArea();
  dsoa.resetOutdoorAirFlowRate();
  dsoa.resetOutdoorAirFlowAirChangesperHour();
  EXPECT_EQ("Sum", dsoa.outdoorAirMethod());
  EXPECT_TRUE(dsoa.isOutdoorAirMethodDefaulted());
  EXPECT_DOUBLE_EQ(0.0, dsoa.outdoorAirFlowperPerson());
  EXPECT_TRUE(dsoa.isOutdoorAirFlowperPersonDefaulted());
  EXPECT_DOUBLE_EQ(0.0, dsoa.outdoorAirFlowperFloorArea());
  EXPECT_TRUE(dsoa.isOutdoorAirFlowperFloorAreaDefaulted());
  EXPECT_DOUBLE_EQ(0.0, dsoa.outdoorAirFlowRate());
  EXPECT_TRUE(dsoa.isOutdoorAirFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.0, dsoa.outdoorAirFlowAirChangesperHour());
  EXPECT_TRUE(dsoa.isOutdoorAirFlowAirChangesperHourDefaulted());
}

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAir_BlankAndExplicitScalarsSurviveReloadWithRelationships) {
  const auto idfPath = uniqueDesignSpecificationOutdoorAirPath("epmodel-dsoa-scalar-defaults");
  const ScopedDesignSpecificationOutdoorAirFileRemoval removeIdf(idfPath);

  Model model;
  ThermalZone zone(model);
  Space space(model);
  DesignSpecificationOutdoorAir blankDsoa(model);
  DesignSpecificationOutdoorAir explicitDsoa(model);
  ScheduleConstant schedule(model);
  ASSERT_TRUE(zone.setName("DSOA Scalar Zone"));
  ASSERT_TRUE(space.setName("DSOA Scalar Space"));
  ASSERT_TRUE(blankDsoa.setName("Blank Scalar DSOA"));
  ASSERT_TRUE(explicitDsoa.setName("Explicit Scalar DSOA"));
  ASSERT_TRUE(schedule.setName("DSOA Scalar Fraction Schedule"));
  ASSERT_TRUE(schedule.setValue(0.7));
  ASSERT_TRUE(space.setThermalZone(zone));
  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(explicitDsoa));
  ASSERT_TRUE(explicitDsoa.setOutdoorAirFlowRateFractionSchedule(schedule));
  ASSERT_TRUE(explicitDsoa.setOutdoorAirMethod("Maximum"));
  ASSERT_TRUE(explicitDsoa.setOutdoorAirFlowperPerson(0.006));
  ASSERT_TRUE(explicitDsoa.setOutdoorAirFlowperFloorArea(0.0006));
  ASSERT_TRUE(explicitDsoa.setOutdoorAirFlowRate(0.18));
  ASSERT_TRUE(explicitDsoa.setOutdoorAirFlowAirChangesperHour(0.75));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ("Sum", blankDsoa.outdoorAirMethod());
  EXPECT_TRUE(blankDsoa.isOutdoorAirMethodDefaulted());
  EXPECT_DOUBLE_EQ(0.0, blankDsoa.outdoorAirFlowperPerson());
  EXPECT_TRUE(blankDsoa.isOutdoorAirFlowperPersonDefaulted());
  EXPECT_DOUBLE_EQ(0.0, blankDsoa.outdoorAirFlowperFloorArea());
  EXPECT_TRUE(blankDsoa.isOutdoorAirFlowperFloorAreaDefaulted());
  EXPECT_DOUBLE_EQ(0.0, blankDsoa.outdoorAirFlowRate());
  EXPECT_TRUE(blankDsoa.isOutdoorAirFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.0, blankDsoa.outdoorAirFlowAirChangesperHour());
  EXPECT_TRUE(blankDsoa.isOutdoorAirFlowAirChangesperHourDefaulted());
  EXPECT_EQ("Maximum", explicitDsoa.outdoorAirMethod());
  EXPECT_FALSE(explicitDsoa.isOutdoorAirMethodDefaulted());
  EXPECT_DOUBLE_EQ(0.006, explicitDsoa.outdoorAirFlowperPerson());
  EXPECT_FALSE(explicitDsoa.isOutdoorAirFlowperPersonDefaulted());
  EXPECT_DOUBLE_EQ(0.0006, explicitDsoa.outdoorAirFlowperFloorArea());
  EXPECT_FALSE(explicitDsoa.isOutdoorAirFlowperFloorAreaDefaulted());
  EXPECT_DOUBLE_EQ(0.18, explicitDsoa.outdoorAirFlowRate());
  EXPECT_FALSE(explicitDsoa.isOutdoorAirFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.75, explicitDsoa.outdoorAirFlowAirChangesperHour());
  EXPECT_FALSE(explicitDsoa.isOutdoorAirFlowAirChangesperHourDefaulted());
  ASSERT_TRUE(space.designSpecificationOutdoorAir());
  EXPECT_EQ(explicitDsoa.handle(), space.designSpecificationOutdoorAir()->handle());
  ASSERT_TRUE(explicitDsoa.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ(schedule.handle(), explicitDsoa.outdoorAirFlowRateFractionSchedule()->handle());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("DSOA Scalar Zone");
  auto loadedSpace = loadedModel->getConcreteModelObjectByName<Space>("DSOA Scalar Space");
  auto loadedBlankDsoa = loadedModel->getConcreteModelObjectByName<DesignSpecificationOutdoorAir>("Blank Scalar DSOA");
  auto loadedExplicitDsoa = loadedModel->getConcreteModelObjectByName<DesignSpecificationOutdoorAir>("Explicit Scalar DSOA");
  auto loadedSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("DSOA Scalar Fraction Schedule");
  ASSERT_TRUE(loadedZone);
  ASSERT_TRUE(loadedSpace);
  ASSERT_TRUE(loadedBlankDsoa);
  ASSERT_TRUE(loadedExplicitDsoa);
  ASSERT_TRUE(loadedSchedule);
  EXPECT_EQ("Sum", loadedBlankDsoa->outdoorAirMethod());
  EXPECT_TRUE(loadedBlankDsoa->isOutdoorAirMethodDefaulted());
  EXPECT_DOUBLE_EQ(0.0, loadedBlankDsoa->outdoorAirFlowperPerson());
  EXPECT_TRUE(loadedBlankDsoa->isOutdoorAirFlowperPersonDefaulted());
  EXPECT_DOUBLE_EQ(0.0, loadedBlankDsoa->outdoorAirFlowperFloorArea());
  EXPECT_TRUE(loadedBlankDsoa->isOutdoorAirFlowperFloorAreaDefaulted());
  EXPECT_DOUBLE_EQ(0.0, loadedBlankDsoa->outdoorAirFlowRate());
  EXPECT_TRUE(loadedBlankDsoa->isOutdoorAirFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.0, loadedBlankDsoa->outdoorAirFlowAirChangesperHour());
  EXPECT_TRUE(loadedBlankDsoa->isOutdoorAirFlowAirChangesperHourDefaulted());
  EXPECT_EQ("Maximum", loadedExplicitDsoa->outdoorAirMethod());
  EXPECT_FALSE(loadedExplicitDsoa->isOutdoorAirMethodDefaulted());
  EXPECT_DOUBLE_EQ(0.006, loadedExplicitDsoa->outdoorAirFlowperPerson());
  EXPECT_FALSE(loadedExplicitDsoa->isOutdoorAirFlowperPersonDefaulted());
  EXPECT_DOUBLE_EQ(0.0006, loadedExplicitDsoa->outdoorAirFlowperFloorArea());
  EXPECT_FALSE(loadedExplicitDsoa->isOutdoorAirFlowperFloorAreaDefaulted());
  EXPECT_DOUBLE_EQ(0.18, loadedExplicitDsoa->outdoorAirFlowRate());
  EXPECT_FALSE(loadedExplicitDsoa->isOutdoorAirFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.75, loadedExplicitDsoa->outdoorAirFlowAirChangesperHour());
  EXPECT_FALSE(loadedExplicitDsoa->isOutdoorAirFlowAirChangesperHourDefaulted());
  ASSERT_TRUE(loadedSpace->thermalZone());
  EXPECT_EQ(loadedZone->handle(), loadedSpace->thermalZone()->handle());
  ASSERT_TRUE(loadedSpace->designSpecificationOutdoorAir());
  EXPECT_EQ(loadedExplicitDsoa->handle(), loadedSpace->designSpecificationOutdoorAir()->handle());
  ASSERT_TRUE(loadedExplicitDsoa->outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ(loadedSchedule->handle(), loadedExplicitDsoa->outdoorAirFlowRateFractionSchedule()->handle());

  loadedExplicitDsoa->resetOutdoorAirMethod();
  loadedExplicitDsoa->resetOutdoorAirFlowperPerson();
  loadedExplicitDsoa->resetOutdoorAirFlowperFloorArea();
  loadedExplicitDsoa->resetOutdoorAirFlowRate();
  loadedExplicitDsoa->resetOutdoorAirFlowAirChangesperHour();
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto resetModel = Model::load(idfPath);
  ASSERT_TRUE(resetModel);
  auto resetZone = resetModel->getConcreteModelObjectByName<ThermalZone>("DSOA Scalar Zone");
  auto resetSpace = resetModel->getConcreteModelObjectByName<Space>("DSOA Scalar Space");
  auto resetDsoa = resetModel->getConcreteModelObjectByName<DesignSpecificationOutdoorAir>("Explicit Scalar DSOA");
  auto resetSchedule = resetModel->getConcreteModelObjectByName<ScheduleConstant>("DSOA Scalar Fraction Schedule");
  ASSERT_TRUE(resetZone);
  ASSERT_TRUE(resetSpace);
  ASSERT_TRUE(resetDsoa);
  ASSERT_TRUE(resetSchedule);
  EXPECT_EQ("Sum", resetDsoa->outdoorAirMethod());
  EXPECT_TRUE(resetDsoa->isOutdoorAirMethodDefaulted());
  EXPECT_DOUBLE_EQ(0.0, resetDsoa->outdoorAirFlowperPerson());
  EXPECT_TRUE(resetDsoa->isOutdoorAirFlowperPersonDefaulted());
  EXPECT_DOUBLE_EQ(0.0, resetDsoa->outdoorAirFlowperFloorArea());
  EXPECT_TRUE(resetDsoa->isOutdoorAirFlowperFloorAreaDefaulted());
  EXPECT_DOUBLE_EQ(0.0, resetDsoa->outdoorAirFlowRate());
  EXPECT_TRUE(resetDsoa->isOutdoorAirFlowRateDefaulted());
  EXPECT_DOUBLE_EQ(0.0, resetDsoa->outdoorAirFlowAirChangesperHour());
  EXPECT_TRUE(resetDsoa->isOutdoorAirFlowAirChangesperHourDefaulted());
  ASSERT_TRUE(resetSpace->thermalZone());
  EXPECT_EQ(resetZone->handle(), resetSpace->thermalZone()->handle());
  ASSERT_TRUE(resetSpace->designSpecificationOutdoorAir());
  EXPECT_EQ(resetDsoa->handle(), resetSpace->designSpecificationOutdoorAir()->handle());
  ASSERT_TRUE(resetDsoa->outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ(resetSchedule->handle(), resetDsoa->outdoorAirFlowRateFractionSchedule()->handle());
}

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAir_ScheduleRelationshipValidationAndReset) {
  Model model;
  DesignSpecificationOutdoorAir dsoa(model);

  ScheduleConstant inferredSchedule(model);
  ASSERT_TRUE(inferredSchedule.setValue(0.5));
  EXPECT_FALSE(inferredSchedule.scheduleTypeLimits());
  ASSERT_TRUE(dsoa.setOutdoorAirFlowRateFractionSchedule(inferredSchedule));
  ASSERT_TRUE(dsoa.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ(inferredSchedule.handle(), dsoa.outdoorAirFlowRateFractionSchedule()->handle());
  ASSERT_TRUE(inferredSchedule.scheduleTypeLimits());
  EXPECT_EQ("Continuous", inferredSchedule.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_TRUE(inferredSchedule.scheduleTypeLimits()->isUnitTypeDefaulted());
  EXPECT_DOUBLE_EQ(0.0, inferredSchedule.scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_DOUBLE_EQ(1.0, inferredSchedule.scheduleTypeLimits()->upperLimitValue().value_or(-1.0));

  ScheduleConstant explicitSchedule(model);
  ScheduleTypeLimits explicitLimits(model);
  ASSERT_TRUE(explicitSchedule.setValue(0.75));
  ASSERT_TRUE(explicitLimits.setNumericType("Continuous"));
  ASSERT_TRUE(explicitLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(explicitLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(explicitLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(explicitSchedule.setScheduleTypeLimits(explicitLimits));
  ASSERT_TRUE(dsoa.setOutdoorAirFlowRateFractionSchedule(explicitSchedule));
  ASSERT_TRUE(dsoa.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ(explicitSchedule.handle(), dsoa.outdoorAirFlowRateFractionSchedule()->handle());

  ScheduleConstant incompatibleSchedule(model);
  ScheduleTypeLimits incompatibleLimits(model);
  ASSERT_TRUE(incompatibleLimits.setNumericType("Continuous"));
  ASSERT_TRUE(incompatibleLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(incompatibleLimits.setLowerLimitValue(-0.1));
  ASSERT_TRUE(incompatibleLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(incompatibleSchedule.setScheduleTypeLimits(incompatibleLimits));
  EXPECT_FALSE(dsoa.setOutdoorAirFlowRateFractionSchedule(incompatibleSchedule));
  ASSERT_TRUE(dsoa.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ(explicitSchedule.handle(), dsoa.outdoorAirFlowRateFractionSchedule()->handle());

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  ASSERT_TRUE(foreignSchedule.setValue(0.25));
  EXPECT_FALSE(dsoa.setOutdoorAirFlowRateFractionSchedule(foreignSchedule));
  ASSERT_TRUE(dsoa.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ(explicitSchedule.handle(), dsoa.outdoorAirFlowRateFractionSchedule()->handle());

  dsoa.resetOutdoorAirFlowRateFractionSchedule();
  EXPECT_FALSE(dsoa.outdoorAirFlowRateFractionSchedule());
}

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAir_ScheduleResetClearsMalformedRawRelationship) {
  Model model;
  DesignSpecificationOutdoorAir dsoa(model);
  auto workspaceImpl = dsoa.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  constexpr auto field = openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirScheduleName;

  // Public setters cannot create an unresolved schedule reference; this low-level write represents malformed imported EnergyPlus storage.
  ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Unresolved Outdoor Air Schedule", false));
  EXPECT_FALSE(dsoa.outdoorAirFlowRateFractionSchedule());

  ScheduleConstant incompatibleSchedule(model);
  ScheduleTypeLimits incompatibleLimits(model);
  ASSERT_TRUE(incompatibleLimits.setNumericType("Discrete"));
  ASSERT_TRUE(incompatibleLimits.setUnitType("Availability"));
  ASSERT_TRUE(incompatibleLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(incompatibleLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(incompatibleSchedule.setScheduleTypeLimits(incompatibleLimits));
  EXPECT_FALSE(dsoa.setOutdoorAirFlowRateFractionSchedule(incompatibleSchedule));

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  EXPECT_FALSE(dsoa.setOutdoorAirFlowRateFractionSchedule(foreignSchedule));
  EXPECT_EQ("Unresolved Outdoor Air Schedule", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));

  dsoa.resetOutdoorAirFlowRateFractionSchedule();
  EXPECT_FALSE(dsoa.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ("", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
}

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAir_CanonicalizesOnlyUnambiguousPersistedScheduleEvidence) {
  Model model;
  ScheduleConstant recoverableByName(model);
  ScheduleConstant duplicateFirst(model);
  ScheduleConstant duplicateSecond(model);
  ASSERT_TRUE(recoverableByName.setName("Recoverable DSOA Schedule"));
  ASSERT_TRUE(duplicateFirst.setName("Ambiguous DSOA Schedule"));
  auto duplicateSecondImpl = duplicateSecond.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(duplicateSecondImpl);
  // Imported IDFs can contain duplicate eligible names, while the public name setter deliberately disambiguates them.
  ASSERT_TRUE(duplicateSecondImpl->openstudio::detail::IdfObject_Impl::setString(0u, "Ambiguous DSOA Schedule", false));

  DesignSpecificationOutdoorAir byName(model);
  DesignSpecificationOutdoorAir missing(model);
  DesignSpecificationOutdoorAir ambiguous(model);
  DesignSpecificationOutdoorAir blank(model);
  auto byNameImpl = byName.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto missingImpl = missing.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto ambiguousImpl = ambiguous.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto blankImpl = blank.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(byNameImpl);
  ASSERT_TRUE(missingImpl);
  ASSERT_TRUE(ambiguousImpl);
  ASSERT_TRUE(blankImpl);
  constexpr auto field = openstudio::DesignSpecification_OutdoorAirFields::OutdoorAirScheduleName;

  // These low-level fields represent imported relationship evidence that validated public setters cannot create.
  ASSERT_TRUE(byNameImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(byNameImpl->openstudio::detail::IdfObject_Impl::setString(field, recoverableByName.nameString(), false));
  ASSERT_TRUE(missingImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(missingImpl->openstudio::detail::IdfObject_Impl::setString(field, "Missing DSOA Schedule", false));
  ASSERT_TRUE(ambiguousImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(ambiguousImpl->openstudio::detail::IdfObject_Impl::setString(field, "Ambiguous DSOA Schedule", false));
  ASSERT_TRUE(blankImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));

  EXPECT_FALSE(byName.outdoorAirFlowRateFractionSchedule());
  const auto scheduleCount = model.getConcreteModelObjects<ScheduleConstant>().size();
  const auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(byName.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ(recoverableByName.handle(), byName.outdoorAirFlowRateFractionSchedule()->handle());
  EXPECT_FALSE(missing.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ("Missing DSOA Schedule", missingImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
  EXPECT_FALSE(ambiguous.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ("Ambiguous DSOA Schedule", ambiguousImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
  EXPECT_FALSE(blank.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ("", blankImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
  EXPECT_EQ(scheduleCount, model.getConcreteModelObjects<ScheduleConstant>().size());

  const auto secondReport = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, secondReport.errorCount);
  ASSERT_TRUE(byName.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ(recoverableByName.handle(), byName.outdoorAirFlowRateFractionSchedule()->handle());
  EXPECT_FALSE(missing.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ("Missing DSOA Schedule", missingImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
  EXPECT_FALSE(ambiguous.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ("Ambiguous DSOA Schedule", ambiguousImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
  EXPECT_FALSE(blank.outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ("", blankImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
  EXPECT_EQ(scheduleCount, model.getConcreteModelObjects<ScheduleConstant>().size());
}

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAir_ScheduleSurvivesReloadMutationResetAndOwnerRemoval) {
  const auto firstPath = uniqueDesignSpecificationOutdoorAirPath("epmodel-dsoa-schedule-first");
  const auto secondPath = uniqueDesignSpecificationOutdoorAirPath("epmodel-dsoa-schedule-second");
  const ScopedDesignSpecificationOutdoorAirFileRemoval removeFirst(firstPath);
  const ScopedDesignSpecificationOutdoorAirFileRemoval removeSecond(secondPath);

  Model model;
  ThermalZone zone(model);
  Space space(model);
  DesignSpecificationOutdoorAir dsoa(model);
  ScheduleConstant originalSchedule(model);
  ASSERT_TRUE(zone.setName("DSOA Schedule Zone"));
  ASSERT_TRUE(space.setName("DSOA Schedule Space"));
  ASSERT_TRUE(dsoa.setName("Reloadable DSOA"));
  ASSERT_TRUE(originalSchedule.setName("Original DSOA Fraction Schedule"));
  ASSERT_TRUE(originalSchedule.setValue(0.6));
  ASSERT_TRUE(space.setThermalZone(zone));
  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));
  ASSERT_TRUE(dsoa.setOutdoorAirFlowRateFractionSchedule(originalSchedule));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("DSOA Schedule Zone");
  auto loadedSpace = loadedModel->getConcreteModelObjectByName<Space>("DSOA Schedule Space");
  auto loadedDsoa = loadedModel->getConcreteModelObjectByName<DesignSpecificationOutdoorAir>("Reloadable DSOA");
  auto loadedOriginalSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original DSOA Fraction Schedule");
  ASSERT_TRUE(loadedZone);
  ASSERT_TRUE(loadedSpace);
  ASSERT_TRUE(loadedDsoa);
  ASSERT_TRUE(loadedOriginalSchedule);
  ASSERT_TRUE(loadedDsoa->outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ(loadedOriginalSchedule->handle(), loadedDsoa->outdoorAirFlowRateFractionSchedule()->handle());
  ASSERT_TRUE(loadedSpace->designSpecificationOutdoorAir());
  EXPECT_EQ(loadedDsoa->handle(), loadedSpace->designSpecificationOutdoorAir()->handle());
  auto loadedSpaceLists = loadedModel->getConcreteModelObjects<DesignSpecificationOutdoorAirSpaceList>();
  ASSERT_EQ(1u, loadedSpaceLists.size());
  auto loadedListedDsoa = loadedSpaceLists.front().designSpecificationOutdoorAir(*loadedSpace);
  ASSERT_TRUE(loadedListedDsoa);
  EXPECT_EQ(loadedDsoa->handle(), loadedListedDsoa->handle());

  ScheduleConstant replacementSchedule(*loadedModel);
  ASSERT_TRUE(replacementSchedule.setName("Replacement DSOA Fraction Schedule"));
  ASSERT_TRUE(replacementSchedule.setValue(0.35));
  ASSERT_TRUE(loadedDsoa->setOutdoorAirFlowRateFractionSchedule(replacementSchedule));
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSpace = reloadedModel->getConcreteModelObjectByName<Space>("DSOA Schedule Space");
  auto reloadedDsoa = reloadedModel->getConcreteModelObjectByName<DesignSpecificationOutdoorAir>("Reloadable DSOA");
  auto reloadedOriginalSchedule = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original DSOA Fraction Schedule");
  auto reloadedReplacementSchedule = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement DSOA Fraction Schedule");
  ASSERT_TRUE(reloadedSpace);
  ASSERT_TRUE(reloadedDsoa);
  ASSERT_TRUE(reloadedOriginalSchedule);
  ASSERT_TRUE(reloadedReplacementSchedule);
  ASSERT_TRUE(reloadedDsoa->outdoorAirFlowRateFractionSchedule());
  EXPECT_EQ(reloadedReplacementSchedule->handle(), reloadedDsoa->outdoorAirFlowRateFractionSchedule()->handle());
  ASSERT_TRUE(reloadedSpace->designSpecificationOutdoorAir());
  EXPECT_EQ(reloadedDsoa->handle(), reloadedSpace->designSpecificationOutdoorAir()->handle());
  auto reloadedSpaceLists = reloadedModel->getConcreteModelObjects<DesignSpecificationOutdoorAirSpaceList>();
  ASSERT_EQ(1u, reloadedSpaceLists.size());
  auto reloadedListedDsoa = reloadedSpaceLists.front().designSpecificationOutdoorAir(*reloadedSpace);
  ASSERT_TRUE(reloadedListedDsoa);
  EXPECT_EQ(reloadedDsoa->handle(), reloadedListedDsoa->handle());

  reloadedDsoa->resetOutdoorAirFlowRateFractionSchedule();
  EXPECT_FALSE(reloadedDsoa->outdoorAirFlowRateFractionSchedule());
  ASSERT_TRUE(reloadedModel->save(secondPath, true));

  auto resetModel = Model::load(secondPath);
  ASSERT_TRUE(resetModel);
  auto resetSpace = resetModel->getConcreteModelObjectByName<Space>("DSOA Schedule Space");
  auto resetDsoa = resetModel->getConcreteModelObjectByName<DesignSpecificationOutdoorAir>("Reloadable DSOA");
  auto resetOriginalSchedule = resetModel->getConcreteModelObjectByName<ScheduleConstant>("Original DSOA Fraction Schedule");
  auto resetReplacementSchedule = resetModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement DSOA Fraction Schedule");
  ASSERT_TRUE(resetSpace);
  ASSERT_TRUE(resetDsoa);
  ASSERT_TRUE(resetOriginalSchedule);
  ASSERT_TRUE(resetReplacementSchedule);
  EXPECT_FALSE(resetDsoa->outdoorAirFlowRateFractionSchedule());
  ASSERT_TRUE(resetSpace->designSpecificationOutdoorAir());
  EXPECT_EQ(resetDsoa->handle(), resetSpace->designSpecificationOutdoorAir()->handle());
  auto resetSpaceLists = resetModel->getConcreteModelObjects<DesignSpecificationOutdoorAirSpaceList>();
  ASSERT_EQ(1u, resetSpaceLists.size());
  auto resetListedDsoa = resetSpaceLists.front().designSpecificationOutdoorAir(*resetSpace);
  ASSERT_TRUE(resetListedDsoa);
  EXPECT_EQ(resetDsoa->handle(), resetListedDsoa->handle());

  DesignSpecificationOutdoorAir removableDsoa(*resetModel);
  ASSERT_TRUE(removableDsoa.setName("Removable Scheduled DSOA"));
  ASSERT_TRUE(removableDsoa.setOutdoorAirFlowRateFractionSchedule(*resetReplacementSchedule));
  const auto removableDsoaHandle = removableDsoa.handle();
  EXPECT_FALSE(removableDsoa.remove().empty());
  EXPECT_FALSE(resetModel->getObject(removableDsoaHandle));
  EXPECT_TRUE(resetModel->getObject(resetOriginalSchedule->handle()));
  EXPECT_TRUE(resetModel->getObject(resetReplacementSchedule->handle()));
  ASSERT_TRUE(resetSpace->designSpecificationOutdoorAir());
  EXPECT_EQ(resetDsoa->handle(), resetSpace->designSpecificationOutdoorAir()->handle());
  ASSERT_TRUE(resetSpaceLists.front().designSpecificationOutdoorAir(*resetSpace));
  EXPECT_EQ(resetDsoa->handle(), resetSpaceLists.front().designSpecificationOutdoorAir(*resetSpace)->handle());
}

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAirSpaceList_DefaultConstructor) {
  Model model;
  DesignSpecificationOutdoorAirSpaceList list(model);
  EXPECT_EQ(DesignSpecificationOutdoorAirSpaceList::iddObjectType(), list.iddObject().type());
  EXPECT_TRUE(list.spaces().empty());
}

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAirSpaceList_NameScalarAccessor_RoundTrip) {
  Model model;
  DesignSpecificationOutdoorAirSpaceList list(model);
  ASSERT_TRUE(list.setName("DSOA Space List A"));
  EXPECT_EQ("DSOA Space List A", list.nameString());
}

TEST_F(EPModelFixture, API_Space_SetDesignSpecificationOutdoorAir_CreatesZoneSpaceListEntry) {
  Model model;
  ThermalZone zone(model);
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));
  DesignSpecificationOutdoorAir dsoa(model);

  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  auto sizingZone = zone.sizingZone();
  auto sizingZoneImpl = sizingZone.getImpl<detail::SizingZone_Impl>();
  ASSERT_TRUE(sizingZoneImpl);
  auto dsoaObject = sizingZone.getModelObjectTarget<ModelObject>(openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName);
  auto directDSOA = dsoaObject ? dsoaObject->optionalCast<DesignSpecificationOutdoorAir>() : boost::none;
  EXPECT_FALSE(directDSOA);
  auto dsoaSpaceList = sizingZoneImpl->designSpecificationOutdoorAirSpaceList();
  ASSERT_TRUE(dsoaSpaceList);
  auto mapped = dsoaSpaceList->designSpecificationOutdoorAir(space);
  ASSERT_TRUE(mapped);
  EXPECT_EQ(dsoa, *mapped);
}

TEST_F(EPModelFixture, API_Space_DesignSpecificationOutdoorAir_FromSpaceSetter) {
  Model model;
  ThermalZone zone(model);
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));

  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  auto spaceDSOA = space.designSpecificationOutdoorAir();
  ASSERT_TRUE(spaceDSOA);
  EXPECT_EQ(dsoa, *spaceDSOA);
}

TEST_F(EPModelFixture, API_SizingZone_Canonicalize_NormalizesDirectToSpaceList_SingleSpace) {
  Model model;
  ThermalZone zone(model);
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));

  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  model.canonicalize(SanitizationPolicy::Repair);

  auto sizingZone = zone.sizingZone();
  auto sizingZoneImpl = sizingZone.getImpl<detail::SizingZone_Impl>();
  ASSERT_TRUE(sizingZoneImpl);
  auto dsoaObject = sizingZone.getModelObjectTarget<ModelObject>(openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName);
  auto directDSOA = dsoaObject ? dsoaObject->optionalCast<DesignSpecificationOutdoorAir>() : boost::none;
  EXPECT_FALSE(directDSOA);
  auto spaceList = sizingZoneImpl->designSpecificationOutdoorAirSpaceList();
  ASSERT_TRUE(spaceList);
  const auto spaces = spaceList->spaces();
  ASSERT_EQ(1u, spaces.size());
  EXPECT_EQ(space, spaces.front());
  auto listedDSOA = spaceList->designSpecificationOutdoorAir(space);
  ASSERT_TRUE(listedDSOA);
  EXPECT_EQ(dsoa, *listedDSOA);
}

TEST_F(EPModelFixture, API_SizingZone_Canonicalize_NormalizesDirectToSpaceList_MultiSpace) {
  Model model;
  ThermalZone zone(model);
  Space space1(model);
  Space space2(model);
  ASSERT_TRUE(space1.setThermalZone(zone));
  ASSERT_TRUE(space2.setThermalZone(zone));

  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(space1.setDesignSpecificationOutdoorAir(dsoa));
  ASSERT_TRUE(space2.setDesignSpecificationOutdoorAir(dsoa));

  model.canonicalize(SanitizationPolicy::Repair);

  auto sizingZone = zone.sizingZone();
  auto sizingZoneImpl = sizingZone.getImpl<detail::SizingZone_Impl>();
  ASSERT_TRUE(sizingZoneImpl);
  auto dsoaObject = sizingZone.getModelObjectTarget<ModelObject>(openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName);
  auto directDSOA = dsoaObject ? dsoaObject->optionalCast<DesignSpecificationOutdoorAir>() : boost::none;
  EXPECT_FALSE(directDSOA);
  auto spaceList = sizingZoneImpl->designSpecificationOutdoorAirSpaceList();
  ASSERT_TRUE(spaceList);
  EXPECT_EQ(2u, spaceList->spaces().size());
  auto listed1 = spaceList->designSpecificationOutdoorAir(space1);
  auto listed2 = spaceList->designSpecificationOutdoorAir(space2);
  ASSERT_TRUE(listed1);
  ASSERT_TRUE(listed2);
  EXPECT_EQ(dsoa, *listed1);
  EXPECT_EQ(dsoa, *listed2);
}

TEST_F(EPModelFixture, API_Space_DesignSpecificationOutdoorAir_FromSpaceList) {
  Model model;
  ThermalZone zone(model);
  Space space1(model);
  Space space2(model);
  ASSERT_TRUE(space1.setThermalZone(zone));
  ASSERT_TRUE(space2.setThermalZone(zone));

  DesignSpecificationOutdoorAir dsoa1(model);
  DesignSpecificationOutdoorAir dsoa2(model);
  dsoa1.setOutdoorAirFlowRate(0.1);
  dsoa2.setOutdoorAirFlowRate(0.2);

  ASSERT_TRUE(space1.setDesignSpecificationOutdoorAir(dsoa1));
  ASSERT_TRUE(space2.setDesignSpecificationOutdoorAir(dsoa2));

  auto space1DSOA = space1.designSpecificationOutdoorAir();
  auto space2DSOA = space2.designSpecificationOutdoorAir();
  ASSERT_TRUE(space1DSOA);
  ASSERT_TRUE(space2DSOA);
  EXPECT_EQ(dsoa1, *space1DSOA);
  EXPECT_EQ(dsoa2, *space2DSOA);
}

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAirSpaceList_Canonicalize_DeduplicatesConflictingSpaceRows) {
  Model model;
  Space space(model);
  DesignSpecificationOutdoorAir dsoa1(model);
  DesignSpecificationOutdoorAir dsoa2(model);
  dsoa1.setName("DSOA 1");
  dsoa2.setName("DSOA 2");

  DesignSpecificationOutdoorAirSpaceList list(model);
  list.setName("Orphan Spaces DSOA Space List");

  auto group1 = list.pushExtensibleGroup();
  auto workspaceGroup1 = group1.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(workspaceGroup1);
  ASSERT_TRUE(workspaceGroup1->setPointer(openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceName, space.handle()));
  ASSERT_TRUE(workspaceGroup1->setPointer(
    openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceDesignSpecificationOutdoorAirObjectName, dsoa1.handle()));

  auto group2 = list.pushExtensibleGroup();
  auto workspaceGroup2 = group2.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(workspaceGroup2);
  ASSERT_TRUE(workspaceGroup2->setPointer(openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceName, space.handle()));
  ASSERT_TRUE(workspaceGroup2->setPointer(
    openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceDesignSpecificationOutdoorAirObjectName, dsoa2.handle()));

  EXPECT_EQ(2u, list.numExtensibleGroups());
  model.canonicalize(SanitizationPolicy::Repair);

  EXPECT_EQ(1u, list.numExtensibleGroups());
  auto assigned = list.designSpecificationOutdoorAir(space);
  ASSERT_TRUE(assigned);
  EXPECT_EQ(dsoa1, *assigned);
}
