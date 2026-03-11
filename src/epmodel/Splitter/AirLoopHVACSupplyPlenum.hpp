/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACSUPPLYPLENUM_HPP
#define EPMODEL_AIRLOOPHVACSUPPLYPLENUM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirLoopHVACSupplyPlenum_Impl;
}

class EPMODEL_API AirLoopHVACSupplyPlenum : public ModelObject
{
 public:
  explicit AirLoopHVACSupplyPlenum(const Model& model);

  virtual ~AirLoopHVACSupplyPlenum() override = default;
  AirLoopHVACSupplyPlenum(const AirLoopHVACSupplyPlenum& other) = default;
  AirLoopHVACSupplyPlenum(AirLoopHVACSupplyPlenum&& other) = default;
  AirLoopHVACSupplyPlenum& operator=(const AirLoopHVACSupplyPlenum&) = default;
  AirLoopHVACSupplyPlenum& operator=(AirLoopHVACSupplyPlenum&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model class naming for this model-counterpart type.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: Zone Name, Zone Node Name, Inlet Node Name, and extensible Outlet Node Name are relationship-like links and excluded from scalar accessors.
  // - ForwardTranslator evidence: translateAirLoopHVACSupplyPlenum writes these fields via zone/node relationships and outlet branch topology.
  // - TODO(parity): Add non-scalar relationship APIs incrementally after scalar saturation.

 protected:
  using ImplType = detail::AirLoopHVACSupplyPlenum_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirLoopHVACSupplyPlenum(std::shared_ptr<detail::AirLoopHVACSupplyPlenum_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
