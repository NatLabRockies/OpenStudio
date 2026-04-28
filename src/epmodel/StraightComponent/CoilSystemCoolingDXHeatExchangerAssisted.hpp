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
  class Node;
  class AirToAirComponent;

  namespace detail {
    class CoilSystemCoolingDXHeatExchangerAssisted_Impl;
  }

  class EPMODEL_API CoilSystemCoolingDXHeatExchangerAssisted : public StraightComponent
  {
   public:
    explicit CoilSystemCoolingDXHeatExchangerAssisted(const Model& model);
    explicit CoilSystemCoolingDXHeatExchangerAssisted(const Model& model, const AirToAirComponent& heatExchanger);

    virtual ~CoilSystemCoolingDXHeatExchangerAssisted() override = default;
    CoilSystemCoolingDXHeatExchangerAssisted(const CoilSystemCoolingDXHeatExchangerAssisted& other) = default;
    CoilSystemCoolingDXHeatExchangerAssisted(CoilSystemCoolingDXHeatExchangerAssisted&& other) = default;
    CoilSystemCoolingDXHeatExchangerAssisted& operator=(const CoilSystemCoolingDXHeatExchangerAssisted&) = default;
    CoilSystemCoolingDXHeatExchangerAssisted& operator=(CoilSystemCoolingDXHeatExchangerAssisted&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatExchangerObjectTypeValues();
    static std::vector<std::string> coolingCoilObjectTypeValues();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical child-object relationships and constructor defaults are now present, while standalone branch
    //   insertion remains intentionally rejected and broader model-owned topology helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::CoilSystemCoolingDXHeatExchangerAssisted.
    // - Implemented Parity: The default constructors, `heatExchanger`, `coolingCoil`, their relationship setters, child traversal, and
    //   standalone `addToNode(...)` rejection preserve the bounded canonical slice for the assisted DX coil-system wrapper.
    // - Documented Delta: Heat-exchanger name, cooling-coil name, and broader model-owned topology helpers from canonical
    //   `openstudio::model::CoilSystemCoolingDXHeatExchangerAssisted` are not exposed yet.
    // - Field/Storage Mapping: Relationship targets map directly to the EnergyPlus heat-exchanger and cooling-coil name fields, while the
    //   object-type choices are synchronized from the linked targets' IDD object names.
    // - Evidence: `src/model/CoilSystemCoolingDXHeatExchangerAssisted.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemCoolingDXHeatExchangerAssisted.cpp`, and `src/epmodel/test/CoilSystemCoolingDXHeatExchangerAssisted_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted name conveniences and any broader model-owned topology helpers without changing the preserved
    //   relationship signatures.

    AirToAirComponent heatExchanger() const;
    bool setHeatExchanger(const AirToAirComponent& heatExchanger);

    StraightComponent coolingCoil() const;
    bool setCoolingCoil(const StraightComponent& coolingCoil);

    bool addToNode(Node& node);

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
