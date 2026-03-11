/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTROLCONTAMINANTCONTROLLER_HPP
#define EPMODEL_ZONECONTROLCONTAMINANTCONTROLLER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneControlContaminantController_Impl;
  }

  class EPMODEL_API ZoneControlContaminantController : public ModelObject
  {
   public:
    explicit ZoneControlContaminantController(const Model& model);

    virtual ~ZoneControlContaminantController() override = default;
    ZoneControlContaminantController(const ZoneControlContaminantController& other) = default;
    ZoneControlContaminantController(ZoneControlContaminantController&& other) = default;
    ZoneControlContaminantController& operator=(const ZoneControlContaminantController&) = default;
    ZoneControlContaminantController& operator=(ZoneControlContaminantController&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Mirrors the openstudio::model counterpart naming (ZoneControlContaminantController).
    // - Field Mapping: Name remains available through the base ModelObject scalar API; all controller-specific fields are relationship-style object-list references (Controlled Zone Name, Carbon Dioxide Control Availability Schedule Name, Carbon Dioxide Setpoint Schedule Name, Minimum Carbon Dioxide Concentration Schedule Name, Generic Contaminant Control Availability Schedule Name, Generic Contaminant Setpoint Schedule Name) and are excluded from scalar accessors.
    // - TODO(parity): Add schedule/relationship APIs once scalar saturation for relationships completes.

   protected:
    using ImplType = detail::ZoneControlContaminantController_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneControlContaminantController(std::shared_ptr<detail::ZoneControlContaminantController_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
