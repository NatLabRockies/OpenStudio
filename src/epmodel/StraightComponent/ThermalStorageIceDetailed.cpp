/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/ThermalStorageIceDetailed.hpp"
#include "StraightComponent/ThermalStorageIceDetailed_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveQuadraticLinear.hpp"
#include "Curve/CurveQuadraticLinear_Impl.hpp"
#include "Model.hpp"
#include "Loop/PlantLoop.hpp"
#include "StraightComponent/Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <memory>
#include <utility>

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ThermalStorage_Ice_Detailed_FieldEnums.hxx>

#include <sstream>
#include <stdexcept>

namespace openstudio {
namespace epmodel {

  ThermalStorageIceDetailed::ThermalStorageIceDetailed(const Model& model) : StraightComponent(iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ThermalStorageIceDetailed_Impl>());

    {
      CurveQuadraticLinear curve(model);
      curve.setCoefficient1Constant(0.0);
      curve.setCoefficient2x(0.09);
      curve.setCoefficient3xPOW2(-0.15);
      curve.setCoefficient4y(0.612);
      curve.setCoefficient5xTIMESY(-0.324);
      curve.setCoefficient6xPOW2TIMESY(-0.216);
      curve.setMinimumValueofx(0.0);
      curve.setMaximumValueofx(1.0);
      curve.setMinimumValueofy(0.0);
      curve.setMaximumValueofy(9.9);

      OS_ASSERT(getImpl<detail::ThermalStorageIceDetailed_Impl>()->setDischargingCurveVariableSpecifications("FractionDischargedLMTD"));
      OS_ASSERT(getImpl<detail::ThermalStorageIceDetailed_Impl>()->setDischargingCurve(curve));
    }

    {
      CurveQuadraticLinear curve(model);
      curve.setCoefficient1Constant(0.0);
      curve.setCoefficient2x(0.09);
      curve.setCoefficient3xPOW2(-0.15);
      curve.setCoefficient4y(0.612);
      curve.setCoefficient5xTIMESY(-0.324);
      curve.setCoefficient6xPOW2TIMESY(-0.216);
      curve.setMinimumValueofx(0.0);
      curve.setMaximumValueofx(1.0);
      curve.setMinimumValueofy(0.0);
      curve.setMaximumValueofy(9.9);

      OS_ASSERT(getImpl<detail::ThermalStorageIceDetailed_Impl>()->setChargingCurveVariableSpecifications("FractionChargedLMTD"));
      OS_ASSERT(getImpl<detail::ThermalStorageIceDetailed_Impl>()->setChargingCurve(curve));
    }

    OS_ASSERT(getImpl<detail::ThermalStorageIceDetailed_Impl>()->setCapacity(0.5));
    OS_ASSERT(getImpl<detail::ThermalStorageIceDetailed_Impl>()->setTimestepoftheCurveData(1.0));
    OS_ASSERT(getImpl<detail::ThermalStorageIceDetailed_Impl>()->setParasiticElectricLoadDuringDischarging(0.0001));
    OS_ASSERT(getImpl<detail::ThermalStorageIceDetailed_Impl>()->setParasiticElectricLoadDuringCharging(0.0002));
    OS_ASSERT(getImpl<detail::ThermalStorageIceDetailed_Impl>()->setTankLossCoefficient(0.0003));
    OS_ASSERT(getImpl<detail::ThermalStorageIceDetailed_Impl>()->setFreezingTemperatureofStorageMedium(0.0));
    OS_ASSERT(getImpl<detail::ThermalStorageIceDetailed_Impl>()->setThawProcessIndicator("OutsideMelt"));
  }

  ThermalStorageIceDetailed::ThermalStorageIceDetailed(std::shared_ptr<detail::ThermalStorageIceDetailed_Impl> impl)
    : StraightComponent(std::static_pointer_cast<detail::StraightComponent_Impl>(std::move(impl))) {}

  IddObjectType ThermalStorageIceDetailed::iddObjectType() {
    return IddObjectType::ThermalStorage_Ice_Detailed;
  }

