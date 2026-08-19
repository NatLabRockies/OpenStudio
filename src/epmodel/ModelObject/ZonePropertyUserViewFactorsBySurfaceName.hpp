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

  /** \brief ZonePropertyUserViewFactorsBySurfaceName.
   *
   * \par EnergyPlus object
   * \epobject{group-advanced-surface-concepts.html#zonepropertyuserviewfactorsbysurfacename,ZoneProperty:UserViewFactors:BySurfaceName}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ZonePropertyUserViewFactorsBySurfaceName</code>. <b>Changed:</b> EPModel exposes direct construction from <code>Model</code>; Model construction requires a thermal zone. This object is relationship-driven, and EPModel does not expose its zone/space references or extensible view-factor entries.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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
