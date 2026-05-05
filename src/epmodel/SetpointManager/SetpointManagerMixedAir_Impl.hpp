/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGERMIXEDAIR_IMPL_HPP
#define EPMODEL_SETPOINTMANAGERMIXEDAIR_IMPL_HPP

#include "SetpointManager/SetpointManager_Impl.hpp"

namespace openstudio {
namespace epmodel {
  class Node;
  namespace detail {

    class EPMODEL_API SetpointManagerMixedAir_Impl : public SetpointManager_Impl
    {
     public:
      using SetpointManager_Impl::SetpointManager_Impl;
      virtual ~SetpointManagerMixedAir_Impl() override = default;

      boost::optional<openstudio::epmodel::Node> setpointNode() const override;
      std::string controlVariable() const override;
      bool setControlVariable(const std::string& value) override;
      bool addToNode(Node& node) override;
      bool setReferenceSetpointNode(const Node& node);
      bool setFanInletNode(const Node& node);
      bool setFanOutletNode(const Node& node);

     protected:
      void doCanonicalize(LoadContext& context) override;

     private:
      bool setSetpointNode(const openstudio::epmodel::Node& node) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
