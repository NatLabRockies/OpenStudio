/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEPROPERTYUSERVIEWFACTORSBYSURFACENAME_HPP
#define EPMODEL_ZONEPROPERTYUSERVIEWFACTORSBYSURFACENAME_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZonePropertyUserViewFactorsBySurfaceName_Impl;
  }

  class EPMODEL_API ZonePropertyUserViewFactorsBySurfaceName : public ModelObject
  {
   public:
    explicit ZonePropertyUserViewFactorsBySurfaceName(const Model& model);

    virtual ~ZonePropertyUserViewFactorsBySurfaceName() override = default;
    ZonePropertyUserViewFactorsBySurfaceName(const ZonePropertyUserViewFactorsBySurfaceName& other) = default;
    ZonePropertyUserViewFactorsBySurfaceName(ZonePropertyUserViewFactorsBySurfaceName&& other) = default;
    ZonePropertyUserViewFactorsBySurfaceName& operator=(const ZonePropertyUserViewFactorsBySurfaceName&) = default;
    ZonePropertyUserViewFactorsBySurfaceName& operator=(ZonePropertyUserViewFactorsBySurfaceName&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserved the openstudio::model naming (ZonePropertyUserViewFactorsBySurfaceName) and rely on translateZonePropertyUserViewFactorsBySurfaceName for the translation wiring.
    // - Field Mapping: Zone/ZoneList/Space/SpaceList references plus the extensible FromSurface/ToSurface/ViewFactor entries are relationship-driven and intentionally excluded from this scalar-only scaffolding pass.
    // - TODO(parity): Add view-factor collection helpers once the relational scaffolding work completes.

   protected:
    using ImplType = detail::ZonePropertyUserViewFactorsBySurfaceName_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZonePropertyUserViewFactorsBySurfaceName(std::shared_ptr<detail::ZonePropertyUserViewFactorsBySurfaceName_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
