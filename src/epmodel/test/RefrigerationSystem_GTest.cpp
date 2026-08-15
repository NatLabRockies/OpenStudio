/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/FluidPropertiesName.hpp"
#include "../ModelObject/RefrigerationSystem.hpp"
#include "../ModelObject/RefrigerationSystem_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Refrigeration_System_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedRefrigerationSystemFileRemoval
{
 public:
  explicit ScopedRefrigerationSystemFileRemoval(openstudio::path path) : m_path(std::move(path)) {}
  ~ScopedRefrigerationSystemFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueRefrigerationSystemPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, RefrigerationSystem_DefaultConstructor) {
  Model model;
  RefrigerationSystem system(model);

  EXPECT_EQ(RefrigerationSystem::iddObjectType(), system.iddObject().type());
  EXPECT_DOUBLE_EQ(21.0, system.minimumCondensingTemperature());
  EXPECT_EQ("ConstantSuctionTemperature", system.suctionTemperatureControlType());
  EXPECT_FALSE(system.suctionPipingZone());
}

TEST_F(EPModelFixture, RefrigerationSystem_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationSystem system(model);

  EXPECT_TRUE(system.setMinimumCondensingTemperature(24.1));
  EXPECT_DOUBLE_EQ(24.1, system.minimumCondensingTemperature());

  FluidPropertiesName fluid(model);
  ASSERT_FALSE(fluid.fluidTypeValues().empty());
  EXPECT_TRUE(fluid.setFluidName("R404a"));
  EXPECT_TRUE(fluid.setFluidType(fluid.fluidTypeValues().front()));
  EXPECT_TRUE(system.setRefrigerationSystemWorkingFluidType(fluid.fluidName()));
  EXPECT_EQ(fluid.fluidName(), system.refrigerationSystemWorkingFluidType());

  auto intercoolerValues = RefrigerationSystem::intercoolerTypeValues();
  ASSERT_FALSE(intercoolerValues.empty());
  EXPECT_TRUE(system.setIntercoolerType(intercoolerValues.front()));
  EXPECT_EQ(intercoolerValues.front(), system.intercoolerType());

  EXPECT_TRUE(system.setSumUASuctionPiping(5.5));
  EXPECT_DOUBLE_EQ(5.5, system.sumUASuctionPiping());
  EXPECT_FALSE(system.isSumUASuctionPipingDefaulted());

  EXPECT_TRUE(system.setEndUseSubcategory("Retail"));
  EXPECT_EQ("Retail", system.endUseSubcategory());
  EXPECT_FALSE(system.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(system.setShellandCoilIntercoolerEffectiveness(0.85));
  EXPECT_DOUBLE_EQ(0.85, system.shellandCoilIntercoolerEffectiveness());
  EXPECT_FALSE(system.isShellandCoilIntercoolerEffectivenessDefaulted());

  system.resetSumUASuctionPiping();
  EXPECT_TRUE(system.isSumUASuctionPipingDefaulted());

  system.resetEndUseSubcategory();
  EXPECT_TRUE(system.isEndUseSubcategoryDefaulted());

  system.resetIntercoolerType();
  EXPECT_TRUE(system.isIntercoolerTypeDefaulted());

  system.resetShellandCoilIntercoolerEffectiveness();
  EXPECT_TRUE(system.isShellandCoilIntercoolerEffectivenessDefaulted());
}

// The TransferLoadList object only exposes a name, so ensure the base name API round-trips for this type.
TEST_F(EPModelFixture, RefrigerationSystem_TransferLoadListName) {
  Model model;
  RefrigerationSystem system(model);

  const char* listName = "TransferLoadListLink";
  system.setName(listName);
  EXPECT_EQ(listName, system.nameString());
}

TEST_F(EPModelFixture, RefrigerationSystem_SuctionPipingZoneValidationAndUnresolvedState) {
  Model model;
  RefrigerationSystem system(model);
  ThermalZone zone(model);
  constexpr auto field = openstudio::Refrigeration_SystemFields::SuctionPipingZoneName;

  EXPECT_TRUE(model.canBeTarget(zone.handle(), system.iddObject().objectLists(field)));
  EXPECT_FALSE(model.canBeTarget(system.handle(), system.iddObject().objectLists(field)));
  ASSERT_TRUE(system.setSuctionPipingZone(zone));
  ASSERT_TRUE(system.suctionPipingZone());
  EXPECT_EQ(zone.handle(), system.suctionPipingZone()->handle());

  Model foreignModel;
  ThermalZone foreignZone(foreignModel);
  EXPECT_FALSE(system.setSuctionPipingZone(foreignZone));
  EXPECT_EQ(zone.handle(), system.suctionPipingZone()->handle());
  system.resetSuctionPipingZone();
  EXPECT_FALSE(system.suctionPipingZone());

  RefrigerationSystem unresolved(model);
  // Public typed APIs cannot create unresolved object-list references. Seed this imported malformed state deliberately to
  // verify that canonicalization and failed typed mutation preserve it until an explicit reset.
  auto impl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(impl);
  ASSERT_TRUE(impl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(impl->openstudio::detail::IdfObject_Impl::setString(field, "Missing Refrigeration Suction Zone", false));
  const auto rawValue = [&]() { return impl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""); };
  EXPECT_FALSE(unresolved.suctionPipingZone());
  EXPECT_FALSE(unresolved.setSuctionPipingZone(foreignZone));
  EXPECT_EQ("Missing Refrigeration Suction Zone", rawValue());
  EXPECT_EQ(0u, model.canonicalize().errorCount);
  EXPECT_EQ("Missing Refrigeration Suction Zone", rawValue());
  unresolved.resetSuctionPipingZone();
  EXPECT_TRUE(rawValue().empty());
}

TEST_F(EPModelFixture, RefrigerationSystem_SuctionPipingZoneSurvivesReloadMutationAndRemoval) {
  const auto firstIdfPath = uniqueRefrigerationSystemPath("epmodel-refrigeration-system-zone-first");
  const auto secondIdfPath = uniqueRefrigerationSystemPath("epmodel-refrigeration-system-zone-second");
  const ScopedRefrigerationSystemFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedRefrigerationSystemFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  RefrigerationSystem system(model);
  ThermalZone originalZone(model);
  ASSERT_TRUE(system.setName("Reloaded Refrigeration System"));
  ASSERT_TRUE(originalZone.setName("Original Refrigeration Suction Zone"));
  ASSERT_TRUE(system.setSuctionPipingZone(originalZone));
  ASSERT_TRUE(system.setSumUASuctionPiping(1.5));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<RefrigerationSystem>("Reloaded Refrigeration System");
  auto loadedOriginalZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Original Refrigeration Suction Zone");
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedOriginalZone);
  ASSERT_TRUE(loadedSystem->suctionPipingZone());
  EXPECT_EQ(loadedOriginalZone->handle(), loadedSystem->suctionPipingZone()->handle());
  EXPECT_DOUBLE_EQ(1.5, loadedSystem->sumUASuctionPiping());

  ThermalZone replacementZone(*loadedModel);
  ASSERT_TRUE(replacementZone.setName("Replacement Refrigeration Suction Zone"));
  ASSERT_TRUE(loadedSystem->setSuctionPipingZone(replacementZone));
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSystem = reloadedModel->getConcreteModelObjectByName<RefrigerationSystem>("Reloaded Refrigeration System");
  auto reloadedOriginalZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Original Refrigeration Suction Zone");
  auto reloadedReplacementZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Replacement Refrigeration Suction Zone");
  ASSERT_TRUE(reloadedSystem);
  ASSERT_TRUE(reloadedOriginalZone);
  ASSERT_TRUE(reloadedReplacementZone);
  ASSERT_TRUE(reloadedSystem->suctionPipingZone());
  EXPECT_EQ(reloadedReplacementZone->handle(), reloadedSystem->suctionPipingZone()->handle());

  EXPECT_FALSE(reloadedSystem->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedOriginalZone->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementZone->handle()));
}
