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
    // - Status: Near Parity for the selected unitary-system workload. The canonical child-object relationships, constructor defaults,
    //   ownership lifecycle, and contained air path are present, while standalone branch insertion remains intentionally rejected.
    // - Canonical Counterpart: openstudio::model::CoilSystemCoolingDXHeatExchangerAssisted.
    // - Implemented Parity: The constructors, `heatExchanger`, `coolingCoil`, atomic relationship setters, child traversal, recursive
    //   removal, and standalone `addToNode(...)` rejection preserve the bounded canonical slice. When owned by an
    //   `AirLoopHVACUnitarySystem`, the heat-exchanger inlet, first-pass outlet, DX coil, second-pass inlet, and heat-exchanger outlet form
    //   one persisted air path.
    // - Documented Delta: EnergyPlus gives the wrapper no direct node fields, so `inletPort()` and `outletPort()` remain zero while the
    //   inherited model-object getters resolve the heat exchanger's boundary nodes. Broader supported-parent coverage is not claimed.
    // - Field/Storage Mapping: Relationship targets map directly to the EnergyPlus heat-exchanger and cooling-coil name fields and their
    //   synchronized object types. Boundary and connector nodes live on the linked heat exchanger and DX coil.
    // - Evidence: `src/model/CoilSystemCoolingDXHeatExchangerAssisted.hpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemCoolingDXHeatExchangerAssisted.cpp`,
    //   `src/epmodel/test/CoilSystemCoolingDXHeatExchangerAssisted_GTest.cpp`, and
    //   `src/epmodel/test/AirLoopHVACUnitarySystem_GTest.cpp`.
    // - Remaining Parity Work: Prove other canonical parent families only when a representative workflow requires them; do not generalize
    //   this selected containment contract into recursive topology by inference.

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
