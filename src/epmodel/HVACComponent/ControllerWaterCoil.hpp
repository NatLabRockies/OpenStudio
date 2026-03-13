/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONTROLLERWATERCOIL_HPP
#define EPMODEL_CONTROLLERWATERCOIL_HPP

#include "EPModelAPI.hpp"
#include "HVACComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ControllerWaterCoil_Impl;
  }

  class EPMODEL_API ControllerWaterCoil : public HVACComponent
  {
   public:
    explicit ControllerWaterCoil(const Model& model);

    virtual ~ControllerWaterCoil() override = default;
    ControllerWaterCoil(const ControllerWaterCoil& other) = default;
    ControllerWaterCoil(ControllerWaterCoil&& other) = default;
    ControllerWaterCoil& operator=(const ControllerWaterCoil&) = default;
    ControllerWaterCoil& operator=(ControllerWaterCoil&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validControlVariableValues();
    static std::vector<std::string> validActionValues();
    static std::vector<std::string> validActuatorVariableValues();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model::ControllerWaterCoil scalar accessor names/signatures.
    // - Field Mapping: controlVariable/action/actuatorVariable and actuated-flow tolerances map directly to
    //   EnergyPlus Controller:WaterCoil scalar fields.
    // - ForwardTranslator evidence: ForwardTranslateControllerWaterCoil.cpp writes these scalar fields directly.
    // - Field Mapping: Relationship fields (Water Coil Name, Sensor Node Name, Actuator Node Name) are intentionally
    //   excluded from this scalar scaffold pass.
    // - TODO(parity): Add non-scalar relationship APIs incrementally without changing scalar signatures.

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

    boost::optional<double> controllerConvergenceTolerance() const;
    bool isControllerConvergenceToleranceDefaulted() const;
    bool isControllerConvergenceToleranceAutosized() const;
    boost::optional<double> autosizedControllerConvergenceTolerance() const;
    bool setControllerConvergenceTolerance(double controllerConvergenceTolerance);
    void resetControllerConvergenceTolerance();
    void autosizeControllerConvergenceTolerance();

    boost::optional<double> maximumActuatedFlow() const;
    bool isMaximumActuatedFlowAutosized() const;
    boost::optional<double> autosizedMaximumActuatedFlow() const;
    bool setMaximumActuatedFlow(double maximumActuatedFlow);
    void resetMaximumActuatedFlow();
    void autosizeMaximumActuatedFlow();

    double minimumActuatedFlow() const;
    bool isMinimumActuatedFlowDefaulted() const;
    bool setMinimumActuatedFlow(double minimumActuatedFlow);
    void resetMinimumActuatedFlow();

   protected:
    using ImplType = detail::ControllerWaterCoil_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ControllerWaterCoil(std::shared_ptr<detail::ControllerWaterCoil_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
