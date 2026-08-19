/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERFOLLOWSYSTEMNODETEMPERATURE_HPP
#define EPMODEL_SETPOINTMANAGERFOLLOWSYSTEMNODETEMPERATURE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class SetpointManagerFollowSystemNodeTemperature_Impl;
  }

  /** \brief Sets a setpoint by following the temperature at another system node.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagerfollowsystemnodetemperature,SetpointManager:FollowSystemNodeTemperature}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerFollowSystemNodeTemperature</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerFollowSystemNodeTemperature : public SetpointManager
  {
   public:
    explicit SetpointManagerFollowSystemNodeTemperature(const Model& model);

    virtual ~SetpointManagerFollowSystemNodeTemperature() override = default;
    SetpointManagerFollowSystemNodeTemperature(const SetpointManagerFollowSystemNodeTemperature& other) = default;
    SetpointManagerFollowSystemNodeTemperature(SetpointManagerFollowSystemNodeTemperature&& other) = default;
    SetpointManagerFollowSystemNodeTemperature& operator=(const SetpointManagerFollowSystemNodeTemperature&) = default;
    SetpointManagerFollowSystemNodeTemperature& operator=(SetpointManagerFollowSystemNodeTemperature&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();
    static std::vector<std::string> referenceTemperatureTypeValues();


    boost::optional<Node> referenceNode() const;
    bool setReferenceNode(const Node& node);
    void resetReferenceNode();

    std::string referenceTemperatureType() const;
    bool setReferenceTemperatureType(const std::string& referenceTemperatureType);

    double offsetTemperatureDifference() const;
    bool setOffsetTemperatureDifference(double offsetTemperatureDifference);

    double maximumLimitSetpointTemperature() const;
    bool setMaximumLimitSetpointTemperature(double maximumLimitSetpointTemperature);

    double minimumLimitSetpointTemperature() const;
    bool setMinimumLimitSetpointTemperature(double minimumLimitSetpointTemperature);

   protected:
    using ImplType = detail::SetpointManagerFollowSystemNodeTemperature_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerFollowSystemNodeTemperature(std::shared_ptr<detail::SetpointManagerFollowSystemNodeTemperature_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
