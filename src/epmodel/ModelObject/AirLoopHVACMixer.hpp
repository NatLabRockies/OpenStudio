/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACMIXER_HPP
#define EPMODEL_AIRLOOPHVACMIXER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirLoopHVACMixer_Impl;
}

class EPMODEL_API AirLoopHVACMixer : public ModelObject
{
 public:
  explicit AirLoopHVACMixer(const Model& model);

  virtual ~AirLoopHVACMixer() override = default;
  AirLoopHVACMixer(const AirLoopHVACMixer& other) = default;
  AirLoopHVACMixer(AirLoopHVACMixer&& other) = default;
  AirLoopHVACMixer& operator=(const AirLoopHVACMixer&) = default;
  AirLoopHVACMixer& operator=(AirLoopHVACMixer&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Outlet Node Name and extensible Inlet Node Name fields are relationship-like node links and excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs incrementally after scalar saturation.

 protected:
  using ImplType = detail::AirLoopHVACMixer_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirLoopHVACMixer(std::shared_ptr<detail::AirLoopHVACMixer_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
