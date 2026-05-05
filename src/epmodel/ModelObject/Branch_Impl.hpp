/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BRANCH_IMPL_HPP
#define EPMODEL_BRANCH_IMPL_HPP

#include "ModelObject_Impl.hpp"
#include "Node.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class ModelObject;
  namespace detail {
    struct LoadContext;

    class EPMODEL_API Branch_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~Branch_Impl() override = default;

      std::vector<openstudio::epmodel::ModelObject> components() const;
      bool insertComponent(unsigned index, const ModelObject& component, const std::string& inletNodeName, const std::string& outletNodeName);
      bool appendComponent(const ModelObject& component, const std::string& inletNodeName, const std::string& outletNodeName);
      bool removeComponent(unsigned index);
      void clearComponents();
      boost::optional<Node> componentInletNode(unsigned index) const;
      boost::optional<Node> componentOutletNode(unsigned index) const;
      bool setComponentInletNode(unsigned index, const Node& node);
      bool setComponentOutletNode(unsigned index, const Node& node);
      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
