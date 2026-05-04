/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACSUPPLYPATH_HPP
#define EPMODEL_AIRLOOPHVACSUPPLYPATH_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class AirLoopHVAC;
class Model;

namespace detail {
class AirLoopHVACSupplyPath_Impl;
}

class EPMODEL_API AirLoopHVACSupplyPath : public ModelObject
{
 public:
  explicit AirLoopHVACSupplyPath(const Model& model);

  virtual ~AirLoopHVACSupplyPath() override = default;
  AirLoopHVACSupplyPath(const AirLoopHVACSupplyPath& other) = default;
  AirLoopHVACSupplyPath(AirLoopHVACSupplyPath&& other) = default;
  AirLoopHVACSupplyPath& operator=(const AirLoopHVACSupplyPath&) = default;
  AirLoopHVACSupplyPath& operator=(AirLoopHVACSupplyPath&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived naming and existing path-link behavior.
  // - Field Mapping: Supply Air Path Inlet Node Name is a node relationship field, excluded from scalar accessors.
  // - Field Mapping: Extensible Component Object Type / Component Name are relationship-like target links, excluded from scalar accessors.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - TODO(parity): Add typed relationship APIs incrementally if needed beyond current behavior.
  boost::optional<openstudio::epmodel::AirLoopHVAC> airLoopHVAC() const;
  std::vector<openstudio::epmodel::ModelObject> components() const;

 protected:
  using ImplType = detail::AirLoopHVACSupplyPath_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class Model;

  explicit AirLoopHVACSupplyPath(std::shared_ptr<detail::AirLoopHVACSupplyPath_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
