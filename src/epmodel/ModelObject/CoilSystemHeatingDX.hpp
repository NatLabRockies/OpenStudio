/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMHEATINGDX_HPP
#define EPMODEL_COILSYSTEMHEATINGDX_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilSystemHeatingDX_Impl;
}

class EPMODEL_API CoilSystemHeatingDX : public ModelObject
{
 public:
  explicit CoilSystemHeatingDX(const Model& model);

  virtual ~CoilSystemHeatingDX() override = default;
  CoilSystemHeatingDX(const CoilSystemHeatingDX& other) = default;
  CoilSystemHeatingDX(CoilSystemHeatingDX&& other) = default;
  CoilSystemHeatingDX& operator=(const CoilSystemHeatingDX&) = default;
  CoilSystemHeatingDX& operator=(CoilSystemHeatingDX&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> heatingCoilObjectTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: heatingCoilObjectType maps directly to CoilSystem:Heating:DX Heating Coil Object Type.
  // - Field Mapping: Availability Schedule Name and Heating Coil Name are relationship-like fields and intentionally excluded.
  // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.
  std::string heatingCoilObjectType() const;
  bool setHeatingCoilObjectType(const std::string& heatingCoilObjectType);

 protected:
  using ImplType = detail::CoilSystemHeatingDX_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilSystemHeatingDX(std::shared_ptr<detail::CoilSystemHeatingDX_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
