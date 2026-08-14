/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Curve/CurveTriquadratic.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/BoilerHotWater.hpp"
#include "../StraightComponent/BoilerHotWater_Impl.hpp"

#include <utilities/idd/Boiler_HotWater_FieldEnums.hxx>
#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedFileRemoval
{
 public:
  explicit ScopedFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

}  // namespace

TEST_F(EPModelFixture, BoilerHotWater_DefaultConstructor) {
  Model model;
  BoilerHotWater boiler(model);
  EXPECT_EQ(BoilerHotWater::iddObjectType(), boiler.iddObject().type());
  EXPECT_FALSE(boiler.nameString().empty());
  EXPECT_DOUBLE_EQ(0.8, boiler.nominalThermalEfficiency());
  EXPECT_DOUBLE_EQ(99.0, boiler.waterOutletUpperTemperatureLimit());
  EXPECT_EQ("ConstantFlow", boiler.boilerFlowMode());
  EXPECT_DOUBLE_EQ(1.0, boiler.sizingFactor());
  EXPECT_EQ("General", boiler.endUseSubcategory());
  EXPECT_DOUBLE_EQ(0.0, boiler.onCycleParasiticElectricLoad());
  EXPECT_DOUBLE_EQ(0.0, boiler.offCycleParasiticFuelLoad());
}

TEST_F(EPModelFixture, BoilerHotWater_ScalarAccessors_RoundTrip) {
  Model model;
  BoilerHotWater boiler(model);

  EXPECT_TRUE(boiler.setFuelType("NaturalGas"));
  EXPECT_EQ("NaturalGas", boiler.fuelType());

  EXPECT_TRUE(boiler.setNominalCapacity(12345.0));
  ASSERT_TRUE(boiler.nominalCapacity());
  EXPECT_DOUBLE_EQ(12345.0, boiler.nominalCapacity().get());
  EXPECT_FALSE(boiler.isNominalCapacityAutosized());
  boiler.autosizeNominalCapacity();
  EXPECT_TRUE(boiler.isNominalCapacityAutosized());

  EXPECT_TRUE(boiler.setDesignWaterFlowRate(0.005));
  ASSERT_TRUE(boiler.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.005, boiler.designWaterFlowRate().get());
  boiler.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(boiler.isDesignWaterFlowRateAutosized());

  EXPECT_TRUE(boiler.setMinimumPartLoadRatio(0.2));
  EXPECT_DOUBLE_EQ(0.2, boiler.minimumPartLoadRatio());
  boiler.resetMinimumPartLoadRatio();
  EXPECT_TRUE(boiler.setMinimumPartLoadRatio(0.3));
  EXPECT_DOUBLE_EQ(0.3, boiler.minimumPartLoadRatio());

  EXPECT_TRUE(boiler.setBoilerFlowMode("VariableFlow"));
  EXPECT_EQ("LeavingSetpointModulated", boiler.boilerFlowMode());

  EXPECT_TRUE(boiler.setOnCycleParasiticElectricLoad(10.0));
  EXPECT_DOUBLE_EQ(10.0, boiler.onCycleParasiticElectricLoad());
}

TEST_F(EPModelFixture, BoilerHotWater_StaticValueNames_MirrorModelShape) {
  EXPECT_EQ(BoilerHotWater::validFuelTypeValues(), BoilerHotWater::fuelTypeValues());
  EXPECT_EQ(BoilerHotWater::validEfficiencyCurveTemperatureEvaluationVariableValues(),
            BoilerHotWater::efficiencyCurveTemperatureEvaluationVariableValues());
  EXPECT_EQ(BoilerHotWater::validBoilerFlowModeValues(), BoilerHotWater::boilerFlowModeValues());
  EXPECT_FALSE(BoilerHotWater::validFuelTypeValues().empty());
  EXPECT_FALSE(BoilerHotWater::validBoilerFlowModeValues().empty());
}

