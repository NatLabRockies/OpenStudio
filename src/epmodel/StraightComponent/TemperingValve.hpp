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
    // - Status: Partial Parity. The canonical tempering-valve node surface is present, but broader loop-topology helpers are still missing.
    // - Canonical Counterpart: openstudio::model::TemperingValve.
    // - Implemented Parity: The preserved node accessors match the stream/source, setpoint, and pump-outlet relationships already covered by the canonical model.
    // - Documented Delta: Inlet/outlet port topology helpers are still managed by StraightComponent plumbing and remain intentionally limited in this pass.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `TemperingValve` node fields used by the forward translator.
    // - Evidence: `src/model/TemperingValve.hpp`, `src/model/TemperingValve.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateTemperingValve.cpp`.
    // - Remaining Parity Work: Add pump and plant-loop topology helpers once the broader plumbing surface is available.
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
