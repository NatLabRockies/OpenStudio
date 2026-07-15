/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACCONTROLLERLIST_HPP
#define EPMODEL_AIRLOOPHVACCONTROLLERLIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class ModelObject;
  class ControllerOutdoorAir;

  namespace detail {
    class AirLoopHVACControllerList_Impl;
  }

  class EPMODEL_API AirLoopHVACControllerList : public ModelObject
  {
   public:
    explicit AirLoopHVACControllerList(const Model& model);

    virtual ~AirLoopHVACControllerList() override = default;
    AirLoopHVACControllerList(const AirLoopHVACControllerList& other) = default;
    AirLoopHVACControllerList(AirLoopHVACControllerList&& other) = default;
    AirLoopHVACControllerList& operator=(const AirLoopHVACControllerList&) = default;
    AirLoopHVACControllerList& operator=(AirLoopHVACControllerList&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps IDD-derived naming and list-management semantics.
    // - Field Mapping: IDD extensible fields (Controller Object Type, Controller Name) are relationship-like and intentionally excluded from scalar accessors.
    // - TODO(parity): Add scalar accessors only if future schema adds non-relationship scalar fields.
    std::vector<ModelObject> controllers() const;

    boost::optional<ControllerOutdoorAir> optionalControllerOutdoorAir() const;

   protected:
    using ImplType = detail::AirLoopHVACControllerList_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit AirLoopHVACControllerList(std::shared_ptr<detail::AirLoopHVACControllerList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
