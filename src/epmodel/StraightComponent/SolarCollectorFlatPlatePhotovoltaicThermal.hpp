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
    // - API: Preserve openstudio::model::SolarCollectorFlatPlatePhotovoltaicThermal scalar accessor names/signatures.
    // - Field Mapping: designFlowRate maps directly to E+ SolarCollector:FlatPlate:PhotovoltaicThermal DesignFlowRate.
    // - Field Mapping: relationship/node fields (performance, surface, photovoltaic, inlet/outlet nodes) are intentionally excluded from this scalar scaffold.
    // - ForwardTranslator evidence: ForwardTranslateSolarCollectorFlatPlatePhotovoltaicThermal.cpp reads designFlowRate() and writes DesignFlowRate.
    // - TODO(parity): add non-scalar relationship APIs incrementally without changing preserved scalar signatures.
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
