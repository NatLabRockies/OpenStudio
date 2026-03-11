/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACEXHAUSTSYSTEM_HPP
#define EPMODEL_AIRLOOPHVACEXHAUSTSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirLoopHVACExhaustSystem_Impl;
}

class EPMODEL_API AirLoopHVACExhaustSystem : public ModelObject
{
 public:
  explicit AirLoopHVACExhaustSystem(const Model& model);

  virtual ~AirLoopHVACExhaustSystem() override = default;
  AirLoopHVACExhaustSystem(const AirLoopHVACExhaustSystem& other) = default;
  AirLoopHVACExhaustSystem(AirLoopHVACExhaustSystem&& other) = default;
  AirLoopHVACExhaustSystem& operator=(const AirLoopHVACExhaustSystem&) = default;
  AirLoopHVACExhaustSystem& operator=(AirLoopHVACExhaustSystem&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Zone Mixer Name, Fan Object Type, and Fan Name are relationship-like link fields and excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs incrementally after scalar saturation.

 protected:
  using ImplType = detail::AirLoopHVACExhaustSystem_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirLoopHVACExhaustSystem(std::shared_ptr<detail::AirLoopHVACExhaustSystem_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
