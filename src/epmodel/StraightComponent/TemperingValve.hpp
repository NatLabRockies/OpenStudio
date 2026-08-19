/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TEMPERINGVALVE_HPP
#define EPMODEL_TEMPERINGVALVE_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class TemperingValve_Impl;
  }

/** \brief A tempering valve in a plant loop.
 *
 * \par EnergyPlus object
 * \epobject{group-plant-condenser-flow-control.html#temperingvalve,TemperingValve}
 *
 * \par Important behavior
 * Stream/source, setpoint, pump-outlet node relationships, and plant-supply placement map directly to TemperingValve.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::TemperingValve</code>.
 *
 * \par Known limitations
 * Broader shared HVACComponent conveniences are not exposed.
 */
  class EPMODEL_API TemperingValve : public StraightComponent
  {
   public:
    explicit TemperingValve(const Model& model);

    virtual ~TemperingValve() override = default;
    TemperingValve(const TemperingValve& other) = default;
    TemperingValve(TemperingValve&& other) = default;
    TemperingValve& operator=(const TemperingValve&) = default;
    TemperingValve& operator=(TemperingValve&&) = default;

    static IddObjectType iddObjectType();

    boost::optional<Node> stream2SourceNode() const;
    bool setStream2SourceNode(const Node& stream2SourceNode);
    void resetStream2SourceNode();

    boost::optional<Node> temperatureSetpointNode() const;
    bool setTemperatureSetpointNode(const Node& temperatureSetpointNode);
    void resetTemperatureSetpointNode();

    boost::optional<Node> pumpOutletNode() const;
    bool setPumpOutletNode(const Node& pumpOutletNode);
    void resetPumpOutletNode();

   protected:
    using ImplType = detail::TemperingValve_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit TemperingValve(std::shared_ptr<detail::TemperingValve_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
