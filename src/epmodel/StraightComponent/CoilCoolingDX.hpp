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
  class Node;
  class Schedule;
  class ThermalZone;
  class CoilCoolingDXCurveFitPerformance;

  namespace detail {
    class CoilCoolingDX_Impl;
  }

  class EPMODEL_API CoilCoolingDX : public StraightComponent
  {
   public:
    explicit CoilCoolingDX(const Model& model);
    explicit CoilCoolingDX(const Model& model, const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance);

    virtual ~CoilCoolingDX() override = default;
    CoilCoolingDX(const CoilCoolingDX& other) = default;
    CoilCoolingDX(CoilCoolingDX&& other) = default;
    CoilCoolingDX& operator=(const CoilCoolingDX&) = default;
    CoilCoolingDX& operator=(CoilCoolingDX&&) = default;

    static IddObjectType iddObjectType();

    bool addToNode(Node& node);

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical schedule/performance/condenser-zone surface, curve-fit performance graph, condenser outdoor-air
    //   storage, and persisted-adapter supply-side air-loop lifecycle are exposed, while the extra condenser-node name accessors remain and the
    //   broader AFN/tank-link and DOAS insertion surfaces are still intentionally deferred.
    // - Canonical Counterpart: openstudio::model::CoilCoolingDX.
    // - Implemented Parity: `availabilitySchedule`, `setAvailabilitySchedule`, `performanceObject`, `setPerformanceObject`, `condenserZone`,
    //   `setCondenserZone`, `resetCondenserZone`, `addToNode` for ordinary supply branches, live branch movement, detach/remove/re-add, the
    //   inherited straight-component ports, and the extra condenser inlet/outlet node-name accessors preserve the bounded contract.
    //   Required condenser nodes receive canonical names, the inlet is declared through valid EnergyPlus outdoor-air storage, and default node
    //   names are live NodeType relationships and follow coil rename, reload, shared declaration, and removal lifecycles.
    // - Documented Delta: AirflowNetworkEquivalentDuct, condensate/evaporative tank-link parity, and the canonical dedicated-outdoor-air
    //   insertion path remain explicitly deferred for this slice.
    // - Field/Storage Mapping: Coil state maps to `Coil:Cooling:DX`; its condenser inlet uses an existing `OutdoorAir:Node` or a generated
    //   one-row `OutdoorAir:NodeList`; direct supply placement persists one `CoilSystem:Cooling:DX` on the Branch, synchronizes both objects'
    //   inlet/outlet nodes and the adapter sensor, and projects this coil as the public AirLoopHVAC component.
    // - Evidence: `src/model/CoilCoolingDX.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDX.cpp`, and
    //   `src/epmodel/test/CoilCoolingDX_GTest.cpp`.
    // - Remaining Parity Work: Add the deferred AFN, tank-link, and dedicated-outdoor-air insertion APIs, and establish scoped workflow and
    //   simulation behavior. Other DX child families remain outside this adapter topology contract until separately characterized.
    Schedule availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);

    boost::optional<ThermalZone> condenserZone() const;
    bool setCondenserZone(const ThermalZone& thermalZone);
    void resetCondenserZone();

    CoilCoolingDXCurveFitPerformance performanceObject() const;
    bool setPerformanceObject(const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance);

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
