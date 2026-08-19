/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORINTEGRALCOLLECTORSTORAGE_HPP
#define EPMODEL_SOLARCOLLECTORINTEGRALCOLLECTORSTORAGE_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SolarCollectorIntegralCollectorStorage_Impl;
  }

/** \brief An integral-collector-storage solar collector.
 *
 * \par EnergyPlus object
 * \epobject{group-solar-collectors.html#solarcollectorintegralcollectorstorage,SolarCollector:IntegralCollectorStorage}
 *
 * \par Important behavior
 * Bottom-surface boundary-condition and maximum-flow fields map directly to SolarCollector:IntegralCollectorStorage.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model type is <code>openstudio::model::SolarCollectorIntegralCollectorStorage</code>.
 *
 * \par Known limitations
 * Collector, surface, and explicit node relationship helpers are not available.
 */
  class EPMODEL_API SolarCollectorIntegralCollectorStorage : public StraightComponent
  {
   public:
    explicit SolarCollectorIntegralCollectorStorage(const Model& model);

    virtual ~SolarCollectorIntegralCollectorStorage() override = default;
    SolarCollectorIntegralCollectorStorage(const SolarCollectorIntegralCollectorStorage& other) = default;
    SolarCollectorIntegralCollectorStorage(SolarCollectorIntegralCollectorStorage&& other) = default;
    SolarCollectorIntegralCollectorStorage& operator=(const SolarCollectorIntegralCollectorStorage&) = default;
    SolarCollectorIntegralCollectorStorage& operator=(SolarCollectorIntegralCollectorStorage&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> bottomSurfaceBoundaryConditionsTypeValues();

    std::string bottomSurfaceBoundaryConditionsType() const;
    bool isBottomSurfaceBoundaryConditionsTypeDefaulted() const;

    // Maximum flow rate
    boost::optional<double> maximumFlowRate() const;
    bool setMaximumFlowRate(double maximumFlowRate);
    void resetMaximumFlowRate();

   protected:
    using ImplType = detail::SolarCollectorIntegralCollectorStorage_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SolarCollectorIntegralCollectorStorage(std::shared_ptr<detail::SolarCollectorIntegralCollectorStorage_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
