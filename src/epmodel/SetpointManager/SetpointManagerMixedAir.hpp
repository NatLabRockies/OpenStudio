/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMIXEDAIR_HPP
#define EPMODEL_SETPOINTMANAGERMIXEDAIR_HPP

#include "EPModelAPI.hpp"
#include "SetpointManager/SetpointManager.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class SetpointManagerMixedAir_Impl;
  }

  /** \brief Sets a mixed-air setpoint using a reference setpoint and fan nodes.
   *
   * \par EnergyPlus object
   * \epobject{group-setpoint-managers.html#setpointmanagermixedair,SetpointManager:MixedAir}
   *
   * \par Important behavior
   * When <code>addToNode</code> succeeds, EPModel derives the reference setpoint node
   * from the air-loop supply outlet and synchronizes the fan inlet and outlet nodes
   * from the air loop.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::SetpointManagerMixedAir</code>.
   *
   * - <b>Not yet available:</b> <code>setReferenceSetpointNode(...)</code>,
   *   <code>setFanInletNode(...)</code>, <code>setFanOutletNode(...)</code>,
   *   and <code>updateFanInletOutletNodes(...)</code>.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SetpointManagerMixedAir : public SetpointManager
  {
   public:
    explicit SetpointManagerMixedAir(const Model& model);

    virtual ~SetpointManagerMixedAir() override = default;
    SetpointManagerMixedAir(const SetpointManagerMixedAir& other) = default;
    SetpointManagerMixedAir(SetpointManagerMixedAir&& other) = default;
    SetpointManagerMixedAir& operator=(const SetpointManagerMixedAir&) = default;
    SetpointManagerMixedAir& operator=(SetpointManagerMixedAir&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<Node> referenceSetpointNode() const;
    boost::optional<Node> fanInletNode() const;
    boost::optional<Node> fanOutletNode() const;

   protected:
    using ImplType = detail::SetpointManagerMixedAir_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SetpointManagerMixedAir(std::shared_ptr<detail::SetpointManagerMixedAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
