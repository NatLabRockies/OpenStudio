/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SETPOINTMANAGER_IMPL_HPP
#define EPMODEL_SETPOINTMANAGER_IMPL_HPP

#include "HVACComponent/HVACComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Node;

  namespace detail {

    class EPMODEL_API SetpointManager_Impl : public HVACComponent_Impl
    {
     public:
      using HVACComponent_Impl::HVACComponent_Impl;
      virtual ~SetpointManager_Impl() override = default;

      boost::optional<openstudio::epmodel::Node> setpointNode() const;

      std::string controlVariable() const;
      bool setControlVariable(const std::string& value);

      virtual bool isAllowedOnPlantLoop() const;
      bool addToNode(openstudio::epmodel::Node& node) override;

      void doCanonicalize(LoadContext& context) override;

     protected:
      virtual unsigned setpointNodeFieldIndex() const = 0;
      bool setSetpointNode(openstudio::epmodel::Node& node);

      virtual unsigned controlVariableFieldIndex() const = 0;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
