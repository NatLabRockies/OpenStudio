/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData.hpp"
#include "ParentObject/CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveCubic.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Model.hpp"
#include "WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed.hpp"
#include "WaterToAirComponent/CoilWaterHeatingAirToWaterHeatPumpVariableSpeed_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedData_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

namespace {

std::shared_ptr<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl> makeDetachedSpeedDataImpl(const Model& model) {
  const auto generatedName = "__transient__wh_air_to_water_hp_vs_speed_data_" + openstudio::toString(openstudio::createUUID());
  auto transient = model.getOrCreateTransientByName<CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData>(generatedName);
  auto impl = transient.getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>();
  OS_ASSERT(impl);
  return impl;
}

}  // namespace

CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData(const Model& model)
  : ParentObject(makeDetachedSpeedDataImpl(model)) {
  CurveBiquadratic waterHeatingCap(model);
  OS_ASSERT(waterHeatingCap.setCoefficient1Constant(0.369827));
  OS_ASSERT(waterHeatingCap.setCoefficient2x(0.043341));
  OS_ASSERT(waterHeatingCap.setCoefficient3xPOW2(-0.00023));
  OS_ASSERT(waterHeatingCap.setCoefficient4y(0.000466));
  OS_ASSERT(waterHeatingCap.setCoefficient5yPOW2(0.000026));
  OS_ASSERT(waterHeatingCap.setCoefficient6xTIMESY(-0.00027));
  OS_ASSERT(waterHeatingCap.setMinimumValueofx(0.0));
  OS_ASSERT(waterHeatingCap.setMaximumValueofx(40.0));
  OS_ASSERT(waterHeatingCap.setMinimumValueofy(20.0));
  OS_ASSERT(waterHeatingCap.setMaximumValueofy(90.0));
  OS_ASSERT(waterHeatingCap.setInputUnitTypeforX("Temperature"));
  OS_ASSERT(waterHeatingCap.setInputUnitTypeforY("Temperature"));

  CurveCubic constantCubic(model);
  OS_ASSERT(constantCubic.setCoefficient1Constant(1.0));
  OS_ASSERT(constantCubic.setCoefficient2x(0.0));
  OS_ASSERT(constantCubic.setCoefficient3xPOW2(0.0));
  OS_ASSERT(constantCubic.setCoefficient4xPOW3(0.0));
  OS_ASSERT(constantCubic.setMinimumValueofx(-100.0));
  OS_ASSERT(constantCubic.setMaximumValueofx(100.0));

  CurveBiquadratic waterHeatingCOP(model);
  OS_ASSERT(waterHeatingCOP.setCoefficient1Constant(1.19713));
  OS_ASSERT(waterHeatingCOP.setCoefficient2x(0.077849));
  OS_ASSERT(waterHeatingCOP.setCoefficient3xPOW2(-0.0000016));
  OS_ASSERT(waterHeatingCOP.setCoefficient4y(-0.02675));
  OS_ASSERT(waterHeatingCOP.setCoefficient5yPOW2(0.000296));
  OS_ASSERT(waterHeatingCOP.setCoefficient6xTIMESY(-0.00112));
  OS_ASSERT(waterHeatingCOP.setMinimumValueofx(0.0));
  OS_ASSERT(waterHeatingCOP.setMaximumValueofx(40.0));
  OS_ASSERT(waterHeatingCOP.setMinimumValueofy(20.0));
  OS_ASSERT(waterHeatingCOP.setMaximumValueofy(90.0));
  OS_ASSERT(waterHeatingCOP.setInputUnitTypeforX("Temperature"));
  OS_ASSERT(waterHeatingCOP.setInputUnitTypeforY("Temperature"));

  bool ok = true;
  ok = setRatedWaterHeatingCapacity(400.0) && ok;
  ok = setRatedWaterHeatingCOP(5.0) && ok;
  ok = setRatedSensibleHeatRatio(0.8) && ok;
  ok = setReferenceUnitRatedAirFlowRate(0.02014) && ok;
  ok = setReferenceUnitRatedWaterFlowRate(0.000018) && ok;
  ok = setReferenceUnitWaterPumpInputPowerAtRatedConditions(10.0) && ok;
  ok = setTotalWaterHeatingCapacityFunctionofTemperatureCurve(waterHeatingCap) && ok;
  ok = setTotalWaterHeatingCapacityFunctionofAirFlowFractionCurve(constantCubic) && ok;
  ok = setTotalWaterHeatingCapacityFunctionofWaterFlowFractionCurve(constantCubic) && ok;
  ok = setCOPFunctionofTemperatureCurve(waterHeatingCOP) && ok;
  ok = setCOPFunctionofAirFlowFractionCurve(constantCubic) && ok;
  ok = setCOPFunctionofWaterFlowFractionCurve(constantCubic) && ok;
  OS_ASSERT(ok);
}

CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData(
  std::shared_ptr<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl> impl)
  : ParentObject(std::move(impl)) {}

IddObjectType CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::iddObjectType() {
  return IddObjectType::OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedData;
}

double CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::ratedWaterHeatingCapacity() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->ratedWaterHeatingCapacity();
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::setRatedWaterHeatingCapacity(double ratedWaterHeatingCapacity) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->setRatedWaterHeatingCapacity(ratedWaterHeatingCapacity);
}

double CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::ratedWaterHeatingCOP() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->ratedWaterHeatingCOP();
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::setRatedWaterHeatingCOP(double ratedWaterHeatingCOP) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->setRatedWaterHeatingCOP(ratedWaterHeatingCOP);
}

double CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::ratedSensibleHeatRatio() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->ratedSensibleHeatRatio();
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->setRatedSensibleHeatRatio(ratedSensibleHeatRatio);
}

double CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::referenceUnitRatedAirFlowRate() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->referenceUnitRatedAirFlowRate();
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::setReferenceUnitRatedAirFlowRate(double referenceUnitRatedAirFlowRate) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->setReferenceUnitRatedAirFlowRate(
    referenceUnitRatedAirFlowRate);
}

double CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::referenceUnitRatedWaterFlowRate() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->referenceUnitRatedWaterFlowRate();
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::setReferenceUnitRatedWaterFlowRate(double referenceUnitRatedWaterFlowRate) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->setReferenceUnitRatedWaterFlowRate(
    referenceUnitRatedWaterFlowRate);
}

double CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::referenceUnitWaterPumpInputPowerAtRatedConditions() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->referenceUnitWaterPumpInputPowerAtRatedConditions();
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::setReferenceUnitWaterPumpInputPowerAtRatedConditions(
  double referenceUnitWaterPumpInputPowerAtRatedConditions) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->setReferenceUnitWaterPumpInputPowerAtRatedConditions(
    referenceUnitWaterPumpInputPowerAtRatedConditions);
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::totalWaterHeatingCapacityFunctionofTemperatureCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->totalWaterHeatingCapacityFunctionofTemperatureCurve();
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::setTotalWaterHeatingCapacityFunctionofTemperatureCurve(const Curve& curve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->setTotalWaterHeatingCapacityFunctionofTemperatureCurve(
    curve);
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::totalWaterHeatingCapacityFunctionofAirFlowFractionCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->totalWaterHeatingCapacityFunctionofAirFlowFractionCurve();
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::setTotalWaterHeatingCapacityFunctionofAirFlowFractionCurve(const Curve& curve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->setTotalWaterHeatingCapacityFunctionofAirFlowFractionCurve(
    curve);
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::totalWaterHeatingCapacityFunctionofWaterFlowFractionCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()
    ->totalWaterHeatingCapacityFunctionofWaterFlowFractionCurve();
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::setTotalWaterHeatingCapacityFunctionofWaterFlowFractionCurve(const Curve& curve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()
    ->setTotalWaterHeatingCapacityFunctionofWaterFlowFractionCurve(curve);
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::copFunctionofTemperatureCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->cOPFunctionofTemperatureCurve();
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::cOPFunctionofTemperatureCurve() const {
  return copFunctionofTemperatureCurve();
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::setCOPFunctionofTemperatureCurve(const Curve& curve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->setCOPFunctionofTemperatureCurve(curve);
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::copFunctionofAirFlowFractionCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->cOPFunctionofAirFlowFractionCurve();
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::cOPFunctionofAirFlowFractionCurve() const {
  return copFunctionofAirFlowFractionCurve();
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::setCOPFunctionofAirFlowFractionCurve(const Curve& curve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->setCOPFunctionofAirFlowFractionCurve(curve);
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::copFunctionofWaterFlowFractionCurve() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->cOPFunctionofWaterFlowFractionCurve();
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::cOPFunctionofWaterFlowFractionCurve() const {
  return copFunctionofWaterFlowFractionCurve();
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::setCOPFunctionofWaterFlowFractionCurve(const Curve& curve) {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->setCOPFunctionofWaterFlowFractionCurve(curve);
}

std::vector<ModelObject> CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData::children() const {
  return getImpl<detail::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl>()->children();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

namespace {

using ParentFields = openstudio::Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields;
using SpeedFields = openstudio::OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields;

boost::optional<WorkspaceExtensibleGroup> attachedGroup(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl& impl) {
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

double requiredDetachedDouble(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl& impl, unsigned field) {
  const auto value = impl.getDouble(field, true);
  OS_ASSERT(value);
  return *value;
}

Curve requiredDetachedCurve(const CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl& impl, unsigned field) {
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

boost::optional<CoilWaterHeatingAirToWaterHeatPumpVariableSpeed> CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::parent() const {
  if (const auto thisName = getObject<ModelObject>().name()) {
    for (const auto& candidate : model().getModelObjects<CoilWaterHeatingAirToWaterHeatPumpVariableSpeed>()) {
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

boost::optional<unsigned> CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::attachedSpeedIndex() const {
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

#define ATTACHED_DOUBLE_GETTER(method, parentField, detachedField) \
double CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::method() const { \
  if (auto group = attachedGroup(*this)) { \
    const auto value = group->getDouble(parentField); \
    OS_ASSERT(value); \
    return *value; \
  } \
  return requiredDetachedDouble(*this, detachedField); \
}

#define ATTACHED_DOUBLE_SETTER(method, parentField, detachedField) \
bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::method(double value) { \
  if (auto group = attachedGroup(*this)) { \
    return group->setDouble(parentField, value) && setDouble(detachedField, value); \
  } \
  return setDouble(detachedField, value); \
}

ATTACHED_DOUBLE_GETTER(ratedWaterHeatingCapacity, ParentFields::SpeedRatedWaterHeatingCapacity, SpeedFields::RatedWaterHeatingCapacity)
ATTACHED_DOUBLE_SETTER(setRatedWaterHeatingCapacity, ParentFields::SpeedRatedWaterHeatingCapacity, SpeedFields::RatedWaterHeatingCapacity)
ATTACHED_DOUBLE_GETTER(ratedWaterHeatingCOP, ParentFields::SpeedRatedWaterHeatingCOP, SpeedFields::RatedWaterHeatingCOP)
ATTACHED_DOUBLE_SETTER(setRatedWaterHeatingCOP, ParentFields::SpeedRatedWaterHeatingCOP, SpeedFields::RatedWaterHeatingCOP)
ATTACHED_DOUBLE_GETTER(ratedSensibleHeatRatio, ParentFields::SpeedRatedSensibleHeatRatio, SpeedFields::RatedSensibleHeatRatio)
ATTACHED_DOUBLE_SETTER(setRatedSensibleHeatRatio, ParentFields::SpeedRatedSensibleHeatRatio, SpeedFields::RatedSensibleHeatRatio)
ATTACHED_DOUBLE_GETTER(referenceUnitRatedAirFlowRate, ParentFields::SpeedReferenceUnitRatedAirFlowRate, SpeedFields::ReferenceUnitRatedAirFlowRate)
ATTACHED_DOUBLE_SETTER(setReferenceUnitRatedAirFlowRate, ParentFields::SpeedReferenceUnitRatedAirFlowRate,
                       SpeedFields::ReferenceUnitRatedAirFlowRate)
ATTACHED_DOUBLE_GETTER(referenceUnitRatedWaterFlowRate, ParentFields::SpeedReferenceUnitRatedWaterFlowRate,
                       SpeedFields::ReferenceUnitRatedWaterFlowRate)
ATTACHED_DOUBLE_SETTER(setReferenceUnitRatedWaterFlowRate, ParentFields::SpeedReferenceUnitRatedWaterFlowRate,
                       SpeedFields::ReferenceUnitRatedWaterFlowRate)
ATTACHED_DOUBLE_GETTER(referenceUnitWaterPumpInputPowerAtRatedConditions,
                       ParentFields::SpeedReferenceUnitWaterPumpInputPowerAtRatedConditions,
                       SpeedFields::ReferenceUnitWaterPumpInputPowerAtRatedConditions)
ATTACHED_DOUBLE_SETTER(setReferenceUnitWaterPumpInputPowerAtRatedConditions,
                       ParentFields::SpeedReferenceUnitWaterPumpInputPowerAtRatedConditions,
                       SpeedFields::ReferenceUnitWaterPumpInputPowerAtRatedConditions)

#undef ATTACHED_DOUBLE_GETTER
#undef ATTACHED_DOUBLE_SETTER

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::totalWaterHeatingCapacityFunctionofTemperatureCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedTotalWHCapacityFunctionofTemperatureCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::TotalWaterHeatingCapacityFunctionofTemperatureCurveName);
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::setTotalWaterHeatingCapacityFunctionofTemperatureCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedTotalWHCapacityFunctionofTemperatureCurveName, curve.handle())
           && setPointer(SpeedFields::TotalWaterHeatingCapacityFunctionofTemperatureCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::TotalWaterHeatingCapacityFunctionofTemperatureCurveName, curve.handle(), false);
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::totalWaterHeatingCapacityFunctionofAirFlowFractionCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedTotalWHCapacityFunctionofAirFlowFractionCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::TotalWaterHeatingCapacityFunctionofAirFlowFractionCurveName);
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::setTotalWaterHeatingCapacityFunctionofAirFlowFractionCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedTotalWHCapacityFunctionofAirFlowFractionCurveName, curve.handle())
           && setPointer(SpeedFields::TotalWaterHeatingCapacityFunctionofAirFlowFractionCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::TotalWaterHeatingCapacityFunctionofAirFlowFractionCurveName, curve.handle(), false);
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::totalWaterHeatingCapacityFunctionofWaterFlowFractionCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedTotalWHCapacityFunctionofWaterFlowFractionCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::TotalWaterHeatingCapacityFunctionofWaterFlowFractionCurveName);
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::setTotalWaterHeatingCapacityFunctionofWaterFlowFractionCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedTotalWHCapacityFunctionofWaterFlowFractionCurveName, curve.handle())
           && setPointer(SpeedFields::TotalWaterHeatingCapacityFunctionofWaterFlowFractionCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::TotalWaterHeatingCapacityFunctionofWaterFlowFractionCurveName, curve.handle(), false);
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::cOPFunctionofTemperatureCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedCOPFunctionofTemperatureCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::COPFunctionofTemperatureCurveName);
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::setCOPFunctionofTemperatureCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedCOPFunctionofTemperatureCurveName, curve.handle())
           && setPointer(SpeedFields::COPFunctionofTemperatureCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::COPFunctionofTemperatureCurveName, curve.handle(), false);
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::cOPFunctionofAirFlowFractionCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedCOPFunctionofAirFlowFractionCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::COPFunctionofAirFlowFractionCurveName);
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::setCOPFunctionofAirFlowFractionCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedCOPFunctionofAirFlowFractionCurveName, curve.handle())
           && setPointer(SpeedFields::COPFunctionofAirFlowFractionCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::COPFunctionofAirFlowFractionCurveName, curve.handle(), false);
}

Curve CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::cOPFunctionofWaterFlowFractionCurve() const {
  if (auto group = attachedGroup(*this)) {
    return requiredAttachedCurve(*group, ParentFields::SpeedCOPFunctionofWaterFlowFractionCurveName,
                                 [](const WorkspaceExtensibleGroup& g, unsigned f) { return g.getTarget(f); });
  }
  return requiredDetachedCurve(*this, SpeedFields::COPFunctionofWaterFlowFractionCurveName);
}

bool CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::setCOPFunctionofWaterFlowFractionCurve(const Curve& curve) {
  if (auto group = attachedGroup(*this)) {
    return group->setPointer(ParentFields::SpeedCOPFunctionofWaterFlowFractionCurveName, curve.handle())
           && setPointer(SpeedFields::COPFunctionofWaterFlowFractionCurveName, curve.handle(), false);
  }
  return setPointer(SpeedFields::COPFunctionofWaterFlowFractionCurveName, curve.handle(), false);
}

std::vector<ModelObject> CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::children() const {
  return {totalWaterHeatingCapacityFunctionofTemperatureCurve(), totalWaterHeatingCapacityFunctionofAirFlowFractionCurve(),
          totalWaterHeatingCapacityFunctionofWaterFlowFractionCurve(), cOPFunctionofTemperatureCurve(),
          cOPFunctionofAirFlowFractionCurve(), cOPFunctionofWaterFlowFractionCurve()};
}

std::vector<IdfObject> CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData_Impl::remove() {
  std::vector<ModelObject> detachedChildren;
  if (!parent()) {
    for (const auto& child : children()) {
      if (std::ranges::none_of(detachedChildren, [&](const auto& existing) { return existing.handle() == child.handle(); })) {
        detachedChildren.push_back(child);
      }
    }
  }

  if (auto currentParent = parent()) {
    currentParent->removeSpeed(getObject<openstudio::epmodel::CoilWaterHeatingAirToWaterHeatPumpVariableSpeedSpeedData>());
  }

  auto result = ParentObject_Impl::remove();
  for (auto& child : detachedChildren) {
    const auto removedChildren = child.remove();
    result.insert(result.end(), removedChildren.begin(), removedChildren.end());
  }
  return result;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
