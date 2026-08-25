/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/RefrigerationCase.hpp"
#include "../ParentObject/RefrigerationCase_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Refrigeration_Case_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedRefrigerationCaseFileRemoval
{
 public:
  explicit ScopedRefrigerationCaseFileRemoval(openstudio::path path) : m_path(std::move(path)) {}
  ~ScopedRefrigerationCaseFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueRefrigerationCasePath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, RefrigerationCase_DefaultConstructor) {
  Model model;
  RefrigerationCase refrigerationCase(model);
  EXPECT_EQ(RefrigerationCase::iddObjectType(), openstudio::IddObjectType::Refrigeration_Case);
  EXPECT_FALSE(refrigerationCase.availabilitySchedule());
  EXPECT_FALSE(refrigerationCase.caseLightingSchedule());
  EXPECT_FALSE(refrigerationCase.caseDefrostSchedule());
  EXPECT_FALSE(refrigerationCase.caseDefrostDripDownSchedule());
  EXPECT_FALSE(refrigerationCase.refrigeratedCaseRestockingSchedule());
  EXPECT_FALSE(refrigerationCase.caseCreditFractionSchedule());
}

TEST_F(EPModelFixture, RefrigerationCase_ScheduleRelationshipsValidationAndReset) {
  Model model;
  RefrigerationCase refrigerationCase(model);
  ScheduleConstant availability(model);
  ScheduleConstant lighting(model);
  ScheduleConstant defrost(model);
  ScheduleConstant dripDown(model);
  ScheduleConstant restocking(model);
  ScheduleConstant creditFraction(model);
  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(lighting.setValue(0.5));
  ASSERT_TRUE(defrost.setValue(1.0));
  ASSERT_TRUE(dripDown.setValue(0.25));
  ASSERT_TRUE(restocking.setValue(125.0));
  ASSERT_TRUE(creditFraction.setValue(0.5));

  ASSERT_TRUE(refrigerationCase.setAvailabilitySchedule(availability));
  ASSERT_TRUE(refrigerationCase.setCaseLightingSchedule(lighting));
  ASSERT_TRUE(refrigerationCase.setCaseDefrostSchedule(defrost));
  ASSERT_TRUE(refrigerationCase.setCaseDefrostDripDownSchedule(dripDown));
  ASSERT_TRUE(refrigerationCase.setRefrigeratedCaseRestockingSchedule(restocking));
  ASSERT_TRUE(refrigerationCase.setCaseCreditFractionSchedule(creditFraction));
  ASSERT_TRUE(refrigerationCase.availabilitySchedule());
  ASSERT_TRUE(refrigerationCase.caseLightingSchedule());
  ASSERT_TRUE(refrigerationCase.caseDefrostSchedule());
  ASSERT_TRUE(refrigerationCase.caseDefrostDripDownSchedule());
  ASSERT_TRUE(refrigerationCase.refrigeratedCaseRestockingSchedule());
  ASSERT_TRUE(refrigerationCase.caseCreditFractionSchedule());
  EXPECT_EQ(availability.handle(), refrigerationCase.availabilitySchedule()->handle());
  EXPECT_EQ(lighting.handle(), refrigerationCase.caseLightingSchedule()->handle());
  EXPECT_EQ(defrost.handle(), refrigerationCase.caseDefrostSchedule()->handle());
  EXPECT_EQ(dripDown.handle(), refrigerationCase.caseDefrostDripDownSchedule()->handle());
  EXPECT_EQ(restocking.handle(), refrigerationCase.refrigeratedCaseRestockingSchedule()->handle());
  EXPECT_EQ(creditFraction.handle(), refrigerationCase.caseCreditFractionSchedule()->handle());

  ASSERT_TRUE(availability.scheduleTypeLimits());
  ASSERT_TRUE(availability.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Discrete", *availability.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Availability", availability.scheduleTypeLimits()->unitType());
  ASSERT_TRUE(availability.scheduleTypeLimits()->lowerLimitValue());
  ASSERT_TRUE(availability.scheduleTypeLimits()->upperLimitValue());
  EXPECT_DOUBLE_EQ(0.0, *availability.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_DOUBLE_EQ(1.0, *availability.scheduleTypeLimits()->upperLimitValue());
  for (const auto* schedule : {&lighting, &defrost, &dripDown, &creditFraction}) {
    ASSERT_TRUE(schedule->scheduleTypeLimits());
    ASSERT_TRUE(schedule->scheduleTypeLimits()->numericType());
    EXPECT_EQ("Continuous", *schedule->scheduleTypeLimits()->numericType());
    EXPECT_TRUE(schedule->scheduleTypeLimits()->isUnitTypeDefaulted());
    ASSERT_TRUE(schedule->scheduleTypeLimits()->lowerLimitValue());
    ASSERT_TRUE(schedule->scheduleTypeLimits()->upperLimitValue());
    EXPECT_DOUBLE_EQ(0.0, *schedule->scheduleTypeLimits()->lowerLimitValue());
    EXPECT_DOUBLE_EQ(1.0, *schedule->scheduleTypeLimits()->upperLimitValue());
  }
  ASSERT_TRUE(restocking.scheduleTypeLimits());
  ASSERT_TRUE(restocking.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Continuous", *restocking.scheduleTypeLimits()->numericType());
  EXPECT_EQ("LinearPowerDensity", restocking.scheduleTypeLimits()->unitType());
  ASSERT_TRUE(restocking.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_DOUBLE_EQ(0.0, *restocking.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_FALSE(restocking.scheduleTypeLimits()->upperLimitValue());

  ScheduleConstant incompatible(model);
  ScheduleTypeLimits incompatibleLimits(model);
  ASSERT_TRUE(incompatibleLimits.setNumericType("Discrete"));
  ASSERT_TRUE(incompatibleLimits.setUnitType("Availability"));
  ASSERT_TRUE(incompatible.setScheduleTypeLimits(incompatibleLimits));
  ScheduleConstant incompatibleAvailability(model);
  ScheduleTypeLimits incompatibleAvailabilityLimits(model);
  ASSERT_TRUE(incompatibleAvailabilityLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatibleAvailability.setScheduleTypeLimits(incompatibleAvailabilityLimits));
  Model foreignModel;
  ScheduleConstant foreign(foreignModel);
  EXPECT_FALSE(refrigerationCase.setCaseLightingSchedule(incompatible));
  EXPECT_FALSE(refrigerationCase.setCaseDefrostSchedule(incompatible));
  EXPECT_FALSE(refrigerationCase.setCaseDefrostDripDownSchedule(incompatible));
  EXPECT_FALSE(refrigerationCase.setRefrigeratedCaseRestockingSchedule(incompatible));
  EXPECT_FALSE(refrigerationCase.setCaseCreditFractionSchedule(incompatible));
  EXPECT_FALSE(refrigerationCase.setAvailabilitySchedule(incompatibleAvailability));
  EXPECT_FALSE(refrigerationCase.setCaseLightingSchedule(foreign));
  EXPECT_EQ(lighting.handle(), refrigerationCase.caseLightingSchedule()->handle());
  EXPECT_EQ(defrost.handle(), refrigerationCase.caseDefrostSchedule()->handle());
  EXPECT_EQ(dripDown.handle(), refrigerationCase.caseDefrostDripDownSchedule()->handle());
  EXPECT_EQ(restocking.handle(), refrigerationCase.refrigeratedCaseRestockingSchedule()->handle());
  EXPECT_EQ(creditFraction.handle(), refrigerationCase.caseCreditFractionSchedule()->handle());
  EXPECT_EQ(availability.handle(), refrigerationCase.availabilitySchedule()->handle());

  auto workspaceImpl = refrigerationCase.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  constexpr auto lightingField = openstudio::Refrigeration_CaseFields::CaseLightingScheduleName;
  ASSERT_TRUE(workspaceImpl->setPointer(lightingField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(lightingField, "Unresolved Case Lighting", false));
  refrigerationCase.resetAvailabilitySchedule();
  refrigerationCase.resetCaseLightingSchedule();
  refrigerationCase.resetCaseDefrostSchedule();
  refrigerationCase.resetCaseDefrostDripDownSchedule();
  refrigerationCase.resetRefrigeratedCaseRestockingSchedule();
  refrigerationCase.resetCaseCreditFractionSchedule();
  EXPECT_FALSE(refrigerationCase.availabilitySchedule());
  EXPECT_FALSE(refrigerationCase.caseLightingSchedule());
  EXPECT_FALSE(refrigerationCase.caseDefrostSchedule());
  EXPECT_FALSE(refrigerationCase.caseDefrostDripDownSchedule());
  EXPECT_FALSE(refrigerationCase.refrigeratedCaseRestockingSchedule());
  EXPECT_FALSE(refrigerationCase.caseCreditFractionSchedule());
  for (const auto field :
       {openstudio::Refrigeration_CaseFields::AvailabilityScheduleName, openstudio::Refrigeration_CaseFields::CaseLightingScheduleName,
        openstudio::Refrigeration_CaseFields::CaseDefrostScheduleName, openstudio::Refrigeration_CaseFields::CaseDefrostDripDownScheduleName,
        openstudio::Refrigeration_CaseFields::RefrigeratedCaseRestockingScheduleName,
        openstudio::Refrigeration_CaseFields::CaseCreditFractionScheduleName}) {
    EXPECT_EQ("", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
  }
}

TEST_F(EPModelFixture, RefrigerationCase_SchedulesSurviveReloadMutationAndRemoval) {
  const auto firstPath = uniqueRefrigerationCasePath("epmodel-refrigeration-case-schedules-first");
  const auto secondPath = uniqueRefrigerationCasePath("epmodel-refrigeration-case-schedules-second");
  const ScopedRefrigerationCaseFileRemoval removeFirst(firstPath);
  const ScopedRefrigerationCaseFileRemoval removeSecond(secondPath);

  Model model;
  RefrigerationCase refrigerationCase(model);
  ScheduleConstant availability(model);
  ScheduleConstant lighting(model);
  ScheduleConstant defrost(model);
  ScheduleConstant dripDown(model);
  ScheduleConstant restocking(model);
  ScheduleConstant creditFraction(model);
  ASSERT_TRUE(refrigerationCase.setName("Reloadable Refrigeration Case"));
  ASSERT_TRUE(availability.setName("Refrigeration Case Availability"));
  ASSERT_TRUE(lighting.setName("Refrigeration Case Lighting"));
  ASSERT_TRUE(defrost.setName("Refrigeration Case Defrost"));
  ASSERT_TRUE(dripDown.setName("Refrigeration Case Drip Down"));
  ASSERT_TRUE(restocking.setName("Refrigeration Case Restocking"));
  ASSERT_TRUE(creditFraction.setName("Refrigeration Case Credit Fraction"));
  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(lighting.setValue(0.5));
  ASSERT_TRUE(defrost.setValue(1.0));
  ASSERT_TRUE(dripDown.setValue(0.25));
  ASSERT_TRUE(restocking.setValue(125.0));
  ASSERT_TRUE(creditFraction.setValue(0.5));
  ASSERT_TRUE(refrigerationCase.setAvailabilitySchedule(availability));
  ASSERT_TRUE(refrigerationCase.setCaseLightingSchedule(lighting));
  ASSERT_TRUE(refrigerationCase.setCaseDefrostSchedule(defrost));
  ASSERT_TRUE(refrigerationCase.setCaseDefrostDripDownSchedule(dripDown));
  ASSERT_TRUE(refrigerationCase.setRefrigeratedCaseRestockingSchedule(restocking));
  ASSERT_TRUE(refrigerationCase.setCaseCreditFractionSchedule(creditFraction));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCase = loadedModel->getConcreteModelObjectByName<RefrigerationCase>("Reloadable Refrigeration Case");
  auto loadedAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Refrigeration Case Availability");
  auto loadedLighting = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Refrigeration Case Lighting");
  auto loadedDefrost = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Refrigeration Case Defrost");
  auto loadedDripDown = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Refrigeration Case Drip Down");
  auto loadedRestocking = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Refrigeration Case Restocking");
  auto loadedCreditFraction = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Refrigeration Case Credit Fraction");
  ASSERT_TRUE(loadedCase);
  ASSERT_TRUE(loadedAvailability);
  ASSERT_TRUE(loadedLighting);
  ASSERT_TRUE(loadedDefrost);
  ASSERT_TRUE(loadedDripDown);
  ASSERT_TRUE(loadedRestocking);
  ASSERT_TRUE(loadedCreditFraction);
  ASSERT_TRUE(loadedCase->availabilitySchedule());
  ASSERT_TRUE(loadedCase->caseLightingSchedule());
  ASSERT_TRUE(loadedCase->caseDefrostSchedule());
  ASSERT_TRUE(loadedCase->caseDefrostDripDownSchedule());
  ASSERT_TRUE(loadedCase->refrigeratedCaseRestockingSchedule());
  ASSERT_TRUE(loadedCase->caseCreditFractionSchedule());
  EXPECT_EQ(loadedAvailability->handle(), loadedCase->availabilitySchedule()->handle());
  EXPECT_EQ(loadedLighting->handle(), loadedCase->caseLightingSchedule()->handle());
  EXPECT_EQ(loadedDefrost->handle(), loadedCase->caseDefrostSchedule()->handle());
  EXPECT_EQ(loadedDripDown->handle(), loadedCase->caseDefrostDripDownSchedule()->handle());
  EXPECT_EQ(loadedRestocking->handle(), loadedCase->refrigeratedCaseRestockingSchedule()->handle());
  EXPECT_EQ(loadedCreditFraction->handle(), loadedCase->caseCreditFractionSchedule()->handle());

  ScheduleConstant replacementLighting(*loadedModel);
  ASSERT_TRUE(replacementLighting.setName("Replacement Refrigeration Case Lighting"));
  ASSERT_TRUE(replacementLighting.setValue(0.75));
  ASSERT_TRUE(loadedCase->setCaseLightingSchedule(replacementLighting));
  loadedCase->resetCaseDefrostDripDownSchedule();
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCase = reloadedModel->getConcreteModelObjectByName<RefrigerationCase>("Reloadable Refrigeration Case");
  auto reloadedAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Refrigeration Case Availability");
  auto reloadedReplacement = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Refrigeration Case Lighting");
  auto reloadedDefrost = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Refrigeration Case Defrost");
  auto reloadedRestocking = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Refrigeration Case Restocking");
  auto reloadedCreditFraction = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Refrigeration Case Credit Fraction");
  ASSERT_TRUE(reloadedCase);
  ASSERT_TRUE(reloadedAvailability);
  ASSERT_TRUE(reloadedReplacement);
  ASSERT_TRUE(reloadedDefrost);
  ASSERT_TRUE(reloadedRestocking);
  ASSERT_TRUE(reloadedCreditFraction);
  ASSERT_TRUE(reloadedCase->availabilitySchedule());
  ASSERT_TRUE(reloadedCase->caseLightingSchedule());
  ASSERT_TRUE(reloadedCase->caseDefrostSchedule());
  EXPECT_FALSE(reloadedCase->caseDefrostDripDownSchedule());
  ASSERT_TRUE(reloadedCase->refrigeratedCaseRestockingSchedule());
  ASSERT_TRUE(reloadedCase->caseCreditFractionSchedule());
  EXPECT_EQ(reloadedAvailability->handle(), reloadedCase->availabilitySchedule()->handle());
  EXPECT_EQ(reloadedReplacement->handle(), reloadedCase->caseLightingSchedule()->handle());
  EXPECT_EQ(reloadedDefrost->handle(), reloadedCase->caseDefrostSchedule()->handle());
  EXPECT_EQ(reloadedRestocking->handle(), reloadedCase->refrigeratedCaseRestockingSchedule()->handle());
  EXPECT_EQ(reloadedCreditFraction->handle(), reloadedCase->caseCreditFractionSchedule()->handle());

  EXPECT_FALSE(reloadedCase->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedAvailability->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacement->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedDefrost->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedRestocking->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedCreditFraction->handle()));
  EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Refrigeration Case Drip Down"));
}

TEST_F(EPModelFixture, RefrigerationCase_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationCase refrigerationCase(model);

  EXPECT_TRUE(refrigerationCase.setRatedAmbientTemperature(25.0));
  EXPECT_DOUBLE_EQ(25.0, refrigerationCase.ratedAmbientTemperature());
  EXPECT_FALSE(refrigerationCase.isRatedAmbientTemperatureDefaulted());
  refrigerationCase.resetRatedAmbientTemperature();
  EXPECT_TRUE(refrigerationCase.isRatedAmbientTemperatureDefaulted());

  const auto defrostTypes = RefrigerationCase::caseDefrostTypeValues();
  ASSERT_FALSE(defrostTypes.empty());
  EXPECT_TRUE(refrigerationCase.setCaseDefrostType(defrostTypes.front()));
  EXPECT_EQ(defrostTypes.front(), refrigerationCase.caseDefrostType());
  refrigerationCase.resetCaseDefrostType();
  EXPECT_TRUE(refrigerationCase.isCaseDefrostTypeDefaulted());

  const auto latentValues = RefrigerationCase::latentCaseCreditCurveTypeValues();
  ASSERT_FALSE(latentValues.empty());
  EXPECT_TRUE(refrigerationCase.setLatentCaseCreditCurveType(latentValues.front()));
  EXPECT_EQ(latentValues.front(), refrigerationCase.latentCaseCreditCurveType());

  EXPECT_TRUE(refrigerationCase.setInstalledCaseLightingPowerperUnitLength(42.0));
  ASSERT_TRUE(refrigerationCase.installedCaseLightingPowerperUnitLength());
  EXPECT_DOUBLE_EQ(42.0, refrigerationCase.installedCaseLightingPowerperUnitLength().get());
  refrigerationCase.resetInstalledCaseLightingPowerperUnitLength();
  EXPECT_FALSE(refrigerationCase.installedCaseLightingPowerperUnitLength());

  EXPECT_TRUE(refrigerationCase.setDesignEvaporatorTemperatureorBrineInletTemperature(-5.0));
  ASSERT_TRUE(refrigerationCase.designEvaporatorTemperatureorBrineInletTemperature());
  EXPECT_DOUBLE_EQ(-5.0, refrigerationCase.designEvaporatorTemperatureorBrineInletTemperature().get());
  refrigerationCase.resetDesignEvaporatorTemperatureorBrineInletTemperature();
  EXPECT_FALSE(refrigerationCase.designEvaporatorTemperatureorBrineInletTemperature());

  EXPECT_TRUE(refrigerationCase.setAverageRefrigerantChargeInventory(1.25));
  EXPECT_DOUBLE_EQ(1.25, refrigerationCase.averageRefrigerantChargeInventory());
}
