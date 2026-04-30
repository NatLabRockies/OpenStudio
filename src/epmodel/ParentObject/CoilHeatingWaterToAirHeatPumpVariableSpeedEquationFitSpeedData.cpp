/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.hpp"
#include "ParentObject/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Model.hpp"
#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.hpp"
#include "WaterToAirComponent/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit_SpeedData_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

namespace {

std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>
makeDetachedSpeedDataImpl(const Model& model) {
  const auto generatedName = "__transient__heating_wtahp_vs_speed_data_" + openstudio::toString(openstudio::createUUID());
  auto transient =
    model.getOrCreateTransientByName<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData>(generatedName);
  auto impl = transient.getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>();
  OS_ASSERT(impl);
  return impl;
}

}  // namespace

CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(const Model& model)
  : ParentObject(makeDetachedSpeedDataImpl(model)) {
  CurveBiquadratic heatingCurve1(model);
  heatingCurve1.setCoefficient1Constant(0.617474);
  heatingCurve1.setCoefficient2x(-0.00245669);
  heatingCurve1.setCoefficient3xPOW2(-1.86550E-05);
  heatingCurve1.setCoefficient4y(0.0254921);
  heatingCurve1.setCoefficient5yPOW2(-1.00773E-04);
  heatingCurve1.setCoefficient6xTIMESY(-1.09447E-04);
  heatingCurve1.setMinimumValueofx(7.0);
  heatingCurve1.setMaximumValueofx(27.0);
  heatingCurve1.setMinimumValueofy(10.0);
  heatingCurve1.setMaximumValueofy(30.0);

  CurveQuadratic heatingCurve2(model);
  heatingCurve2.setCoefficient1Constant(1.0);
  heatingCurve2.setCoefficient2x(0.0);
  heatingCurve2.setCoefficient3xPOW2(0.0);
  heatingCurve2.setMinimumValueofx(0.0);
  heatingCurve2.setMaximumValueofx(1.0);

  CurveQuadratic heatingCurve3(model);
  heatingCurve3.setCoefficient1Constant(1.0);
  heatingCurve3.setCoefficient2x(0.0);
  heatingCurve3.setCoefficient3xPOW2(0.0);
  heatingCurve3.setMinimumValueofx(0.0);
  heatingCurve3.setMaximumValueofx(1.0);

  CurveBiquadratic heatingCurve4(model);
  heatingCurve4.setCoefficient1Constant(0.993257);
  heatingCurve4.setCoefficient2x(0.0201512);
  heatingCurve4.setCoefficient3xPOW2(7.72375E-05);
  heatingCurve4.setCoefficient4y(-0.0317207);
  heatingCurve4.setCoefficient5yPOW2(0.000740649);
  heatingCurve4.setCoefficient6xTIMESY(-3.03875E-04);
  heatingCurve4.setMinimumValueofx(7.0);
  heatingCurve4.setMaximumValueofx(27.0);
  heatingCurve4.setMinimumValueofy(10.0);
  heatingCurve4.setMaximumValueofy(30.0);

  CurveQuadratic heatingCurve5(model);
  heatingCurve5.setCoefficient1Constant(1.0);
  heatingCurve5.setCoefficient2x(0.0);
  heatingCurve5.setCoefficient3xPOW2(0.0);
  heatingCurve5.setMinimumValueofx(0.0);
  heatingCurve5.setMaximumValueofx(1.0);

  CurveQuadratic heatingCurve6(model);
  heatingCurve6.setCoefficient1Constant(1.0);
  heatingCurve6.setCoefficient2x(0.0);
  heatingCurve6.setCoefficient3xPOW2(0.0);
  heatingCurve6.setMinimumValueofx(0.0);
  heatingCurve6.setMaximumValueofx(1.0);

  CurveBiquadratic heatingCurve7(model);
  heatingCurve7.setCoefficient1Constant(1.0);
  heatingCurve7.setCoefficient2x(0.0);
  heatingCurve7.setCoefficient3xPOW2(0.0);
  heatingCurve7.setCoefficient4y(0.0);
  heatingCurve7.setCoefficient5yPOW2(0.0);
  heatingCurve7.setCoefficient6xTIMESY(0.0);
  heatingCurve7.setMinimumValueofx(7.0);
  heatingCurve7.setMaximumValueofx(27.0);
  heatingCurve7.setMinimumValueofy(10.0);
  heatingCurve7.setMaximumValueofy(30.0);

  bool ok = true;
  ok = setReferenceUnitGrossRatedHeatingCapacity(1838.7) && ok;
  ok = setReferenceUnitGrossRatedHeatingCOP(5.0) && ok;
  ok = setReferenceUnitRatedAirFlow(0.1661088) && ok;
  ok = setReferenceUnitRatedWaterFlowRate(0.000381695) && ok;
  ok = setReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions(0.1) && ok;
  ok = setHeatingCapacityFunctionofTemperatureCurve(heatingCurve1) && ok;
  ok = setTotalHeatingCapacityFunctionofAirFlowFractionCurve(heatingCurve2) && ok;
  ok = setHeatingCapacityFunctionofWaterFlowFractionCurve(heatingCurve3) && ok;
  ok = setEnergyInputRatioFunctionofTemperatureCurve(heatingCurve4) && ok;
  ok = setEnergyInputRatioFunctionofAirFlowFractionCurve(heatingCurve5) && ok;
  ok = setEnergyInputRatioFunctionofWaterFlowFractionCurve(heatingCurve6) && ok;
  ok = setWasteHeatFunctionofTemperatureCurve(heatingCurve7) && ok;
  OS_ASSERT(ok);
}

CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(
  const Model& model, const Curve& heatingCapacityFunctionofTemperature, const Curve& totalHeatingCapacityFunctionofAirFlowFraction,
  const Curve& heatingCapacityFunctionofWaterFlowFraction, const Curve& energyInputRatioFunctionofTemperature,
  const Curve& energyInputRatioFunctionofAirFlowFraction, const Curve& energyInputRatioFunctionofWaterFlowFraction,
  const Curve& wasteHeatFunctionofTemperature)
  : ParentObject(makeDetachedSpeedDataImpl(model)) {
  bool ok = true;
  ok = setReferenceUnitGrossRatedHeatingCapacity(1838.7) && ok;
  ok = setReferenceUnitGrossRatedHeatingCOP(5.0) && ok;
  ok = setReferenceUnitRatedAirFlow(0.1661088) && ok;
  ok = setReferenceUnitRatedWaterFlowRate(0.000381695) && ok;
  ok = setReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions(0.1) && ok;
  ok = setHeatingCapacityFunctionofTemperatureCurve(heatingCapacityFunctionofTemperature) && ok;
  ok = setTotalHeatingCapacityFunctionofAirFlowFractionCurve(totalHeatingCapacityFunctionofAirFlowFraction) && ok;
  ok = setHeatingCapacityFunctionofWaterFlowFractionCurve(heatingCapacityFunctionofWaterFlowFraction) && ok;
  ok = setEnergyInputRatioFunctionofTemperatureCurve(energyInputRatioFunctionofTemperature) && ok;
  ok = setEnergyInputRatioFunctionofAirFlowFractionCurve(energyInputRatioFunctionofAirFlowFraction) && ok;
  ok = setEnergyInputRatioFunctionofWaterFlowFractionCurve(energyInputRatioFunctionofWaterFlowFraction) && ok;
  ok = setWasteHeatFunctionofTemperatureCurve(wasteHeatFunctionofTemperature) && ok;
  OS_ASSERT(ok);
}

CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData(
  std::shared_ptr<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl> impl)
  : ParentObject(std::move(impl)) {}

IddObjectType CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::iddObjectType() {
  return IddObjectType::OS_Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit_SpeedData;
}

double CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::referenceUnitGrossRatedHeatingCapacity() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->referenceUnitGrossRatedHeatingCapacity();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setReferenceUnitGrossRatedHeatingCapacity(
  double referenceUnitGrossRatedHeatingCapacity) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setReferenceUnitGrossRatedHeatingCapacity(referenceUnitGrossRatedHeatingCapacity);
}

double CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::referenceUnitGrossRatedHeatingCOP() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->referenceUnitGrossRatedHeatingCOP();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setReferenceUnitGrossRatedHeatingCOP(double referenceUnitGrossRatedHeatingCOP) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setReferenceUnitGrossRatedHeatingCOP(referenceUnitGrossRatedHeatingCOP);
}

double CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::referenceUnitRatedAirFlow() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->referenceUnitRatedAirFlow();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setReferenceUnitRatedAirFlow(double referenceUnitRatedAirFlow) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->setReferenceUnitRatedAirFlow(referenceUnitRatedAirFlow);
}

double CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::referenceUnitRatedWaterFlowRate() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->referenceUnitRatedWaterFlowRate();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setReferenceUnitRatedWaterFlowRate(double referenceUnitRatedWaterFlowRate) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setReferenceUnitRatedWaterFlowRate(referenceUnitRatedWaterFlowRate);
}

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::heatingCapacityFunctionofTemperatureCurve() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->heatingCapacityFunctionofTemperatureCurve();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setHeatingCapacityFunctionofTemperatureCurve(const Curve& curve) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->setHeatingCapacityFunctionofTemperatureCurve(curve);
}

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::totalHeatingCapacityFunctionofAirFlowFractionCurve() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->totalHeatingCapacityFunctionofAirFlowFractionCurve();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setTotalHeatingCapacityFunctionofAirFlowFractionCurve(const Curve& curve) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setTotalHeatingCapacityFunctionofAirFlowFractionCurve(curve);
}

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::heatingCapacityFunctionofWaterFlowFractionCurve() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->heatingCapacityFunctionofWaterFlowFractionCurve();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setHeatingCapacityFunctionofWaterFlowFractionCurve(const Curve& curve) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setHeatingCapacityFunctionofWaterFlowFractionCurve(curve);
}

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::energyInputRatioFunctionofTemperatureCurve() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->energyInputRatioFunctionofTemperatureCurve();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setEnergyInputRatioFunctionofTemperatureCurve(curve);
}

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::energyInputRatioFunctionofAirFlowFractionCurve() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->energyInputRatioFunctionofAirFlowFractionCurve();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setEnergyInputRatioFunctionofAirFlowFractionCurve(const Curve& curve) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setEnergyInputRatioFunctionofAirFlowFractionCurve(curve);
}

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::energyInputRatioFunctionofWaterFlowFractionCurve() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->energyInputRatioFunctionofWaterFlowFractionCurve();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setEnergyInputRatioFunctionofWaterFlowFractionCurve(const Curve& curve) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setEnergyInputRatioFunctionofWaterFlowFractionCurve(curve);
}

double CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::referenceUnitWasteHeatFractionofInputPowerAtRatedConditions() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->referenceUnitWasteHeatFractionofInputPowerAtRatedConditions();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions(
  double referenceUnitWasteHeatFractionofInputPowerAtRatedConditions) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()
    ->setReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions(referenceUnitWasteHeatFractionofInputPowerAtRatedConditions);
}

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::wasteHeatFunctionofTemperatureCurve() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->wasteHeatFunctionofTemperatureCurve();
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::setWasteHeatFunctionofTemperatureCurve(const Curve& curve) {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->setWasteHeatFunctionofTemperatureCurve(curve);
}

