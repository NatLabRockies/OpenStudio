/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERFOLLOWGROUNDTEMPERATURE_HPP
#define EPMODEL_SETPOINTMANAGERFOLLOWGROUNDTEMPERATURE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerFollowGroundTemperature_Impl;
  }

  /** \brief Sets a setpoint by following a selected ground-temperature source.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagerfollowgroundtemperature,SetpointManager:FollowGroundTemperature}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerFollowGroundTemperature</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerFollowGroundTemperature : public SetpointManager
  {
   public:
    explicit SetpointManagerFollowGroundTemperature(const Model& model);

    virtual ~SetpointManagerFollowGroundTemperature() override = default;
    SetpointManagerFollowGroundTemperature(const SetpointManagerFollowGroundTemperature& other) = default;
    SetpointManagerFollowGroundTemperature(SetpointManagerFollowGroundTemperature&& other) = default;
    SetpointManagerFollowGroundTemperature& operator=(const SetpointManagerFollowGroundTemperature&) = default;
    SetpointManagerFollowGroundTemperature& operator=(SetpointManagerFollowGroundTemperature&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();
    static std::vector<std::string> referenceGroundTemperatureObjectTypeValues();


    std::string referenceGroundTemperatureObjectType() const;
    bool setReferenceGroundTemperatureObjectType(const std::string& groundTemperatureObjType);

    double offsetTemperatureDifference() const;
    bool setOffsetTemperatureDifference(double offsetTemperatureDifference);

    double maximumSetpointTemperature() const;
    bool setMaximumSetpointTemperature(double maximumSetpointTemperature);

    double minimumSetpointTemperature() const;
    bool setMinimumSetpointTemperature(double minimumSetpointTemperature);

   protected:
    using ImplType = detail::SetpointManagerFollowGroundTemperature_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerFollowGroundTemperature(std::shared_ptr<detail::SetpointManagerFollowGroundTemperature_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
