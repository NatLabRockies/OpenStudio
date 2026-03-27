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
    // - Status: Partial Parity. Core scalar control fields and value sets are aligned, but the canonical water-coil and node-link surface is still incomplete.
    // - Canonical Counterpart: openstudio::model::ControllerWaterCoil.
    // - Implemented Parity: `validControlVariableValues`, `validActionValues`, `validActuatorVariableValues`, `controlVariable`, `action`, `actuatorVariable`, and the convergence/flow setters preserve the canonical scalar control contract.
    // - Documented Delta: Public accessors for the linked water coil, sensor node, and actuator node are not exposed yet, so the canonical relationship surface remains implementation-owned.
    // - Field/Storage Mapping: The epmodel wrapper maps its scalars directly to EnergyPlus `Controller:WaterCoil` fields; object links are held by the underlying EnergyPlus-backed topology rather than exposed as public accessors.
    // - Evidence: `src/model/ControllerWaterCoil.hpp`, `src/model/ControllerWaterCoil.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateControllerWaterCoil.cpp`, and `src/epmodel/test/ControllerWaterCoil_GTest.cpp`.
    // - Remaining Parity Work: Add the missing object-link accessors for the wrapped water coil and nodes once relationship parity is in scope.

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