std::vector<ModelObject> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData::children() const {
  return getImpl<detail::CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl>()->children();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

using ParentFields = openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitExtensibleFields;
using SpeedFields = openstudio::OS_Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit_SpeedDataFields;

boost::optional<WorkspaceExtensibleGroup> attachedGroup(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl& impl) {
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

double requiredDetachedDouble(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl& impl, unsigned field) {
  const auto value = impl.getDouble(field, true);
  OS_ASSERT(value);
  return *value;
}

Curve requiredDetachedCurve(const CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl& impl, unsigned field) {
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

boost::optional<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::parent() const {
  // These transient speed-data children still recover their owner by stable
  // transient name. That is deliberate for now: the wrapper is not persisted in
  // EnergyPlus, and epmodel does not yet carry an explicit transient parent
  // handle for this pattern.
  if (const auto thisName = getObject<ModelObject>().name()) {
    for (const auto& candidate : model().getModelObjects<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit>()) {
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

boost::optional<unsigned> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::attachedSpeedIndex() const {
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

double CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::referenceUnitGrossRatedHeatingCapacity() const {
  if (auto group = attachedGroup(*this)) {
    const auto value = group->getDouble(ParentFields::SpeedReferenceUnitGrossRatedHeatingCapacity);
    OS_ASSERT(value);
    return *value;
  }
  return requiredDetachedDouble(*this, SpeedFields::ReferenceUnitGrossRatedHeatingCapacity);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setReferenceUnitGrossRatedHeatingCapacity(
  double referenceUnitGrossRatedHeatingCapacity) {
  if (auto group = attachedGroup(*this)) {
    return group->setDouble(ParentFields::SpeedReferenceUnitGrossRatedHeatingCapacity, referenceUnitGrossRatedHeatingCapacity)
           && setDouble(SpeedFields::ReferenceUnitGrossRatedHeatingCapacity, referenceUnitGrossRatedHeatingCapacity);
  }
  return setDouble(SpeedFields::ReferenceUnitGrossRatedHeatingCapacity, referenceUnitGrossRatedHeatingCapacity);
}

double CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::referenceUnitGrossRatedHeatingCOP() const {
  if (auto group = attachedGroup(*this)) {
    const auto value = group->getDouble(ParentFields::SpeedReferenceUnitGrossRatedHeatingCOP);
    OS_ASSERT(value);
    return *value;
  }
  return requiredDetachedDouble(*this, SpeedFields::ReferenceUnitGrossRatedHeatingCOP);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setReferenceUnitGrossRatedHeatingCOP(double referenceUnitGrossRatedHeatingCOP) {
  if (auto group = attachedGroup(*this)) {
    return group->setDouble(ParentFields::SpeedReferenceUnitGrossRatedHeatingCOP, referenceUnitGrossRatedHeatingCOP)
           && setDouble(SpeedFields::ReferenceUnitGrossRatedHeatingCOP, referenceUnitGrossRatedHeatingCOP);
  }
  return setDouble(SpeedFields::ReferenceUnitGrossRatedHeatingCOP, referenceUnitGrossRatedHeatingCOP);
}

double CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::referenceUnitRatedAirFlow() const {
  if (auto group = attachedGroup(*this)) {
    const auto value = group->getDouble(ParentFields::SpeedReferenceUnitRatedAirFlowRate);
    OS_ASSERT(value);
    return *value;
  }
  return requiredDetachedDouble(*this, SpeedFields::ReferenceUnitRatedAirFlow);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setReferenceUnitRatedAirFlow(double referenceUnitRatedAirFlow) {
  if (auto group = attachedGroup(*this)) {
    return group->setDouble(ParentFields::SpeedReferenceUnitRatedAirFlowRate, referenceUnitRatedAirFlow)
           && setDouble(SpeedFields::ReferenceUnitRatedAirFlow, referenceUnitRatedAirFlow);
  }
  return setDouble(SpeedFields::ReferenceUnitRatedAirFlow, referenceUnitRatedAirFlow);
}

double CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::referenceUnitRatedWaterFlowRate() const {
  if (auto group = attachedGroup(*this)) {
    const auto value = group->getDouble(ParentFields::SpeedReferenceUnitRatedWaterFlowRate);
    OS_ASSERT(value);
    return *value;
  }
  return requiredDetachedDouble(*this, SpeedFields::ReferenceUnitRatedWaterFlowRate);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setReferenceUnitRatedWaterFlowRate(double referenceUnitRatedWaterFlowRate) {
  if (auto group = attachedGroup(*this)) {
    return group->setDouble(ParentFields::SpeedReferenceUnitRatedWaterFlowRate, referenceUnitRatedWaterFlowRate)
           && setDouble(SpeedFields::ReferenceUnitRatedWaterFlowRate, referenceUnitRatedWaterFlowRate);
  }
  return setDouble(SpeedFields::ReferenceUnitRatedWaterFlowRate, referenceUnitRatedWaterFlowRate);
}

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::heatingCapacityFunctionofTemperatureCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedHeatingCapacityFunctionofTemperatureCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::HeatingCapacityFunctionofTemperatureCurveName);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setHeatingCapacityFunctionofTemperatureCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedHeatingCapacityFunctionofTemperatureCurveName, curve.handle())
           && setPointer(SpeedFields::HeatingCapacityFunctionofTemperatureCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::HeatingCapacityFunctionofTemperatureCurveName, curve.handle(), false);
}

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::totalHeatingCapacityFunctionofAirFlowFractionCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedTotalHeatingCapacityFunctionofAirFlowFractionCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::TotalHeatingCapacityFunctionofAirFlowFractionCurveName);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setTotalHeatingCapacityFunctionofAirFlowFractionCurve(
  const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedTotalHeatingCapacityFunctionofAirFlowFractionCurveName, curve.handle())
           && setPointer(SpeedFields::TotalHeatingCapacityFunctionofAirFlowFractionCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::TotalHeatingCapacityFunctionofAirFlowFractionCurveName, curve.handle(), false);
}

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::heatingCapacityFunctionofWaterFlowFractionCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedHeatingCapacityFunctionofWaterFlowFractionCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::HeatingCapacityFunctionofWaterFlowFractionCurveName);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setHeatingCapacityFunctionofWaterFlowFractionCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedHeatingCapacityFunctionofWaterFlowFractionCurveName, curve.handle())
           && setPointer(SpeedFields::HeatingCapacityFunctionofWaterFlowFractionCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::HeatingCapacityFunctionofWaterFlowFractionCurveName, curve.handle(), false);
}

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::energyInputRatioFunctionofTemperatureCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedEnergyInputRatioFunctionofTemperatureCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::EnergyInputRatioFunctionofTemperatureCurveName);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedEnergyInputRatioFunctionofTemperatureCurveName, curve.handle())
           && setPointer(SpeedFields::EnergyInputRatioFunctionofTemperatureCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::EnergyInputRatioFunctionofTemperatureCurveName, curve.handle(), false);
}

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::energyInputRatioFunctionofAirFlowFractionCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::EnergyInputRatioFunctionofAirFlowFractionCurveName);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setEnergyInputRatioFunctionofAirFlowFractionCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName, curve.handle())
           && setPointer(SpeedFields::EnergyInputRatioFunctionofAirFlowFractionCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::EnergyInputRatioFunctionofAirFlowFractionCurveName, curve.handle(), false);
}

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::energyInputRatioFunctionofWaterFlowFractionCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedEnergyInputRatioFunctionofWaterFlowFractionCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::EnergyInputRatioFunctionofWaterFlowFractionCurveName);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setEnergyInputRatioFunctionofWaterFlowFractionCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedEnergyInputRatioFunctionofWaterFlowFractionCurveName, curve.handle())
           && setPointer(SpeedFields::EnergyInputRatioFunctionofWaterFlowFractionCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::EnergyInputRatioFunctionofWaterFlowFractionCurveName, curve.handle(), false);
}

double CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::referenceUnitWasteHeatFractionofInputPowerAtRatedConditions() const {
  if (auto group = attachedGroup(*this)) {
    const auto value = group->getDouble(ParentFields::SpeedReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions);
    OS_ASSERT(value);
    return *value;
  }
  return requiredDetachedDouble(*this, SpeedFields::ReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setReferenceUnitWasteHeatFractionofInputPowerAtRatedConditions(
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

Curve CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::wasteHeatFunctionofTemperatureCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedWasteHeatFunctionofTemperatureCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::WasteHeatFunctionofTemperatureCurveName);
}

bool CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::setWasteHeatFunctionofTemperatureCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedWasteHeatFunctionofTemperatureCurveName, curve.handle())
           && setPointer(SpeedFields::WasteHeatFunctionofTemperatureCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::WasteHeatFunctionofTemperatureCurveName, curve.handle(), false);
}

std::vector<ModelObject> CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl::children() const {
  std::vector<ModelObject> result;
  result.push_back(heatingCapacityFunctionofTemperatureCurve());
  result.push_back(totalHeatingCapacityFunctionofAirFlowFractionCurve());
  result.push_back(heatingCapacityFunctionofWaterFlowFractionCurve());
  result.push_back(energyInputRatioFunctionofTemperatureCurve());
  result.push_back(energyInputRatioFunctionofAirFlowFractionCurve());
  result.push_back(energyInputRatioFunctionofWaterFlowFractionCurve());
  result.push_back(wasteHeatFunctionofTemperatureCurve());
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
