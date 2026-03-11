/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACEHVACZONERETURNMIXER_HPP
#define EPMODEL_SPACEHVACZONERETURNMIXER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SpaceHVACZoneReturnMixer_Impl;
}

class EPMODEL_API SpaceHVACZoneReturnMixer : public ModelObject
{
 public:
  explicit SpaceHVACZoneReturnMixer(const Model& model);

  virtual ~SpaceHVACZoneReturnMixer() override = default;
  SpaceHVACZoneReturnMixer(const SpaceHVACZoneReturnMixer& other) = default;
  SpaceHVACZoneReturnMixer(SpaceHVACZoneReturnMixer&& other) = default;
  SpaceHVACZoneReturnMixer& operator=(const SpaceHVACZoneReturnMixer&) = default;
  SpaceHVACZoneReturnMixer& operator=(SpaceHVACZoneReturnMixer&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Zone Name, Zone Return Air Node Name, and extensible Space Name / Space Return Air Node Name are relationship-like fields
  //   and excluded from scalar accessors.
  // - TODO(parity): Add typed relationship APIs incrementally after scalar saturation.

 protected:
  using ImplType = detail::SpaceHVACZoneReturnMixer_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SpaceHVACZoneReturnMixer(std::shared_ptr<detail::SpaceHVACZoneReturnMixer_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
