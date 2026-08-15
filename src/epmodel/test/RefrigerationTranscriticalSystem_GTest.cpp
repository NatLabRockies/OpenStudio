/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/FluidPropertiesName.hpp"
#include "../ModelObject/RefrigerationTranscriticalSystem.hpp"
#include "../ModelObject/RefrigerationTranscriticalSystem_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Refrigeration_TranscriticalSystem_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedTranscriticalSystemFileRemoval
{
 public:
  explicit ScopedTranscriticalSystemFileRemoval(openstudio::path path) : m_path(std::move(path)) {}
  ~ScopedTranscriticalSystemFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueTranscriticalSystemPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, RefrigerationTranscriticalSystem_DefaultConstructor) {
  Model model;
  RefrigerationTranscriticalSystem system(model);
  EXPECT_EQ(RefrigerationTranscriticalSystem::iddObjectType(), system.iddObject().type());
  EXPECT_DOUBLE_EQ(3500000.0, system.receiverPressure());
  EXPECT_DOUBLE_EQ(0.4, system.subcoolerEffectiveness());
  EXPECT_EQ("R744", system.refrigerationSystemWorkingFluidType());
  EXPECT_DOUBLE_EQ(0.0, system.sumUASuctionPipingforMediumTemperatureLoads());
  EXPECT_DOUBLE_EQ(0.0, system.sumUASuctionPipingforLowTemperatureLoads());
  EXPECT_FALSE(system.mediumTemperatureSuctionPipingZone());
  EXPECT_FALSE(system.lowTemperatureSuctionPipingZone());
  EXPECT_TRUE(system.isEndUseSubcategoryDefaulted());
}

TEST_F(EPModelFixture, RefrigerationTranscriticalSystem_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationTranscriticalSystem system(model);

  EXPECT_TRUE(system.setReceiverPressure(3600000.0));
  EXPECT_DOUBLE_EQ(3600000.0, system.receiverPressure());
  system.resetReceiverPressure();
  EXPECT_TRUE(system.isReceiverPressureDefaulted());

  EXPECT_TRUE(system.setSubcoolerEffectiveness(0.5));
  EXPECT_DOUBLE_EQ(0.5, system.subcoolerEffectiveness());
  system.resetSubcoolerEffectiveness();
  EXPECT_TRUE(system.isSubcoolerEffectivenessDefaulted());

  FluidPropertiesName fluid(model);
  ASSERT_FALSE(fluid.fluidTypeValues().empty());
  EXPECT_TRUE(fluid.setFluidName("R134a"));
  EXPECT_TRUE(fluid.setFluidType(fluid.fluidTypeValues().front()));
  EXPECT_TRUE(system.setRefrigerationSystemWorkingFluidType(fluid.fluidName()));
  EXPECT_EQ(fluid.fluidName(), system.refrigerationSystemWorkingFluidType());

  EXPECT_TRUE(system.setSumUASuctionPipingforMediumTemperatureLoads(1.1));
  EXPECT_DOUBLE_EQ(1.1, system.sumUASuctionPipingforMediumTemperatureLoads());
  system.resetSumUASuctionPipingforMediumTemperatureLoads();
  EXPECT_TRUE(system.isSumUASuctionPipingforMediumTemperatureLoadsDefaulted());

  EXPECT_TRUE(system.setSumUASuctionPipingforLowTemperatureLoads(2.2));
  EXPECT_DOUBLE_EQ(2.2, system.sumUASuctionPipingforLowTemperatureLoads());
  system.resetSumUASuctionPipingforLowTemperatureLoads();
  EXPECT_TRUE(system.isSumUASuctionPipingforLowTemperatureLoadsDefaulted());

  EXPECT_TRUE(system.setEndUseSubcategory("Grocery"));
  EXPECT_EQ("Grocery", system.endUseSubcategory());
  EXPECT_FALSE(system.isEndUseSubcategoryDefaulted());
  system.resetEndUseSubcategory();
  EXPECT_TRUE(system.isEndUseSubcategoryDefaulted());
}

