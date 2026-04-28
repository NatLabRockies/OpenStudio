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
  class Node;
  class AirToAirComponent;
  class WaterToAirComponent;

  namespace detail {
    class CoilSystemCoolingWaterHeatExchangerAssisted_Impl;
  }

  class EPMODEL_API CoilSystemCoolingWaterHeatExchangerAssisted : public StraightComponent
  {
   public:
    explicit CoilSystemCoolingWaterHeatExchangerAssisted(const Model& model);
    explicit CoilSystemCoolingWaterHeatExchangerAssisted(const Model& model, const AirToAirComponent& heatExchanger);

    virtual ~CoilSystemCoolingWaterHeatExchangerAssisted() override = default;
    CoilSystemCoolingWaterHeatExchangerAssisted(const CoilSystemCoolingWaterHeatExchangerAssisted& other) = default;
    CoilSystemCoolingWaterHeatExchangerAssisted(CoilSystemCoolingWaterHeatExchangerAssisted&& other) = default;
    CoilSystemCoolingWaterHeatExchangerAssisted& operator=(const CoilSystemCoolingWaterHeatExchangerAssisted&) = default;
    CoilSystemCoolingWaterHeatExchangerAssisted& operator=(CoilSystemCoolingWaterHeatExchangerAssisted&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatExchangerObjectTypeValues();
    static std::vector<std::string> coolingCoilObjectTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical child-object relationships, object-type helpers, and topology gate used by this wrapper are
    //   present, while the heat-exchanger link remains a raw-name/object-type field per the underlying schema.
    // - Canonical Counterpart: openstudio::model::CoilSystemCoolingWaterHeatExchangerAssisted.
    // - Implemented Parity: The default constructors, `coolingCoil`, its tracked relationship setter, `heatExchanger`, and child traversal
    //   preserve the wrapper slice that the EnergyPlus schema supports for this object.
    // - Documented Delta: The heat-exchanger slot is stored as a schema-valid name plus object-type pair rather than a tracked object-list
    //   relationship; broader model-owned behavior outside this wrapper remains out of scope.
    // - Field/Storage Mapping: Cooling-coil targets map through the EnergyPlus object-list field, while the heat-exchanger target is resolved
    //   by name and synchronized through the companion object-type field.
    // - Evidence: `src/model/CoilSystemCoolingWaterHeatExchangerAssisted.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemCoolingWaterHeatExchangerAssisted.cpp`, and `src/epmodel/test/CoilSystemCoolingWaterHeatExchangerAssisted_GTest.cpp`.
    // - Remaining Parity Work: Extend the wrapper only if additional canonical surfaces are explicitly needed.
    AirToAirComponent heatExchanger() const;
    bool setHeatExchanger(const AirToAirComponent& heatExchanger);

    WaterToAirComponent coolingCoil() const;
    bool setCoolingCoil(const WaterToAirComponent& coolingCoil);

    bool addToNode(Node& node);
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
