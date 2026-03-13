/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACRETURNPATH_IMPL_HPP
#define EPMODEL_AIRLOOPHVACRETURNPATH_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  class AirLoopHVAC;
  class Node;
  class ModelObject;
  namespace detail {

    class EPMODEL_API AirLoopHVACReturnPath_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirLoopHVACReturnPath_Impl() override = default;

      /** @name Return air path outlet node */
      //@{
      boost::optional<openstudio::epmodel::Node> returnAirPathOutletNode() const;
      bool setReturnAirPathOutletNode(const openstudio::epmodel::Node& node);
      //@}

      /** @name Relationship helpers */
      //@{
      boost::optional<openstudio::epmodel::AirLoopHVAC> airLoopHVAC() const;
      std::vector<openstudio::epmodel::ModelObject> components() const;
      //@}
      void doCanonicalize(LoadContext& context) override;

     private:
      bool addComponent(const openstudio::epmodel::ModelObject& component);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
