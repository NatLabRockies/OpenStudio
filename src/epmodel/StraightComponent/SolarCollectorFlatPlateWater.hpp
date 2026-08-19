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

/** \brief A flat-plate water solar collector.
 *
 * \par EnergyPlus object
 * \epobject{group-solar-collectors.html#solarcollectorflatplatewater,SolarCollector:FlatPlate:Water}
 *
 * \par Important behavior
 * Performance relationship, maximum flow, and plant-supply placement map directly to SolarCollector:FlatPlate:Water.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::SolarCollectorFlatPlateWater</code>.
 *
 * \par Known limitations
 * The canonical surface()/setSurface() relationship is not available because EPModel has no shared planar-surface wrapper.
 */
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
