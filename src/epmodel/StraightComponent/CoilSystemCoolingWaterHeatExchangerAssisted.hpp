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
    // - Status: Near Parity for the selected direct air-loop workload. The canonical child relationships, direct branch identity,
    //   contained air path, plant-connected water coil, and controller/setpoint projection are present.
    // - Canonical Counterpart: openstudio::model::CoilSystemCoolingWaterHeatExchangerAssisted.
    // - Implemented Parity: The constructors, atomic relationship setters, child traversal, direct supply-branch placement, adjacent
    //   rewiring, persistence, and recursive removal preserve the bounded canonical slice. The heat exchanger's two passes and enclosed
    //   water coil form one path, while the water coil remains independently connected to its plant demand branch.
    // - Documented Delta: EnergyPlus gives the wrapper no direct node fields, so inherited boundary getters resolve the heat exchanger's
    //   first inlet and second outlet. A storage-only mixed-air setpoint manager mirrors canonical translation behavior when a supply fan is
    //   present. Other wrapper parents and numerical heat-recovery performance are not claimed.
    // - Field/Storage Mapping: Child targets map through the EnergyPlus object-type/name pairs. Boundary and connector nodes live on the
    //   linked heat exchanger and water coil; the water controller senses the internal cooling-coil outlet.
    // - Evidence: `src/model/CoilSystemCoolingWaterHeatExchangerAssisted.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilSystemCoolingWaterHeatExchangerAssisted.cpp`, and `src/epmodel/test/CoilSystemCoolingWaterHeatExchangerAssisted_GTest.cpp`.
    // - Remaining Parity Work: Prove additional parent families only from representative workflows; do not infer a generic recursive
    //   topology contract from this selected direct-placement path.
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