TEST_F(EPModelFixture, BoilerHotWater_NormalizedBoilerEfficiencyCurve_RoundTripAndReset) {
  Model model;
  BoilerHotWater boiler(model);
  CurveLinear univariateCurve(model);
  CurveBiquadratic bivariateCurve(model);

  EXPECT_FALSE(boiler.normalizedBoilerEfficiencyCurve());

  EXPECT_TRUE(boiler.setNormalizedBoilerEfficiencyCurve(univariateCurve));
  ASSERT_TRUE(boiler.normalizedBoilerEfficiencyCurve());
  EXPECT_EQ(univariateCurve.handle(), boiler.normalizedBoilerEfficiencyCurve()->handle());

  EXPECT_TRUE(boiler.setNormalizedBoilerEfficiencyCurve(bivariateCurve));
  ASSERT_TRUE(boiler.normalizedBoilerEfficiencyCurve());
  EXPECT_EQ(bivariateCurve.handle(), boiler.normalizedBoilerEfficiencyCurve()->handle());

  boiler.resetNormalizedBoilerEfficiencyCurve();
  EXPECT_FALSE(boiler.normalizedBoilerEfficiencyCurve());
  EXPECT_EQ("", boiler.getString(openstudio::Boiler_HotWaterFields::NormalizedBoilerEfficiencyCurveName).get());
}

TEST_F(EPModelFixture, BoilerHotWater_NormalizedBoilerEfficiencyCurve_RejectsInvalidTargetsWithoutChangingOldTargetOrRawText) {
  Model model;
  BoilerHotWater boiler(model);
  CurveLinear allowedCurve(model);
  CurveTriquadratic disallowedCurve(model);
  ASSERT_TRUE(boiler.setNormalizedBoilerEfficiencyCurve(allowedCurve));

  EXPECT_FALSE(boiler.setNormalizedBoilerEfficiencyCurve(disallowedCurve));
  ASSERT_TRUE(boiler.normalizedBoilerEfficiencyCurve());
  EXPECT_EQ(allowedCurve.handle(), boiler.normalizedBoilerEfficiencyCurve()->handle());

  const auto field = openstudio::Boiler_HotWaterFields::NormalizedBoilerEfficiencyCurveName;
  auto boilerWorkspaceImpl = boiler.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(boilerWorkspaceImpl);
  ASSERT_TRUE(boilerWorkspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(boilerWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Unresolved Boiler Curve", false));
  EXPECT_FALSE(boiler.normalizedBoilerEfficiencyCurve());
  EXPECT_FALSE(boiler.setNormalizedBoilerEfficiencyCurve(disallowedCurve));
  EXPECT_FALSE(boiler.normalizedBoilerEfficiencyCurve());
  EXPECT_EQ("Unresolved Boiler Curve", boilerWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
}

TEST_F(EPModelFixture, BoilerHotWater_NormalizedBoilerEfficiencyCurve_RejectsForeignModelTargetWithoutChangingOldTarget) {
  Model model;
  BoilerHotWater boiler(model);
  CurveLinear allowedCurve(model);
  ASSERT_TRUE(boiler.setNormalizedBoilerEfficiencyCurve(allowedCurve));

  Model foreignModel;
  CurveLinear foreignCurve(foreignModel);
  EXPECT_FALSE(boiler.setNormalizedBoilerEfficiencyCurve(foreignCurve));
  ASSERT_TRUE(boiler.normalizedBoilerEfficiencyCurve());
  EXPECT_EQ(allowedCurve.handle(), boiler.normalizedBoilerEfficiencyCurve()->handle());
}

TEST_F(EPModelFixture, BoilerHotWater_NormalizedBoilerEfficiencyCurve_SaveLoadIdentityByName) {
  const auto idfPath =
    openstudio::tempDir()
    / openstudio::toPath("epmodel-boiler-hot-water-normalized-efficiency-curve-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  BoilerHotWater boiler(model);
  CurveBiquadratic curve(model);
  ASSERT_TRUE(boiler.setName("Relationship Boiler"));
  ASSERT_TRUE(curve.setName("Normalized Boiler Efficiency Curve"));
  ASSERT_TRUE(boiler.setNormalizedBoilerEfficiencyCurve(curve));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedBoiler = loadedModel->getConcreteModelObjectByName<BoilerHotWater>("Relationship Boiler");
  auto loadedCurve = loadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Normalized Boiler Efficiency Curve");
  ASSERT_TRUE(loadedBoiler);
  ASSERT_TRUE(loadedCurve);
  ASSERT_TRUE(loadedBoiler->normalizedBoilerEfficiencyCurve());
  EXPECT_EQ(loadedCurve->handle(), loadedBoiler->normalizedBoilerEfficiencyCurve()->handle());
}

TEST_F(EPModelFixture, BoilerHotWater_AddToNode_PlantSupplyOnly) {
  Model model;
  BoilerHotWater boiler(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(boiler.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  PlantLoop plantLoop(model);
  auto supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(boiler.addToNode(supplyOutletNode));
  EXPECT_EQ("Water", plantLoop.fluidType());
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());

  auto demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(boiler.addToNode(demandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}
