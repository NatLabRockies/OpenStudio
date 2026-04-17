/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_TEMPERINGVALVE_IMPL_HPP
#define EPMODEL_TEMPERINGVALVE_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class Node;

  namespace detail {

    class EPMODEL_API TemperingValve_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~TemperingValve_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

      boost::optional<Node> stream2SourceNode() const;
      boost::optional<Node> temperatureSetpointNode() const;
      boost::optional<Node> pumpOutletNode() const;

      bool setStream2SourceNode(const Node& stream2SourceNode);
      void resetStream2SourceNode();

      bool setTemperatureSetpointNode(const Node& temperatureSetpointNode);
      void resetTemperatureSetpointNode();

      bool setPumpOutletNode(const Node& pumpOutletNode);
      void resetPumpOutletNode();

      bool setControlNodes();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
