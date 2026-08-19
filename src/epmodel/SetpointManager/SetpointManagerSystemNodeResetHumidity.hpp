/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERSYSTEMNODERESETHUMIDITY_HPP
#define EPMODEL_SETPOINTMANAGERSYSTEMNODERESETHUMIDITY_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class SetpointManagerSystemNodeResetHumidity_Impl;
  }

  /** \brief Resets a humidity-ratio setpoint from a reference system node.
   *
   * \par EnergyPlus object
   * <code>SetpointManager:SystemNodeReset:Humidity</code>
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SetpointManagerSystemNodeResetHumidity</code>.
   * No known public API differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerSystemNodeResetHumidity : public SetpointManager
  {
   public:
    explicit SetpointManagerSystemNodeResetHumidity(const Model& model);

    virtual ~SetpointManagerSystemNodeResetHumidity() override = default;
    SetpointManagerSystemNodeResetHumidity(const SetpointManagerSystemNodeResetHumidity& other) = default;
    SetpointManagerSystemNodeResetHumidity(SetpointManagerSystemNodeResetHumidity&& other) = default;
    SetpointManagerSystemNodeResetHumidity& operator=(const SetpointManagerSystemNodeResetHumidity&) = default;
    SetpointManagerSystemNodeResetHumidity& operator=(SetpointManagerSystemNodeResetHumidity&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> controlVariableValues();

    double setpointatLowReferenceHumidityRatio() const;
    bool setSetpointatLowReferenceHumidityRatio(double setpointatLowReferenceHumidityRatio);

    double setpointatHighReferenceHumidityRatio() const;
    bool setSetpointatHighReferenceHumidityRatio(double setpointatHighReferenceHumidityRatio);

    double lowReferenceHumidityRatio() const;
    bool setLowReferenceHumidityRatio(double lowReferenceHumidityRatio);

    double highReferenceHumidityRatio() const;
    bool setHighReferenceHumidityRatio(double highReferenceHumidityRatio);

    boost::optional<Node> referenceNode() const;
    bool setReferenceNode(const Node& node);
    void resetReferenceNode();

   protected:
    using ImplType = detail::SetpointManagerSystemNodeResetHumidity_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerSystemNodeResetHumidity(std::shared_ptr<detail::SetpointManagerSystemNodeResetHumidity_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
