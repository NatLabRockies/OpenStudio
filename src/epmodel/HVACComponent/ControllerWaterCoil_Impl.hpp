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

namespace detail {

class EPMODEL_API ControllerWaterCoil_Impl : public HVACComponent_Impl
{
 public:
  using HVACComponent_Impl::HVACComponent_Impl;
  virtual ~ControllerWaterCoil_Impl() override = default;

  boost::optional<std::string> controlVariable() const;
  bool isControlVariableDefaulted() const;

  boost::optional<std::string> action() const;

  boost::optional<std::string> actuatorVariable() const;
  bool isActuatorVariableDefaulted() const;

  boost::optional<double> controllerConvergenceTolerance() const;
  bool isControllerConvergenceToleranceDefaulted() const;
  bool isControllerConvergenceToleranceAutosized() const;

  boost::optional<double> maximumActuatedFlow() const;
  bool isMaximumActuatedFlowAutosized() const;

  double minimumActuatedFlow() const;
  bool isMinimumActuatedFlowDefaulted() const;

  bool setControlVariable(const std::string& controlVariable);
  void resetControlVariable();

  bool setAction(const std::string& action);
  void resetAction();

  bool setActuatorVariable(const std::string& actuatorVariable);
  void resetActuatorVariable();

  bool setControllerConvergenceTolerance(double controllerConvergenceTolerance);
  void resetControllerConvergenceTolerance();
  void autosizeControllerConvergenceTolerance();

  bool setMaximumActuatedFlow(double maximumActuatedFlow);
  void resetMaximumActuatedFlow();
  void autosizeMaximumActuatedFlow();

  bool setMinimumActuatedFlow(double minimumActuatedFlow);
  void resetMinimumActuatedFlow();

  boost::optional<double> autosizedControllerConvergenceTolerance() const;
  boost::optional<double> autosizedMaximumActuatedFlow() const;

  std::vector<std::string> validControlVariableValues() const;
  std::vector<std::string> validActionValues() const;
  std::vector<std::string> validActuatorVariableValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
