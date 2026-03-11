/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGDXHEATEXCHANGERASSISTED_HPP
#define EPMODEL_COILSYSTEMCOOLINGDXHEATEXCHANGERASSISTED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilSystemCoolingDXHeatExchangerAssisted_Impl;
}

class EPMODEL_API CoilSystemCoolingDXHeatExchangerAssisted : public StraightComponent
{
 public:
  explicit CoilSystemCoolingDXHeatExchangerAssisted(const Model& model);

  virtual ~CoilSystemCoolingDXHeatExchangerAssisted() override = default;
  CoilSystemCoolingDXHeatExchangerAssisted(const CoilSystemCoolingDXHeatExchangerAssisted& other) = default;
  CoilSystemCoolingDXHeatExchangerAssisted(CoilSystemCoolingDXHeatExchangerAssisted&& other) = default;
  CoilSystemCoolingDXHeatExchangerAssisted& operator=(const CoilSystemCoolingDXHeatExchangerAssisted&) = default;
  CoilSystemCoolingDXHeatExchangerAssisted& operator=(CoilSystemCoolingDXHeatExchangerAssisted&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> heatExchangerObjectTypeValues();
  static std::vector<std::string> coolingCoilObjectTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model class naming for counterpart CoilSystemCoolingDXHeatExchangerAssisted.
  // - Field Mapping: heatExchangerObjectType/coolingCoilObjectType map to EnergyPlus CoilSystem:Cooling:DX:HeatExchangerAssisted choice fields.
  // - ForwardTranslator evidence: ForwardTranslateCoilSystemCoolingDXHeatExchangerAssisted sets these object-type fields from translated child objects.
  // - Field Mapping: Heat Exchanger Name, Cooling Coil Name, and inlet/outlet node links are relationship-like and intentionally excluded from scalar APIs.
  // - TODO(parity): Add relationship APIs in a dedicated parity pass without changing scalar signatures.
  std::string heatExchangerObjectType() const;
  bool setHeatExchangerObjectType(const std::string& heatExchangerObjectType);

  std::string coolingCoilObjectType() const;
  bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);

 protected:
  using ImplType = detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilSystemCoolingDXHeatExchangerAssisted(std::shared_ptr<detail::CoilSystemCoolingDXHeatExchangerAssisted_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
