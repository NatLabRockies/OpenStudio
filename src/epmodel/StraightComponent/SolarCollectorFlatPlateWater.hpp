/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORFLATPLATEWATER_HPP
#define EPMODEL_SOLARCOLLECTORFLATPLATEWATER_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class SolarCollectorPerformanceFlatPlate;

  namespace detail {
    class SolarCollectorFlatPlateWater_Impl;
  }

  class EPMODEL_API SolarCollectorFlatPlateWater : public StraightComponent
  {
   public:
    explicit SolarCollectorFlatPlateWater(const Model& model);

    virtual ~SolarCollectorFlatPlateWater() override = default;
    SolarCollectorFlatPlateWater(const SolarCollectorFlatPlateWater& other) = default;
    SolarCollectorFlatPlateWater(SolarCollectorFlatPlateWater&& other) = default;
    SolarCollectorFlatPlateWater& operator=(const SolarCollectorFlatPlateWater&) = default;
    SolarCollectorFlatPlateWater& operator=(SolarCollectorFlatPlateWater&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity.
    // - Canonical Counterpart: openstudio::model::SolarCollectorFlatPlateWater.
    // - Implemented Parity: Default `SolarCollectorPerformanceFlatPlate` ownership, performance replacement/reset, maximum-flow-rate accessors, and
    //   inherited `addToNode(...)` now follow the canonical plant-supply-only behavior.
    // - Documented Delta: The canonical `surface()` / `setSurface(...)` API remains deferred because epmodel does not yet have the shared
    //   planar-surface/shading-surface wrapper abstraction needed to preserve the canonical `PlanarSurface` signature cleanly.
    // - Field/Storage Mapping: The performance relationship and maximum-flow-rate accessor map directly to EnergyPlus
    //   `SolarCollector:FlatPlate:Water` fields used by the forward translator.
    // - Evidence: `src/model/SolarCollectorFlatPlateWater.hpp`, `src/model/SolarCollectorFlatPlateWater.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateSolarCollectorFlatPlateWater.cpp`.
    // - Remaining Parity Work: Add canonical surface helpers once the shared epmodel planar/shading-surface support is in scope.

    /** @name Solar collector performance */
    //@{
    SolarCollectorPerformanceFlatPlate solarCollectorPerformance() const;
    bool setSolarCollectorPerformance(const SolarCollectorPerformanceFlatPlate& solarCollectorPerformanceFlatPlate);
    void resetSolarCollectorPerformance();
    //@}

    /** @name Maximum flow rate */
    //@{
    boost::optional<double> maximumFlowRate() const;
    bool setMaximumFlowRate(double maximumFlowRate);
    void resetMaximumFlowRate();
    //@}

   protected:
    using ImplType = detail::SolarCollectorFlatPlateWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SolarCollectorFlatPlateWater(std::shared_ptr<detail::SolarCollectorFlatPlateWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
