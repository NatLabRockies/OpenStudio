/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDXVariableRefrigerantFlow.hpp"
#include "StraightComponent/CoilCoolingDXVariableRefrigerantFlow_Impl.hpp"

#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveBiquadratic_Impl.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Curve/CurveQuadratic_Impl.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

namespace {

void applyConstructorDefaults(CoilCoolingDXVariableRefrigerantFlow& coil) {
  const auto& model = coil.model();

  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(coil.setAvailabilitySchedule(alwaysOn));

  coil.autosizeRatedTotalCoolingCapacity();
  coil.autosizeRatedSensibleHeatRatio();
  coil.autosizeRatedAirFlowRate();

  CurveBiquadratic vrfTUCoolCapFT(model);
  vrfTUCoolCapFT.setName("VRFTUCoolCapFT");
  OS_ASSERT(vrfTUCoolCapFT.setCoefficient1Constant(5.85884077803259E-02));
  OS_ASSERT(vrfTUCoolCapFT.setCoefficient2x(5.87396532718384E-02));
  OS_ASSERT(vrfTUCoolCapFT.setCoefficient3xPOW2(-2.10274979759697E-04));
  OS_ASSERT(vrfTUCoolCapFT.setCoefficient4y(1.09370473889647E-02));
  OS_ASSERT(vrfTUCoolCapFT.setCoefficient5yPOW2(-0.0001219549));
  OS_ASSERT(vrfTUCoolCapFT.setCoefficient6xTIMESY(-0.0005246615));
  OS_ASSERT(vrfTUCoolCapFT.setMinimumValueofx(15.0));
  OS_ASSERT(vrfTUCoolCapFT.setMaximumValueofx(23.89));
  OS_ASSERT(vrfTUCoolCapFT.setMinimumValueofy(20.0));
  OS_ASSERT(vrfTUCoolCapFT.setMaximumValueofy(43.33));
  OS_ASSERT(vrfTUCoolCapFT.setMinimumCurveOutput(0.8083));
  OS_ASSERT(vrfTUCoolCapFT.setMaximumCurveOutput(1.2583));
  OS_ASSERT(coil.setCoolingCapacityRatioModifierFunctionofTemperatureCurve(vrfTUCoolCapFT));

  CurveQuadratic vrfACCoolCapFFF(model);
  vrfACCoolCapFFF.setName("VRFACCoolCapFFF");
  OS_ASSERT(vrfACCoolCapFFF.setCoefficient1Constant(0.8));
  OS_ASSERT(vrfACCoolCapFFF.setCoefficient2x(0.2));
  OS_ASSERT(vrfACCoolCapFFF.setCoefficient3xPOW2(0.0));
  OS_ASSERT(vrfACCoolCapFFF.setMinimumValueofx(0.5));
  OS_ASSERT(vrfACCoolCapFFF.setMaximumValueofx(1.5));
  OS_ASSERT(coil.setCoolingCapacityModifierCurveFunctionofFlowFraction(vrfACCoolCapFFF));
}

}  // namespace

CoilCoolingDXVariableRefrigerantFlow::CoilCoolingDXVariableRefrigerantFlow(const Model& model)
  : StraightComponent(CoilCoolingDXVariableRefrigerantFlow::iddObjectType(), model) {
  auto impl = getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
  applyConstructorDefaults(*this);
}

CoilCoolingDXVariableRefrigerantFlow::CoilCoolingDXVariableRefrigerantFlow(
  std::shared_ptr<detail::CoilCoolingDXVariableRefrigerantFlow_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType CoilCoolingDXVariableRefrigerantFlow::iddObjectType() {
  return IddObjectType::Coil_Cooling_DX_VariableRefrigerantFlow;
}

Schedule CoilCoolingDXVariableRefrigerantFlow::availabilitySchedule() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->availabilitySchedule();
}

bool CoilCoolingDXVariableRefrigerantFlow::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setAvailabilitySchedule(schedule);
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow::ratedTotalCoolingCapacity() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->ratedTotalCoolingCapacity();
}

bool CoilCoolingDXVariableRefrigerantFlow::isRatedTotalCoolingCapacityAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->isRatedTotalCoolingCapacityAutosized();
}

bool CoilCoolingDXVariableRefrigerantFlow::setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setRatedTotalCoolingCapacity(ratedTotalCoolingCapacity);
}

void CoilCoolingDXVariableRefrigerantFlow::autosizeRatedTotalCoolingCapacity() {
  getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->autosizeRatedTotalCoolingCapacity();
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow::ratedSensibleHeatRatio() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->ratedSensibleHeatRatio();
}

bool CoilCoolingDXVariableRefrigerantFlow::isRatedSensibleHeatRatioAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->isRatedSensibleHeatRatioAutosized();
}

bool CoilCoolingDXVariableRefrigerantFlow::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setRatedSensibleHeatRatio(ratedSensibleHeatRatio);
}

