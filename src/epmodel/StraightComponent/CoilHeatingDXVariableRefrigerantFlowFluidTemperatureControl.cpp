/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl.hpp"
#include "StraightComponent/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Curve/CurveQuadratic_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    void applyConstructorDefaults(CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl& coil) {
      const auto& model = coil.model();

      auto alwaysOn = model.alwaysOnDiscreteSchedule();
      OS_ASSERT(coil.setAvailabilitySchedule(alwaysOn));
      coil.autosizeRatedTotalHeatingCapacity();
      OS_ASSERT(coil.setIndoorUnitReferenceSubcooling(5.0));

      CurveQuadratic indoorUnitCondensingTemperatureFunctionofSubcoolingCurve(model);
      indoorUnitCondensingTemperatureFunctionofSubcoolingCurve.setName("VRFIUCondTempCurve");
      OS_ASSERT(indoorUnitCondensingTemperatureFunctionofSubcoolingCurve.setCoefficient1Constant(-1.85));
      OS_ASSERT(indoorUnitCondensingTemperatureFunctionofSubcoolingCurve.setCoefficient2x(0.411));
      OS_ASSERT(indoorUnitCondensingTemperatureFunctionofSubcoolingCurve.setCoefficient3xPOW2(0.0196));
      OS_ASSERT(indoorUnitCondensingTemperatureFunctionofSubcoolingCurve.setMinimumValueofx(0));
      OS_ASSERT(indoorUnitCondensingTemperatureFunctionofSubcoolingCurve.setMaximumValueofx(20));
      OS_ASSERT(coil.setIndoorUnitCondensingTemperatureFunctionofSubcoolingCurve(indoorUnitCondensingTemperatureFunctionofSubcoolingCurve));
    }

  }  // namespace

  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl(const Model& model)
    : StraightComponent(CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>());
    applyConstructorDefaults(*this);
  }

  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl(
    std::shared_ptr<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::iddObjectType() {
    return IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl;
  }

  Schedule CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::availabilitySchedule() const {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->availabilitySchedule();
  }

  bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<double> CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::ratedTotalHeatingCapacity() const {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->ratedTotalHeatingCapacity();
  }

  bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::isRatedTotalHeatingCapacityAutosized() const {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->isRatedTotalHeatingCapacityAutosized();
  }

  bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity) {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setRatedTotalHeatingCapacity(
      ratedTotalHeatingCapacity);
  }

  void CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::autosizeRatedTotalHeatingCapacity() {
    getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->autosizeRatedTotalHeatingCapacity();
  }

  double CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::indoorUnitReferenceSubcooling() const {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->indoorUnitReferenceSubcooling();
  }

  Curve CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::indoorUnitCondensingTemperatureFunctionofSubcoolingCurve() const {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->indoorUnitCondensingTemperatureFunctionofSubcoolingCurve();
  }

  bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::setIndoorUnitReferenceSubcooling(double indoorUnitReferenceSubcooling) {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()->setIndoorUnitReferenceSubcooling(
      indoorUnitReferenceSubcooling);
  }

  bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::setIndoorUnitCondensingTemperatureFunctionofSubcoolingCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl>()
      ->setIndoorUnitCondensingTemperatureFunctionofSubcoolingCurve(curve);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    Schedule CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::AvailabilitySchedule);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::AvailabilitySchedule, schedule.handle(),
                        false);
    }

    unsigned CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::inletPort() const {
      return openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirInletNode;
    }

    unsigned CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::outletPort() const {
      return openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirOutletNode;
    }

    bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::addToNode(Node& /*node*/) {
      // This coil has a simple one-inlet/one-outlet air shape, so epmodel exposes
      // it as a StraightComponent. It is still intended to live inside VRF-owned
      // terminal topology, not to participate as standalone loop equipment.
      return false;
    }

    boost::optional<double> CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::ratedTotalHeatingCapacity() const {
      return getDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedTotalHeatingCapacity, true);
    }

    bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::isRatedTotalHeatingCapacityAutosized() const {
      if (const auto value =
            getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedTotalHeatingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity) {
      return setDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedTotalHeatingCapacity,
                       ratedTotalHeatingCapacity);
    }

    void CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::autosizeRatedTotalHeatingCapacity() {
      OS_ASSERT(setString(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedTotalHeatingCapacity, "autosize"));
    }

    double CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::indoorUnitReferenceSubcooling() const {
      const auto value =
        getDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::IndoorUnitReferenceSubcooling, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::setIndoorUnitReferenceSubcooling(double indoorUnitReferenceSubcooling) {
      return setDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::IndoorUnitReferenceSubcooling,
                       indoorUnitReferenceSubcooling);
    }

    Curve CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::indoorUnitCondensingTemperatureFunctionofSubcoolingCurve() const {
      auto value =
        getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::
                                                               IndoorUnitCondensingTemperatureFunctionofSubcoolingCurveName);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::setIndoorUnitCondensingTemperatureFunctionofSubcoolingCurve(
      const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::
                          IndoorUnitCondensingTemperatureFunctionofSubcoolingCurveName,
                        curve.handle(), false);
    }

    std::vector<ModelObject> CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_Impl::children() const {
      std::vector<ModelObject> result;
      result.push_back(indoorUnitCondensingTemperatureFunctionofSubcoolingCurve());
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
