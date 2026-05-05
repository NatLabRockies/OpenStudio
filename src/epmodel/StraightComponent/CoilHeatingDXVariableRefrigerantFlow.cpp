/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingDXVariableRefrigerantFlow.hpp"
#include "StraightComponent/CoilHeatingDXVariableRefrigerantFlow_Impl.hpp"

#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveBiquadratic_Impl.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Curve/CurveQuadratic_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_DX_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    void applyConstructorDefaults(CoilHeatingDXVariableRefrigerantFlow& coil) {
      const auto& model = coil.model();

      auto alwaysOn = model.alwaysOnDiscreteSchedule();
      OS_ASSERT(coil.setAvailabilitySchedule(alwaysOn));

      coil.autosizeRatedTotalHeatingCapacity();
      coil.autosizeRatedAirFlowRate();

      CurveBiquadratic vrfTUHeatCAPFT(model);
      vrfTUHeatCAPFT.setName(coil.name().get() + " VRFTUHeatCAPFT");
      OS_ASSERT(vrfTUHeatCAPFT.setCoefficient1Constant(0.375443994956127));
      OS_ASSERT(vrfTUHeatCAPFT.setCoefficient2x(6.68190645147821E-02));
      OS_ASSERT(vrfTUHeatCAPFT.setCoefficient3xPOW2(-1.94171026482001E-03));
      OS_ASSERT(vrfTUHeatCAPFT.setCoefficient4y(4.42618420640187E-02));
      OS_ASSERT(vrfTUHeatCAPFT.setCoefficient5yPOW2(-0.0004009578));
      OS_ASSERT(vrfTUHeatCAPFT.setCoefficient6xTIMESY(-0.0014819801));
      OS_ASSERT(vrfTUHeatCAPFT.setMinimumValueofx(21.11));
      OS_ASSERT(vrfTUHeatCAPFT.setMaximumValueofx(27.22));
      OS_ASSERT(vrfTUHeatCAPFT.setMinimumValueofy(-15));
      OS_ASSERT(vrfTUHeatCAPFT.setMaximumValueofy(18.33));
      OS_ASSERT(vrfTUHeatCAPFT.setMinimumCurveOutput(0.6074));
      OS_ASSERT(vrfTUHeatCAPFT.setMaximumCurveOutput(1.0));
      OS_ASSERT(coil.setHeatingCapacityRatioModifierFunctionofTemperatureCurve(vrfTUHeatCAPFT));

      CurveQuadratic vrfACCoolCapFFF(model);
      vrfACCoolCapFFF.setName(coil.name().get() + " VRFACCoolCapFFF");
      OS_ASSERT(vrfACCoolCapFFF.setCoefficient1Constant(0.8));
      OS_ASSERT(vrfACCoolCapFFF.setCoefficient2x(0.2));
      OS_ASSERT(vrfACCoolCapFFF.setCoefficient3xPOW2(0.0));
      OS_ASSERT(vrfACCoolCapFFF.setMinimumValueofx(0.5));
      OS_ASSERT(vrfACCoolCapFFF.setMaximumValueofx(1.5));
      OS_ASSERT(coil.setHeatingCapacityModifierFunctionofFlowFractionCurve(vrfACCoolCapFFF));
    }

  }  // namespace

  CoilHeatingDXVariableRefrigerantFlow::CoilHeatingDXVariableRefrigerantFlow(const Model& model)
    : StraightComponent(CoilHeatingDXVariableRefrigerantFlow::iddObjectType(), model) {
    auto impl = getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>();
    OS_ASSERT(impl);
    applyConstructorDefaults(*this);
  }

  CoilHeatingDXVariableRefrigerantFlow::CoilHeatingDXVariableRefrigerantFlow(std::shared_ptr<detail::CoilHeatingDXVariableRefrigerantFlow_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingDXVariableRefrigerantFlow::iddObjectType() {
    return IddObjectType::Coil_Heating_DX_VariableRefrigerantFlow;
  }

  Schedule CoilHeatingDXVariableRefrigerantFlow::availabilitySchedule() const {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->availabilitySchedule();
  }

  bool CoilHeatingDXVariableRefrigerantFlow::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<double> CoilHeatingDXVariableRefrigerantFlow::ratedTotalHeatingCapacity() const {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->ratedTotalHeatingCapacity();
  }

  bool CoilHeatingDXVariableRefrigerantFlow::isRatedTotalHeatingCapacityAutosized() const {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->isRatedTotalHeatingCapacityAutosized();
  }

  bool CoilHeatingDXVariableRefrigerantFlow::setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity) {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->setRatedTotalHeatingCapacity(ratedTotalHeatingCapacity);
  }

  void CoilHeatingDXVariableRefrigerantFlow::autosizeRatedTotalHeatingCapacity() {
    getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->autosizeRatedTotalHeatingCapacity();
  }

  boost::optional<double> CoilHeatingDXVariableRefrigerantFlow::ratedAirFlowRate() const {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->ratedAirFlowRate();
  }

  bool CoilHeatingDXVariableRefrigerantFlow::isRatedAirFlowRateAutosized() const {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->isRatedAirFlowRateAutosized();
  }

  bool CoilHeatingDXVariableRefrigerantFlow::setRatedAirFlowRate(double ratedAirFlowRate) {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
  }

  void CoilHeatingDXVariableRefrigerantFlow::autosizeRatedAirFlowRate() {
    getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->autosizeRatedAirFlowRate();
  }

  Curve CoilHeatingDXVariableRefrigerantFlow::heatingCapacityRatioModifierFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->heatingCapacityRatioModifierFunctionofTemperatureCurve();
  }

  bool CoilHeatingDXVariableRefrigerantFlow::setHeatingCapacityRatioModifierFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->setHeatingCapacityRatioModifierFunctionofTemperatureCurve(curve);
  }

  Curve CoilHeatingDXVariableRefrigerantFlow::heatingCapacityModifierFunctionofFlowFractionCurve() const {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->heatingCapacityModifierFunctionofFlowFractionCurve();
  }

  bool CoilHeatingDXVariableRefrigerantFlow::setHeatingCapacityModifierFunctionofFlowFractionCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingDXVariableRefrigerantFlow_Impl>()->setHeatingCapacityModifierFunctionofFlowFractionCurve(curve);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned CoilHeatingDXVariableRefrigerantFlow_Impl::inletPort() const {
      return openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirInletNode;
    }

    unsigned CoilHeatingDXVariableRefrigerantFlow_Impl::outletPort() const {
      return openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::CoilAirOutletNode;
    }

    bool CoilHeatingDXVariableRefrigerantFlow_Impl::addToNode(Node& /*node*/) {
      // This coil has a fixed one-inlet/one-outlet air shape, so epmodel exposes
      // it as a StraightComponent. It is still intended to live inside compound
      // VRF topology, not to participate as standalone loop equipment.
      return false;
    }

    Schedule CoilHeatingDXVariableRefrigerantFlow_Impl::availabilitySchedule() const {
      auto schedule =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::AvailabilitySchedule);
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool CoilHeatingDXVariableRefrigerantFlow_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::AvailabilitySchedule, schedule.handle(), false);
    }

    boost::optional<double> CoilHeatingDXVariableRefrigerantFlow_Impl::ratedTotalHeatingCapacity() const {
      return getDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, true);
    }

    bool CoilHeatingDXVariableRefrigerantFlow_Impl::isRatedTotalHeatingCapacityAutosized() const {
      if (const auto value = getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilHeatingDXVariableRefrigerantFlow_Impl::setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity) {
      return setDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, ratedTotalHeatingCapacity);
    }

    void CoilHeatingDXVariableRefrigerantFlow_Impl::autosizeRatedTotalHeatingCapacity() {
      OS_ASSERT(setString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, "autosize"));
    }

    boost::optional<double> CoilHeatingDXVariableRefrigerantFlow_Impl::ratedAirFlowRate() const {
      return getDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, true);
    }

    bool CoilHeatingDXVariableRefrigerantFlow_Impl::isRatedAirFlowRateAutosized() const {
      if (const auto value = getString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilHeatingDXVariableRefrigerantFlow_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
      return setDouble(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, ratedAirFlowRate);
    }

    void CoilHeatingDXVariableRefrigerantFlow_Impl::autosizeRatedAirFlowRate() {
      OS_ASSERT(setString(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, "autosize"));
    }

    Curve CoilHeatingDXVariableRefrigerantFlow_Impl::heatingCapacityRatioModifierFunctionofTemperatureCurve() const {
      auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofTemperatureCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilHeatingDXVariableRefrigerantFlow_Impl::setHeatingCapacityRatioModifierFunctionofTemperatureCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofTemperatureCurveName,
                        curve.handle(), false);
    }

    Curve CoilHeatingDXVariableRefrigerantFlow_Impl::heatingCapacityModifierFunctionofFlowFractionCurve() const {
      auto curve = getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::HeatingCapacityModifierFunctionofFlowFractionCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool CoilHeatingDXVariableRefrigerantFlow_Impl::setHeatingCapacityModifierFunctionofFlowFractionCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_DX_VariableRefrigerantFlowFields::HeatingCapacityModifierFunctionofFlowFractionCurveName,
                        curve.handle(), false);
    }

    std::vector<ModelObject> CoilHeatingDXVariableRefrigerantFlow_Impl::children() const {
      std::vector<ModelObject> result;
      result.push_back(heatingCapacityRatioModifierFunctionofTemperatureCurve());
      result.push_back(heatingCapacityModifierFunctionofFlowFractionCurve());
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