  std::vector<std::string> ThermalStorageIceDetailed::dischargingCurveVariableSpecificationsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ThermalStorage_Ice_DetailedFields::DischargingCurveVariableSpecifications);
  }

  std::vector<std::string> ThermalStorageIceDetailed::chargingCurveVariableSpecificationsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ThermalStorage_Ice_DetailedFields::ChargingCurveVariableSpecifications);
  }

  std::vector<std::string> ThermalStorageIceDetailed::thawProcessIndicatorValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ThermalStorage_Ice_DetailedFields::ThawProcessIndicator);
  }

  boost::optional<Schedule> ThermalStorageIceDetailed::availabilitySchedule() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->availabilitySchedule();
  }

  bool ThermalStorageIceDetailed::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setAvailabilitySchedule(schedule);
  }

  void ThermalStorageIceDetailed::resetAvailabilitySchedule() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->resetAvailabilitySchedule();
  }

  Curve ThermalStorageIceDetailed::dischargingCurve() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->dischargingCurve();
  }

  bool ThermalStorageIceDetailed::setDischargingCurve(const Curve& dischargingCurve) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setDischargingCurve(dischargingCurve);
  }

  Curve ThermalStorageIceDetailed::chargingCurve() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->chargingCurve();
  }

  bool ThermalStorageIceDetailed::setChargingCurve(const Curve& chargingCurve) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setChargingCurve(chargingCurve);
  }

  double ThermalStorageIceDetailed::capacity() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->capacity();
  }

  bool ThermalStorageIceDetailed::setCapacity(double capacity) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setCapacity(capacity);
  }

  bool ThermalStorageIceDetailed::isCapacityAutosized() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->isCapacityAutosized();
  }

  void ThermalStorageIceDetailed::autosizeCapacity() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->autosizeCapacity();
  }

  std::string ThermalStorageIceDetailed::dischargingCurveVariableSpecifications() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->dischargingCurveVariableSpecifications();
  }

  bool ThermalStorageIceDetailed::setDischargingCurveVariableSpecifications(const std::string& dischargingCurveVariableSpecifications) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setDischargingCurveVariableSpecifications(dischargingCurveVariableSpecifications);
  }

  std::string ThermalStorageIceDetailed::chargingCurveVariableSpecifications() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->chargingCurveVariableSpecifications();
  }

  bool ThermalStorageIceDetailed::setChargingCurveVariableSpecifications(const std::string& chargingCurveVariableSpecifications) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setChargingCurveVariableSpecifications(chargingCurveVariableSpecifications);
  }

  boost::optional<double> ThermalStorageIceDetailed::timestepoftheCurveData() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->timestepoftheCurveData();
  }

  bool ThermalStorageIceDetailed::setTimestepoftheCurveData(double timestepoftheCurveData) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setTimestepoftheCurveData(timestepoftheCurveData);
  }

  void ThermalStorageIceDetailed::resetTimestepoftheCurveData() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->resetTimestepoftheCurveData();
  }

  boost::optional<double> ThermalStorageIceDetailed::parasiticElectricLoadDuringDischarging() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->parasiticElectricLoadDuringDischarging();
  }

  bool ThermalStorageIceDetailed::setParasiticElectricLoadDuringDischarging(double parasiticElectricLoadDuringDischarging) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setParasiticElectricLoadDuringDischarging(parasiticElectricLoadDuringDischarging);
  }

  void ThermalStorageIceDetailed::resetParasiticElectricLoadDuringDischarging() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->resetParasiticElectricLoadDuringDischarging();
  }

  boost::optional<double> ThermalStorageIceDetailed::parasiticElectricLoadDuringCharging() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->parasiticElectricLoadDuringCharging();
  }

  bool ThermalStorageIceDetailed::setParasiticElectricLoadDuringCharging(double parasiticElectricLoadDuringCharging) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setParasiticElectricLoadDuringCharging(parasiticElectricLoadDuringCharging);
  }

  void ThermalStorageIceDetailed::resetParasiticElectricLoadDuringCharging() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->resetParasiticElectricLoadDuringCharging();
  }

  boost::optional<double> ThermalStorageIceDetailed::tankLossCoefficient() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->tankLossCoefficient();
  }

  bool ThermalStorageIceDetailed::setTankLossCoefficient(double tankLossCoefficient) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setTankLossCoefficient(tankLossCoefficient);
  }

  void ThermalStorageIceDetailed::resetTankLossCoefficient() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->resetTankLossCoefficient();
  }

  double ThermalStorageIceDetailed::freezingTemperatureofStorageMedium() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->freezingTemperatureofStorageMedium();
  }

  bool ThermalStorageIceDetailed::setFreezingTemperatureofStorageMedium(double freezingTemperatureofStorageMedium) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setFreezingTemperatureofStorageMedium(freezingTemperatureofStorageMedium);
  }

  bool ThermalStorageIceDetailed::isFreezingTemperatureofStorageMediumDefaulted() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->isFreezingTemperatureofStorageMediumDefaulted();
  }

  void ThermalStorageIceDetailed::resetFreezingTemperatureofStorageMedium() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->resetFreezingTemperatureofStorageMedium();
  }

  std::string ThermalStorageIceDetailed::thawProcessIndicator() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->thawProcessIndicator();
  }

  bool ThermalStorageIceDetailed::setThawProcessIndicator(const std::string& thawProcessIndicator) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->setThawProcessIndicator(thawProcessIndicator);
  }

  bool ThermalStorageIceDetailed::isThawProcessIndicatorDefaulted() const {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->isThawProcessIndicatorDefaulted();
  }

  void ThermalStorageIceDetailed::resetThawProcessIndicator() {
    getImpl<detail::ThermalStorageIceDetailed_Impl>()->resetThawProcessIndicator();
  }

  bool ThermalStorageIceDetailed::addToNode(Node& node) {
    return getImpl<detail::ThermalStorageIceDetailed_Impl>()->addToNode(node);
  }

  namespace detail {

    unsigned ThermalStorageIceDetailed_Impl::inletPort() const {
      return openstudio::ThermalStorage_Ice_DetailedFields::InletNodeName;
    }

    unsigned ThermalStorageIceDetailed_Impl::outletPort() const {
      return openstudio::ThermalStorage_Ice_DetailedFields::OutletNodeName;
    }

    std::vector<ModelObject> ThermalStorageIceDetailed_Impl::children() const {
      std::vector<ModelObject> result;
      result.push_back(dischargingCurve());
      result.push_back(chargingCurve());
      return result;
    }

    bool ThermalStorageIceDetailed_Impl::addToNode(Node& node) {
      if (auto plant = node.plantLoop()) {
        if (!plant->demandComponent(node.handle())) {
          return false;
        }
        return StraightComponent_Impl::addToNode(node);
      }

      return false;
    }

    boost::optional<Schedule> ThermalStorageIceDetailed_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::ThermalStorage_Ice_DetailedFields::AvailabilityScheduleName);
    }

    bool ThermalStorageIceDetailed_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::ThermalStorage_Ice_DetailedFields::AvailabilityScheduleName, schedule.handle(), false);
    }

    void ThermalStorageIceDetailed_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setPointer(openstudio::ThermalStorage_Ice_DetailedFields::AvailabilityScheduleName, openstudio::Handle(), false));
    }

    Curve ThermalStorageIceDetailed_Impl::dischargingCurve() const {
      auto value = optionalDischargingCurve();
      if (!value) {
        std::ostringstream message;
        message << briefDescription() << " does not have a Discharging Curve attached.";
        throw std::runtime_error(message.str());
      }
      return *value;
    }

    bool ThermalStorageIceDetailed_Impl::setDischargingCurve(const Curve& dischargingCurve) {
      return setPointer(openstudio::ThermalStorage_Ice_DetailedFields::DischargingCurveName, dischargingCurve.handle(), false);
    }

    Curve ThermalStorageIceDetailed_Impl::chargingCurve() const {
      auto value = optionalChargingCurve();
      if (!value) {
        std::ostringstream message;
        message << briefDescription() << " does not have a Charging Curve attached.";
        throw std::runtime_error(message.str());
      }
      return *value;
    }

    bool ThermalStorageIceDetailed_Impl::setChargingCurve(const Curve& chargingCurve) {
      return setPointer(openstudio::ThermalStorage_Ice_DetailedFields::ChargingCurveName, chargingCurve.handle(), false);
    }

    double ThermalStorageIceDetailed_Impl::capacity() const {
      auto value = getDouble(openstudio::ThermalStorage_Ice_DetailedFields::Capacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageIceDetailed_Impl::setCapacity(double capacity) {
      return setDouble(openstudio::ThermalStorage_Ice_DetailedFields::Capacity, capacity);
    }

    bool ThermalStorageIceDetailed_Impl::isCapacityAutosized() const {
      if (auto value = getString(openstudio::ThermalStorage_Ice_DetailedFields::Capacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void ThermalStorageIceDetailed_Impl::autosizeCapacity() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::Capacity, "autosize"));
    }

    std::string ThermalStorageIceDetailed_Impl::dischargingCurveVariableSpecifications() const {
      auto value = getString(openstudio::ThermalStorage_Ice_DetailedFields::DischargingCurveVariableSpecifications, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageIceDetailed_Impl::setDischargingCurveVariableSpecifications(const std::string& dischargingCurveVariableSpecifications) {
      return setString(openstudio::ThermalStorage_Ice_DetailedFields::DischargingCurveVariableSpecifications, dischargingCurveVariableSpecifications);
    }

    std::string ThermalStorageIceDetailed_Impl::chargingCurveVariableSpecifications() const {
      auto value = getString(openstudio::ThermalStorage_Ice_DetailedFields::ChargingCurveVariableSpecifications, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageIceDetailed_Impl::setChargingCurveVariableSpecifications(const std::string& chargingCurveVariableSpecifications) {
      return setString(openstudio::ThermalStorage_Ice_DetailedFields::ChargingCurveVariableSpecifications, chargingCurveVariableSpecifications);
    }

    boost::optional<double> ThermalStorageIceDetailed_Impl::timestepoftheCurveData() const {
      return getDouble(openstudio::ThermalStorage_Ice_DetailedFields::TimestepoftheCurveData, true);
    }

    bool ThermalStorageIceDetailed_Impl::setTimestepoftheCurveData(double timestepoftheCurveData) {
      return setDouble(openstudio::ThermalStorage_Ice_DetailedFields::TimestepoftheCurveData, timestepoftheCurveData);
    }

    void ThermalStorageIceDetailed_Impl::resetTimestepoftheCurveData() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::TimestepoftheCurveData, ""));
    }

    boost::optional<double> ThermalStorageIceDetailed_Impl::parasiticElectricLoadDuringDischarging() const {
      return getDouble(openstudio::ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringDischarging, true);
    }

    bool ThermalStorageIceDetailed_Impl::setParasiticElectricLoadDuringDischarging(double parasiticElectricLoadDuringDischarging) {
      return setDouble(openstudio::ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringDischarging, parasiticElectricLoadDuringDischarging);
    }

    void ThermalStorageIceDetailed_Impl::resetParasiticElectricLoadDuringDischarging() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringDischarging, ""));
    }

    boost::optional<double> ThermalStorageIceDetailed_Impl::parasiticElectricLoadDuringCharging() const {
      return getDouble(openstudio::ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringCharging, true);
    }

    bool ThermalStorageIceDetailed_Impl::setParasiticElectricLoadDuringCharging(double parasiticElectricLoadDuringCharging) {
      return setDouble(openstudio::ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringCharging, parasiticElectricLoadDuringCharging);
    }

    void ThermalStorageIceDetailed_Impl::resetParasiticElectricLoadDuringCharging() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::ParasiticElectricLoadDuringCharging, ""));
    }

    boost::optional<double> ThermalStorageIceDetailed_Impl::tankLossCoefficient() const {
      return getDouble(openstudio::ThermalStorage_Ice_DetailedFields::TankLossCoefficient, true);
    }

    bool ThermalStorageIceDetailed_Impl::setTankLossCoefficient(double tankLossCoefficient) {
      return setDouble(openstudio::ThermalStorage_Ice_DetailedFields::TankLossCoefficient, tankLossCoefficient);
    }

    void ThermalStorageIceDetailed_Impl::resetTankLossCoefficient() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::TankLossCoefficient, ""));
    }

    double ThermalStorageIceDetailed_Impl::freezingTemperatureofStorageMedium() const {
      auto value = getDouble(openstudio::ThermalStorage_Ice_DetailedFields::FreezingTemperatureofStorageMedium, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageIceDetailed_Impl::setFreezingTemperatureofStorageMedium(double freezingTemperatureofStorageMedium) {
      return setDouble(openstudio::ThermalStorage_Ice_DetailedFields::FreezingTemperatureofStorageMedium, freezingTemperatureofStorageMedium);
    }

    bool ThermalStorageIceDetailed_Impl::isFreezingTemperatureofStorageMediumDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_Ice_DetailedFields::FreezingTemperatureofStorageMedium);
    }

    void ThermalStorageIceDetailed_Impl::resetFreezingTemperatureofStorageMedium() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::FreezingTemperatureofStorageMedium, ""));
    }

    std::string ThermalStorageIceDetailed_Impl::thawProcessIndicator() const {
      auto value = getString(openstudio::ThermalStorage_Ice_DetailedFields::ThawProcessIndicator, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ThermalStorageIceDetailed_Impl::setThawProcessIndicator(const std::string& thawProcessIndicator) {
      return setString(openstudio::ThermalStorage_Ice_DetailedFields::ThawProcessIndicator, thawProcessIndicator);
    }

    bool ThermalStorageIceDetailed_Impl::isThawProcessIndicatorDefaulted() const {
      return isEmpty(openstudio::ThermalStorage_Ice_DetailedFields::ThawProcessIndicator);
    }

    void ThermalStorageIceDetailed_Impl::resetThawProcessIndicator() {
      OS_ASSERT(setString(openstudio::ThermalStorage_Ice_DetailedFields::ThawProcessIndicator, ""));
    }

    boost::optional<Curve> ThermalStorageIceDetailed_Impl::optionalDischargingCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::ThermalStorage_Ice_DetailedFields::DischargingCurveName);
    }

    boost::optional<Curve> ThermalStorageIceDetailed_Impl::optionalChargingCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::ThermalStorage_Ice_DetailedFields::ChargingCurveName);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
