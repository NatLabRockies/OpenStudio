/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORFLATPLATEPHOTOVOLTAICTHERMAL_HPP
#define EPMODEL_SOLARCOLLECTORFLATPLATEPHOTOVOLTAICTHERMAL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SolarCollectorFlatPlatePhotovoltaicThermal_Impl;
  }

  class EPMODEL_API SolarCollectorFlatPlatePhotovoltaicThermal : public StraightComponent
  {
   public:
    explicit SolarCollectorFlatPlatePhotovoltaicThermal(const Model& model);

    virtual ~SolarCollectorFlatPlatePhotovoltaicThermal() override = default;
    SolarCollectorFlatPlatePhotovoltaicThermal(const SolarCollectorFlatPlatePhotovoltaicThermal& other) = default;
    SolarCollectorFlatPlatePhotovoltaicThermal(SolarCollectorFlatPlatePhotovoltaicThermal&& other) = default;
    SolarCollectorFlatPlatePhotovoltaicThermal& operator=(const SolarCollectorFlatPlatePhotovoltaicThermal&) = default;
    SolarCollectorFlatPlatePhotovoltaicThermal& operator=(SolarCollectorFlatPlatePhotovoltaicThermal&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical photovoltaic-thermal solar-collector scalar surface is present, while performance, surface, photovoltaic, and node helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::SolarCollectorFlatPlatePhotovoltaicThermal.
    // - Implemented Parity: The preserved scalar API matches the design-flow accessor with matching reset/autosize behavior.
    // - Documented Delta: Performance, surface, photovoltaic, inlet, and outlet relationship helpers remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: This accessor maps directly to the EnergyPlus `SolarCollector:FlatPlate:PhotovoltaicThermal` design-flow field used by the forward translator.
    // - Evidence: `src/model/SolarCollectorFlatPlatePhotovoltaicThermal.hpp`, `src/model/SolarCollectorFlatPlatePhotovoltaicThermal.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateSolarCollectorFlatPlatePhotovoltaicThermal.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
    boost::optional<double> designFlowRate() const;
    bool setDesignFlowRate(double designFlowRate);
    void resetDesignFlowRate();
    void autosizeDesignFlowRate();
    bool isDesignFlowRateAutosized() const;
    boost::optional<double> autosizedDesignFlowRate() const;

   protected:
    using ImplType = detail::SolarCollectorFlatPlatePhotovoltaicThermal_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SolarCollectorFlatPlatePhotovoltaicThermal(std::shared_ptr<detail::SolarCollectorFlatPlatePhotovoltaicThermal_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
