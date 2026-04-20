/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DUCTLOSSLEAKAGE_HPP
#define EPMODEL_DUCTLOSSLEAKAGE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class DuctLossLeakage_Impl;
}

class EPMODEL_API DuctLossLeakage : public ModelObject
{
 public:
  explicit DuctLossLeakage(const Model& model);

  virtual ~DuctLossLeakage() override = default;
  DuctLossLeakage(const DuctLossLeakage& other) = default;
  DuctLossLeakage(DuctLossLeakage&& other) = default;
  DuctLossLeakage& operator=(const DuctLossLeakage&) = default;
  DuctLossLeakage& operator=(DuctLossLeakage&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - Field Mapping: AirLoopHVAC Name and AirflowNetwork:Distribution:Linkage Name are relationship-like object-list fields and are
  //   excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs incrementally after scalar saturation.

 protected:
  using ImplType = detail::DuctLossLeakage_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit DuctLossLeakage(std::shared_ptr<detail::DuctLossLeakage_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
