/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDX_HPP
#define EPMODEL_COILCOOLINGDX_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilCoolingDX_Impl;
}

class EPMODEL_API CoilCoolingDX : public StraightComponent
{
 public:
  explicit CoilCoolingDX(const Model& model);

  virtual ~CoilCoolingDX() override = default;
  CoilCoolingDX(const CoilCoolingDX& other) = default;
  CoilCoolingDX(CoilCoolingDX&& other) = default;
  CoilCoolingDX& operator=(const CoilCoolingDX&) = default;
  CoilCoolingDX& operator=(CoilCoolingDX&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::CoilCoolingDX scalar accessor naming/signatures where available.
  // - Field Mapping: condenserInletNodeName/condenserOutletNodeName map to EnergyPlus Coil:Cooling:DX condenser node fields.
  // - ForwardTranslator evidence: ForwardTranslateCoilCoolingDX sets these fields as plain string node names.
  // - TODO(parity): Add relationship APIs (schedule, condenser zone, performance object, tank links) in a dedicated pass.
  std::string condenserInletNodeName() const;
  bool setCondenserInletNodeName(const std::string& condenserInletNodeName);

  std::string condenserOutletNodeName() const;
  bool setCondenserOutletNodeName(const std::string& condenserOutletNodeName);

 protected:
  using ImplType = detail::CoilCoolingDX_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilCoolingDX(std::shared_ptr<detail::CoilCoolingDX_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