TEST_F(EPModelFixture, RefrigerationTranscriticalSystem_SuctionPipingZonesRoundTripAndRejectForeignModels) {
  Model model;
  RefrigerationTranscriticalSystem system(model);
  ThermalZone mediumZone(model);
  ThermalZone lowZone(model);

  constexpr auto mediumField = openstudio::Refrigeration_TranscriticalSystemFields::MediumTemperatureSuctionPipingZoneName;
  constexpr auto lowField = openstudio::Refrigeration_TranscriticalSystemFields::LowTemperatureSuctionPipingZoneName;
  EXPECT_TRUE(model.canBeTarget(mediumZone.handle(), system.iddObject().objectLists(mediumField)));
  EXPECT_TRUE(model.canBeTarget(lowZone.handle(), system.iddObject().objectLists(lowField)));
  EXPECT_FALSE(model.canBeTarget(system.handle(), system.iddObject().objectLists(mediumField)));

  ASSERT_TRUE(system.setMediumTemperatureSuctionPipingZone(mediumZone));
  ASSERT_TRUE(system.setLowTemperatureSuctionPipingZone(lowZone));
  ASSERT_TRUE(system.mediumTemperatureSuctionPipingZone());
  ASSERT_TRUE(system.lowTemperatureSuctionPipingZone());
  EXPECT_EQ(mediumZone.handle(), system.mediumTemperatureSuctionPipingZone()->handle());
  EXPECT_EQ(lowZone.handle(), system.lowTemperatureSuctionPipingZone()->handle());

  ASSERT_TRUE(system.setLowTemperatureSuctionPipingZone(mediumZone));
  EXPECT_EQ(mediumZone.handle(), system.lowTemperatureSuctionPipingZone()->handle());

  Model foreignModel;
  ThermalZone foreignZone(foreignModel);
  EXPECT_FALSE(system.setMediumTemperatureSuctionPipingZone(foreignZone));
  EXPECT_FALSE(system.setLowTemperatureSuctionPipingZone(foreignZone));
  EXPECT_EQ(mediumZone.handle(), system.mediumTemperatureSuctionPipingZone()->handle());
  EXPECT_EQ(mediumZone.handle(), system.lowTemperatureSuctionPipingZone()->handle());

  system.resetMediumTemperatureSuctionPipingZone();
  EXPECT_FALSE(system.mediumTemperatureSuctionPipingZone());
  EXPECT_EQ(mediumZone.handle(), system.lowTemperatureSuctionPipingZone()->handle());
  system.resetLowTemperatureSuctionPipingZone();
  EXPECT_FALSE(system.lowTemperatureSuctionPipingZone());
}

TEST_F(EPModelFixture, RefrigerationTranscriticalSystem_UnresolvedSuctionPipingZonesRemainUntilExplicitlyChanged) {
  Model model;
  RefrigerationTranscriticalSystem system(model);
  constexpr auto mediumField = openstudio::Refrigeration_TranscriticalSystemFields::MediumTemperatureSuctionPipingZoneName;
  constexpr auto lowField = openstudio::Refrigeration_TranscriticalSystemFields::LowTemperatureSuctionPipingZoneName;

  // Public typed APIs cannot create unresolved object-list references. Seed that imported malformed state deliberately so
  // canonicalization, failed typed setters, explicit repair, and raw-clearing reset can be observed.
  auto impl = system.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(impl);
  const auto setUnresolvedRaw = [&](unsigned field, const std::string& value) {
    ASSERT_TRUE(impl->setPointer(field, openstudio::Handle(), false));
    ASSERT_TRUE(impl->openstudio::detail::IdfObject_Impl::setString(field, value, false));
  };
  const auto rawValue = [&](unsigned field) { return impl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""); };
  setUnresolvedRaw(mediumField, "Missing Medium Suction Zone");
  setUnresolvedRaw(lowField, "Missing Low Suction Zone");
  EXPECT_FALSE(system.mediumTemperatureSuctionPipingZone());
  EXPECT_FALSE(system.lowTemperatureSuctionPipingZone());

  Model foreignModel;
  ThermalZone foreignZone(foreignModel);
  EXPECT_FALSE(system.setMediumTemperatureSuctionPipingZone(foreignZone));
  EXPECT_FALSE(system.setLowTemperatureSuctionPipingZone(foreignZone));
  EXPECT_EQ("Missing Medium Suction Zone", rawValue(mediumField));
  EXPECT_EQ("Missing Low Suction Zone", rawValue(lowField));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ("Missing Medium Suction Zone", rawValue(mediumField));
  EXPECT_EQ("Missing Low Suction Zone", rawValue(lowField));

  ThermalZone repairedZone(model);
  ASSERT_TRUE(system.setMediumTemperatureSuctionPipingZone(repairedZone));
  ASSERT_TRUE(system.mediumTemperatureSuctionPipingZone());
  EXPECT_EQ(repairedZone.handle(), system.mediumTemperatureSuctionPipingZone()->handle());
  system.resetLowTemperatureSuctionPipingZone();
  EXPECT_FALSE(system.lowTemperatureSuctionPipingZone());
  EXPECT_TRUE(rawValue(lowField).empty());
}

