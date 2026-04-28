/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEPROPERTYLOCALENVIRONMENT_HPP
#define EPMODEL_ZONEPROPERTYLOCALENVIRONMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZonePropertyLocalEnvironment_Impl;
  }

  class EPMODEL_API ZonePropertyLocalEnvironment : public ModelObject
  {
   public:
    explicit ZonePropertyLocalEnvironment(const Model& model);

    virtual ~ZonePropertyLocalEnvironment() override = default;
    ZonePropertyLocalEnvironment(const ZonePropertyLocalEnvironment& other) = default;
    ZonePropertyLocalEnvironment(ZonePropertyLocalEnvironment&& other) = default;
    ZonePropertyLocalEnvironment& operator=(const ZonePropertyLocalEnvironment&) = default;
    ZonePropertyLocalEnvironment& operator=(ZonePropertyLocalEnvironment&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: IDD-derived naming is retained because this type has no openstudio::model counterpart.
    // - Field Mapping: Name is already available via ModelObject base scalars; Zone Name and Outdoor Air Node Name are relationship fields excluded from this scalar-only scaffolding pass.
    // - TODO(parity): Add relationship helpers after the scalar saturation milestone finishes.

   protected:
    using ImplType = detail::ZonePropertyLocalEnvironment_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZonePropertyLocalEnvironment(std::shared_ptr<detail::ZonePropertyLocalEnvironment_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
