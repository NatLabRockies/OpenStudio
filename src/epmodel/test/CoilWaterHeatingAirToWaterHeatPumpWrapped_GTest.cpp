/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <utility>

#include "EPModelFixture.hpp"
#include "../Curve/Curve.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveCubic.hpp"
#include "../Curve/CurveCubic_Impl.hpp"
#include "../Curve/CurveTriquadratic.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilWaterHeatingAirToWaterHeatPumpWrapped.hpp"
#include "../StraightComponent/CoilWaterHeatingAirToWaterHeatPumpWrapped_Impl.hpp"
#include "../StraightComponent/StraightComponent.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser.hpp"
#include "../ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_WaterHeating_AirToWaterHeatPump_Wrapped_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

using namespace openstudio::epmodel;

namespace {

class ScopedWrappedCoilFileRemoval
{
 public:
  explicit ScopedWrappedCoilFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedWrappedCoilFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueWrappedCoilPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

}  // namespace

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpWrapped_DefaultConstructor) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpWrapped coil(model);
  EXPECT_EQ(CoilWaterHeatingAirToWaterHeatPumpWrapped::iddObjectType(), coil.iddObject().type());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coil.availabilitySchedule().handle());
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());

  auto capacityTemperature = coil.heatingCapacityFunctionofTemperatureCurve().cast<CurveBiquadratic>();
  EXPECT_EQ("HPWH-Htg-Cap-fT", capacityTemperature.nameString());
  EXPECT_DOUBLE_EQ(0.563, capacityTemperature.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.0437, capacityTemperature.coefficient2x());
  EXPECT_DOUBLE_EQ(0.000039, capacityTemperature.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0055, capacityTemperature.coefficient4y());
  EXPECT_DOUBLE_EQ(-0.000148, capacityTemperature.coefficient5yPOW2());
  EXPECT_DOUBLE_EQ(-0.000145, capacityTemperature.coefficient6xTIMESY());
  EXPECT_DOUBLE_EQ(0.0, capacityTemperature.minimumValueofx());
  EXPECT_DOUBLE_EQ(100.0, capacityTemperature.maximumValueofx());
  EXPECT_DOUBLE_EQ(0.0, capacityTemperature.minimumValueofy());
  EXPECT_DOUBLE_EQ(100.0, capacityTemperature.maximumValueofy());
  ASSERT_TRUE(capacityTemperature.minimumCurveOutput());
  EXPECT_DOUBLE_EQ(0.0, *capacityTemperature.minimumCurveOutput());

  auto capacityAirFlow = coil.heatingCapacityFunctionofAirFlowFractionCurve().cast<CurveCubic>();
  EXPECT_EQ("HPWH-Htg-Cap-FF", capacityAirFlow.nameString());
  EXPECT_DOUBLE_EQ(1.0, capacityAirFlow.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.0, capacityAirFlow.coefficient2x());
  EXPECT_DOUBLE_EQ(0.0, capacityAirFlow.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, capacityAirFlow.coefficient4xPOW3());
  EXPECT_DOUBLE_EQ(0.0, capacityAirFlow.minimumValueofx());
  EXPECT_DOUBLE_EQ(100.0, capacityAirFlow.maximumValueofx());

  auto copTemperature = coil.heatingCOPFunctionofTemperatureCurve().cast<CurveBiquadratic>();
  EXPECT_EQ("HPWH-Htg-COP-fT", copTemperature.nameString());
  EXPECT_DOUBLE_EQ(1.1332, copTemperature.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.063, copTemperature.coefficient2x());
  EXPECT_DOUBLE_EQ(-0.0000979, copTemperature.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(-0.00972, copTemperature.coefficient4y());
  EXPECT_DOUBLE_EQ(-0.0000214, copTemperature.coefficient5yPOW2());
  EXPECT_DOUBLE_EQ(-0.000686, copTemperature.coefficient6xTIMESY());

  auto copAirFlow = coil.heatingCOPFunctionofAirFlowFractionCurve().cast<CurveCubic>();
  EXPECT_EQ("HPWH-Htg-COP-FF", copAirFlow.nameString());
  EXPECT_DOUBLE_EQ(1.0, copAirFlow.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.0, copAirFlow.coefficient2x());
  EXPECT_DOUBLE_EQ(0.0, copAirFlow.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, copAirFlow.coefficient4xPOW3());

  auto partLoad = coil.partLoadFractionCorrelationCurve().cast<CurveCubic>();
  EXPECT_EQ("HPWH-COP-fPLR", partLoad.nameString());
  EXPECT_DOUBLE_EQ(1.0, partLoad.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.0, partLoad.coefficient2x());
  EXPECT_DOUBLE_EQ(0.0, partLoad.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, partLoad.coefficient4xPOW3());
  EXPECT_DOUBLE_EQ(0.0, partLoad.minimumValueofx());
  EXPECT_DOUBLE_EQ(1.0, partLoad.maximumValueofx());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpWrapped_StraightComponentPortsWithoutLoopPlacement) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpWrapped coil(model);
  Node node(model);

  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirInletNodeName, coil.inletPort());
  EXPECT_EQ(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirOutletNodeName, coil.outletPort());
  EXPECT_FALSE(coil.addToNode(node));
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpWrapped_ScalarAccessors_RoundTrip) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpWrapped coil(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(1.0));

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  ASSERT_TRUE(coil.getTarget(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::AvailabilityScheduleName));
  EXPECT_EQ(availability.handle(),
            coil.getTarget(openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::AvailabilityScheduleName)->handle());

  EXPECT_TRUE(coil.setRatedHeatingCapacity(4000.0));
  EXPECT_DOUBLE_EQ(4000.0, coil.ratedHeatingCapacity());

  EXPECT_TRUE(coil.isRatedCOPDefaulted());
  EXPECT_DOUBLE_EQ(3.2, coil.ratedCOP());
  EXPECT_TRUE(coil.setRatedCOP(3.6));
  EXPECT_DOUBLE_EQ(3.6, coil.ratedCOP());
  EXPECT_FALSE(coil.isRatedCOPDefaulted());
  coil.resetRatedCOP();
  EXPECT_TRUE(coil.isRatedCOPDefaulted());

  EXPECT_TRUE(coil.isRatedSensibleHeatRatioDefaulted());
  EXPECT_DOUBLE_EQ(0.85, coil.ratedSensibleHeatRatio());
  EXPECT_TRUE(coil.setRatedSensibleHeatRatio(0.9));
  EXPECT_DOUBLE_EQ(0.9, coil.ratedSensibleHeatRatio());
  coil.resetRatedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedSensibleHeatRatioDefaulted());

  EXPECT_TRUE(coil.isRatedEvaporatorInletAirDryBulbTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(19.7, coil.ratedEvaporatorInletAirDryBulbTemperature());
  EXPECT_TRUE(coil.setRatedEvaporatorInletAirDryBulbTemperature(21.1));
  EXPECT_DOUBLE_EQ(21.1, coil.ratedEvaporatorInletAirDryBulbTemperature());
  coil.resetRatedEvaporatorInletAirDryBulbTemperature();
  EXPECT_TRUE(coil.isRatedEvaporatorInletAirDryBulbTemperatureDefaulted());

  EXPECT_TRUE(coil.isRatedEvaporatorInletAirWetBulbTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(13.5, coil.ratedEvaporatorInletAirWetBulbTemperature());
  EXPECT_TRUE(coil.setRatedEvaporatorInletAirWetBulbTemperature(14.2));
  EXPECT_DOUBLE_EQ(14.2, coil.ratedEvaporatorInletAirWetBulbTemperature());
  coil.resetRatedEvaporatorInletAirWetBulbTemperature();
  EXPECT_TRUE(coil.isRatedEvaporatorInletAirWetBulbTemperatureDefaulted());

  EXPECT_TRUE(coil.isRatedCondenserWaterTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(57.5, coil.ratedCondenserWaterTemperature());
  EXPECT_TRUE(coil.setRatedCondenserWaterTemperature(52.0));
  EXPECT_DOUBLE_EQ(52.0, coil.ratedCondenserWaterTemperature());
  coil.resetRatedCondenserWaterTemperature();
  EXPECT_TRUE(coil.isRatedCondenserWaterTemperatureDefaulted());

  EXPECT_FALSE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_FALSE(coil.isRatedEvaporatorAirFlowRateAutocalculated());
  EXPECT_TRUE(coil.setRatedEvaporatorAirFlowRate(1.0));
  ASSERT_TRUE(coil.ratedEvaporatorAirFlowRate());
  EXPECT_DOUBLE_EQ(1.0, coil.ratedEvaporatorAirFlowRate().get());
  coil.autocalculateRatedEvaporatorAirFlowRate();
  EXPECT_TRUE(coil.isRatedEvaporatorAirFlowRateAutocalculated());
  coil.resetRatedEvaporatorAirFlowRate();
  EXPECT_FALSE(coil.ratedEvaporatorAirFlowRate());

  EXPECT_TRUE(coil.isEvaporatorFanPowerIncludedinRatedCOPDefaulted());
  EXPECT_TRUE(coil.evaporatorFanPowerIncludedinRatedCOP());
  EXPECT_TRUE(coil.setEvaporatorFanPowerIncludedinRatedCOP(false));
  EXPECT_FALSE(coil.evaporatorFanPowerIncludedinRatedCOP());
  coil.resetEvaporatorFanPowerIncludedinRatedCOP();
  EXPECT_TRUE(coil.isEvaporatorFanPowerIncludedinRatedCOPDefaulted());

  EXPECT_TRUE(coil.isCrankcaseHeaterCapacityDefaulted());
  EXPECT_DOUBLE_EQ(0.0, coil.crankcaseHeaterCapacity());
  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(105.0));
  EXPECT_DOUBLE_EQ(105.0, coil.crankcaseHeaterCapacity());
  coil.resetCrankcaseHeaterCapacity();
  EXPECT_TRUE(coil.isCrankcaseHeaterCapacityDefaulted());

  EXPECT_TRUE(coil.isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted());
  EXPECT_DOUBLE_EQ(10.0, coil.maximumAmbientTemperatureforCrankcaseHeaterOperation());
  EXPECT_TRUE(coil.setMaximumAmbientTemperatureforCrankcaseHeaterOperation(9.0));
  EXPECT_DOUBLE_EQ(9.0, coil.maximumAmbientTemperatureforCrankcaseHeaterOperation());
  coil.resetMaximumAmbientTemperatureforCrankcaseHeaterOperation();
  EXPECT_TRUE(coil.isMaximumAmbientTemperatureforCrankcaseHeaterOperationDefaulted());

  const auto temperatureTypeChoices = CoilWaterHeatingAirToWaterHeatPumpWrapped::evaporatorAirTemperatureTypeforCurveObjectsValues();
  EXPECT_FALSE(temperatureTypeChoices.empty());
  EXPECT_TRUE(std::find(temperatureTypeChoices.begin(), temperatureTypeChoices.end(), "WetBulbTemperature") != temperatureTypeChoices.end());

  EXPECT_TRUE(coil.isEvaporatorAirTemperatureTypeforCurveObjectsDefaulted());
  EXPECT_EQ("WetBulbTemperature", coil.evaporatorAirTemperatureTypeforCurveObjects());
  EXPECT_TRUE(coil.setEvaporatorAirTemperatureTypeforCurveObjects("DryBulbTemperature"));
  EXPECT_EQ("DryBulbTemperature", coil.evaporatorAirTemperatureTypeforCurveObjects());
  coil.resetEvaporatorAirTemperatureTypeforCurveObjects();
  EXPECT_TRUE(coil.isEvaporatorAirTemperatureTypeforCurveObjectsDefaulted());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpWrapped_RelationshipValidationAndRawPreservation) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpWrapped coil(model);

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(coil.setAvailabilitySchedule(availability));
  ASSERT_TRUE(availability.scheduleTypeLimits());
  EXPECT_EQ("Availability", availability.scheduleTypeLimits()->unitType());
  ASSERT_TRUE(availability.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Discrete", *availability.scheduleTypeLimits()->numericType());

  ScheduleConstant incompatibleSchedule(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(temperatureLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(temperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatibleSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(coil.setAvailabilitySchedule(incompatibleSchedule));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());

  CurveBiquadratic temperatureCurve(model);
  CurveCubic univariateCurve(model);
  CurveTriquadratic ineligibleCurve(model);
  ASSERT_TRUE(coil.setHeatingCapacityFunctionofTemperatureCurve(temperatureCurve));
  ASSERT_TRUE(coil.setHeatingCapacityFunctionofAirFlowFractionCurve(univariateCurve));
  ASSERT_TRUE(coil.setHeatingCOPFunctionofTemperatureCurve(temperatureCurve));
  ASSERT_TRUE(coil.setHeatingCOPFunctionofAirFlowFractionCurve(univariateCurve));
  ASSERT_TRUE(coil.setPartLoadFractionCorrelationCurve(univariateCurve));
  ASSERT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(univariateCurve));

  EXPECT_FALSE(coil.setHeatingCapacityFunctionofTemperatureCurve(ineligibleCurve));
  EXPECT_FALSE(coil.setHeatingCapacityFunctionofAirFlowFractionCurve(temperatureCurve));
  EXPECT_FALSE(coil.setHeatingCOPFunctionofTemperatureCurve(ineligibleCurve));
  EXPECT_FALSE(coil.setHeatingCOPFunctionofAirFlowFractionCurve(temperatureCurve));
  EXPECT_FALSE(coil.setPartLoadFractionCorrelationCurve(temperatureCurve));
  EXPECT_FALSE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(temperatureCurve));
  EXPECT_EQ(temperatureCurve.handle(), coil.heatingCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(univariateCurve.handle(), coil.heatingCapacityFunctionofAirFlowFractionCurve().handle());
  EXPECT_EQ(temperatureCurve.handle(), coil.heatingCOPFunctionofTemperatureCurve().handle());
  EXPECT_EQ(univariateCurve.handle(), coil.heatingCOPFunctionofAirFlowFractionCurve().handle());
  EXPECT_EQ(univariateCurve.handle(), coil.partLoadFractionCorrelationCurve().handle());
  ASSERT_TRUE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(univariateCurve.handle(), coil.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  CurveBiquadratic foreignTemperatureCurve(foreignModel);
  CurveCubic foreignUnivariateCurve(foreignModel);
  EXPECT_FALSE(coil.setAvailabilitySchedule(foreignSchedule));
  EXPECT_FALSE(coil.setHeatingCapacityFunctionofTemperatureCurve(foreignTemperatureCurve));
  EXPECT_FALSE(coil.setHeatingCapacityFunctionofAirFlowFractionCurve(foreignUnivariateCurve));
  EXPECT_FALSE(coil.setHeatingCOPFunctionofTemperatureCurve(foreignTemperatureCurve));
  EXPECT_FALSE(coil.setHeatingCOPFunctionofAirFlowFractionCurve(foreignUnivariateCurve));
  EXPECT_FALSE(coil.setPartLoadFractionCorrelationCurve(foreignUnivariateCurve));
  EXPECT_FALSE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(foreignUnivariateCurve));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  EXPECT_EQ(temperatureCurve.handle(), coil.heatingCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(univariateCurve.handle(), coil.partLoadFractionCorrelationCurve().handle());

  auto workspaceImpl = coil.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  constexpr auto availabilityField = openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::AvailabilityScheduleName;
  constexpr auto crankcaseField =
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName;
  ASSERT_TRUE(workspaceImpl->setPointer(availabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(availabilityField, "Unresolved Wrapped Availability", false));
  ASSERT_TRUE(workspaceImpl->setPointer(crankcaseField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(crankcaseField, "Unresolved Wrapped Crankcase Curve", false));

  EXPECT_FALSE(coil.setAvailabilitySchedule(incompatibleSchedule));
  EXPECT_FALSE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(temperatureCurve));
  EXPECT_EQ("Unresolved Wrapped Availability",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Unresolved Wrapped Crankcase Curve",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(crankcaseField, false, true).value_or(""));

  coil.resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(crankcaseField, false, true).value_or("").empty());
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpWrapped_CanonicalizeBlankOnlyAndPreserveUnresolved) {
  Model model;
  CoilWaterHeatingAirToWaterHeatPumpWrapped blank(model);
  CoilWaterHeatingAirToWaterHeatPumpWrapped unresolved(model);
  ASSERT_TRUE(blank.setName("Blank Wrapped Coil"));
  ASSERT_TRUE(unresolved.setName("Unresolved Wrapped Coil"));

  auto blankImpl = blank.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankImpl);
  ASSERT_TRUE(unresolvedImpl);

  constexpr auto availabilityField = openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::AvailabilityScheduleName;
  constexpr std::array<unsigned, 5> requiredCurveFields{
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCapacityFunctionofTemperatureCurveName,
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCapacityFunctionofAirFlowFractionCurveName,
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCOPFunctionofTemperatureCurveName,
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCOPFunctionofAirFlowFractionCurveName,
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::PartLoadFractionCorrelationCurveName,
  };

  ASSERT_TRUE(blankImpl->setPointer(availabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(availabilityField, "", false));
  for (const auto field : requiredCurveFields) {
    ASSERT_TRUE(blankImpl->setPointer(field, openstudio::Handle(), false));
    ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  }

  constexpr auto unresolvedCurveField =
    openstudio::Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCapacityFunctionofAirFlowFractionCurveName;
  ASSERT_TRUE(unresolvedImpl->setPointer(availabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(unresolvedImpl->openstudio::detail::IdfObject_Impl::setString(availabilityField, "Missing Wrapped Availability", false));
  ASSERT_TRUE(unresolvedImpl->setPointer(unresolvedCurveField, openstudio::Handle(), false));
  ASSERT_TRUE(unresolvedImpl->openstudio::detail::IdfObject_Impl::setString(unresolvedCurveField, "Missing Wrapped Capacity Curve", false));

  const auto curveCountBefore = model.getObjectsByType(openstudio::IddObjectType::Curve_Biquadratic).size()
                                + model.getObjectsByType(openstudio::IddObjectType::Curve_Cubic).size();
  const auto report = model.canonicalize();
  EXPECT_GE(report.warningCount, 2u);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), blank.availabilitySchedule().handle());
  EXPECT_TRUE(blank.heatingCapacityFunctionofTemperatureCurve().optionalCast<CurveBiquadratic>());
  EXPECT_TRUE(blank.heatingCapacityFunctionofAirFlowFractionCurve().optionalCast<CurveCubic>());
  EXPECT_TRUE(blank.heatingCOPFunctionofTemperatureCurve().optionalCast<CurveBiquadratic>());
  EXPECT_TRUE(blank.heatingCOPFunctionofAirFlowFractionCurve().optionalCast<CurveCubic>());
  EXPECT_TRUE(blank.partLoadFractionCorrelationCurve().optionalCast<CurveCubic>());
  EXPECT_EQ(curveCountBefore + 5u, model.getObjectsByType(openstudio::IddObjectType::Curve_Biquadratic).size()
                                     + model.getObjectsByType(openstudio::IddObjectType::Curve_Cubic).size());

  EXPECT_FALSE(unresolved.getModelObjectTarget<Schedule>(availabilityField));
  EXPECT_FALSE(unresolved.getModelObjectTarget<Curve>(unresolvedCurveField));
  EXPECT_EQ("Missing Wrapped Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Missing Wrapped Capacity Curve",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(unresolvedCurveField, false, true).value_or(""));

  const auto curveCountAfter = model.getObjectsByType(openstudio::IddObjectType::Curve_Biquadratic).size()
                               + model.getObjectsByType(openstudio::IddObjectType::Curve_Cubic).size();
  model.canonicalize();
  EXPECT_EQ(curveCountAfter, model.getObjectsByType(openstudio::IddObjectType::Curve_Biquadratic).size()
                               + model.getObjectsByType(openstudio::IddObjectType::Curve_Cubic).size());
  EXPECT_EQ("Missing Wrapped Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Missing Wrapped Capacity Curve",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(unresolvedCurveField, false, true).value_or(""));
}

TEST_F(EPModelFixture, CoilWaterHeatingAirToWaterHeatPumpWrapped_ReloadMutationAndResourceLifetime) {
  const auto firstPath = uniqueWrappedCoilPath("epmodel-wrapped-water-heating-coil-first");
  const auto secondPath = uniqueWrappedCoilPath("epmodel-wrapped-water-heating-coil-second");
  const ScopedWrappedCoilFileRemoval removeFirst(firstPath);
  const ScopedWrappedCoilFileRemoval removeSecond(secondPath);

  Model model;
  CoilWaterHeatingAirToWaterHeatPumpWrapped coil(model);
  ScheduleConstant originalSchedule(model);
  CurveBiquadratic originalCapacityTemperature(model);
  CurveCubic originalCapacityAirFlow(model);
  CurveBiquadratic originalCOPTemperature(model);
  CurveCubic originalCOPAirFlow(model);
  CurveCubic originalPartLoad(model);
  CurveCubic originalCrankcase(model);
  ASSERT_TRUE(coil.setName("Reloadable Wrapped Water Heating Coil"));
  ASSERT_TRUE(originalSchedule.setName("Original Wrapped Availability"));
  ASSERT_TRUE(originalSchedule.setValue(1.0));
  ASSERT_TRUE(originalCapacityTemperature.setName("Original Wrapped Capacity Temperature"));
  ASSERT_TRUE(originalCapacityAirFlow.setName("Original Wrapped Capacity Air Flow"));
  ASSERT_TRUE(originalCOPTemperature.setName("Original Wrapped COP Temperature"));
  ASSERT_TRUE(originalCOPAirFlow.setName("Original Wrapped COP Air Flow"));
  ASSERT_TRUE(originalPartLoad.setName("Original Wrapped Part Load"));
  ASSERT_TRUE(originalCrankcase.setName("Original Wrapped Crankcase"));
  ASSERT_TRUE(coil.setAvailabilitySchedule(originalSchedule));
  ASSERT_TRUE(coil.setHeatingCapacityFunctionofTemperatureCurve(originalCapacityTemperature));
  ASSERT_TRUE(coil.setHeatingCapacityFunctionofAirFlowFractionCurve(originalCapacityAirFlow));
  ASSERT_TRUE(coil.setHeatingCOPFunctionofTemperatureCurve(originalCOPTemperature));
  ASSERT_TRUE(coil.setHeatingCOPFunctionofAirFlowFractionCurve(originalCOPAirFlow));
  ASSERT_TRUE(coil.setPartLoadFractionCorrelationCurve(originalPartLoad));
  ASSERT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(originalCrankcase));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilWaterHeatingAirToWaterHeatPumpWrapped>("Reloadable Wrapped Water Heating Coil");
  auto loadedSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Wrapped Availability");
  auto loadedCapacityTemperature = loadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Original Wrapped Capacity Temperature");
  auto loadedCapacityAirFlow = loadedModel->getConcreteModelObjectByName<CurveCubic>("Original Wrapped Capacity Air Flow");
  auto loadedCOPTemperature = loadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Original Wrapped COP Temperature");
  auto loadedCOPAirFlow = loadedModel->getConcreteModelObjectByName<CurveCubic>("Original Wrapped COP Air Flow");
  auto loadedPartLoad = loadedModel->getConcreteModelObjectByName<CurveCubic>("Original Wrapped Part Load");
  auto loadedCrankcase = loadedModel->getConcreteModelObjectByName<CurveCubic>("Original Wrapped Crankcase");
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedSchedule);
  ASSERT_TRUE(loadedCapacityTemperature);
  ASSERT_TRUE(loadedCapacityAirFlow);
  ASSERT_TRUE(loadedCOPTemperature);
  ASSERT_TRUE(loadedCOPAirFlow);
  ASSERT_TRUE(loadedPartLoad);
  ASSERT_TRUE(loadedCrankcase);
  EXPECT_EQ(loadedSchedule->handle(), loadedCoil->availabilitySchedule().handle());
  EXPECT_EQ(loadedCapacityTemperature->handle(), loadedCoil->heatingCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(loadedCapacityAirFlow->handle(), loadedCoil->heatingCapacityFunctionofAirFlowFractionCurve().handle());
  EXPECT_EQ(loadedCOPTemperature->handle(), loadedCoil->heatingCOPFunctionofTemperatureCurve().handle());
  EXPECT_EQ(loadedCOPAirFlow->handle(), loadedCoil->heatingCOPFunctionofAirFlowFractionCurve().handle());
  EXPECT_EQ(loadedPartLoad->handle(), loadedCoil->partLoadFractionCorrelationCurve().handle());
  ASSERT_TRUE(loadedCoil->crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(loadedCrankcase->handle(), loadedCoil->crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());

  ScheduleConstant replacementSchedule(*loadedModel);
  CurveBiquadratic replacementTemperature(*loadedModel);
  CurveCubic replacementUnivariate(*loadedModel);
  CurveCubic replacementCrankcase(*loadedModel);
  ASSERT_TRUE(replacementSchedule.setName("Replacement Wrapped Availability"));
  ASSERT_TRUE(replacementSchedule.setValue(1.0));
  ASSERT_TRUE(replacementTemperature.setName("Replacement Wrapped Temperature Curves"));
  ASSERT_TRUE(replacementUnivariate.setName("Replacement Wrapped Univariate Curves"));
  ASSERT_TRUE(replacementCrankcase.setName("Replacement Wrapped Crankcase"));
  ASSERT_TRUE(loadedCoil->setAvailabilitySchedule(replacementSchedule));
  ASSERT_TRUE(loadedCoil->setHeatingCapacityFunctionofTemperatureCurve(replacementTemperature));
  ASSERT_TRUE(loadedCoil->setHeatingCapacityFunctionofAirFlowFractionCurve(replacementUnivariate));
  ASSERT_TRUE(loadedCoil->setHeatingCOPFunctionofTemperatureCurve(replacementTemperature));
  ASSERT_TRUE(loadedCoil->setHeatingCOPFunctionofAirFlowFractionCurve(replacementUnivariate));
  ASSERT_TRUE(loadedCoil->setPartLoadFractionCorrelationCurve(replacementUnivariate));
  ASSERT_TRUE(loadedCoil->setCrankcaseHeaterCapacityFunctionofTemperatureCurve(replacementCrankcase));
  loadedCoil->resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCoil = reloadedModel->getConcreteModelObjectByName<CoilWaterHeatingAirToWaterHeatPumpWrapped>("Reloadable Wrapped Water Heating Coil");
  auto reloadedSchedule = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Wrapped Availability");
  auto reloadedTemperature = reloadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Replacement Wrapped Temperature Curves");
  auto reloadedUnivariate = reloadedModel->getConcreteModelObjectByName<CurveCubic>("Replacement Wrapped Univariate Curves");
  auto reloadedCrankcase = reloadedModel->getConcreteModelObjectByName<CurveCubic>("Replacement Wrapped Crankcase");
  ASSERT_TRUE(reloadedCoil);
  ASSERT_TRUE(reloadedSchedule);
  ASSERT_TRUE(reloadedTemperature);
  ASSERT_TRUE(reloadedUnivariate);
  ASSERT_TRUE(reloadedCrankcase);
  EXPECT_EQ(reloadedSchedule->handle(), reloadedCoil->availabilitySchedule().handle());
  EXPECT_EQ(reloadedTemperature->handle(), reloadedCoil->heatingCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(reloadedUnivariate->handle(), reloadedCoil->heatingCapacityFunctionofAirFlowFractionCurve().handle());
  EXPECT_EQ(reloadedTemperature->handle(), reloadedCoil->heatingCOPFunctionofTemperatureCurve().handle());
  EXPECT_EQ(reloadedUnivariate->handle(), reloadedCoil->heatingCOPFunctionofAirFlowFractionCurve().handle());
  EXPECT_EQ(reloadedUnivariate->handle(), reloadedCoil->partLoadFractionCorrelationCurve().handle());
  EXPECT_FALSE(reloadedCoil->crankcaseHeaterCapacityFunctionofTemperatureCurve());

  const std::array<openstudio::Handle, 4> externalHandles{reloadedSchedule->handle(), reloadedTemperature->handle(), reloadedUnivariate->handle(),
                                                          reloadedCrankcase->handle()};
  EXPECT_FALSE(reloadedCoil->remove().empty());
  for (const auto& handle : externalHandles) {
    EXPECT_TRUE(reloadedModel->getObject(handle));
  }

  WaterHeaterHeatPumpWrappedCondenser parent(*reloadedModel);
  auto containedCoil = parent.dXCoil().cast<CoilWaterHeatingAirToWaterHeatPumpWrapped>();
  const auto parentChildren = parent.children();
  ASSERT_EQ(3u, parentChildren.size());
  EXPECT_NE(parentChildren.end(), std::find(parentChildren.begin(), parentChildren.end(), containedCoil.cast<ModelObject>()));
  ASSERT_TRUE(containedCoil.setAvailabilitySchedule(*reloadedSchedule));
  ASSERT_TRUE(containedCoil.setHeatingCapacityFunctionofTemperatureCurve(*reloadedTemperature));
  ASSERT_TRUE(containedCoil.setHeatingCapacityFunctionofAirFlowFractionCurve(*reloadedUnivariate));
  ASSERT_TRUE(containedCoil.setHeatingCOPFunctionofTemperatureCurve(*reloadedTemperature));
  ASSERT_TRUE(containedCoil.setHeatingCOPFunctionofAirFlowFractionCurve(*reloadedUnivariate));
  ASSERT_TRUE(containedCoil.setPartLoadFractionCorrelationCurve(*reloadedUnivariate));
  EXPECT_TRUE(containedCoil.remove().empty());
  EXPECT_FALSE(parent.remove().empty());
  for (const auto& handle : externalHandles) {
    EXPECT_TRUE(reloadedModel->getObject(handle));
  }
}
