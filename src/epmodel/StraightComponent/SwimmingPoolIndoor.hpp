/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SWIMMINGPOOLINDOOR_HPP
#define EPMODEL_SWIMMINGPOOLINDOOR_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace boost {
template <typename T>
class optional;
}

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;

  namespace detail {
    class SwimmingPoolIndoor_Impl;
  }

  class EPMODEL_API SwimmingPoolIndoor : public StraightComponent
  {
   public:
    explicit SwimmingPoolIndoor(const Model& model);

    virtual ~SwimmingPoolIndoor() override = default;
    SwimmingPoolIndoor(const SwimmingPoolIndoor& other) = default;
    SwimmingPoolIndoor(SwimmingPoolIndoor&& other) = default;
    SwimmingPoolIndoor& operator=(const SwimmingPoolIndoor&) = default;
    SwimmingPoolIndoor& operator=(SwimmingPoolIndoor&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The canonical indoor-swimming-pool scalar surface and plant-demand placement contract are present, while the
    //   surface and schedule relationship helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::SwimmingPoolIndoor.
    // - Implemented Parity: The preserved scalar API matches the cover-factor, heating-flow, miscellaneous-power, depth, and occupancy
    //   accessors, including the canonical exposed constructor defaults for average depth, maximum people, heating flow, and miscellaneous
    //   power; `addToNode(...)` now mirrors the canonical plant-demand-only restriction; and the pool water node convenience getters project
    //   the straight-component inlet/outlet topology the same way the canonical wrapper does.
    // - Documented Delta: Surface-name and all schedule relationship helpers remain intentionally omitted from this EnergyPlus-first wrapper,
    //   and the `isCover*Defaulted()` / `resetCover*()` helpers are epmodel-only conveniences with no canonical counterpart.
    // - Field/Storage Mapping: Scalar accessors write directly to EnergyPlus `SwimmingPool:Indoor` fields, while pool water node helpers resolve
    //   the same inlet/outlet node fields used by loop topology and forward translation.
    // - Evidence: `src/model/SwimmingPoolIndoor.hpp`, `src/model/SwimmingPoolIndoor.cpp`,
    //   `src/energyplus/ForwardTranslator/ForwardTranslateSwimmingPoolIndoor.cpp`, and `src/model/test/SwimmingPoolIndoor_GTest.cpp`.
    // - Remaining Parity Work: Add the omitted surface and schedule relationship helpers and decide whether the epmodel-only cover default/reset
    //   helpers should remain a documented divergence or be folded back behind canonical-style behavior.
    double averageDepth() const;
    bool setAverageDepth(double averageDepth);

    double coverEvaporationFactor() const;
    bool isCoverEvaporationFactorDefaulted() const;
    bool setCoverEvaporationFactor(double coverEvaporationFactor);
    void resetCoverEvaporationFactor();

    double coverConvectionFactor() const;
    bool isCoverConvectionFactorDefaulted() const;
    bool setCoverConvectionFactor(double coverConvectionFactor);
    void resetCoverConvectionFactor();

    double coverShortWavelengthRadiationFactor() const;
    bool isCoverShortWavelengthRadiationFactorDefaulted() const;
    bool setCoverShortWavelengthRadiationFactor(double coverShortWavelengthRadiationFactor);
    void resetCoverShortWavelengthRadiationFactor();

    double coverLongWavelengthRadiationFactor() const;
    bool isCoverLongWavelengthRadiationFactorDefaulted() const;
    bool setCoverLongWavelengthRadiationFactor(double coverLongWavelengthRadiationFactor);
    void resetCoverLongWavelengthRadiationFactor();

    double poolHeatingSystemMaximumWaterFlowRate() const;
    bool setPoolHeatingSystemMaximumWaterFlowRate(double poolHeatingSystemMaximumWaterFlowRate);

    double poolMiscellaneousEquipmentPower() const;
    bool setPoolMiscellaneousEquipmentPower(double poolMiscellaneousEquipmentPower);

    double maximumNumberofPeople() const;
    bool setMaximumNumberofPeople(double maximumNumberofPeople);

    boost::optional<Node> poolWaterInletNode() const;
    boost::optional<Node> poolWaterOutletNode() const;

   protected:
    using ImplType = detail::SwimmingPoolIndoor_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    explicit SwimmingPoolIndoor(std::shared_ptr<detail::SwimmingPoolIndoor_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
