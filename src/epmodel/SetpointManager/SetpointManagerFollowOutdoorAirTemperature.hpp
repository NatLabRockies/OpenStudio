/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERFOLLOWOUTDOORAIRTEMPERATURE_HPP
#define EPMODEL_SETPOINTMANAGERFOLLOWOUTDOORAIRTEMPERATURE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SetpointManagerFollowOutdoorAirTemperature_Impl;
  }

  /** \brief Sets a setpoint by following outdoor-air temperature.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagerfollowoutdoorairtemperature,SetpointManager:FollowOutdoorAirTemperature}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerFollowOutdoorAirTemperature</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerFollowOutdoorAirTemperature : public SetpointManager
  {
   public:
    explicit SetpointManagerFollowOutdoorAirTemperature(const Model& model);

    virtual ~SetpointManagerFollowOutdoorAirTemperature() override = default;
    SetpointManagerFollowOutdoorAirTemperature(const SetpointManagerFollowOutdoorAirTemperature& other) = default;
    SetpointManagerFollowOutdoorAirTemperature(SetpointManagerFollowOutdoorAirTemperature&& other) = default;
    SetpointManagerFollowOutdoorAirTemperature& operator=(const SetpointManagerFollowOutdoorAirTemperature&) = default;
    SetpointManagerFollowOutdoorAirTemperature& operator=(SetpointManagerFollowOutdoorAirTemperature&&) = default;

    static IddObjectType iddObjectType();


    std::string referenceTemperatureType() const;
    bool setReferenceTemperatureType(const std::string& value);

    double offsetTemperatureDifference() const;
    bool setOffsetTemperatureDifference(double value);

    double maximumSetpointTemperature() const;
    bool setMaximumSetpointTemperature(double value);

    double minimumSetpointTemperature() const;
    bool setMinimumSetpointTemperature(double value);

   protected:
    using ImplType = detail::SetpointManagerFollowOutdoorAirTemperature_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerFollowOutdoorAirTemperature(std::shared_ptr<detail::SetpointManagerFollowOutdoorAirTemperature_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
