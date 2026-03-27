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
  // - Status: Partial Parity. The canonical wrapper surface is mostly relationship-heavy and only the condenser node links are surfaced in epmodel so far.
  // - Canonical Counterpart: openstudio::model::CoilCoolingDX.
  // - Implemented Parity: `condenserInletNodeName` and `condenserOutletNodeName` preserve the existing node-link portion of the canonical API.
  // - Documented Delta: Availability schedule, performance-object, condenser-zone, and tank-link accessors from canonical `openstudio::model::CoilCoolingDX` are not exposed yet.
  // - Field/Storage Mapping: The preserved API maps directly to EnergyPlus `Coil:Cooling:DX` condenser node-name fields.
  // - Evidence: `src/model/CoilCoolingDX.hpp` and `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDX.cpp`.
  // - Remaining Parity Work: Add the omitted schedule, performance-object, condenser-zone, and tank-link helpers when relationship parity is extended.
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
