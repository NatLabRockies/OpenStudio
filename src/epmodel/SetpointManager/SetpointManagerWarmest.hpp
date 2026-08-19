/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERWARMEST_HPP
#define EPMODEL_SETPOINTMANAGERWARMEST_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerWarmest_Impl;
  }

  /** \brief Selects a supply-air setpoint based on the warmest zone.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagerwarmest,SetpointManager:Warmest}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerWarmest</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerWarmest : public SetpointManager
  {
   public:
    explicit SetpointManagerWarmest(const Model& model);

    virtual ~SetpointManagerWarmest() override = default;
    SetpointManagerWarmest(const SetpointManagerWarmest& other) = default;
    SetpointManagerWarmest(SetpointManagerWarmest&& other) = default;
    SetpointManagerWarmest& operator=(const SetpointManagerWarmest&) = default;
    SetpointManagerWarmest& operator=(SetpointManagerWarmest&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();
    static std::vector<std::string> strategyValues();

    double minimumSetpointTemperature() const;
    bool setMinimumSetpointTemperature(double minimumSetpointTemperature);

    double maximumSetpointTemperature() const;
    bool setMaximumSetpointTemperature(double maximumSetpointTemperature);

    std::string strategy() const;
    bool setStrategy(const std::string& strategy);

   protected:
    using ImplType = detail::SetpointManagerWarmest_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerWarmest(std::shared_ptr<detail::SetpointManagerWarmest_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
