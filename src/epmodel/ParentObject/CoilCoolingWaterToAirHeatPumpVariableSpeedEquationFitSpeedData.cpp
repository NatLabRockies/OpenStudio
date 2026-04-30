/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.hpp"
#include "ParentObject/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Model.hpp"
#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.hpp"
#include "WaterToAirComponent/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit_SpeedData_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

namespace {

std::shared_ptr<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>
makeDetachedSpeedDataImpl(const Model& model) {
  const auto generatedName = "__transient__cooling_wtahp_vs_speed_data_" + openstudio::toString(openstudio::createUUID());
  auto transient =
    model.getOrCreateTransientByName<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData>(generatedName);
  auto impl = transient.getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>();
  OS_ASSERT(impl);
  return impl;
}

}  // namespace

CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(const Model& model)
  : ParentObject(makeDetachedSpeedDataImpl(model)) {
  CurveBiquadratic coolingCurve1(model);
  coolingCurve1.setCoefficient1Constant(1.43085);
  coolingCurve1.setCoefficient2x(-0.0453653);
  coolingCurve1.setCoefficient3xPOW2(0.00199378);
  coolingCurve1.setCoefficient4y(-0.00805944);
  coolingCurve1.setCoefficient5yPOW2(3.93414E-05);
  coolingCurve1.setCoefficient6xTIMESY(-1.81187E-04);
  coolingCurve1.setMinimumValueofx(10.0);
  coolingCurve1.setMaximumValueofx(25.6);
  coolingCurve1.setMinimumValueofy(7.2);
  coolingCurve1.setMaximumValueofy(48.9);

  CurveQuadratic coolingCurve2(model);
  coolingCurve2.setCoefficient1Constant(1.0);
  coolingCurve2.setCoefficient2x(0.0);
  coolingCurve2.setCoefficient3xPOW2(0.0);
  coolingCurve2.setMinimumValueofx(0.0);
  coolingCurve2.setMaximumValueofx(1.0);

  CurveQuadratic coolingCurve3(model);
  coolingCurve3.setCoefficient1Constant(1.0);
  coolingCurve3.setCoefficient2x(0.0);
  coolingCurve3.setCoefficient3xPOW2(0.0);
  coolingCurve3.setMinimumValueofx(0.0);
  coolingCurve3.setMaximumValueofx(1.0);

  CurveBiquadratic coolingCurve4(model);
  coolingCurve4.setCoefficient1Constant(0.138848);
  coolingCurve4.setCoefficient2x(0.0457985);
  coolingCurve4.setCoefficient3xPOW2(-0.00138661);
  coolingCurve4.setCoefficient4y(0.0141485);
  coolingCurve4.setCoefficient5yPOW2(0.000386055);
  coolingCurve4.setCoefficient6xTIMESY(-4.38194E-04);
  coolingCurve4.setMinimumValueofx(10.0);
  coolingCurve4.setMaximumValueofx(25.6);
  coolingCurve4.setMinimumValueofy(7.2);
  coolingCurve4.setMaximumValueofy(48.9);

  CurveQuadratic coolingCurve5(model);
  coolingCurve5.setCoefficient1Constant(1.0);
  coolingCurve5.setCoefficient2x(0.0);
  coolingCurve5.setCoefficient3xPOW2(0.0);
  coolingCurve5.setMinimumValueofx(0.0);
  coolingCurve5.setMaximumValueofx(1.0);

  CurveQuadratic coolingCurve6(model);
  coolingCurve6.setCoefficient1Constant(1.0);
  coolingCurve6.setCoefficient2x(0.0);
  coolingCurve6.setCoefficient3xPOW2(0.0);
  coolingCurve6.setMinimumValueofx(0.0);
  coolingCurve6.setMaximumValueofx(1.0);

  CurveBiquadratic coolingCurve7(model);
  coolingCurve7.setCoefficient1Constant(1.0);
  coolingCurve7.setCoefficient2x(0.0);
  coolingCurve7.setCoefficient3xPOW2(0.0);
  coolingCurve7.setCoefficient4y(0.0);
  coolingCurve7.setCoefficient5yPOW2(0.0);
  coolingCurve7.setCoefficient6xTIMESY(0.0);
  coolingCurve7.setMinimumValueofx(10.0);
  coolingCurve7.setMaximumValueofx(25.6);
  coolingCurve7.setMinimumValueofy(7.2);
  coolingCurve7.setMaximumValueofy(48.9);

  bool ok = true;
  ok = setReferenceUnitGrossRatedTotalCoolingCapacity(1524.1) && ok;
  ok = setReferenceUnitGrossRatedSensibleHeatRatio(0.75) && ok;
  ok = setReferenceUnitGrossRatedCoolingCOP(4.0) && ok;
  ok = setReferenceUnitRatedAirFlowRate(0.1359072) && ok;
  ok = setReferenceUnitRatedWaterFlowRate(0.000381695) && ok;
  ok = setReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions(0.1) && ok;
  ok = setTotalCoolingCapacityFunctionofTemperatureCurve(coolingCurve1) && ok;
  ok = setTotalCoolingCapacityFunctionofAirFlowFractionCurve(coolingCurve2) && ok;
  ok = setTotalCoolingCapacityFunctionofWaterFlowFractionCurve(coolingCurve3) && ok;
  ok = setEnergyInputRatioFunctionofTemperatureCurve(coolingCurve4) && ok;
  ok = setEnergyInputRatioFunctionofAirFlowFractionCurve(coolingCurve5) && ok;
  ok = setEnergyInputRatioFunctionofWaterFlowFractionCurve(coolingCurve6) && ok;
  ok = setWasteHeatFunctionofTemperatureCurve(coolingCurve7) && ok;
  OS_ASSERT(ok);
}

CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(
  const Model& model, const Curve& totalCoolingCapacityFunctionofTemperature, const Curve& totalCoolingCapacityFunctionofAirFlowFraction,
  const Curve& totalCoolingCapacityFunctionofWaterFlowFraction, const Curve& energyInputRatioFunctionofTemperature,
  const Curve& energyInputRatioFunctionofAirFlowFraction, const Curve& energyInputRatioFunctionofWaterFlowFraction,
  const Curve& wasteHeatFunctionofTemperature)
  : ParentObject(makeDetachedSpeedDataImpl(model)) {
  bool ok = true;
  ok = setReferenceUnitGrossRatedTotalCoolingCapacity(1524.1) && ok;
  ok = setReferenceUnitGrossRatedSensibleHeatRatio(0.75) && ok;
  ok = setReferenceUnitGrossRatedCoolingCOP(4.0) && ok;
  ok = setReferenceUnitRatedAirFlowRate(0.1359072) && ok;
  ok = setReferenceUnitRatedWaterFlowRate(0.000381695) && ok;
  ok = setReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions(0.1) && ok;
  ok = setTotalCoolingCapacityFunctionofTemperatureCurve(totalCoolingCapacityFunctionofTemperature) && ok;
  ok = setTotalCoolingCapacityFunctionofAirFlowFractionCurve(totalCoolingCapacityFunctionofAirFlowFraction) && ok;
  ok = setTotalCoolingCapacityFunctionofWaterFlowFractionCurve(totalCoolingCapacityFunctionofWaterFlowFraction) && ok;
  ok = setEnergyInputRatioFunctionofTemperatureCurve(energyInputRatioFunctionofTemperature) && ok;
  ok = setEnergyInputRatioFunctionofAirFlowFractionCurve(energyInputRatioFunctionofAirFlowFraction) && ok;
  ok = setEnergyInputRatioFunctionofWaterFlowFractionCurve(energyInputRatioFunctionofWaterFlowFraction) && ok;
  ok = setWasteHeatFunctionofTemperatureCurve(wasteHeatFunctionofTemperature) && ok;
  OS_ASSERT(ok);
}

CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(
  std::shared_ptr<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl> impl)
  : ParentObject(std::move(impl)) {}

