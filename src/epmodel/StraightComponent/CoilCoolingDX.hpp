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
    // - Status: Partial Parity. The canonical schedule/performance/condenser-zone surface plus the current epmodel supply-side air-loop
    //   insertion path are now exposed, while the existing condenser-node scalar shim remains and the broader AFN/tank-link and DOAS
    //   insertion surfaces are still intentionally deferred.
    // - Canonical Counterpart: openstudio::model::CoilCoolingDX.
    // - Implemented Parity: `availabilitySchedule`, `setAvailabilitySchedule`, `performanceObject`, `setPerformanceObject`, `condenserZone`,
    //   `setCondenserZone`, `resetCondenserZone`, `addToNode` for the current supply-side air-loop path, the inherited straight-component ports,
    //   and the existing condenser inlet/outlet node-name scalar accessors preserve the bounded canonical contract.
    // - Documented Delta: AirflowNetworkEquivalentDuct, condensate/evaporative tank-link parity, and the canonical dedicated-outdoor-air
    //   insertion path remain explicitly deferred for this slice.
    // - Field/Storage Mapping: The preserved API maps directly to EnergyPlus `Coil:Cooling:DX` schedule, performance-object, condenser-zone,
    //   condenser node-name fields, plus the inherited inlet/outlet node wiring used for the current air-loop insertion path.
    // - Evidence: `src/model/CoilCoolingDX.hpp` and `src/energyplus/ForwardTranslator/ForwardTranslateCoilCoolingDX.cpp`.
    // - Remaining Parity Work: Add the deferred AFN, tank-link, and dedicated-outdoor-air insertion helpers when the relationship surface is
    //   expanded further.
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
