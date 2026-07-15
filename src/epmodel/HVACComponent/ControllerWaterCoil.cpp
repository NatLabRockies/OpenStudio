/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACComponent/ControllerWaterCoil.hpp"
#include "HVACComponent/ControllerWaterCoil_Impl.hpp"

#include "Model.hpp"
#include "StraightComponent/Node.hpp"
#include "WaterToAirComponent/CoilCoolingWater.hpp"
#include "WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "WaterToAirComponent/CoilHeatingWater.hpp"
#include "WaterToAirComponent/CoilHeatingWater_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Controller_WaterCoil_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  namespace {

    template <typename CoilType>
    boost::optional<HVACComponent> inferWaterCoilByNodes(const detail::ControllerWaterCoil_Impl& controllerImpl) {
      const auto actuatorNode = controllerImpl.actuatorNode();
      const auto sensorNode = controllerImpl.sensorNode();
      if (!actuatorNode || !sensorNode) {
        return boost::none;
      }

      for (const auto& coil : controllerImpl.model().getConcreteModelObjects<CoilType>()) {
        const auto waterInlet = coil.waterInletModelObject();
        const auto airOutlet = coil.airOutletModelObject();
        if (waterInlet && airOutlet && waterInlet->handle() == actuatorNode->handle() && airOutlet->handle() == sensorNode->handle()) {
          return coil.template cast<HVACComponent>();
        }
      }

      return boost::none;
    }

  }  // namespace

  ControllerWaterCoil::ControllerWaterCoil(const Model& model) : HVACComponent(ControllerWaterCoil::iddObjectType(), model) {
    OS_ASSERT(setControlVariable("Temperature"));
    OS_ASSERT(setActuatorVariable("Flow"));
    resetMinimumActuatedFlow();
  }

  ControllerWaterCoil::ControllerWaterCoil(std::shared_ptr<detail::ControllerWaterCoil_Impl> impl) : HVACComponent(std::move(impl)) {}

  IddObjectType ControllerWaterCoil::iddObjectType() {
    return IddObjectType::Controller_WaterCoil;
  }

  std::vector<std::string> ControllerWaterCoil::validControlVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Controller_WaterCoilFields::ControlVariable);
  }

  std::vector<std::string> ControllerWaterCoil::validActionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Controller_WaterCoilFields::Action);
  }

  std::vector<std::string> ControllerWaterCoil::validActuatorVariableValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Controller_WaterCoilFields::ActuatorVariable);
  }

  boost::optional<HVACComponent> ControllerWaterCoil::waterCoil() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->waterCoil();
  }

  boost::optional<std::string> ControllerWaterCoil::controlVariable() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->controlVariable();
  }

  bool ControllerWaterCoil::isControlVariableDefaulted() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->isControlVariableDefaulted();
  }

  bool ControllerWaterCoil::setControlVariable(const std::string& controlVariable) {
    return getImpl<detail::ControllerWaterCoil_Impl>()->setControlVariable(controlVariable);
  }

  void ControllerWaterCoil::resetControlVariable() {
    getImpl<detail::ControllerWaterCoil_Impl>()->resetControlVariable();
  }

  boost::optional<std::string> ControllerWaterCoil::action() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->action();
  }

  bool ControllerWaterCoil::setAction(const std::string& action) {
    return getImpl<detail::ControllerWaterCoil_Impl>()->setAction(action);
  }

  void ControllerWaterCoil::resetAction() {
    getImpl<detail::ControllerWaterCoil_Impl>()->resetAction();
  }

  boost::optional<std::string> ControllerWaterCoil::actuatorVariable() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->actuatorVariable();
  }

  bool ControllerWaterCoil::isActuatorVariableDefaulted() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->isActuatorVariableDefaulted();
  }

  bool ControllerWaterCoil::setActuatorVariable(const std::string& actuatorVariable) {
    return getImpl<detail::ControllerWaterCoil_Impl>()->setActuatorVariable(actuatorVariable);
  }

  void ControllerWaterCoil::resetActuatorVariable() {
    getImpl<detail::ControllerWaterCoil_Impl>()->resetActuatorVariable();
  }

  boost::optional<Node> ControllerWaterCoil::sensorNode() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->sensorNode();
  }

  bool ControllerWaterCoil::setSensorNode(const Node& sensorNode) {
    return getImpl<detail::ControllerWaterCoil_Impl>()->setSensorNode(sensorNode);
  }

  boost::optional<Node> ControllerWaterCoil::actuatorNode() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->actuatorNode();
  }

  bool ControllerWaterCoil::setActuatorNode(const Node& actuatorNode) {
    return getImpl<detail::ControllerWaterCoil_Impl>()->setActuatorNode(actuatorNode);
  }

  boost::optional<double> ControllerWaterCoil::controllerConvergenceTolerance() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->controllerConvergenceTolerance();
  }

  bool ControllerWaterCoil::isControllerConvergenceToleranceDefaulted() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->isControllerConvergenceToleranceDefaulted();
  }

  bool ControllerWaterCoil::isControllerConvergenceToleranceAutosized() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->isControllerConvergenceToleranceAutosized();
  }

  bool ControllerWaterCoil::setControllerConvergenceTolerance(double controllerConvergenceTolerance) {
    return getImpl<detail::ControllerWaterCoil_Impl>()->setControllerConvergenceTolerance(controllerConvergenceTolerance);
  }

  void ControllerWaterCoil::resetControllerConvergenceTolerance() {
    getImpl<detail::ControllerWaterCoil_Impl>()->resetControllerConvergenceTolerance();
  }

  void ControllerWaterCoil::autosizeControllerConvergenceTolerance() {
    getImpl<detail::ControllerWaterCoil_Impl>()->autosizeControllerConvergenceTolerance();
  }

  boost::optional<double> ControllerWaterCoil::autosizedControllerConvergenceTolerance() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->autosizedControllerConvergenceTolerance();
  }

  boost::optional<double> ControllerWaterCoil::maximumActuatedFlow() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->maximumActuatedFlow();
  }

  bool ControllerWaterCoil::isMaximumActuatedFlowAutosized() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->isMaximumActuatedFlowAutosized();
  }

  bool ControllerWaterCoil::setMaximumActuatedFlow(double maximumActuatedFlow) {
    return getImpl<detail::ControllerWaterCoil_Impl>()->setMaximumActuatedFlow(maximumActuatedFlow);
  }

  void ControllerWaterCoil::resetMaximumActuatedFlow() {
    getImpl<detail::ControllerWaterCoil_Impl>()->resetMaximumActuatedFlow();
  }

  void ControllerWaterCoil::autosizeMaximumActuatedFlow() {
    getImpl<detail::ControllerWaterCoil_Impl>()->autosizeMaximumActuatedFlow();
  }

  boost::optional<double> ControllerWaterCoil::autosizedMaximumActuatedFlow() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->autosizedMaximumActuatedFlow();
  }

  double ControllerWaterCoil::minimumActuatedFlow() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->minimumActuatedFlow();
  }

  bool ControllerWaterCoil::isMinimumActuatedFlowDefaulted() const {
    return getImpl<detail::ControllerWaterCoil_Impl>()->isMinimumActuatedFlowDefaulted();
  }

  bool ControllerWaterCoil::setMinimumActuatedFlow(double minimumActuatedFlow) {
    return getImpl<detail::ControllerWaterCoil_Impl>()->setMinimumActuatedFlow(minimumActuatedFlow);
  }

  void ControllerWaterCoil::resetMinimumActuatedFlow() {
    getImpl<detail::ControllerWaterCoil_Impl>()->resetMinimumActuatedFlow();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<HVACComponent> ControllerWaterCoil_Impl::waterCoil() const {
      if (auto coolingCoil = inferWaterCoilByNodes<CoilCoolingWater>(*this)) {
        return coolingCoil;
      }
      return inferWaterCoilByNodes<CoilHeatingWater>(*this);
    }

    void ControllerWaterCoil_Impl::doCanonicalize(LoadContext& context) {
      HVACComponent_Impl::doCanonicalize(context);

      if (isEmpty(openstudio::Controller_WaterCoilFields::ControlVariable)) {
        OS_ASSERT(setControlVariable("Temperature"));
      }
      if (isEmpty(openstudio::Controller_WaterCoilFields::ActuatorVariable)) {
        OS_ASSERT(setActuatorVariable("Flow"));
      }
    }

    boost::optional<std::string> ControllerWaterCoil_Impl::controlVariable() const {
      return getString(openstudio::Controller_WaterCoilFields::ControlVariable, true);
    }

    bool ControllerWaterCoil_Impl::isControlVariableDefaulted() const {
      return isEmpty(openstudio::Controller_WaterCoilFields::ControlVariable);
    }

    bool ControllerWaterCoil_Impl::setControlVariable(const std::string& controlVariable) {
      return setString(openstudio::Controller_WaterCoilFields::ControlVariable, controlVariable);
    }

    void ControllerWaterCoil_Impl::resetControlVariable() {
      const bool result = setString(openstudio::Controller_WaterCoilFields::ControlVariable, "");
      OS_ASSERT(result);
    }

    boost::optional<std::string> ControllerWaterCoil_Impl::action() const {
      return getString(openstudio::Controller_WaterCoilFields::Action, true);
    }

    bool ControllerWaterCoil_Impl::setAction(const std::string& action) {
      return setString(openstudio::Controller_WaterCoilFields::Action, action);
    }

    void ControllerWaterCoil_Impl::resetAction() {
      const bool result = setString(openstudio::Controller_WaterCoilFields::Action, "");
      OS_ASSERT(result);
    }

    boost::optional<std::string> ControllerWaterCoil_Impl::actuatorVariable() const {
      return getString(openstudio::Controller_WaterCoilFields::ActuatorVariable, true);
    }

    bool ControllerWaterCoil_Impl::isActuatorVariableDefaulted() const {
      return isEmpty(openstudio::Controller_WaterCoilFields::ActuatorVariable);
    }

    bool ControllerWaterCoil_Impl::setActuatorVariable(const std::string& actuatorVariable) {
      return setString(openstudio::Controller_WaterCoilFields::ActuatorVariable, actuatorVariable);
    }

    void ControllerWaterCoil_Impl::resetActuatorVariable() {
      const bool result = setString(openstudio::Controller_WaterCoilFields::ActuatorVariable, "");
      OS_ASSERT(result);
    }

    boost::optional<Node> ControllerWaterCoil_Impl::sensorNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(openstudio::Controller_WaterCoilFields::SensorNodeName);
    }

    bool ControllerWaterCoil_Impl::setSensorNode(const Node& sensorNode) {
      return setPointer(openstudio::Controller_WaterCoilFields::SensorNodeName, sensorNode.handle());
    }

    boost::optional<Node> ControllerWaterCoil_Impl::actuatorNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(openstudio::Controller_WaterCoilFields::ActuatorNodeName);
    }

    bool ControllerWaterCoil_Impl::setActuatorNode(const Node& actuatorNode) {
      return setPointer(openstudio::Controller_WaterCoilFields::ActuatorNodeName, actuatorNode.handle());
    }

    boost::optional<double> ControllerWaterCoil_Impl::controllerConvergenceTolerance() const {
      return getDouble(openstudio::Controller_WaterCoilFields::ControllerConvergenceTolerance, true);
    }

    bool ControllerWaterCoil_Impl::isControllerConvergenceToleranceDefaulted() const {
      return isEmpty(openstudio::Controller_WaterCoilFields::ControllerConvergenceTolerance);
    }

    bool ControllerWaterCoil_Impl::isControllerConvergenceToleranceAutosized() const {
      if (const auto value = getString(openstudio::Controller_WaterCoilFields::ControllerConvergenceTolerance, true)) {
        return openstudio::istringEqual(*value, "Autosize");
      }
      return false;
    }

    bool ControllerWaterCoil_Impl::setControllerConvergenceTolerance(double controllerConvergenceTolerance) {
      const bool result = setDouble(openstudio::Controller_WaterCoilFields::ControllerConvergenceTolerance, controllerConvergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    void ControllerWaterCoil_Impl::resetControllerConvergenceTolerance() {
      const bool result = setString(openstudio::Controller_WaterCoilFields::ControllerConvergenceTolerance, "");
      OS_ASSERT(result);
    }

    void ControllerWaterCoil_Impl::autosizeControllerConvergenceTolerance() {
      const bool result = setString(openstudio::Controller_WaterCoilFields::ControllerConvergenceTolerance, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ControllerWaterCoil_Impl::autosizedControllerConvergenceTolerance() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ControllerWaterCoil_Impl::maximumActuatedFlow() const {
      return getDouble(openstudio::Controller_WaterCoilFields::MaximumActuatedFlow, true);
    }

    bool ControllerWaterCoil_Impl::isMaximumActuatedFlowAutosized() const {
      if (const auto value = getString(openstudio::Controller_WaterCoilFields::MaximumActuatedFlow, true)) {
        return openstudio::istringEqual(*value, "Autosize");
      }
      return false;
    }

    bool ControllerWaterCoil_Impl::setMaximumActuatedFlow(double maximumActuatedFlow) {
      return setDouble(openstudio::Controller_WaterCoilFields::MaximumActuatedFlow, maximumActuatedFlow);
    }

    void ControllerWaterCoil_Impl::resetMaximumActuatedFlow() {
      const bool result = setString(openstudio::Controller_WaterCoilFields::MaximumActuatedFlow, "");
      OS_ASSERT(result);
    }

    void ControllerWaterCoil_Impl::autosizeMaximumActuatedFlow() {
      const bool result = setString(openstudio::Controller_WaterCoilFields::MaximumActuatedFlow, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ControllerWaterCoil_Impl::autosizedMaximumActuatedFlow() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    double ControllerWaterCoil_Impl::minimumActuatedFlow() const {
      const auto value = getDouble(openstudio::Controller_WaterCoilFields::MinimumActuatedFlow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ControllerWaterCoil_Impl::isMinimumActuatedFlowDefaulted() const {
      return isEmpty(openstudio::Controller_WaterCoilFields::MinimumActuatedFlow);
    }

    bool ControllerWaterCoil_Impl::setMinimumActuatedFlow(double minimumActuatedFlow) {
      return setDouble(openstudio::Controller_WaterCoilFields::MinimumActuatedFlow, minimumActuatedFlow);
    }

    void ControllerWaterCoil_Impl::resetMinimumActuatedFlow() {
      const bool result = setString(openstudio::Controller_WaterCoilFields::MinimumActuatedFlow, "");
      OS_ASSERT(result);
    }

    std::vector<std::string> ControllerWaterCoil_Impl::validControlVariableValues() const {
      return openstudio::epmodel::ControllerWaterCoil::validControlVariableValues();
    }

    std::vector<std::string> ControllerWaterCoil_Impl::validActionValues() const {
      return openstudio::epmodel::ControllerWaterCoil::validActionValues();
    }

    std::vector<std::string> ControllerWaterCoil_Impl::validActuatorVariableValues() const {
      return openstudio::epmodel::ControllerWaterCoil::validActuatorVariableValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
