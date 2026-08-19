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
  class Node;

  namespace detail {
    class ControllerWaterCoil_Impl;
  }

  /** \brief Represents a controller that regulates a water coil.
   *
   * \par EnergyPlus object
   * \epobject{group-controllers.html#controllerwatercoil,Controller:WaterCoil}.
   *
   * \par Important behavior
   * <code>waterCoil()</code> is inferred from the controller's sensor and actuator
   * node relationships because the EnergyPlus object has no direct coil pointer.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ControllerWaterCoil</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * A water coil is returned only when the persisted node topology identifies one;
   * the relationship is not stored as an independent controller-to-coil link.
   */
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

    boost::optional<HVACComponent> waterCoil() const;

    // TODO: remove Defaulted + Reset + getter returns non optional : required in IDD AND canonicalized to a default value (+ ctor)
    boost::optional<std::string> controlVariable() const;
    bool isControlVariableDefaulted() const;
    bool setControlVariable(const std::string& controlVariable);
    void resetControlVariable();

    boost::optional<std::string> action() const;
    bool setAction(const std::string& action);
    void resetAction();

    // TODO: remove Defaulted + Reset + getter returns non optional : required in IDD AND canonicalized to a default value (+ ctor)
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
