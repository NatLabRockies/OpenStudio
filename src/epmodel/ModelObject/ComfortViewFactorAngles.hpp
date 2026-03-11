/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COMFORTVIEWFACTORANGLES_HPP
#define EPMODEL_COMFORTVIEWFACTORANGLES_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ComfortViewFactorAngles_Impl;
}

class EPMODEL_API ComfortViewFactorAngles : public ModelObject
{
 public:
  explicit ComfortViewFactorAngles(const Model& model);

  virtual ~ComfortViewFactorAngles() override = default;
  ComfortViewFactorAngles(const ComfortViewFactorAngles& other) = default;
  ComfortViewFactorAngles(ComfortViewFactorAngles&& other) = default;
  ComfortViewFactorAngles& operator=(const ComfortViewFactorAngles&) = default;
  ComfortViewFactorAngles& operator=(ComfortViewFactorAngles&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Extensible Surface Name and Angle Factor entries are relationship/extensible fields
  //   and are intentionally excluded from simple scalar accessor scaffolding.
  // - TODO(parity): Add dedicated extensible-group APIs after scalar saturation.

 protected:
  using ImplType = detail::ComfortViewFactorAngles_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ComfortViewFactorAngles(std::shared_ptr<detail::ComfortViewFactorAngles_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