IddObjectType CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::iddObjectType() {
  return IddObjectType::OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit_SpeedData;
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::referenceUnitGrossRatedTotalCoolingCapacity() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->referenceUnitGrossRatedTotalCoolingCapacity();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setReferenceUnitGrossRatedTotalCoolingCapacity(
  double referenceUnitGrossRatedTotalCoolingCapacity) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setReferenceUnitGrossRatedTotalCoolingCapacity(referenceUnitGrossRatedTotalCoolingCapacity);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::referenceUnitGrossRatedSensibleHeatRatio() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->referenceUnitGrossRatedSensibleHeatRatio();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setReferenceUnitGrossRatedSensibleHeatRatio(
  double referenceUnitGrossRatedSensibleHeatRatio) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setReferenceUnitGrossRatedSensibleHeatRatio(referenceUnitGrossRatedSensibleHeatRatio);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::referenceUnitGrossRatedCoolingCOP() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->referenceUnitGrossRatedCoolingCOP();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setReferenceUnitGrossRatedCoolingCOP(double referenceUnitGrossRatedCoolingCOP) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setReferenceUnitGrossRatedCoolingCOP(referenceUnitGrossRatedCoolingCOP);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::referenceUnitRatedAirFlowRate() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->referenceUnitRatedAirFlowRate();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setReferenceUnitRatedAirFlowRate(double referenceUnitRatedAirFlowRate) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setReferenceUnitRatedAirFlowRate(referenceUnitRatedAirFlowRate);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::referenceUnitRatedWaterFlowRate() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->referenceUnitRatedWaterFlowRate();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setReferenceUnitRatedWaterFlowRate(double referenceUnitRatedWaterFlowRate) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setReferenceUnitRatedWaterFlowRate(referenceUnitRatedWaterFlowRate);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::totalCoolingCapacityFunctionofTemperatureCurve() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->totalCoolingCapacityFunctionofTemperatureCurve();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setTotalCoolingCapacityFunctionofTemperatureCurve(const Curve& curve) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setTotalCoolingCapacityFunctionofTemperatureCurve(curve);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::totalCoolingCapacityFunctionofAirFlowFractionCurve() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->totalCoolingCapacityFunctionofAirFlowFractionCurve();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setTotalCoolingCapacityFunctionofAirFlowFractionCurve(const Curve& curve) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setTotalCoolingCapacityFunctionofAirFlowFractionCurve(curve);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::totalCoolingCapacityFunctionofWaterFlowFractionCurve() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->totalCoolingCapacityFunctionofWaterFlowFractionCurve();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setTotalCoolingCapacityFunctionofWaterFlowFractionCurve(const Curve& curve) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setTotalCoolingCapacityFunctionofWaterFlowFractionCurve(curve);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::energyInputRatioFunctionofTemperatureCurve() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->energyInputRatioFunctionofTemperatureCurve();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setEnergyInputRatioFunctionofTemperatureCurve(curve);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::energyInputRatioFunctionofAirFlowFractionCurve() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->energyInputRatioFunctionofAirFlowFractionCurve();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setEnergyInputRatioFunctionofAirFlowFractionCurve(const Curve& curve) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setEnergyInputRatioFunctionofAirFlowFractionCurve(curve);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::energyInputRatioFunctionofWaterFlowFractionCurve() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->energyInputRatioFunctionofWaterFlowFractionCurve();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setEnergyInputRatioFunctionofWaterFlowFractionCurve(const Curve& curve) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setEnergyInputRatioFunctionofWaterFlowFractionCurve(curve);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::referenceUnitWasteHeatFractionofInputPowerAtRatedConditions() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->referenceUnitWasteHeatFractionofInputPowerAtRatedConditions();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions(
  double referenceUnitWasteHeatFractionofInputPowerAtRatedConditions) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions(referenceUnitWasteHeatFractionofInputPowerAtRatedConditions);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::wasteHeatFunctionofTemperatureCurve() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->wasteHeatFunctionofTemperatureCurve();
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setWasteHeatFunctionofTemperatureCurve(const Curve& curve) {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->setWasteHeatFunctionofTemperatureCurve(curve);
}

std::vector<ModelObject> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::children() const {
  return getImpl<detail::CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->children();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

using ParentFields = openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields;
using SpeedFields = openstudio::OS_Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit_SpeedDataFields;

boost::optional<WorkspaceExtensibleGroup> attachedGroup(const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl& impl) {
  auto parent = impl.parent();
  auto speedIndex = impl.attachedSpeedIndex();
  if (!parent || !speedIndex) {
    return boost::none;
  }
  const auto groups = parent->extensibleGroups();
  if (*speedIndex >= groups.size()) {
    return boost::none;
  }
  return groups[*speedIndex].optionalCast<WorkspaceExtensibleGroup>();
}

double requiredDetachedDouble(const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl& impl, unsigned field) {
  const auto value = impl.getDouble(field, true);
  OS_ASSERT(value);
  return *value;
}

Curve requiredDetachedCurve(const CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl& impl, unsigned field) {
  auto value = impl.getObject<ModelObject>().getModelObjectTarget<Curve>(field);
  OS_ASSERT(value);
  return *value;
}

template <typename Getter>
Curve requiredAttachedCurve(const WorkspaceExtensibleGroup& group, unsigned field, Getter&& getter) {
  auto value = getter(group, field);
  OS_ASSERT(value);
  auto curve = value->template optionalCast<Curve>();
  OS_ASSERT(curve);
  return *curve;
}

}  // namespace

boost::optional<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::parent() const {
  if (const auto thisName = getObject<ModelObject>().name()) {
    for (const auto& candidate : model().getModelObjects<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit>()) {
      const auto groups = candidate.extensibleGroups();
      for (unsigned i = 0; i < groups.size(); ++i) {
        if (openstudio::istringEqual(*thisName, detail::transientSpeedDataName(candidate, i))) {
          return candidate;
        }
      }
    }
  }
  return boost::none;
}

boost::optional<unsigned> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::attachedSpeedIndex() const {
  if (const auto thisName = getObject<ModelObject>().name()) {
    if (auto currentParent = parent()) {
      const auto groups = currentParent->extensibleGroups();
      for (unsigned i = 0; i < groups.size(); ++i) {
        if (openstudio::istringEqual(*thisName, detail::transientSpeedDataName(*currentParent, i))) {
          return i;
        }
      }
    }
  }
  return boost::none;
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::referenceUnitGrossRatedTotalCoolingCapacity() const {
  if (auto group = attachedGroup(*this)) {
    const auto value = group->getDouble(ParentFields::SpeedReferenceUnitGrossRatedTotalCoolingCapacity);
    OS_ASSERT(value);
    return *value;
  }
  return requiredDetachedDouble(*this, SpeedFields::ReferenceUnitGrossRatedTotalCoolingCapacity);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setReferenceUnitGrossRatedTotalCoolingCapacity(
  double referenceUnitGrossRatedTotalCoolingCapacity) {
  if (auto group = attachedGroup(*this)) {
    return group->setDouble(ParentFields::SpeedReferenceUnitGrossRatedTotalCoolingCapacity, referenceUnitGrossRatedTotalCoolingCapacity)
           && setDouble(SpeedFields::ReferenceUnitGrossRatedTotalCoolingCapacity, referenceUnitGrossRatedTotalCoolingCapacity);
  }
  return setDouble(SpeedFields::ReferenceUnitGrossRatedTotalCoolingCapacity, referenceUnitGrossRatedTotalCoolingCapacity);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::referenceUnitGrossRatedSensibleHeatRatio() const {
  if (auto group = attachedGroup(*this)) {
    const auto value = group->getDouble(ParentFields::SpeedReferenceUnitGrossRatedSensibleHeatRatio);
    OS_ASSERT(value);
    return *value;
  }
  return requiredDetachedDouble(*this, SpeedFields::ReferenceUnitGrossRatedSensibleHeatRatio);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setReferenceUnitGrossRatedSensibleHeatRatio(
  double referenceUnitGrossRatedSensibleHeatRatio) {
  if (auto group = attachedGroup(*this)) {
    return group->setDouble(ParentFields::SpeedReferenceUnitGrossRatedSensibleHeatRatio, referenceUnitGrossRatedSensibleHeatRatio)
           && setDouble(SpeedFields::ReferenceUnitGrossRatedSensibleHeatRatio, referenceUnitGrossRatedSensibleHeatRatio);
  }
  return setDouble(SpeedFields::ReferenceUnitGrossRatedSensibleHeatRatio, referenceUnitGrossRatedSensibleHeatRatio);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::referenceUnitGrossRatedCoolingCOP() const {
  if (auto group = attachedGroup(*this)) {
    const auto value = group->getDouble(ParentFields::SpeedReferenceUnitGrossRatedCoolingCOP);
    OS_ASSERT(value);
    return *value;
  }
  return requiredDetachedDouble(*this, SpeedFields::ReferenceUnitGrossRatedCoolingCOP);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setReferenceUnitGrossRatedCoolingCOP(double referenceUnitGrossRatedCoolingCOP) {
  if (auto group = attachedGroup(*this)) {
    return group->setDouble(ParentFields::SpeedReferenceUnitGrossRatedCoolingCOP, referenceUnitGrossRatedCoolingCOP)
           && setDouble(SpeedFields::ReferenceUnitGrossRatedCoolingCOP, referenceUnitGrossRatedCoolingCOP);
  }
  return setDouble(SpeedFields::ReferenceUnitGrossRatedCoolingCOP, referenceUnitGrossRatedCoolingCOP);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::referenceUnitRatedAirFlowRate() const {
  if (auto group = attachedGroup(*this)) {
    const auto value = group->getDouble(ParentFields::SpeedReferenceUnitRatedAirFlowRate);
    OS_ASSERT(value);
    return *value;
  }
  return requiredDetachedDouble(*this, SpeedFields::ReferenceUnitRatedAirFlowRate);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setReferenceUnitRatedAirFlowRate(double referenceUnitRatedAirFlowRate) {
  if (auto group = attachedGroup(*this)) {
    return group->setDouble(ParentFields::SpeedReferenceUnitRatedAirFlowRate, referenceUnitRatedAirFlowRate)
           && setDouble(SpeedFields::ReferenceUnitRatedAirFlowRate, referenceUnitRatedAirFlowRate);
  }
  return setDouble(SpeedFields::ReferenceUnitRatedAirFlowRate, referenceUnitRatedAirFlowRate);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::referenceUnitRatedWaterFlowRate() const {
  if (auto group = attachedGroup(*this)) {
    const auto value = group->getDouble(ParentFields::SpeedReferenceUnitRatedWaterFlowRate);
    OS_ASSERT(value);
    return *value;
  }
  return requiredDetachedDouble(*this, SpeedFields::ReferenceUnitRatedWaterFlowRate);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setReferenceUnitRatedWaterFlowRate(double referenceUnitRatedWaterFlowRate) {
  if (auto group = attachedGroup(*this)) {
    return group->setDouble(ParentFields::SpeedReferenceUnitRatedWaterFlowRate, referenceUnitRatedWaterFlowRate)
           && setDouble(SpeedFields::ReferenceUnitRatedWaterFlowRate, referenceUnitRatedWaterFlowRate);
  }
  return setDouble(SpeedFields::ReferenceUnitRatedWaterFlowRate, referenceUnitRatedWaterFlowRate);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::totalCoolingCapacityFunctionofTemperatureCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedTotalCoolingCapacityFunctionofTemperatureCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::TotalCoolingCapacityFunctionofTemperatureCurveName);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setTotalCoolingCapacityFunctionofTemperatureCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedTotalCoolingCapacityFunctionofTemperatureCurveName, curve.handle())
           && setPointer(SpeedFields::TotalCoolingCapacityFunctionofTemperatureCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::TotalCoolingCapacityFunctionofTemperatureCurveName, curve.handle(), false);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::totalCoolingCapacityFunctionofAirFlowFractionCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedTotalCoolingCapacityFunctionofAirFlowFractionCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::TotalCoolingCapacityFunctionofAirFlowFractionCurveName);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setTotalCoolingCapacityFunctionofAirFlowFractionCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedTotalCoolingCapacityFunctionofAirFlowFractionCurveName, curve.handle())
           && setPointer(SpeedFields::TotalCoolingCapacityFunctionofAirFlowFractionCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::TotalCoolingCapacityFunctionofAirFlowFractionCurveName, curve.handle(), false);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::totalCoolingCapacityFunctionofWaterFlowFractionCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedTotalCoolingCapacityFunctionofWaterFlowFractionCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::TotalCoolingCapacityFunctionofWaterFlowFractionCurveName);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setTotalCoolingCapacityFunctionofWaterFlowFractionCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedTotalCoolingCapacityFunctionofWaterFlowFractionCurveName, curve.handle())
           && setPointer(SpeedFields::TotalCoolingCapacityFunctionofWaterFlowFractionCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::TotalCoolingCapacityFunctionofWaterFlowFractionCurveName, curve.handle(), false);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::energyInputRatioFunctionofTemperatureCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedEnergyInputRatioFunctionofTemperatureCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::EnergyInputRatioFunctionofTemperatureCurveName);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedEnergyInputRatioFunctionofTemperatureCurveName, curve.handle())
           && setPointer(SpeedFields::EnergyInputRatioFunctionofTemperatureCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::EnergyInputRatioFunctionofTemperatureCurveName, curve.handle(), false);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::energyInputRatioFunctionofAirFlowFractionCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::EnergyInputRatioFunctionofAirFlowFractionCurveName);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setEnergyInputRatioFunctionofAirFlowFractionCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName, curve.handle())
           && setPointer(SpeedFields::EnergyInputRatioFunctionofAirFlowFractionCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::EnergyInputRatioFunctionofAirFlowFractionCurveName, curve.handle(), false);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::energyInputRatioFunctionofWaterFlowFractionCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedEnergyInputRatioFunctionofWaterFlowFractionCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::EnergyInputRatioFunctionofWaterFlowFractionCurveName);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setEnergyInputRatioFunctionofWaterFlowFractionCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedEnergyInputRatioFunctionofWaterFlowFractionCurveName, curve.handle())
           && setPointer(SpeedFields::EnergyInputRatioFunctionofWaterFlowFractionCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::EnergyInputRatioFunctionofWaterFlowFractionCurveName, curve.handle(), false);
}

double CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::referenceUnitWasteHeatFractionofInputPowerAtRatedConditions() const {
  if (auto group = attachedGroup(*this)) {
    const auto value = group->getDouble(ParentFields::SpeedReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions);
    OS_ASSERT(value);
    return *value;
  }
  return requiredDetachedDouble(*this, SpeedFields::ReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions(
  double referenceUnitWasteHeatFractionofInputPowerAtRatedConditions) {
  if (auto group = attachedGroup(*this)) {
    return group->setDouble(ParentFields::SpeedReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions,
                            referenceUnitWasteHeatFractionofInputPowerAtRatedConditions)
           && setDouble(SpeedFields::ReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions,
                        referenceUnitWasteHeatFractionofInputPowerAtRatedConditions);
  }
  return setDouble(SpeedFields::ReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions,
                   referenceUnitWasteHeatFractionofInputPowerAtRatedConditions);
}

Curve CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::wasteHeatFunctionofTemperatureCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedWasteHeatFunctionofTemperatureCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::WasteHeatFunctionofTemperatureCurveName);
}

bool CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setWasteHeatFunctionofTemperatureCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedWasteHeatFunctionofTemperatureCurveName, curve.handle())
           && setPointer(SpeedFields::WasteHeatFunctionofTemperatureCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::WasteHeatFunctionofTemperatureCurveName, curve.handle(), false);
}

std::vector<ModelObject> CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::children() const {
  std::vector<ModelObject> result;
  result.push_back(totalCoolingCapacityFunctionofTemperatureCurve());
  result.push_back(totalCoolingCapacityFunctionofAirFlowFractionCurve());
  result.push_back(totalCoolingCapacityFunctionofWaterFlowFractionCurve());
  result.push_back(energyInputRatioFunctionofTemperatureCurve());
  result.push_back(energyInputRatioFunctionofAirFlowFractionCurve());
  result.push_back(energyInputRatioFunctionofWaterFlowFractionCurve());
  result.push_back(wasteHeatFunctionofTemperatureCurve());
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
