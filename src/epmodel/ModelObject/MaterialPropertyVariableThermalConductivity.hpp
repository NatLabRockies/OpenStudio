/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_MATERIALPROPERTYVARIABLETHERMALCONDUCTIVITY_HPP
#define EPMODEL_MATERIALPROPERTYVARIABLETHERMALCONDUCTIVITY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class MaterialPropertyVariableThermalConductivity_Impl;
}

/** MaterialPropertyVariableThermalConductivity is a ModelObject that wraps the EnergyPlus IDD object
 * 'MaterialProperty:VariableThermalConductivity'. */
class EPMODEL_API MaterialPropertyVariableThermalConductivity : public ModelObject
{
 public:
  explicit MaterialPropertyVariableThermalConductivity(const Model& model);

  virtual ~MaterialPropertyVariableThermalConductivity() override = default;
  MaterialPropertyVariableThermalConductivity(const MaterialPropertyVariableThermalConductivity& other) = default;
  MaterialPropertyVariableThermalConductivity(MaterialPropertyVariableThermalConductivity&& other) = default;
  MaterialPropertyVariableThermalConductivity& operator=(const MaterialPropertyVariableThermalConductivity&) = default;
  MaterialPropertyVariableThermalConductivity& operator=(MaterialPropertyVariableThermalConductivity&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class naming.
  // - Field Mapping: In scalar-only scaffold mode, only inherited ModelObject name accessors are exposed.
  // - Field Mapping: Extensible Temperature / Thermal Conductivity pairs are intentionally excluded from scalar accessors.
  // - TODO(parity): Add extensible-group APIs in a dedicated extensible parity pass.

 protected:
  using ImplType = detail::MaterialPropertyVariableThermalConductivity_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit MaterialPropertyVariableThermalConductivity(std::shared_ptr<detail::MaterialPropertyVariableThermalConductivity_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
