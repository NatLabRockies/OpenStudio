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
    // - API: Preserve openstudio::model::SolarCollectorIntegralCollectorStorage scalar accessor names/signatures.
    // - Field Mapping: bottomSurfaceBoundaryConditionsType and isBottomSurfaceBoundaryConditionsTypeDefaulted map to E+
    //   SolarCollector:IntegralCollectorStorage Bottom Surface Boundary Conditions Type.
    // - Field Mapping: maximumFlowRate/setMaximumFlowRate/resetMaximumFlowRate map to E+
    //   SolarCollector:IntegralCollectorStorage Maximum Flow Rate.
    // - Field Mapping: integral collector storage parameters, surface, boundary condition model name, and inlet/outlet node
    //   linkage are excluded relationship-like/non-scalar APIs in this scaffold pass.
    // - ForwardTranslator evidence: ForwardTranslateSolarCollectorIntegralCollectorStorage.cpp writes
    //   bottomSurfaceBoundaryConditionsType() and maximumFlowRate() to matching E+ fields.
    // - TODO(parity): add excluded non-scalar APIs incrementally without changing preserved scalar signatures.
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
