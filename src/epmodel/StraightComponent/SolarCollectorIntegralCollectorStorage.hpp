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

    // Schema Alignment Notes:
    // - Status: Scalar Parity. The canonical integral-collector-storage scalar surface is present, while collector, surface, and node helpers remain out of scope.
    // - Canonical Counterpart: openstudio::model::SolarCollectorIntegralCollectorStorage.
    // - Implemented Parity: The preserved scalar API matches the bottom-surface boundary-condition and maximum-flow-rate accessors with matching default behavior.
    // - Documented Delta: Collector-storage parameters, boundary-condition model linkage, and inlet/outlet node helpers remain intentionally excluded from this scalar pass.
    // - Field/Storage Mapping: These accessors map directly to EnergyPlus `SolarCollector:IntegralCollectorStorage` scalar fields used by the forward translator.
    // - Evidence: `src/model/SolarCollectorIntegralCollectorStorage.hpp`, `src/model/SolarCollectorIntegralCollectorStorage.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateSolarCollectorIntegralCollectorStorage.cpp`.
    // - Remaining Parity Work: Add the omitted relationship helpers without changing the preserved scalar signatures.
    // Bottom surface boundary conditions type
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
