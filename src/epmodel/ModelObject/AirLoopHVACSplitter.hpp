/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACSPLITTER_HPP
#define EPMODEL_AIRLOOPHVACSPLITTER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirLoopHVACSplitter_Impl;
}

class EPMODEL_API AirLoopHVACSplitter : public ModelObject
{
 public:
  explicit AirLoopHVACSplitter(const Model& model);

  virtual ~AirLoopHVACSplitter() override = default;
  AirLoopHVACSplitter(const AirLoopHVACSplitter& other) = default;
  AirLoopHVACSplitter(AirLoopHVACSplitter&& other) = default;
  AirLoopHVACSplitter& operator=(const AirLoopHVACSplitter&) = default;
  AirLoopHVACSplitter& operator=(AirLoopHVACSplitter&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Inlet Node Name and extensible Outlet Node Name fields are relationship-like node links and excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs incrementally after scalar saturation.

 protected:
  using ImplType = detail::AirLoopHVACSplitter_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirLoopHVACSplitter(std::shared_ptr<detail::AirLoopHVACSplitter_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
