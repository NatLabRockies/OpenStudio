/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACCONTROLLERLIST_IMPL_HPP
#define EPMODEL_AIRLOOPHVACCONTROLLERLIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class ModelObject;
  class ControllerOutdoorAir;

  namespace detail {
    struct LoadContext;

    class EPMODEL_API AirLoopHVACControllerList_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirLoopHVACControllerList_Impl() override = default;

      std::vector<openstudio::epmodel::ModelObject> controllers() const;
      bool addController(const openstudio::epmodel::ModelObject& controller);
      bool removeController(const openstudio::epmodel::ModelObject& controller);

      boost::optional<openstudio::epmodel::ControllerOutdoorAir> optionalControllerOutdoorAir() const;
      bool setControllerOutdoorAir(const openstudio::epmodel::ControllerOutdoorAir& controllerOutdoorAir);

      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
