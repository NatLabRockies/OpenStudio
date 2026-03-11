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

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::TemperingValve node getter/setter names/signatures for this model-counterpart type.
    // - Field Mapping: stream2SourceNode, temperatureSetpointNode, and pumpOutletNode map directly to EnergyPlus
    //   TemperingValve Stream2SourceNodeName, TemperatureSetpointNodeName, and PumpOutletNodeName fields tracked by
    //   ForwardTranslateTemperingValve.
    // - Field Mapping: InletNodeName/OutletNodeName port wiring is managed through StraightComponent inlet/outlet ports and
    //   loop canonicalization, so they are not re-exposed as additional scalars.
    // - TODO(parity): Add pump/plant loop topology helpers once epmodel plant loop plumbing reaches the same coverage.
    boost::optional<Node> stream2SourceNode() const;
    boost::optional<Node> temperatureSetpointNode() const;
    boost::optional<Node> pumpOutletNode() const;

    bool setStream2SourceNode(const Node& stream2SourceNode);
    void resetStream2SourceNode();

    bool setTemperatureSetpointNode(const Node& temperatureSetpointNode);
    void resetTemperatureSetpointNode();

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
