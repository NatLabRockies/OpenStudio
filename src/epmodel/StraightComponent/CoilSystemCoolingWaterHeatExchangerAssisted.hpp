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
    // - API: Preserve openstudio::model class naming for counterpart CoilSystemCoolingWaterHeatExchangerAssisted.
    // - API: Keep counterpart-driven naming even when inventory rows are seeded under unrelated IDD types during serial queue runs.
    // - Field Mapping: heatExchangerObjectType/coolingCoilObjectType map to EnergyPlus CoilSystem:Cooling:Water:HeatExchangerAssisted choice fields.
    // - ForwardTranslator evidence: ForwardTranslateCoilSystemCoolingWaterHeatExchangerAssisted sets these object-type fields from translated child objects.
    // - Field Mapping: Heat Exchanger Name, Cooling Coil Name, and inlet/outlet node links are relationship-like and intentionally excluded from scalar APIs.
    // - TODO(parity): Add relationship APIs in a dedicated parity pass without changing scalar signatures.
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
