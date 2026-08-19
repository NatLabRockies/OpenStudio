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

/** \brief A flat-plate photovoltaic-thermal solar collector.
 *
 * \par EnergyPlus object
 * \epobject{group-solar-collectors.html#solarcollectorflatplatephotovoltaicthermal,SolarCollector:FlatPlate:PhotovoltaicThermal}
 *
 * \par Important behavior
 * Design-flow and air/water node insertion map directly to SolarCollector:FlatPlate:PhotovoltaicThermal.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::SolarCollectorFlatPlatePhotovoltaicThermal</code>.
 *
 * \par Known limitations
 * Performance, surface, photovoltaic, and explicit inlet/outlet relationship helpers are not available; autosized design-flow results are unresolved.
 */
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
