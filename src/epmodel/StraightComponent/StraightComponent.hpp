/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_STRAIGHTCOMPONENT_HPP
#define EPMODEL_STRAIGHTCOMPONENT_HPP

#include "HVACComponent/HVACComponent.hpp"
#include "ModelObject.hpp"
#include "Loop/AirLoopHVAC.hpp"

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class StraightComponent_Impl;
  }

  class EPMODEL_API StraightComponent : public HVACComponent
  {
   public:
    virtual ~StraightComponent() override = default;
    StraightComponent() = default;
    StraightComponent(const StraightComponent& other) = default;
    StraightComponent(StraightComponent&& other) = default;
    StraightComponent& operator=(const StraightComponent&) = default;
    StraightComponent& operator=(StraightComponent&&) = default;

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical single-inlet/single-outlet topology contract is present, but the base straight-component surface is still slightly narrower than `openstudio::model`.
    // - Canonical Counterpart: openstudio::model::StraightComponent.
    // - Implemented Parity: `removeFromLoop`, `inletPort`, `outletPort`, `inletModelObject`, and `outletModelObject` preserve the canonical straight-component topology contract used throughout air and plant equipment wrappers.
    // - Documented Delta: The base epmodel wrapper does not yet re-expose the canonical `airLoopHVAC()` override or other model-side convenience beyond what already comes from `HVACComponent`.
    // - Field/Storage Mapping: Inlet and outlet relationships are resolved from EnergyPlus-backed loop topology and transient connective-tissue objects rather than OpenStudio `Connection` storage.
    // - Evidence: `src/model/StraightComponent.hpp` defines the canonical base surface that this wrapper is matching selectively.
    // - Remaining Parity Work: Add any remaining base-level convenience overrides once the loop/topology family is fully normalized.
    bool removeFromLoop();

    unsigned inletPort() const;
    boost::optional<ModelObject> inletModelObject() const;

    unsigned outletPort() const;
    boost::optional<ModelObject> outletModelObject() const;

   protected:
    friend class Model;
    friend class openstudio::IdfObject;

    using ImplType = detail::StraightComponent_Impl;

    StraightComponent(IddObjectType type, const Model& model, bool fastName = false, bool isTransient = false);
    explicit StraightComponent(std::shared_ptr<detail::StraightComponent_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
