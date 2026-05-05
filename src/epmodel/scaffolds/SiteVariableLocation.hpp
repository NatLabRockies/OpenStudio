/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEVARIABLELOCATION_HPP
#define EPMODEL_SITEVARIABLELOCATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SiteVariableLocation_Impl;
  }

  class EPMODEL_API SiteVariableLocation : public ModelObject
  {
   public:
    explicit SiteVariableLocation(const Model& model);

    virtual ~SiteVariableLocation() override = default;
    SiteVariableLocation(const SiteVariableLocation& other) = default;
    SiteVariableLocation(SiteVariableLocation&& other) = default;
    SiteVariableLocation& operator=(const SiteVariableLocation&) = default;
    SiteVariableLocation& operator=(SiteVariableLocation&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Name remains available through base ModelObject scalar API.
    // - Field Mapping: Building Location Latitude/Longitude/Orientation Schedule are relationship-like object-list fields and are excluded.
    // - TODO(parity): Add typed schedule-link APIs when non-scalar parity is in scope.

   protected:
    using ImplType = detail::SiteVariableLocation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteVariableLocation(std::shared_ptr<detail::SiteVariableLocation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
