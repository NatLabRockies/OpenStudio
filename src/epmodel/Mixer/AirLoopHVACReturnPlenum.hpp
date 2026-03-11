/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACRETURNPLENUM_HPP
#define EPMODEL_AIRLOOPHVACRETURNPLENUM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirLoopHVACReturnPlenum_Impl;
}

class EPMODEL_API AirLoopHVACReturnPlenum : public ModelObject
{
 public:
  explicit AirLoopHVACReturnPlenum(const Model& model);

  virtual ~AirLoopHVACReturnPlenum() override = default;
  AirLoopHVACReturnPlenum(const AirLoopHVACReturnPlenum& other) = default;
  AirLoopHVACReturnPlenum(AirLoopHVACReturnPlenum&& other) = default;
  AirLoopHVACReturnPlenum& operator=(const AirLoopHVACReturnPlenum&) = default;
  AirLoopHVACReturnPlenum& operator=(AirLoopHVACReturnPlenum&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model class naming for this model-counterpart type.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Zone Name, Zone Node Name, Outlet Node Name, Induced Air Outlet Node or NodeList Name, and extensible Inlet Node Name are relationship-like
  //   links and excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirLoopHVACReturnPlenum writes those fields through node/zone relationships and generated NodeList wiring.
  // - TODO(parity): Add non-scalar relationship APIs incrementally after scalar saturation.

 protected:
  using ImplType = detail::AirLoopHVACReturnPlenum_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirLoopHVACReturnPlenum(std::shared_ptr<detail::AirLoopHVACReturnPlenum_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