TEST_F(EPModelFixture, RefrigerationTranscriticalSystem_SuctionPipingZonesSurviveReloadMutationAndRemoval) {
  const auto firstIdfPath = uniqueTranscriticalSystemPath("epmodel-transcritical-zones-first");
  const auto secondIdfPath = uniqueTranscriticalSystemPath("epmodel-transcritical-zones-second");
  const ScopedTranscriticalSystemFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedTranscriticalSystemFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  RefrigerationTranscriticalSystem system(model);
  ThermalZone mediumZone(model);
  ThermalZone lowZone(model);
  ASSERT_TRUE(system.setName("Reloaded Transcritical System"));
  ASSERT_TRUE(mediumZone.setName("Original Medium Suction Zone"));
  ASSERT_TRUE(lowZone.setName("Original Low Suction Zone"));
  ASSERT_TRUE(system.setMediumTemperatureSuctionPipingZone(mediumZone));
  ASSERT_TRUE(system.setLowTemperatureSuctionPipingZone(lowZone));
  ASSERT_TRUE(system.setSumUASuctionPipingforMediumTemperatureLoads(1.25));
  ASSERT_TRUE(system.setSumUASuctionPipingforLowTemperatureLoads(2.5));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<RefrigerationTranscriticalSystem>("Reloaded Transcritical System");
  auto loadedMediumZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Original Medium Suction Zone");
  auto loadedLowZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Original Low Suction Zone");
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedMediumZone);
  ASSERT_TRUE(loadedLowZone);
  ASSERT_TRUE(loadedSystem->mediumTemperatureSuctionPipingZone());
  ASSERT_TRUE(loadedSystem->lowTemperatureSuctionPipingZone());
  EXPECT_EQ(loadedMediumZone->handle(), loadedSystem->mediumTemperatureSuctionPipingZone()->handle());
  EXPECT_EQ(loadedLowZone->handle(), loadedSystem->lowTemperatureSuctionPipingZone()->handle());
  EXPECT_DOUBLE_EQ(1.25, loadedSystem->sumUASuctionPipingforMediumTemperatureLoads());
  EXPECT_DOUBLE_EQ(2.5, loadedSystem->sumUASuctionPipingforLowTemperatureLoads());

  ThermalZone replacementZone(*loadedModel);
  ASSERT_TRUE(replacementZone.setName("Replacement Medium Suction Zone"));
  ASSERT_TRUE(loadedSystem->setMediumTemperatureSuctionPipingZone(replacementZone));
  loadedSystem->resetLowTemperatureSuctionPipingZone();
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSystem = reloadedModel->getConcreteModelObjectByName<RefrigerationTranscriticalSystem>("Reloaded Transcritical System");
  auto reloadedMediumZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Original Medium Suction Zone");
  auto reloadedLowZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Original Low Suction Zone");
  auto reloadedReplacementZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Replacement Medium Suction Zone");
  ASSERT_TRUE(reloadedSystem);
  ASSERT_TRUE(reloadedMediumZone);
  ASSERT_TRUE(reloadedLowZone);
  ASSERT_TRUE(reloadedReplacementZone);
  ASSERT_TRUE(reloadedSystem->mediumTemperatureSuctionPipingZone());
  EXPECT_EQ(reloadedReplacementZone->handle(), reloadedSystem->mediumTemperatureSuctionPipingZone()->handle());
  EXPECT_FALSE(reloadedSystem->lowTemperatureSuctionPipingZone());

  EXPECT_FALSE(reloadedSystem->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedMediumZone->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedLowZone->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementZone->handle()));
}
