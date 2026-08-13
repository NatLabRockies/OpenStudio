/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACSUPPLYPATH_IMPL_HPP
#define EPMODEL_AIRLOOPHVACSUPPLYPATH_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  class AirLoopHVAC;
  class Node;
  class ModelObject;
  namespace detail {

    class EPMODEL_API AirLoopHVACSupplyPath_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirLoopHVACSupplyPath_Impl() override = default;

      boost::optional<openstudio::epmodel::Node> supplyAirPathInletNode() const;
      bool setSupplyAirPathInletNode(const openstudio::epmodel::Node& node);

      boost::optional<openstudio::epmodel::AirLoopHVAC> airLoopHVAC() const;

      std::vector<openstudio::epmodel::ModelObject> components() const;
      bool addComponent(const openstudio::epmodel::ModelObject& component);
      bool removeComponent(const openstudio::epmodel::ModelObject& component);

      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
