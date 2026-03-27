/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGWATERHEATEXCHANGERASSISTED_HPP
#define EPMODEL_COILSYSTEMCOOLINGWATERHEATEXCHANGERASSISTED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class CoilSystemCoolingWaterHeatExchangerAssisted_Impl;
  }

  class EPMODEL_API CoilSystemCoolingWaterHeatExchangerAssisted : public StraightComponent
  {
   public:
    explicit CoilSystemCoolingWaterHeatExchangerAssisted(const Model& model);

    virtual ~CoilSystemCoolingWaterHeatExchangerAssisted() override = default;
    CoilSystemCoolingWaterHeatExchangerAssisted(const CoilSystemCoolingWaterHeatExchangerAssisted& other) = default;
    CoilSystemCoolingWaterHeatExchangerAssisted(CoilSystemCoolingWaterHeatExchangerAssisted&& other) = default;
    CoilSystemCoolingWaterHeatExchangerAssisted& operator=(const CoilSystemCoolingWaterHeatExchangerAssisted&) = default;
    CoilSystemCoolingWaterHeatExchangerAssisted& operator=(CoilSystemCoolingWaterHeatExchangerAssisted&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatExchangerObjectTypeValues();
    static std::vector<std::string> coolingCoilObjectTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The object-type choice surface is present, but the child-object and topology helpers remain model-owned.
    // - Canonical Counterpart: openstudio::model::CoilSystemCoolingWaterHeatExchangerAssisted.
    // - Implemented Parity: `heatExchangerObjectType` and `coolingCoilObjectType` preserve the canonical object-choice API.
    // - Documented Delta: Heat-exchanger name, cooling-coil name, and node-link helpers from canonical `openstudio::model::CoilSystemCoolingWaterHeatExchangerAssisted` are not exposed yet.
    // - Field/Storage Mapping: Preserved scalars map directly to EnergyPlus `CoilSystem:Cooling:Water:HeatExchangerAssisted` choice fields.
    // - Evidence: `src/model/CoilSystemCoolingWaterHeatExchangerAssisted.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemCoolingWaterHeatExchangerAssisted.cpp`, and `src/epmodel/test/CoilSystemCoolingWaterHeatExchangerAssisted_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted child-object and topology helpers without changing the preserved scalar signatures.
    /** @name Heat exchanger object type */
    //@{
    std::string heatExchangerObjectType() const;
    bool setHeatExchangerObjectType(const std::string& heatExchangerObjectType);
    //@}

    /** @name Cooling coil object type */
    //@{
    std::string coolingCoilObjectType() const;
    bool setCoolingCoilObjectType(const std::string& coolingCoilObjectType);
    //@}

   protected:
    using ImplType = detail::CoilSystemCoolingWaterHeatExchangerAssisted_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit CoilSystemCoolingWaterHeatExchangerAssisted(std::shared_ptr<detail::CoilSystemCoolingWaterHeatExchangerAssisted_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
