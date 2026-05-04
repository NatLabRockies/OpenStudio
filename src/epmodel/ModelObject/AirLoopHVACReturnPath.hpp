/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACRETURNPATH_HPP
#define EPMODEL_AIRLOOPHVACRETURNPATH_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class AirLoopHVAC;
class Model;

namespace detail {
  class AirLoopHVACReturnPath_Impl;
}

class EPMODEL_API AirLoopHVACReturnPath : public ModelObject
{
 public:
  explicit AirLoopHVACReturnPath(const Model& model);

  virtual ~AirLoopHVACReturnPath() override = default;
  AirLoopHVACReturnPath(const AirLoopHVACReturnPath& other) = default;
  AirLoopHVACReturnPath(AirLoopHVACReturnPath&& other) = default;
  AirLoopHVACReturnPath& operator=(const AirLoopHVACReturnPath&) = default;
  AirLoopHVACReturnPath& operator=(AirLoopHVACReturnPath&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived naming and existing path-link behavior.
  // - Field Mapping: Return Air Path Outlet Node Name is a node relationship field, excluded from scalar accessors.
  // - Field Mapping: Extensible Component Object Type / Component Name are relationship-like target links, excluded from scalar accessors.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - TODO(parity): Add typed relationship APIs incrementally if needed beyond current behavior.
  boost::optional<openstudio::epmodel::AirLoopHVAC> airLoopHVAC() const;
  std::vector<openstudio::epmodel::ModelObject> components() const;

 protected:
  using ImplType = detail::AirLoopHVACReturnPath_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class Model;

  explicit AirLoopHVACReturnPath(std::shared_ptr<detail::AirLoopHVACReturnPath_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
