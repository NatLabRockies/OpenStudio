/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTION_HPP
#define EPMODEL_CONSTRUCTION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class Construction_Impl;
}

class EPMODEL_API Construction : public ModelObject
{
 public:
  explicit Construction(const Model& model);

  virtual ~Construction() override = default;
  Construction(const Construction& other) = default;
  Construction(Construction&& other) = default;
  Construction& operator=(const Construction&) = default;
  Construction& operator=(Construction&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model class/API naming for this model-counterpart type.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Construction layer fields are extensible relationship links and are intentionally excluded from scalar accessors.
  // - TODO(parity): Add layer relationship APIs when LayeredConstruction/ConstructionBase epmodel families are scaffolded.

 protected:
  using ImplType = detail::Construction_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit Construction(std::shared_ptr<detail::Construction_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
