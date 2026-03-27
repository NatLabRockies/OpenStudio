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
    // - Status: Partial Parity. The object-type choice surface is present, but the child-object and topology helpers remain model-owned.
    // - Canonical Counterpart: openstudio::model::CoilSystemCoolingDXHeatExchangerAssisted.
    // - Implemented Parity: `heatExchangerObjectType` and `coolingCoilObjectType` preserve the canonical object-choice API.
    // - Documented Delta: Heat-exchanger name, cooling-coil name, and node-link helpers from canonical `openstudio::model::CoilSystemCoolingDXHeatExchangerAssisted` are not exposed yet.
    // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `CoilSystem:Cooling:DX:HeatExchangerAssisted` choice fields.
    // - Evidence: `src/model/CoilSystemCoolingDXHeatExchangerAssisted.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemCoolingDXHeatExchangerAssisted.cpp`, and `src/epmodel/test/CoilSystemCoolingDXHeatExchangerAssisted_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted child-object and topology helpers without changing the preserved scalar signatures.

    // Heat exchanger object-type accessors
    std::string heatExchangerObjectType() const;
    bool setHeatExchangerObjectType(const std::string& heatExchangerObjectType);

    // Cooling coil object-type accessors
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
