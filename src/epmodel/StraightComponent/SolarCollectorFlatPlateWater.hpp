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
    // - Status: Scalar Parity. The canonical flat-plate-water solar-collector scalar surface is present, while performance, surface, and node helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::SolarCollectorFlatPlateWater.
    // - Implemented Parity: The preserved scalar API matches the maximum-flow-rate accessor with matching reset/default behavior.
    // - Documented Delta: Performance, surface, inlet, and outlet relationship helpers remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: This accessor maps directly to the EnergyPlus `SolarCollector:FlatPlate:Water` maximum-flow-rate field used by the forward translator.
    // - Evidence: `src/model/SolarCollectorFlatPlateWater.hpp`, `src/model/SolarCollectorFlatPlateWater.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateSolarCollectorFlatPlateWater.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.

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
