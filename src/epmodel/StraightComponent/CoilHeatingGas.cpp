/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingGas.hpp"
#include "StraightComponent/CoilHeatingGas_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  CoilHeatingGas::CoilHeatingGas(const Model& model) : StraightComponent(CoilHeatingGas::iddObjectType(), model) {
    auto impl = getImpl<detail::CoilHeatingGas_Impl>();
    OS_ASSERT(impl);

    // Preserve model counterpart defaults for required scalar fields.
    bool ok = true;
    ok = setGasBurnerEfficiency(0.8);
    OS_ASSERT(ok);
    ok = setString(openstudio::Coil_Heating_FuelFields::NominalCapacity, "AutoSize");
    OS_ASSERT(ok);
    ok = setOnCycleParasiticElectricLoad(0.0);
    OS_ASSERT(ok);
    ok = setOffCycleParasiticGasLoad(0.0);
    OS_ASSERT(ok);
    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    ok = setAvailabilitySchedule(alwaysOn);
    OS_ASSERT(ok);

    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  CoilHeatingGas::CoilHeatingGas(std::shared_ptr<detail::CoilHeatingGas_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingGas::iddObjectType() {
    return IddObjectType::Coil_Heating_Fuel;
  }

  bool CoilHeatingGas::addToNode(Node& node) {
    return getImpl<detail::CoilHeatingGas_Impl>()->addToNode(node);
  }

  Schedule CoilHeatingGas::availabilitySchedule() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->availabilitySchedule();
  }

  bool CoilHeatingGas::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<Curve> CoilHeatingGas::partLoadFractionCorrelationCurve() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->partLoadFractionCorrelationCurve();
  }

  bool CoilHeatingGas::setPartLoadFractionCorrelationCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setPartLoadFractionCorrelationCurve(curve);
  }

  void CoilHeatingGas::resetPartLoadFractionCorrelationCurve() {
    getImpl<detail::CoilHeatingGas_Impl>()->resetPartLoadFractionCorrelationCurve();
  }

  std::vector<std::string> CoilHeatingGas::validFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Heating_FuelFields::FuelType);
  }

  std::string CoilHeatingGas::fuelType() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->fuelType();
  }

  bool CoilHeatingGas::setFuelType(const std::string& fuelType) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setFuelType(fuelType);
  }

  void CoilHeatingGas::resetFuelType() {
    getImpl<detail::CoilHeatingGas_Impl>()->resetFuelType();
  }

  double CoilHeatingGas::gasBurnerEfficiency() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->gasBurnerEfficiency();
  }

  bool CoilHeatingGas::setGasBurnerEfficiency(double value) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setGasBurnerEfficiency(value);
  }

  double CoilHeatingGas::parasiticElectricLoad() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->parasiticElectricLoad();
  }

  bool CoilHeatingGas::setParasiticElectricLoad(double value) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setParasiticElectricLoad(value);
  }

  double CoilHeatingGas::onCycleParasiticElectricLoad() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->onCycleParasiticElectricLoad();
  }

  bool CoilHeatingGas::setOnCycleParasiticElectricLoad(double value) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setOnCycleParasiticElectricLoad(value);
  }

  double CoilHeatingGas::parasiticGasLoad() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->parasiticGasLoad();
  }

  bool CoilHeatingGas::setParasiticGasLoad(double value) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setParasiticGasLoad(value);
  }

  double CoilHeatingGas::offCycleParasiticGasLoad() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->offCycleParasiticGasLoad();
  }

  bool CoilHeatingGas::setOffCycleParasiticGasLoad(double value) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setOffCycleParasiticGasLoad(value);
  }

  boost::optional<double> CoilHeatingGas::nominalCapacity() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->nominalCapacity();
  }

  boost::optional<double> CoilHeatingGas::autosizedNominalCapacity() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->autosizedNominalCapacity();
  }

  bool CoilHeatingGas::isNominalCapacityAutosized() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->isNominalCapacityAutosized();
  }

  bool CoilHeatingGas::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setNominalCapacity(nominalCapacity);
  }

  void CoilHeatingGas::resetNominalCapacity() {
    getImpl<detail::CoilHeatingGas_Impl>()->resetNominalCapacity();
  }

  void CoilHeatingGas::autosizeNominalCapacity() {
    getImpl<detail::CoilHeatingGas_Impl>()->autosizeNominalCapacity();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned CoilHeatingGas_Impl::inletPort() const {
      return openstudio::Coil_Heating_FuelFields::AirInletNodeName;
    }

    unsigned CoilHeatingGas_Impl::outletPort() const {
      return openstudio::Coil_Heating_FuelFields::AirOutletNodeName;
    }

    std::vector<ModelObject> CoilHeatingGas_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto partLoadCurve = partLoadFractionCorrelationCurve()) {
        result.push_back(*partLoadCurve);
      }
      return result;
    }

    bool CoilHeatingGas_Impl::addToNode(Node& node) {
      if (node.airLoopHVACOutdoorAirSystem()) {
        return StraightComponent_Impl::addToNode(node);
      }

      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
    }

    Schedule CoilHeatingGas_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Heating_FuelFields::AvailabilityScheduleName);
      if (!value) {
        value = this->model().alwaysOnDiscreteSchedule();
        OS_ASSERT(value);
        const_cast<CoilHeatingGas_Impl*>(this)->setAvailabilitySchedule(*value);
        value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Heating_FuelFields::AvailabilityScheduleName);
      }
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingGas_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Heating_FuelFields::AvailabilityScheduleName, schedule.handle(), false);
    }

    boost::optional<Curve> CoilHeatingGas_Impl::partLoadFractionCorrelationCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::Coil_Heating_FuelFields::PartLoadFractionCorrelationCurveName);
    }

    bool CoilHeatingGas_Impl::setPartLoadFractionCorrelationCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_FuelFields::PartLoadFractionCorrelationCurveName, curve.handle(), false);
    }

    void CoilHeatingGas_Impl::resetPartLoadFractionCorrelationCurve() {
      OS_ASSERT(setPointer(openstudio::Coil_Heating_FuelFields::PartLoadFractionCorrelationCurveName, openstudio::Handle(), false));
    }

    std::string CoilHeatingGas_Impl::fuelType() const {
      const auto value = getString(openstudio::Coil_Heating_FuelFields::FuelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingGas_Impl::setFuelType(const std::string& fuelType) {
      return setString(openstudio::Coil_Heating_FuelFields::FuelType, fuelType);
    }

    void CoilHeatingGas_Impl::resetFuelType() {
      const bool result = setString(openstudio::Coil_Heating_FuelFields::FuelType, "");
      OS_ASSERT(result);
    }

    double CoilHeatingGas_Impl::gasBurnerEfficiency() const {
      const auto value = getDouble(openstudio::Coil_Heating_FuelFields::BurnerEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingGas_Impl::setGasBurnerEfficiency(double value) {
      return setDouble(openstudio::Coil_Heating_FuelFields::BurnerEfficiency, value);
    }

    double CoilHeatingGas_Impl::parasiticElectricLoad() const {
      return onCycleParasiticElectricLoad();
    }

    bool CoilHeatingGas_Impl::setParasiticElectricLoad(double value) {
      return setOnCycleParasiticElectricLoad(value);
    }

    double CoilHeatingGas_Impl::onCycleParasiticElectricLoad() const {
      const auto value = getDouble(openstudio::Coil_Heating_FuelFields::OnCycleParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingGas_Impl::setOnCycleParasiticElectricLoad(double value) {
      return setDouble(openstudio::Coil_Heating_FuelFields::OnCycleParasiticElectricLoad, value);
    }

    double CoilHeatingGas_Impl::parasiticGasLoad() const {
      return offCycleParasiticGasLoad();
    }

    bool CoilHeatingGas_Impl::setParasiticGasLoad(double value) {
      return setOffCycleParasiticGasLoad(value);
    }

    double CoilHeatingGas_Impl::offCycleParasiticGasLoad() const {
      const auto value = getDouble(openstudio::Coil_Heating_FuelFields::OffCycleParasiticFuelLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingGas_Impl::setOffCycleParasiticGasLoad(double value) {
      return setDouble(openstudio::Coil_Heating_FuelFields::OffCycleParasiticFuelLoad, value);
    }

    boost::optional<double> CoilHeatingGas_Impl::nominalCapacity() const {
      return getDouble(openstudio::Coil_Heating_FuelFields::NominalCapacity, true);
    }

    boost::optional<double> CoilHeatingGas_Impl::autosizedNominalCapacity() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    bool CoilHeatingGas_Impl::isNominalCapacityAutosized() const {
      if (const auto value = getString(openstudio::Coil_Heating_FuelFields::NominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilHeatingGas_Impl::setNominalCapacity(double nominalCapacity) {
      return setDouble(openstudio::Coil_Heating_FuelFields::NominalCapacity, nominalCapacity);
    }

    void CoilHeatingGas_Impl::resetNominalCapacity() {
      const bool result = setString(openstudio::Coil_Heating_FuelFields::NominalCapacity, "");
      OS_ASSERT(result);
    }

    void CoilHeatingGas_Impl::autosizeNominalCapacity() {
      const bool result = setString(openstudio::Coil_Heating_FuelFields::NominalCapacity, "Autosize");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
