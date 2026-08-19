/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERWARMESTTEMPERATUREFLOW_HPP
#define EPMODEL_SETPOINTMANAGERWARMESTTEMPERATUREFLOW_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerWarmestTemperatureFlow_Impl;
  }

  /** \brief Selects a supply-air setpoint based on the warmest zone and available flow.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagerwarmesttemperatureflow,SetpointManager:WarmestTemperatureFlow}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SetpointManagerWarmestTemperatureFlow</code>.
   *
   * - <b>Not yet available:</b> <code>setSetpointNode(...)</code> and
   *   <code>resetSetpointNode()</code>. Use <code>addToNode(...)</code> to
   *   attach the manager instead.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerWarmestTemperatureFlow : public SetpointManager
  {
   public:
    explicit SetpointManagerWarmestTemperatureFlow(const Model& model);

    virtual ~SetpointManagerWarmestTemperatureFlow() override = default;
    SetpointManagerWarmestTemperatureFlow(const SetpointManagerWarmestTemperatureFlow& other) = default;
    SetpointManagerWarmestTemperatureFlow(SetpointManagerWarmestTemperatureFlow&& other) = default;
    SetpointManagerWarmestTemperatureFlow& operator=(const SetpointManagerWarmestTemperatureFlow&) = default;
    SetpointManagerWarmestTemperatureFlow& operator=(SetpointManagerWarmestTemperatureFlow&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();
    static std::vector<std::string> strategyValues();

    double minimumSetpointTemperature() const;
    bool setMinimumSetpointTemperature(double minimumSetpointTemperature);

    double maximumSetpointTemperature() const;
    bool setMaximumSetpointTemperature(double maximumSetpointTemperature);

    std::string strategy() const;
    bool setStrategy(const std::string& strategy);

    double minimumTurndownRatio() const;
    bool setMinimumTurndownRatio(double minimumTurndownRatio);

   protected:
    using ImplType = detail::SetpointManagerWarmestTemperatureFlow_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerWarmestTemperatureFlow(std::shared_ptr<detail::SetpointManagerWarmestTemperatureFlow_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
