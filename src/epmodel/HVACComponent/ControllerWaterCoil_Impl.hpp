/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONTROLLERWATERCOIL_IMPL_HPP
#define EPMODEL_CONTROLLERWATERCOIL_IMPL_HPP

#include "HVACComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class Node;
  class HVACComponent;

  namespace detail {

    class EPMODEL_API ControllerWaterCoil_Impl : public HVACComponent_Impl
    {
     public:
      using HVACComponent_Impl::HVACComponent_Impl;
      virtual ~ControllerWaterCoil_Impl() override = default;

      void doCanonicalize(LoadContext& context) override;

      boost::optional<HVACComponent> waterCoil() const;

      boost::optional<std::string> controlVariable() const;
      bool isControlVariableDefaulted() const;
      bool setControlVariable(const std::string& controlVariable);
      void resetControlVariable();

      boost::optional<std::string> action() const;
      bool setAction(const std::string& action);
      void resetAction();

      boost::optional<std::string> actuatorVariable() const;
      bool isActuatorVariableDefaulted() const;
      bool setActuatorVariable(const std::string& actuatorVariable);
      void resetActuatorVariable();

      boost::optional<Node> sensorNode() const;
      bool setSensorNode(const Node& sensorNode);

      boost::optional<Node> actuatorNode() const;
      bool setActuatorNode(const Node& actuatorNode);

      boost::optional<double> controllerConvergenceTolerance() const;
      bool isControllerConvergenceToleranceDefaulted() const;
      bool isControllerConvergenceToleranceAutosized() const;
      bool setControllerConvergenceTolerance(double controllerConvergenceTolerance);
      void resetControllerConvergenceTolerance();
      void autosizeControllerConvergenceTolerance();
      boost::optional<double> autosizedControllerConvergenceTolerance() const;

      boost::optional<double> maximumActuatedFlow() const;
      bool isMaximumActuatedFlowAutosized() const;
      bool setMaximumActuatedFlow(double maximumActuatedFlow);
      void resetMaximumActuatedFlow();
      void autosizeMaximumActuatedFlow();
      boost::optional<double> autosizedMaximumActuatedFlow() const;

      double minimumActuatedFlow() const;
      bool isMinimumActuatedFlowDefaulted() const;
      bool setMinimumActuatedFlow(double minimumActuatedFlow);
      void resetMinimumActuatedFlow();

      std::vector<std::string> validControlVariableValues() const;
      std::vector<std::string> validActionValues() const;
      std::vector<std::string> validActuatorVariableValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
