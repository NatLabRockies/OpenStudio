/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERCOLDEST_HPP
#define EPMODEL_SETPOINTMANAGERCOLDEST_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerColdest_Impl;
  }

  /** \brief Selects a supply-air setpoint based on the coldest zone.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagercoldest,SetpointManager:Coldest}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerColdest</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerColdest : public SetpointManager
  {
   public:
    explicit SetpointManagerColdest(const Model& model);

    virtual ~SetpointManagerColdest() override = default;
    SetpointManagerColdest(const SetpointManagerColdest& other) = default;
    SetpointManagerColdest(SetpointManagerColdest&& other) = default;
    SetpointManagerColdest& operator=(const SetpointManagerColdest&) = default;
    SetpointManagerColdest& operator=(SetpointManagerColdest&&) = default;

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
    using ImplType = detail::SetpointManagerColdest_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerColdest(std::shared_ptr<detail::SetpointManagerColdest_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