void CoilCoolingDXVariableRefrigerantFlow::autosizeRatedSensibleHeatRatio() {
  getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->autosizeRatedSensibleHeatRatio();
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow::ratedAirFlowRate() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->ratedAirFlowRate();
}

bool CoilCoolingDXVariableRefrigerantFlow::isRatedAirFlowRateAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->isRatedAirFlowRateAutosized();
}

bool CoilCoolingDXVariableRefrigerantFlow::setRatedAirFlowRate(double ratedAirFlowRate) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
}

void CoilCoolingDXVariableRefrigerantFlow::autosizeRatedAirFlowRate() {
  getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->autosizeRatedAirFlowRate();
}

Curve CoilCoolingDXVariableRefrigerantFlow::coolingCapacityRatioModifierFunctionofTemperatureCurve() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->coolingCapacityRatioModifierFunctionofTemperatureCurve();
}

bool CoilCoolingDXVariableRefrigerantFlow::setCoolingCapacityRatioModifierFunctionofTemperatureCurve(const Curve& curve) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setCoolingCapacityRatioModifierFunctionofTemperatureCurve(curve);
}

Curve CoilCoolingDXVariableRefrigerantFlow::coolingCapacityModifierCurveFunctionofFlowFraction() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->coolingCapacityModifierCurveFunctionofFlowFraction();
}

bool CoilCoolingDXVariableRefrigerantFlow::setCoolingCapacityModifierCurveFunctionofFlowFraction(const Curve& curve) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setCoolingCapacityModifierCurveFunctionofFlowFraction(curve);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

Schedule CoilCoolingDXVariableRefrigerantFlow_Impl::availabilitySchedule() const {
  auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::AvailabilityScheduleName);
  OS_ASSERT(value);
  return *value;
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::setAvailabilitySchedule(Schedule& schedule) {
  return setPointer(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::AvailabilityScheduleName, schedule.handle(), false);
}

unsigned CoilCoolingDXVariableRefrigerantFlow_Impl::inletPort() const {
  return openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirInletNode;
}

unsigned CoilCoolingDXVariableRefrigerantFlow_Impl::outletPort() const {
  return openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirOutletNode;
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::addToNode(Node& /*node*/) {
  // This coil has a simple one-inlet/one-outlet air shape, so epmodel exposes
  // it as a StraightComponent. It is still intended to live inside VRF-owned
  // terminal topology, not to participate as standalone loop equipment.
  return false;
}

Curve CoilCoolingDXVariableRefrigerantFlow_Impl::coolingCapacityRatioModifierFunctionofTemperatureCurve() const {
  auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofTemperatureCurveName);
  OS_ASSERT(curve);
  return *curve;
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::setCoolingCapacityRatioModifierFunctionofTemperatureCurve(const Curve& curve) {
  return setPointer(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofTemperatureCurveName,
                    curve.handle(), false);
}

Curve CoilCoolingDXVariableRefrigerantFlow_Impl::coolingCapacityModifierCurveFunctionofFlowFraction() const {
  auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
    openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoolingCapacityModifierCurveFunctionofFlowFractionName);
  OS_ASSERT(curve);
  return *curve;
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::setCoolingCapacityModifierCurveFunctionofFlowFraction(const Curve& curve) {
  return setPointer(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoolingCapacityModifierCurveFunctionofFlowFractionName,
                    curve.handle(), false);
}

std::vector<ModelObject> CoilCoolingDXVariableRefrigerantFlow_Impl::children() const {
  std::vector<ModelObject> result;
  result.push_back(coolingCapacityRatioModifierFunctionofTemperatureCurve());
  result.push_back(coolingCapacityModifierCurveFunctionofFlowFraction());
  return result;
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow_Impl::ratedTotalCoolingCapacity() const {
  return getDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, true);
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::isRatedTotalCoolingCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, ratedTotalCoolingCapacity);
}

void CoilCoolingDXVariableRefrigerantFlow_Impl::autosizeRatedTotalCoolingCapacity() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, "autosize"));
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow_Impl::ratedSensibleHeatRatio() const {
  return getDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedSensibleHeatRatio, true);
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::isRatedSensibleHeatRatioAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedSensibleHeatRatio, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedSensibleHeatRatio, ratedSensibleHeatRatio);
}

void CoilCoolingDXVariableRefrigerantFlow_Impl::autosizeRatedSensibleHeatRatio() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::GrossRatedSensibleHeatRatio, "autosize"));
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow_Impl::ratedAirFlowRate() const {
  return getDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, true);
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::isRatedAirFlowRateAutosized() const {
  if (const auto value = getString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilCoolingDXVariableRefrigerantFlow_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
  return setDouble(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, ratedAirFlowRate);
}

void CoilCoolingDXVariableRefrigerantFlow_Impl::autosizeRatedAirFlowRate() {
  OS_ASSERT(setString(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, "autosize"));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
