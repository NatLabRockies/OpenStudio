/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSYSTEMNODERESETTEMPERATURE_HPP
#define EPMODEL_SETPOINTMANAGERSYSTEMNODERESETTEMPERATURE_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class SetpointManagerSystemNodeResetTemperature_Impl;
  }

  /** \brief Resets a temperature setpoint from a reference system node.
   *
   * \par EnergyPlus object
   * <code>SetpointManager:SystemNodeReset:Temperature</code>
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerSystemNodeResetTemperature</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerSystemNodeResetTemperature : public SetpointManager
  {
   public:
    explicit SetpointManagerSystemNodeResetTemperature(const Model& model);

    virtual ~SetpointManagerSystemNodeResetTemperature() override = default;
    SetpointManagerSystemNodeResetTemperature(const SetpointManagerSystemNodeResetTemperature& other) = default;
    SetpointManagerSystemNodeResetTemperature(SetpointManagerSystemNodeResetTemperature&& other) = default;
    SetpointManagerSystemNodeResetTemperature& operator=(const SetpointManagerSystemNodeResetTemperature&) = default;
    SetpointManagerSystemNodeResetTemperature& operator=(SetpointManagerSystemNodeResetTemperature&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    double setpointatLowReferenceTemperature() const;
    bool setSetpointatLowReferenceTemperature(double setpointatLowReferenceTemperature);

    double setpointatHighReferenceTemperature() const;
    bool setSetpointatHighReferenceTemperature(double setpointatHighReferenceTemperature);

    double lowReferenceTemperature() const;
    bool setLowReferenceTemperature(double lowReferenceTemperature);

    double highReferenceTemperature() const;
    bool setHighReferenceTemperature(double highReferenceTemperature);

    boost::optional<Node> referenceNode() const;
    bool setReferenceNode(const Node& node);
    void resetReferenceNode();

   protected:
    using ImplType = detail::SetpointManagerSystemNodeResetTemperature_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSystemNodeResetTemperature(std::shared_ptr<detail::SetpointManagerSystemNodeResetTemperature_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
